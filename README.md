# Model Predictive Control (MPC)
Self-Driving Car Engineer Nanodegree Program

---

This project implements the Model Predictive Control (MPC) technique which frames the control problem as an optimization problem over time horizons. This technique involves choosing trajectories by minimizing the cost relative to a reference path, then choosing the actuator values which minimize error in the next prediction step.


## Implementation

Model Predictive Control (MPC) uses an optimizer to find the control inputs that minimize the cost function.

The MPC algorithm - 

Setup:

* Define the length of the trajectory, N, and duration of each timestep, dt.
* Define vehicle dynamics and actuator limitations along with other constraints.
* Define the cost function.

Loop:

* We pass the current state as the initial state to the model predictive controller.
* We call the optimization solver. Given the initial state, the solver will return the vector of control inputs that minimizes the cost function. The solver we'll use is called Ipopt.
* We apply the first control input to the vehicle.
* Back to 1.

## Model
The state of a vehicle includes
 
* x - x position location of the vehicle
* y - y position location of the vehicle
* psi - orientation of the vehicle
* v - velocity of a vehicle in motion
* cte - cross-track error.
* epsi - orientation error.

Actuators 
* delta - steering angle
* a - throttle value

* Timestep Length and Elapsed Duration (N & dt)


Based on manually tuning the hyper parameters, I settled on the values for N = 10 , dt = 0.1. The goal was to get the cross track error decreased to 0. When I set N to a higher value (eg. 100), the simulation was running much slower.This is because the solver had to optimize 4 times as many control inputs. Ipopt, the solver, permutes the control input values until it finds the lowest cost. 

* Polynomial Fitting and MPC Preprocessing

The server returns waypoints using the map's coordinate system, which is different than the car's coordinate system. I transformed the waypoints to make it easier to both display them and to calculate the CTE and Epsi values for the model predictive controller. A 3rd degree polynomial was fitted to waypoints. 

* Model Predictive Control with Latency
A 100 ms. latency between measurement and calculation is expected. The Kinematic vehicle model is used to compensate for latency.
[![Equations used to account for latency with dt = 0.1s ](https://github.com/bhatiarajesh/CarND-MPC-Project/raw/master/out/Kinematic-Model.png)]


## Additional Tuning
At higher speeds than 40mph. it was found the car would react with high values of steering. This would induce violent osscilations on the vehicle.The factors were introduced in the error calculation for the steering values so that the gap between successive steps is diminished. Good values were found on a trial and error basis to about a 1000 multiplier for the delta and 1400 for the gap.

## Visualization
It was helpful to visualize both the reference path and the MPC trajectory path.I displayed the connected point paths in the simulator by sending a list of optional x and y values to the mpc_x,mpc_y, next_x, and next_y fields in the C++ main script. If these fields were left untouched then simply no path was displayed.The mpc_x and mpc_y variables display a line projection in green. The next_x and next_y variables display a line projection in yellow. I could display these both at the same time, as seen in the image below.

These (x,y) points are displayed in reference to the vehicle's coordinate system. The x axis always points in the direction of the car’s heading and the y axis points to the left of the car. 

## Conclusion

The result of running the MPC model was that the vehicle successfully drove a lap around the track. The following image and video depict the result. The MPC trajectory path is displayed in green, and the polynomial fitted reference path in yellow.

[![Displaying the MPC trajectory path in green, and the polynomial fitted reference path in yellow.](https://github.com/bhatiarajesh/CarND-MPC-Project/raw/master/out/CarND-MPC-Project.png)]

See, [video recording of the MPC project run](https://youtu.be/QTP3pxZDqB0)



——————————————————————————————————————————————————————————————————————————————————————————


# Dependencies and Build instructions
---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `install-mac.sh` or `install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Fortran Compiler
  * Mac: `brew install gcc` (might not be required)
  * Linux: `sudo apt-get install gfortran`. Additionall you have also have to install gcc and g++, `sudo apt-get install gcc g++`. Look in [this Dockerfile](https://github.com/udacity/CarND-MPC-Quizzes/blob/master/Dockerfile) for more info.
* [Ipopt](https://projects.coin-or.org/Ipopt)
  * Mac: `brew install ipopt`
  * Linux
    * You will need a version of Ipopt 3.12.1 or higher. The version available through `apt-get` is 3.11.x. If you can get that version to work great but if not there's a script `install_ipopt.sh` that will install Ipopt. You just need to download the source from the Ipopt [releases page](https://www.coin-or.org/download/source/Ipopt/) or the [Github releases](https://github.com/coin-or/Ipopt/releases) page.
    * Then call `install_ipopt.sh` with the source directory as the first argument, ex: `bash install_ipopt.sh Ipopt-3.12.1`. 
  * Windows: TODO. If you can use the Linux subsystem and follow the Linux instructions.
* [CppAD](https://www.coin-or.org/CppAD/)
  * Mac: `brew install cppad`
  * Linux `sudo apt-get install cppad` or equivalent.
  * Windows: TODO. If you can use the Linux subsystem and follow the Linux instructions.
* [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page). This is already part of the repo so you shouldn't have to worry about it.
* Simulator. You can download these from the [releases tab](https://github.com/udacity/self-driving-car-sim/releases).
* Not a dependency but read the [DATA.md](./DATA.md) for a description of the data sent back from the simulator.


## Basic Build Instructions


1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./mpc`.

## Tips

1. It's recommended to test the MPC on basic examples to see if your implementation behaves as desired. One possible example
is the vehicle starting offset of a straight line (reference). If the MPC implementation is correct, after some number of timesteps
(not too many) it should find and track the reference line.
2. The `lake_track_waypoints.csv` file has the waypoints of the lake track. You could use this to fit polynomials and points and see of how well your model tracks curve. NOTE: This file might be not completely in sync with the simulator so your solution should NOT depend on it.
3. For visualization this C++ [matplotlib wrapper](https://github.com/lava/matplotlib-cpp) could be helpful.

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/b1ff3be0-c904-438e-aad3-2b5379f0e0c3/concepts/1a2255a0-e23c-44cf-8d41-39b8a3c8264a)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
