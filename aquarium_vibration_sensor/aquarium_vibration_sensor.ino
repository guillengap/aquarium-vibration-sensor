// AUTHOR: GUILLERMO PEREZ GUILLEN

#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

// Wiring 12C LCD: SDA pin is connected to D14 and SCL pin to D15.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27,16,2) for 16x2 LCD.

int LED_Pin = D13; // LED diode
int vibr_Pin =D2; // Vout of the vibration sensor
int vibr_max = -100; 

void setup() {
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();
  pinMode(LED_Pin, OUTPUT);
  pinMode(vibr_Pin, INPUT); //set vibr_Pin input for measurment
  Serial.begin(9600); //init serial 9600  
}


void loop() {
  long measurement =TP_init();
  delay(50);
  Serial.println(measurement);

  // DETECTING VIBRATION MAXIMUM
  if (measurement > vibr_max){ 
    vibr_max = measurement;
  }

  // DETECTING VIBRATIONS ABOVE 1000 MICROSECONDS   
  if (measurement > 1000){ //
    digitalWrite(LED_Pin, HIGH);
  }
  else{
    digitalWrite(LED_Pin, LOW); 
  }
  
  // PRINTING VALUES
  lcd.setCursor(0, 0); // Set the cursor on the 1st column and 1st row.
  lcd.print("  VIBRATION SENSOR"); // Print the string "VIBRATION SENSOR"
  lcd.setCursor(0, 2); //Set the cursor on the 1st column and the 3rd row.
  lcd.print("Measurment = ");
  lcd.setCursor(13, 2); //Set the cursor on the 13th column and the 3rd row.
  lcd.print(measurement);  
  lcd.print("      ");
  lcd.setCursor(0, 3); //Set the cursor on the 1st column and the 4th row.
  lcd.print("Maximum = ");  
  lcd.setCursor(10, 3); //Set the cursor on the 10th column and the 4th row.
  lcd.print(vibr_max);    
  lcd.print("      ");  
}

// DETECTING MESUREMENTS
long TP_init(){
  delay(20);
  long measurement=pulseIn (vibr_Pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}
