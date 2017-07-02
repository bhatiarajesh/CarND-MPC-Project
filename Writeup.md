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


