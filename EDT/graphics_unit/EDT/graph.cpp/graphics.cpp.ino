#include <TaskScheduler.h>
#include <TaskSchedulerDeclarations.h>
#include <Memory.h>
#include <unwind-cxx.h>
#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <utility.h>
#include <vector>
#include "graphics.h"
#include <stdio.h>



Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

struct button {
  //Position of top left corner
  int x;
  int y;
  int width;
  int height;
  int parameter;
  int radius;
  int text_size;
  char *text;
  uint16_t text_color;
  uint16_t background_color;
  void (*func)(int);
  
};

using namespace std;

vector<button *> button_vector;


void graphics_begin(Adafruit_ILI9341 tft) {
  tft.begin();
  tft.setRotation(1);
}

int add_button(int x, int y, int height, int width, int radius, int parameter, int text_size, char *text, uint16_t text_color, uint16_t background_color, void (*func)(int)) {
  button *new_button =(button *) mallocNew(sizeof(button));
  new_button->x = x;
  new_button->y = y;
  new_button->height = height;
  new_button->width = width;
  new_button->text = text;
  new_button->radius = radius;
  new_button->text_color = text_color;
  new_button->background_color = background_color;
  new_button->parameter = parameter;
  new_button->func = func;
  button_vector.push_back(new_button);
  return button_vector.size();
}

void check_press(int x, int y) {
  for (int i = 0; i < button_vector.size(); i++) {
    if ((x > button_vector[i]->x and x < (button_vector[i]->x + button_vector[i]->width)) and (y > button_vector[i]->y and y < (button_vector[i]->y + button_vector[i]->height))) {
      button_vector[i]->func(button_vector[i]->parameter);
    }
    yield();
  }
}

void button_delete(int index) {
;
  freeVar(button_vector[index]);
}

int16_t height() {
  return tft.height();
}

int16_t width() {
  return tft.width();
}

void drawText(char *text, int x, int y,
          uint16_t c = BLACK, uint8_t size = 8) {
  tft.setCursor(x, y);
  tft.setTextColor(c);
  tft.setTextSize(size);
  tft.println(text);
}

void drawLine(int x1, int y1, int x2, int y2,
          uint16_t c = BLACK) {
  tft.drawLine(x1, y1, x2, y2, c);
}

void drawRect(int16_t x, int16_t y, int16_t w, int16_t h,
          uint16_t c = BLACK) {
  tft.drawRect(x, y, w, h, c);
}

void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
          uint16_t c = BLACK) {
  tft.fillRect(x, y, w, h, c);
}

void fillScreen(uint16_t c = BLACK) {
  tft.fillScreen(c);
}

void drawCircle(int16_t x, int16_t y, uint8_t r,
        uint16_t c = BLACK) {
  tft.drawCircle(x, y, r, c);
}

void fillCircle(int16_t x, int16_t y, uint8_t r,
        uint16_t c = BLACK) {
  tft.fillCircle(x, y, r, c);
}

void drawTriangle(int16_t top_x, int16_t top_y, int16_t bottom_left_x, int16_t bottom_left_y, int16_t bottom_right_x, int16_t bottom_right_y,
          uint16_t c = BLACK) {
  tft.drawTriangle(top_x, top_y, bottom_left_x, bottom_left_y, bottom_right_x, bottom_right_y, c);
}

void fillTriangle(int16_t top_x, int16_t top_y, int16_t bottom_left_x, int16_t bottom_left_y, int16_t bottom_right_x, int16_t bottom_right_y,
          uint16_t c = BLACK) {
            tft.fillTriangle(top_x, top_y, bottom_left_x, bottom_left_y, bottom_right_x, bottom_right_y, c);
}
          
void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
           int16_t r = 3, uint16_t c = BLACK) {
  tft.drawRoundRect(x, y, w, h, r, c);
}

void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
           int16_t r = 3, uint16_t c = BLACK) {
  tft.fillRoundRect(x, y, w, h, r, c);
}

void clear_buttons() {
  for (unsigned i = 0; i < button_vector.size(); i++) {
    button_delete(i);
  }
}

void draw_button(int index) {
  button *temp = button_vector[index];
  drawRoundRect(temp->x, temp->y, temp->width, temp->height, temp->radius, temp->background_color);
  drawText(temp->text, temp->x + 5, temp->y + 5, temp->text_color, temp->text_size);
  
}
