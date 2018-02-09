# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "bekci: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ibekci:/home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(bekci_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/msg/JointValue.msg" NAME_WE)
add_custom_target(_bekci_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "bekci" "/home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/msg/JointValue.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(bekci
  "/home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/msg/JointValue.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bekci
)

### Generating Services

### Generating Module File
_generate_module_cpp(bekci
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bekci
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(bekci_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(bekci_generate_messages bekci_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/msg/JointValue.msg" NAME_WE)
add_dependencies(bekci_generate_messages_cpp _bekci_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bekci_gencpp)
add_dependencies(bekci_gencpp bekci_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bekci_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(bekci
  "/home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/msg/JointValue.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bekci
)

### Generating Services

### Generating Module File
_generate_module_lisp(bekci
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bekci
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(bekci_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(bekci_generate_messages bekci_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/msg/JointValue.msg" NAME_WE)
add_dependencies(bekci_generate_messages_lisp _bekci_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bekci_genlisp)
add_dependencies(bekci_genlisp bekci_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bekci_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(bekci
  "/home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/msg/JointValue.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bekci
)

### Generating Services

### Generating Module File
_generate_module_py(bekci
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bekci
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(bekci_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(bekci_generate_messages bekci_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/msg/JointValue.msg" NAME_WE)
add_dependencies(bekci_generate_messages_py _bekci_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bekci_genpy)
add_dependencies(bekci_genpy bekci_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bekci_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bekci)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bekci
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(bekci_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bekci)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bekci
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(bekci_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bekci)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bekci\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bekci
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(bekci_generate_messages_py std_msgs_generate_messages_py)
endif()
