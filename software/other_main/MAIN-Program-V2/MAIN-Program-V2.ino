        // Librairy
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <U8g2lib.h> // définit la police : https://github.com/olikraus/u8g2/wiki/fntlistall  

          
          // Push button
  #define DELAY_ANTI_REBOUND 2500
#define PIN_SET 2
bool lastStateButton_SET = HIGH;
bool falling_SET = 0;
uint32_t lastFalling_SET = 0;       

#define PIN_RESET 8                 // number of the button's pin
bool lastStateButton_RESET = HIGH;  // when the button isn't push; the value is HIGH
bool falling_RESET = 0;             // give the falling button
uint32_t lastFalling_RESET = 0;     // Record the time of the last falling


  // MPU-6050
Adafruit_MPU6050 mpu;

  // OLED screen
//Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 



void setup() {

// push button
  pinMode(PIN_SET, INPUT_PULLUP);
  pinMode(PIN_RESET, INPUT_PULLUP);

// Connect the MPU
  if (!mpu.begin()) {  
    while (1)
      yield();
  }

  u8g2.begin();
   
   u8g2.setFont(u8g2_font_8x13B_tf  );  // 8x13 pixel : définit la police : https://github.com/olikraus/u8g2/wiki/fntlistall
  
  
}

void loop() {
  
  BetweenScreen();
  BetweenScreen();
  HomeScreen();
  
  BetweenScreen();
  TestPushButtonScreen();
  
}


void BetweenScreen(void){
  
  uint32_t time1=millis() + 1000;
  
  while (millis() < (time1)){
  
    u8g2.setCursor(0, 13); // 25 21
    u8g2.print("NEXT SCREEN...");
    u8g2.setCursor(0, 32); // 25 21
    u8g2.print(millis()); u8g2.print(" < "); u8g2.print(time1);
    RefreshScreen();
    
  }
  
   
  // wait 500 ms before the next screen
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
    
    static bool SET_OnOFF = 0, RESET_OnOFF = 0;
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



 
  


/*                  // pin number   //signal of falling   //last state's change          // last state of the button
void FallingButton(byte pinButton, bool *fallingState, uint32_t *lastFalling_RESET, bool *pointeurLastStateButton) { 
  
  bool stateButton = digitalRead(pinButton);
  
  // if button is not equal at last state 
  if (stateButton != *pointeurLastStateButton){

    // Record the moment t [us]
    uint32_t _micros = micros();
  
    // if the time is bigger than the delay
    if(_micros - *pointeurLastFalling >= DELAY_ANTI_REBOUND){
      
      // if that only a falling and not a rising
      if(stateButton == 0){
        *fallingState = 1;
      }
    }
    // Record again the last change state
    //Serial.println(_micros);
    *pointeurLastFalling = _micros;
  } else {
     *fallingState = 0;
  }
  
  // retiens le dernier état du bouton
  *pointeurLastStateButton = stateButton; 

  
      //https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/15417-a-lassaut-des-pointeurs
      // Function anti rebound and falling detect
}*/


void RefreshScreen(void){
  u8g2.sendBuffer();          
  u8g2.clearBuffer(); 
}
void testOLED(){
  static byte x=0, y=0, z=0; 
  u8g2.setCursor(0, y); // 25 21
  //u8g2.setFont(u8g2_font_unifont_t_greek );  // 10 x 7 pixel : 
  u8g2.print("Home screen : "); // 11 char 
  u8g2.print(x); // 11 char
  //u8g2.setFont(u8g2_font_8x13B_tf  );  // 8x13 pixel

  if(z>5){
    u8g2.sendBuffer();          
    u8g2.clearBuffer(); 
    z=0;  
  }
  x++;
  z++;
  if(x>10){
    y++;
    x=0;
  }
}
