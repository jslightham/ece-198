// check current button inputs 
// return a 4 bit number 
// eg. 15 = 1111
int check_button_input();

// initialize all ports, inputs, outputs 
void initialize();

// return a random number from 1-15
int random_number();

// if current button combination matches note, return true 
bool button_match_note(int current_button, int note);

// set current_round_tune and current_round_size
void set_tune(int current_round_tune[], int tune_to_set[], int *current_round_size, int size_to_set);

// contains main loop 
int main();