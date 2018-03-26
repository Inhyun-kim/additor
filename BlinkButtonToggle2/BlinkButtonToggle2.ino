
#define SW_START 7 // pin 7,8,9
#define SW_CNT  3
#define LED_START 11 // pin 11,12,13
#define LED_END  13
#define bounceWait 250

unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillisBtn = 0;
int interval = 1000; // interval at which to blink (milliseconds)
boolean ledFlag = LOW;
byte onLed = LED_START;
byte btnStateMask = 0;

void setup() {
  for(int led = LED_START; led <= LED_END; led++){
    pinMode(led, OUTPUT);
  }
  for(int sw = 0; sw < SW_CNT; sw++){
    pinMode(SW_START+sw, INPUT_PULLUP);  
  }
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if((currentMillis - previousMillisBtn) > bounceWait){
    previousMillisBtn = currentMillis;
    for(int sw = 0; sw < SW_CNT; sw++){
      int btnState = !digitalRead(SW_START+sw);
      if(btnState == HIGH && (btnStateMask << sw) == LOW){
        switch(sw){
          case 0:
            interval += 200;
            break;
          case 1:
            interval -= 200;
            break;
          case 2:
            ledFlag = LOW;
            digitalWrite(onLed, ledFlag);
            onLed++;
            if(onLed > LED_END) onLed = LED_START;
            Serial.print("Change Led ");
            Serial.println(onLed);
            break;
        }
        if(sw == 0 || sw == 1){
          interval = constrain(interval, 200, 2000);
          Serial.print("Delay to ");
          Serial.println(interval);
        }
        Serial.print("btnStateMask: ");
        Serial.println(btnState << sw);
        break;
      }
      btnStateMask = btnStateMask - (btnStateMask << sw) + (btnState << sw);
      //Serial.println(btnStateMask);
    }
  }
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(onLed, ledFlag=!ledFlag);
  }
}
