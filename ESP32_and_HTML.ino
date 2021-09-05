#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPAsyncWebServer.h>

#include "index.h"  // Página da web e seus arquivos
#define sinalmotor 2
WebServer server(80);//objeto do servidor 

int aux = 0; //váriavel de contagem 
String header;
int StatusMotor = 0; 



// Esta rotina é executada quando você abre seu IP no navegador

void handleRoot() {
 String s = MAIN_page; //ler o conteudo HTML 
 server.send(200, "text/html", s); //Envia página da Web
}
 
void handleADC() {
 aux++; // variavel do sinal do encoder 
 String VelocidadeMotor = String(aux);
 
 server.send(200, "text/plane", VelocidadeMotor); //Envia valor da velocidade do motor para a Web
}
void Zero() {
  //variavél da analógica do esp
 server.send(200, "text/plane", "");
}

void Cinquenta() {
   //variavél da analógica do esp
 server.send(200, "text/plane", "");
}

void Cem() {
   //variavél da analógica do esp
 server.send(200, "text/plane", "");
}


void botao() {
  if(StatusMotor == 0){
    digitalWrite(sinalmotor, HIGH);// Inicia os pinos em nível baixo (LOW)
    StatusMotor = 1;
    }
    else {
      digitalWrite(sinalmotor, LOW);// Inicia os pinos em nível baixo (LOW)
      StatusMotor = 0;
      }

  String StatusMotorTexto = String (StatusMotor);    
  server.send(200, "text/plane",StatusMotorTexto); //Envia valor da velocidade do motor para a Web
  }


void setup(void){
  Serial.begin(115200);//inicializa serial com 115200 bits por segundo
  Serial.println();

pinMode(sinalmotor, OUTPUT);// Define os pinos como saída de sinal
digitalWrite(sinalmotor, LOW);// Inicia os pinos em nível baixo (LOW)

pinMode(T0, INPUT);

//ESP32 As access point
  WiFi.mode(WIFI_AP); //Modo do WI-FI

    //Se a conexão for bem sucedida, mostre o endereço IP no monitor serial
  Serial.println("");
  Serial.print("Conectado a ");
//  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //Endereço IP atribuído ao seu ESP
//----------------------------------------------------------------
 
  server.on("/", handleRoot);      //Está é a pagina de exibição
  server.on("/readADC", handleADC);//Para obter a atualização do valor VelocidadeMotor apenas
  server.on("/LigarDelisgarMotor", botao);//Para obter a atualização do valor do botão
  server.on("/0%", Zero);
  server.on("/50%", Cinquenta);
  server.on("/100%", Cem);     
  server.begin();                  //Inicia servidor
  Serial.println("Iniciar servidor HTTP");
}

//===============================================================
// Esta rotina é executada ao abrir seu IP no navegador
//===============================================================
void loop(void){
  server.handleClient();
  delay(1);

}

 


  
