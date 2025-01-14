// In this quiz you'll implement the global kinematic model.
#include <math.h>
#include <iostream>
#include "Eigen-3.3/Eigen/Core"

//
// Helper functions
//
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

const double Lf = 2;

// Return the next state.
Eigen::VectorXd globalKinematic(const Eigen::VectorXd &state, 
                         const Eigen::VectorXd &actuators, double dt);

int main() {
  // [x, y, psi, v]
  Eigen::VectorXd state(4);
  // [delta, v]
  Eigen::VectorXd actuators(2);

  state << 0, 0, deg2rad(45), 1;
  actuators << deg2rad(5), 1;

  // should be [0.212132, 0.212132, 0.798488, 1.3]
  auto next_state = globalKinematic(state, actuators, 0.3);

  std::cout << next_state << std::endl;
}

Eigen::VectorXd globalKinematic(const Eigen::VectorXd &state, 
                         const Eigen::VectorXd &actuators, double dt) {
  // Create a new vector for the next state.
  Eigen::VectorXd next_state(state.size());

  // NOTE: state is [x, y, psi, v] and actuators is [delta, a]
  next_state[0] = state[0] + state[3] * cos(state[2]) * dt;
  next_state[1] = state[1] + state[3] * sin(state[2]) * dt;
  next_state[2] = state[2] + (state[3]/Lf) * actuators[0] * dt;
  next_state[3] = state[3] + actuators[1] * dt;

  return next_state;
}