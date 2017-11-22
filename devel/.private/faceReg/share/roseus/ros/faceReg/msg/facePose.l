;; Auto-generated. Do not edit!


(when (boundp 'faceReg::facePose)
  (if (not (find-package "FACEREG"))
    (make-package "FACEREG"))
  (shadow 'facePose (find-package "FACEREG")))
(unless (find-package "FACEREG::FACEPOSE")
  (make-package "FACEREG::FACEPOSE"))

(in-package "ROS")
;;//! \htmlinclude facePose.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass faceReg::facePose
  :super ros::object
  :slots (_header _trans_x _trans_y _trans_z _rot_x _rot_y _rot_z ))

(defmethod faceReg::facePose
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:trans_x __trans_x) 0.0)
    ((:trans_y __trans_y) 0.0)
    ((:trans_z __trans_z) 0.0)
    ((:rot_x __rot_x) 0.0)
    ((:rot_y __rot_y) 0.0)
    ((:rot_z __rot_z) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _trans_x (float __trans_x))
   (setq _trans_y (float __trans_y))
   (setq _trans_z (float __trans_z))
   (setq _rot_x (float __rot_x))
   (setq _rot_y (float __rot_y))
   (setq _rot_z (float __rot_z))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:trans_x
   (&optional __trans_x)
   (if __trans_x (setq _trans_x __trans_x)) _trans_x)
  (:trans_y
   (&optional __trans_y)
   (if __trans_y (setq _trans_y __trans_y)) _trans_y)
  (:trans_z
   (&optional __trans_z)
   (if __trans_z (setq _trans_z __trans_z)) _trans_z)
  (:rot_x
   (&optional __rot_x)
   (if __rot_x (setq _rot_x __rot_x)) _rot_x)
  (:rot_y
   (&optional __rot_y)
   (if __rot_y (setq _rot_y __rot_y)) _rot_y)
  (:rot_z
   (&optional __rot_z)
   (if __rot_z (setq _rot_z __rot_z)) _rot_z)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _trans_x
    8
    ;; float64 _trans_y
    8
    ;; float64 _trans_z
    8
    ;; float64 _rot_x
    8
    ;; float64 _rot_y
    8
    ;; float64 _rot_z
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _trans_x
       (sys::poke _trans_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _trans_y
       (sys::poke _trans_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _trans_z
       (sys::poke _trans_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rot_x
       (sys::poke _rot_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rot_y
       (sys::poke _rot_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rot_z
       (sys::poke _rot_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _trans_x
     (setq _trans_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _trans_y
     (setq _trans_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _trans_z
     (setq _trans_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rot_x
     (setq _rot_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rot_y
     (setq _rot_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rot_z
     (setq _rot_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get faceReg::facePose :md5sum-) "efb58ddc3c5f275bf54bdee14c47103a")
(setf (get faceReg::facePose :datatype-) "faceReg/facePose")
(setf (get faceReg::facePose :definition-)
      "Header header
float64 trans_x
float64 trans_y
float64 trans_z
float64 rot_x
float64 rot_y
float64 rot_z

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

")



(provide :faceReg/facePose "efb58ddc3c5f275bf54bdee14c47103a")


