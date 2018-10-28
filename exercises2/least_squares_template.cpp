#include <eigen3/Eigen/Dense>
#include <iostream>
#include <math.h>

Eigen::MatrixXd Vandermonde(const Eigen::VectorXd &x, int n) {
  int m = x.size();
  Eigen::MatrixXd V(m, n);

  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      V(i, j) = pow(x[i], j);
    }
  }

  return V;
}

Eigen::VectorXd r(const Eigen::VectorXd &x) {
  return (1.0 / (1.0 + 25.0 * x.array() * x.array())).matrix();
}

int main() {
  int n = 11;           // Number of polynomial coefficients
  int m;                // Number of samples
  Eigen::MatrixXd V;    // Vandermonde matrix
  Eigen::VectorXd x;    // Samples in [-1, 1]
  Eigen::VectorXd y;    // r(x)
  Eigen::VectorXd a(n); // Polynomial coefficients

  Eigen::IOFormat PythonFmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ",
                            ";\n", "[", "]", "[", "]");

  std::cout << "Polynomial coefficients obtained by..." << std::endl;

  // Compute overfitted polynomial coefficients
  m = n;
  x.setLinSpaced(m, -1.0, 1.0);

  // TODO: Task (b)
  y = r(x);
  V = Vandermonde(x, n);
  a = V.partialPivLu().solve(y);

  std::cout << "...overfitting:" << std::endl;
  std::cout << a.transpose().format(PythonFmt) << std::endl;

  // Compute least squares polynomial coefficients
  m = 3 * n;
  x.setLinSpaced(m, -1.0, 1.0);

  // TODO: Task (c)
  y = r(x);
  V = Vandermonde(x, n);
  a = (V.adjoint() * V).ldlt().solve(V.adjoint()*y);

  std::cout << "...least squares:" << std::endl;
  std::cout << a.transpose().format(PythonFmt) << std::endl;

  return 0;
}
