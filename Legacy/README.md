# 旧版 DriverLib 源码

`driverlib_v1_30/` 是原工程随附的 TI DriverLib 源码。它与较新 MSPM0 SDK 的头文件存在函数声明冲突，因此从构建目标中移除，仅用于追溯原工程。当前 GCC 和 Keil 配置都使用所安装 SDK 对应的预编译 DriverLib。
