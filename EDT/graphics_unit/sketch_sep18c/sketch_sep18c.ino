void setup() {
  // put your setup code here, to run once:
pinMode(A0, INPUT);
pinMode(3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int potentiometer=analogRead(A0);
analogWrite(3, potentiometer);
}
