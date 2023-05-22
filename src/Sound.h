// Frequencies are taken from: https://pages.mtu.edu/~suits/notefreqs.html
// Place a 120ohm resistor between the speaker and signal line

#define NOTE_C3 130
#define NOTE_CS3 138
#define NOTE_D3 146
#define NOTE_DS3 155
#define NOTE_E3 164
#define NOTE_F3 174
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 246

#define NOTE_C4 261
#define NOTE_CS4 277
#define NOTE_D4 293
#define NOTE_DS4 311
#define NOTE_E4 329
#define NOTE_F4 349
#define NOTE_FS4 369
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 493

#define NOTE_A 100
#define NOTE_B 250
#define NOTE_C 400
#define NOTE_D 550
#define NOTE_E 700
#define NOTE_F 900


// Play note note for length length (in milliseconds)
void playNote(int note, int length);
