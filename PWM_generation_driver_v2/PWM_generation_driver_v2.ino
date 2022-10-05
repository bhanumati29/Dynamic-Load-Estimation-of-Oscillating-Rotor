
#include "PWM_driver.h"

float f = 100; // freaq Hz
float dt = 1.0/f; // sample time in sec
float loop_time = dt*1000000.0; // itme taken for one loop in us
unsigned long t;

PWM_driver pwm;
float pos;
float pi = PI;

float Amp = 500;
float TimeP=20.0;
float freq =1.0/TimeP;
float w = 2*PI*freq;
float t_now = 0;
float a=1.0;

// encoder variable starts here
#define A 18 // Int3
#define B 19 // Int2 this is used to generate interrupt

volatile uint8_t pin_state = 0;
volatile bool stateA = 0;
volatile bool stateB = 0;

volatile long count = 0;
float th = 0;
float sf = 0.36;
// encoder variable ends here


void setup() {
  pwm.initialize_PWM(1500, 1000, 1578.2, 1896.45);
  Serial.begin(115200);

  while(1){}
  
  delay(5000);
  
  //ESC_signal
   pwm.set_pwm2(1800);
   
   while(Serial.available()==0){}

  // encoder variables starts
  pinMode(A,INPUT);
  pinMode(B,INPUT);
  initialize_interrupt();
  // encoder variables ends
  
  t = micros();
}

void loop() {
   
  th = ((float)count)*sf;
  Serial.print(t_now,3); Serial.print('\t');
  //Serial.print(count); Serial.print('\t');
  Serial.print(th,2); Serial.print('\t');
  
  // timer4 @ 100 Hz
  // timer5 @ 400 Hz
  //pwm no: 1,  2,  3,  4, 5, 6
  //pin no: 6, 44, 46, 45, 7, 8
  //timer:  4,  5,  5,  5, 4, 4
  
  // Servo Oscillation
  pos = Amp*sin(w*t_now) + 1500;
  Serial.println(pos);
  t_now += dt;
  pwm.set_pwm1(pos);
  
  // Fixing loop's time period
  //  Serial.print(1000000.0/((float)((micros()-t)))); Serial.print('\t');
  while((float)((micros()-t))<loop_time){}
  //  Serial.println(1000000.0/((float)((micros()-t))));
  t = micros();
  
  // For quarter/One oscillation
   while (t_now>(a/freq)){}
}

void initialize_interrupt(){
  //interrupt 2 -> 19
  EICRA |= (1 << ISC20);
  EIMSK |= (1 << INT2);
  sei(); // activate any interrupt to be executed
}

ISR(INT2_vect){
  //stateA = digitalRead(A);
  //stateB = digitalRead(B);
  pin_state = PIND;
  stateA = pin_state & 0b00001000;
  stateB = pin_state & 0b00000100;

  if(stateA==1){
    if(stateB==0){
      count++;
    }
    else{
      count--;
    }
  }
}
