// Minimum position for servo: 0.1ms on, 19.9ms off
// Maximum position for servo: 2.75ms on, 18.25ms off

#include "ece198.h"
#include "Servo.h"

// Lock the prize door
void closePrizeDoor(void) {
        for (int i = 0; i < 20; i++) {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_1);
            HAL_Delay(1);
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_1);
            HAL_Delay(19);
    }
}

// Unlock the prize door
void openPrizeDoor(void) {
        for (int i = 0; i < 20; i++) {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_1);
            HAL_Delay(2.75);
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_1);
            HAL_Delay(18.25);
    }
}