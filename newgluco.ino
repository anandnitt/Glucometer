#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
      lcd.print("GLUCOMETER");
      
    pinMode(7,OUTPUT)  ;
    
Serial.begin(9600);
}

void loop() {
  static double glucose=0,adcv=0,glevel=0,flag=0,avg=0,avgt=0,disp=0,adcv1=0,insulin=0;
  // put your main code here, to run repeatedly:
pinMode(9,OUTPUT);
tone(9,55000);
analogWrite(10,127);
adcv=analogRead(A0);
adcv1=analogRead(A1);

glucose=abs((adcv-adcv1))*5/1024;


//Serial.println(flag);
flag++;

if(flag>=500)
{
  avg+=glucose;
  
  if(flag==1000)
  {
    avg=avg/500;
    avgt+=avg;
    disp++;
    lcd.setCursor(0,0);
      lcd.print("Calc. glucose level");
      lcd.setCursor(0,1);
      lcd.print("Please Wait");
      for(int i=0;i<disp;i++)
      lcd.print(".");
    if(disp==5)
    {avgt=avgt/5;
    lcd.clear();
      lcd.setCursor(0,0);
     
      if(avgt<0.5)
      lcd.print("Please keep finger");
      else
      { lcd.setCursor(0,0);
       lcd.print("Normal: 70-140 mg/dl");
        lcd.print("Your level is :");
      lcd.setCursor(0,1);
       avgt=-0.041*avgt*avgt - 0.617*avgt + 5.648;
     lcd.print(avgt*18.04);
     //Serial.println(avgt);
       
     lcd.print(" mg/dl");
     if(avgt*18.04>150)
     {
      insulin=(avgt*18.04-140)/50.0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Insulin dosage:");
      lcd.setCursor(0,1);
      lcd.print(insulin);
      lcd.print(" units");
      delay(2000);
      digitalWrite(7,HIGH);
       delay(2000);
       digitalWrite(7,LOW);
      insulin=0;
      }
     
     }
      avgt=0;
      disp=0;
      delay(2000);
      }
    
    avg=0;
    flag=0;
    }
  }

glucose=0;
glevel=0;

}

