//Jason - KeyboardScreen.cpp
//THE KEYBOARDS ARE HERE

#include <graphics.h>
#include <KeyboardScreen.h>

const int MaxLength = 17;
int used = 0;
char *keys = "1234567890qwertyuiopasdfghjklzxcvbnm ";
char *nums = "1234567890";
char input[MaxLength + 1];
boolean flagged = false;
BackboneProgram *prog;

void setProgram(BackboneProgram *p) {
  prog = p;
}

void finish(int param) {
        //Serial.println("finished");
        if (used == 0) {
                flagged = false;
        } else {
                flagged = true;
        }
        prog->popState(0);
}

void add_char(int index) {
        if (used < MaxLength) {
                input[used] = keys[index];
               // //Serial.print("'");
               // //Serial.print(keys[index]);
               // //Serial.println("'");
                used++;
                drawText(input, 10, 20, WHITE, 3);
                delay(100);
        }
}

void add_num(int index) {
        ////Serial.println(index);
        ////Serial.println((char)(index + 48));
        if (used < MaxLength) {
                //Serial.println(used);
                input[used] = (char)(index + 48);
                //Serial.println(input);
                used++;
                drawText(input, 10, 20, WHITE, 3);
                delay(100);
        }
}

void del_char(int index) {
        Serial.println("DELETE");
        if (used != 0) {
                drawText(input, 10, 20, BLACK, 3);
                used--;
                input[used] = '\0';
                drawText(input ,10, 20, WHITE, 3);
                input[used] = '\0';
                delay(100);
        }
}

void KeyboardInit() {
        used = 0;
        flagged = false;

}

void alphaDraw() {


        for (int i = 0; i < used; i++) {
          input[i] = ' ';
        }
        used = 0;
        input[MaxLength] = '\0';
        //input[MaxLength] = '\0';
        int keyWidth = 26;
        int keyHeight = 26;
        int init_x = 5;
        int last_x = init_x;
        int init_y = 81;
        int last_y = init_y;
        int iter;
        int n;
        int i = 0;
        char *c = "a";

        fillScreen(BLACK);

        for (i = 0; i < 10; i++) {
                c[0] = keys[i];
                n = add_button(last_x, last_y, keyWidth, keyHeight, 0, i, 2, c, BLACK, WHITE, add_char);
                draw_button(n);
                last_x = last_x + 5 + keyWidth;

        }
        last_x = init_x;
        last_y = last_y + keyHeight + 5;
        for (i; i < 20; i++) {
                c[0] = keys[i];
                n = add_button(last_x, last_y, keyWidth, keyHeight, 0, i, 2, c, BLACK, WHITE, add_char);
                draw_button(n);
                last_x = last_x + 5 + keyWidth;
        }

        last_x = init_x + (31/2);
        last_y = last_y + keyHeight + 5;
        for (i; i < 29; i++) {
                c[0] = keys[i];
                n = add_button(last_x, last_y, keyWidth, keyHeight, 0, i, 2, c, BLACK, WHITE, add_char);
                draw_button(n);
                last_x = last_x + 5 + keyWidth;
        }

        last_x = init_x + (46);
        last_y = last_y + keyHeight + 5;
        n = add_button(init_x, last_y + 31, (last_x + 26) - init_x, keyHeight, 0, 0, 2, "DEL", BLACK, WHITE, del_char);
        draw_button(n);

        for (i; i < 36; i++) {
                c[0] = keys[i];
                n = add_button(last_x, last_y, keyWidth, keyHeight, 0, i, 2, c, BLACK, WHITE, add_char);
                draw_button(n);
                last_x = last_x + 5 + keyWidth;
        }

        n = add_button((160 - (3 * 26)/2),  last_y + keyHeight + 5, keyWidth * 3, keyHeight , 0, i, 2, "Space", BLACK, WHITE, add_char);
        ////Serial.println(i);
        draw_button(n);
        n = add_button(320 - keyWidth - 5, 240 - keyHeight - 5, keyHeight, keyWidth, 0, 0 , 2, "OK", BLACK, GREEN, finish);
        draw_button(n);




}


void numDraw() {

        for (int i = 0; i < used; i++) {
	  input[i] = ' ';
	}
	used = 0;
        input[MaxLength] = '\0';

        //input[MaxLength] = '\0';
        int keyWidth = 38;
        int keyHeight = 38;
        int init_x =99;
        int last_x = init_x;
        int last_y = 68;
        int iter;
        int n;
        char *c = "a";

        fillScreen(BLACK);
        ////Serial.println("Filled");

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                        iter = j + (i * 3);
                        c[0] = nums[iter];

                        ////Serial.print("C is: ");
                        //Serial.println(c);
                        n = add_button(last_x + 5, last_y , keyHeight, keyWidth, 0, iter + 1, 3, c, BLACK, WHITE, add_num);
                        last_x = last_x + 10 + keyWidth;
                        ////Serial.println("Added");
                        //Serial.println(iter);
                        //Serial.println(n);
                        draw_button(n);

                }
                last_x = init_x;
                last_y = last_y + keyHeight + 5;

        }
        n = add_button(init_x + 53, last_y, keyHeight, keyWidth, 0, 0, 3, "0", BLACK, WHITE, add_num);
        draw_button(n);
        n = add_button(init_x + 5, last_y, keyWidth, keyHeight, 0, 0, 2, "DEL", BLACK, WHITE, del_char);
        draw_button(n);
        n = add_button(320 - keyWidth - 5, 240 - keyHeight - 5, keyHeight, keyWidth, 0, 0 , 2, "OK", BLACK, GREEN, finish);
        draw_button(n);

        //draw_all_buttons();
        ////Serial.println("Buttons Drawn");

}

void KeyboardRun(int delta) {
        (void) delta;
        check_touch();
        delay(250);


}

boolean check_flag() {
        return flagged;
}

char *get_val() {
        flagged = false;
        return input;
}

BackboneScreen *getKeyboard(int type, BackboneProgram *source){
        prog = source;
        if (type == 0){
                BackboneScreen *KeyboardScreen = new BackboneScreen( KeyboardInit, alphaDraw, KeyboardRun);
        } else if (type == 1) {
                BackboneScreen *KeyboardScreen = new BackboneScreen( KeyboardInit,  numDraw, KeyboardRun);
        }
}
