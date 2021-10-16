## Introduction
miniob设计的目标是让不熟悉数据库设计和实现的同学能够快速的了解与深入学习数据库内核，期望通过miniob相关训练之后，能够对各个数据库内核模块的功能与它们之间的关联有所了解，并能够在
使用时，设计出高效的SQL。面向的对象主要是在校学生，并且诸多模块做了简化，比如不考虑并发操作。
注意：此代码仅供学习使用，不考虑任何安全特性。

# How to build
git clone 以后
``` shell
mkdir build && cd build 
cmake .. 
make
```

## 进度
10.16 配置依赖库，能直接build运行  
> 备注：228服务器上可以了，要用其他服务器得 使用 git submodule init && git submodule update 命令再去 deps 安装3个库
