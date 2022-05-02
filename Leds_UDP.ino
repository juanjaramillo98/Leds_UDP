#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>

// Set WiFi credentials
#define WIFI_SSID "juanpablo"
#define WIFI_PASS "70577893"
#define UDP_PORT 4210

#define LED_PIN    5

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 256

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// UDP
WiFiUDP UDP;
char packet[768];
char reply[] = "Packet received!";

   
void setup() {
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
   
  // Begin WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
   
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
   
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);

  strip.begin();
  strip.show();
   
}
   
void loop() {
  // put your main code here, to run repeatedly:
  // If packet received...
  int packetSize = UDP.parsePacket();
  if (packetSize) {
    strip.clear();
    //Serial.print("Received packet! Size: ");
    //Serial.println(packetSize); 
    int len = UDP.read(packet, 768);
    int k;
    int p;
    int l;
    for(int j=0; j<16; j++){
      for(int i=0; i<16; i++) {
        if(j%2==0){
          k = (16*j)+i;
        }else{
          k = (16*j)+(15-i);
        }
        l = (16*j)+i;
        p = k*3;
        strip.setPixelColor(l, strip.Color(packet[p], packet[p+1], packet[p+2]));
      }
      //Serial.println();
    }
    strip.show();
  }
}
