#include "PWM_driver.h"

float f = 100; // freaq Hz
float dt = 1.0/f; // sample time in sec
float loop_time = dt*1000000.0; // itme taken for one loop in us
unsigned long t;

PWM_driver pwm;
float pos;
float pi = PI;

float A = 500;
float TimeP=1.0;
float freq =1.0/TimeP;
float w = 2*PI*freq;
float t_now = 0;
float a=1.0;

void setup() {
  pwm.initialize_PWM(1500, 1000, 1578.2, 1896.45);
  Serial.begin(115200);
  delay(10000);
  //ESC_signal
  pwm.set_pwm2(1500);
  //while(1){}
  delay(5000); 
  t = micros();
}

void loop() {
  // timer4 @ 100 Hz
  // timer5 @ 400 Hz
  //pwm no: 1,  2,  3,  4, 5, 6
  //pin no: 6, 44, 46, 45, 7, 8
  //timer:  4,  5,  5,  5, 4, 4
    
// Servo Oscillation
  pos = A*sin(w*t_now) + 1500;
  Serial.println(t_now);
  t_now += dt;
  pwm.set_pwm1(pos);
  
// Fixing loop's time period
//  Serial.print(1000000.0/((float)((micros()-t)))); Serial.print('\t');
  while((float)((micros()-t))<loop_time){}
//  Serial.println(1000000.0/((float)((micros()-t))));
  t = micros();

//fixed movement of servo
// while (t_now>=(a/freq)){}
 
}
