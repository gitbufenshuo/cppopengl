# cppopengl

### 介绍

cppopengl 是一个用c++来试验opengl相关api的项目，尽量封装成一个好用的渲染引擎。

### 软件架构
c++
opengl


### 安装教程

暂无

```bash
# for windows
cd others/study/glad/src
gcc -c glad.c -fPIC -o glad.o -I../../include
gcc -shared glad.o -o glad.dll
mv glad.dll ../../lib/
```

### 使用说明

- Material 概念和 自定义 Material [点击查看](docs/material.md)

### 命令行工具

- 生成 texture [点击查看](docs/texture.md)
