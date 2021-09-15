EESchema Schematic File Version 4
LIBS:robot_self_balancing-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Schéma électronique robot self-balancing"
Date ""
Rev ""
Comp "ETML"
Comment1 "Théo Grivel"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Motor:Motor_DC M1
U 1 1 607E4EA1
P 6300 7200
F 0 "M1" H 6050 7250 50  0000 L CNN
F 1 "Right" H 5950 7150 50  0000 L CNN
F 2 "robot_self_balancing:TGL-NO_PRINT" H 6300 7110 50  0001 C CNN
F 3 "~" H 6300 7110 50  0001 C CNN
	1    6300 7200
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal Y1
U 1 1 607E6ECB
P 9800 3250
F 0 "Y1" H 9800 3518 50  0000 C CNN
F 1 "20MHz" H 9800 3427 50  0000 C CNN
F 2 "Crystal:Resonator-2Pin_W7.0mm_H2.5mm" H 9800 3250 50  0001 C CNN
F 3 "~" H 9800 3250 50  0001 C CNN
	1    9800 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 607E741A
P 9450 3500
F 0 "C1" H 9565 3546 50  0000 L CNN
F 1 "22 pF" H 9565 3455 50  0000 L CNN
F 2 "robot_self_balancing:TGL-C_12pF" H 9488 3350 50  0001 C CNN
F 3 "~" H 9450 3500 50  0001 C CNN
	1    9450 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 607E7C0D
P 10150 3500
F 0 "C2" H 10265 3546 50  0000 L CNN
F 1 "22 pF" H 10265 3455 50  0000 L CNN
F 2 "robot_self_balancing:TGL-C_12pF" H 10188 3350 50  0001 C CNN
F 3 "~" H 10150 3500 50  0001 C CNN
	1    10150 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 607EA55E
P 9450 3650
F 0 "#PWR0101" H 9450 3400 50  0001 C CNN
F 1 "GND" H 9455 3477 50  0000 C CNN
F 2 "" H 9450 3650 50  0001 C CNN
F 3 "" H 9450 3650 50  0001 C CNN
	1    9450 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 607EAAE7
P 10150 3650
F 0 "#PWR0102" H 10150 3400 50  0001 C CNN
F 1 "GND" H 10155 3477 50  0000 C CNN
F 2 "" H 10150 3650 50  0001 C CNN
F 3 "" H 10150 3650 50  0001 C CNN
	1    10150 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 3350 9450 3250
Wire Wire Line
	9450 3250 9650 3250
Wire Wire Line
	9950 3250 10150 3250
Text GLabel 10150 3150 1    50   BiDi ~ 0
20Mhz_2
Text GLabel 9450 3150 1    50   BiDi ~ 0
20Mhz_1
Wire Wire Line
	10150 3250 10150 3150
Wire Wire Line
	10150 3350 10150 3250
Connection ~ 10150 3250
Wire Wire Line
	9450 3250 9450 3150
Connection ~ 9450 3250
Text GLabel 5100 3600 2    50   BiDi ~ 0
20Mhz_1
Text GLabel 5100 3700 2    50   BiDi ~ 0
20Mhz_2
Text Notes 8850 2650 0    100  ~ 0
External crystal oscillator 
Text Notes 5350 6750 0    100  ~ 0
Motors
Text Notes 4750 2600 0    100  ~ 0
Microcontroller
$Comp
L Sensor_Motion:MPU-6050 K3
U 1 1 607F14C0
P 2100 2200
F 0 "K3" H 1500 2750 50  0000 C CNN
F 1 "MPU-6050" H 1500 2850 50  0000 C CNN
F 2 "robot_self_balancing:TGL-MPU_6050" H 2100 1400 50  0001 C CNN
F 3 "https://store.invensense.com/datasheets/invensense/MPU-6050_DataSheet_V3%204.pdf" H 2100 2050 50  0001 C CNN
	1    2100 2200
	1    0    0    -1  
$EndComp
NoConn ~ 2800 2100
NoConn ~ 2800 2200
NoConn ~ 2800 2400
NoConn ~ 2800 2500
NoConn ~ 1400 2500
NoConn ~ 1400 2400
NoConn ~ 2000 1500
Text GLabel 1400 1900 0    50   BiDi ~ 0
SDA
$Comp
L Switch:SW_Push_Dual_x2 S1
U 1 1 607F31F0
P 9850 5350
F 0 "S1" V 9896 5262 50  0000 R CNN
F 1 "Reset" V 9805 5262 50  0000 R CNN
F 2 "robot_self_balancing:TGL-Push_Button" H 9850 5550 50  0001 C CNN
F 3 "~" H 9850 5550 50  0001 C CNN
	1    9850 5350
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push_Dual_x2 S2
U 1 1 607F39F7
P 9450 5350
F 0 "S2" V 9496 5262 50  0000 R CNN
F 1 "Set" V 9405 5262 50  0000 R CNN
F 2 "robot_self_balancing:TGL-Push_Button" H 9450 5550 50  0001 C CNN
F 3 "~" H 9450 5550 50  0001 C CNN
	1    9450 5350
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 607F5030
P 9450 5550
F 0 "#PWR0103" H 9450 5300 50  0001 C CNN
F 1 "GND" H 9455 5377 50  0000 C CNN
F 2 "" H 9450 5550 50  0001 C CNN
F 3 "" H 9450 5550 50  0001 C CNN
	1    9450 5550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 607F5A6D
P 9850 5550
F 0 "#PWR0104" H 9850 5300 50  0001 C CNN
F 1 "GND" H 9855 5377 50  0000 C CNN
F 2 "" H 9850 5550 50  0001 C CNN
F 3 "" H 9850 5550 50  0001 C CNN
	1    9850 5550
	1    0    0    -1  
$EndComp
Text Notes 9600 4850 0    100  ~ 0
Buttons\n
Text Notes 1800 900  0    100  ~ 0
Gyroscope
$Comp
L power:+5V #PWR0105
U 1 1 607F6AF4
P 3550 1000
F 0 "#PWR0105" H 3550 850 50  0001 C CNN
F 1 "+5V" H 3565 1173 50  0000 C CNN
F 2 "" H 3550 1000 50  0001 C CNN
F 3 "" H 3550 1000 50  0001 C CNN
	1    3550 1000
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 607F8762
P 3150 1150
F 0 "L1" V 3340 1150 50  0000 C CNN
F 1 "1500nH" V 3250 1150 50  0000 C CNN
F 2 "robot_self_balancing:TGL_L" H 3150 1150 50  0001 C CNN
F 3 "~" H 3150 1150 50  0001 C CNN
	1    3150 1150
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 607FA5F4
P 2100 2900
F 0 "#PWR0107" H 2100 2650 50  0001 C CNN
F 1 "GND" H 2105 2727 50  0000 C CNN
F 2 "" H 2100 2900 50  0001 C CNN
F 3 "" H 2100 2900 50  0001 C CNN
	1    2100 2900
	1    0    0    -1  
$EndComp
Text Notes 1350 6500 0    100  ~ 0
Drivers motors
Wire Wire Line
	3550 1000 3550 1150
Text Notes 1550 4500 0    100  ~ 0
Screen
Text GLabel 5100 4400 2    50   BiDi ~ 0
SCL
Text GLabel 5100 4300 2    50   BiDi ~ 0
SDA
Text GLabel 1500 5000 0    50   BiDi ~ 0
SCL
Text GLabel 1500 4900 0    50   BiDi ~ 0
SDA
$Comp
L OLED_Screen:OLED_Screen P1
U 1 1 608002E0
P 1850 4600
F 0 "P1" H 2128 4296 50  0000 L CNN
F 1 "OLED_Screen" H 2128 4205 50  0000 L CNN
F 2 "robot_self_balancing:TGL-OLED_Screen" H 1850 4600 50  0001 C CNN
F 3 "" H 1850 4600 50  0001 C CNN
	1    1850 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 60803B90
P 1500 5100
F 0 "#PWR0109" H 1500 4850 50  0001 C CNN
F 1 "GND" H 1505 4927 50  0000 C CNN
F 2 "" H 1500 5100 50  0001 C CNN
F 3 "" H 1500 5100 50  0001 C CNN
	1    1500 5100
	1    0    0    -1  
$EndComp
$Comp
L L298N_MotoDriver-2:L298N T1
U 1 1 608074D5
P 2900 7000
F 0 "T1" H 3150 7600 50  0000 C CNN
F 1 "L298N" H 3200 7500 50  0000 C CNN
F 2 "robot_self_balancing:TGL-NO_PRINT" H 2900 8050 50  0001 C CNN
F 3 "" H 2900 8050 50  0001 C CNN
	1    2900 7000
	1    0    0    -1  
$EndComp
Text GLabel 3350 6850 2    50   Output ~ 0
motor_left-1
Text GLabel 3350 6950 2    50   Output ~ 0
motor_left-2
Text GLabel 3350 7050 2    50   Output ~ 0
motor_right-1
Text GLabel 3350 7150 2    50   Output ~ 0
motor_right-2
Text GLabel 6250 6950 0    50   Input ~ 0
motor_right-1
Text GLabel 6250 7550 0    50   Input ~ 0
motor_right-2
Wire Wire Line
	5100 7000 5100 6950
Wire Wire Line
	5100 6950 5050 6950
Wire Wire Line
	5100 7500 5100 7550
Wire Wire Line
	5100 7550 5050 7550
Wire Wire Line
	6300 7500 6300 7550
Wire Wire Line
	6300 7550 6250 7550
Wire Wire Line
	6300 7000 6300 6950
Wire Wire Line
	6300 6950 6250 6950
$Comp
L Device:C C5
U 1 1 6080D5A6
P 5400 7250
F 0 "C5" H 5515 7296 50  0000 L CNN
F 1 "100nF" H 5515 7205 50  0000 L CNN
F 2 "robot_self_balancing:TGL-NO_PRINT" H 5438 7100 50  0001 C CNN
F 3 "~" H 5400 7250 50  0001 C CNN
	1    5400 7250
	1    0    0    -1  
$EndComp
Text GLabel 5050 7550 0    50   Input ~ 0
motor_left-2
Text GLabel 5050 6950 0    50   Input ~ 0
motor_left-1
$Comp
L Motor:Motor_DC M2
U 1 1 607E674F
P 5100 7200
F 0 "M2" H 4850 7200 50  0000 L CNN
F 1 "Left" H 4800 7100 50  0000 L CNN
F 2 "robot_self_balancing:TGL-NO_PRINT" H 5100 7110 50  0001 C CNN
F 3 "~" H 5100 7110 50  0001 C CNN
	1    5100 7200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 6080F4E8
P 6600 7250
F 0 "C6" H 6715 7296 50  0000 L CNN
F 1 "100nF" H 6715 7205 50  0000 L CNN
F 2 "robot_self_balancing:TGL-NO_PRINT" H 6638 7100 50  0001 C CNN
F 3 "~" H 6600 7250 50  0001 C CNN
	1    6600 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 7100 5400 6950
Wire Wire Line
	5400 6950 5100 6950
Connection ~ 5100 6950
Wire Wire Line
	5400 7400 5400 7550
Wire Wire Line
	5400 7550 5100 7550
Connection ~ 5100 7550
Wire Wire Line
	6600 7100 6600 6950
Wire Wire Line
	6600 6950 6300 6950
Connection ~ 6300 6950
Wire Wire Line
	6600 7400 6600 7550
Wire Wire Line
	6600 7550 6300 7550
Connection ~ 6300 7550
$Comp
L Device:Battery_Cell BT2
U 1 1 60822B55
P 7200 1400
F 0 "BT2" H 7100 1500 50  0000 R CNN
F 1 "LiPo 3V7" H 7100 1400 50  0000 R CNN
F 2 "robot_self_balancing:TGL-NO_PRINT" V 7200 1460 50  0001 C CNN
F 3 "~" V 7200 1460 50  0001 C CNN
	1    7200 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 608253B5
P 7200 1700
F 0 "BT1" H 7100 1800 50  0000 R CNN
F 1 "LiPo 3V7" H 7100 1700 50  0000 R CNN
F 2 "robot_self_balancing:TGL-NO_PRINT" V 7200 1760 50  0001 C CNN
F 3 "~" V 7200 1760 50  0001 C CNN
	1    7200 1700
	1    0    0    -1  
$EndComp
Text Notes 7200 750  0    100  ~ 0
Accumulator and power circuit
Wire Wire Line
	3300 1150 3550 1150
Text GLabel 9600 5000 2    50   Output ~ 0
D1-button_SET
Text GLabel 9900 5100 2    50   Output ~ 0
D2-button_RESET
$Comp
L power:+5V #PWR0110
U 1 1 60833E20
P 4500 2400
F 0 "#PWR0110" H 4500 2250 50  0001 C CNN
F 1 "+5V" H 4515 2573 50  0000 C CNN
F 2 "" H 4500 2400 50  0001 C CNN
F 3 "" H 4500 2400 50  0001 C CNN
	1    4500 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2700 4500 2600
Wire Wire Line
	4500 2600 4500 2400
$Comp
L Device:C C8
U 1 1 6083C484
P 4200 2600
F 0 "C8" V 4452 2600 50  0000 C CNN
F 1 "100 nF" V 4361 2600 50  0000 C CNN
F 2 "robot_self_balancing:TGL-C_12pF" H 4238 2450 50  0001 C CNN
F 3 "~" H 4200 2600 50  0001 C CNN
	1    4200 2600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 6083E9C8
P 4050 2600
F 0 "#PWR0111" H 4050 2350 50  0001 C CNN
F 1 "GND" V 4055 2472 50  0000 R CNN
F 2 "" H 4050 2600 50  0001 C CNN
F 3 "" H 4050 2600 50  0001 C CNN
	1    4050 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 2600 4500 2600
Connection ~ 4500 2600
$Comp
L Graphic:SYM_Arrow_XLarge 7V4
U 1 1 607F55B5
P 7350 1500
F 0 "7V4" H 7350 1590 50  0001 C CNN
F 1 "+7V4" V 7300 1500 50  0000 L CNN
F 2 "robot_self_balancing:TGL-NO_PRINT" H 7350 1500 50  0001 C CNN
F 3 "~" H 7350 1500 50  0001 C CNN
	1    7350 1500
	0    1    1    0   
$EndComp
$Comp
L Regulator_Linear:LM7805_TO220 U3
U 1 1 607FCED1
P 7600 3050
F 0 "U3" H 7600 3292 50  0000 C CNN
F 1 "78M05CT" H 7600 3201 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7600 3275 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7805.pdf" H 7600 3000 50  0001 C CNN
	1    7600 3050
	1    0    0    -1  
$EndComp
Text GLabel 7100 3050 0    50   Input ~ 0
+7V4_500mA
$Comp
L Device:C C9
U 1 1 607FEC3B
P 7200 3300
F 0 "C9" V 7452 3300 50  0000 C CNN
F 1 "100nF" V 7361 3300 50  0000 C CNN
F 2 "robot_self_balancing:TGL-C_12pF" H 7238 3150 50  0001 C CNN
F 3 "~" H 7200 3300 50  0001 C CNN
	1    7200 3300
	-1   0    0    1   
$EndComp
$Comp
L Device:C C10
U 1 1 607FFB85
P 8000 3300
F 0 "C10" V 8252 3300 50  0000 C CNN
F 1 "100nF" V 8161 3300 50  0000 C CNN
F 2 "robot_self_balancing:TGL-C_12pF" H 8038 3150 50  0001 C CNN
F 3 "~" H 8000 3300 50  0001 C CNN
	1    8000 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3050 7200 3050
Wire Wire Line
	7200 3050 7200 3150
Connection ~ 7200 3050
Wire Wire Line
	7200 3050 7300 3050
Wire Wire Line
	7900 3050 8000 3050
Wire Wire Line
	8000 3150 8000 3050
Connection ~ 8000 3050
Wire Wire Line
	8000 3050 8100 3050
$Comp
L power:GND #PWR0113
U 1 1 60803AAC
P 7200 3450
F 0 "#PWR0113" H 7200 3200 50  0001 C CNN
F 1 "GND" H 7205 3277 50  0000 C CNN
F 2 "" H 7200 3450 50  0001 C CNN
F 3 "" H 7200 3450 50  0001 C CNN
	1    7200 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 60803F27
P 8000 3450
F 0 "#PWR0114" H 8000 3200 50  0001 C CNN
F 1 "GND" H 8005 3277 50  0000 C CNN
F 2 "" H 8000 3450 50  0001 C CNN
F 3 "" H 8000 3450 50  0001 C CNN
	1    8000 3450
	1    0    0    -1  
$EndComp
Text Notes 7000 2700 0    100  ~ 0
Voltage regulation
$Comp
L power:GND #PWR0108
U 1 1 60815842
P 7600 3350
F 0 "#PWR0108" H 7600 3100 50  0001 C CNN
F 1 "GND" H 7605 3177 50  0000 C CNN
F 2 "" H 7600 3350 50  0001 C CNN
F 3 "" H 7600 3350 50  0001 C CNN
	1    7600 3350
	1    0    0    -1  
$EndComp
Text GLabel 1600 6850 0    50   Input ~ 0
D3-left_motor_forward
Text GLabel 1600 6950 0    50   Input ~ 0
D5-left_motor_backward
Text GLabel 1600 7050 0    50   Input ~ 0
D6-right_motor_forward
Text GLabel 1600 7150 0    50   Input ~ 0
D9-right_motor_backward
Text GLabel 3000 6450 1    50   Input ~ 0
+7V4_500mA-driver
NoConn ~ 2800 6450
$Comp
L Connector:Conn_01x06_Male J1
U 1 1 6081A198
P 7000 5250
F 0 "J1" H 7100 5700 50  0000 C CNN
F 1 "Programmer" H 7100 5600 50  0000 C CNN
F 2 "robot_self_balancing:TGL_IDC-Header_2x03_P2.54mm_Vertical_1.2" H 7000 5250 50  0001 C CNN
F 3 "~" H 7000 5250 50  0001 C CNN
	1    7000 5250
	1    0    0    -1  
$EndComp
Text Notes 6850 4650 0    100  ~ 0
Programmer USBasp
Text GLabel 7200 5050 2    50   Input ~ 0
MISO
Text GLabel 8200 5450 2    50   Output ~ 0
RESET
Text GLabel 7200 5250 2    50   Output ~ 0
SCK
Text GLabel 7200 5350 2    50   Output ~ 0
MOSI
$Comp
L Device:R R1
U 1 1 6081D7E4
P 7950 5300
F 0 "R1" H 8020 5346 50  0000 L CNN
F 1 "10k" H 8020 5255 50  0000 L CNN
F 2 "robot_self_balancing:TGL_R" V 7880 5300 50  0001 C CNN
F 3 "~" H 7950 5300 50  0001 C CNN
	1    7950 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 6081E1EC
P 7200 5550
F 0 "#PWR0116" H 7200 5300 50  0001 C CNN
F 1 "GND" H 7205 5377 50  0000 C CNN
F 2 "" H 7200 5550 50  0001 C CNN
F 3 "" H 7200 5550 50  0001 C CNN
	1    7200 5550
	1    0    0    -1  
$EndComp
Text GLabel 5100 3400 2    50   Output ~ 0
MISO
Text GLabel 5100 3300 2    50   Input ~ 0
MOSI
Text GLabel 5100 3500 2    50   Input ~ 0
SCK
Text GLabel 5100 4500 2    50   Input ~ 0
RESET
$Comp
L robot_self_balancing-rescue:ATmega328P-PU-MCU_Microchip_ATmega K1
U 1 1 60821430
P 4500 4200
F 0 "K1" H 3856 4246 50  0000 R CNN
F 1 "ATmega328P-PU" H 3856 4155 50  0000 R CNN
F 2 "robot_self_balancing:TGL-ATmega328P_PU" H 4500 4200 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 4500 4200 50  0001 C CNN
	1    4500 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 60825601
P 4500 5700
F 0 "#PWR0117" H 4500 5450 50  0001 C CNN
F 1 "GND" H 4505 5527 50  0000 C CNN
F 2 "" H 4500 5700 50  0001 C CNN
F 3 "" H 4500 5700 50  0001 C CNN
	1    4500 5700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0118
U 1 1 6082671B
P 7950 5150
F 0 "#PWR0118" H 7950 5000 50  0001 C CNN
F 1 "+5V" H 7965 5323 50  0000 C CNN
F 2 "" H 7950 5150 50  0001 C CNN
F 3 "" H 7950 5150 50  0001 C CNN
	1    7950 5150
	1    0    0    -1  
$EndComp
Connection ~ 7950 5450
NoConn ~ 7200 5150
Wire Wire Line
	9850 5150 9850 5100
Wire Wire Line
	9850 5100 9900 5100
Wire Wire Line
	9450 5150 9450 5000
Wire Wire Line
	9450 5000 9600 5000
NoConn ~ 1400 2100
Text GLabel 5100 5000 2    50   Output ~ 0
D3-left_motor_forward
Text GLabel 5100 5200 2    50   Output ~ 0
D5-left_motor_backward
Text GLabel 5100 5300 2    50   Output ~ 0
D6-right_motor_forward
Text GLabel 5100 3100 2    50   Output ~ 0
D9-right_motor_backward
Text GLabel 5100 3000 2    50   Input ~ 0
D1-button_SET
Text GLabel 5100 4900 2    50   Input ~ 0
D2-button_RESET
NoConn ~ 4600 2700
NoConn ~ 5100 3900
NoConn ~ 5100 4000
NoConn ~ 5100 4100
NoConn ~ 5100 4200
NoConn ~ 5100 4700
NoConn ~ 5100 5100
NoConn ~ 5100 5400
NoConn ~ 2800 1900
Wire Wire Line
	2200 1150 2450 1150
Connection ~ 2450 1150
$Comp
L Device:CP1 C3
U 1 1 60818E53
P 2450 1300
F 0 "C3" H 2565 1346 50  0000 L CNN
F 1 "10μF" H 2565 1255 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 2450 1300 50  0001 C CNN
F 3 "~" H 2450 1300 50  0001 C CNN
	1    2450 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 6083D812
P 2850 1450
F 0 "#PWR0119" H 2850 1200 50  0001 C CNN
F 1 "GND" H 2855 1277 50  0000 C CNN
F 2 "" H 2850 1450 50  0001 C CNN
F 3 "" H 2850 1450 50  0001 C CNN
	1    2850 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 1150 2850 1150
Wire Wire Line
	2850 1150 3000 1150
Connection ~ 2850 1150
$Comp
L Device:C C11
U 1 1 6083A695
P 2850 1300
F 0 "C11" H 2965 1346 50  0000 L CNN
F 1 "100nF" H 2965 1255 50  0000 L CNN
F 2 "robot_self_balancing:TGL-C_12pF" H 2888 1150 50  0001 C CNN
F 3 "~" H 2850 1300 50  0001 C CNN
	1    2850 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1150 2200 1500
$Comp
L power:GND #PWR0106
U 1 1 607F9ECE
P 2450 1450
F 0 "#PWR0106" H 2450 1200 50  0001 C CNN
F 1 "GND" H 2455 1277 50  0000 C CNN
F 2 "" H 2450 1450 50  0001 C CNN
F 3 "" H 2450 1450 50  0001 C CNN
	1    2450 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 1150 10500 1150
Wire Wire Line
	10350 1450 9800 1450
Wire Wire Line
	10350 1150 10350 1450
Text GLabel 10500 1150 2    50   Output ~ 0
+7V4_500mA
$Comp
L Connector_Generic:Conn_02x04_Top_Bottom J14
U 1 1 608AA5D7
P 9500 1250
F 0 "J14" H 9550 1500 50  0000 C CNN
F 1 "Power bornier" H 9550 1600 50  0000 C CNN
F 2 "robot_self_balancing:TGL-Bornier4Pins_mm" H 9500 1250 50  0001 C CNN
F 3 "~" H 9500 1250 50  0001 C CNN
	1    9500 1250
	1    0    0    -1  
$EndComp
$Comp
L TGL-Fuse:TGL-Fuse F1
U 1 1 60842831
P 10050 1150
F 0 "F1" V 9950 1150 50  0000 C CNN
F 1 "630mA" V 9850 1150 50  0000 C CNN
F 2 "robot_self_balancing:TGL-Fuse" V 9980 1150 50  0001 C CNN
F 3 "~" H 10050 1150 50  0001 C CNN
	1    10050 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	9800 1150 9900 1150
Wire Wire Line
	10200 1150 10350 1150
Connection ~ 10350 1150
$Comp
L power:+5V #PWR0112
U 1 1 609887A0
P 1500 4800
F 0 "#PWR0112" H 1500 4650 50  0001 C CNN
F 1 "+5V" H 1515 4973 50  0000 C CNN
F 2 "" H 1500 4800 50  0001 C CNN
F 3 "" H 1500 4800 50  0001 C CNN
	1    1500 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 609A442D
P 1050 2300
F 0 "R2" H 1120 2346 50  0000 L CNN
F 1 "0Ω" H 1120 2255 50  0000 L CNN
F 2 "robot_self_balancing:TGL_R" V 980 2300 50  0001 C CNN
F 3 "~" H 1050 2300 50  0001 C CNN
	1    1050 2300
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 609ABF0D
P 1750 6850
F 0 "R3" V 1550 6800 50  0000 L CNN
F 1 "0Ω" V 1650 6800 50  0000 L CNN
F 2 "robot_self_balancing:TGL_R" V 1680 6850 50  0001 C CNN
F 3 "~" H 1750 6850 50  0001 C CNN
	1    1750 6850
	0    1    1    0   
$EndComp
Text GLabel 9300 1450 0    50   Output ~ 0
+7V4_500mA-driver
Text GLabel 9300 1350 0    50   Output ~ 0
0V-driver
Wire Wire Line
	9800 1250 9900 1250
Wire Wire Line
	9900 1250 9900 1350
Wire Wire Line
	9900 1350 9800 1350
Text GLabel 1000 2500 0    50   BiDi ~ 0
SCL
Wire Wire Line
	1400 2000 1050 2000
Wire Wire Line
	1050 2000 1050 2100
NoConn ~ 5100 3200
$Comp
L Device:R R5
U 1 1 6086802F
P 1750 7150
F 0 "R5" V 1550 7100 50  0000 L CNN
F 1 "0Ω" V 1650 7100 50  0000 L CNN
F 2 "robot_self_balancing:TGL_R" V 1680 7150 50  0001 C CNN
F 3 "~" H 1750 7150 50  0001 C CNN
	1    1750 7150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R6
U 1 1 6086C694
P 7450 5450
F 0 "R6" V 7350 5400 50  0000 L CNN
F 1 "0Ω" V 7250 5400 50  0000 L CNN
F 2 "robot_self_balancing:TGL_R" V 7380 5450 50  0001 C CNN
F 3 "~" H 7450 5450 50  0001 C CNN
	1    7450 5450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7900 5450 7950 5450
Wire Wire Line
	7950 5450 8200 5450
Wire Wire Line
	7300 5450 7200 5450
Text GLabel 1000 2100 0    50   BiDi ~ 0
SCL
Wire Wire Line
	1000 2100 1050 2100
Connection ~ 1050 2100
Wire Wire Line
	1050 2100 1050 2150
Wire Wire Line
	1000 2500 1050 2500
Wire Wire Line
	1050 2500 1050 2450
$Comp
L Device:R R7
U 1 1 609930BA
P 7750 5450
F 0 "R7" V 7650 5400 50  0000 L CNN
F 1 "0Ω" V 7550 5400 50  0000 L CNN
F 2 "robot_self_balancing:TGL_R" V 7680 5450 50  0001 C CNN
F 3 "~" H 7750 5450 50  0001 C CNN
	1    7750 5450
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_02x04_Top_Bottom J2
U 1 1 6090C2E3
P 2300 7050
F 0 "J2" H 2350 6650 50  0000 C CNN
F 1 "motor command" H 2350 6750 50  0000 C CNN
F 2 "robot_self_balancing:TGL-Bornier4Pins_mm" H 2300 7050 50  0001 C CNN
F 3 "~" H 2300 7050 50  0001 C CNN
	1    2300 7050
	-1   0    0    1   
$EndComp
Text GLabel 2900 6450 1    50   Input ~ 0
0V-driver
$Comp
L power:GND #PWR0115
U 1 1 6087D27F
P 10000 1350
F 0 "#PWR0115" H 10000 1100 50  0001 C CNN
F 1 "GND" H 10005 1177 50  0000 C CNN
F 2 "" H 10000 1350 50  0001 C CNN
F 3 "" H 10000 1350 50  0001 C CNN
	1    10000 1350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10000 1350 9900 1350
Connection ~ 9900 1350
$Comp
L Connector:Conn_01x02_Female J12
U 1 1 6093C677
P 8050 1250
F 0 "J12" H 8050 950 50  0000 R CNN
F 1 "Accu LiPo" H 8050 1050 50  0000 R CNN
F 2 "robot_self_balancing:TGL-NO_PRINT" H 8050 1250 50  0001 C CNN
F 3 "~" H 8050 1250 50  0001 C CNN
	1    8050 1250
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Male J11
U 1 1 6093CD1E
P 7900 1250
F 0 "J11" H 7900 950 50  0000 L CNN
F 1 "Accu LiPo" H 7900 1050 50  0000 L CNN
F 2 "robot_self_balancing:TGL-NO_PRINT" H 7900 1250 50  0001 C CNN
F 3 "~" H 7900 1250 50  0001 C CNN
	1    7900 1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	7200 1200 7200 1150
Wire Wire Line
	7200 1150 7700 1150
Wire Wire Line
	7200 1800 7200 1850
Wire Wire Line
	7200 1850 7600 1850
Wire Wire Line
	7600 1850 7600 1250
Wire Wire Line
	7600 1250 7700 1250
Wire Wire Line
	8250 1150 8550 1150
Connection ~ 7200 1150
Wire Wire Line
	7200 1500 6750 1500
Wire Wire Line
	6750 1500 6750 1250
Connection ~ 7200 1500
Wire Wire Line
	7200 1850 6700 1850
Wire Wire Line
	6700 1850 6700 1350
Connection ~ 7200 1850
Text Notes 6600 1150 0    26   ~ 0
Red
Text Notes 6600 1250 0    26   ~ 0
White
Text Notes 7700 1250 2    26   ~ 0
Black
Text Notes 7700 1150 2    26   ~ 0
Red
Text Notes 6600 1350 0    26   ~ 0
Black
Wire Wire Line
	7200 1150 6600 1150
Wire Wire Line
	6750 1250 6600 1250
Wire Wire Line
	6700 1350 6600 1350
$Comp
L Connector:Conn_01x03_Female J13
U 1 1 6093A82B
P 6400 1250
F 0 "J13" H 6500 1150 50  0000 C CNN
F 1 "Regulator charge" H 6450 1250 50  0000 L CNN
F 2 "robot_self_balancing:TGL-NO_PRINT" H 6400 1250 50  0001 C CNN
F 3 "~" H 6400 1250 50  0001 C CNN
	1    6400 1250
	-1   0    0    1   
$EndComp
$Comp
L TGL-SchematicLibrairy:mainSwitch S10
U 1 1 60983BBC
P 8700 800
F 0 "S10" H 8750 800 50  0000 R CNN
F 1 "mainSwitch" H 8850 700 50  0000 R CNN
F 2 "robot_self_balancing:TGL-NO_PRINT" H 8700 800 26  0001 C CNN
F 3 "" H 8700 800 26  0001 C CNN
	1    8700 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 1250 9300 1250
Wire Wire Line
	8800 1150 9300 1150
$Comp
L power:+5V #PWR0120
U 1 1 6095CDFE
P 8100 3050
F 0 "#PWR0120" H 8100 2900 50  0001 C CNN
F 1 "+5V" H 8115 3223 50  0000 C CNN
F 2 "" H 8100 3050 50  0001 C CNN
F 3 "" H 8100 3050 50  0001 C CNN
	1    8100 3050
	1    0    0    -1  
$EndComp
NoConn ~ 5100 4800
Text Notes 9600 1600 0    50   ~ 0
PCB\n
Text Notes 9500 1600 2    50   ~ 0
outside
Text Notes 2300 7300 0    50   ~ 0
outside
Text Notes 2200 7300 2    50   ~ 0
PCB
Wire Wire Line
	1600 6950 2000 6950
Wire Wire Line
	1600 7050 2000 7050
Wire Wire Line
	2000 6850 1900 6850
Wire Wire Line
	2000 7150 1900 7150
$EndSCHEMATC
