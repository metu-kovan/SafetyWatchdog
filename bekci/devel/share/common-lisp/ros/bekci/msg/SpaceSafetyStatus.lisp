; Auto-generated. Do not edit!


(cl:in-package bekci-msg)


;//! \htmlinclude SpaceSafetyStatus.msg.html

(cl:defclass <SpaceSafetyStatus> (roslisp-msg-protocol:ros-message)
  ((sphere_status
    :reader sphere_status
    :initarg :sphere_status
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass SpaceSafetyStatus (<SpaceSafetyStatus>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SpaceSafetyStatus>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SpaceSafetyStatus)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bekci-msg:<SpaceSafetyStatus> is deprecated: use bekci-msg:SpaceSafetyStatus instead.")))

(cl:ensure-generic-function 'sphere_status-val :lambda-list '(m))
(cl:defmethod sphere_status-val ((m <SpaceSafetyStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bekci-msg:sphere_status-val is deprecated.  Use bekci-msg:sphere_status instead.")
  (sphere_status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SpaceSafetyStatus>) ostream)
  "Serializes a message object of type '<SpaceSafetyStatus>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'sphere_status))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    ))
   (cl:slot-value msg 'sphere_status))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SpaceSafetyStatus>) istream)
  "Deserializes a message object of type '<SpaceSafetyStatus>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'sphere_status) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'sphere_status)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256)))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SpaceSafetyStatus>)))
  "Returns string type for a message object of type '<SpaceSafetyStatus>"
  "bekci/SpaceSafetyStatus")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SpaceSafetyStatus)))
  "Returns string type for a message object of type 'SpaceSafetyStatus"
  "bekci/SpaceSafetyStatus")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SpaceSafetyStatus>)))
  "Returns md5sum for a message object of type '<SpaceSafetyStatus>"
  "5525024a991106c89e7d72a280b60a24")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SpaceSafetyStatus)))
  "Returns md5sum for a message object of type 'SpaceSafetyStatus"
  "5525024a991106c89e7d72a280b60a24")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SpaceSafetyStatus>)))
  "Returns full string definition for message of type '<SpaceSafetyStatus>"
  (cl:format cl:nil "int8[]  sphere_status~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SpaceSafetyStatus)))
  "Returns full string definition for message of type 'SpaceSafetyStatus"
  (cl:format cl:nil "int8[]  sphere_status~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SpaceSafetyStatus>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'sphere_status) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SpaceSafetyStatus>))
  "Converts a ROS message object to a list"
  (cl:list 'SpaceSafetyStatus
    (cl:cons ':sphere_status (sphere_status msg))
))
