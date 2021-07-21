#define ONBOARD_LED  2
 
void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  pinMode(ONBOARD_LED,OUTPUT);
}
 
void loop() {
  delay(10000);
  digitalWrite(ONBOARD_LED,HIGH);
  Serial.println("On");
  delay(10000);
  digitalWrite(ONBOARD_LED,LOW);
  Serial.println("Off");
}
