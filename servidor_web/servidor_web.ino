
#include <Wifi.h>
#include <WebServer.h>

const char* ssid = "23_F";
const char* password = "AULA23_FPOO";

//inicia el server en el puerto 80 U:

WebServer server(80);
const int ledPin = 14;

void HadleRoot(){
  
  string html = "<h1>Controlar el LED N</h1>"
  html += "<p><a href=\"/on\"><button>ON</button></a></p>";
  html += "<p><a href=\"/off\"><button>OFF</button></a></p>";
  server.send(200, "text/html",html);

}

void handleOn(){

  digitalWrite(ledPin, HIGH);
  server.send(200, "text/htmll", "LED ENCENDIDO <br><a href=\"/\">Volver</a>");
  
}

void handleOff(){

  digitalWrite(ledPin, LOW);
  server.send(200, "text/htmll", "LED APAGADO <br><a href=\"/\">Volver</a>");
  
}

void setup() {
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  delay(400);
  Wifi.begin(ssid, password);

  Serial.print("Conectando al Wifi ...");

  while(Wifi.status() != WL_CONNECTED){

    delay(500);
    Serial.print(".");

  } 
  Serial.println("\nConexión Exitosa");
  Serial.println("IP del Servidor: ");
  Serial.println(Wifi.localIP());

  server.on("/", HandleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();

}

void loop() {
  
  server.handleClient();
  

}
