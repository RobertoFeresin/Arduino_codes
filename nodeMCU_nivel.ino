/*-------------------------------------
Centro Universitário SENAI Mariano Ferraz
Curso Superior de Tecnologia em Automação Industrial

Disciplina: instrumentação Industrial 2
Professor: Caio Vinícius

Código Exemplo
Objetivo: Realizar a leitura dos dados do sensor de nível

Estrutura do Código:

1- Inclusão de bibliotecas e variáveis
2- Conexão do nodeMCU com a internet
3- Leitura dos valores obtidos pelo sensor de nível

Configurações:
Na IDE Arduino, 
	a)ir em prefências e depois colar no campo de add board o link: 
	http://arduino.esp8266.com/stable/package_esp8266com_index.json


*/

//------------Bibliotecas e definições---------------

// biblioteca do sensor de nível by Martin Sosid, versão 2.0.0
// existem outras bibliotecas
#include <HCSR04.h>

// biblioteca para conexão wifi
#include <ESP8266WiFi.h>

// pinos de configuração do sensor ultrassonico
#define pino_trigger D6
#define pino_echo D5
#define buzzer D1


//Conexao RCW-001 ou HC-SR04
UltraSonicDistanceSensor distanceSensor(pino_trigger, pino_echo); 

void barulho(){
  if(distanceSensor.measureDistanceCm()< 10 && distanceSensor.measureDistanceCm()>5){
  tone(D1, 1000); // gera frequencia de 2000Hz no buzzer
  delay(250);
  noTone(D1); // para frequencia no buzzer
  delay(250);
  }
  else if(distanceSensor.measureDistanceCm()< 5 && distanceSensor.measureDistanceCm()>0){
    tone(D1, 3000); // gera frequencia de 2000Hz no buzzer
  delay(100);
  noTone(D1); // para frequencia no buzzer
  delay(100);
  }
  else{
    noTone(D1);
  }
}
  
void conexao(){
	const char* ssid     = "SSID";
	const char* password = "1234565";

	Serial.print("Conectando na rede");
	Serial.println(ssid);

	WiFi.begin(ssid,password);
	
	while(WiFi.status() != WL_CONNECTED){
		Serial.println(".");
		delay(500);
	}
	// só sai do while quando a conexão for realizada!

	Serial.print("Conectado na rede");
	Serial.println(ssid);
}



void setup() {
    pinMode(D1, OUTPUT);
    Serial.begin(9600); 
    // conexao();
}


void loop() {

    Serial.print("Distancia: ");
    Serial.print(distanceSensor.measureDistanceCm());
    Serial.println(" cm");

    barulho();
    delay(20);
}
