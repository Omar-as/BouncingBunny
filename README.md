# Bouncing Ball Graphics Application

## Description

This graphics application simulates a bouncing ball on the screen. The ball can be of two types (cube or sphere) and can be drawn in wireframe or solid mode. The program uses shader-based OpenGL and the GLFW 3D graphics library to create an interactive and visually appealing animation.

## Table of Contents

- [Problem Description and Learning Objectives](#problem-description-and-learning-objectives)
- [Problem Specification](#problem-specification)
- [Bonus](#bonus)

## Problem Description and Learning Objectives

In this assignment, you will design and implement a basic graphics application that animates a ball bouncing horizontally on the screen. This will be an interactive program that allows the user to select an object to draw (from a choice of two objects), to choose various drawing attributes for the object (such as color and polygon mode). Each time the user selects one of the drawing options, the image on the screen will be redrawn with the new choice. To develop this program you will need to learn how to use both shader-based OpenGL and GLFW 3D graphics libraries. The GLFW library includes functions for implementing event-driven input and display handling operations. This assignment will be an introduction to event-driven graphics programming. Your program must be developed using shader-based OpenGL and C/C++.

## Problem Specification

Your program will simulate and display a bouncing ball (either cubical or spherical) under gravitational force. The ball will initially be placed on top leftmost of the display window and then will start its fall (accelerated with gravity). The initial (horizontal) velocity will be a parameter to set. The ball will move rightwards with proper acceleration until it hits the bottom of the window, and bounce back slowing down gradually with each hit until it goes out of the window or its velocity becomes zero. Bouncing will continue as such. You may reduce the velocity by a fixed factor after each bouncing.

During execution, the user may change the object type, color, and drawing mode.

You can refer to the following page for physics of a bouncing ball under gravity (Note that in this assignment we will be ignoring the deformation of the bouncing ball): [Bouncing Ball Physics](https://interestingengineering.com/science/what-are-the-physics-behind-bouncing-balls)

Your program must handle user input from the keyboard and mouse, and set the drawing modes as specified below:

- **Object type and drawing mode (wireframe or solid)** must be set by using the mouse button callback:
  - Object type: Set the current object to be drawn; switch between the following two choices, whenever right button is pressed:
    - Cube
    - Sphere
  - Drawing mode: Set how the triangles are drawn; switch between the following two choices, whenever left button is pressed:
    - Wireframe (i.e., as lines)
    - Solid mode

- **Object initialization, color setting, termination, and help functionalities** should be controlled through the keyboard callback as specified below:
  - `i`: Initialize the pose (top left corner of the window)
  - `c`: Switch between two colors (of your choice), which are used to draw lines or triangles.
  - `h`: Help; print explanation of your input control (simply to the command line)
  - `q`: Quit (exit) the program

Your program must also properly handle the reshape event; so you must define your own reshape callback function.

Transformations (i.e., vertex displacements) and projection have to be implemented in vertex shader. Since we haven't yet seen how to shade surfaces, when you display your objects in solid (filled polygon) mode, you'll be able to observe them only as silhouettes.

You can use the default orthographic projection (the viewing volume being the cube centered at the origin with sides of length 2).  Note that since reshape callback function is invoked when the window is first opened at the beginning of program execution, it is a good place to put all projection-related settings (that means you won't then need to set projection in init() function).

### Bonus

Load and display the 3D Bunny model from an OFF file as a third object type (bunny.off). So in this case you will be able to set the current object to draw, as one of the three choices (cube, sphere or bunny). Note that you may initially need to adjust the orientation and scale of the bunny model using a transformation matrix.

You can preview a given off file in 3D using the following web link: [3D Viewer](https://3dviewer.net/). The off file in our case includes a vertex list first and then a triangle list as shown below. Off files are actually ASCII files and you can see their content using any text editor. But for your application you need to write your own loader:

```
OFF
4922 9840 0
1.7325 -9.534 24.02
1.7 -9.7711 23.8073
2.216 -9.723 23.6798
2.285 -9.5198 23.923
1.0534 -9.8046 23.8978
...
...
3 0 1 2
3 0 2 3
3 4 1 0
3 4 0 5
3 6 1 4
3 6 4 7
...
```
