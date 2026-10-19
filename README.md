# 八路红外双电机寻迹工程（MSPM0G3507）

此工程使用 MSPM0G3507、八路数字红外模块与 L1/R1 两个直流电机寻迹。上电后等待 1 秒，随后每 20 ms 读取一次 X1～X8；根据黑线位置调节左右轮 PWM，每 100 ms 经 UART0（115200、8N1）发送一次采样和电机状态。

## 目录职责

| 路径 | 职责 |
| --- | --- |
| `Core/Inc`, `Core/Src` | 芯片入口和 SysConfig 生成的外设初始化代码。`Core/Src/main.c` 只初始化硬件并进入应用。 |
| Task | 寻迹主循环，位于 Task/app_main.c。 |
| APP | 八路红外采样与双轮差速寻迹；其他旧应用模块保留。 |
| BSP | SysTick 延时、UART、电机驱动等板级代码。 |
| `empty.syscfg` | SysConfig 的引脚与外设配置源文件；生成结果放在 `Core` 中。 |
| `gcc`, `keil` | 两套构建入口。GCC 使用 TI SDK 的 DriverLib 静态库；Keil 项目也配置为使用 SDK 静态库。 |
| `Legacy/driverlib_v1_30` | 原工程随附的旧版 TI DriverLib 源码，仅归档，不参与构建。 |
| `Legacy/ticlang_template` | 原始 TI Clang 空工程模板，仍引用不存在的 `empty.c`，不参与当前构建。 |
| `Legacy/Event.dot` | 原工程遗留的独立 Graphviz 图文件，不参与固件构建。 |
| `OBJ` | 原工程留下的 HEX 文件；新 GCC 构建产物在 `build/<配置>/`。 |

当前调用链：Core/Src/main.c → Task/app_main.c → APP/app_irtracking.c → BSP/bsp_at8236.c 和 BSP/bsp_usart.c。红外 X1～X8 按从左到右的顺序对应 PA28、PA31、PA2、PB24、PB20、PB19、PB18、PA7。UART0 TX/RX 对应 PA10/PA11。

## 寻迹与接线

| 功能 | MSPM0G3507 引脚 | 接到驱动 |
| --- | --- | --- |
| L1 / M1 正反转控制 | PA12、PA13 | L1 的 IN1、IN2 |
| R1 / M3 正反转控制 | PB6、PB7 | R1 的 IN1、IN2 |
| 红外 X1～X8 | PA28、PA31、PA2、PB24、PB20、PB19、PB18、PA7 | 模块的八路数字输出 |
| 串口数据输出 | PA10 (UART0 TX) | USB 串口模块 RX |

开发板、红外模块、驱动板和串口模块需要共地。电机由驱动板的电机电源供电。L2/R2 定时器不会启动，不需要接这两台电机。

默认黑线使红外输出为低电平。算法将 X1～X8 映射到从左到右的权重 -7,-5,-3,-1,+1,+3,+5,+7，取检测到黑线的通道平均位置作为偏差。偏差为负时降低 L1、提高 R1；偏差为正时反之。全部通道都未检测到黑线时，两台电机停止；全部通道都检测到黑线时按居中处理。没有接入编码器速度闭环。

APP/app_irtracking.h 中可调整黑线有效电平、基础 PWM、转向增益、最大 PWM 和前进方向符号。根据实车直行方向反馈，L1 前进使用负 PWM，R1 前进使用正 PWM。首次测试请抬起车轮，确认 X1 位于车头左侧、两轮前进方向正确，再落地调速。

BSP/bsp_at8236.c 将 0～999 的 PWM 幅值转换为定时器递减计数所需的比较值；0 幅值使驱动的两个输入均保持低电平。当前直行命令为 939，加上驱动的 60 计数死区补偿后达到 999 上限；检测到偏线时降低内侧轮 PWM 来转向。实际车速还取决于电机、供电和负载，不能按 PWM 比例推算。

UART0 每 100 ms 输出一行，例如：

    IR:11100111,VALID:1,ERR:0,L:300,R:300

IR 是 X1～X8 的原始 0/1 电平；VALID 表示是否检测到黑线；ERR 为黑线位置偏差；L、R 是左右轮的前进 PWM 幅值。若 VALID:0，两轮 PWM 均为 0。

## GCC 构建

需要 CMake、Ninja、`arm-none-eabi-gcc`、`arm-none-eabi-objcopy` 和 TI MSPM0 SDK。构建脚本优先使用 `MSPM0_SDK_DIR` 环境变量；未设置时，在 `~/.local/opt/ti/mspm0_sdk_*` 中查找。也可以通过 CMake 参数指定 SDK：

```sh
cmake --preset Debug -DMSPM0_SDK_DIR=/path/to/mspm0_sdk
cmake --build --preset Debug
```

产物为 `build/Debug/print_Eight_model_IO.elf`、`.hex` 和 `.map`。Release 构建使用 `cmake --preset Release`、`cmake --build --preset Release`。

## Keil 构建

打开 `keil/print_Eight_model_IO.uvprojx`。安装 MSPM0G3507 器件包、ARM Compiler 6 和 TI MSPM0 SDK，并使环境变量 `MSPM0_SDK_DIR` 指向 SDK 根目录。项目的头文件路径和 DriverLib 库路径通过该变量引用 SDK。

原项目的 SysConfig 构建前命令指向已不存在的 SDK 相对路径，现已禁用。修改 `empty.syscfg` 后，先用与工程匹配的 SysConfig 重新生成 `Core/Src/ti_msp_dl_config.c` 和 `Core/Inc/ti_msp_dl_config.h`，再编译。本仓库已有的生成文件可以直接用于当前配置。

## 运行验证

Debug 构建通过后，先断开电机电源，用串口确认 IR 八位与实际遮挡顺序一致；再抬起车轮接通电机电源测试 L1/R1。黑线有效电平、左右轮方向和 PWM 数值需要按实际传感器与底盘调校。
