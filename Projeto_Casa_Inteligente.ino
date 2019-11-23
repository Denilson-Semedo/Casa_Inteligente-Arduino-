#include <Servo.h>
Servo servo;
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;

char op;
char opcao;
float temperatura;

void setup()
{
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);
  pinMode(13, OUTPUT);
  servo.attach(8);
  servo.write(0);
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600);
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

void ledrgb(){
  RGB_color(255, 0, 0); 
  delay(80);
  RGB_color(0, 255, 0); 
  delay(80);
  RGB_color(0, 0, 255);
  delay(80);
  RGB_color(255, 255, 125); 
  delay(80);
  RGB_color(0, 255, 255);
  delay(80);
  RGB_color(255, 0, 255);
  delay(80);
  RGB_color(255, 255, 0);
  delay(80);
  RGB_color(255, 255, 255);
  delay(80);
}


void porta(){
    // put your main code here, to run repeatedly:
    int i;
    for(i=0;i<90;i++){
      servo.write(i);
      delay(10);
    }
  
    delay(6000);
    
    for(i=90;i>0;i--){
      servo.write(i);
      delay(10);
    }
     delay(6000);
}

void LuzDaCasa(){
  Serial.println("1->quarto 1");
  Serial.println("2->quarto 2");
  Serial.println("3->quarto 3");
  Serial.println("4->quarto 4");
  Serial.println("5->Apagar todas luzes");

  int op;
  
  op = (Serial.read());

  switch(op)
  {
    case '1':
      digitalWrite(2,HIGH);    
      break;
    case '2':
      digitalWrite(3,HIGH);
      break;
    case '3':
      digitalWrite(4,HIGH);
      break;
    case '4':
      digitalWrite(5,HIGH);
      break;
    case '5':
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      break;
    default:
      break;
  }
}

void loop()
{
  temperatura = (float(analogRead(A0))*5/(1023))/0.01;
  if(temperatura > 40){
    digitalWrite(10,HIGH);
  }
  if (Serial.available())

  {
    op = (Serial.read());

    switch(op){
        Serial.println("switch1");
        case '1':
         //AC();
         digitalWrite(13, HIGH);
         Serial.println("\t\t\t\t\t\t\t\tCASA INTELIGENTE");
         Serial.println("1->Ligar AC;");
         Serial.println("2->Acender a luz;");
         Serial.println("3->Acender a luz da piscina;");
         Serial.println("4->Abrir a porta principal;");
         Serial.println("5->Abrir a porta da garagem;");
        
         opcao = (Serial.read());

         switch(opcao){
              Serial.println("switch2");
              case '1':
               LuzDaCasa();
               Serial.println(opcao);
               break;
              case '2':
               //LuzDaCasa();
               digitalWrite(13, LOW);
               Serial.println(opcao);
               break;
              case '3':
               ledrgb();
               break;
              case '4':
               porta();
               Serial.println(opcao);
               break;
              case '5':
               //Garagem();
               break;
              default:
                break;
              }         
             
             break;
            default:
              break;
      }
  }
}
