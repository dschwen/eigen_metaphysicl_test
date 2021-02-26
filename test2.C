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

// Eigen includes
#include "Eigen/Core"

// define dual number based matrix type
typedef Eigen::Matrix<DualReal, 6, 6, Eigen::DontAlign> DualMatrix;

int main(int argc, char* argv[])
{
  // https://listengine.tuxfamily.org/lists.tuxfamily.org/eigen/2016/10/msg00041.html
  std::cout << "std::is_convertible<DualMatrix, DualReal> == " << std::is_convertible<DualMatrix, DualReal>::value
            << '\n';

  return 0;
}
