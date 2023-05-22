#include "Display.h"
#include <string.h>
#include <stdlib.h>
#include "LiquidCrystal.h"

// Convert the 4-bit integer a, into the first button value
int getButton1(int a) {
    int n1, n2, n3, n4;
    // take the remainder dividing the button by 2, to convert to binary
    n1 = a % 2;
    a = a / 2;
    n2 = a % 2;
    a = a / 2;
    n3 = a % 2;
    a = a / 2;
    n4 = a % 2;
    
    // Given the binary value, return the first button value
    if (n1 == 1) {
        return 4;
    } else if (n2 == 1) {
        return 3;
    }
    else if (n3 == 1) {
        return 2;
    }
    else if (n4 == 1) {
        return 1;
    }
    return 0;
}

// Convert the 4-bit integer a, into the second button value
int getButton2(int a) {
    int n1, n2, n3, n4;
    n1 = a % 2;
    a = a / 2;
    n2 = a % 2;
    a = a / 2;
    n3 = a % 2;
    a = a / 2;
    n4 = a % 2;

    // Given the binary value, return the second button value
    bool hasButton1 = false;
    if (n1 == 1 && !hasButton1) {
        hasButton1 = true; // Button 1 will never be the second button.
    }
    if (n2 == 1) {
        if (hasButton1) {
            return 3;
        } else {
            hasButton1 = true;
        }
    }
    if (n3 == 1) {
        if (hasButton1) {
            return 2;
        } else {
            hasButton1 = true;
        }
    }
    if (n4 == 1) {
        return 1;
    }
    return 0;
}

// Display the 6 given notes (4-bit numbers) on the LCD
void displayNotes(int a, int b, int c, int d, int e, int f) {
    char *str1 = malloc(sizeof(char) * 15); // Line 1 of LCD
    char *str2 = malloc(sizeof(char) * 15); // Line 2 of LCD
    
    // Manually set each LCD letter
    str1[0] = 'A';
    str1[1] = ':';
    str1[2] = getButton1(a) + '0'; // add the 0 character to convert to ASCII
    str1[3] = getButton2(a) + '0';
    str1[4] = ' ';
    str1[5] = 'B';
    str1[6] = ':';
    str1[7] = getButton1(b) + '0';
    str1[8] = getButton2(b) + '0';
    str1[9] = ' ';
    str1[10] = 'C';
    str1[11] = ':';
    str1[12] = getButton1(c) + '0';
    str1[13] = getButton2(c) + '0';
    str1[14] = ' ';
    str1[15] = '\0';

    // Manually set each LCD letter
    str2[0] = 'D';
    str2[1] = ':';
    str2[2] = getButton1(d) + '0';
    str2[3] = getButton2(d) + '0';
    str2[4] = ' ';
    str2[5] = 'E';
    str2[6] = ':';
    str2[7] = getButton1(e) + '0';
    str2[8] = getButton2(e) + '0';
    str2[9] = ' ';
    str2[10] = 'F';
    str2[11] = ':';
    str2[12] = getButton1(f) + '0';
    str2[13] = getButton2(f) + '0';
    str2[14] = ' ';
    str2[15] = '\0';

    // Write to the LCD
    setCursor(1, 0);
    print(str1);
    setCursor(1, 1);
    print(str2);

    // Free the memory
    free(str1);
    free(str2);
}