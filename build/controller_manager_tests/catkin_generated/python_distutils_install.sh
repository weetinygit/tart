#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/weety/tart5/src/roscontrol/src/ros_control/controller_manager_tests"

# snsure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/weety/tart5/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/weety/tart5/install/lib/python2.7/dist-packages:/home/weety/tart5/build/controller_manager_tests/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/weety/tart5/build/controller_manager_tests" \
    "/usr/bin/python" \
    "/home/weety/tart5/src/roscontrol/src/ros_control/controller_manager_tests/setup.py" \
    build --build-base "/home/weety/tart5/build/controller_manager_tests" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/weety/tart5/install" --install-scripts="/home/weety/tart5/install/bin"
