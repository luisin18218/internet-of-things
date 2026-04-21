
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "23_F";
const char* password = "AULA23_FPOO";

//inicia el server en el puerto 80 U:

WebServer server(80);

const char* htmlPage = R"rawliteral( <!DOCTYPE html>
<html>
    <head>
        <title>Clima</title>

        <style>
            body { font-family: Arial; text-align: center; margin: 50px; }
            h1 {color: aqua;}
            #potValue { font-size: 24px; color: chocolate;}
        </style>

    </head>
    <body>
        <h1>Temparatura actual en Puebla</h1>
        <p id="TempValue"> --- </p>
        
        <script>
            function upadateWeather() {
                fetch('/weather')
                .then(Response => Response.text()) //de respuesta a texto
                .then(data => document.getElementById('TempValue').innerText = data + "°C") //redireccionar a data, modificar el html
                
            }
            setInterval(upadateWeather,5000); //que se repita la funcion
        </script>
    </body>

</html> )rawliteral";

float latitude = 19.04;
float longitude = 19.04;
bool current_Weather = true;

void handleRoot(){
  server.sen(200, "text/html", htmlPage);
}

void handleWeather() {
  
  if(Wifi.status() == WL_CONNECTED){
    HTTPClient http;
    String url = "https://api.open-meteo.com/v1/forecast?latitude="+
                  Sring(latitude,2) +
                  "&longitude="+String(longitude,2)+
                  "current_weather="+
                  String(current_Weather ? "true":"false"); 
    http.begin(url);
    int httpCode = http.GET();

    if(httpCode > 0){
      String payload = http.getString(); //regresa un json
      StaticJsonDocument<1024> doc;
      DeserializationError error =  deserializeJson(doc,payload); 

      if(!error){
        float temperatura = doc["current_weather"]["temperature"];

        server.send(200, "text/plain",String(temperatura));
        http.end();
        return;
      }

    }
  }
  server.send(200,"text/plain","ERROR") 

void setup() {
  Serial.begin(115200);
  Wifi.begin(ssid, password)
  
  Serial.print("Conectado al Wifi ...")
  
  while(Wifi.status() != WL_CONNECTED){
    delay(50);
    Serial.print(".");
  }
   Serial.print("\nConectado");
   Serial.print("IP del Servidor: ");
   Serial.println(Wifi.localIP()); 

   server.on("/", handleRoot);
   server.on("/weather", handleWeather);
   server.begin(); 
    // put your setup code here, to run once:

}

void loop() {
  server.handleClient();

}
