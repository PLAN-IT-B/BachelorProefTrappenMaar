//#include <Wire.h> //include Wire.h library
#include <Adafruit_PN532.h>
#include <LiquidCrystal_I2C.h>

#define reed 12

/*
void setup()
{
  Wire.begin(); // Wire communication begin
  Serial.begin(115200); // The baudrate of Serial monitor is set in 9600
  while (!Serial); // Waiting for Serial Monitor
  Serial.println("\nI2C address Scanner CircuitSchools.com");
}
 
void loop()
{
  byte error, address; //variable for error and I2C address
  int devicecount;
 
  Serial.println("Scanning...");
 
  devicecount = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      devicecount++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (devicecount == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000); // wait 5 seconds for the next I2C scan
}

*/

// #include < Wire .h> we are removing this because it is already added in liquid crystal library
 
// Create the lcd object address 0x3F and 16 columns x 2 rows 
LiquidCrystal_I2C lcd (0x27, 20,4);  //
byte block[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte line[] = {
  B00000,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001
};

byte one[] = {
  B00000,
  B00000,
  B00100,
  B00010,
  B11111,
  B00000,
  B00000,
  B00000
};

byte two[] = {
  B00000,
  B00000,
  B11101,
  B10101,
  B10111,
  B00000,
  B00000,
  B00000
};

byte three[] = {
  B00000,
  B00000,
  B10101,
  B10101,
  B11111,
  B00000,
  B00000,
  B00000
};

byte four[] = {
  B00000,
  B00000,
  B00111,
  B00100,
  B11111,
  B00000,
  B00000,
  B00000
};

byte emptyBlock[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

// general place holder (for use in functions)
unsigned long millisValue = 0;
// speed value
float Speed = 0 ;
// wheel size in CM
const int Wheel_circumference_in_Cm = 100 ;  // (2PiR).
// Magnatic reader params
const int MagneticReader_Pin = 12;
boolean MagneticReader_Last_state;
boolean MagneticReader_Current_state;
unsigned long MagneticReader_Last_state_Change = 0;
 
int MagneticReader_Last_state_isonMove_Millis_Gap = Wheel_circumference_in_Cm * 36 ; // the min for 1km/hour speed
// isonMove
boolean isonMove = false;
// total distance and time
unsigned long total_time_onMove = 0;
unsigned long total_cm_onMove = 0;
// for now leave this as indicator
const int ledPin =  13;      // the number of the LED pin
int tempcounter = 0;



//https://maxpromer.github.io/LCD-Character-Creator/

void  setup () {
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);                // Start serial monitor after a few seconds. Mainly for testing code to get it to work.
  lcd.begin(20,4);
  
  lcd.createChar(0, block);
  lcd.createChar(1, line);
  lcd.createChar(2, one);
  lcd.createChar(3, two);
  lcd.createChar(4, three);
  lcd.createChar(5, four);
  lcd.createChar(6, emptyBlock);


  //---- design ----//
  lcd.setCursor(4,3); lcd.write(1);
  lcd.setCursor(9,3); lcd.write(1);
  lcd.setCursor(14,3); lcd.write(1);

  lcd.setCursor(2,3); lcd.write(2);
  lcd.setCursor(7,3); lcd.write(3);
  lcd.setCursor(12,3); lcd.write(4);
  lcd.setCursor(17,3); lcd.write(5);

  //---- create custom characters ----//
  //lcd.setCursor(0, 0); lcd.write(0); 
  //lcd.setCursor(0,1); lcd.write(0); 
  //lcd.setCursor(0, 2); lcd.write(0); 

  //--- reedswitch ---//
  
  pinMode(ledPin, OUTPUT);
  pinMode(MagneticReader_Pin, INPUT_PULLUP);
 
  MagneticReader_Last_state = digitalRead(MagneticReader_Pin); 
}

void display(int r) {
  lcd.setCursor(15, 2);
  if (int(r) < 10) {
    lcd.print(" ");  // if less then 10 add " " space - to remove prev carcters
  }
  lcd.print(int(2*r));
    if( (2*r)==0) {
      lcd.setCursor(0,0); lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);
      lcd.setCursor(0,1); lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);
      lcd.setCursor(0,2); lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);
        }
    else if( (2*r) <=10) {
      lcd.setCursor(0,0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,1); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,2); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(5,0); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);
      lcd.setCursor(5,1); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);
      lcd.setCursor(5,2); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);


    }
    else if((10 < (2*r)) && ((2*r) <=20)){
      lcd.setCursor(0,0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,1); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,2); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(10,0); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); 
      lcd.setCursor(10,1); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); 
      lcd.setCursor(10,2); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); 

 }
    else if((20 < (2*r)) && ((2*r) <=30)){
      lcd.setCursor(0,0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,1); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,2); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(15,0); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);
      lcd.setCursor(15,1); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);
      lcd.setCursor(15,2); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);

}

    else if((2*r)> 30) {
      lcd.setCursor(0,0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,1); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,2); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      
}
  
}

void displayReset(){

}
 
void  loop () {
     MagneticReader_Current_state = !digitalRead(MagneticReader_Pin);
 
    // if the last read was longer then 3 sec ... probably stop - show speed 0 (zero)
    if (MagneticReader_Last_state_Change + MagneticReader_Last_state_isonMove_Millis_Gap < millis()) {
    // set speed to ZERO For display
    Speed = 0;
    // set on the move to false
    isonMove = false;
  } // end if past time
 // set indicator // TO BE REMOVED (THIS ONLY FOR VISUAL DEBUG - BLIN KEVERY TIME THE WHEEL CROSS)
  digitalWrite(ledPin, MagneticReader_Current_state);
 
  // if state changed
  if (MagneticReader_Current_state != MagneticReader_Last_state)  {
    // set the global var to use in all the functions to keep it on the same millis
    millisValue = millis();
 
    // only when we turn HIGH we do the calc of speed and setting of the last chnage miliis
    if (MagneticReader_Current_state)    {
      // now only if we already on the move
      if (isonMove) {
 
        // set the counter - will display for debugin TO BE REMOVED
        tempcounter += 1;
        Serial.println(tempcounter);
 
        // calc speed
        Speed =  float(Wheel_circumference_in_Cm) / float((millisValue - MagneticReader_Last_state_Change) / 36) ;
 
        // Calculate totals :
        total_time_onMove += millisValue - MagneticReader_Last_state_Change;
        total_cm_onMove += Wheel_circumference_in_Cm;
 
        // if not is on move -
      } else {
        // flip satet
        isonMove = true;
      } // end  (isonMove)
 
      // set the time
      MagneticReader_Last_state_Change = millisValue;
    } // end if (MagneticReader_Current_state)
 
    // set the current to last - so this loop will not happen again untill it chnages again.
    MagneticReader_Last_state = MagneticReader_Current_state;
  } // end if state changed
 
  // print speed - if speed less then 10 print it align to right
  /*lcd.setCursor(15, 1);
  if (int(Speed) < 10) {
    lcd.print(" ");  // if less then 10 add " " space - to remove prev carcters
  }
  lcd.print(int(Speed));*/
  display(int(Speed));
 // delay(2000);


 
  /*// print total distance
  lcd.setCursor(11, 0);
  if (int(total_cm_onMove / 100000) < 10) {
    lcd.print(" ");  // if less then 10 add " " space  so when its over 10 it will not move in "space"
  }
  lcd.print(float(float(total_cm_onMove) / 100000.00), 2);
 
  //calc and print time in MM:SS
  int minutes_for_diplay = int(total_time_onMove / 60000);
  int sec_for_display = int((total_time_onMove - minutes_for_diplay * 60000) / 1000);
 
  // print total time
  lcd.setCursor(7, 1);
  if (minutes_for_diplay < 10) {
    lcd.print("0"); // if min less then 10 add 0 (zero)
  }
  lcd.print(minutes_for_diplay);
  lcd.print(":");
  if (sec_for_display < 10) {
    lcd.print("0"); // if sec less then 10 add 0 (zero)
  }
  lcd.print(sec_for_display);
 */
 
} // end loop
  
  