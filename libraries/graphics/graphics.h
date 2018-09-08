#ifndef graphics_h
#define graphics_h

#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "SPI.h"
#include <XPT2046_Touchscreen.h>


#define RED ILI9341_RED
#define CYAN ILI9341_CYAN
#define BLUE ILI9341_BLUE
#define GREEN ILI9341_GREEN
#define YELLOW ILI9341_YELLOW
#define BLACK ILI9341_BLACK
#define NAVY ILI9341_NAVY
#define DARKGREEN ILI9341_DARKGREEN
#define DARKCYAN ILI9341_DARKCYAN
#define MAROON ILI9341_MAROON
#define PURPLE ILI9341_PURPLE
#define OLIVE ILI9341_OLIVE
#define LIGHTGREY ILI9341_LIGHTGREY
#define DARKGREY ILI9341_DARKGREY
#define WHITE ILI9341_WHITE
#define ORANGE ILI9341_ORANGE
#define GREENYELLOW ILI9341_GREENYELLOW
#define PINK ILI9341_PINK
#define MAGENTA ILI9341_MAGENTA
#define TRANSPARENT 1



//Calls tft.begin to intialize the touchscreen object
void graphics_begin();

//Adds a button and returns the button number
int add_button(int, int, int, int, int, int, int, char *, uint16_t, uint16_t, void (*func)(int));

//Checks if a button has been pressed
void check_press(int, int);

//Deletes a single button and frees the memory
void button_delete(int);

//draw a button
void draw_button(int);

int16_t height();

int16_t width();
void drawText(char *text, int x, int y,
          uint16_t, uint8_t);

void drawLine(int x1, int y1, int x2, int y2,
          uint16_t );

void drawRect(int16_t x, int16_t y, int16_t w, int16_t h,
          uint16_t c);

void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
          uint16_t c);

void drawRectWithBorder(int16_t x, int16_t y, int16_t w, int16_t h,
			uint16_t c_fill, uint16_t c_border);

void fillScreen(uint16_t );

void drawCircle(int16_t x, int16_t y, uint8_t r,
        uint16_t );

void fillCircle(int16_t x, int16_t y, uint8_t r,
        uint16_t );

void drawTriangle(int16_t top_x, int16_t top_y, int16_t bottom_left_x, int16_t bottom_left_y, int16_t bottom_right_x, int16_t bottom_right_y,
          uint16_t);

void fillTriangle(int16_t top_x, int16_t top_y, int16_t bottom_left_x, int16_t bottom_left_y, int16_t bottom_right_x, int16_t bottom_right_y,
          uint16_t);

void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
           int16_t, uint16_t);

void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
           int16_t, uint16_t);

void clear_buttons();

//draws all the buttons
void draw_all_buttons();

TS_Point check_touch();

#endif
