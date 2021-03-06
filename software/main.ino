// Librairy
  #include <Adafruit_MPU6050.h>
  #include <Adafruit_SSD1306.h>
  #include <Adafruit_Sensor.h>
  #include <U8g2lib.h> // Dox sur la librairie de l'écran OLED : https://github.com/olikraus/u8g2/wiki/fntlistall  

  #include <Wire.h> // librairie pour le bus I2C

// Constante
  #define OFFSET_DEMARAGE_MOTEUR 90 // définit la valeur minimum où démarre le moteur
  #define TIME_BETWEEN_SCREEN 500 // Temps entre chaque fenêtre
  #define DELAY_ANTI_REBOUND 10000 // Temps anti rebond [us]

// Boutons Set Reset
  #define PIN_SET 2 // broche du bouton set
  bool lastStateButton_SET = HIGH; // Valeur par défaut du bouton
  bool falling_SET = 0; // front montant
  uint32_t lastFalling_SET = 0; // retient le dernier front      

  #define PIN_RESET 8 // broche du bouton reset
  bool lastStateButton_RESET = HIGH;  // when the button isn't push; the value is HIGH
  bool falling_RESET = 0;             // give the falling button
  uint32_t lastFalling_RESET = 0;     // Record the time of the last falling
  const byte pinMotor[] = {3, 5, 9, 6};

// MPU-6050
  Adafruit_MPU6050 mpu;

  // Variable pour le capteur MPU-6050
  int gyro_x, gyro_y, gyro_z;
  long gyro_x_cal, gyro_y_cal, gyro_z_cal;
  boolean set_gyro_angles;

  long acc_x, acc_y, acc_z, acc_total_vector;
  float angle_roll_acc, angle_pitch_acc;

  float angle_pitch, angle_roll, angle_axisZ;
  int angle_pitch_buffer, angle_roll_buffer;
  float angle_pitch_output, angle_roll_output;
  
  
  // retient la dernière prise de mesure
  long loop_timer;
  

// Display counter  
  byte displaycount = 0;


// OLED screen
  U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

// Régulation
  
  // Constante PID pour la régulation
  float kP = 20.0, kI = 0, kD = 0.0;
  char letter = 'P'; // lettre Afficher durant les réglages.
  
  // dérivé et intégrale
  float lastError = 0, integralError;



void setup() {

// push button
  // résistance de pull up interne
  pinMode(PIN_SET, INPUT_PULLUP);
  pinMode(PIN_RESET, INPUT_PULLUP);
  
//Start I2C
  Wire.begin(); 

//Setup the registers of the MPU-6050                                                       
  setup_mpu_6050_registers(); 

// police de l'écran oled
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_8x13B_tf  );  // 8x13 pixel : définit la police : https://github.com/olikraus/u8g2/wiki/fntlistall
  
  HomeScreen(); BetweenScreen(); // écran d'acceuille
  
  TestPushButtonScreen(); BetweenScreen(); // écran pour tester les boutons
}



void loop() {

  DisplayXaxisMPUScreen(); BetweenScreen(); // Prise du zéro 

  ScreenKPsetting(); BetweenScreen(); // réglage de P
  
  ScreenKIsetting(); BetweenScreen(); // réglage de I

  ScreenKDsetting(); BetweenScreen(); // réglage de D
  
}



// Menu pour régler P
void ScreenKPsetting(void){

  do{
	  // lis l'état des boutons
    ReadPushButton();
	
	// lis l'angle du capteur
    loop_mpu_6050();
    
	// Affiche que l'on va régler P et l'angle
    u8g2.setCursor(0, 13); u8g2.print("Réglage de Kp"); 
    u8g2.setCursor(0, 30); u8g2.print("inc. :"); u8g2.print(angle_pitch_output);
    
	// recharge l'écran
    RefreshScreen();
    
  }while(lastStateButton_SET);
    
    letter = 'P';
  BetweenScreen();
  
  do{
    
    ReadPushButton();
    
    loop_mpu_6050();

    Regulation();
    
    if(falling_RESET){
		
      // incrément P à chaque appuie de Reset
      kP += 2.0;
      
    }
    
    
  }while(lastStateButton_SET);

  BetweenScreen();
  shutDownMotors(); // turn off all motors
  
  do{
    
    ReadPushButton();
    
	// Affiche la valeur de P
    u8g2.setCursor(0, 13); u8g2.print("Valeur de Kp :"); 
    u8g2.setCursor(0, 30); u8g2.print(kP);
    
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

  letter = 'I';
  BetweenScreen();
  
  do{
    
    ReadPushButton();
    
    loop_mpu_6050();

    Regulation();
    
    if(falling_RESET){
      // each time reset button is pressed
      // increments Kp of 1 
      kI += 0.1;
      
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


void ScreenKDsetting(void){

  do{
    ReadPushButton();

    loop_mpu_6050();
    
    u8g2.setCursor(0, 13); u8g2.print("Réglage de Kd"); 
    u8g2.setCursor(0, 30); u8g2.print("inc. :"); u8g2.print(angle_pitch_output);
    
    RefreshScreen();
    
  }while(lastStateButton_SET);
   letter = 'D';
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
    
    u8g2.setCursor(0, 13); u8g2.print("Valeur de KD : "); 
    u8g2.setCursor(0, 32); u8g2.print(kD);
    
    RefreshScreen();
    
  }while(lastStateButton_SET);

}


void TestMotorsScreen(void){
  for(byte i=0; i<4; i++){
    for(byte j=0; j<255; j+=5){
      analogWrite(pinMotor[i], j);
      u8g2.setCursor(0, 13); u8g2.print("Moteur : "); u8g2.print(pinMotor[i]);
      u8g2.setCursor(0, 32); u8g2.print("Vitesse : "); u8g2.print(j);
      RefreshScreen();
      delay(250);
    }
    analogWrite(pinMotor[i], 0);
  }

  
  uint32_t t=millis();
  u8g2.setCursor(0, 13); u8g2.print("Reculer ");
  u8g2.setCursor(0, 32); u8g2.print("full pwr"); 
  RefreshScreen();
  
  while((millis() - 4000) < t){
    
    analogWrite(3, 255);
    analogWrite(9, 255);
    
  }
  
  shutDownMotors(); // turn off all motors
}



void TestPushButtonScreen(void){
  do {

    ReadPushButton();
    
	// valeur qui sont mise à 1 ou à 0 à chaque front descendant 
    static bool SET_OnOFF = 1, RESET_OnOFF = 0;
	
    if(falling_RESET){RESET_OnOFF = !RESET_OnOFF;}
    if(falling_SET){SET_OnOFF = !SET_OnOFF;}

    u8g2.setCursor(0, 13); 
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

    if(falling_RESET){set_OFFSET_mpu_6050_registers();}
    u8g2.setCursor(0, 13); u8g2.print("R take offset"); 
    u8g2.setCursor(0, 30); u8g2.print("axis X : "); u8g2.println(angle_pitch_output);
    RefreshScreen();
    
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
      u8g2.setCursor(0, 13); u8g2.print("prise du zéro..."); 
      u8g2.setCursor(0, 30); u8g2.print("mesure n°"); u8g2.print(cal_int);
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

	// boucle où les mesures sont prise au maximum à 250 Hz
  while((micros() - loop_timer) < 4000){
    ;
  }
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
  int temp = Wire.read()<<8|Wire.read();                                   
  gyro_x = Wire.read()<<8|Wire.read();                                 
  gyro_y = Wire.read()<<8|Wire.read();                                 
  gyro_z = Wire.read()<<8|Wire.read();  

  loop_timer = micros();  
}




void Regulation(void){
  
  // calcule l'erreur
  float error = 0 - angle_pitch_output;
  
  //Calcule l'intégrale
  integralError += error;
  
  // Calcule le signal PWM à donner aux moteurs
  float commande = error * kP + (error - lastError) * kD + integralError* kI ;
  
  
// Reculer
  if(commande > 0.0){ 
    
  commande += OFFSET_DEMARAGE_MOTEUR; // La valeur de commande + la valeur minimale pour faire tourner le moteur
    if(commande > 255.0 ){commande = 255;}
    
    analogWrite(5, commande);
    analogWrite(6, commande);

// Avancer    
  } else {
    
    commande = OFFSET_DEMARAGE_MOTEUR - commande; // donne la valeur absolue de la commande
    if(commande > 255){commande = 255;}
    
    analogWrite(3, commande);
    analogWrite(9, commande);
    
  }
  
  // Retien l'ancienne erreur
  lastError = error;
  
}



void ReadPushButton(void){
  
  // Measures the state of the buttons
  
  bool stateButtonReset = digitalRead(PIN_RESET);
  
  // if button is not equal at last state 
  if (stateButtonReset != lastStateButton_RESET){

    // Record the moment t [us]
    uint32_t _micros = micros();
  
    // if the time is bigger than the delay
    if(_micros - lastFalling_RESET >= DELAY_ANTI_REBOUND){
      
      // if that only a falling and not a rising
      if(stateButtonReset == 0){
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
  lastStateButton_RESET = stateButtonReset; 


  
  bool stateButtonSet = digitalRead(PIN_SET);
  
  // if button is not equal at last state 
  if (stateButtonSet != lastStateButton_SET){

    // Record the moment t [us]
    uint32_t _micros = micros();
  
    // if the time is bigger than the delay
    if(_micros - lastFalling_SET >= DELAY_ANTI_REBOUND){
      
      // if that only a falling and not a rising
      if(stateButtonSet == 0){
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
  lastStateButton_SET = stateButtonSet; 
  
}



void RefreshScreen(void){
  
  // recharge l'écran
  u8g2.sendBuffer();          
  u8g2.clearBuffer(); 
  
}



void shutDownMotors(void){
	
  // met tous les moteurs à zéro
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(3, 0);
  analogWrite(9, 0);
  
}



void BetweenScreen(void){
  
  // retiens le temps où on commence cette fenêtre
  uint32_t time1=millis();
  
  // Si (maintenant - durée de la fênetre) < temps de départ 
  while (millis() - TIME_BETWEEN_SCREEN < (time1)){
  
    u8g2.setCursor(0, 13); u8g2.print("NEXT SCREEN...");
    u8g2.setCursor(0, 32); u8g2.print(millis()); u8g2.print(" < "); u8g2.print(time1);
    RefreshScreen(); // recharge l'écran
    
  }
	// Affiche la lettre de la régulation
    u8g2.setCursor(20, 13); u8g2.print(letter);
	// recharge l'écran
    RefreshScreen();
}



void HomeScreen(void){
  do {
  
	// lis l'état des boutons  
  ReadPushButton();
  
  // Affiche au milieu de l'écran le numéro de l'écran
  u8g2.setCursor(0, 21); 
  u8g2.print("Home screen :V14");   
  
  // Recharge l'écran
  RefreshScreen();
  
  // Dès que set vaut 0 (appuyé)
  // On sort de la boucle
  }while(lastStateButton_SET);
}
