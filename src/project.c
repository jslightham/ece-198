
#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"
#include "Sound.h"
#include "LiquidCrystal.h"
#include "Display.h"
#include "Servo.h"

// Structure for a button, which stores the port and pins
struct button {
   GPIO_TypeDef *port;
   uint16_t pin;
};

struct button buttons[4];

// Check current button inputs, button combinations are stored as 4 bit numbers
// return a 4 bit number 
// eg. 15 = 1111 (button 1, 2, 3, 4)
// eg. 3 = 0011 (button 3, 4)
int check_button_input(){
    return (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) * 8 +
            !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) * 4 + 
            !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) * 2 + 
            !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0));
}

// initialize all ports, inputs, outputs 
void initialize(){

    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Declare button Pins & Ports
    buttons[0].port = GPIOA;
    buttons[0].pin = GPIO_PIN_0;
    buttons[1].port = GPIOA;
    buttons[1].pin = GPIO_PIN_1;
    buttons[2].port = GPIOA;
    buttons[2].pin = GPIO_PIN_4;
    buttons[3].port = GPIOB;
    buttons[3].pin = GPIO_PIN_0;

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the buttons)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the LCD Display, and buttons)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, servo, and speaker)

    SerialSetup(9600);

    // inputs for buttons 
    InitializePin(GPIOA, GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_PULLUP, 0); // A0
    InitializePin(GPIOA, GPIO_PIN_1, GPIO_MODE_INPUT, GPIO_PULLUP, 0); // A1
    InitializePin(GPIOA, GPIO_PIN_4, GPIO_MODE_INPUT, GPIO_PULLUP, 0); // A4
    InitializePin(GPIOB, GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_PULLUP, 0); // B0

    // Servo Motors
    InitializePin(GPIOC, GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); 

    // Initialize LCD
    LiquidCrystal(GPIOB, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6);

    // Initialize Speaker
    InitializePin(GPIOC, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // put a 120 ohm resistor on the speaker so it doesn't draw too much current
}

// Return a number between index from and to
int random_number(int from, int to) {
    return (random() % (to) + from);
}

// if current button combination matches note, return true 
bool button_match_note(int current_button, int note){
    return current_button == note;
}

// set current_round_tune and current_round_size
void set_tune(int current_round_tune[], int tune_to_set[], int *current_round_size, int size_to_set){
    (*current_round_size) = size_to_set;
    for(int i = 0; i < (*current_round_size); i++){
        current_round_tune[i] = tune_to_set[i];
    }
}

// main function 
// contains main loop 
int main(void){
    initialize(); // Initialize all ports, inputs, outputs

    // press on board blue button to start
    while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)){
    }
    
    srand(HAL_GetTick()); // seed for randon number

    int note_b = 0;
    int note_a = 0; 
    int note_c = 0; // combination for each note 
    int note_d = 0;
    int note_e = 0;
    int note_f = 0;

    // Shuffle a known array of valid button combinations to get randomiozed buttons for the game
    int validNumbers[6] = {3, 5, 6, 9, 10, 12};
    for (int i = 0; i < 8; i++) {
        int n1 = random_number(0, 5);
        int n2 = random_number(0, 5);
        int temp = validNumbers[n1];
        validNumbers[n1] = validNumbers[n2];
        validNumbers[n2] = temp;
    }
    note_a = validNumbers[0];
    note_b = validNumbers[1];
    note_c = validNumbers[2];
    note_d = validNumbers[3];
    note_e = validNumbers[4];
    note_f = validNumbers[5];

    // Display the first round notes on the LCD
    displayNotes(note_a, note_b, note_c, note_d, note_e, note_f);

    int current_button = 0; // current button combination 

    int round_1_tune[3] = {note_a, note_b, note_c}; // note combination for each round 
    int round_2_tune[4] = {note_a, note_b, note_c, note_d};
    int round_3_tune[5] = {note_a, note_b, note_c, note_d, note_e};

    int round_1_size = 3; // number of notes for each round 
    int round_2_size = 4;
    int round_3_size = 5;

    int current_round_tune[5] = {0, 0, 0, 0, 0}; // note combination for current round 

    int current_round_size = 0;

    int current_note_index = 0; // which note in the tune the player is currently on 

    int current_round = 1; // current round for the player, corresponds to round_#_tune 
    bool current_round_win = false; // if player won the current round 

    bool all_rounds_win = false;

    int *p_current_round_size = &current_round_size;
    set_tune(current_round_tune, round_1_tune, p_current_round_size, round_1_size); // setup tune for first round 

    closePrizeDoor(); // Ensure the prize door is locked before game start


    // main loop 
    while(!all_rounds_win){ // while player has not won yet 
        // Play the round's note on the speaker
        if(current_round_tune[current_note_index] == note_a){
            playNote(NOTE_A, 1000);
        }
        else if(current_round_tune[current_note_index] == note_b){
            playNote(NOTE_B, 1000);
        }
        else if(current_round_tune[current_note_index] == note_c){
            playNote(NOTE_C, 1000);
        }
        else if(current_round_tune[current_note_index] == note_d){
            playNote(NOTE_D, 1000);
        }
        else if(current_round_tune[current_note_index] == note_e){
            playNote(NOTE_E, 1000);
        }
        else if(current_round_tune[current_note_index] == note_f){
            playNote(NOTE_F, 1000);
        }
        
        while(current_button != note_a && current_button != note_b && current_button != note_c && current_button != note_d && current_button != note_e && current_button != note_f){
            // check which button combination player pressed 
            current_button = check_button_input();
        }

        // check if button matches any note, if there is a match, play it on speaker 
        if(button_match_note(current_button, note_a)){
            playNote(NOTE_A, 1000); 
        }
        else if(button_match_note(current_button, note_b)){
            playNote(NOTE_B, 1000);
        }
        else if(button_match_note(current_button, note_c)){
            playNote(NOTE_C, 1000);
        }
        else if(button_match_note(current_button, note_d)){
            playNote(NOTE_D, 1000);
        }
        else if(button_match_note(current_button, note_e)){
            playNote(NOTE_E, 1000);
        }
        else if(button_match_note(current_button, note_f)){
            playNote(NOTE_F, 1000);
        }
        else{ // if there is no match 
            // play a long, low note to indicate a wrong button combination
            playNote(50, 2000);
        }

        // check if player input matches tune 
        if(current_button == current_round_tune[current_note_index]){ // if player played correct in the tune 
            current_note_index ++; 
        }
        else{ // if player plays wrong note 
            current_note_index = 0; // reset to start of round 
        }
        
        // check if player wins current round
        if(current_note_index == current_round_size){ // if player has played all the notes for the round 
            current_round_win = true;
                // Play a win tune
                playNote(NOTE_A, 500);
                playNote(NOTE_B, 500);
                playNote(NOTE_C, 500);
                HAL_Delay(100);
                playNote(NOTE_C, 500);
                HAL_Delay(100);
                playNote(NOTE_C, 500);
                HAL_Delay(100);
                playNote(NOTE_C, 500);

            if(current_round == 3){ // if player wins last round 
                all_rounds_win = true; 
            }
            current_note_index = 0; // reset index to beginning for next round
        }

        // set up next round 
        if(current_round_win){ // if player wins the current round 
            if(current_round == 1){ // if player won round 1
                int *p_current_round_size = &current_round_size;
                set_tune(current_round_tune, round_2_tune, p_current_round_size, round_2_size); // setup round 2
            }
            else if(current_round == 2){
                int *p_current_round_size = &current_round_size;
                set_tune(current_round_tune, round_3_tune, p_current_round_size, round_3_size);
            }
            current_round ++;
            current_round_win = false; 
        }
        current_button = 0; // reset current button
        HAL_Delay(1000);
    }

    openPrizeDoor();

    // when the player wins all rounds
    // play sound for winning 
    playNote(NOTE_A, 500);
    playNote(NOTE_B, 500);
    playNote(NOTE_C, 500);
    playNote(NOTE_D, 500);
    playNote(NOTE_E, 500);
    playNote(NOTE_F, 500);
    HAL_Delay(100);
    playNote(NOTE_F, 500);
    HAL_Delay(100);
    playNote(NOTE_F, 500);
    HAL_Delay(100);
    playNote(NOTE_F, 500);
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void) {
    HAL_IncTick(); // tell HAL that a new tick has happened
}
