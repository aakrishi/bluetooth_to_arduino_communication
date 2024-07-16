void setup() {
  // Set pin 13 as an OUTPUT
  pinMode(13, OUTPUT);
  // Begin serial communication at a baud rate of 9600
  Serial.begin(9600);
  // Welcome message
  Serial.println("Bluetooth Module Ready. Send commands to control the LED.");
}

void loop() {
  // Variable to store received data
  String receivedString = "";
  char receivedChar;
  
  // Check if data is available to read
  if (Serial.available() > 0) {
    // Read the incoming data
    while (Serial.available() > 0) {
      receivedChar = Serial.read();
      receivedString += receivedChar;
      delay(10); // Allow time for all data to be received
    }

    // Remove any trailing newlines
    receivedString.trim();

    // Process the received string
    if (receivedString.equals("ON")) {
      digitalWrite(13, HIGH);
      Serial.println("LED is ON");
    } 
    else if (receivedString.equals("OFF")) {
      digitalWrite(13, LOW);
      Serial.println("LED is OFF");
    } 
    else if (receivedString.equals("STATUS")) {
      if (digitalRead(13) == HIGH) {
        Serial.println("LED is currently ON");
      } else {
        Serial.println("LED is currently OFF");
      }
    } 
    else if (receivedString.startsWith("BRIGHTNESS ")) {
      // Extract the brightness value
      int brightness = receivedString.substring(11).toInt();
      // Ensure the brightness value is between 0 and 255
      brightness = constrain(brightness, 0, 255);
      analogWrite(13, brightness);
      Serial.print("LED brightness set to ");
      Serial.println(brightness);
    } 
    else {
      // Handle unknown commands
      Serial.print("Unknown command: ");
      Serial.println(receivedString);
      Serial.println("Valid commands: ON, OFF, STATUS, BRIGHTNESS <value>");
    }
  }
}

