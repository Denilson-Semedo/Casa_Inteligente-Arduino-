#include <Servo.h>
Servo servo;
Servo servo1;
float temperatura;

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(7,INPUT);
  pinMode(8,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW); 
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);

  servo.attach(15);
  servo.write(0);
  servo1.attach(12);
  servo1.write(0);
  Serial.begin(9600);
}
int x=0;
int y=0;
void portaopen(){
    int i;
    for(i=0;i<90;i++){
    servo.write(i);
    delay(10);
    } 
    x=1;
}
void portaclose(){
    int i;
    for(i=90;i>0;i--){
    servo.write(i);
    delay(10);
    } 
    x=0;
}
void garaopen(){
    int i;
    for(i=0;i<90;i++){
    servo1.write(i);
    delay(10);
    } 
    y=1;
}
void garaclose(){
    int i;
    for(i=90;i>0;i--){
    servo1.write(i);
    delay(10);
    } 
    y=0;
}

void loop() {
  noTone(14);
  temperatura = (float(analogRead(A0))*5/(1023))/0.01;
  Serial.println(temperatura);
  if(temperatura > 36){
    digitalWrite(13,HIGH);
  }

  if(digitalRead(7)==HIGH){
    tone(14,1000);  
    noTone(14);
  }
  
    char c;
    c = (Serial.read());
    
    if(c == 'A'){
      digitalWrite(9,HIGH);  
    } 
    if(c == 'B'){
       digitalWrite(9,LOW);
    }
    if(c == 'C' && x==0){
      portaopen(); 
    }
    if(c == 'D' && x==1){
      portaclose();
    }
    if(c == 'Z' && y==0){
      garaopen(); 
    }
    if(c == 'Y' && y==1){
      garaclose();
    }
    if(c == 'W'){
      digitalWrite(16,HIGH);
    }
    if(c == 'T'){
      digitalWrite(16,LOW);
    }
    if(c == 'E'){
       digitalWrite(13,HIGH);
    }
    if(c == 'F'){
       digitalWrite(13,LOW);
    }
    if(c == 'G'){
       digitalWrite(6,HIGH);
    }
    if(c == 'H'){
       digitalWrite(6,LOW);
    }
    if(c == 'I'){
      digitalWrite(2,HIGH); 
    }
    if(c == 'J'){
       digitalWrite(2,LOW);
    }
    if(c == 'K'){
      digitalWrite(3,HIGH); 
    }
    if(c == 'L'){
       digitalWrite(3,LOW);
    }
    if(c == 'M'){
       digitalWrite(8,HIGH);
    }
    if(c == 'N'){
       digitalWrite(8,LOW);
    }
    if(c == 'O'){
      digitalWrite(4,HIGH);
    }
    if(c == 'P'){
       digitalWrite(4,LOW);
    }
    if(c == 'R'){
      digitalWrite(5,HIGH);
    }
    if(c == 'S'){
       digitalWrite(5,LOW);
    }
    if(c == 'Q'){
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(8,LOW);
      digitalWrite(6,LOW);
      digitalWrite(9,LOW);
    }
}
