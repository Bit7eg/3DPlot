# 3DPlot

## Description

This program was made for my friend. 3DPlot can plot any set of points in 3 dimensional space according to given conditions. As well it let see figure from different angles.

## Build

3DPlot sources can be built using [cmake](https://cmake.org)

## Usage

### Controls

* __W__ - moves camera forward
* __A__ - moves camera left
* __S__ - moves camera backward
* __D__ - moves camera right
* __SHIFT__ - moves camera up
* __CTRL__ - moves camera down
* __MOUSE WHEEL__ - zooming
* __ESC__ - close program

### Configuration

Scene configuration is in `config.txt` file. 3DPlot supports the folowing options:

* __WIDTH__ - sets window width (__default: 800__)
* __HEIGHT__ - sets window height (__default: 600__)
* __FIGURE__ - sets figure file name (__no defaults__, ___required___)
* __FIGURE_COLOR__ - sets figure color using RGB format (__default: 0.5 0.5 0.5__)
* __FIGURE_TRANSPARENCY__ - sets figure transparency, where 0.0 - opaque and 1.0 - transparent (__default: 0.5__)
* __CAMERA_POSITION__ - sets start position for camera (__default: 0.0 0.0 0.0__)
* __HORIZONTAL_CAMERA_ROTATION__ - sets the angle of horizontal camera rotation (__default: -π/2__)
* __VERTICAL_CAMERA_ROTATION__ - sets the angle of vertical camera rotation (__default: 0.0__)
* __CAMERA_MOVING_SPEED__ - sets camera moving speed (__default: 5.0__)
* __MOUSE_SENSITIVITY__ - sets camera rotation speed (__default: 2.0__)
* __VIEWING_ANGLE__ - sets field of view angle (__default: π/4__)
* __ZOOM_SPEED__ - sets speed of zooming (__default: 0.1__)
* __STEP_SIZE__ - sets size of one step in ray modeling. It _affects performance_ and lines thickness (__defaults: 0.01__)
* __VIEW_DISTANCE__ - sets maximum rays length. It _affects performance_ and view distance (__defaults: 10.0__)

### Figures

Figures files are stored in `figures` directory. This files are part of fragment shader. To describe your own figure you should write a code fragment using [GLSL](https://www.khronos.org/opengl/wiki/Core_Language_(GLSL)). This code fragment should return boolean using `return` command. You can use `vec3` variable `point` to access the current point. If you want check equality of two float values, you should use `isEquals()` function instead of `==` operator.
