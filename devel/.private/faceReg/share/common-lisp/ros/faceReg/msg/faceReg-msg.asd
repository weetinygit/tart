
(cl:in-package :asdf)

(defsystem "faceReg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "facePose" :depends-on ("_package_facePose"))
    (:file "_package_facePose" :depends-on ("_package"))
  ))