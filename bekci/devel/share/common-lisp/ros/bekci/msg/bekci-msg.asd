
(cl:in-package :asdf)

(defsystem "bekci-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Pose" :depends-on ("_package_Pose"))
    (:file "_package_Pose" :depends-on ("_package"))
    (:file "JointValue" :depends-on ("_package_JointValue"))
    (:file "_package_JointValue" :depends-on ("_package"))
    (:file "JointPose" :depends-on ("_package_JointPose"))
    (:file "_package_JointPose" :depends-on ("_package"))
  ))