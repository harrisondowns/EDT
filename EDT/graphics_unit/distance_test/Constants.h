#include <Servo.h>
#include <NewPing.h>


int orientations[] = {0,1,2,3}; // Up, Right, Down, Left
int orientation;
int initOrientation;
int wall_distance = 0;
int front_threshold = 0;
int turn_threshold = 0;
int tolerance = 0;
int servo_pin = 0;

int LEFT_IN2 = 9;
int LEFT_IN1 = 6;
int RIGHT_IN2 = 11;
int RIGHT_IN1 = 10;

int front_trigger = 43;
int front_echo = 42;
int back_trigger = 53;
int back_echo = 52;
int front_left_trigger = 47;
int front_left_echo = 46;
int back_left_trigger = 39;
int back_left_echo = 38;
int front_right_trigger = 45;
int front_right_echo = 44;
int back_right_trigger = 51;
int back_right_echo = 50;

NewPing front_sensor(front_trigger, front_echo);
NewPing back_sensor(back_trigger, back_echo);
NewPing front_right_sensor(front_right_trigger, front_right_echo);
NewPing front_left_sensor(front_left_trigger, front_left_echo);
NewPing back_right_sensor(back_right_trigger, back_right_echo);
NewPing back_left_sensor(back_left_trigger, back_left_echo);

Servo servo;
