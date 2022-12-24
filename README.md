# Arduino-Time
This Arduino project allows the user to set the time on an Arduino board using the serial monitor. The time is then displayed on a 16x2 LCD screen.

### Hardware
+ Arduino board
+ 16x2 LCD screen
+ TimeLib library

### Setup
1. Connect the LCD screen to the Arduino board according to the pinout listed in the code.
2. Install the TimeLib library in the Arduino IDE.
3. Upload the code to the Arduino board.

### Usage
1. Open the serial monitor in the Arduino IDE.
2. Enter the time in the following format: mm/dd/yyyy hh/mm/ss
3. Press send to set the time on the Arduino board. The time will be displayed on the LCD screen.
4. If the input is in the wrong format, an error message will be displayed in the serial monitor.

### Code
The code reads input from the serial monitor and converts it to the appropriate variables for month, day, year, hour, minute, and second. Error checking is performed to ensure that the input is in the correct format and that the values for month and day are valid. The time is then set using the setTime function from the TimeLib library and displayed on the LCD screen. The time is updated every second.



