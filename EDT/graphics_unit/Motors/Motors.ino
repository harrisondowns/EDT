const int A_ENBL = 3;
const int A_PHASE = 2;
const int B_ENBL = 5;
const int B_PHASE = 4;

void setup() {
  pinMode(A_PHASE, OUTPUT);
  pinMode(B_PHASE, OUTPUT);
  pinMode(A_ENBL, OUTPUT);
  pinMode(B_ENBL, OUTPUT);
  digitalWrite(A_PHASE, LOW);
  digitalWrite(B_PHASE, LOW);
  analogWrite(A_ENBL, 255);
  analogWrite(B_ENBL, 255);
  delay(2000);
  analog3Write(A_ENBL, 0);
  analogWrite(B_ENBL, 0);
  
}
void loop() {
  // put your main code here, to run repeatedly:

}
