# GAMES101-HW

Homework of [GAMES101](https://games-cn.org/intro-graphics/) under Windows platform.

## Dependency

You need a C++ compiler of Windows ([Visual Studio 2022 Build Tools](https://visualstudio.microsoft.com/zh-hans/downloads/#build-tools-for-visual-studio-2022) for example) and the latest version of [CMake](https://cmake.org/download/) before building [eigen3](https://eigen.tuxfamily.org/index.php?title=Main_Page) and [OpenCV](https://opencv.org/).

The dependency building code is based on `pwsh`. You may need to modify a bit to use it in `cmd` or other terminals.

```pwsh
git clone https://github.com/UranusITS/GAMES101-HW
cd GAMES101-HW
git submodule update --init --recursive
```

### eigen3

```pwsh
cd build
mkdir eigen3 && cd eigen3
cmake ../../dependency/eigen3/
cmake --build . --target install # need admin permission
```

By default, eigen3 will be installed in `C:\Program Files (x86)\Eigen3`. Then you need to setup system environment variable `EIGEN3_INCLUDE_DIR` to `C:\Program Files (x86)\Eigen3\include` in the Windows Settings or with this command in PowerShell with admin permission.

```pwsh
[System.Environment]::SetEnvironmentVariable('EIGEN3_INCLUDE_DIR','C:\Program Files (x86)\Eigen3\include','Machine')
```

### opencv

```pwsh
cd .. # to build dir
mkdir opencv && cd opencv
cmake -D CMAKE_BUILD_TYPE=RELEASE `
    -D OPENCV_GENERATE_PKGCONFIG=ON `
    -D OPENCV_EXTRA_MODULES_PATH=../../dependency/opencv_contrib/modules `
    -D BUILD_TESTS=OFF `
    -D BUILD_PERF_TESTS=OFF `
    -D BUILD_opencv_java=OFF `
    -D BUILD_opencv_python2=OFF `
    -D BUILD_opencv_python3=OFF `
    -D WITH_GSTREAMER=ON `
    -D WITH_TBB=ON `
    -D CMAKE_LIBRARY_PATH="C:/Program Files (x86)/TBB/lib" `
    -D WITH_OPENMP=ON ../../dependency/opencv/
cmake --build . --target install
```

By default, opencv will be installed in `./build/opencv/install/`. You can change it by adding `-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>`. You need to setup system environment variable `OpenCV_DIR` to `<REPO_DIR>\build\opencv` in the Windows Settings or with this command in PowerShell with admin permission.

```pwsh
[System.Environment]::SetEnvironmentVariable('OpenCV_DIR','<REPO_DIR>\build\opencv','Machine')
```

and add the installed binary dir to PATH, `<REPO_DIR>\build\opencv\install\x64\vc17\bin` by default.

### GStreamer

Install the latest version in its [download page](https://gstreamer.freedesktop.org/download/). You may need to add the binary dir to system path if link error occurs.

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

## Todo List

- [ ] Fix dependency installation guidance
  - [x] Eigen3
  - [ ] OpenCV
  - [x] GStreamer
  - [ ] OneTBB
- [ ] Finish all homework
  - [x] hw1
  - [x] hw2
  - [ ] hw3
  - [ ] hw4
  - [ ] hw5
  - [ ] hw6
  - [ ] hw7
  - [ ] hw8
