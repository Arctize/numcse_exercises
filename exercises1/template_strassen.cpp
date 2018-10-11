#include <bits/stdc++.h>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;

// a)
MatrixXf mult(const MatrixXf& A, const MatrixXf& B)
{
    int N = A.rows();
    MatrixXf C = MatrixXf::Zero(N, N);

    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    for (int k = 0; k < N; k++) {
		C(i, j) += A(i, k) * B(k, j);
	    }
	}
    }

    return C;
}

// b) O(n^3)

// c)
MatrixXf mult_rec(const MatrixXf& A, const MatrixXf& B)
{
    int N = A.rows();
    MatrixXf C(N, N);
    if (N < 16) // fall back to iterative multiplication
    {
	C = mult(A, B);
    } else {
	int m = N / 2;
	MatrixXf C11 = mult_rec(A.block(0, 0, m, m), B.block(0, 0, m, m)) + mult_rec(A.block(0, m, m, m), B.block(m, 0, m, m));
	MatrixXf C12 = mult_rec(A.block(0, 0, m, m), B.block(0, m, m, m)) + mult_rec(A.block(0, m, m, m), B.block(m, m, m, m));
	MatrixXf C21 = mult_rec(A.block(m, 0, m, m), B.block(0, 0, m, m)) + mult_rec(A.block(m, m, m, m), B.block(m, 0, m, m));
	MatrixXf C22 = mult_rec(A.block(m, 0, m, m), B.block(0, m, m, m)) + mult_rec(A.block(m, m, m, m), B.block(m, m, m, m));
	C.block(0, 0, m, m) = C11;
	C.block(0, m, m, m) = C12;
	C.block(m, 0, m, m) = C21;
	C.block(m, m, m, m) = C22;
    }

    return C;
}

MatrixXf strassen(const MatrixXf& A, const MatrixXf& B)
{
    int N = A.rows();
    MatrixXf C(N, N);
    if (N < 16) { // fall back to iterative multiplication
	C = mult(A, B);
    } else {
	int m = N / 2;

	MatrixXf A11 = A.block(0, 0, m, m);
	MatrixXf A12 = A.block(0, m, m, m);
	MatrixXf A21 = A.block(m, 0, m, m);
	MatrixXf A22 = A.block(m, m, m, m);

	MatrixXf B11 = B.block(0, 0, m, m);
	MatrixXf B12 = B.block(0, m, m, m);
	MatrixXf B21 = B.block(m, 0, m, m);
	MatrixXf B22 = B.block(m, m, m, m);

	MatrixXf M1 = strassen(A11 + A22, B11 + B22);
	MatrixXf M2 = strassen(A21 + A22, B11);
	MatrixXf M3 = strassen(A11, B12 - B22);
	MatrixXf M4 = strassen(A22, B21 - B11);
	MatrixXf M5 = strassen(A11 + A12, B22);
	MatrixXf M6 = strassen(A21 - A11, B11 + B12);
	MatrixXf M7 = strassen(A12 - A22, B21 + B22);

	C.block(0, 0, m, m) = M1 + M4 + M7 - M5;
	C.block(0, m, m, m) = M3 + M5;
	C.block(m, 0, m, m) = M2 + M4;
	C.block(m, m, m, m) = M1 + M3 + M6 - M2;
    }

    return C;
}

int main()
{
    srand(time(0));
    cout << setprecision(6) << setfill(' ');

    for (int i = 9; i < 10; i++) {
	int N = 1 << i;
	cout << "Matrix size = " << N << endl;
	MatrixXd AA = MatrixXd::Random(N, N);
	MatrixXd BB = MatrixXd::Random(N, N);
	MatrixXd ans = AA * BB;
	MatrixXf A = AA.cast<float>();
	MatrixXf B = BB.cast<float>();

	auto start = std::chrono::steady_clock::now();
	MatrixXf W = mult(A, B);
	auto finish = std::chrono::steady_clock::now();
	cout << setw(24) << " " << setw(15)
	     << "Time (s)" << setw(20) << "Error (l2-norm)" << endl;
	cout << setw(24) << "Naive iterative " << setw(15)
	     << std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count() << setw(20) << (W.cast<double>() - ans).norm() << endl;

	start = std::chrono::steady_clock::now();
	MatrixXf X = mult_rec(A, B);
	finish = std::chrono::steady_clock::now();
	cout << setw(24) << "Naive recursive " << setw(15)
	     << std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count() << setw(20) << (X.cast<double>() - ans).norm() << endl;
	start = std::chrono::steady_clock::now();
	MatrixXf Y = strassen(A, B);
	finish = std::chrono::steady_clock::now();
	cout << setw(24) << "Strassen recursive " << setw(15)
	     << std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count() << setw(20) << (Y.cast<double>() - ans).norm() << endl;
	start = std::chrono::steady_clock::now();
	MatrixXf Z = A * B;
	finish = std::chrono::steady_clock::now();
	cout << setw(24) << "Eigen built-in " << setw(15)
	     << std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count() << setw(20) << (Z.cast<double>() - ans).norm() << "\n\n\n";
    }
}
