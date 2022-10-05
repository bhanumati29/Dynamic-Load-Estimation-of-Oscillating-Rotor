#ifndef PWM_DRIVER 
#define PWM_DRIVER 

#include <avr/io.h> 

class PWM_driver{      
  public:
    PWM_driver();      
    void initialize_PWM(float pwm1=1000, float pwm2=1000, float pwm3=1000, float pwm4=1000, float pwm5=1000, float pwm6=1000);  //function
    void set_pwm6n(float pwm1=1000, float pwm2=1000, float pwm3=1000, float pwm4=1000, float pwm5=1000, float pwm6=1000);
    void set_pwm4n(float pwm1=1000, float pwm2=1000, float pwm3=1000, float pwm4=1000);
    void set_pwm1(float pwm1);
    void set_pwm2(float pwm2);
    void set_pwm3(float pwm3);
    void set_pwm4(float pwm4);
    void set_pwm5(float pwm5);
    void set_pwm6(float pwm6);
    
  private:
    void configure_registers(float pwm1=1000, float pwm2=1000, float pwm3=1000, float pwm4=1000, float pwm5=1000, float pwm6=1000);
    void configure_timer_4_registers(float pwm1=1000, float pwm5=1000, float pwm6=1000);
    void configure_timer_5_registers(float pwm3=1000, float pwm4=1000, float pwm2=1000);
    uint16_t pw_to_OCRnX_t4(float pwm);
    uint16_t pw_to_OCRnX_t5(float pwm);
};

#endif
