//Jason - KeyboardScreen.cpp

#include <graphics.h>
#include <BackboneScreen.h>

const int MaxLength = 20;
char *keys = "1234567890qwertyuiopasdfghjkl;zxcvbnm,./ ";
char *nums = "1234567890";

void add_num(int index) {
        Serial.println(index);
}

void KeyboardInit() {

}

void alphaDraw() {

}

void numDraw() {
        int keyWidth = 43;
        int keyHeight = 43;
        int init_x =84;
        int last_x = init_x;
        int last_y = 48;
        int iter;
        int n;
        char *c = "a";

        fillScreen(BLACK);
        Serial.println("Filled");

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                        iter = j + (i * 3);
                        c[0] = nums[iter];

                        Serial.print("C is: ");
                        Serial.println(c);
                        n = add_button(last_x + 5, last_y , keyHeight, keyWidth, 0, iter, 10, c, BLACK, WHITE, add_num);
                        last_x = last_x + 10 + keyWidth;
                        Serial.println("Added");
                        Serial.println(iter);
                        Serial.println(n);
                        draw_button(n);

                }
                last_x = init_x;
                last_y = last_y + keyHeight + 5;

        }
        n = add_button(init_x + 58, last_y, keyHeight, keyWidth, 0, 0, 10, "0", BLACK, WHITE, add_num);
        draw_button(n);

        //draw_all_buttons();
        Serial.println("Buttons Drawn");

}

void KeyboardRun(int delta) {

}

BackboneScreen *getKeyboard(int type){
        if (type == 0){
                BackboneScreen *KeyboardScreen = new BackboneScreen( KeyboardInit, alphaDraw, KeyboardRun);
        } else if (type == 1) {
                BackboneScreen *KeyboardScreen = new BackboneScreen( KeyboardInit,  numDraw, KeyboardRun);
        }
}