#include <eigen3/Eigen/Dense>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace Eigen;

VectorXd load_pgm(const std::string &filename) {
  // returns a picture as a flattened vector

  int row = 0, col = 0, rows = 0, cols = 0;

  std::ifstream infile(filename);
  std::stringstream ss;
  std::string inputLine = "";

  // First line : version
  std::getline(infile, inputLine);

  // Second line : comment
  std::getline(infile, inputLine);

  // Continue with a stringstream
  ss << infile.rdbuf();
  // Third line : size
  ss >> cols >> rows;

  VectorXd picture(rows * cols);

  // Following lines : data
  for (row = 0; row < rows; ++row) {
    for (col = 0; col < cols; ++col) {
      int val;
      ss >> val;
      picture(col * rows + row) = val;
    }
  }

  infile.close();
  return picture;
}

using namespace std;
using namespace Eigen;

int main() {

  int h = 231;
  int w = 195;
  int M = 15;

  MatrixXd faces(h * w, M);
  VectorXd meanFace(h * w);

  // loads pictures as flattened vectors into faces
  for (int i = 0; i < M; i++) {
    string filename = "./basePictures/subject" + to_string(i + 1) + ".pgm";
    VectorXd flatPic = load_pgm(filename);
    faces.col(i) = flatPic;

    // TODO: Point (b)
    meanFace += flatPic;
  }

  meanFace /= M;
  faces.colwise() -= meanFace;

  JacobiSVD<MatrixXd> svd(faces, ComputeThinU);
  MatrixXd u = svd.matrixU();

  //MatrixXd projectedFaces(1000, M);
  //for (int i = 0; i < faces.cols(); i++) {
  //  projectedFaces.col(i) = u.transpose() * (faces.col(i) - meanFace);
  //}
  MatrixXd projectedFaces = u.transpose() * faces;

  string testPicture = "./testPictures/Narutowicz.pgm";
  VectorXd newFace = load_pgm(testPicture);
  VectorXd d = u.transpose() * (newFace - meanFace);

  int minIndex = 0;
  int minNorm = (projectedFaces.col(0) - d).norm();
  for (int i = 1; i < faces.cols(); i++) {
    double norm = (projectedFaces.col(i) - d).norm();
    if (norm < minNorm) {
      minNorm = norm;
      minIndex = i;
    }
  }

  cout << minIndex << endl;

  // TODO: Point (g)
  //  MatrixXd projFaces = u.transpose() * faces;
  // VectorXd projNewFace = u.transpose() * (newFace - meanFace);
  // int indexMinNorm;
  //(projFaces.colwise() -
  // projNewFace).colwise().norm().minCoeff(&indexMinNorm); cout << testPicName
  // << " is identified as subject " << indexMinNorm + 1
  //     << endl;
}
