# Route Planning Project

This repo contains my implementation of Udacity's Route Planning project.

<img src="map.png" width="600" height="450" />

## Quick start

This quick start guide depends on the following being installed:

[Docker](https://docs.docker.com/get-docker/)

[GNU Make](https://www.gnu.org/software/make/)

To build, run and view the route planning application run the following command in your terminal:
```bash
make launch
```
Follow the instructions displayed in the terminal to generate a path for the given co-ordinates.
You can view the path by connecting to http://localhost:5900 using a [VNC Client](https://www.realvnc.com/download/viewer/).
Use the password 'secret' if prompted.

To build a docker container for development purposes run the following command in the terminal:
```bash
make build-dev
```

To see available make commands run the following in the terminal:
```bash
make help
```

## Cloning

When cloning this project, be sure to use the `--recurse-submodules` flag. Using HTTPS:
```
git clone https://github.com/GiancarloFusiello/CppND-Route-Planning-Project.git --recurse-submodules
```
or with SSH:
```
git clone git@github.com:GiancarloFusiello/CppND-Route-Planning-Project.git --recurse-submodules
```

## Dependencies for Running Locally
* cmake >= 3.11.3
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 7.4.0
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same instructions as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* IO2D
  * Installation instructions for all operating systems can be found [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md)
  * This library must be built in a place where CMake `find_package` will be able to find it

## Compiling and Running

### Compiling
To compile the project, first, create a `build` directory and change to that directory:
```
mkdir build && cd build
```
From within the `build` directory, then run `cmake` and `make` as follows:
```
cmake ..
make
```
### Running
The executable will be placed in the `build` directory. From within `build`, you can run the project as follows:
```
./OSM_A_star_search
```
Or to specify a map file:
```
./OSM_A_star_search -f ../<your_osm_file.osm>
```

## Testing

The testing executable is also placed in the `build` directory. From within `build`, you can run the unit tests as follows:
```
./test
```
