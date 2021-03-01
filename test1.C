//
// Testing Eigen with MetaPhysicL dual numbers
// Daniel Schwen 2021
//

#include <iostream>
#include <type_traits>

// MetaPhysicL includes
#include "metaphysicl/dualnumberarray.h"

// dual number type
constexpr int ad_size = 10;
typedef double Real;
typedef MetaPhysicL::NumberArray<ad_size, Real> DNDerivativeType;
typedef MetaPhysicL::DualNumber<Real, DNDerivativeType, /*allow_skiping_derivatives=*/true> DualReal;

// this should be defined in Macros.h ! Argh!
#define EIGEN_ALIGN_TO_BOUNDARY(n) alignas(n)

// macros and traits required for Eigen forwards (not not alphabetically sort these includes!)
// clang-format off
#include "Eigen/src/Core/util/Macros.h"
#include "Eigen/src/Core/util/Constants.h"
#include "Eigen/src/Core/util/Meta.h"
#include "Eigen/src/Core/util/ForwardDeclarations.h"
// clang-format on

// define dual number based matrix type
typedef Eigen::Matrix<DualReal, 6, 6> DualMatrix;

// custom type trait
namespace std
{
template <>
struct is_convertible<DualMatrix, DualReal>
{
  static constexpr bool value = false;
};
} // namespace std

// Eigen includes
#include "Eigen/Core"
#include "Eigen/Eigenvalues"

int main(int argc, char* argv[])
{
  // build symmetric matrix
  auto X = DualMatrix::Random(6, 6);
  auto A = X + X.transpose();

  Eigen::SelfAdjointEigenSolver<DualMatrix> es(A);

  std::cout << "Eigenvalues: " << es.eigenvalues() << '\n';
  std::cout << "Eigenvectors: " << es.eigenvectors() << '\n';

  return 0;
}
