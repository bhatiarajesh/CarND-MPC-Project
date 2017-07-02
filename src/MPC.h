#ifndef MPC_H
#define MPC_H

#include <vector>
#include "Eigen-3.3/Eigen/Core"

using namespace std;

// Define the length of the trajectory, N, and duration of each timestep, dt.
const size_t N = 10;
const double dt = 0.1;

// This is the length from front to CoG that has a similar radius.
const double Lf = 2.67;

// Reference velocity
const double ref_v = 60;

// Error calculation constants
const double delta_factor = 1000;
const double delta_gap_factor = 1400;

class MPC {
 public:
  MPC();

  virtual ~MPC();

  vector<double> predicted_x;
  vector<double> predicted_y;
  // Solve the model given an initial state and polynomial coefficients.
  // Return the first actuatotions.
  vector<double> Solve(Eigen::VectorXd state, Eigen::VectorXd coeffs);
};

#endif /* MPC_H */
