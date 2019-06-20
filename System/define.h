#ifndef __DEFINE_H
#define __DEFINE_H

typedef unsigned char 			uint8_t;
typedef unsigned short int 	uint16_t;
typedef unsigned int 				uint32_t;
typedef unsigned __int64 		uint64_t;

typedef uint32_t 			u32;
typedef uint16_t 			u16;
typedef uint8_t 			u8;

typedef volatile uint32_t  vu32;
typedef volatile uint16_t vu16;
typedef volatile uint8_t  vu8;

#define __IO volatile
#ifdef __cplusplus
  #define     __I     volatile                /*!< defines 'read only' permissions      */
#else
  #define     __I     volatile const          /*!< defines 'read only' permissions      */
#endif

	
	

typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

/******  STM32 specific Interrupt Numbers *********************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                            */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt            */
  TAMPER_IRQn                 = 2,      /*!< Tamper Interrupt                                     */
  RTC_IRQn                    = 3,      /*!< RTC global Interrupt                                 */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                               */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                 */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                 */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                 */
  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                 */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                 */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                 */
  DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 global Interrupt                      */
  DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 global Interrupt                      */
  DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 global Interrupt                      */
  DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 global Interrupt                      */
  DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 global Interrupt                      */
  DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 global Interrupt                      */
  DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 global Interrupt                      */

  ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
  USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
  USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
  CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
  CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
  TIM1_BRK_IRQn               = 24,     /*!< TIM1 Break Interrupt                                 */
  TIM1_UP_IRQn                = 25,     /*!< TIM1 Update Interrupt                                */
  TIM1_TRG_COM_IRQn           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                */
  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                */
  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
  RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
  USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
  TIM8_BRK_IRQn               = 43,     /*!< TIM8 Break Interrupt                                 */
  TIM8_UP_IRQn                = 44,     /*!< TIM8 Update Interrupt                                */
  TIM8_TRG_COM_IRQn           = 45,     /*!< TIM8 Trigger and Commutation Interrupt               */
  TIM8_CC_IRQn                = 46,     /*!< TIM8 Capture Compare Interrupt                       */
  ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
  FSMC_IRQn                   = 48,     /*!< FSMC global Interrupt                                */
  SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                */
  TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                */
  SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
  UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
  UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
  TIM6_IRQn                   = 54,     /*!< TIM6 global Interrupt                                */
  TIM7_IRQn                   = 55,     /*!< TIM7 global Interrupt                                */
  DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
  DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
  DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
  DMA2_Channel4_5_IRQn        = 59      /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
} IRQn_Type;


	
	
typedef struct{
	volatile uint32_t CTRL;	//偏移量：0x00
	volatile uint32_t LOAD;	//偏移量：0x04
	volatile uint32_t VAL;	//偏移量：0x08
	volatile uint32_t CALIB;//偏移量：0x0c
}SysTick_Type;


typedef struct{
	volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;
}RCC_TypeDef;

typedef struct
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;

typedef struct
{
  __IO uint32_t ACR;
  __IO uint32_t KEYR;
  __IO uint32_t OPTKEYR;
  __IO uint32_t SR;
  __IO uint32_t CR;
  __IO uint32_t AR;
  __IO uint32_t RESERVED;
  __IO uint32_t OBR;
  __IO uint32_t WRPR; 
} FLASH_TypeDef;


typedef struct
{
  __I  uint32_t CPUID;                        /*!< Offset: 0x00  CPU ID Base Register                                  */
  __IO uint32_t ICSR;                         /*!< Offset: 0x04  Interrupt Control State Register                      */
  __IO uint32_t VTOR;                         /*!< Offset: 0x08  Vector Table Offset Register                          */
  __IO uint32_t AIRCR;                        /*!< Offset: 0x0C  Application Interrupt / Reset Control Register        */
  __IO uint32_t SCR;                          /*!< Offset: 0x10  System Control Register                               */
  __IO uint32_t CCR;                          /*!< Offset: 0x14  Configuration Control Register                        */
  __IO uint8_t  SHP[12];                      /*!< Offset: 0x18  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IO uint32_t SHCSR;                        /*!< Offset: 0x24  System Handler Control and State Register             */
  __IO uint32_t CFSR;                         /*!< Offset: 0x28  Configurable Fault Status Register                    */
  __IO uint32_t HFSR;                         /*!< Offset: 0x2C  Hard Fault Status Register                            */
  __IO uint32_t DFSR;                         /*!< Offset: 0x30  Debug Fault Status Register                           */
  __IO uint32_t MMFAR;                        /*!< Offset: 0x34  Mem Manage Address Register                           */
  __IO uint32_t BFAR;                         /*!< Offset: 0x38  Bus Fault Address Register                            */
  __IO uint32_t AFSR;                         /*!< Offset: 0x3C  Auxiliary Fault Status Register                       */
  __I  uint32_t PFR[2];                       /*!< Offset: 0x40  Processor Feature Register                            */
  __I  uint32_t DFR;                          /*!< Offset: 0x48  Debug Feature Register                                */
  __I  uint32_t ADR;                          /*!< Offset: 0x4C  Auxiliary Feature Register                            */
  __I  uint32_t MMFR[4];                      /*!< Offset: 0x50  Memory Model Feature Register                         */
  __I  uint32_t ISAR[5];                      /*!< Offset: 0x60  ISA Feature Register                                  */
} SCB_Type;  


typedef struct
{
  uint32_t  RESERVED0;
  __IO uint16_t DR1;
  uint16_t  RESERVED1;
  __IO uint16_t DR2;
  uint16_t  RESERVED2;
  __IO uint16_t DR3;
  uint16_t  RESERVED3;
  __IO uint16_t DR4;
  uint16_t  RESERVED4;
  __IO uint16_t DR5;
  uint16_t  RESERVED5;
  __IO uint16_t DR6;
  uint16_t  RESERVED6;
  __IO uint16_t DR7;
  uint16_t  RESERVED7;
  __IO uint16_t DR8;
  uint16_t  RESERVED8;
  __IO uint16_t DR9;
  uint16_t  RESERVED9;
  __IO uint16_t DR10;
  uint16_t  RESERVED10; 
  __IO uint16_t RTCCR;
  uint16_t  RESERVED11;
  __IO uint16_t CR;
  uint16_t  RESERVED12;
  __IO uint16_t CSR;
  uint16_t  RESERVED13[5];
  __IO uint16_t DR11;
  uint16_t  RESERVED14;
  __IO uint16_t DR12;
  uint16_t  RESERVED15;
  __IO uint16_t DR13;
  uint16_t  RESERVED16;
  __IO uint16_t DR14;
  uint16_t  RESERVED17;
  __IO uint16_t DR15;
  uint16_t  RESERVED18;
  __IO uint16_t DR16;
  uint16_t  RESERVED19;
  __IO uint16_t DR17;
  uint16_t  RESERVED20;
  __IO uint16_t DR18;
  uint16_t  RESERVED21;
  __IO uint16_t DR19;
  uint16_t  RESERVED22;
  __IO uint16_t DR20;
  uint16_t  RESERVED23;
  __IO uint16_t DR21;
  uint16_t  RESERVED24;
  __IO uint16_t DR22;
  uint16_t  RESERVED25;
  __IO uint16_t DR23;
  uint16_t  RESERVED26;
  __IO uint16_t DR24;
  uint16_t  RESERVED27;
  __IO uint16_t DR25;
  uint16_t  RESERVED28;
  __IO uint16_t DR26;
  uint16_t  RESERVED29;
  __IO uint16_t DR27;
  uint16_t  RESERVED30;
  __IO uint16_t DR28;
  uint16_t  RESERVED31;
  __IO uint16_t DR29;
  uint16_t  RESERVED32;
  __IO uint16_t DR30;
  uint16_t  RESERVED33; 
  __IO uint16_t DR31;
  uint16_t  RESERVED34;
  __IO uint16_t DR32;
  uint16_t  RESERVED35;
  __IO uint16_t DR33;
  uint16_t  RESERVED36;
  __IO uint16_t DR34;
  uint16_t  RESERVED37;
  __IO uint16_t DR35;
  uint16_t  RESERVED38;
  __IO uint16_t DR36;
  uint16_t  RESERVED39;
  __IO uint16_t DR37;
  uint16_t  RESERVED40;
  __IO uint16_t DR38;
  uint16_t  RESERVED41;
  __IO uint16_t DR39;
  uint16_t  RESERVED42;
  __IO uint16_t DR40;
  uint16_t  RESERVED43;
  __IO uint16_t DR41;
  uint16_t  RESERVED44;
  __IO uint16_t DR42;
  uint16_t  RESERVED45;    
} BKP_TypeDef;


typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t CSR;
} PWR_TypeDef;


typedef struct
{
  __IO uint16_t CRH;
  uint16_t  RESERVED0;
  __IO uint16_t CRL;
  uint16_t  RESERVED1;
  __IO uint16_t PRLH;
  uint16_t  RESERVED2;
  __IO uint16_t PRLL;
  uint16_t  RESERVED3;
  __IO uint16_t DIVH;
  uint16_t  RESERVED4;
  __IO uint16_t DIVL;
  uint16_t  RESERVED5;
  __IO uint16_t CNTH;
  uint16_t  RESERVED6;
  __IO uint16_t CNTL;
  uint16_t  RESERVED7;
  __IO uint16_t ALRH;
  uint16_t  RESERVED8;
  __IO uint16_t ALRL;
  uint16_t  RESERVED9;
} RTC_TypeDef;


typedef struct
{
  __IO uint32_t ISER[8];                      /*!< Offset: 0x000  Interrupt Set Enable Register           */
       uint32_t RESERVED0[24];                                   
  __IO uint32_t ICER[8];                      /*!< Offset: 0x080  Interrupt Clear Enable Register         */
       uint32_t RSERVED1[24];                                    
  __IO uint32_t ISPR[8];                      /*!< Offset: 0x100  Interrupt Set Pending Register          */
       uint32_t RESERVED2[24];                                   
  __IO uint32_t ICPR[8];                      /*!< Offset: 0x180  Interrupt Clear Pending Register        */
       uint32_t RESERVED3[24];                                   
  __IO uint32_t IABR[8];                      /*!< Offset: 0x200  Interrupt Active bit Register           */
       uint32_t RESERVED4[56];                                   
  __IO uint8_t  IP[240];                      /*!< Offset: 0x300  Interrupt Priority Register (8Bit wide) */
       uint32_t RESERVED5[644];                                  
  __IO  uint32_t STIR;                         /*!< Offset: 0xE00  Software Trigger Interrupt Register     */
}  NVIC_Type;                                               


typedef struct
{
  __IO uint16_t SR;
  uint16_t  RESERVED0;
  __IO uint16_t DR;
  uint16_t  RESERVED1;
  __IO uint16_t BRR;
  uint16_t  RESERVED2;
  __IO uint16_t CR1;
  uint16_t  RESERVED3;
  __IO uint16_t CR2;
  uint16_t  RESERVED4;
  __IO uint16_t CR3;
  uint16_t  RESERVED5;
  __IO uint16_t GTPR;
  uint16_t  RESERVED6;
} USART_TypeDef;


typedef struct
{
  volatile uint32_t BTCR[8];   
} FSMC_Bank1_TypeDef; 

typedef struct
{
  volatile uint32_t BWTR[7];
} FSMC_Bank1E_TypeDef;




/* Memory mapping of Cortex-M3 Hardware */
#define SCS_BASE            (0xE000E000)                              /*!< System Control Space Base Address */
#define ITM_BASE            (0xE0000000)                              /*!< ITM Base Address                  */
#define CoreDebug_BASE      (0xE000EDF0)                              /*!< Core Debug Base Address           */
#define SysTick_BASE        (SCS_BASE +  0x0010)                      /*!< SysTick Base Address              */
#define NVIC_BASE           (SCS_BASE +  0x0100)                      /*!< NVIC Base Address                 */
#define SCB_BASE            (SCS_BASE +  0x0D00)


  
/*Peripheral memory map*/
#define PERIPH_BASE           ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */
#define FSMC_R_BASE           ((uint32_t)0xA0000000)

#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)



#define RTC_BASE              (APB1PERIPH_BASE + 0x2800)
#define BKP_BASE              (APB1PERIPH_BASE + 0x6C00)
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000)


#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASE            (APB2PERIPH_BASE + 0x1C00)
#define GPIOG_BASE            (APB2PERIPH_BASE + 0x2000)
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800)



#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)
#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x2000)


#define NVIC_BASE           	(SCS_BASE +  0x0100)

//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08



#define FSMC_Bank1_R_BASE     (FSMC_R_BASE + 0x0000)
#define FSMC_Bank1E_R_BASE    (FSMC_R_BASE + 0x0104)


#define RTC                 ((RTC_TypeDef *) RTC_BASE)
#define BKP                 ((BKP_TypeDef *) BKP_BASE)
#define PWR                 ((PWR_TypeDef *) PWR_BASE)
#define SCB                 ((SCB_Type *)SCB_BASE)
#define SysTick 						((SysTick_Type*)SysTick_BASE)
#define NVIC                ((NVIC_Type *) NVIC_BASE)




#define RCC 								((RCC_TypeDef *) RCC_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)


#define FLASH               ((FLASH_TypeDef *) FLASH_R_BASE)
#define USART1              ((USART_TypeDef *) USART1_BASE)

//CM3 的位带操作，具体的实现比较复杂
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入








#define FSMC_Bank1          ((FSMC_Bank1_TypeDef *) FSMC_Bank1_R_BASE)
#define FSMC_Bank1E         ((FSMC_Bank1E_TypeDef *) FSMC_Bank1E_R_BASE)




void Stm32_Clock_Init();
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);//设置偏移地址
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);//设置NVIC分组
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);//设置中断
#endif