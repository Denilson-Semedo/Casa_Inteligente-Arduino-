#include <Servo.h>
Servo servo;
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;

char op;
char opcao;

void setup()
{
  pinMode(13, OUTPUT);
  servo.attach(8);
  servo.write(0);
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
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

void loop()
{
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
           //LuzDaCasa();
           digitalWrite(13, HIGH);
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
