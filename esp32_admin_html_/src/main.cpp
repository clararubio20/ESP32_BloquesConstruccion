/*
* Archivo creado por: Clara Rubio Almagro
* Fecha de la ultima modificación: 15/06/2023
* Trabajo Fin de Grado
* Titulación: Sistemas electrónicos
* Universidad de Málaga
*/

/* LIBRERIAS */
#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>              // Para guardar archivos en la RAM
#include <ArduinoJson.h>         // Formato de mensajes que se van a enviar
#include <AsyncTCP.h>            // Uso de websockets
#include <ESPAsyncWebServer.h>   // Servidor web
#include "esp32-hal-cpu.h"       // Para obtener datos de la ESP32
#include <DNSServer.h>

/* ARCHIVOS DEL PROYECTO */
#include "ClaseDormitorio.h"
#include "ClaseHabitacion.h"
#include "header.hpp"
#include "functions.hpp"
#include "Config.hpp"
#include "ESP32_WIFI.hpp"
#include "Server.hpp"
#include "ESP32_API.hpp"         
#include "Websocket.hpp"
#include "ESP32_WS.hpp"

void setup() 
{
  /* VELOCIDAD DEL PUERTO SERIE */
  Serial.begin(115200);
  /* FRECUENCIA DE LA CPU (VELOCIDAD DEL MICRO) */
  setCpuFrequencyMhz(240);
  log("\nInfo:Iniciando Setup");
  /* CONFIGURACIÓN DE LAS HABITACIONES */
  dormitorio1.configuracionInicial(12, 27, 35, 50, '0','0','0', 0);
  habitacion1.configuracionInicial(13, 33, 34, 50, '0','0', 0);
  /* CONFIGURACIÓN PINES */
  configPines();
  /* SPIFFS */
  if (!SPIFFS.begin(true))
  {
    log("\nError: Fallo la inicialización del SPIFFS ERROR");
    while (true);
  }
  /* LECTURA CONFIGURACIÓN */
  configRead();
  /* GUARDADO CONFIGURACIÓN */
  configSave();
  /* CONFIGURACIÓN WIFI */
  WiFi.disconnect(true);
  delay(1000);
  WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  configWiFi();
  /* INICIO WEBSOCKET */
  InitWebSockets();
  /* INICIO SERVIDOR */
  InitServer();
  log("\nInfo: Setup completado");
}

void loop() {
  /* PROCESADOR DE PETICIONES DE LA WEB */
  dnsServer.processNextRequest();
  /* ENVÍO DE MENSAJES CADA SEGUNDO */
  if (millis() - lastSendWS > 1000){
      lastSendWS  = millis();
      WsMessage(GetJson(), "");
  }
  /* LECTURA TEMPERATURA CPU */
  TempCPU = (temprature_sens_read() - 32) / 1.8;
  /* LECTURA SENSORES INFRARROJOS */
  int valueINFR = 0;
  // Dormitorio
  valueINFR = digitalRead(dormitorio1.leerPinIFR());
  if (valueINFR == LOW) {
      dormitorio1.cambiarEstadoPresencia('1');
  }
  else{
    dormitorio1.cambiarEstadoPresencia('0');
  }
  // Habitacion
  valueINFR = digitalRead(habitacion1.leerPinIFR() );
  if (valueINFR == LOW) {
      habitacion1.cambiarEstadoPresencia('1');
  }
  else{
    habitacion1.cambiarEstadoPresencia('0');
  }
  /* LECTURA LDR */
  dormitorio1.cambiarLuz(map(analogRead(dormitorio1.leerPinLDR()), 4095 , 0, 0 ,100));
  habitacion1.cambiarLuz(map(analogRead(habitacion1.leerPinLDR()), 4095 , 0, 0 ,100));
  /* MÁQUINA DE ESTADOS */
  if (modo == true)
  {
    // Gestión individual de las habitaciones
    dormitorio();
    habitacion();
  }
}