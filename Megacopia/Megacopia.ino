#include <Wire.h>
#include <HX711_ADC.h>

//CONSTANTES
#define DOUT A1
#define CLK A0
const int EchoPin = 50;
const int TriggerPin = 52;

float const ftrCal_ = 231.8885;
int peso = 0;
int cm = 0;
int lectura = 0;

String datos;
HX711_ADC balanza(DOUT, CLK); //HX711 constructor (dout pin, sck pin)
long t;
long t_espera = 1000; //Nota 0: coloquemos este tiempo de espera para que se tomen datos cada 1 segundo (500 milesegundos)
long t_actual;

void setup() {
   Serial.begin(115200);
   Serial3.begin(115200);
   pinMode(TriggerPin, OUTPUT);
   pinMode(EchoPin, INPUT);
   balanza.begin();
   balanza.start(2000); // la preciscion de la tara puede mejorar al añadir un par de segundos
   balanza.setCalFactor(ftrCal_);
   //Serial.println("Configuración completada...");
   t_actual = millis();
   pinMode(0, INPUT);
}

void loop() {
  //Tamaño de la botella
   cm = ping(TriggerPin, EchoPin);
   delay(100);
   
  //Peso de la botella
    balanza.update();
    if (millis() > t_actual + t_espera){
      peso = round(balanza.getData());
      //Serial.print("Peso:");
      //Serial.println(peso_);
      t_actual = millis();
    }
    delay(100);
    lectura = Serial3.read();
    delay(100);
    if(lectura == 1){
      Serial3.write(cm);
      Serial.println("distancia");
      }
     if(lectura == 2){
      Serial3.write(peso);
      Serial.println("peso");
      }
      //Serial3.flush();
    Serial.println(String(cm)+" "+String(peso));
    Serial3.flush();
    lectura = 0;
    delay(100);
}

int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   float distanciaCm = 30 - distanceCm;
   return distanciaCm;
}

/*void sendBytes(int value)
{
  Serial3.print(highByte(value));
   Serial.print(highByte(value));
  Serial3.println(lowByte(value));
  Serial.println(lowByte(value));
}*/
