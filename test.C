//
// Testing Eigen with MetaPhysicL dual numbers
// Daniel Schwen 2021
//

#include <iostream>

// MetaPhysicL includes
#include "metaphysicl/dualnumberarray.h"

// dual number type
constexpr int ad_size = 10;
typedef double Real;
typedef MetaPhysicL::NumberArray<ad_size, Real> DNDerivativeType;
typedef MetaPhysicL::DualNumber<Real, DNDerivativeType, /*allow_skiping_derivatives=*/true> DualReal;

// Eigen includes
#include "Eigen/Core"
#include "Eigen/Eigenvalues"

int main(int argc, char* argv[])
{
  // define dual number based matrix type
  typedef Eigen::Matrix<DualReal, 6, 6, Eigen::DontAlign> DualMatrix;

  // build symmetric matrix
  auto X = DualMatrix::Random(6, 6);
  auto A = X + X.transpose();

  Eigen::SelfAdjointEigenSolver<DualMatrix> es(A);

  std::cout << "Eigenvalues: " << es.eigenvalues() << '\n';
  std::cout << "Eigenvectors: " << es.eigenvectors() << '\n';

  return 0;
}
