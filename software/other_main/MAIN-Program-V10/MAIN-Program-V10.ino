  // Librairy
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <U8g2lib.h> // définit la police : https://github.com/olikraus/u8g2/wiki/fntlistall  

#include <Wire.h>
#define TIME_BETWEEN_SCREEN 500 // ms
          // Push button
  #define DELAY_ANTI_REBOUND 10000 // us
#define PIN_SET 2
bool lastStateButton_SET = HIGH;
bool falling_SET = 0;
uint32_t lastFalling_SET = 0;       

#define PIN_RESET 8                 // number of the button's pin
bool lastStateButton_RESET = HIGH;  // when the button isn't push; the value is HIGH
bool falling_RESET = 0;             // give the falling button
uint32_t lastFalling_RESET = 0;     // Record the time of the last falling
const byte pinMotor[] = {3, 5, 9, 6};

  // MPU-6050
Adafruit_MPU6050 mpu;

int16_t ax, ay, az;  //mesures brutes
int16_t gx, gy, gz;
int32_t gyro_x_cal;
float angle_pitch_output=0;
// Setup timers and temp variables
long loop_timer;


// Display counter  
  byte displaycount = 0;


  // OLED screen
//Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
//u8g2.sendBuffer();
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

// Régulation
float kP = 10.0, kI = 0.00, kD = 0.00;
float lastError = 0, integralError;





void setup() {

// push button
  pinMode(PIN_SET, INPUT_PULLUP);
  pinMode(PIN_RESET, INPUT_PULLUP);

  
//Start I2C
  Wire.begin(); 

//Setup the registers of the MPU-6050                                                       
  setup_mpu_6050_registers(); 

  u8g2.begin();
  u8g2.enableUTF8Print();    // enable UTF8 support for the Arduino print() function 
  u8g2.setFont(u8g2_font_8x13B_tf  );  // 8x13 pixel : définit la police : https://github.com/olikraus/u8g2/wiki/fntlistall

  HomeScreen(); BetweenScreen();
  
  TestPushButtonScreen(); BetweenScreen();
}



void loop() {

  DisplayXaxisMPUScreen(); BetweenScreen(); //Prends le 0

  ScreenKPsetting(); BetweenScreen(); // Règle de P

  ScreenKDsetting(); BetweenScreen(); // Règle de D
  
  ScreenKIsetting(); BetweenScreen(); // Règle de I
  
}


void ScreenKPsetting(void){

  do{
    ReadPushButton();

    loop_mpu_6050();
    
    u8g2.setCursor(0, 13); u8g2.print("Réglage de P"); 
    u8g2.setCursor(0, 30); u8g2.print("inc. :"); u8g2.print(angle_pitch_output);
    
    RefreshScreen();
    
  }while(lastStateButton_SET);
    
  BetweenScreen();
  
  do{
    
    ReadPushButton();
    
    loop_mpu_6050();

    Regulation();
    
    if(falling_RESET){
      // each time reset button is pressed
      // increments Kp of 1 
      kP += 0.5;
      
    }
    
    
  }while(lastStateButton_SET);

  BetweenScreen();
  shutDownMotors(); // turn off all motors
  
  do{
    
    ReadPushButton();
    
    u8g2.setCursor(0, 13); u8g2.print("Valeur de P :"); 
    u8g2.setCursor(0, 30); u8g2.print(kP);
    
    RefreshScreen();
    
  }while(lastStateButton_SET);

}



void ScreenKDsetting(void){

  do{
    ReadPushButton();

    loop_mpu_6050();
    
    u8g2.setCursor(0, 13); u8g2.print("Réglage de D"); 
    u8g2.setCursor(0, 30); u8g2.print("inc. :"); u8g2.print(angle_pitch_output);
    
    RefreshScreen();
    
  }while(lastStateButton_SET);
    
  BetweenScreen();
  
  do{
    
    ReadPushButton();
    
    loop_mpu_6050();

    Regulation();
    
    if(falling_RESET){
      // each time reset button is pressed
      // increments Kp of 1 
      kD += 0.01;
      
    }
    
    
  }while(lastStateButton_SET);

  BetweenScreen();
  shutDownMotors(); // turn off all motors
  
  do{
    
    ReadPushButton();
    
    u8g2.setCursor(0, 13); u8g2.print("Valeur de D : "); 
    u8g2.setCursor(0, 32); u8g2.print(kD);
    
    RefreshScreen();
    
  }while(lastStateButton_SET);

}



void ScreenKIsetting(void){

  do{
    ReadPushButton();

    loop_mpu_6050();
    
    u8g2.setCursor(0, 13); u8g2.print("Réglage de I"); 
    u8g2.setCursor(0, 30); u8g2.print("inc. :"); u8g2.print(angle_pitch_output);
    
    RefreshScreen();
    
  }while(lastStateButton_SET);
    
  BetweenScreen();
  
  do{
    
    ReadPushButton();
    
    loop_mpu_6050();

    Regulation();
    
    if(falling_RESET){
      // each time reset button is pressed
      // increments Kp of 1 
      kI += 0.01;
      
    }
    
    
  }while(lastStateButton_SET);

  BetweenScreen();
  shutDownMotors(); // turn off all motors
  
  do{
    
    ReadPushButton();
    
    u8g2.setCursor(0, 13); u8g2.print("Valeur de I : "); 
    u8g2.setCursor(0, 32); u8g2.print(kI);
    
    RefreshScreen();
    
  }while(lastStateButton_SET);

}



void BetweenScreen(void){
  ReadPushButton();
  uint32_t time1=millis() + TIME_BETWEEN_SCREEN;
  
  while (millis() < (time1)){
  ReadPushButton();
    u8g2.setCursor(0, 13); // 25 21
    u8g2.print("NEXT SCREEN...");
    u8g2.setCursor(0, 32); // 25 21
    u8g2.print(millis()); u8g2.print(" < "); u8g2.print(time1);
    RefreshScreen();
    
  }
}



void HomeScreen(void){
  do {
    
  ReadPushButton();
  
  u8g2.setCursor(0, 21); // 25 21
  u8g2.print("Home screen :V10");   
  
  RefreshScreen();
  
  }while(lastStateButton_SET);
} // Function



void TestPushButtonScreen(void){
  do {

    ReadPushButton();
    
    static bool SET_OnOFF = 1, RESET_OnOFF = 0;
    if(falling_RESET){RESET_OnOFF = !RESET_OnOFF;}
    if(falling_SET){SET_OnOFF = !SET_OnOFF;}

    u8g2.setCursor(0, 13); // 25 21
    u8g2.print("  SET : "); u8g2.print(!lastStateButton_SET); 
    u8g2.print(" : "); u8g2.print(SET_OnOFF); 
    
    u8g2.setCursor(0, 32);
    u8g2.print("RESET : "); u8g2.print(!lastStateButton_RESET); 
    u8g2.print(" : "); u8g2.print(RESET_OnOFF); 
    
    RefreshScreen();
    
  }while(lastStateButton_RESET || lastStateButton_SET);
  
} // Function



void DisplayXaxisMPUScreen(){
  
  /* Affiche l'inclinaison
   * Si on presse sur Reset,
   * Il reprend le 0 avec 1000 mesures
   */
  do{ 
    
    ReadPushButton();

    loop_mpu_6050();

    if(falling_RESET){offset_mpu_6050_registers();}
    u8g2.setCursor(0, 13); u8g2.print("R take offset"); 
    u8g2.setCursor(0, 30); u8g2.print("axis X : "); u8g2.println(angle_pitch_output);
    RefreshScreen();
    
  }while(lastStateButton_SET);

}



void offset_mpu_6050_registers(){
  
  
  
  int32_t gyro_y_cal;
  int32_t gyro_z_cal;
  
  //Read the raw acc and gyro data from the MPU-6050 1000 times                                          
  for (int cal_int = 0; cal_int < 1000 ; cal_int ++){                  
    read_mpu_6050_data(); 
    //Add the gyro x offset to the gyro_x_cal variable                                            
    gyro_x_cal += gx;
    //Add the gyro y offset to the gyro_y_cal variable                                              
    gyro_y_cal += gy; 
    //Add the gyro z offset to the gyro_z_cal variable                                             
    gyro_z_cal += gz; 
    //Delay 3us to have 250Hz for-loop                                             

    displaycount++;
    if (displaycount > 60) { 
      
      //Display a bar loading
      u8g2.setCursor(0, 13); u8g2.print("prise du zéro..."); 
      u8g2.setCursor(0, 30); u8g2.print("mesure n°"); u8g2.print(cal_int);
      RefreshScreen();
      
      displaycount=0;
    } 
    delay(3);                                                          
  }

  gyro_x_cal /= 1000;                                                 
   
  // Init Timer 
  loop_timer = micros();   
}



void loop_mpu_6050(void){
  
     
  while(micros() - loop_timer < 400); 
 
 
  // Get data from MPU-6050
  read_mpu_6050_data();

  gx -= gyro_x_cal;
  angle_pitch_output=0.94*(angle_pitch_output+float(gx)*0.004/131) + 0.06*atan2((double)ay,(double)az)*180/PI; //+ gyro_x_cal;
  
  //Reset the loop timer                                
  loop_timer = micros();

}



void setup_mpu_6050_registers(){

  //Activate the MPU-6050
  
  //Start communicating with the MPU-6050
  Wire.beginTransmission(0x68); 
  //Send the requested starting register                                       
  Wire.write(0x6B);  
  //Set the requested starting register                                                  
  Wire.write(0x00);
  //End the transmission                                                    
  Wire.endTransmission(); 
                                              
  //Configure the accelerometer (+/-8g)
  
  //Start communicating with the MPU-6050
  Wire.beginTransmission(0x68); 
  //Send the requested starting register                                       
  Wire.write(0x1C);   
  //Set the requested starting register                                                 
  Wire.write(0x10); 
  //End the transmission                                                   
  Wire.endTransmission(); 
                                              
  //Configure the gyro (500dps full scale)
  
  //Start communicating with the MPU-6050
  Wire.beginTransmission(0x68);
  //Send the requested starting register                                        
  Wire.write(0x1B);
  //Set the requested starting register                                                    
  Wire.write(0x08); 
  //End the transmission                                                  
  Wire.endTransmission(); 
                                              
}



void read_mpu_6050_data(){ 

  //Read the raw gyro and accelerometer data

  //Start communicating with the MPU-6050                                          
  Wire.beginTransmission(0x68);  
  //Send the requested starting register                                      
  Wire.write(0x3B);
  //End the transmission                                                    
  Wire.endTransmission(); 
  //Request 14 bytes from the MPU-6050                                  
  Wire.requestFrom(0x68,14);    
  //Wait until all the bytes are received                                       
  while(Wire.available() < 14);
  

  //Following statements left shift 8 bits, then bitwise OR.  
  //Turns two 8-bit values into one 16-bit value                                       
  ax = Wire.read()<<8|Wire.read();                                  
  ay = Wire.read()<<8|Wire.read();                                  
  az = Wire.read()<<8|Wire.read();                                  
  int temp = Wire.read()<<8|Wire.read();                                   
  gx = Wire.read()<<8|Wire.read();                                 
  gy = Wire.read()<<8|Wire.read();                                 
  gz = Wire.read()<<8|Wire.read();                                 
}




void Regulation(void){

  float error = 0 - angle_pitch_output;
  float deltaError = error - lastError;
  float commande = error * kP + deltaError * kD + integralError * kI;

  integralError += error;
 
  if(commande > 0.0){ // reculer
    
    if(commande > 255){commande = 255;}
    
    analogWrite(6, commande); // droite
    analogWrite(5, commande); // gauche
    
  } else { // avancer
    
    commande = 0 - commande;
    if(commande > 255){commande = 255;}
    
    analogWrite(9, commande); //droite
    analogWrite(3, commande); // gauche
    
  }
  
     /*
  // affiche l'inclinaison 
  //  et le signal PWM au moteur
  // Increment the display counter
  displaycount = displaycount +1;
  
  if (displaycount == 255) {
  
  u8g2.setCursor(0, 13); // 25 21
  u8g2.print("axis X : "); u8g2.println(angle_pitch_output);
  
  u8g2.setCursor(0, 32); // 25 21
  u8g2.print("commande :"); u8g2.println(commande);
  
  RefreshScreen();
  
  displaycount = 0;
  
  } 
  */

  
  lastError = error;
  
}



void ReadPushButton(void){
  
  // Measures the state of the buttons
  
  bool stateButton = digitalRead(PIN_RESET);
  
  // if button is not equal at last state 
  if (stateButton != lastStateButton_RESET){

    // Record the moment t [us]
    uint32_t _micros = micros();
  
    // if the time is bigger than the delay
    if(_micros - lastFalling_RESET >= DELAY_ANTI_REBOUND){
      
      // if that only a falling and not a rising
      if(stateButton == 0){
        falling_RESET = 1;
      }
    }
    // Record again the last change state
    //Serial.println(_micros);
    lastFalling_RESET = _micros;
  } else {
     falling_RESET = 0;
  }
  
  // retiens le dernier état du bouton
  lastStateButton_RESET = stateButton; 


  
  stateButton = digitalRead(PIN_SET);
  
  // if button is not equal at last state 
  if (stateButton != lastStateButton_SET){

    // Record the moment t [us]
    uint32_t _micros = micros();
  
    // if the time is bigger than the delay
    if(_micros - lastFalling_SET >= DELAY_ANTI_REBOUND){
      
      // if that only a falling and not a rising
      if(stateButton == 0){
        falling_SET = 1;
      }
    }
    // Record again the last change state
    //Serial.println(_micros);
    lastFalling_SET = _micros;
  } else {
     falling_SET = 0;
  }
  
  // retiens le dernier état du bouton
  lastStateButton_SET = stateButton; 
  
}



void RefreshScreen(void){
  u8g2.sendBuffer();          
  u8g2.clearBuffer(); 
}



void shutDownMotors(void){
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(3, 0);
  analogWrite(9, 0);
}
