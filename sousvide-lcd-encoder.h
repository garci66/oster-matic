#define RELAYPIN 5 //Use pin 5 as its PWM capable and the control board requires analog a PWM singal "(AC coupled)"
#define TEMPPIN 6
#define BOTTOMTEMPPIN A1
#define ENCODER1A 0 
#define ENCODER1B 1
#define ENCODER_BUTTON 11
#define DEBOUNCE_DELAY 10


#define TEMP_READ_TIMEOUT 2000
#define TEMP_READ_DELAY 1000
#define RELAY_PULSE 10000
#define ADJUST_TIMER_LIMIT 2000
#define ADJUST_JUMP 256
#define ADC_OFF 32
#define MINTEMP 30
#define MAXTEMP 100
#define DELTA_TEMP_SENSORS 3.0

#define OUTPUT_MIN 0
#define OUTPUT_MAX 255
#define KP .12
#define KI .0003
#define KD 0
#define SERIALPRINTLOOPTIME 2000
#define PRINTLOOPTIME 500
