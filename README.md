xps [![endorse](https://api.coderwall.com/caseydunham/endorsecount.png)](https://coderwall.com/caseydunham)
===

xps is a very simple cross platform (linux/win/mac) version of the nix utility ps

The intent of creating this project was to experiment with CMake. It isn't meant to be a replacement for ps. 

Building
====

To build xps you will need to install CMake on whatever platform you are intending to build on.

Windows
-------

In the root of the project 

    mkdir build
    cd build
    cmake ..\XpsMain\

The above will create a Visual Studio solution that you can than open and use to build.

OSX
---

In the root of the project

    mkdir build
    cd build
    cmake -G Xcode ../XpsMain/

Linux
-----

In the root of the project

    mkdir build
    cd build
    cmake ../XpsMain/
    make

