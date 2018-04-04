; Auto-generated. Do not edit!


(cl:in-package bekci-msg)


;//! \htmlinclude JointVelocity.msg.html

(cl:defclass <JointVelocity> (roslisp-msg-protocol:ros-message)
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
   (velocities
    :reader velocities
    :initarg :velocities
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass JointVelocity (<JointVelocity>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <JointVelocity>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'JointVelocity)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bekci-msg:<JointVelocity> is deprecated: use bekci-msg:JointVelocity instead.")))

(cl:ensure-generic-function 'DOF-val :lambda-list '(m))
(cl:defmethod DOF-val ((m <JointVelocity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bekci-msg:DOF-val is deprecated.  Use bekci-msg:DOF instead.")
  (DOF m))

(cl:ensure-generic-function 'names-val :lambda-list '(m))
(cl:defmethod names-val ((m <JointVelocity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bekci-msg:names-val is deprecated.  Use bekci-msg:names instead.")
  (names m))

(cl:ensure-generic-function 'velocities-val :lambda-list '(m))
(cl:defmethod velocities-val ((m <JointVelocity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bekci-msg:velocities-val is deprecated.  Use bekci-msg:velocities instead.")
  (velocities m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <JointVelocity>) ostream)
  "Serializes a message object of type '<JointVelocity>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'DOF)) ostream)
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
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'velocities))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'velocities))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <JointVelocity>) istream)
  "Deserializes a message object of type '<JointVelocity>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'DOF)) (cl:read-byte istream))
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
  (cl:setf (cl:slot-value msg 'velocities) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'velocities)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<JointVelocity>)))
  "Returns string type for a message object of type '<JointVelocity>"
  "bekci/JointVelocity")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'JointVelocity)))
  "Returns string type for a message object of type 'JointVelocity"
  "bekci/JointVelocity")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<JointVelocity>)))
  "Returns md5sum for a message object of type '<JointVelocity>"
  "7c001b9923259e52bcef9600eaf6b8f5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'JointVelocity)))
  "Returns md5sum for a message object of type 'JointVelocity"
  "7c001b9923259e52bcef9600eaf6b8f5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<JointVelocity>)))
  "Returns full string definition for message of type '<JointVelocity>"
  (cl:format cl:nil "uint8 DOF~%string[] names~%float64[] velocities~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'JointVelocity)))
  "Returns full string definition for message of type 'JointVelocity"
  (cl:format cl:nil "uint8 DOF~%string[] names~%float64[] velocities~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <JointVelocity>))
  (cl:+ 0
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'names) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'velocities) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <JointVelocity>))
  "Converts a ROS message object to a list"
  (cl:list 'JointVelocity
    (cl:cons ':DOF (DOF msg))
    (cl:cons ':names (names msg))
    (cl:cons ':velocities (velocities msg))
))
