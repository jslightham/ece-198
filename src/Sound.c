#include "ece198.h"
#include "Sound.h"

// Play a note with a given frequency for the given note length
void playNote(int note, int length) {
    int i = 0;
    double delay = 1000.0/(note*2.0);
    // Generate a square wave with given frequency
    while (i * delay < length) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
        HAL_Delay(delay);
        i++;
    }
}
