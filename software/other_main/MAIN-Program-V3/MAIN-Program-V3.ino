// Librairy
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <U8g2lib.h> // définit la police : https://github.com/olikraus/u8g2/wiki/fntlistall  

#include <Wire.h>
#define TIME_BETWEEN_SCREEN 1000 // ms
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

//Variables for Gyroscope
int gyro_x, gyro_y, gyro_z;
long gyro_x_cal, gyro_y_cal, gyro_z_cal;
boolean set_gyro_angles;

long acc_x, acc_y, acc_z, acc_total_vector;
float angle_roll_acc, angle_pitch_acc;

float angle_pitch, angle_roll, angle_axisZ;
int angle_pitch_buffer, angle_roll_buffer;
float angle_pitch_output, angle_roll_output;

// Setup timers and temp variables
long loop_timer;
int temp;

// Display counter
int displaycount = 0;



  // OLED screen
//Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
//u8g2.sendBuffer();
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

// Régulation
float kP = 0, kI = 0, kD = 0;
float commande = 0;

void setup() {

// push button
  pinMode(PIN_SET, INPUT_PULLUP);
  pinMode(PIN_RESET, INPUT_PULLUP);

// Connect the MPU 
/*
  if (!mpu.begin()) {  
    while (1)
      yield();
  }*/
  
  //Start I2C
  Wire.begin(); 

  //Setup the registers of the MPU-6050                                                       
  setup_mpu_6050_registers(); 

  u8g2.begin();
  u8g2.enableUTF8Print();    // enable UTF8 support for the Arduino print() function 
  u8g2.setFont(u8g2_font_8x13B_tf  );  // 8x13 pixel : définit la police : https://github.com/olikraus/u8g2/wiki/fntlistall
  
  
}



void loop() {
  
  BetweenScreen();
  TestMotorsScreen();
  
  
  BetweenScreen();
  HomeScreen();
  
  BetweenScreen();
  TestPushButtonScreen();
  
  
  BetweenScreen();
  DisplayXaxisMPUScreen();


  BetweenScreen();
  ScreenKPsetting();
  
}



void mathConversion(void){
  float a = 5.6f;
  byte b = a / 2;
  u8g2.setCursor(0, 13); u8g2.print(a); u8g2.print("/2 = "); u8g2.print(b);
  u8g2.setCursor(0, 32); u8g2.print(commande);
    RefreshScreen();
}


void ScreenKPsetting(void){
  
  
    u8g2.setCursor(0, 13); u8g2.print("1. Kp :"); u8g2.print(kP);
    u8g2.setCursor(0, 32); u8g2.print(commande);
    RefreshScreen();
  
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

  do{
    
    ReadPushButton();
    
    u8g2.setCursor(0, 13); u8g2.print("Réglage de Kp :2 "); 
    u8g2.setCursor(0, 32); u8g2.print(kP);
    RefreshScreen();
    
  }while(lastStateButton_SET);

}



void TestMotorsScreen(void){
  for(byte i=0; i<4; i++){
    for(byte j=0; j<255; j+=5){
      analogWrite(pinMotor[i], j);
      u8g2.setCursor(0, 13); // 25 21
      u8g2.print("Moteur : "); u8g2.print(pinMotor[i]);
      u8g2.setCursor(0, 32); // 25 21
      u8g2.print("Vitesse : "); u8g2.print(j);
      RefreshScreen();
      delay(40);
    }
    analogWrite(pinMotor[i], 0);
  }
}



void BetweenScreen(void){
  
  uint32_t time1=millis() + TIME_BETWEEN_SCREEN;
  
  while (millis() < (time1)){
  
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
  u8g2.print("Home screen : ");   
  
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
  
  set_OFFSET_mpu_6050_registers();
  
  do{
    
    ReadPushButton();
    
    loop_mpu_6050();

    if(falling_RESET){
      gyro_x_cal = 0;
    }
    
  }while(lastStateButton_SET);
}



void set_OFFSET_mpu_6050_registers(){
  //Read the raw acc and gyro data from the MPU-6050 1000 times                                          
  for (int cal_int = 0; cal_int < 1000 ; cal_int ++){                  
    read_mpu_6050_data(); 
    //Add the gyro x offset to the gyro_x_cal variable                                            
    gyro_x_cal += gyro_x;
    //Add the gyro y offset to the gyro_y_cal variable                                              
    gyro_y_cal += gyro_y; 
    //Add the gyro z offset to the gyro_z_cal variable                                             
    gyro_z_cal += gyro_z; 
    //Delay 3us to have 250Hz for-loop                                             

    displaycount++;
    if (displaycount > 60) { 
      
      //Display a bar loading
      u8g2.setCursor(0, 13);
      u8g2.print(cal_int);
      RefreshScreen();
      
      displaycount=0;
    } 
    delay(3);                                                          
  }

  gyro_x_cal /= 1000;                                                 
  gyro_y_cal /= 1000;                                                 
  gyro_z_cal /= 1000;
  
  u8g2.setCursor(0, 13);
  u8g2.print("offset X : ");
  u8g2.println(gyro_x_cal);
  RefreshScreen();
  delay(500);
  
  // Init Timer 
  loop_timer = micros();   
}



void loop_mpu_6050(void){
  // Get data from MPU-6050
  read_mpu_6050_data();
     
  //Subtract the offset values from the raw gyro values
  gyro_x -= gyro_x_cal;                                                
  gyro_y -= gyro_y_cal;                                                
  gyro_z -= gyro_z_cal;                                                
         
  //Gyro angle calculations . Note 0.0000611 = 1 / (250Hz x 65.5)
  
  //Calculate the traveled pitch angle and add this to the angle_pitch variable
  angle_pitch += gyro_x * 0.0000611;  
  //Calculate the traveled roll angle and add this to the angle_roll variable
  //0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians                                
  angle_roll += gyro_y * 0.0000611; 
  
  //z axis
  angle_axisZ += gyro_z * 0.0000611; 
                                     
  //If the IMU has yawed transfer the roll angle to the pitch angle
  angle_pitch += angle_roll * sin(gyro_z * 0.000001066);
  //If the IMU has yawed transfer the pitch angle to the roll angle               
  angle_roll -= angle_pitch * sin(gyro_z * 0.000001066);               
  
  //Accelerometer angle calculations
  
  //Calculate the total accelerometer vector
  acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z)); 
   
  //57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
  //Calculate the pitch angle
  angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296; 
  //Calculate the roll angle      
  angle_roll_acc = asin((float)acc_x/acc_total_vector)* -57.296;       
  
  //Accelerometer calibration value for pitch
  angle_pitch_acc -= 0.0;
  //Accelerometer calibration value for roll                                              
  angle_roll_acc -= 0.0;                                               

  if(set_gyro_angles){ 
  
  //If the IMU has been running 
  //Correct the drift of the gyro pitch angle with the accelerometer pitch angle                      
    angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004; 
    //Correct the drift of the gyro roll angle with the accelerometer roll angle    
    angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;        
  }
  else{ 
    //IMU has just started  
    //Set the gyro pitch angle equal to the accelerometer pitch angle                                                           
    angle_pitch = angle_pitch_acc;
    //Set the gyro roll angle equal to the accelerometer roll angle                                       
    angle_roll = angle_roll_acc;
    //Set the IMU started flag                                       
    set_gyro_angles = true;                                            
  }
  
  //To dampen the pitch and roll angles a complementary filter is used
  //Take 90% of the output pitch value and add 10% of the raw pitch value
  angle_pitch_output = angle_pitch_output * 0.9 + angle_pitch * 0.1; 
  //Take 90% of the output roll value and add 10% of the raw roll value 
  angle_roll_output = angle_roll_output * 0.9 + angle_roll * 0.1; 
  //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop  
  
  // Print to Serial Monitor   
  
  
  
  // Increment the display counter
  displaycount = displaycount +1;
  
  if (displaycount > 100) {
  
  u8g2.setCursor(0, 13); // 25 21
  u8g2.print("axis X : "); u8g2.println(angle_pitch_output);
  
  u8g2.setCursor(0, 32); // 25 21
  u8g2.print("commande :"); u8g2.println(commande);
  //u8g2.print("axis Y : "); u8g2.println(angle_roll_output);
  RefreshScreen();
  
  displaycount = 0;
  
  }
  

 while(micros() - loop_timer < 4000); 
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
  acc_x = Wire.read()<<8|Wire.read();                                  
  acc_y = Wire.read()<<8|Wire.read();                                  
  acc_z = Wire.read()<<8|Wire.read();                                  
  temp = Wire.read()<<8|Wire.read();                                   
  gyro_x = Wire.read()<<8|Wire.read();                                 
  gyro_y = Wire.read()<<8|Wire.read();                                 
  gyro_z = Wire.read()<<8|Wire.read();                                 
}



void Regulation(void){
  float erreur = 0 - angle_pitch_output;
  commande = erreur * kP + 0;
  if(commande < 0.0){ //avancer
    
    float cmd = 0 - commande;
    analogWrite(3, cmd);
    analogWrite(9, cmd);
    
  }
  if(commande > 0.0){ // reculer
    
    analogWrite(5, commande);
    analogWrite(6, commande);
  }
}



void ReadPushButton(void){
  
  // Measures the state of the buttons
  
/* _____  ______  _____ ______ _______  BIG
  |  __ \|  ____|/ ____|  ____|__   __|
  | |__) | |__  | (___ | |__     | |   
  |  _  /|  __|  \___ \|  __|    | |   
  | | \ \| |____ ____) | |____   | |   
  |_|  \_\______|_____/|______|  |_|
*/ 
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


  
/*
  _____ ______ _______ 
 / ____|  ____|__   __|
| (___ | |__     | |   
 \___ \|  __|    | |   
 ____) | |____   | |   
|_____/|______|  |_|  
*/ 
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
