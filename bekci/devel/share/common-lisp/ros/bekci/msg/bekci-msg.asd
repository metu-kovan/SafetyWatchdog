
(cl:in-package :asdf)

(defsystem "bekci-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "JointValue" :depends-on ("_package_JointValue"))
    (:file "_package_JointValue" :depends-on ("_package"))
  ))