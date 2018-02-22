; Auto-generated. Do not edit!


(cl:in-package bekci-msg)


;//! \htmlinclude JointPose.msg.html

(cl:defclass <JointPose> (roslisp-msg-protocol:ros-message)
  ((DOF
    :reader DOF
    :initarg :DOF
    :type cl:fixnum
    :initform 0)
   (names
    :reader names
    :initarg :names
    :type (cl:vector cl:string)
   :initform (cl:make-array 0 :element-type 'cl:string :initial-element ""))
   (poses
    :reader poses
    :initarg :poses
    :type (cl:vector bekci-msg:Pose)
   :initform (cl:make-array 0 :element-type 'bekci-msg:Pose :initial-element (cl:make-instance 'bekci-msg:Pose))))
)

(cl:defclass JointPose (<JointPose>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <JointPose>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'JointPose)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bekci-msg:<JointPose> is deprecated: use bekci-msg:JointPose instead.")))

(cl:ensure-generic-function 'DOF-val :lambda-list '(m))
(cl:defmethod DOF-val ((m <JointPose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bekci-msg:DOF-val is deprecated.  Use bekci-msg:DOF instead.")
  (DOF m))

(cl:ensure-generic-function 'names-val :lambda-list '(m))
(cl:defmethod names-val ((m <JointPose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bekci-msg:names-val is deprecated.  Use bekci-msg:names instead.")
  (names m))

(cl:ensure-generic-function 'poses-val :lambda-list '(m))
(cl:defmethod poses-val ((m <JointPose>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bekci-msg:poses-val is deprecated.  Use bekci-msg:poses instead.")
  (poses m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <JointPose>) ostream)
  "Serializes a message object of type '<JointPose>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'DOF)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'DOF)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'names))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__ros_str_len (cl:length ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) ele))
   (cl:slot-value msg 'names))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'poses))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'poses))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <JointPose>) istream)
  "Deserializes a message object of type '<JointPose>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'DOF)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'DOF)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'names) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'names)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:aref vals i) __ros_str_idx) (cl:code-char (cl:read-byte istream))))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'poses) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'poses)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'bekci-msg:Pose))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<JointPose>)))
  "Returns string type for a message object of type '<JointPose>"
  "bekci/JointPose")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'JointPose)))
  "Returns string type for a message object of type 'JointPose"
  "bekci/JointPose")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<JointPose>)))
  "Returns md5sum for a message object of type '<JointPose>"
  "19abeb982f48e5effbac09d592bc2f48")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'JointPose)))
  "Returns md5sum for a message object of type 'JointPose"
  "19abeb982f48e5effbac09d592bc2f48")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<JointPose>)))
  "Returns full string definition for message of type '<JointPose>"
  (cl:format cl:nil "uint16 DOF~%string[] names~%Pose[] poses~%================================================================================~%MSG: bekci/Pose~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'JointPose)))
  "Returns full string definition for message of type 'JointPose"
  (cl:format cl:nil "uint16 DOF~%string[] names~%Pose[] poses~%================================================================================~%MSG: bekci/Pose~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <JointPose>))
  (cl:+ 0
     2
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'names) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'poses) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <JointPose>))
  "Converts a ROS message object to a list"
  (cl:list 'JointPose
    (cl:cons ':DOF (DOF msg))
    (cl:cons ':names (names msg))
    (cl:cons ':poses (poses msg))
))
