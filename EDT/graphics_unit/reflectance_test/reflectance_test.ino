const int Lreflectance = 2;
const int Rreflectance = 3;
void setup() {
  // put your setup code here, to run once:
pinMode(Lreflectance, INPUT);
pinMode(Rreflectance, INPUT);
Serial.begin(9600);
}

void loop() {
  int Lvalue;
  int Rvalue;
  Lvalue = analogRead(Lreflectance);
  Rvalue = analogRead(Rreflectance);
  Serial.print(Lvalue);
  Serial.print("       ");
  Serial.println(Rvalue);
  
  delay(500);
  // put your main code here, to run repeatedly:

}
