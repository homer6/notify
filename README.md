Notify
------
    Linux Daemon that runs a script when a file in the directory has changed (listens recursively). MIT License.
    Does not follow symlinks.


Requirements
------------

    sudo apt-get install cmake g++ make



Download and Install
--------------------

    git clone git://github.com/homer6/notify.git
    cd notify
    git submodule update --init --recursive

    cd lib/jet/
    cmake .
    make
    sudo ln -s `pwd`/build/libjet_shared.so /usr/lib/libjet_shared.so
    sudo ln -s `pwd`/build/libjet_static.a /usr/lib/libjet_static.a

    cd ../..
    cmake .
    make

    sudo ln -s `pwd`/build/notify /usr/bin/notify




Running
-------

    notify examples/python/skeleton.py listen_test/



Systems Successfully Run On
---------------------------

    - Linux 2.6.32, gcc version 4.4.3, ubuntu (lucid)
