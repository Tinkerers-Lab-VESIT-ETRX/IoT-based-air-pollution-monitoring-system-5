#include <LiquidCrystal.h>      //Header file for LCD
const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2; //pins of LCD connected to Arduino
LiquidCrystal lcd(rs,en,d4,d5,d6,d7); //lcd function from LiquidCrystal
int buz = 8;  //buzzer connected to pin 8
int led = 9;  //led connected to pin 9
const int aqsensor = A0;  //output of mq135 connected to A0 pin of Arduino
int threshold = 250;      //Threshold level for Air Quality

void setup() {

  pinMode (buz,OUTPUT);     // buzzer is connected as Output from Arduino
  pinMode (led,OUTPUT);     // led is connected as output from Arduino
  pinMode (aqsensor,INPUT); // MQ135 is connected as INPUT to arduino
  Serial.begin (9600);      //begin serial communication with baud rate of 9600

  lcd.clear();              // clear lcd
  lcd.begin (16,2);         // consider 16,2 lcd
}

void loop() {

  int ppm = analogRead(aqsensor); //read MQ135 analog outputs at A0 and store it in ppm

  Serial.print("Air Quality: ");  //print message in serail monitor
  Serial.println(ppm);            //print value of ppm in serial monitor

  lcd.setCursor(0,0);             // set cursor of lcd to 1st row and 1st column
  lcd.print("Air Qualit: ");      // print message on lcd
  lcd.print(ppm);                 // print value of MQ135

  if (ppm < 51)            // check is ppm is greater than threshold or not
    {
      digitalWrite(led,LOW);   
      digitalWrite(buz,LOW);
      lcd.setCursor(1,1);         //jump here if ppm is greater than threshold
      lcd.print("AQ Level HIGH");
      //Serial.println("AQ Level IS GOOD");     
      tone(led,1000,200);         //blink led with turn on time 1000mS, turn off time 200mS                   //digitalWrite(buz,HIGH);
    }
  else if (50 < ppm < 101)
  {
     digitalWrite(led,LOW);   
      digitalWrite(buz,LOW);
      lcd.setCursor(1,1);         //jump here if ppm is greater than threshold
      lcd.print("AQ Level MODERATE");
      //Serial.println("AQ Level IS MODERATE");     
      tone(led,1000,200);
  }
  else if (100 < ppm < 201)
  {   
      digitalWrite(led,HIGH);
      digitalWrite(buz,LOW);
      lcd.setCursor(1,1);         //jump here if ppm is greater than threshold
      lcd.print("AQ Level UNHEALTHY ");
      //Serial.println("AQ Level IS UNHEALTHY");     
      tone(led,1000,200);
  }
  else if (200 < ppm < 301)
  {
      digitalWrite(led,HIGH);
      digitalWrite(buz,HIGH);
      lcd.setCursor(1,1);         //jump here if ppm is greater than threshold
      lcd.print("AQ Level is very UNHEALTHY ");
      //Serial.println("AQ Level IS VERY UNHEALTHY");     
      tone(led,1000,200);
  }
  else
    {
      lcd.setCursor(1,1);
      lcd.print ("AQ Level is DANGER ");
      //Serial.println("AQ Level DANGER");
      digitalWrite(led,HIGH);
      digitalWrite(buz,HIGH);
    }  
  delay (500);
}
