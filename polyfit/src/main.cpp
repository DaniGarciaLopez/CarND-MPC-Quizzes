// In this quiz you'll fit a polynomial to waypoints.

#include <iostream>
#include "Eigen-3.3/Eigen/Core"
#include "Eigen-3.3/Eigen/QR"

#include <fstream>

// Evaluate a polynomial.
double polyeval(const Eigen::VectorXd &coeffs, double x);
// Fit a polynomial.
Eigen::VectorXd polyfit(const Eigen::VectorXd &xvals, const Eigen::VectorXd &yvals, int order);

//Create CSV file to plot with Plotjuggler
void to_csv(const Eigen::VectorXd &xvals, const Eigen::VectorXd &yvals);

int main() {
  Eigen::VectorXd xvals(6);
  Eigen::VectorXd yvals(6);
  // x waypoint coordinates
  xvals << 9.261977, -2.06803, -19.6663, -36.868, -51.6263, -66.3482;
  // y waypoint coordinates
  yvals << 5.17, -2.25, -15.306, -29.46, -42.85, -57.6116;

  Eigen::VectorXd fit_curve = polyfit(xvals, yvals, 3);

  for (double x = 0; x <= 20; ++x) {

    std::cout << polyeval(fit_curve, x) << std::endl; 
  }

  // Expected output
  // -0.905562
  // -0.226606
  // 0.447594
  // 1.11706
  // 1.7818
  // 2.44185
  // 3.09723
  // 3.74794
  // 4.39402
  // 5.03548
  // 5.67235
  // 6.30463
  // 6.93236
  // 7.55555
  // 8.17423
  // 8.7884
  // 9.3981
  // 10.0033
  // 10.6041
  // 11.2005
  // 11.7925
}

double polyeval(const Eigen::VectorXd &coeffs, double x) {
  double result = 0.0;
  for (int i = 0; i < coeffs.size(); ++i) {
    result += coeffs[i] * pow(x, i);
  }
  return result;
}

// Adapted from:
// https://github.com/JuliaMath/Polynomials.jl/blob/master/src/Polynomials.jl#L676-L716
Eigen::VectorXd polyfit(const Eigen::VectorXd &xvals, const Eigen::VectorXd &yvals, int order) {
  assert(xvals.size() == yvals.size());
  assert(order >= 1 && order <= xvals.size() - 1);

  Eigen::MatrixXd A(xvals.size(), order + 1);

  for (int i = 0; i < xvals.size(); ++i) {
    A(i, 0) = 1.0;
  }

  for (int j = 0; j < xvals.size(); ++j) {
    for (int i = 0; i < order; ++i) {
      A(j, i + 1) = A(j, i) * xvals(j);
    }
  }

  auto Q = A.householderQr();
  auto result = Q.solve(yvals);

  return result;
}

void to_csv(const Eigen::VectorXd &xvals, const Eigen::VectorXd &yvals){
  // Create an output filestream object
  std::ofstream csv("polyfit.csv");
  
  // Send data to the stream
  csv << "X, Y\n";
  for (int i = 0; i < xvals.size(); ++i) {
    csv << xvals(i) << ", " << yvals(i) << "\n";
  }

  // Close the file
  csv.close();
}