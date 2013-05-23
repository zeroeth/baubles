baubles
=======

This is an old fixed pipeline opengl app I'm slowly turning into modern opengl. Meaning:

* Replacing display lists with vertex arrays and vertex buffer objects
* Using shaders for the materials
* Properly handling openglES and different extensions.

Initial idea for overlapping borders came from an old Flash art book which I coded in ActionScript [http://pixel-flow.deviantart.com/art/Stars-169501086](http://pixel-flow.deviantart.com/art/Stars-169501086)

BUILD
-----

I made a small shell script for xcode/osx-gcc, just replace framework with pkg-configs for opengl and it should run fine.

TODO
----
* load/save colors in ant
* grab colors from api xml/json like colourlovers/kuler in c/c++
