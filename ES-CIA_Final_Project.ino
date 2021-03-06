#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);


int ch = 4;
int IRSensor = 2; 
int relay[] = {13, 12, 11};
const int buzzer = 10;
int person_state =0;
char  cabinet_number = 0;

void setup()
{
pinMode(buzzer, OUTPUT);
pinMode (IRSensor, INPUT);
for(int i=0; i<ch; i++)
{
pinMode(relay[i], OUTPUT);
}
lcd.init();                 //Init the LCD
lcd.backlight();            //Activate backlight     
lcd.home();  
Serial.begin(9600);
for(int i=0; i<ch; i++){
digitalWrite(relay[i], LOW);
} 
digitalWrite(IRSensor, LOW);
}
void loop()
{
 if (Serial.available() > 0)
{
cabinet_number = Serial.read();
}
 while(cabinet_number > 0)
{
 sense_person();  
 }
for(int i=0; i<ch; i++){
digitalWrite(relay[i], HIGH);
}
person_state = 0;
}
void sense_person()
{
int status_IR = digitalRead (IRSensor);
if (status_IR == 0)
{
delay(50);
switch(cabinet_number)
{
case '1':
drawer_1();
break;
case '2':
drawer_2();
break;
case '3':
drawer_3();
break;
}
person_state = 1;
}
else if (status_IR == 1)
{
delay(1000);
if(person_state == 1)
{
cabinet_number =0;
}
else
{
tone(buzzer,200,200);
}
}
}
void reset_cabinet()
{
int status_IR = digitalRead (IRSensor);
 }

void drawer_1()
{
digitalWrite(relay[0], LOW);
lcd.setCursor(0,0);
lcd.print("Medicine box 1");
}
void drawer_2()
{
digitalWrite(relay[1], LOW);  
lcd.setCursor(0,0);
lcd.print("Medicine box 2");
}

void drawer_3()
{
digitalWrite(relay[2], LOW);
lcd.setCursor(0,0);
lcd.print("Medicine box 3");
}
