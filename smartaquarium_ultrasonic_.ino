#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


#define FIREBASE_HOST "tubesiot-a2e9c.firebaseio.com"
#define FIREBASE_AUTH "yRHiYAel2aSBXYar4xbCLAb5jnuAbypndTsma9kr"
#define WIFI_SSID "rexus"
#define WIFI_PASSWORD "Abi180798"

#define trigPin D6
#define echoPin D7
#define led D5

long duration, distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);

  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


void loop() {
  if (Firebase.getInt("isi") <= 7 ){
    if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
    }else{
      Serial.println(Firebase.getInt("isi"));
      digitalWrite(led, LOW);
      Serial.println("Masih Ada");
      SonarSensor(trigPin, echoPin);
      Firebase.setInt("isi", distance);
    }
  }else{
    if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());
      return;
    }else{
      Serial.println(Firebase.getInt("isi"));
      Serial.println("Silahkan isi kembali");
      digitalWrite(led, HIGH);
      SonarSensor(trigPin, echoPin);
      Firebase.setInt("isi", distance);
    }
  }
}
void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
}
