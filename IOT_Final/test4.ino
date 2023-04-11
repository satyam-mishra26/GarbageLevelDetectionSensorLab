#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

// Replace with your Wi-Fi network credentials
const char* ssid = "Rinku";
const char* password = "Shankar@mishra";

// Replace with your Firebase project's URL and secret
#define FIREBASE_HOST "https://sensorlab-32dfe-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyCAjgz4E_MoB95TUrIFx0cwIklH5AC5d1c"

// Initialize Firebase
FirebaseData firebaseData;

// Define the ultrasonic sensor pins
#define trigPin D7
#define echoPin D8
#define trigPin1 D5
#define echoPin1 D6

// Define the maximum distance to detect garbage level (in centimeters)
#define maxDistance 50

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi!");

  // Initialize the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.println("Firebase initialized!");
}

void loop() {
  // Get the distance from the ultrasonic sensor
   float duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print("\n Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
//  Firebase.setString(firebaseData, "/garbageLevels", String(distance).c_str());
//    if (firebaseData.dataAvailable()) {
//      Serial.println("Garbage level uploaded to Firebase!");
//    } else {
//      Serial.println("Error uploading garbage level to Firebase:");
//      Serial.println(firebaseData.errorReason());
//    }

   // Wait for some time before taking the next reading
  delay(2000);

  float duration1, distance1;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 / 2) / 29.1;
  Serial.print("\n Distance: ");
  Serial.print(distance1);
  Serial.println(" cm");
  Firebase.setString(firebaseData, "/garbageLevels/sensor1", String(distance).c_str());
  Firebase.setString(firebaseData, "/garbageLevels/sensor2", String(distance1).c_str());
    if (firebaseData.dataAvailable()) {
      Serial.println("Garbage level of second sensor uploaded to Firebase!");
    } else {
      Serial.println("Error uploading garbage level of Second Sensor to Firebase:");
      Serial.println(firebaseData.errorReason());
    }

  // Wait for some time before taking the next reading
  delay(2000);
}
