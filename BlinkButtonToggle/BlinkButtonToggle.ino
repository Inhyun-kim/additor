
#define SW1  8
#define SW2  9
#define SW3  7
#define redLed 13
#define greenLed 12
#define blueLed 11
#define bounceWait 200

unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long currentMillis = 0;
unsigned int interval = 1000;           // interval at which to blink (milliseconds)

boolean ledState = LOW;
boolean prev1 = LOW;
boolean prev2 = LOW;
boolean prev3 = LOW;
byte onLed = redLed;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  Serial.begin(9600);
}

boolean buttonCheck(byte swNum, boolean btnState, boolean btnStatePrev){
  int time = 0;
  if(btnState == HIGH && btnStatePrev == LOW && (currentMillis - time) > bounceWait) {
    if(swNum == 1){
      interval += 200;
    } else if(swNum == 2) {
      interval -= 200;
    } else if(swNum == 3){
      ledState = LOW;
      digitalWrite(onLed, ledState);
      onLed -= 1;
      if(onLed < blueLed) onLed = redLed;
    }
    interval = constrain(interval, 200, 2000);
    time = currentMillis;
    Serial.print("Delay to ");
    Serial.println(interval);
  }  
  return btnState;
}

void loop() {
  currentMillis = millis();
  
  prev3 = buttonCheck(3, digitalRead(SW3), prev3);
  prev1 = buttonCheck(1, digitalRead(SW1), prev1);
  prev2 = buttonCheck(2, digitalRead(SW2), prev2);

  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(onLed, ledState=!ledState);
  }
}
