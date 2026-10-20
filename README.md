# 八路红外双电机寻迹工程（MSPM0G3507）

此工程使用 MSPM0G3507、FreeRTOS、八路数字红外模块与 L1/R1 两个直流电机寻迹。上电后等待 1 秒，随后底盘任务 `ChassisTask` 每 20 ms 读取一次 X1～X8；根据黑线位置调节左右轮 PWM，每 100 ms 经 UART0（115200、8N1）发送一次采样和电机状态。

## 目录职责

| 路径 | 职责 |
| --- | --- |
| `Core/Inc`, `Core/Src` | 芯片入口和 SysConfig 生成的外设初始化代码。`Core/Src/main.c` 只初始化硬件并进入应用。 |
| Task | `app_main.c` 负责 FreeRTOS 任务创建与调度启动；`app_chassis.c/.h` 放置底盘任务 `ChassisTask` 及其配置。 |
| APP | 八路红外采样与双轮差速寻迹；其他旧应用模块保留。 |
| BSP | SysTick 延时、UART、电机驱动等板级代码。 |
| `empty.syscfg` | SysConfig 的引脚与外设配置源文件；生成结果放在 `Core` 中。 |
| `gcc`, `keil` | 两套构建入口。GCC 使用 TI SDK 的 DriverLib 静态库；Keil 项目也配置为使用 SDK 静态库。 |
| `Legacy/driverlib_v1_30` | 原工程随附的旧版 TI DriverLib 源码，仅归档，不参与构建。 |
| `Legacy/ticlang_template` | 原始 TI Clang 空工程模板，仍引用不存在的 `empty.c`，不参与当前构建。 |
| `Legacy/Event.dot` | 原工程遗留的独立 Graphviz 图文件，不参与固件构建。 |
| `OBJ` | 原工程留下的 HEX 文件；新 GCC 构建产物在 `build/<配置>/`。 |

当前调用链：Core/Src/main.c → Task/app_main.c 创建 `ChassisTask` → Task/app_chassis.c → APP/app_irtracking.c → BSP/bsp_at8236.c 和 BSP/bsp_usart.c。红外 X1～X8 按从左到右的顺序对应 PA28、PA31、PA2、PB24、PB20、PB19、PB18、PA7。UART0 TX/RX 对应 PA10/PA11。

## FreeRTOS 任务

| 任务 | 周期 | 优先级 | 当前职责 |
| --- | --- | --- | --- |
| `ChassisTask` | 20 ms | `tskIDLE_PRIORITY + 2` | 底盘控制：八路红外采样、循迹误差计算、L1/R1 PWM 输出、每 100 ms 串口上报 |

视觉、底盘 IMU、云台 IMU 和云台电机尚无实际驱动或协议代码，因此当前不创建占位任务。后续每完成一个驱动模块，再将对应周期任务接入 `Task/app_main.c`。

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

需要 CMake、Ninja、`arm-none-eabi-gcc`、`arm-none-eabi-objcopy` 和包含 `kernel/freertos` 的 TI MSPM0 SDK。构建脚本优先使用 `MSPM0_SDK_DIR` 环境变量；未设置时，在 `~/.local/opt/ti/mspm0_sdk_*` 中查找。也可以通过 CMake 参数指定 SDK：

```sh
cmake --preset Debug -DMSPM0_SDK_DIR=/path/to/mspm0_sdk
cmake --build --preset Debug
```

产物为 `build/Debug/print_Eight_model_IO.elf`、`.hex` 和 `.map`。Release 构建使用 `cmake --preset Release`、`cmake --build --preset Release`。

## CLion 编译、J-Link 下载与调试

右上角运行配置下拉框提供三个入口，构建配置选择 `Debug`：

| 配置 | 操作 | 行为 |
| --- | --- | --- |
| `编译 Debug` | 点击构建锤子或运行 ▶ | 只编译固件，不连接开发板。 |
| `编译 + 下载` | 点击运行 ▶ | 先编译当前 Debug 目标，再下载固件并复位运行。 |
| `编译 + 下载 + 调试` | 点击调试 🐞 | 先编译、下载，再复位暂停并进入调试；可设置断点、单步和查看变量。 |

两个下载入口都使用 CLion 原生 `OpenOCD Download & Run` 配置，加载 `tools/clion-jlink.cfg`。下载文件由 CLion 根据当前构建目标确定，避免使用其他构建目录中的旧固件。底层参数在 `j-link.cfg` 中统一设置：J-Link USB 序列号 `123456`、SWD `4000 kHz`（4 MHz，已验证连接）、调试端口 ID `0x6ba02477`。

CLion 的“设置 → 构建、执行、部署 → 嵌入式开发 → OpenOCD 位置”应为 `/home/eris/.local/opt/mspm0-openocd-jlink/bin/openocd`。系统自带的 `/usr/bin/openocd` 不是本次验证使用的版本。若配置尚未刷新，重新打开工程或重启 CLion 后使用。

`tools/clion-jlink.cfg` 本身不会触发下载，由 CLion 控制下载时机。终端直接执行 `openocd -f j-link.cfg` 则仍会编程、校验、复位运行并退出。下载和调试不能同时占用同一只 J-Link，启动另一个操作前先停止当前调试会话。

## Keil 构建

当前 FreeRTOS 接入已在 GCC/CMake 构建下验证。`keil/print_Eight_model_IO.uvprojx` 仍保留为历史裸机工程，尚未加入 FreeRTOS 内核源文件和 Cortex-M0+ 移植层，不应直接用于当前版本。

如后续需要 Keil 构建，应安装 MSPM0G3507 器件包、ARM Compiler 6 和 TI MSPM0 SDK，并在 Keil 工程中补齐 FreeRTOS 内核、内存管理和 ARM Cortex-M0+ 端口后再编译。

原项目的 SysConfig 构建前命令指向已不存在的 SDK 相对路径，现已禁用。修改 `empty.syscfg` 后，先用与工程匹配的 SysConfig 重新生成 `Core/Src/ti_msp_dl_config.c` 和 `Core/Inc/ti_msp_dl_config.h`，再编译。本仓库已有的生成文件可以直接用于当前配置。

## 运行验证

Debug 构建通过后，先断开电机电源，用串口确认 IR 八位与实际遮挡顺序一致；再抬起车轮接通电机电源测试 L1/R1。黑线有效电平、左右轮方向和 PWM 数值需要按实际传感器与底盘调校。
