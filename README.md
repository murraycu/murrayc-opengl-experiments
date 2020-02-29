# OpenGL Experiments

## Introduction

This is an attempt to explore some basics ideas of the OpenGL API.
It is heavily based on this tutorial:
https://github.com/BennyQBD/ModernOpenGLTutorial
https://www.youtube.com/playlist?list=PLEETnX-uPtBXT9T-hD0Bj31DSnwio-ywh

## Dependencies

This requires a few OpenGl libraries, and the glfw3 and stb libraries.
For instance, on Ubuntu or Debian:

$ sudo apt install libglew-dev libglfw3-dev libstb-dev

## Build

Like so:

$ git submodule init
$ ./autogen
$ make

Or:

$ ./autogen.sh --prefix=/opt/somewhere --enable-warnings=fatal
$ make



