#include "gpio_it.h"


//为每个外设实例注册回调
static EXTI_Callback EXTI0_Callback = NULL;
static EXTI_Callback EXTI1_Callback = NULL;
static EXTI_Callback EXTI2_Callback = NULL;
static EXTI_Callback EXTI3_Callback = NULL;
static EXTI_Callback EXTI4_Callback = NULL;
static EXTI_Callback EXTI5_Callback = NULL;
//...
static EXTI_Callback EXTI12_Callback = NULL;


//在初始化时注册回调函数
void exti_register_callback(uint16_t GPIO_Pin, EXTI_Callback callback_function) {
    // if (GPIO_Pin == GPIO_PIN_0) {
    //     EXTI0_Callback = callback_function;
    // } else if (GPIO_Pin == GPIO_PIN_1) {
    //     EXTI1_Callback = callback_function;
    // } else if (GPIO_Pin == GPIO_PIN_2) {
    //     EXTI2_Callback = callback_function;
    // } else if (GPIO_Pin == GPIO_PIN_3) {
    //     EXTI3_Callback = callback_function;
    // } else if (GPIO_Pin == GPIO_PIN_4) {
    //     EXTI4_Callback = callback_function;
    // }
    if(GPIO_Pin == GPIO_PIN_12)
    {
        EXTI12_Callback = callback_function;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    // if (GPIO_Pin == GPIO_PIN_0 && EXTI0_Callback) {
    //     EXTI0_Callback();
    // } else if (GPIO_Pin == GPIO_PIN_1 && EXTI1_Callback) {
    //     EXTI1_Callback();
    // } else if (GPIO_Pin == GPIO_PIN_2 && EXTI2_Callback) {
    //     EXTI2_Callback();
    // } else if (GPIO_Pin == GPIO_PIN_3 && EXTI3_Callback) {
    //     EXTI3_Callback();
    // } else if (GPIO_Pin == GPIO_PIN_4 && EXTI4_Callback) {
    //     EXTI4_Callback();
    // }
    if(GPIO_Pin == GPIO_PIN_12 && EXTI12_Callback) {
        EXTI12_Callback();
    }
}

