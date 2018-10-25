//#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Sparse>
#include <eigen3/Eigen/SparseLU>

#include <chrono> // clock

std::vector<Eigen::Triplet<double>> MakeTripletList(int n) {
  int nnz = 3 * n - 2;
  std::vector<Eigen::Triplet<double>> tripletList(nnz);

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (i == j)
        tripletList.push_back(Eigen::Triplet<double>(i, j, 2));
      else if ((i > 0 && i - 1 == j) || (j > 0 && j - 1 == i))
        tripletList.push_back(Eigen::Triplet<double>(i, j, -1));

  return tripletList;
}

double Runtime(const std::function<void(void)> &f) {
  double t = 0;

  // Do 10 runs for measuring average time
  for (int i = 10; i >= 0; i--) {
    auto start = std::chrono::steady_clock::now();
    f();
    auto finish = std::chrono::steady_clock::now();
    t += std::chrono::duration_cast<std::chrono::duration<double>>(finish -
                                                                   start)
             .count();
  }
  return t/100;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  os << "[";
  if (!v.empty()) {
    os << v[0];
    for (int i = 1; i < v.size(); ++i)
      os << ", " << v[i];
  }
  os << "]";

  return os;
}

int main() {
  // print small example of the tridiagonal matrix
  int m = 4;
  std::vector<Eigen::Triplet<double>> tripletList = MakeTripletList(m);
  Eigen::SparseMatrix<double> S_(m, m);
  S_.setFromTriplets(tripletList.begin(), tripletList.end());
  std::cout << "If n = " << m << ", then T equals" << std::endl;
  std::cout << Eigen::MatrixXd(S_) << std::endl;

  // matrix sizes for benchmark
  std::vector<int> N = {64, 128, 256, 512};
  std::cout << "LU decomposition of T, where n = " << N << std::endl;

  // set up variables for runtime measurement
  std::vector<double> runtimeSparse;
  std::vector<double> runtimeDense;

  std::function<void(void)> f;

  for (int n : N) {
    tripletList = MakeTripletList(n);
    Eigen::SparseMatrix<double> S(n, n);
    S.setFromTriplets(tripletList.begin(), tripletList.end());
    S.makeCompressed();

    // sparse LU decomposition
    f = [&S]() {
      Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
      solver.analyzePattern(S);
      solver.factorize(S);
    };
    runtimeSparse.push_back(Runtime(f));

    // dense LU decomposition
    Eigen::MatrixXd D(S);
    f = [&D]() { Eigen::FullPivLU<Eigen::MatrixXd> solverFull(D); };
    runtimeDense.push_back(Runtime(f));
  }

  std::cout << "Runtime in seconds using storage format..." << std::endl;
  std::cout << "...sparse: " << runtimeSparse << std::endl;
  std::cout << "...dense:  " << runtimeDense << std::endl;

  return 0;
}
