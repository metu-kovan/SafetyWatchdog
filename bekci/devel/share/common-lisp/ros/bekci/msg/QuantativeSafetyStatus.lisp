; Auto-generated. Do not edit!


(cl:in-package bekci-msg)


;//! \htmlinclude QuantativeSafetyStatus.msg.html

(cl:defclass <QuantativeSafetyStatus> (roslisp-msg-protocol:ros-message)
  ((joint_status
    :reader joint_status
    :initarg :joint_status
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass QuantativeSafetyStatus (<QuantativeSafetyStatus>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <QuantativeSafetyStatus>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'QuantativeSafetyStatus)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bekci-msg:<QuantativeSafetyStatus> is deprecated: use bekci-msg:QuantativeSafetyStatus instead.")))

(cl:ensure-generic-function 'joint_status-val :lambda-list '(m))
(cl:defmethod joint_status-val ((m <QuantativeSafetyStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bekci-msg:joint_status-val is deprecated.  Use bekci-msg:joint_status instead.")
  (joint_status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <QuantativeSafetyStatus>) ostream)
  "Serializes a message object of type '<QuantativeSafetyStatus>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'joint_status))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'joint_status))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <QuantativeSafetyStatus>) istream)
  "Deserializes a message object of type '<QuantativeSafetyStatus>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'joint_status) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'joint_status)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<QuantativeSafetyStatus>)))
  "Returns string type for a message object of type '<QuantativeSafetyStatus>"
  "bekci/QuantativeSafetyStatus")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'QuantativeSafetyStatus)))
  "Returns string type for a message object of type 'QuantativeSafetyStatus"
  "bekci/QuantativeSafetyStatus")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<QuantativeSafetyStatus>)))
  "Returns md5sum for a message object of type '<QuantativeSafetyStatus>"
  "957215486e0af0ae488964248502b403")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'QuantativeSafetyStatus)))
  "Returns md5sum for a message object of type 'QuantativeSafetyStatus"
  "957215486e0af0ae488964248502b403")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<QuantativeSafetyStatus>)))
  "Returns full string definition for message of type '<QuantativeSafetyStatus>"
  (cl:format cl:nil "uint8[] joint_status~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'QuantativeSafetyStatus)))
  "Returns full string definition for message of type 'QuantativeSafetyStatus"
  (cl:format cl:nil "uint8[] joint_status~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <QuantativeSafetyStatus>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'joint_status) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <QuantativeSafetyStatus>))
  "Converts a ROS message object to a list"
  (cl:list 'QuantativeSafetyStatus
    (cl:cons ':joint_status (joint_status msg))
))
