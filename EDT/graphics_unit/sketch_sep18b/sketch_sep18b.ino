

void setup() {
  // put your setup code here, to run once:
pinMode(3, OUTPUT); 
pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x=0;
  int potentiometer=analogRead(A0);
  while(x<=55){
   x=x+1;
  analogWrite(3, 5*x);
  delay(potentiometer);
  if (potentiometer>500);
    potentiometer=500;
  if (potentiometer<50);
    potentiometer=50;

  }
}
