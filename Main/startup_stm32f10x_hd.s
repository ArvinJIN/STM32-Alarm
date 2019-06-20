;* File Name : startup_stm32f10x_hd.s
;* Author : MCD Application Team
;* Version : V3.5.0
;* Date : 11-March-2011
;* Description : STM32F10x High Density Devices vector table for MDK-ARM
;* toolchain.
;* This module performs:
;* - Set the initial SP
;* - Set the initial PC == Reset_Handler
;* - Set the vector table entries with the exceptions ISR address
;* - Configure the clock system and also configure the external
;* SRAM mounted on STM3210E-EVAL board to be used as data
;* memory (optional, to be enabled by user)
;* - Branches to __main in the C library (which eventually
;* calls main()).
;* After Reset the CortexM3 processor is in Thread mode,
;* priority is Privileged, and the Stack is set to Main.
;* <<< Use Configuration Wizard in Context Menu >>>
; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
; <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
; 首先对栈和堆的大小进行定义，并在代码区的起始处建立中断向量表，其第一个表项是栈
; 顶地址，第二个表项是复位中断服务入口地址。然后在复位中断服务程序中跳转C/C++标
; 准实时库的__main函数。假设STM32被设置为从内部FLASH启动中断向量表起始地位为0x8000000，
; 则栈顶地址存放于0x8000000处，而复位中断服务入口地址存放于0x8000004处。当STM32遇
; 到复位信号后，则从0x80000004处取出复位中断服务入口地址继而执行复位中断服务程序，
; 然后跳转__main函数，最后来到C的世界。
; DCD指令：作用是开辟一段空间，其意义等价于C语言中的地址符“&”。开始建立的中断向量
; 表则类似于使用C语.其每一个成员都是一个函数指针，分别指向各个中断服务函数
;伪指令AREA，表示开辟一段大小为Stack_Size的内存空间作为栈，段名是STACK，可读可写。
;NOINIT：指定此数据段仅仅保留了内存单元，而没有将各初始值写入内存单元，或者将各个内存单元值初始化为0
;常见的数据定义伪指令有如下几种：
;— DCB 用于分配一片连续的字节存储单元并用指定的数据初始化。
;— DCW （DCWU） 用于分配一片连续的半字存储单元并用指定的数据初始化。
;— DCD （DCDU） 用于分配一片连续的字存储单元并用指定的数据初始化。
;— DCFD （DCFDU）用于为双精度的浮点数分配一片连续的字存储单元并用指定的数据初始化。
;— DCFS (DCFSU） 用于为单精度的浮点数分配一片连续的字存储单元并用指定的数据初始化。
;— DCQ (DCQU） 用于分配一片以 8 字节为单位的连续的存储单元并用指定的数据初始化。
;— SPACE 用于分配一片连续的存储单元
;— MAP 用于定义一个结构化的内存表首地址
;— FIELD 用于定义一个结构化的内存表的数据域
;EXPORT伪指令用于在程序中声明一个全局的标号，该标号可在其他的文件中引用。EXPORT可用GLOBAL代替。标号在程序中区分大小写，[WEAK]选项声明其他的同名标号优先于该标号被引用。
;EQU 用于将一个数值或寄存器名赋给一个指定的符号名,表达式必须是一个简单再定位表达式。用 EQU 指令赋值以后的字符名，可以用作数据地址、代码地址、位地址或者直接当做一个立即数使用。
;启动程序的作用
;1.堆和栈的初始化
;2.向量表的定义
;3.地址重映射及中断向量表的转移
;4.设置系统时钟频率
;5.中断寄存器的初始化
;6.进入C应用程序
;1.堆和栈的初始化
;栈区（stack）由编译器自动分配释放 ，存放函数的参数值，局部变量的值等。其操作方式类似于数据结构中的栈
Stack_Size EQU 0x00000400 ;将一个数值(0x00000400)或寄存器名赋给一个指定的符号名Stack_size,即定义栈的大小为1Kb,
                AREA STACK, NOINIT, READWRITE, ALIGN=3 ;段的名字、未初始化或可初始为0、 允许读写、定义栈，8字节对齐2*2*2,2的3次方
                ;AREA 伪指令用于定义一个代码段或数据段,
                ;NOINIT：指定此数据段仅仅保留了内存单元，
              ;READWRITE属性：指定本段为可读可写，数据段的默认属性为READWRITE。
              ;STACK 段名
              ;ALIGN属性：使用方式为ALIGN 表达式。在默认时，ELF（可执行连接文件）的代码段和数据段是按字对齐的，表达式的取值范围为0～31，相应的对齐方式为2表达式次方。
Stack_Mem SPACE Stack_Size ;分配栈空间1Kb连续字节，并初始化为0，并把首地址赋给Stack_Mem
__initial_sp    ;初始化堆栈指针，指向栈顶位置，标号__initial_sp，表示栈空间顶地址。
                                                
; <h> Heap Configuration
; <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
;堆区（heap） —主要用于动态内存分配，也就是malloc、calloc、realloc等函数分配的变量空间是在堆上，一般由程序员分配释放， 若程序员不释放，程序结束时可能由OS回收 。注意它与数据结构中的堆是两回事，分配方式倒是类似于链表
Heap_Size EQU 0x00000200 ;定义堆的大小512Byte
                AREA HEAP, NOINIT, READWRITE, ALIGN=3 ;ALIGN用来指定对齐方式， 8字节对齐
__heap_base     ;表示堆空间起始地址
Heap_Mem SPACE Heap_Size ;分配0x200个连续字节，并初始化为0
__heap_limit    ;表示堆空间结束地址
                PRESERVE8 ;PRESERVE8 指令指定当前文件保持堆栈八字节对齐
                THUMB   ;告诉汇编器下面是32位的Thumb指令，如果需要汇编器将插入位以保证对齐

;2.向量表的定义
; Vector Table Mapped to Address 0 at Reset
;以下为向量表，在复位时被映射到FLASH的0地址
;实际上是在CODE区（假设STM32从FLASH启动，则此中断向量表起始地址即为0x8000000）
                AREA RESET, DATA, READONLY ;定义一块数据段，只可读，段名字是RESET
                                             ;DATA属性：用于定义数据段，默认为READWRITE。
                EXPORT __Vectors       ;中断向量表开始，EXPORT：在程序中声明一个全局的标号__Vectors，该标号可在其他的文件中引用
                EXPORT __Vectors_End   ;中断向量表结束
                EXPORT __Vectors_Size  ;中断向量表大小
;DCD命令表示分配1个4字节（32为）的空间，每行DCD都会生成一个4字节的二进制代码，中断向量表存放的实际上是中断服务程序的入口地址。中断向量表一般存放在Falsh的0地址
__Vectors DCD __initial_sp ; Top of Stack
                                                 ;第一个表项是栈顶地址
;该处物理地址值即为 __Vetors 标号所表示的值,该地址中存储__initial_sp所表示的地址值
;栈顶指针，被放在向量表的开始，FLASH的0地址，复位后首先装载栈顶指针
                DCD Reset_Handler ; Reset Handler
                                                 ;第二个表项是复位中断服务入口地址
                                                 ;复位异常，装载栈顶后，第一个执行的，并且不返回
                DCD NMI_Handler ; NMI Handler 不可屏蔽中断
                DCD HardFault_Handler ; Hard Fault Handler 硬件错误处理
                DCD MemManage_Handler ; MPU Fault Handler 存储器错误处理
                DCD BusFault_Handler ; Bus Fault Handler 总线错误处理
                ;总线错误中断，一般发生在数据访问异常，比如fsmc访问不当
                DCD UsageFault_Handler ; Usage Fault Handler 用法错误处理
                ;用法错误中断，一般是预取值，或者位置指令，数据处理等错误
                DCD 0 ; Reserved 这种形式就是保留地址，不给任何标号分配
                DCD 0 ; Reserved
                DCD 0 ; Reserved
                DCD 0 ; Reserved
                DCD SVC_Handler ; SVCall Handler ;系统调用异常，主要是为了调用操作系统内核服务（服务请求）
                DCD DebugMon_Handler ; Debug Monitor Handler 调试监视器（断点，数据观察点，或者是外部调试请求
                DCD 0 ; Reserved
                DCD PendSV_Handler ; PendSV Handler 为系统设备而设的“可悬挂请求” （pendable request）
                DCD SysTick_Handler ; SysTick Handler 系统滴答定时器
                ; External Interrupts 外设中断
                DCD WWDG_IRQHandler ; Window Watchdog 窗口看门狗
                DCD PVD_IRQHandler ; PVD through EXTI Line detect
                                                 ;电源电压检测(PVD)中断
                DCD TAMPER_IRQHandler ; Tamper
                DCD RTC_IRQHandler ; RTC
                DCD FLASH_IRQHandler ; Flash
                DCD RCC_IRQHandler ; RCC
                DCD EXTI0_IRQHandler ; EXTI Line 0
                DCD EXTI1_IRQHandler ; EXTI Line 1
                DCD EXTI2_IRQHandler ; EXTI Line 2
                DCD EXTI3_IRQHandler ; EXTI Line 3
                DCD EXTI4_IRQHandler ; EXTI Line 4
                DCD DMA1_Channel1_IRQHandler ; DMA1 Channel 1
                DCD DMA1_Channel2_IRQHandler ; DMA1 Channel 2
                DCD DMA1_Channel3_IRQHandler ; DMA1 Channel 3
                DCD DMA1_Channel4_IRQHandler ; DMA1 Channel 4
                DCD DMA1_Channel5_IRQHandler ; DMA1 Channel 5
                DCD DMA1_Channel6_IRQHandler ; DMA1 Channel 6
                DCD DMA1_Channel7_IRQHandler ; DMA1 Channel 7
                DCD ADC1_2_IRQHandler ; ADC1 & ADC2
                DCD USB_HP_CAN1_TX_IRQHandler ; USB High Priority or CAN1 TX
                DCD USB_LP_CAN1_RX0_IRQHandler ; USB Low Priority or CAN1 RX0
                DCD CAN1_RX1_IRQHandler ; CAN1 RX1
                DCD CAN1_SCE_IRQHandler ; CAN1 SCE
                DCD EXTI9_5_IRQHandler ; EXTI Line 9..5
                DCD TIM1_BRK_IRQHandler ; TIM1 Break
                DCD TIM1_UP_IRQHandler ; TIM1 Update
                DCD TIM1_TRG_COM_IRQHandler ; TIM1 Trigger and Commutation
                DCD TIM1_CC_IRQHandler ; TIM1 Capture Compare
                DCD TIM2_IRQHandler ; TIM2
                DCD TIM3_IRQHandler ; TIM3
                DCD TIM4_IRQHandler ; TIM4
                DCD I2C1_EV_IRQHandler ; I2C1 Event
                DCD I2C1_ER_IRQHandler ; I2C1 Error
                DCD I2C2_EV_IRQHandler ; I2C2 Event
                DCD I2C2_ER_IRQHandler ; I2C2 Error
                DCD SPI1_IRQHandler ; SPI1
                DCD SPI2_IRQHandler ; SPI2
                DCD USART1_IRQHandler ; USART1
                DCD USART2_IRQHandler ; USART2
                DCD USART3_IRQHandler ; USART3
                DCD EXTI15_10_IRQHandler ; EXTI Line 15..10
                DCD RTCAlarm_IRQHandler ; RTC Alarm through EXTI Line
                DCD USBWakeUp_IRQHandler ; USB Wakeup from suspend
                DCD TIM8_BRK_IRQHandler ; TIM8 Break
                DCD TIM8_UP_IRQHandler ; TIM8 Update
                DCD TIM8_TRG_COM_IRQHandler ; TIM8 Trigger and Commutation
                DCD TIM8_CC_IRQHandler ; TIM8 Capture Compare
                DCD ADC3_IRQHandler ; ADC3
                DCD FSMC_IRQHandler ; FSMC
                DCD SDIO_IRQHandler ; SDIO
                DCD TIM5_IRQHandler ; TIM5
                DCD SPI3_IRQHandler ; SPI3
                DCD UART4_IRQHandler ; UART4
                DCD UART5_IRQHandler ; UART5
                DCD TIM6_IRQHandler ; TIM6
                DCD TIM7_IRQHandler ; TIM7
                DCD DMA2_Channel1_IRQHandler ; DMA2 Channel1
                DCD DMA2_Channel2_IRQHandler ; DMA2 Channel2
                DCD DMA2_Channel3_IRQHandler ; DMA2 Channel3
                DCD DMA2_Channel4_5_IRQHandler ; DMA2 Channel4 & Channel5
__Vectors_End ; 结束
__Vectors_Size EQU __Vectors_End - __Vectors ;得到向量表的大小,304个字节也就是0x130个字节

;3.地址重映射及中断向量表的转移
;|.text|用于表示由C编译程序产生的代码段，或用于以某种方式与C库关联的代码段
                AREA |.text|, CODE, READONLY ;定义一个代码段，可读，段名字是.text 段名若以数字开头，则该段名需用"|"括起来，如|1_test|。
                ;定义只读"数据段"，实际上是在CODE区，如果在FLASH区起动，则 中断向量起始地址为0X8000000
                ;CODE属性：用于定义代码段，默认为READONLY
; Reset handler
Reset_Handler PROC ;标记一个函数的开始;利用PROC、ENDP这一对伪指令把程序段分为若干个过程，使程序的结构加清晰
                EXPORT Reset_Handler [WEAK]
                ;WEAK声明其他的同名标号优先于该标号被引用,就是说如果外面声明了的话,会调用外面的，这就让我们可以在c文件中放置中断服务程序，只要保证C函数名和向量表一致就行
                ;EXPORT伪指令用于在程序中声明一个全局的标号
                ;IMPORT：伪指令用于通知编译器要使用的标号在其他的源文件中定义
                IMPORT __main ;__main为运行时库提供的函数；完成堆栈，堆的初始化等工作，会调用下面定义的__user_initial_stackheap
                ;IMPORT SystemInit
                ;LDR R0, =SystemInit
                ;BLX R0
                LDR R0, =__main ;跳到__main，进入C的世界
                BX R0
                ENDP
                
; Dummy Exception Handlers (infinite loops which can be modified)
;虚拟异常处理器(无限循环可以修改了)
NMI_Handler PROC
                EXPORT NMI_Handler [WEAK]
                B . ;会调用外面的
                ENDP
HardFault_Handler\
                PROC
                EXPORT HardFault_Handler [WEAK]
                B .
                ENDP
MemManage_Handler\
                PROC
                EXPORT MemManage_Handler [WEAK]
                B .
                ENDP
BusFault_Handler\
                PROC
                EXPORT BusFault_Handler [WEAK]
                B .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT UsageFault_Handler [WEAK]
                B .
                ENDP
SVC_Handler PROC
                EXPORT SVC_Handler [WEAK]
                B .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT DebugMon_Handler [WEAK]
                B .
                ENDP
PendSV_Handler PROC
                EXPORT PendSV_Handler [WEAK]
                B .
                ENDP
SysTick_Handler PROC
                EXPORT SysTick_Handler [WEAK]
                B .
                ENDP
Default_Handler PROC
                EXPORT WWDG_IRQHandler [WEAK]
                EXPORT PVD_IRQHandler [WEAK]
                EXPORT TAMPER_IRQHandler [WEAK]
                EXPORT RTC_IRQHandler [WEAK]
                EXPORT FLASH_IRQHandler [WEAK]
                EXPORT RCC_IRQHandler [WEAK]
                EXPORT EXTI0_IRQHandler [WEAK]
                EXPORT EXTI1_IRQHandler [WEAK]
                EXPORT EXTI2_IRQHandler [WEAK]
                EXPORT EXTI3_IRQHandler [WEAK]
                EXPORT EXTI4_IRQHandler [WEAK]
                EXPORT DMA1_Channel1_IRQHandler [WEAK]
                EXPORT DMA1_Channel2_IRQHandler [WEAK]
                EXPORT DMA1_Channel3_IRQHandler [WEAK]
                EXPORT DMA1_Channel4_IRQHandler [WEAK]
                EXPORT DMA1_Channel5_IRQHandler [WEAK]
                EXPORT DMA1_Channel6_IRQHandler [WEAK]
                EXPORT DMA1_Channel7_IRQHandler [WEAK]
                EXPORT ADC1_2_IRQHandler [WEAK]
                EXPORT USB_HP_CAN1_TX_IRQHandler [WEAK]
                EXPORT USB_LP_CAN1_RX0_IRQHandler [WEAK]
                EXPORT CAN1_RX1_IRQHandler [WEAK]
                EXPORT CAN1_SCE_IRQHandler [WEAK]
                EXPORT EXTI9_5_IRQHandler [WEAK]
                EXPORT TIM1_BRK_IRQHandler [WEAK]
                EXPORT TIM1_UP_IRQHandler [WEAK]
                EXPORT TIM1_TRG_COM_IRQHandler [WEAK]
                EXPORT TIM1_CC_IRQHandler [WEAK]
                EXPORT TIM2_IRQHandler [WEAK]
                EXPORT TIM3_IRQHandler [WEAK]
                EXPORT TIM4_IRQHandler [WEAK]
                EXPORT I2C1_EV_IRQHandler [WEAK]
                EXPORT I2C1_ER_IRQHandler [WEAK]
                EXPORT I2C2_EV_IRQHandler [WEAK]
                EXPORT I2C2_ER_IRQHandler [WEAK]
                EXPORT SPI1_IRQHandler [WEAK]
                EXPORT SPI2_IRQHandler [WEAK]
                EXPORT USART1_IRQHandler [WEAK]
                EXPORT USART2_IRQHandler [WEAK]
                EXPORT USART3_IRQHandler [WEAK]
                EXPORT EXTI15_10_IRQHandler [WEAK]
                EXPORT RTCAlarm_IRQHandler [WEAK]
                EXPORT USBWakeUp_IRQHandler [WEAK]
                EXPORT TIM8_BRK_IRQHandler [WEAK]
                EXPORT TIM8_UP_IRQHandler [WEAK]
                EXPORT TIM8_TRG_COM_IRQHandler [WEAK]
                EXPORT TIM8_CC_IRQHandler [WEAK]
                EXPORT ADC3_IRQHandler [WEAK]
                EXPORT FSMC_IRQHandler [WEAK]
                EXPORT SDIO_IRQHandler [WEAK]
                EXPORT TIM5_IRQHandler [WEAK]
                EXPORT SPI3_IRQHandler [WEAK]
                EXPORT UART4_IRQHandler [WEAK]
                EXPORT UART5_IRQHandler [WEAK]
                EXPORT TIM6_IRQHandler [WEAK]
                EXPORT TIM7_IRQHandler [WEAK]
                EXPORT DMA2_Channel1_IRQHandler [WEAK]
                EXPORT DMA2_Channel2_IRQHandler [WEAK]
                EXPORT DMA2_Channel3_IRQHandler [WEAK]
                EXPORT DMA2_Channel4_5_IRQHandler [WEAK]
;如下只是定义了一个空函数
WWDG_IRQHandler
PVD_IRQHandler
TAMPER_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
ADC1_2_IRQHandler
USB_HP_CAN1_TX_IRQHandler
USB_LP_CAN1_RX0_IRQHandler
CAN1_RX1_IRQHandler
CAN1_SCE_IRQHandler
EXTI9_5_IRQHandler
TIM1_BRK_IRQHandler
TIM1_UP_IRQHandler
TIM1_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM4_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
EXTI15_10_IRQHandler
RTCAlarm_IRQHandler
USBWakeUp_IRQHandler
TIM8_BRK_IRQHandler
TIM8_UP_IRQHandler
TIM8_TRG_COM_IRQHandler
TIM8_CC_IRQHandler
ADC3_IRQHandler
FSMC_IRQHandler
SDIO_IRQHandler
TIM5_IRQHandler
SPI3_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
TIM6_IRQHandler
TIM7_IRQHandler
DMA2_Channel1_IRQHandler
DMA2_Channel2_IRQHandler
DMA2_Channel3_IRQHandler
DMA2_Channel4_5_IRQHandler
                B .
                ENDP
                ALIGN
;*******************************************************************************
; User Stack and Heap initialization
;4.堆和栈的初始化
;*******************************************************************************
                 IF :DEF:__MICROLIB
                 ;判断是否使用DEF:__MICROLIB（micro lib）
                 EXPORT __initial_sp
                 EXPORT __heap_base
                 EXPORT __heap_limit
                
                 ELSE
                
                 IMPORT __use_two_region_memory
                 EXPORT __user_initial_stackheap
                
__user_initial_stackheap
                 LDR R0, = Heap_Mem ;保存堆始地址
                 LDR R1, =(Stack_Mem + Stack_Size);保存栈的大小
                 LDR R2, = (Heap_Mem + Heap_Size);保存堆的大小
                 LDR R3, = Stack_Mem ;保存栈顶指针
                 BX LR
                 ALIGN  
                 ;ALIGN属性：使用方式为ALIGN 表达式。在默认时，ELF（可执行连接文件）的代码段和数据段是按字对齐的，表达式的取值范围为0～31，相应的对齐方式为2表达式次方
                 ENDIF
                 END
