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
