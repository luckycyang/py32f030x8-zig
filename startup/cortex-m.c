
#include <stdint.h>
// #include <string.h>

extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss;

void Reset_Handler(void);
void _start(void) __attribute__((alias("Reset_Handler")));
void Default_Handler(void);
extern int main(void);
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

void WWDG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_15_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_3_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void ADC_COMP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
    __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void LPTIM1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM14_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM16_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM17_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void LED_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));

void (*const isr_vector[])(void) __attribute__((section(".isr_vector"))) = {
    Reset_Handler,      // Reset Handler
    NMI_Handler,        // NMI Handler
    HardFault_Handler,  // Hard Fault
    MemManage_Handler,  // Memory Management
    BusFault_Handler,   // Bus Fault
    UsageFault_Handler, // Usage Fault
    (void (*)(void))0,  // Reserved
    (void (*)(void))0,  // Reserved
    (void (*)(void))0,  // Reserved
    (void (*)(void))0,  // Reserved
    SVC_Handler,        // SVCall Handler
    DebugMon_Handler,   // Debug Monitor
    (void (*)(void))0,  // Reserved
    PendSV_Handler,     // PendSV Handler
    SysTick_Handler,    // SysTick Handler
    // External Interrupts
    WWDG_IRQHandler,                // Window Watchdog
    PVD_IRQHandler,                 // PVD
    RTC_IRQHandler,                 // RTC
    FLASH_IRQHandler,               // Flash
    RCC_IRQHandler,                 // RCC
    EXTI0_1_IRQHandler,             // EXTI Line 0 and 1
    EXTI2_3_IRQHandler,             // EXTI Line 2 and 3
    EXTI4_15_IRQHandler,            // EXTI Line 4 to 15
    (void (*)(void))0,              // Reserved
    DMA1_Channel1_IRQHandler,       // DMA1 Channel 1
    DMA1_Channel2_3_IRQHandler,     // DMA1 Channel 2 and 3
    (void (*)(void))0,              // Reserved
    ADC_COMP_IRQHandler,            // ADC and Comparator
    TIM1_BRK_UP_TRG_COM_IRQHandler, // TIM1 Break, Update, Trigger and
                                    // Commutation
    TIM1_CC_IRQHandler,             // TIM1 Capture Compare
    (void (*)(void))0,              // Reserved
    TIM3_IRQHandler,                // TIM3
    LPTIM1_IRQHandler,              // LPTIM1
    (void (*)(void))0,              // Reserved
    TIM14_IRQHandler,               // TIM14
    (void (*)(void))0,              // Reserved
    TIM16_IRQHandler,               // TIM16
    TIM17_IRQHandler,               // TIM17
    I2C1_IRQHandler,                // I2C1
    (void (*)(void))0,              // Reserved
    SPI1_IRQHandler,                // SPI1
    SPI2_IRQHandler,                // SPI2
    USART1_IRQHandler,              // USART1
    USART2_IRQHandler,              // USART2
    (void (*)(void))0,              // Reserved
    LED_IRQHandler,                 // LED
    (void (*)(void))0               // Reserved
};

void Reset_Handler(void) {
  uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *flash_data = (uint8_t *)&_sidata;
  uint8_t *sram_data = (uint8_t *)&_sdata;
  uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  uint8_t *start_bss = (uint8_t *)&_sbss;
  // Copy data section from Flash to SRAM
  // memcpy(sram_data, flash_data, data_size);
  for (int i = 0; i < data_size; i++) {
    sram_data[i] = flash_data[i];
  }

  // Zero-fill .bss section in SRAM
  // memset(start_bss, 0, bss_size);
  for (int i = 0; i < bss_size; i++) {
    start_bss[i] = 0;
  }

  // if HAL
  // extern void SystemInit(void);
  // SystemInit();

  main();
}
void Default_Handler(void) {
  while (1) {
  }
}
