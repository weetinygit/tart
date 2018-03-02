// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

    This example program shows how to find frontal human faces in an image and
    estimate their pose.  The pose takes the form of 68 landmarks.  These are
    points on the face such as the corners of the mouth, along the eyebrows, on
    the eyes, and so forth.  
    

    This example is essentially just a version of the face_landmark_detection_ex.cpp
    example modified to use OpenCV's VideoCapture object to read from a camera instead 
    of files.


    Finally, note that the face detector is fastest when compiled with at least
    SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
    chip then you should enable at least SSE2 instructions.  If you are using
    cmake to compile this program you can enable them by using one of the
    following commands when you create the build project:
        cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
    This will set the appropriate compiler options for GCC, clang, Visual
    Studio, or the Intel compiler.  If you are using another compiler then you
    need to consult your compiler's manual to determine how to enable these
    instructions.  Note that AVX is the fastest but requires a CPU from at least
    2011.  SSE4 is the next fastest and is supported by most current machines.  
*/

#include <dlib/opencv.h>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <faceReg/facePose.h>

#include <tf/transform_broadcaster.h>

#include <sstream>

using namespace dlib;
using namespace std;

int main(int argc, char **argv)
{
    //3D model points used for pose estimation
    std::vector<cv::Point3d> model_points;
    model_points.push_back(cv::Point3d(0.0f, 0.0f, 0.0f));               // Nose tip
    model_points.push_back(cv::Point3d(0.0f, -330.0f, -65.0f));          // Chin
    model_points.push_back(cv::Point3d(-225.0f, 170.0f, -135.0f));       // Left eye left corner
    model_points.push_back(cv::Point3d(225.0f, 170.0f, -135.0f));        // Right eye right corner
    model_points.push_back(cv::Point3d(-150.0f, -150.0f, -125.0f));      // Left Mouth corner
    model_points.push_back(cv::Point3d(150.0f, -150.0f, -125.0f));       // Right
    
    //For ROS
    ros::init(argc, argv, "talker");    //Initialize ROS
    ros::NodeHandle n;
    ros::Publisher facePose_pub = n.advertise<faceReg::facePose>("facePose", 10);
    ros::Rate loop_rate(10);
	
	//For TF
	tf::TransformBroadcaster br;
    
    faceReg::facePose rosMsg;
    
    //For averaging poses throughout
    int averageCount = 0;
    cv::Mat_<double> transAve = cv::Mat(3,1, CV_32F, 0.0);
    cv::Mat_<double> rotateAve = cv::Mat(3,1, CV_32F, 0.0);
    
    

    
    try
    {
        cv::VideoCapture cap(1);
        if (!cap.isOpened())
        {
            cerr << "Unable to connect to camera" << endl;
            return 1;
        }

        image_window win;

        // Load face detection and pose estimation models.
        frontal_face_detector detector = get_frontal_face_detector();
        shape_predictor pose_model;
        deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;

        // Grab and process frames until the main window is closed by the user.
        while(!win.is_closed())
        {
            // Grab a frame
            cv::Mat temp;
            if (!cap.read(temp))
            {
                break;
            }
            // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
            // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
            // long as temp is valid.  Also don't do anything to temp that would cause it
            // to reallocate the memory which stores the image as that will make cimg
            // contain dangling pointers.  This basically means you shouldn't modify temp
            // while using cimg.
			transpose(temp, temp);
            cv_image<bgr_pixel> cimg(temp);

            // Detect faces 
            std::vector<rectangle> faces = detector(cimg);
            // Find the pose of each face.
            std::vector<full_object_detection> shapes;
            for (unsigned long i = 0; i < faces.size(); ++i) {
                full_object_detection pose = pose_model(cimg, faces[i]);
                //Generate 2D locations of specific landmarks
                std::vector<cv::Point2d> image_points;
                image_points.push_back( cv::Point2d((int)pose.part(33)(0), (int)pose.part(33)(1)));  // Nose tip
                image_points.push_back( cv::Point2d((int)pose.part(8)(0), (int)pose.part(8)(1)));    // Chin
                image_points.push_back( cv::Point2d((int)pose.part(36)(0), (int)pose.part(36)(1)));  // Left eye left corner
                image_points.push_back( cv::Point2d((int)pose.part(45)(0), (int)pose.part(45)(1)));  // Right eye right corner
                image_points.push_back( cv::Point2d((int)pose.part(48)(0), (int)pose.part(48)(1)));  // Left Mouth corner
                image_points.push_back( cv::Point2d((int)pose.part(54)(0), (int)pose.part(54)(1)));  // Right mouth corner
                
                // Camera internals
                double focal_length = temp.cols; // Approximate focal length.
                cv::Point2d center = cv::Point2d(temp.cols/2,temp.rows/2);
                cv::Mat camera_matrix = (cv::Mat_<double>(3,3) << focal_length, 0, center.x, 0 , focal_length, center.y, 0, 0, 1);
                cv::Mat dist_coeffs = cv::Mat::zeros(4,1,cv::DataType<double>::type); // Assuming no lens distortion
                cout << "Camera Matrix " << endl << camera_matrix << endl ;

                // Output rotation and translation
                cv::Mat rotation_vector; // Rotation in axis-angle form
                cv::Mat translation_vector;
     
                // Solve for pose
                cv::solvePnP(model_points, image_points, camera_matrix, dist_coeffs, rotation_vector, translation_vector);
                
                //Averaging pose across 3 frames
                transAve = transAve + translation_vector;
                rotateAve = rotateAve + rotation_vector;
                
                if (averageCount == 2){
                
                transAve = transAve/3;
                rotateAve = rotateAve/3;
                     
 
     
                // Project a 3D point (0, 0, 1000.0) onto the image plane.
                // We use this to draw a line sticking out of the nose
                
     
                std::vector<cv::Point3d> nose_end_point3D;
                std::vector<cv::Point2d> nose_end_point2D;
                nose_end_point3D.push_back(cv::Point3d(0,0,1000.0));
                projectPoints(nose_end_point3D, rotateAve, transAve, camera_matrix, dist_coeffs, nose_end_point2D);
                
                for(int i=0; i < image_points.size(); i++) {
                circle(temp, image_points[i], 3, cv::Scalar(0,0,255), -1);
                }
     
                cv::line(temp,image_points[0], nose_end_point2D[0], cv::Scalar(255,0,0), 2);
     
                cout << "Rotation Vector " << endl << rotateAve << endl;
                cout << "Translation Vector" << endl << transAve << endl;
                cout <<transAve(1)<<endl;
                
                
                
                
                if (ros::ok()) {  
                /*** This is a message object. You stuff it with data, and then publish it.*/
                rosMsg.header.stamp = ros::Time::now();
                rosMsg.header.frame_id = "/tablet";
                rosMsg.trans_x = transAve(0);
                rosMsg.trans_y = transAve(1);
                rosMsg.trans_z = transAve(2);
                rosMsg.rot_x = rotateAve(0);
                rosMsg.rot_y = rotateAve(1);
                rosMsg.rot_z = rotateAve(2);
                facePose_pub.publish(rosMsg);
                
                /***std_msgs::String msg;
                std::stringstream ss;
                ss << "hello world " << count;
                msg.data = ss.str();
                ROS_INFO("%s", msg.data.c_str());
                */
                /**
                * The publish() function is how you send messages. The parameter
                * is the message object. The type of this object must agree with the type
                * given as a template parameter to the advertise<>() call, as was done
                * in the constructor above.
                */
                /***chatter_pub.publish(msg);
				*/
                ros::spinOnce();
                loop_rate.sleep();
                }
                }
                //Reset averages count
                averageCount++;
                if (averageCount>=3) {
                averageCount = 0; 
                transAve = cv::Mat(3,1, CV_32F, 0.0);
                rotateAve = cv::Mat(3,1, CV_32F, 0.0);
                }
     
                // You get the idea, you can get all the face part locations if
                // you want them.  Here we just store them in shapes so we can
                // put them on the screen.
                
                shapes.push_back(pose);
             }
             

            //cout << "Rotation Vector " << endl << rotation_vector << endl;
            //cout << "Translation Vector" << endl << translation_vector << endl;

            // Display it all on the screen

            win.clear_overlay();
            win.set_image(cimg);
            win.add_overlay(render_face_detections(shapes));
        }
    }
    catch(serialization_error& e)
    {
        cout << "You need dlib's default face landmarking model file to run this example." << endl;
        cout << "You can get it from the following URL: " << endl;
        cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
        cout << endl << e.what() << endl;
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }
}

