#include "PWM_driver.h"

PWM_driver::PWM_driver(){
}

void PWM_driver::initialize_PWM(float pwm1, float pwm2, float pwm3, float pwm4, float pwm5, float pwm6){
  configure_registers(pwm1, pwm2, pwm3, pwm4, pwm5, pwm6);
}

void PWM_driver::configure_registers(float pwm1, float pwm2, float pwm3, float pwm4, float pwm5, float pwm6){
  configure_timer_4_registers(pwm1, pwm5, pwm6);
  configure_timer_5_registers(pwm3, pwm4, pwm2);
}

void PWM_driver::set_pwm4n(float pwm1, float pwm2, float pwm3, float pwm4){
  OCR4A = pw_to_OCRnX_t4(pwm1);
  OCR5A = pw_to_OCRnX_t4(pwm3);
  OCR5B = pw_to_OCRnX_t4(pwm4);
  OCR5C = pw_to_OCRnX_t4(pwm2);
}

void PWM_driver::set_pwm6n(float pwm1, float pwm2, float pwm3, float pwm4, float pwm5, float pwm6){
  OCR4A = pw_to_OCRnX_t4(pwm1);
  OCR4B = pw_to_OCRnX_t4(pwm5);
  OCR4C = pw_to_OCRnX_t4(pwm6);
  OCR5A = pw_to_OCRnX_t5(pwm3);
  OCR5B = pw_to_OCRnX_t5(pwm4);
  OCR5C = pw_to_OCRnX_t5(pwm2);
}
  
void PWM_driver::configure_timer_4_registers(float pwm1, float pwm5, float pwm6){
    // waveform generation mode for timer 4 (Fast PWM mode 14)
  TCCR4A = (1<<WGM41) | (1<<COM4A1) | (1<<COM4B1) | (1<<COM4C1);
  TCCR4B = (1<<WGM43) | (1<<WGM42) | (1<<CS41);

  // TOP value of counter
  ICR4 = 19999;

  // compare match to reset the timer_5 counter
  OCR4A = pw_to_OCRnX_t4(pwm1);
  OCR4B = pw_to_OCRnX_t4(pwm5);
  OCR4C = pw_to_OCRnX_t4(pwm6);

  // set pins as output
  DDRH |= (1<<PH3) | (1<<PH4) | (1<<PH5);
}

void PWM_driver::configure_timer_5_registers(float pwm3, float pwm4, float pwm2){
  // waveform generation mode for timer 5
  TCCR5A = (1<<WGM51) | (1<<COM5A1) | (1<<COM5B1) | (1<<COM5C1);
  TCCR5B = (1<<WGM53) | (1<<WGM52) | (1<<CS50);

  // TOP value of counter
  ICR5 = 39999;

  // compare match to reset the timer_5 counter
  OCR5A = pw_to_OCRnX_t5(pwm3);
  OCR5B = pw_to_OCRnX_t5(pwm4);
  OCR5C = pw_to_OCRnX_t5(pwm2);

  // set pins as output
  DDRL |= (1<<PL3) | (1<<PL4) | (1<<PL5);
}

void PWM_driver::set_pwm1(float pwm1){
  OCR4A = pw_to_OCRnX_t4(pwm1);
}

void PWM_driver::set_pwm2(float pwm2){
  OCR5C = pw_to_OCRnX_t5(pwm2);
}

void PWM_driver::set_pwm3(float pwm3){
  OCR5A = pw_to_OCRnX_t5(pwm3);
}

void PWM_driver::set_pwm4(float pwm4){
  OCR5B = pw_to_OCRnX_t5(pwm4);
}

void PWM_driver::set_pwm5(float pwm5){
  OCR4B = pw_to_OCRnX_t4(pwm5);
}

void PWM_driver::set_pwm6(float pwm6){
  OCR4C = pw_to_OCRnX_t4(pwm6);
}

uint16_t PWM_driver::pw_to_OCRnX_t4(float pwm){
  float OCRnX = 2.0*pwm - 1.0;
  return (uint16_t)OCRnX;
}

uint16_t PWM_driver::pw_to_OCRnX_t5(float pwm){
  float OCRnX = 16.0*pwm - 1.0;
  return (uint16_t)OCRnX;
}
