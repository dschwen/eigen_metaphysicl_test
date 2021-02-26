# Testing Eigen with MetaPhysicL dual numbers

Something is going awry when templating Eigen objects on MetaPhysicl dual
numbers. This repository is aimed at providing minimal examples to
reproduce the observed compile errors.

## Building the test

Install the prerequisites provided through git submodules

```
git submodule update --init --recursive
```

Build MetaPhysicL

```
cd MetaPhysicL
./bootstrap
./configure --prefix=${TEST_DIR}/install
make
make install
cd ..
```

Build the test executable

```
make
```

## Casting dual numbers to int

I believe this bit below is requires to enable Eigen to cast dual numbers to
integers, as MetaPhysicL prohibits implicit (and explicit) casts of dual to
non-dual numbers to prevent accidental loss of derivative information.

```
// integer casting helper
namespace Eigen
{
namespace internal
{
template <>
struct cast_impl<DualReal, int>
{
  static inline int run(const DualReal& x) { return static_cast<int>(MetaPhysicL::raw_value(x)); }
};
} // namespace internal
} // namespace Eigen
```

## Error

Compiling with clang 11 results in

```
In file included from test.C:19:
In file included from ./eigen/Eigen/Eigenvalues:36:
./eigen/Eigen/src/Eigenvalues/./Tridiagonalization.h:370:35: error: use of overloaded operator '*' is ambiguous (with operand types 'typename SelfAdjointViewReturnType<1U>::Type' (aka 'SelfAdjointView<Eigen::Block<Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 0, 6, 6>, -1, -1, false>, 1U>') and 'const CwiseBinaryOp<internal::scalar_product_op<typename internal::promote_scalar_arg<Scalar, DualNumber<double, NumberArray<10, double>, true>, (Eigen::internal::has_ReturnType<Eigen::ScalarBinaryOpTraits<DualNumber<double, NumberArray<10, double>, true>, Scalar, Eigen::internal::scalar_product_op<DualNumber<double, NumberArray<10, double>, true>, Scalar>>>::value)>::type, typename internal::traits<Block<Block<Matrix<DualNumber<double, NumberArray<10, double>, true>, 6, 6, 0, 6, 6>, 6, 1, true>, -1, 1, false>>::Scalar>, const typename internal::plain_constant_type<Block<Block<Matrix<DualNumber<double, NumberArray<10, double>, true>, 6, 6, 0, 6, 6>, 6, 1, true>, -1, 1, false>, typename internal::promote_scalar_arg<Scalar, DualNumber<double, NumberArray<10, double>, true>, (Eigen::internal::has_ReturnType<Eigen::ScalarBinaryOpTraits<DualNumber<double, NumberArray<10, double>, true>, Scalar, Eigen::internal::scalar_product_op<DualNumber<double, NumberArray<10, double>, true>, Scalar>>>::value)>::type>::type, const Eigen::Block<Eigen::Block<Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 0, 6, 6>, 6, 1, true>, -1, 1, false>>' (aka 'const CwiseBinaryOp<scalar_product_op<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>>, const CwiseNullaryOp<scalar_constant_op<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>>, const Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, -1, 1, 0, 6, 1>>, const Eigen::Block<Eigen::Block<Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 0, 6, 6>, 6, 1, true>, -1, 1, false>>'))
                                  * (conj(h) * matA.col(i).tail(remainingSize)));
                                  ^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
./eigen/Eigen/src/Eigenvalues/./Tridiagonalization.h:449:5: note: in instantiation of function template specialization 'Eigen::internal::tridiagonalization_inplace<Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 0, 6, 6>, Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 5, 1, 0, 5, 1>>' requested here
    tridiagonalization_inplace(mat,hCoeffs);
    ^
./eigen/Eigen/src/Eigenvalues/./Tridiagonalization.h:433:52: note: in instantiation of function template specialization 'Eigen::internal::tridiagonalization_inplace_selector<Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 0, 6, 6>, 6, false>::run<Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 1, 0, 6, 1>, Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 5, 1, 2, 5, 1>>' requested here
  tridiagonalization_inplace_selector<MatrixType>::run(mat, diag, subdiag, extractQ);
                                                   ^
./eigen/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h:444:13: note: in instantiation of function template specialization 'Eigen::internal::tridiagonalization_inplace<Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 0, 6, 6>, Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 1, 0, 6, 1>, Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 5, 1, 2, 5, 1>>' requested here
  internal::tridiagonalization_inplace(mat, diag, m_subdiag, computeEigenvectors);
            ^
./eigen/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h:174:7: note: in instantiation of function template specialization 'Eigen::SelfAdjointEigenSolver<Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 2, 6, 6>>::compute<Eigen::CwiseBinaryOp<Eigen::internal::scalar_sum_op<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>>, const Eigen::CwiseNullaryOp<Eigen::internal::scalar_random_op<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>>, Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 0, 6, 6>>, const Eigen::Transpose<Eigen::CwiseNullaryOp<Eigen::internal::scalar_random_op<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>>, Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 0, 6, 6>>>>>' requested here
      compute(matrix.derived(), options);
      ^
test.C:30:45: note: in instantiation of function template specialization 'Eigen::SelfAdjointEigenSolver<Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 2, 6, 6>>::SelfAdjointEigenSolver<Eigen::CwiseBinaryOp<Eigen::internal::scalar_sum_op<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>>, const Eigen::CwiseNullaryOp<Eigen::internal::scalar_random_op<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>>, Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 0, 6, 6>>, const Eigen::Transpose<Eigen::CwiseNullaryOp<Eigen::internal::scalar_random_op<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>>, Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 0, 6, 6>>>>>' requested here
  Eigen::SelfAdjointEigenSolver<DualMatrix> es(A);
                                            ^
./eigen/Eigen/src/Core/../plugins/CommonCwiseBinaryOps.h:50:29: note: candidate function [with T = Eigen::SelfAdjointView<Eigen::Block<Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 0, 6, 6>, -1, -1, false>, 1>]
EIGEN_MAKE_SCALAR_BINARY_OP(operator*,product)
                            ^
./eigen/Eigen/src/Core/SelfAdjointView.h:122:5: note: candidate function [with OtherDerived = Eigen::CwiseBinaryOp<Eigen::internal::scalar_product_op<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>>, const Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>>, const Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, -1, 1, 0, 6, 1>>, const Eigen::Block<Eigen::Block<Eigen::Matrix<MetaPhysicL::DualNumber<double, MetaPhysicL::NumberArray<10, double>, true>, 6, 6, 0, 6, 6>, 6, 1, true>, -1, 1, false>>]
    operator*(const MatrixBase<OtherDerived>& rhs) const
    ^
```
