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

int main(int argc, char* argv[])
{
  DualReal a = 10;
  DualReal b = 5;
  std::cout << a * b << '\n';
  return 0;
}
