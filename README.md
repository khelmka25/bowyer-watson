# Bowyer Watson Algorithm
Implementation of the [Bowyer Watson Algorithm](https://en.wikipedia.org/wiki/Bowyer%E2%80%93Watson_algorithm) using C++17 and GLFW.

## About
The Bowyer-Watson algorithm is an algorithm used to traingulate a set of random points in 2D space. In my implementation, I generate a few hundred points and create randomly colored triangles using the algorithm. Below are a few example outputs.

### 99 points

![99 Points](/images/image1.png)

### 333 points

![333 Points](/images/image2.png)

### 999 points

![999 Points](/images/image3.png)

## Building
Use the following instructions to build the application from source:

Clone the repo to your computer
```bash
cd path/to/cwd
git clone https://github.com/khelmka25/bowyer-watson.git
cd bowyer-watson
```
Pull the required submodules, and change glad's branch to **c**
```bash
cd deps
git submodule update --init --recursive
cd glad
git checkout c
```
Return to the project directory
```bash
cd ../../
```
Create a build directory and copy the shaders
```bash
mkdir build
cp -r ./shaders/ ./build/
```
Open the build directory, use cmake to create the make files, and build the application.
```bash
cd build
cmake ..
make
```

## Running the Application
To run the application from the build directory, call it in the command line with no additional arguments
```bash
./bowyer_watson
```
When inside the application, you may use the following keys to change the triangulation
```
Press R to build a new triangulation
Press - to remove 5 triangles and build a new triangulation
Press + to add 5 traingles and build a new triangulation
Press W to toggle between wireframe and shaded drawing
````