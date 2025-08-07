const py32f030x8 = @cImport({
    @cDefine("PY32F030x8", "y");
    @cInclude("py32f0xx.h");
});

export fn main() void {
    const rcc: [*c]volatile py32f030x8.RCC_TypeDef = py32f030x8.RCC;
    const gpioa: [*c]volatile py32f030x8.GPIO_TypeDef = py32f030x8.GPIOA;
    rcc.*.IOPENR &= ~py32f030x8.RCC_IOPENR_GPIOAEN;
    rcc.*.IOPENR |= py32f030x8.RCC_IOPENR_GPIOAEN;
    gpioa.*.MODER &= ~py32f030x8.GPIO_MODER_MODE2;
    gpioa.*.MODER |= py32f030x8.GPIO_MODER_MODE2 & (1 << py32f030x8.GPIO_MODER_MODE2_Pos);
    gpioa.*.OTYPER &= ~py32f030x8.GPIO_OTYPER_OT2;
    gpioa.*.OTYPER |= py32f030x8.GPIO_OTYPER_OT2 & (1 << py32f030x8.GPIO_OTYPER_OT2_Pos);

    while (true) {
        gpioa.*.ODR = py32f030x8.GPIO_ODR_OD2 ^ gpioa.*.ODR;
    }
}

// RCC->IOPENR &= ~RCC_IOPENR_GPIOAEN;
// RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
// GPIOA->MODER &= ~GPIO_MODER_MODE2;
// GPIOA->MODER |= GPIO_MODER_MODE2 & (1U << GPIO_MODER_MODE2_Pos);
// GPIOA->OTYPER &= ~GPIO_OTYPER_OT2;
// GPIOA->OTYPER |= GPIO_OTYPER_OT2 & (1U << GPIO_OTYPER_OT2_Pos);
// while (1) {
//   GPIOA->ODR = GPIO_ODR_OD2 ^ GPIOA->ODR;
//   __WFI();
// }
