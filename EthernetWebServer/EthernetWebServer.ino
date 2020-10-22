
#include <SPI.h>
#include <Ethernet.h>

int Light_1 = 5;
int Light_2 = 6;
int Light_3 = 7;
int Fan_1 = 8;


byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };//physical mac address
byte ip[] = { 
  192, 168, 0, 200 };                 //ip address auto-connection when the app is open
byte gateway[] = { 
  192, 168, 0, 1 };                   // internet access via router
byte subnet[] = { 
  255, 255, 255, 0 };                 //subnet mask
EthernetServer server(80);           //server port     

String readString;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  for(int i = 5; i<=8;i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH); 
  }

  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
        }

        //if HTTP request has ended
        if (c == '\n') {          
          Serial.println(readString); //print to serial monitor for debuging       

          delay(1);
          //stopping client
          client.stop();
          //controls the Arduino if you press the buttons
          if (readString.indexOf("on1") >0){
            digitalWrite(Light_1, LOW);
          }
          if (readString.indexOf("off1") >0){
            digitalWrite(Light_1, HIGH);
          }
          if (readString.indexOf("on2") >0){
            digitalWrite(Light_2, LOW);
          }
          if (readString.indexOf("off2") >0){
            digitalWrite(Light_2, HIGH);
          }
          if (readString.indexOf("on3") >0){
            digitalWrite(Light_3, LOW);
          }
          if (readString.indexOf("off3") >0){
            digitalWrite(Light_3, HIGH);
          }
          if (readString.indexOf("onFan") >0){
            digitalWrite(Fan_1, LOW);
          }
          if (readString.indexOf("offFan") >0){
            digitalWrite(Fan_1, HIGH);
          }
          //clearing string for next read
          readString="";  

        }
      }
    }
  }
}






