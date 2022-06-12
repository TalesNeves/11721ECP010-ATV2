/*manual https://www.st.com/resource/en/reference_manual/dm00119316-stm32f411xc-e-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf#%5B%7B%22num%22%3A287%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C66%2C708%2Cnull%5D*/
#include <stdlib.h>
#include <stdint.h>
#define STM32_RCC_BASE              0x40023800 /*Reference: 2.3*/
#define STM32_GPIOC_BASE            0x40020800U /*Reference: 2.3*/
#define STM32_GPIOA_BASE            0x40020000U /*Reference: 2.3*/
#define STM32_RCC_AHB1ENR_OFFSET    0x0030
#define STM32_GPIO_MODER_OFFSET     0x0000/* GPIO port mode register. Address offset: 0x00. Reference: 8.4.1*/
#define STM32_GPIO_OTYPER_OFFSET    0x0004/* GPIO port output type registe. Address offset: 0x04. Reference: 8.4.2*/
#define STM32_GPIO_PUPDR_OFFSET     0x000c/* GPIO port pull-up/pull-downregister. Address offset: 0x0C. Reference: 8.4.4 */
#define STM32_GPIO_IDR_OFFSET       0x10/*GPIO port input data register (GPIOx_IDR). Address offext: 0x10. Reference: 8.4.5*/
#define STM32_GPIO_BSRR_OFFSET      0x18/*GPIO port bit set/reset register (GPIOx_BSRR). Addresses: 0x18. Referenc: 8.4.7 */
#define STM32_RCC_AHB1ENR           (STM32_RCC_BASE + STM32_RCC_AHB1ENR_OFFSET)

/*GPIO ADDRESSES AND BIT VALUES*/
#define STM32_GPIOC_MODER           (STM32_GPIOC_BASE + STM32_GPIO_MODER_OFFSET)
#define STM32_GPIOC_OTYPER          (STM32_GPIOC_BASE + STM32_GPIO_OTYPER_OFFSET)
#define STM32_GPIOC_PUPDR           (STM32_GPIOC_BASE + STM32_GPIO_PUPDR_OFFSET)
#define STM32_GPIOC_BSRR            (STM32_GPIOC_BASE + STM32_GPIO_BSRR_OFFSET)

#define STM32_GPIOA_MODER           (STM32_GPIOA_BASE + STM32_GPIO_MODER_OFFSET)
#define STM32_GPIOA_PUPDR           (STM32_GPIOA_BASE + STM32_GPIO_PUPDR_OFFSET)
#define STM32_GPIOA_IDR             (STM32_GPIOA_BASE + STM32_GPIO_IDR_OFFSET)  

#define RCC_AHB1ENR_GPIOCEN         (1 << 2)
    /*8.4.1*/
#define GPIO_MODER_INPUT            (0)/* Input */
#define GPIO_MODER_OUTPUT           (1)/* General purpose output mode */
#define GPIO_MODER_ALT              (2)/* Alternate mode */
#define GPIO_MODER_ANALOG           (3)/* Analog mode */

    /*8.4.2*/
#define GPIO_OTYPER_PP              (0)/* 0=Output push-pull */
#define GPIO_OTYPER_OD              (1)/* 1=Output open-drain */

    /*8.4.4*/
#define GPIO_PUPDR_NONE             (0)/* No pull-up, pull-down */
#define GPIO_PUPDR_PULLUP           (1)/* Pull-up */
#define GPIO_PUPDR_PULLDOWN         (2)/* Pull-down */

/*LED ADDRESSES AND MASKS*/
#define GPIO_MODER13_SHIFT          (26) /*MODER13 starts at the 26th bit on the GPIO port mode register (GPIOx_MODER).Reference: Section 8.4.1 */
#define GPIO_MODER13_MASK           (GPIO_MODER_ANALOG << GPIO_MODER13_SHIFT) /*set port13 port mode to analog*/
#define GPIO_OT13_SHIFT             (13) /*OT13 is the 13th bit at the GPIO port output type register (GPIOx_OTYPER).Reference: Section 8.4.2*/
#define GPIO_OT13_MASK              (GPIO_OTYPER_OD << GPIO_OT13_SHIFT) /*set OT13 as output open-drain*/

#define GPIO_PUPDR13_SHIFT          (26) /*PUPDR13 starts at the 26th bit on the  GPIO port pull-up/pull-down register (GPIOx_PUPDR).Reference: Section 8.4.4*/
#define GPIO_PUPDR13_MASK           (GPIO_PUPDR_NONE << GPIO_PUPDR13_SHIFT)
#define GPIO_BSRR_SET(n)            (1 << (n))
#define GPIO_BSRR_RST(n)            (1 << (n + 16))

/*INPUT BUTTON*/
#define GPIO_MODERPA0_SHIFT          (0) /*MODER0 starts at the first bit on the GPIO port mode register (GPIOx_MODER).Reference: Section 8.4.1 */
#define GPIO_MODERPA0_MASK           (GPIO_MODER_INPUT << GPIO_MODERPA0_SHIFT) /*set port13 port mode to analog*/


#define GPIO_PUPDRPA0_SHIFT          (0) /*PUPDRPA0 starts at the first bit on the  GPIO port pull-up/pull-down register (GPIOx_PUPDR).Reference: Section 8.4.4*/
#define GPIO_PUPDRPA0_MASK           (GPIO_PUPDR_PULLUP << GPIO_PUPDR13_SHIFT)

#define GPIO_IDRPA0_SHIFT            (0)

int main(int argc,char *argv[]){
    uint32_t reg;

    uint32_t *pRCC_AHB1ENR  = (uint32_t *)STM32_RCC_AHB1ENR;

    uint32_t *pGPIOC_MODER  = (uint32_t *)STM32_GPIOC_MODER;
    uint32_t *pGPIOC_OTYPER = (uint32_t *)STM32_GPIOC_OTYPER;
    uint32_t *pGPIOC_PUPDR  = (uint32_t *)STM32_GPIOC_PUPDR;
    uint32_t *pGPIOC_BSRR   = (uint32_t *)STM32_GPIOC_BSRR;

    uint32_t *pGPIOA_MODER  = (uint32_t *)STM32_GPIOA_MODER;
    uint32_t *pGPIOA_PUPDR  = (uint32_t *)STM32_GPIOA_PUPDR;
    uint32_t *pGPIOA_IDR    = (uint32_t *)STM32_GPIOA_IDR;
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

    reg = *pGPIOA_MODER;
    reg &= ~(GPIO_MODERPA0_MASK);
    reg |= (GPIO_MODER_INPUT << GPIO_MODERPA0_SHIFT);
    *pGPIOA_MODER = reg;
    reg = *pGPIOA_PUPDR;
    reg &= ~(GPIO_PUPDRPA0_MASK);
    reg |= (GPIO_PUPDR_PULLUP << GPIO_PUPDRPA0_SHIFT);
    *pGPIOA_PUPDR=reg;
    reg = *pGPIOA_IDR;
    reg &= ~(0);
    reg |= (0);
    *pGPIOA_PUPDR=reg;

    static char fw_version[] = {'V', 'i','.','0'};
    static uint32_t led_status;
    uint32_t LED_DELAY = 150;
    uint32_t button_state = 0;
    while(1){
        button_state = *pGPIOA_IDR;
        if(button_state &(1 << GPIO_IDRPA0_SHIFT))
        {
            LED_DELAY = 75;
        }
        else{
            LED_DELAY = 150;
        }
        *pGPIOC_BSRR = GPIO_BSRR_SET(13);
        for(uint32_t i =0; i < LED_DELAY; i++);
        *pGPIOC_BSRR = GPIO_BSRR_RST(13);
        for(uint32_t i =0; i < LED_DELAY; i++);
    };
    return EXIT_SUCCESS;
}
