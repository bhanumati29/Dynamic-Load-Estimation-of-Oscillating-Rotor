#define A 18 // Int3
#define B 19 // Int2 this is used to generate interrupt

volatile uint8_t pin_state = 0;
volatile bool stateA = 0;
volatile bool stateB = 0;

volatile long count = 0;
float th = 0;
float sf = 0.36;

void setup(){
  Serial.begin(115200);

  pinMode(A,INPUT);
  pinMode(B,INPUT);

  initialize_interrupt();
}

void loop(){
  th = ((float)count)*sf;
  Serial.print(count); Serial.print('\t'); Serial.println(th);

  delay(10);
}

void initialize_interrupt(){
  //interrupt 2 -> 19
  EICRA |= (1 << ISC20);
  EIMSK |= (1 << INT2);
  sei();
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
