// 1- Miran Member
// 2- Communication
// 3- Description - Using the the serial monitor show the user input and the time from the said input on the lcd screen on the arduino.
// 5- References - https://www.arduino.cc/en/Tutorial/LiquidCrystalScroll
#include <LiquidCrystal.h>
#include <TimeLib.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
bool pass = false;

String incomingString;

//set serial and lcd
void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  Serial.println("Please Input(date & time) Format = 'mm/dd/yyyy hh/mm/ss' : ");
}



void loop() {
  //if serial is availave from the serial monitor then read the input in the string format
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingString = Serial.readString();

    // the length can only be 20 if its less then wrong format and wiseversa.
    if (incomingString.length() != 20) {
      Serial.println("Wrong Format, Please Input(date & time) Format = 'mm/dd/yyyy hh/mm/ss' : ");
      return;
    } else if (incomingString[2] != '/' || incomingString[5] != '/' || incomingString[13] != '/' || incomingString[16] != '/') {
      Serial.println("Wrong Format, Please Input(date & time) Format = 'mm/dd/yyyy hh/mm/ss' : ");
      return;
    }

    //convert all the input to month all the way to seconds.
    int month = (int(incomingString[0] - 48) * 10) + int(incomingString[1] - 48);
    int day = (int(incomingString[3] - 48) * 10) + int(incomingString[4] - 48);
    int year = (int(incomingString[6] - 48) * 1000) + (int(incomingString[7] - 48) * 100) + (int(incomingString[8] - 48) * 10) + (int(incomingString[9] - 48));

    int hour = (int(incomingString[11] - 48) * 10) + int(incomingString[12] - 48);
    int minute = (int(incomingString[14] - 48) * 10) + int(incomingString[15] - 48);
    int second = (int(incomingString[17] - 48) * 10) + int(incomingString[18] - 48);

    if (month <= 0 || month >= 13) {
      Serial.println("Month Incorrect, Please Input(date & time) Format = 'mm/dd/yyyy hh/mm/ss' : ");
      return;
    }
    //day checking is the worst because there are some months with 31 or 30 days so using a switch satement create error checker
    if (day <= 0 || day >= 32) {
      Serial.println("Day Incorrect, Please Input(date & time) Format = 'mm/dd/yyyy hh/mm/ss' : ");
      return;
    } else {
      if (day == 31) {
        switch (month) {
          case 1:
            break;
          case 3:
            break;
          case 5:
            break;
          case 7:
            break;
          case 8:
            break;
          case 10:
            break;
          case 12:
            break;
          default:
            Serial.println("Day Not Month, Please Input(date & time) Format = 'mm/dd/yyyy hh/mm/ss' : ");
            return;
            break;   
        }
      }
      if (day == 30) {
        switch (month) {
          case 4:
            break;
          case 6:
            break;
          case 9:
            break;
          case 11:
            break;
          default:
            Serial.println("Day Not Month, Please Input(date & time) Format = 'mm/dd/yyyy hh/mm/ss' : ");
            return;
            break;   
        }
      }
      if (month == 2) {
        if (day <= 0 || day >= 29) {
          Serial.println("Day Incorrect, Please Input(date & time) Format = 'mm/dd/yyyy hh/mm/ss' : ");
          return;
        }
        if (day == 29) {
          // checks weather its a leap year or not and if it is leap year and the date is 29 then all OK otherwise ask again for input.
          if (year % 400 == 0) {
          } else if (year % 100 == 0) {
            Serial.println("Not Leap Year, Please Input(date & time) Format = 'mm/dd/yyyy hh/mm/ss' : ");
            return;
          } else if (year % 4 == 0) {
          } else {
            Serial.println("Not Leap Year, Please Input(date & time) Format = 'mm/dd/yyyy hh/mm/ss' : ");
            return;
          }
        }
      }
      
    }
    if (hour < 0 || hour > 23) {
      Serial.println("Hour Incorrect, Please Input(date & time) Format = 'mm/dd/yyyy hh/mm/ss' : ");
    }
    if (minute < 0 || minute > 59) {
      Serial.println("Minute Incorrect, Please Input(date & time) Format = 'mm/dd/yyyy hh/mm/ss' : ");
    }
    if (second < 0 || second > 59) {
      Serial.println("Second Incorrect, Please Input(date & time) Format = 'mm/dd/yyyy hh/mm/ss' : ");
    }
    //set time using all the user input
    setTime(hour,minute,second,day,month,year);
    // since we are inside a loop we need a pass that only works when the user input is correct.
    pass = true;
    lcd.setCursor(0, 0);
    lcd.print(digitalClockDisplay());
    lcd.print(digitalDate());
    lcd.setCursor(0,1);
    lcd.print(digitalYear());
  }

  if (pass) {
    // continue to get the time and update it on the screen.
    lcd.setCursor(8, 1);
    Serial.println(digitalClockDisplay());
    lcd.print(digitalClockDisplay());
    delay(1000);
  }
}

String digitalDate() {
  String ret = " " + String(month()) + "/" +  String(day()) + "/";
  return ret;
}

String digitalYear() {
  return String(year());
}

String digitalClockDisplay() {
 String ret = hour() + printDigits(minute()) + printDigits(second());
 return ret;
}

String printDigits(int digits) {
 String ret = ":";
 if (digits < 10) {
  ret += "0";
 }
 ret += digits;
 return ret;
}
