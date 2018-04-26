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
#include<math.h>

#include <sstream>


#define X_SCALE 0.01
#define Y_SCALE 0.01
#define Z_SCALE 0.01

#define X_DISPLACE 0
#define Y_DISPLACE -0
#define Z_DISPLACE 0

#define ROLL_SCALE 1
#define PITCH_SCALE -1
#define YAW_SCALE -1

#define SUDDENCHANGETOLERANCE 20
#define NOISECOUNTLIMIT 5

using namespace dlib;
using namespace std;

//Check difference
double measureTranslationChange(cv::Mat_<double> v1, cv::Mat_<double> v2){
	return sqrt((v1(0)-v2(0))*(v1(0)-v2(0))+(v1(1)-v2(1))*(v1(1)-v2(1))+(v1(2)-v2(2))*(v1(2)-v2(2)));
}

int main(int argc, char **argv)
{
    //3D model points used for pose estimation
    std::vector<cv::Point3d> model_points;
    model_points.push_back(cv::Point3d(6.825897, 6.760612, 4.402142));     //#33 left brow left corner
    model_points.push_back(cv::Point3d(1.330353, 7.122144, 6.903745));     //#29 left brow right corner
    model_points.push_back(cv::Point3d(-1.330353, 7.122144, 6.903745));    //#34 right brow left corner
    model_points.push_back(cv::Point3d(-6.825897, 6.760612, 4.402142));    //#38 right brow right corner
    model_points.push_back(cv::Point3d(5.311432, 5.485328, 3.987654));     //#13 left eye left corner
    model_points.push_back(cv::Point3d(1.789930, 5.393625, 4.413414));     //#17 left eye right corner
    model_points.push_back(cv::Point3d(-1.789930, 5.393625, 4.413414));    //#25 right eye left corner
    model_points.push_back(cv::Point3d(-5.311432, 5.485328, 3.987654));    //#21 right eye right corner
    model_points.push_back(cv::Point3d(2.005628, 1.409845, 6.165652));     //#55 nose left corner
    model_points.push_back(cv::Point3d(-2.005628, 1.409845, 6.165652));    //#49 nose right corner
    model_points.push_back(cv::Point3d(2.774015, -2.080775, 5.048531));    //#43 mouth left corner
    model_points.push_back(cv::Point3d(-2.774015, -2.080775, 5.048531));   //#39 mouth right corner
    model_points.push_back(cv::Point3d(0.000000, -3.116408, 6.097667));    //#45 mouth central bottom corner
	model_points.push_back(cv::Point3d(0.000000, -7.415691, 4.070434));    //#6 chin corner
	
	//reproject 3D points world coordinate axis to verify result pose
    std::vector<cv::Point3d> reprojectsrc;
    reprojectsrc.push_back(cv::Point3d(10.0, 10.0, 20.0));
    reprojectsrc.push_back(cv::Point3d(10.0, 10.0, 0.0));
    reprojectsrc.push_back(cv::Point3d(10.0, -10.0, 0.0));
    reprojectsrc.push_back(cv::Point3d(10.0, -10.0, 20.0));
    reprojectsrc.push_back(cv::Point3d(-10.0, 10.0, 20.0));
    reprojectsrc.push_back(cv::Point3d(-10.0, 10.0, 0.0));
    reprojectsrc.push_back(cv::Point3d(-10.0, -10.0, 0.0));
    reprojectsrc.push_back(cv::Point3d(-10.0, -10.0, 20.0));
	
	/*NECESSARY INITIALIZATIONS*/
	
    //reprojected 2D points
    std::vector<cv::Point2d> reprojectdst;
	reprojectdst.resize(8);
	
	// Output rotation and translation
	cv::Mat_<double> rotation_vector, rotation_vector_temp; // Rotation in axis-angle form
	cv::Mat_<double> translation_vector, translation_vector_temp, translation_vector_prev(3,1,0.0f);
	int noiseDataCount = NOISECOUNTLIMIT; //Variable to check if data is noise
	
	//Camera parmeters
	double focal_length; // Approximate focal length.
	cv::Point2d center;
	cv::Mat camera_matrix;
	cv::Mat dist_coeffs; // Assuming no lens distortion
	
	/*old model
    model_points.push_back(cv::Point3d(0.0f, 0.0f, 0.0f));               // Nose tip
    model_points.push_back(cv::Point3d(0.0f, -330.0f, -65.0f));          // Chin
    model_points.push_back(cv::Point3d(-225.0f, 170.0f, -135.0f));       // Left eye left corner
    model_points.push_back(cv::Point3d(225.0f, 170.0f, -135.0f));        // Right eye right corner
    model_points.push_back(cv::Point3d(-150.0f, -150.0f, -125.0f));      // Left Mouth corner
    model_points.push_back(cv::Point3d(150.0f, -150.0f, -125.0f));       // Right
    */
	
    //For ROS
    ros::init(argc, argv, "talker");    //Initialize ROS
    ros::NodeHandle n;
    ros::Publisher facePose_pub = n.advertise<faceReg::facePose>("facePose", 10);
    ros::Rate loop_rate(20);
    faceReg::facePose rosMsg;
	
	cv::Mat rotation_mat;                           //3 x 3 R
    cv::Mat pose_mat = cv::Mat(3, 4, CV_64FC1);     //3 x 4 R | T
	cv::Mat euler_angle = cv::Mat(3, 1, CV_64FC1);
	//temp buf for decomposeProjectionMatrix()
    cv::Mat out_intrinsics = cv::Mat(3, 3, CV_64FC1);
    cv::Mat out_rotation = cv::Mat(3, 3, CV_64FC1);
	cv::Mat out_translation = cv::Mat(3, 1, CV_64FC1);
	//text on screen
	std::ostringstream outtext;
    

    /*START OF VIDEO CAPTURE LOOP*/
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
            cv::Mat temp0, temp;
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
			
			//undistort
			//camera_matrix = (cv::Mat_<double>(3,3) << 2.3227180367866636e+03, 0., 320., 0., 2.3227180367866636e+03, 240., 0., 0., 1.);
			//dist_coeffs = (cv::Mat_<double>(5,1) << 2.7657565130008392e+00, -4.9238754066884417e+02, 0., 0., 1.2714707127163863e+04);
			//cv::undistort(temp0,temp,camera_matrix, dist_coeffs);
			transpose(temp, temp);
			//cv::flip(temp,temp,1);
			//temp.convertTo(temp, -1, 1.5, 10);  //brightness and contrast
			
			
            cv_image<bgr_pixel> cimg(temp);
			

            // Detect faces 
            std::vector<rectangle> faces = detector(cimg);
            // Find the pose of each face.
            std::vector<full_object_detection> shapes;
            for (unsigned long i = 0; i < faces.size(); ++i) {
                full_object_detection pose = pose_model(cimg, faces[i]);
                //Generate 2D locations of specific landmarks
                std::vector<cv::Point2d> image_points;
				
				
				/*old model
                image_points.push_back( cv::Point2d((int)pose.part(33)(0), (int)pose.part(33)(1)));  // Nose tip
                image_points.push_back( cv::Point2d((int)pose.part(8)(0), (int)pose.part(8)(1)));    // Chin
                image_points.push_back( cv::Point2d((int)pose.part(36)(0), (int)pose.part(36)(1)));  // Left eye left corner
                image_points.push_back( cv::Point2d((int)pose.part(45)(0), (int)pose.part(45)(1)));  // Right eye right corner
                image_points.push_back( cv::Point2d((int)pose.part(48)(0), (int)pose.part(48)(1)));  // Left Mouth corner
                image_points.push_back( cv::Point2d((int)pose.part(54)(0), (int)pose.part(54)(1)));  // Right mouth corner
                */
				//fill in 2D ref points, annotations follow https://ibug.doc.ic.ac.uk/resources/300-W/
				//image_points.push_back(cv::Point2d(pose.part(30).x(), pose.part(30).y())); //#30 nose middle
				image_points.push_back(cv::Point2d(pose.part(17).x(), pose.part(17).y())); //#17 left brow left corner
				image_points.push_back(cv::Point2d(pose.part(21).x(), pose.part(21).y())); //#21 left brow right corner
				image_points.push_back(cv::Point2d(pose.part(22).x(), pose.part(22).y())); //#22 right brow left corner
				image_points.push_back(cv::Point2d(pose.part(26).x(), pose.part(26).y())); //#26 right brow right corner
				image_points.push_back(cv::Point2d(pose.part(36).x(), pose.part(36).y())); //#36 left eye left corner
				image_points.push_back(cv::Point2d(pose.part(39).x(), pose.part(39).y())); //#39 left eye right corner
				image_points.push_back(cv::Point2d(pose.part(42).x(), pose.part(42).y())); //#42 right eye left corner
				image_points.push_back(cv::Point2d(pose.part(45).x(), pose.part(45).y())); //#45 right eye right corner
				image_points.push_back(cv::Point2d(pose.part(31).x(), pose.part(31).y())); //#31 nose left corner
				image_points.push_back(cv::Point2d(pose.part(35).x(), pose.part(35).y())); //#35 nose right corner
				image_points.push_back(cv::Point2d(pose.part(48).x(), pose.part(48).y())); //#48 mouth left corner
				image_points.push_back(cv::Point2d(pose.part(54).x(), pose.part(54).y())); //#54 mouth right corner
				image_points.push_back(cv::Point2d(pose.part(57).x(), pose.part(57).y())); //#57 mouth central bottom corner
				image_points.push_back(cv::Point2d(pose.part(8).x(), pose.part(8).y())); //#8 chin corner
				
				
				// Camera internals (original)
				focal_length = temp.cols; // Approximate focal length.
				center = cv::Point2d(temp.cols/2,temp.rows/2);
				camera_matrix = (cv::Mat_<double>(3,3) << focal_length, 0, center.x, 0 , focal_length, center.y, 0, 0, 1);
				dist_coeffs = cv::Mat::zeros(4,1,cv::DataType<double>::type); // Assuming no lens distortion*/
				
				/*// Camera internals (current)
				focal_length = temp.cols; // Approximate focal length.
				center = cv::Point2d(temp.cols/2,temp.rows/2);
				camera_matrix = (cv::Mat_<double>(3,3) << 1.7647874090475282e+03, 0., 320., 0., 1.7647874090475282e+03, 240., 0., 0., 1.);
				dist_coeffs = (cv::Mat_<double>(5,1) << -1.1996815733941411e-01, -1.1389524422393094e+02, 0., 0., 1.9493590560763098e+03);*/
				

				// Solve for pose, account for multiple faces by only taking values from the nearest
				if (i == 0) cv::solvePnP(model_points, image_points, camera_matrix, dist_coeffs, rotation_vector, translation_vector);
				
				else {
				cout << i <<endl;
					cv::solvePnP(model_points, image_points, camera_matrix, dist_coeffs, rotation_vector_temp, translation_vector_temp);		
					if(translation_vector_temp(2)>translation_vector(2)){
						translation_vector = translation_vector_temp;
						rotation_vector = rotation_vector_temp;
					}
				}
				
				for(int i=0; i < image_points.size(); i++) {
				circle(temp, image_points[i], 3, cv::Scalar(0,0,255), -1);
				}
                
                shapes.push_back(pose);
             }
		
			if(faces.size()>0){
				
				/*DRAWING RED VISUAL BOX*/
				//reproject
				cv::projectPoints(reprojectsrc, rotation_vector, translation_vector, camera_matrix, dist_coeffs, reprojectdst);
				cv::line(temp, reprojectdst[0], reprojectdst[1], cv::Scalar(0, 0, 255));
				cv::line(temp, reprojectdst[1], reprojectdst[2], cv::Scalar(0, 0, 255));
				cv::line(temp, reprojectdst[2], reprojectdst[3], cv::Scalar(0, 0, 255));
				cv::line(temp, reprojectdst[3], reprojectdst[0], cv::Scalar(0, 0, 255));
				cv::line(temp, reprojectdst[4], reprojectdst[5], cv::Scalar(0, 0, 255));
				cv::line(temp, reprojectdst[5], reprojectdst[6], cv::Scalar(0, 0, 255));
				cv::line(temp, reprojectdst[6], reprojectdst[7], cv::Scalar(0, 0, 255));
				cv::line(temp, reprojectdst[7], reprojectdst[4], cv::Scalar(0, 0, 255));
				cv::line(temp, reprojectdst[0], reprojectdst[4], cv::Scalar(0, 0, 255));
				cv::line(temp, reprojectdst[1], reprojectdst[5], cv::Scalar(0, 0, 255));
				cv::line(temp, reprojectdst[2], reprojectdst[6], cv::Scalar(0, 0, 255));
				cv::line(temp, reprojectdst[3], reprojectdst[7], cv::Scalar(0, 0, 255));


				//cout << "Translation Vector" << endl << translation_vector << endl;
				//cout << "Rotation Vector " << endl << rotation_vector << endl;
				
				//calc euler angle
				cv::Rodrigues(rotation_vector, rotation_mat);
				cv::hconcat(rotation_mat, translation_vector, pose_mat);
				cv::decomposeProjectionMatrix(pose_mat, out_intrinsics, out_rotation, out_translation, cv::noArray(), cv::noArray(), cv::noArray(), euler_angle);

				//show angle result
				outtext << "X: " << std::setprecision(3) << euler_angle.at<double>(0);
				cv::putText(temp, outtext.str(), cv::Point(50, 40), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 0));
				outtext.str("");
				outtext << "Y: " << std::setprecision(3) << euler_angle.at<double>(1);
				cv::putText(temp, outtext.str(), cv::Point(50, 60), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 0));
				outtext.str("");
				outtext << "Z: " << std::setprecision(3) << euler_angle.at<double>(2);
				cv::putText(temp, outtext.str(), cv::Point(50, 80), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 0));
				outtext.str("");



				if (ros::ok()) {
					//cout<< measureTranslationChange(translation_vector, translation_vector_prev) <<endl;
					if ( ((measureTranslationChange(translation_vector, translation_vector_prev) < SUDDENCHANGETOLERANCE)||(noiseDataCount>NOISECOUNTLIMIT))&&translation_vector(2)<0){
						rosMsg.header.stamp = ros::Time::now();
						rosMsg.header.frame_id = "/face_pos";		

						rosMsg.trans_x = translation_vector(0)*X_SCALE+X_DISPLACE;
						rosMsg.trans_y = translation_vector(1)*Y_SCALE+Y_DISPLACE;
						rosMsg.trans_z = translation_vector(2)*Z_SCALE+Z_DISPLACE;
						rosMsg.rot_x = rotation_vector(0)*ROLL_SCALE;
						rosMsg.rot_y = 0*PITCH_SCALE;
						rosMsg.rot_z = 0;
						facePose_pub.publish(rosMsg);
						noiseDataCount = 0;  //Reset count to 0 upon successful publishing
						translation_vector_prev = translation_vector;  //Record sent pose upon successful publishing
					} else noiseDataCount++;
					//cout<< noiseDataCount <<endl;
					ros::spinOnce();
					loop_rate.sleep();
				}
			}
			
			

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

