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

int reedVal;


//https://maxpromer.github.io/LCD-Character-Creator/

void  setup () {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, block);
  lcd.createChar(1, line);
  lcd.createChar(2, one);
  lcd.createChar(3, two);
  lcd.createChar(4, three);
  lcd.createChar(5, four);


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
  Serial.begin(115200);                // Start serial monitor after a few seconds. Mainly for testing code to get it to work.

  
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

 
void  loop () {
    reedVal = analogRead(reed);//get val of 12
    Serial.println(reedVal);
    display(reedVal);
    }