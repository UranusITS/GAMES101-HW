# 作业3已知问题

## 找不到models

models文件夹放置在源代码文件夹中，需要手动移动至`./build/hw3`，或手动调整`main.cpp`中模型加载的位置。

## 渲染速度

在Debug配置下编译时，渲染速度可能过慢，可以选择使用Release配置加快速度。

```pwsh
# build hw3
cd build
mkdir hw3 && cd hw3
cmake ../../hw3
cmake --build .. --config release
# run hw3
cd Release
./Rasterizer output-texture.png texture
```
