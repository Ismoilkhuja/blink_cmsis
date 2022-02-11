#include "stm32f1xx.h"

__IO uint32_t time = 0;


void delay_ms(uint32_t ms){
    uint32_t start = time;
    while((time - start) < ms){}
}

void RCC_DeInit(void)
{
    SET_BIT(RCC->CR, RCC_CR_HSION);
    while(READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RESET) {}
    MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80U);
    CLEAR_REG(RCC->CFGR);
    while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET) {}
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET) {}
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON);
    while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET) {}
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
    //Reset all CSR flags
    SET_BIT(RCC->CSR, RCC_CSR_RMVF);
}


void SetSysClockTo72(void){
    SET_BIT(RCC->CR, RCC_CR_HSEON);
    while(READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET) {}
    //Enable the Prefetch Buffer
    CLEAR_BIT(FLASH->ACR, FLASH_ACR_PRFTBE);
    SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBE);
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_2);
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV1);
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV2);
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL,
               RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9);
    SET_BIT(RCC->CR, RCC_CR_PLLON);
    while(READ_BIT(RCC->CR, RCC_CR_PLLRDY) != (RCC_CR_PLLRDY)) {}
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {}
}

void GPIO_Init(void){
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF1 | GPIO_CRL_MODE1, GPIO_CRL_MODE1);
}


int main(void){

    RCC_DeInit();
    SetSysClockTo72();
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/1000);
    GPIO_Init();

    while (1) {
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
        delay_ms(1000);
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS1);
        delay_ms(1000);
    }

    return 0;
}



void SysTick_Handler(void){
    time++;
}
