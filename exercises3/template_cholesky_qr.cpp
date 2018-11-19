#include <iostream>

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/QR>

/* @brief QR decomposition from Cholesky decomposition
 * @param[in] A An $m \times n$ matrix
 * @param[out] R The upper triangular matrix from the QR decomposition of $A$
 * @param[out] Q The orthogonal matrix from the QR decomposition of $A$
 */
void CholeskyQR(const Eigen::MatrixXd &A, Eigen::MatrixXd &R,
                Eigen::MatrixXd &Q) {

  // Task (c)
  Eigen::MatrixXd AtA = A.transpose() * A;
  Eigen::LLT<Eigen::MatrixXd> cholesky = AtA.llt();
  Eigen::MatrixXd L = cholesky.matrixL();
  R = cholesky.matrixL().transpose();
  Q = L.triangularView<Eigen::Lower>()
          .solve(A.transpose())
          .transpose(); // Why can't we use cholesky.matrixL() instead of L
                        // here?
}

/* @brief Direct QR decomposition
 * @param[in] A An $m \times n$ matrix
 * @param[out] R The upper triangular matrix from the QR decomposition of $A$
 * @param[out] Q The orthogonal matrix from the QR decomposition of $A$
 */
void DirectQR(const Eigen::MatrixXd &A, Eigen::MatrixXd &R,
              Eigen::MatrixXd &Q) {

  // Task (d)
  int m = A.rows(), n = A.cols();
  Eigen::HouseholderQR<Eigen::MatrixXd> qr(A);
  Eigen::MatrixXd thinQ = (Eigen::MatrixXd::Identity(m, std::min(m, n)));
  Q = qr.householderQ();
  thinQ = qr.householderQ() * thinQ;
  R = qr.matrixQR().triangularView<Eigen::Upper>();
}

int main() {
  int m = 3;
  int n = 2;

  Eigen::MatrixXd A(m, n);
  double epsilon = 1.e-8;
  // A << 3, 5, 1, 9, 7, 1;
  A << 1, 1, epsilon, 0, 0, epsilon;
  std::cout << "A =" << std::endl << A << std::endl;

  Eigen::MatrixXd R, Q;

  CholeskyQR(A, R, Q);
  std::cout << "CholeskyQR: ===========" << std::endl;
  std::cout << "R =" << std::endl << R << std::endl;
  std::cout << "Q =" << std::endl << Q << std::endl;

  DirectQR(A, R, Q);
  std::cout << "DirectQR: =============" << std::endl;
  std::cout << "R =" << std::endl << R << std::endl;
  std::cout << "Q =" << std::endl << Q << std::endl;

  return 0;
}
