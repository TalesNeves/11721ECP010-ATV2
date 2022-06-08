#include <stdlib.h>
#define STM32_RCC_BASE 0x40023800
#define STM32_GPIOC_BASE     0x48000800U
#define STM32_RCC_AHB1ENR_OFFSET 0x0030
#define STM32_GPIO_MODER_OFFSET   0x0000/* GPIO port mode register */
#define STM32_GPIO_OTYPER_OFFSET  0x0004/* GPIO port output type register */
#define STM32_GPIO_PUPDR_OFFSET   0x000c/* GPIO port pull-up/pull-downregister */
#define STM32_RCC_AHB1ENR (STM32_RCC_BASE + STM32_RCC_AHB1ENR_OFFSET)
#define STM32_GPIOC_MODER(STM32_GPIOC_BASE + STM32_GPIO_MODER_OFFSET)
#define STM32_GPIOC_OTYPER(STM32_GPIOC_BASE + STM32_GPIO_OTYPER_OFFSET)
#define STM32_GPIOC_PUPDR(STM32_GPIOC_BASE + STM32_GPIO_PUPDR_OFFSET)
#define RCC_AHB1ENR_GPIOCEN (1 << 2)
#define GPIO_MODER_INPUT(0)/* Input */
#define GPIO_MODER_OUTPUT(1)/* General purpose output mode */
#define GPIO_MODER_ALT(2)/* Alternate mode */
#define GPIO_MODER_ANALOG(3)/* Analog mode */
#define GPIO_MODER13_SHIFT(26)
#define GPIO_MODER13_MASK(3 << GPIO_MODER13_SHIFT)
#define GPIO_OTYPER_PP(0)/* 0=Output push-pull */
#define GPIO_OTYPER_OD(1)/* 1=Output open-drain */
#define GPIO_OT13_SHIFT(13)
#define GPIO_OT13_MASK(1 << GPIO_OT13_SHIFT)
#define GPIO_PUPDR_NONE(0)/* No pull-up, pull-down */
#define GPIO_PUPDR_PULLUP(1)/* Pull-up */
#define GPIO_PUPDR_PULLDOWN(2)/* Pull-down */
#define GPIO_PUPDR13_SHIFT(26)
#define GPIO_PUPDR13_MASK(3 << GPIO_PUPDR13_SHIFT)


int main(int argc,char *argv[]){
    uint32_t*pRCC_AHB1ENR  = (uint32_t*)STM32_RCC_AHB1ENR;
    uint32_t*pGPIOC_MODER  = (uint32_t*)STM32_GPIOC_MODER;
    uint32_t*pGPIOC_OTYPER = (uint32_t*)STM32_GPIOC_OTYPER;
    uint32_t*pGPIOC_PUPDR  = (uint32_t*)STM32_GPIOC_PUPDR;
    uint32_t*pGPIOC_BSRR   = (uint32_t*)STM32_GPIOC_BSRR;
    reg  = *pRCC_AHB1ENR;
    reg |= RCC_AHB1ENR_GPIOCEN;
    *pRCC_AHB1ENR = reg;

    reg = *pGPIOC_MODER;
    reg &= ~(GPIO_MODER13_MASK);
    reg |= (GPIO_MODER_OUTPUT << GPIO_MODER13_SHIFT);
    *pGPIOC_MODER = reg;
    reg = *pGPIOC_OTYPER;
    reg &= ~(GPIO_OT13_MASK);
    reg |= (GPIO_OTYPER_PP << GPIO_OT13_SHIFT);
    *pGPIOC_OTYPER = reg;
    reg = *pGPIOC_PUPDR;
    reg &= ~(GPIO_PUPDR13_MASK);
    reg |= (GPIO_PUPDR_NONE << GPIO_PUPDR13_SHIFT);
    *pGPIOC_PUPDR = reg;


    while(1);
    return EXIT_SUCCESS;
}