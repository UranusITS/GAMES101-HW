# GAMES101-HW

Homework of [GAMES101](https://games-cn.org/intro-graphics/) under Windows platform.

## Dependency

You need a C++ compiler of Windows ([Visual Studio 2022 Build Tools](https://visualstudio.microsoft.com/zh-hans/downloads/#build-tools-for-visual-studio-2022) for example) and the latest version of [CMake](https://cmake.org/download/) before building eigen3.

```pwsh
# clone this repo and the submodule
git clone https://github.com/UranusITS/GAMES101-HW
cd GAMES101-HW
git submodule update --init --recursive
# build eigen3 for windows
cd build
mkdir eigen3 && cd eigen3
cmake ../../eigen3/
cmake --build . --target install
```

By default, eigen3 will be installed in `C:\Program Files (x86)\Eigen3`. Then you need to setup system environment variable `EIGEN3_INCLUDE_DIR` to `C:\Program Files (x86)\Eigen3\include` in the Windows Settings or with this command in PowerShell with admin permission.

```pwsh
[System.Environment]::SetEnvironmentVariable('EIGEN3_INCLUDE_DIR','C:\Program Files (x86)\Eigen3\include','Machine')
```

## Run Homework

In the directory of this repo, you can build and run each homework. Take `hw0` for example:

```pwsh
# build hw0
cd build
mkdir hw0 && cd hw0
cmake ../../hw0
cmake --build .
# run hw0
./Debug/Transformation.exe
```
