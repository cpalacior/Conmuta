// Load Wi-Fi library
//#include <Wire.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
const char* ssid     = "Palares";
const char* password = "21119767";

String distancia;
String peso;

SoftwareSerial swSer(4, 5, false, 256);

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  //Wire.begin(1);
  Serial.begin(115200);
  swSer.begin(115200);
  
  for (char ch = ' '; ch <= 'z'; ch++) {
    swSer.write(ch);
  }
  swSer.println("");
  
  // Initialize the output variables as outputs

  // Connect to Wi-Fi network with SSID and password
  //Serial.print("Connecting to ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  // Print local IP address and start web server
  //Serial.println("");
  //Serial.println("WiFi connected.");
  //Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  delay(1000);
}

void loop(){
  //Wire.requestFrom(1,1);
  //Serial.print(swSer.available());
  WiFiClient client = server.available();   // Listen for incoming clients

    if (!client) {
      return;
    }
  
    Serial.println("New Client.");          // print a message out in the serial port

    while(!client.available()){  //Esperamos a que el ciente mande una solicitud
      delay(1);
    }

    String request = client.readStringUntil('\r');
    Serial.println(request); //Imprimimos la solicitud
    client.flush(); //Descartamos los datos que se han escrito en el cliente y no se han leido

    //Serial.println("swSer disponible");
    //data[dataIndex] = byteToInt(byte1, byte2);
    //Serial.println(String(data[0])+"|"+String(data[1]));

      if (request.indexOf("/tamano") != -1){
      //distancia = datos;
      swSer.write(1);
      delay(500);
      distancia = swSer.read();
    }
    else if (request.indexOf("/peso") != -1){
      //distancia = datos;
      swSer.write(2);
      delay(500);
      peso = swSer.read();
      }
     //swSer.flush();
    delay(100);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();
          
    // Display the HTML web page
    client.println("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head>");
    client.println("<meta charset=\"utf-8\">");
    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<title>Teoría de la Conmutación</title>");
    client.println("<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-Zenh87qX5JnK2Jl0vWa8Ck2rdkQ2Bzep5IDxbcnCeuOxjzrPF/et3URy9Bv1WTRi\" crossorigin=\"anonymous\">");
    client.println("</head>");
    client.println("<body style=\"background-color: rgba(0, 0, 0, 0.849);\">");
    client.println("<center>");
    client.println("<div class=\"container\">\n");
    client.println("<br><br><br><br><br><br>");
    client.println("<h1 class=\"text-white\">¡Bienvenidos!</h1>");
    client.println("<p class=\"text-white\">Sistema para medir el peso y tamaño de una botella plástica - Teoría de la Conmutación.</p>");
    client.println("<p><div class=\"text-center\">");
    client.println("<a href=\"/tamano\" class=\"btn btn-outline-light\" >Obtener tamaño</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
    client.println("<a href=\"/peso\" class=\"btn btn-outline-light\" >Obtener peso</a>");
    client.println("</div></p>");
    client.println("</center>");
    client.println("<br><br><br><br>");
    client.println("<h3 class=\"container text-white\">Detalles de la botella plástica:</h3>");
    client.println("<br>");
    client.println("<center>");
    client.println("<div class=\"row container section\">");
    client.println("<div class=\"col-6\">");
    client.println("<input class=\"form-control text-white-50\" type=\"text\" style=\"background-color:transparent;\" value=\"Tamaño de la botella plástica :"+String(distancia)+"\" aria-label=\"readonly input example\" readonly>");
    client.println("</div>");
    client.println("<div class=\"col-6\">");
    client.println("<input class=\"form-control text-white-50\" type=\"text\" style=\"background-color:transparent;\" value=\"Peso de la botella plástica :"+String(peso)+"\" aria-label=\"readonly input example\" readonly>");
    client.println("</div>");
    client.println("</div>");
    client.println("</center>");
    client.println("<br><br><br><br><br><br><br><br><br><br><br><br>");
    client.println("<script src=\"https://cdn.jsdelivr.net/npm/@popperjs/core@2.11.6/dist/umd/popper.min.js\" integrity=\"sha384-oBqDVmMz9ATKxIep9tiCxS/Z9fNfEXiDAYTujMAeBAsjFuCZSmKbSSUnQlmh/jp3\" crossorigin=\"anonymous\"></script>");
    client.println("<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/js/bootstrap.min.js\"integrity=\"sha384-IDwe1+LCz02ROU9k972gdyvl+AESN10+x7tBKgc9I5HFtuNz0wWnPclzo6p9vxnk\" crossorigin=\"anonymous\"></script>");
    client.println("</body>");
    client.println("</html>");
    swSer.flush();
   }
   

/*uint16_t byteToInt(int byte1, byte byte2)
{
   return (uint16_t)byte1 << 8 | (uint16_t)byte2;
}*/
