//
// Testing Eigen with MetaPhysicL dual numbers
// Daniel Schwen 2021
//

#include <cmath>
#include <iostream>
#include <type_traits>

// MetaPhysicL includes
#include "metaphysicl/dualnumberarray.h"
#include "metaphysicl/dynamicsparsenumberarray.h"

typedef double Real;
typedef MetaPhysicL::DualNumber<double, MetaPhysicL::DynamicSparseNumberArray<Real, unsigned int>>
    FirstDerivativeReal;
typedef MetaPhysicL::DualNumber<
    FirstDerivativeReal,
    MetaPhysicL::DynamicSparseNumberArray<FirstDerivativeReal, unsigned int>>
    ADReal;


namespace std
{
bool isinf(ADReal arg)
{
  return std::isinf(MetaPhysicL::raw_value(arg));
}
} // namespace std

// Eigen includes
#include "Eigen/Core"
#include "Eigen/Eigenvalues"

typedef Eigen::Matrix<ADReal, 3, 3> ADRankTwoTensor;

int main(int argc, char* argv[])
{

std::cout << "std::is_convertible<ADRankTwoTensor, ADReal> == "
            << std::is_convertible<ADRankTwoTensor, ADReal>::value << '\n';

  return 0;
}
