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

echo_and_run cd "/home/weety/tart5/src/tart_python"

# snsure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/weety/tart5/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/weety/tart5/install/lib/python2.7/dist-packages:/home/weety/tart5/build/tart_python/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/weety/tart5/build/tart_python" \
    "/usr/bin/python" \
    "/home/weety/tart5/src/tart_python/setup.py" \
    build --build-base "/home/weety/tart5/build/tart_python" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/weety/tart5/install" --install-scripts="/home/weety/tart5/install/bin"
