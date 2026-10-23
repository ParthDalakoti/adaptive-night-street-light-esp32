#define TRIG_PIN 9 
#define ECHO_PIN 10 
#define LDR_PIN A0 
 
#define WHITE_LED1 3 
#define WHITE_LED2 4 
#define WHITE_LED3 5 
 
#define GREEN_LED1 6 
#define GREEN_LED2 7 
 
const int ldrThreshold = 500;      // Adjust according to your LDR readings 
const int distanceThreshold = 50;  // Vehicle detection range in cm 
 
unsigned long whiteLedTimer = 0; 
bool whiteLedState = false; 
 
void setup() { 
  Serial.begin(9600); 
 
  pinMode(TRIG_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT); 
 
  pinMode(WHITE_LED1, OUTPUT); 
  pinMode(WHITE_LED2, OUTPUT); 
  pinMode(WHITE_LED3, OUTPUT); 
 
  pinMode(GREEN_LED1, OUTPUT); 
  pinMode(GREEN_LED2, OUTPUT); 
 
  allLightsOff(); 
} 
 
long getDistance() { 
  digitalWrite(TRIG_PIN, LOW); 
  delayMicroseconds(2); 
 
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIG_PIN, LOW); 
 
  long duration = pulseIn(ECHO_PIN, HIGH); 
  long distance = duration * 0.034 / 2; 
 

  return distance; 
} 
 
void allLightsOff() { 
  digitalWrite(WHITE_LED1, LOW); 
  digitalWrite(WHITE_LED2, LOW); 
  digitalWrite(WHITE_LED3, LOW); 
  digitalWrite(GREEN_LED1, LOW); 
  digitalWrite(GREEN_LED2, LOW); 
} 
 
void whiteLightsOn() { 
  digitalWrite(WHITE_LED1, HIGH); 
  digitalWrite(WHITE_LED2, HIGH); 
  digitalWrite(WHITE_LED3, HIGH); 
} 
 
void greenLightsOn() { 
  digitalWrite(GREEN_LED1, HIGH); 
  digitalWrite(GREEN_LED2, HIGH); 
} 
 
void greenLightsOff() { 
  digitalWrite(GREEN_LED1, LOW); 
  digitalWrite(GREEN_LED2, LOW); 
} 
 
void loop() { 
  int ldrValue = analogRead(LDR_PIN); 
  long distance = getDistance(); 
 
  Serial.print("LDR Value: "); 
  Serial.print(ldrValue); 
  Serial.print(" | Distance: "); 
  Serial.println(distance); 
 
  // DAY MODE 
  if (ldrValue > ldrThreshold) { 
    allLightsOff(); 
    whiteLedState = false; 
    delay(100); 
    return; 
  } 
 
  // NIGHT MODE 
  if (distance > 0 && distance < distanceThreshold) { 
    whiteLightsOn(); 
    greenLightsOff(); 

 
    whiteLedTimer = millis(); 
    whiteLedState = true; 
  } 
 
  if (whiteLedState) { 
    if (millis() - whiteLedTimer >= 10000) { 
      digitalWrite(WHITE_LED1, LOW); 
      digitalWrite(WHITE_LED2, LOW); 
      digitalWrite(WHITE_LED3, LOW); 
 
      greenLightsOn(); 
      whiteLedState = false; 
    } 
  } else { 
    greenLightsOn(); 
  } 
 
  delay(100); 
}