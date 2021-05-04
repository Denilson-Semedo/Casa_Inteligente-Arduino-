#include <Servo.h>
#include <MFRC522.h>
Servo servo;
Servo servo1;
float temperatura;

#define LDR A1
int valorLido = 0;

#define pino_SDA 53
#define pino_RST 49
int luzruaBT=0;

MFRC522 mfrc522(pino_SDA, pino_RST);

int pinopir = 17;
int acionamento;
int garagem=0;

void setup() {
  
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Aproxime o teu cartão do leitor...");
  Serial.println();
  pinMode(LDR,INPUT);
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
  pinMode(pinopir, INPUT);
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

void Temperatura(){
  temperatura = (float(analogRead(A0))*5/(1023))/0.01;
  Serial.println(temperatura);
  
  if(temperatura > 36){
    digitalWrite(13,HIGH);
  }

  if(digitalRead(7)==HIGH){
    tone(14,1000);  
    noTone(14);
  }
}

void Proximidade(){
  acionamento = digitalRead(pinopir);
 
  if(acionamento == HIGH) {
    if(garagem == 0){
      garaopen();
      garagem=1;
    }
  }  
}


void RFID(){
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.print("ID DA TAG: ");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  
  if (conteudo.substring(1) == "40 28 B3 39") {
    portaopen(); 
    delay(5000);
    portaclose();
  } else if (conteudo.substring(1) == "29 24 76 E7") {
    portaopen(); 
    delay(5000);
    portaclose();
  } else {
    Serial.println("Acesso Negado"); 
  }
}


void loop() {

  valorLido = analogRead(LDR);
  if(luzruaBT == 0){
    if(valorLido<50){
    digitalWrite(9,HIGH);
  }else{
     digitalWrite(9,LOW);
  }
 
  /*Serial.print(" O valor lido = ");
  Serial.print(valorLido);*/
  }
  
  
  Proximidade();

  noTone(14);
  
  Temperatura();
  
    char c;
    c = (Serial.read());
    
    if(c == 'A'){
      digitalWrite(9,HIGH);  
      luzruaBT=1;
    }
         
    if(c == 'B'){
       digitalWrite(9,LOW);
       luzruaBT=0;
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
      garagem=0;
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

       RFID();
}
