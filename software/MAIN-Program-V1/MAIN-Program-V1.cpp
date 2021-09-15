/* TITLE
 *
 *         .-. .-. .-.   .-. .-. .-. .-. .-. 
 *          |  |-'  |    |(  | | |(  | |  |  
 *          '  '   `-'   ' ' `-' `-' `-'  ' 
 *
 * .-. .-. .   .-. .-. .-. .   .-. . . .-. .-. . . .-. 
 * `-. |-  |   |-  |(  |-| |   |-| |\| |    |  |\| |.. 
 * `-' `-' `-' '   `-' ` ' `-' ` ' ' ` `-' `-' ' ` `-' 
 *
 *
 *                police : Amc3Line
 *            https://ascii.co.uk/text
 *              author : Théo Grivel
 *
 *
 * Electronic board information:
 *
 *        microcontroller : ATmega328P
 *              gyroscope : MPU-6050
 *   Motors of the wheels : Moto-réducteur : https://www.conrad.fr/p/joy-it-com-motor01-moto-reducteur-jaune-noir-adapte-pour-ordinateur-monocarte-arduino-banana-pi-cubieboard-raspber-1573543
 *             Push buton : ???
 *                 Screen : ??? : https://github.com/olikraus/u8g2
 *
 *
 */


#region // define & include

#include <Arduino.h>

/* CRYSTAL ?
 * External Oscillator: up to 20MHz
 * accélérer à 2,5 fois la vitesse ! (20/8)
 * Avec les 6 & 7 du PORT B
 * Utiliser un crystal de 16 Mhz externe
 * au lieu des 8 MHz interne pour doubler la rapidité ?
 */


	// Left Motor
// PORT D
#define MOTOR_LEFT_1 1
#define MOTOR_LEFT_2 2
#define MOTOR_LEFT_PWM 3		// broche PWM

	
	// Right Motor
// PORT D
#define MOTOR_RIGHT_1 0  
#define MOTOR_RIGHT_2 4
#define MOTOR_RIGHT_PWM 5		// broche PWM


	// Push button
// Port D
#define BUTTON_SET 6
bool lastStateButton_SET = HIGH;
bool falling_SET = 0;
uint32_t lastFalling_SET = 0; 		// Record the last falling

#define BUTTON_RESET 7				// number of the button pin
bool lastStateButton_RESET = HIGH;	// when the button isn't push; the value is HIGH
bool falling_RESET = 0;				// give the falling button
uint32_t lastFalling_RESET = 0; 	// Record the last falling

#define DELAY_ANTI_REBOND 250	// micro seconde


	// Main screen
// I2C (Port C ? A 5-6???)
#define OLED_TYPE				// Screen type OLED

	// Gyroscope
// I2C (Port C ? A 5-6???)


byte numberMenu = 0; // Select the menu

/* Régulation
 * précision float (32 bit)
 * Float +- 3.4 * 10^-38 +- 3.4 * 10^38
 * C++ doesn't have unsigned float...
 *
 */
float valueKp = 0;
float valueKi = 0;
float valueKd = 0;
 
 
#endregion




//https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/15417-a-lassaut-des-pointeurs
// Function anti rebound and falling detect
				// pin number		//signal of falling		//last state's change 	// last state of the button
void FallingButton(byte pinButton, bool *fallingState, uint32_t *pointeurLastFalling, bool *pointeurLastStateButton) { 
  
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
  
}


void ScreenTestButton() { // 1st menu
	
do {
	
	// Measures the state of the buttons
	FallingButton(/*pin number*/, /*falling's signal*/, /*time of the last falling*/, /*last state of the button*/);
	
	FallingButton(BUTTON_SET, &falling_SET, &lastFalling_SET, &lastStateButton_SET);
	FallingButton(BUTTON_RESET, &falling_RESET, &lastFalling_RESET, &lastStateButton_RESET)
	
	
	// Display the current state 
	if (lastStateButton_SET) {printf("0");} else {printf("1");}
	if (lastStateButton_RESET) {printf("0");} else {printf("1");}
	
	// and the self-holding
	static bool ON_OFF_set=0;
	static bool ON_OFF_reset=0;
	
	// after each falling, 
	// switch ON/OFF
	if (falling_Set){ON_OFF_set = !ON_OFF_set;} // switch the self-holding
	if (falling_Reset){ON_OFF_reset = !ON_OFF_reset;}
	
	// Display ON/OFF
	if (ON_OFF_set){printf("ON");} else {printf("OFF");} // display the self-holding state
	if (ON_OFF_reset){printf("ON");} else {printf("OFF");}
	
	
	
	// if the both button is 1
	// change to the next menu
	if (!lastStateButton_SET && !lastStateButton_RESET){
		numberMenu++;
	}
	
	
} while (numberMenu == 0);
} // function


void ScreenCalibration() { // 2nd menu : calibration
do {

	// Take the gyroscope measure
	
	
	// Measures the state of the buttons
	bool falling_Set = FallingButton(BUTTON_SET, lastFalling_SET, lastStateButton_SET);
	bool falling_Reset = FallingButton(BUTTON_RESET, lastFalling_RESET, lastStateButton_RESET);
	
	// if the reset button is pressed
	// the 0 of the gyroscope is reset
	
	
	// display It
	
	
	// if the set button is pressed
	// change to the next menu
	numberMenu += falling_Set;
	
} while (numberMenu == 1);
} // function


void ScreenKPsetting() { // 3rd menu : Kp

do {
	
	// Measures the state of the buttons
	bool falling_Set = FallingButton(BUTTON_SET, lastFalling_SET, lastStateButton_SET);
	bool falling_Reset = FallingButton(BUTTON_RESET, lastFalling_RESET, lastStateButton_RESET);
	
	// each time reset button is pressed
	// increments Kp of 1 
	valueKp += falling_Reset;
	
	// if set button is pressed
	if(falling_Set){
		do {
	
		// display the Kp value
		
		// Measures the state of the buttons
		bool falling_Set = FallingButton(BUTTON_SET, lastFalling_SET, lastStateButton_SET);
		bool falling_Reset = FallingButton(BUTTON_RESET, lastFalling_RESET, lastStateButton_RESET);
		
		} while (falling_Set == 0)
	}
	
	
	// if set button is pressed
	// change to the next menu
	numberMenu += falling_Set;
	
	
} while (numberMenu == 2)
}


void ScreenKDsetting() { // 4th menu : Kd
	
	// each time set button is pressed
	// increments Kd of 1 
	
	// if reset button is pressed
	// display the Kd value
	
	// if set button is pressed
	// change to the next menu 
	
}


void ScreenKIsetting() { // 5th menu : ki
	
	// each time set button is pressed
	// increments Ki of 1 
	
	// if reset button is pressed
	// display the Ki value
	
	// if set button is pressed
	// change to the next menu 
	
}



void testDrawChar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

	for (uint8_t i=0; i < 168; i++) {
		if (i == '\n') continue;
			display.write(i);
		if ((i > 0) && (i % 21 == 0))
			display.println();
  }    
  display.display();
}
	
	
void readGyroscope() {
	
}

void setup() { // Funtion setup
	
	pinMode(BUTTON_RESET, INPUT_PULLUP); // no need a outside pull-up resistor
	pinMode(BUTTON_SET, INPUT_PULLUP); // no need a outside pull-up resistor
	
//Start I2C
	Wire.begin(); 
  
// I2C OLED
	// by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
	// init done
	
	// Show image buffer on the display hardware.
	// Since the buffer is intialized with an Adafruit splashscreen
	// internally, this will display the splashscreen.
	display.display();
	delay(1000);
	display.clearDisplay();
	testDrawChar();
  
// I2C gyroscope
	
	
}


void loop() { // Function Loop
	
	ScreenTestButton(); // start with the 1st menu
	
	ScreenCalibration(); // Calibration of the gyroscopey
	
	ScreenKPsetting(); // set the Kp value
	
	ScreenKdsetting(); // set the Kd value
	
	ScreenKisetting(); // set the Ki value
	
	
}



/* try anti rebound
 *https://www.tutorialspoint.com/how-can-we-return-multiple-values-from-a-function-in-c-cplusplus#:~:text=We%20can%20return%20more%20than,the%20address%20of%20the%20data.
bool FallingButton(byte pinButton, uint32_t lastFalling, bool lastStateButton) { // Function anti rebound and falling detect
	
	bool stateButton = digitalRead(pinButton);
	
	// if button is not equal at last state 
	if (stateButton != lastStateButton){
		
		// Record the moment t [us]
		uint32_t _micros = micros();
	
		// if the time is bigger than the delay
		if(_micros - lastFalling >= DELAY_ANTI_REBOND){
			
			// if that only a falling and not a rising
			if(stateButton == 0){
				return 1;
			}
		}
		// Record again the last change state
		*lastFalling = _micros;
	}
	
	// retiens le dernier état du bouton
	*lastStateButton = stateButton; 
	return 0;
}*/


/* Useless Function
void Menu() { // Function Menu Screen
	static byte menuNumber = 0;
	
	switch (menuNumber) {
		case 0:
		// Welcome screen
		break;
		
		case 1:
		// Tes
		break;
		
		case 2:
		// instruction
		break;
	}
} */
