//#include <TaskScheduler.h>
//#include <TaskSchedulerDeclarations.h>
#include <Memory.h>
#include <vector>
#include <graphics.h>
#include <stdio.h>

#define TFT_CS D2
#define TFT_DC D1
#define CS_PIN D4

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
XPT2046_Touchscreen ts(CS_PIN);

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

bool touchDown = false;

void graphics_begin() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  ts.begin();
  ts.setRotation(3);
}

int add_button(int x, int y, int width, int height, int radius, int parameter, int text_size, char *text, uint16_t text_color, uint16_t background_color, void (*func)(int)) {
  button *new_button =(button *) malloc(sizeof(button));
  new_button->x = x;
  new_button->y = y;
  new_button->height = height;
  new_button->width = width;
  new_button->text = text;
  new_button->radius = radius;
  new_button->text_size = text_size;
  new_button->text_color = text_color;
  new_button->background_color = background_color;
  new_button->parameter = parameter;
  new_button->func = func;
  Serial.println(new_button->x);
  Serial.println(new_button->y);
  button_vector.push_back(new_button);
  return button_vector.size() - 1;
}

void check_press(int x, int y) {
  if (touchDown == false){
    for (int i = 0; i < button_vector.size(); ++i) {
      if ((x > button_vector[i]->x and x < (button_vector[i]->x + button_vector[i]->width)) and (y > button_vector[i]->y and y < (button_vector[i]->y + button_vector[i]->height))) {
        button_vector[i]->func(button_vector[i]->parameter);
        touchDown = true;
        break;
      }
      yield();
    }
  }
}

void button_delete(int index) {
;
  free(button_vector[index]);
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

void drawRectWithBorder(int16_t x, int16_t y, int16_t w, int16_t h,
			uint16_t c_fill, uint16_t c_border) {
  fillRect(x, y, w, h, c_fill);
  drawRect(x, y, w, h, c_border);
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
  for (int i = button_vector.size() - 1; i >= 0; i--) {
    button_delete(i);
    button_vector.pop_back();
  }
}

void draw_button(int index) {
  button *temp = button_vector[index];

  fillRect(temp->x, temp->y, temp->width, temp->height, /*temp->radius,*/ temp->background_color);
  drawText(temp->text, temp->x + 5, temp->y + (temp->height / 2) - (temp->text_size * 2), temp->text_color, temp->text_size);
  yield();
}

void draw_all_buttons() {
        for (int i = 0; i < button_vector.size(); i++) {
                draw_button(i);
        }
        yield();
}

TS_Point check_touch() {
        TS_Point point = ts.getPoint();
        if (ts.touched() && point.z > 1100) {
                int x = ((float)(point.x - 250) / (float)(3720 - 250)) * 320;
                int y = ((float)(point.y - 250) / (float)(3880 - 250)) * 240;
                check_press(x, y);
                point.x = x;
                point.y = y;
                return point;
        } else {
                touchDown = false;
                point.x = -1;
                point.y = -1;
                return point;
        }
}
