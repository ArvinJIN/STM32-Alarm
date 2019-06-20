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
; ���ȶ�ջ�ͶѵĴ�С���ж��壬���ڴ���������ʼ�������ж����������һ��������ջ
; ����ַ���ڶ��������Ǹ�λ�жϷ�����ڵ�ַ��Ȼ���ڸ�λ�жϷ����������תC/C++��
; ׼ʵʱ���__main����������STM32������Ϊ���ڲ�FLASH�����ж���������ʼ��λΪ0x8000000��
; ��ջ����ַ�����0x8000000��������λ�жϷ�����ڵ�ַ�����0x8000004������STM32��
; ����λ�źź����0x80000004��ȡ����λ�жϷ�����ڵ�ַ�̶�ִ�и�λ�жϷ������
; Ȼ����ת__main�������������C�����硣
; DCDָ������ǿ���һ�οռ䣬������ȼ���C�����еĵ�ַ����&������ʼ�������ж�����
; ����������ʹ��C��.��ÿһ����Ա����һ������ָ�룬�ֱ�ָ������жϷ�����
;αָ��AREA����ʾ����һ�δ�СΪStack_Size���ڴ�ռ���Ϊջ��������STACK���ɶ���д��
;NOINIT��ָ�������ݶν����������ڴ浥Ԫ����û�н�����ʼֵд���ڴ浥Ԫ�����߽������ڴ浥Ԫֵ��ʼ��Ϊ0
;���������ݶ���αָ�������¼��֣�
;�� DCB ���ڷ���һƬ�������ֽڴ洢��Ԫ����ָ�������ݳ�ʼ����
;�� DCW ��DCWU�� ���ڷ���һƬ�����İ��ִ洢��Ԫ����ָ�������ݳ�ʼ����
;�� DCD ��DCDU�� ���ڷ���һƬ�������ִ洢��Ԫ����ָ�������ݳ�ʼ����
;�� DCFD ��DCFDU������Ϊ˫���ȵĸ���������һƬ�������ִ洢��Ԫ����ָ�������ݳ�ʼ����
;�� DCFS (DCFSU�� ����Ϊ�����ȵĸ���������һƬ�������ִ洢��Ԫ����ָ�������ݳ�ʼ����
;�� DCQ (DCQU�� ���ڷ���һƬ�� 8 �ֽ�Ϊ��λ�������Ĵ洢��Ԫ����ָ�������ݳ�ʼ����
;�� SPACE ���ڷ���һƬ�����Ĵ洢��Ԫ
;�� MAP ���ڶ���һ���ṹ�����ڴ���׵�ַ
;�� FIELD ���ڶ���һ���ṹ�����ڴ���������
;EXPORTαָ�������ڳ���������һ��ȫ�ֵı�ţ��ñ�ſ����������ļ������á�EXPORT����GLOBAL���档����ڳ��������ִ�Сд��[WEAK]ѡ������������ͬ����������ڸñ�ű����á�
;EQU ���ڽ�һ����ֵ��Ĵ���������һ��ָ���ķ�����,���ʽ������һ�����ٶ�λ���ʽ���� EQU ָ�ֵ�Ժ���ַ����������������ݵ�ַ�������ַ��λ��ַ����ֱ�ӵ���һ��������ʹ�á�
;�������������
;1.�Ѻ�ջ�ĳ�ʼ��
;2.������Ķ���
;3.��ַ��ӳ�估�ж��������ת��
;4.����ϵͳʱ��Ƶ��
;5.�жϼĴ����ĳ�ʼ��
;6.����CӦ�ó���
;1.�Ѻ�ջ�ĳ�ʼ��
;ջ����stack���ɱ������Զ������ͷ� ����ź����Ĳ���ֵ���ֲ�������ֵ�ȡ��������ʽ���������ݽṹ�е�ջ
Stack_Size EQU 0x00000400 ;��һ����ֵ(0x00000400)��Ĵ���������һ��ָ���ķ�����Stack_size,������ջ�Ĵ�СΪ1Kb,
                AREA STACK, NOINIT, READWRITE, ALIGN=3 ;�ε����֡�δ��ʼ����ɳ�ʼΪ0�� �����д������ջ��8�ֽڶ���2*2*2,2��3�η�
                ;AREA αָ�����ڶ���һ������λ����ݶ�,
                ;NOINIT��ָ�������ݶν����������ڴ浥Ԫ��
              ;READWRITE���ԣ�ָ������Ϊ�ɶ���д�����ݶε�Ĭ������ΪREADWRITE��
              ;STACK ����
              ;ALIGN���ԣ�ʹ�÷�ʽΪALIGN ���ʽ����Ĭ��ʱ��ELF����ִ�������ļ����Ĵ���κ����ݶ��ǰ��ֶ���ģ����ʽ��ȡֵ��ΧΪ0��31����Ӧ�Ķ��뷽ʽΪ2���ʽ�η���
Stack_Mem SPACE Stack_Size ;����ջ�ռ�1Kb�����ֽڣ�����ʼ��Ϊ0�������׵�ַ����Stack_Mem
__initial_sp    ;��ʼ����ջָ�룬ָ��ջ��λ�ã����__initial_sp����ʾջ�ռ䶥��ַ��
                                                
; <h> Heap Configuration
; <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
;������heap�� ����Ҫ���ڶ�̬�ڴ���䣬Ҳ����malloc��calloc��realloc�Ⱥ�������ı����ռ����ڶ��ϣ�һ���ɳ���Ա�����ͷţ� ������Ա���ͷţ��������ʱ������OS���� ��ע���������ݽṹ�еĶ��������£����䷽ʽ��������������
Heap_Size EQU 0x00000200 ;����ѵĴ�С512Byte
                AREA HEAP, NOINIT, READWRITE, ALIGN=3 ;ALIGN����ָ�����뷽ʽ�� 8�ֽڶ���
__heap_base     ;��ʾ�ѿռ���ʼ��ַ
Heap_Mem SPACE Heap_Size ;����0x200�������ֽڣ�����ʼ��Ϊ0
__heap_limit    ;��ʾ�ѿռ������ַ
                PRESERVE8 ;PRESERVE8 ָ��ָ����ǰ�ļ����ֶ�ջ���ֽڶ���
                THUMB   ;���߻����������32λ��Thumbָ������Ҫ�����������λ�Ա�֤����

;2.������Ķ���
; Vector Table Mapped to Address 0 at Reset
;����Ϊ�������ڸ�λʱ��ӳ�䵽FLASH��0��ַ
;ʵ��������CODE��������STM32��FLASH����������ж���������ʼ��ַ��Ϊ0x8000000��
                AREA RESET, DATA, READONLY ;����һ�����ݶΣ�ֻ�ɶ�����������RESET
                                             ;DATA���ԣ����ڶ������ݶΣ�Ĭ��ΪREADWRITE��
                EXPORT __Vectors       ;�ж�������ʼ��EXPORT���ڳ���������һ��ȫ�ֵı��__Vectors���ñ�ſ����������ļ�������
                EXPORT __Vectors_End   ;�ж����������
                EXPORT __Vectors_Size  ;�ж��������С
;DCD�����ʾ����1��4�ֽڣ�32Ϊ���Ŀռ䣬ÿ��DCD��������һ��4�ֽڵĶ����ƴ��룬�ж��������ŵ�ʵ�������жϷ���������ڵ�ַ���ж�������һ������Falsh��0��ַ
__Vectors DCD __initial_sp ; Top of Stack
                                                 ;��һ��������ջ����ַ
;�ô������ֵַ��Ϊ __Vetors �������ʾ��ֵ,�õ�ַ�д洢__initial_sp����ʾ�ĵ�ֵַ
;ջ��ָ�룬������������Ŀ�ʼ��FLASH��0��ַ����λ������װ��ջ��ָ��
                DCD Reset_Handler ; Reset Handler
                                                 ;�ڶ��������Ǹ�λ�жϷ�����ڵ�ַ
                                                 ;��λ�쳣��װ��ջ���󣬵�һ��ִ�еģ����Ҳ�����
                DCD NMI_Handler ; NMI Handler ���������ж�
                DCD HardFault_Handler ; Hard Fault Handler Ӳ��������
                DCD MemManage_Handler ; MPU Fault Handler �洢��������
                DCD BusFault_Handler ; Bus Fault Handler ���ߴ�����
                ;���ߴ����жϣ�һ�㷢�������ݷ����쳣������fsmc���ʲ���
                DCD UsageFault_Handler ; Usage Fault Handler �÷�������
                ;�÷������жϣ�һ����Ԥȡֵ������λ��ָ����ݴ���ȴ���
                DCD 0 ; Reserved ������ʽ���Ǳ�����ַ�������κα�ŷ���
                DCD 0 ; Reserved
                DCD 0 ; Reserved
                DCD 0 ; Reserved
                DCD SVC_Handler ; SVCall Handler ;ϵͳ�����쳣����Ҫ��Ϊ�˵��ò���ϵͳ�ں˷��񣨷�������
                DCD DebugMon_Handler ; Debug Monitor Handler ���Լ��������ϵ㣬���ݹ۲�㣬�������ⲿ��������
                DCD 0 ; Reserved
                DCD PendSV_Handler ; PendSV Handler Ϊϵͳ�豸����ġ����������� ��pendable request��
                DCD SysTick_Handler ; SysTick Handler ϵͳ�δ�ʱ��
                ; External Interrupts �����ж�
                DCD WWDG_IRQHandler ; Window Watchdog ���ڿ��Ź�
                DCD PVD_IRQHandler ; PVD through EXTI Line detect
                                                 ;��Դ��ѹ���(PVD)�ж�
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
__Vectors_End ; ����
__Vectors_Size EQU __Vectors_End - __Vectors ;�õ�������Ĵ�С,304���ֽ�Ҳ����0x130���ֽ�

;3.��ַ��ӳ�估�ж��������ת��
;|.text|���ڱ�ʾ��C�����������Ĵ���Σ���������ĳ�ַ�ʽ��C������Ĵ����
                AREA |.text|, CODE, READONLY ;����һ������Σ��ɶ�����������.text �����������ֿ�ͷ����ö�������"|"����������|1_test|��
                ;����ֻ��"���ݶ�"��ʵ��������CODE���������FLASH���𶯣��� �ж�������ʼ��ַΪ0X8000000
                ;CODE���ԣ����ڶ������Σ�Ĭ��ΪREADONLY
; Reset handler
Reset_Handler PROC ;���һ�������Ŀ�ʼ;����PROC��ENDP��һ��αָ��ѳ���η�Ϊ���ɸ����̣�ʹ����Ľṹ������
                EXPORT Reset_Handler [WEAK]
                ;WEAK����������ͬ����������ڸñ�ű�����,����˵������������˵Ļ�,���������ģ���������ǿ�����c�ļ��з����жϷ������ֻҪ��֤C��������������һ�¾���
                ;EXPORTαָ�������ڳ���������һ��ȫ�ֵı��
                ;IMPORT��αָ������֪ͨ������Ҫʹ�õı����������Դ�ļ��ж���
                IMPORT __main ;__mainΪ����ʱ���ṩ�ĺ�������ɶ�ջ���ѵĳ�ʼ���ȹ�������������涨���__user_initial_stackheap
                ;IMPORT SystemInit
                ;LDR R0, =SystemInit
                ;BLX R0
                LDR R0, =__main ;����__main������C������
                BX R0
                ENDP
                
; Dummy Exception Handlers (infinite loops which can be modified)
;�����쳣������(����ѭ�������޸���)
NMI_Handler PROC
                EXPORT NMI_Handler [WEAK]
                B . ;����������
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
;����ֻ�Ƕ�����һ���պ���
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
;4.�Ѻ�ջ�ĳ�ʼ��
;*******************************************************************************
                 IF :DEF:__MICROLIB
                 ;�ж��Ƿ�ʹ��DEF:__MICROLIB��micro lib��
                 EXPORT __initial_sp
                 EXPORT __heap_base
                 EXPORT __heap_limit
                
                 ELSE
                
                 IMPORT __use_two_region_memory
                 EXPORT __user_initial_stackheap
                
__user_initial_stackheap
                 LDR R0, = Heap_Mem ;�����ʼ��ַ
                 LDR R1, =(Stack_Mem + Stack_Size);����ջ�Ĵ�С
                 LDR R2, = (Heap_Mem + Heap_Size);����ѵĴ�С
                 LDR R3, = Stack_Mem ;����ջ��ָ��
                 BX LR
                 ALIGN  
                 ;ALIGN���ԣ�ʹ�÷�ʽΪALIGN ���ʽ����Ĭ��ʱ��ELF����ִ�������ļ����Ĵ���κ����ݶ��ǰ��ֶ���ģ����ʽ��ȡֵ��ΧΪ0��31����Ӧ�Ķ��뷽ʽΪ2���ʽ�η�
                 ENDIF
                 END
