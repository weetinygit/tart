# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "faceReg: 1 messages, 0 services")

set(MSG_I_FLAGS "-IfaceReg:/home/weety/tart5/src/faceReg/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(faceReg_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/weety/tart5/src/faceReg/msg/facePose.msg" NAME_WE)
add_custom_target(_faceReg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "faceReg" "/home/weety/tart5/src/faceReg/msg/facePose.msg" "std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(faceReg
  "/home/weety/tart5/src/faceReg/msg/facePose.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/faceReg
)

### Generating Services

### Generating Module File
_generate_module_cpp(faceReg
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/faceReg
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(faceReg_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(faceReg_generate_messages faceReg_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/weety/tart5/src/faceReg/msg/facePose.msg" NAME_WE)
add_dependencies(faceReg_generate_messages_cpp _faceReg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(faceReg_gencpp)
add_dependencies(faceReg_gencpp faceReg_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS faceReg_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(faceReg
  "/home/weety/tart5/src/faceReg/msg/facePose.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/faceReg
)

### Generating Services

### Generating Module File
_generate_module_eus(faceReg
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/faceReg
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(faceReg_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(faceReg_generate_messages faceReg_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/weety/tart5/src/faceReg/msg/facePose.msg" NAME_WE)
add_dependencies(faceReg_generate_messages_eus _faceReg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(faceReg_geneus)
add_dependencies(faceReg_geneus faceReg_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS faceReg_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(faceReg
  "/home/weety/tart5/src/faceReg/msg/facePose.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/faceReg
)

### Generating Services

### Generating Module File
_generate_module_lisp(faceReg
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/faceReg
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(faceReg_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(faceReg_generate_messages faceReg_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/weety/tart5/src/faceReg/msg/facePose.msg" NAME_WE)
add_dependencies(faceReg_generate_messages_lisp _faceReg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(faceReg_genlisp)
add_dependencies(faceReg_genlisp faceReg_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS faceReg_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(faceReg
  "/home/weety/tart5/src/faceReg/msg/facePose.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/faceReg
)

### Generating Services

### Generating Module File
_generate_module_nodejs(faceReg
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/faceReg
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(faceReg_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(faceReg_generate_messages faceReg_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/weety/tart5/src/faceReg/msg/facePose.msg" NAME_WE)
add_dependencies(faceReg_generate_messages_nodejs _faceReg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(faceReg_gennodejs)
add_dependencies(faceReg_gennodejs faceReg_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS faceReg_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(faceReg
  "/home/weety/tart5/src/faceReg/msg/facePose.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/faceReg
)

### Generating Services

### Generating Module File
_generate_module_py(faceReg
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/faceReg
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(faceReg_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(faceReg_generate_messages faceReg_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/weety/tart5/src/faceReg/msg/facePose.msg" NAME_WE)
add_dependencies(faceReg_generate_messages_py _faceReg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(faceReg_genpy)
add_dependencies(faceReg_genpy faceReg_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS faceReg_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/faceReg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/faceReg
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(faceReg_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/faceReg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/faceReg
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(faceReg_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/faceReg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/faceReg
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(faceReg_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/faceReg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/faceReg
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(faceReg_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/faceReg)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/faceReg\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/faceReg
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(faceReg_generate_messages_py std_msgs_generate_messages_py)
endif()
