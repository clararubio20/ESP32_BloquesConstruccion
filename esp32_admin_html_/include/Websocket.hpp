/*
* Archivo creado por: Clara Rubio Almagro
* Fecha de la ultima modificación: 15/06/2023
* Trabajo Fin de Grado
* Titulación: Sistemas electrónicos
* Universidad de Málaga
*/

/* CREACION DEL JSON SEGÚN LOS VALORES ACTUALES */
String GetJson(){
   String response;
   StaticJsonDocument<3000> jsonDoc;
   jsonDoc["WFEstatus"] = WiFi.status() == WL_CONNECTED ? F("<span class='label label-success'>CONECTADO</span>") : F("<span class='label label-important'>DESCONECTADO</span>");
   jsonDoc["WFDBM"] = WiFi.status() == WL_CONNECTED ? String(WiFi.RSSI()) : F("0");
   jsonDoc["WFPRC"] = WiFi.status() == WL_CONNECTED ? String(round(1.88 * (WiFi.RSSI() + 100)), 0) : F("0"); 
   jsonDoc["cpu"] = String(TempCPU); 
   jsonDoc["ram"] = String(ESP.getFreeHeap() * 100 / ESP.getHeapSize()); 
   jsonDoc["PMEM"] = String(round(SPIFFS.usedBytes() * 100 / SPIFFS.totalBytes()), 0); 
   // Estado LED1
   jsonDoc["led1"] = String(dormitorio1.leerEstadoLED());
   // Estado LED2
   jsonDoc["led2"] = String(habitacion1.leerEstadoLED()); 
   // Estado presencia en dormitorio
   jsonDoc["presDorm"] = String(dormitorio1.leerEstadoPresencia());
   // Estado presencia en dormitorio
   jsonDoc["presHab"] = String(habitacion1.leerEstadoPresencia()); 
   // Cantidad de luz en el dormitorio
   jsonDoc["luzDorm"] = String(dormitorio1.leerLuz());
   // Cantidad de luz en la habitacion
   jsonDoc["luzHab"] = String(habitacion1.leerLuz());
   jsonDoc["valorActDorm"] = String(dormitorio1.leerLuzAdec());
   jsonDoc["valorActHab"] = String(habitacion1.leerLuzAdec());
   jsonDoc["esNoche"] = String(dormitorio1.leerHorario());
   jsonDoc["consumoVerano"] = String(consumoVerano); 
   jsonDoc["consumoInvierno"] = String(consumoInvierno); 
   
   serializeJson(jsonDoc, response);   
   return response;
}

/* PROCESADO DE PETICIONES DE LA WEB SEGÚN COMANDO */
void ProcessRequest(AsyncWebSocketClient * client, String request){

   Serial.println(request);
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, request);
  if (error) { return; }
  
  String command = doc["command"];
  if(command == "DormOn")
  {
    LedDormOn(client, request);
  }
  else if (command == "DormOff")
  {
    LedDormOff(client, request);
  }
  else if (command == "HabOn")
  {
    LedHabOn(client, request);
  }
  else if (command == "HabOff")
  {
    LedHabOff(client, request);
  }
  else if (command == "configData")
  {
    configData(client, request);
  }
  else if (command == "ModoManual")
  {
    modo = false;
  }
  else if (command == "ModoInteligente")
  {
    modo = true;
  }
  else if (command == "cambioDia")
  {
    dormitorio1.cambiarHorario('0');
  }
  else if (command == "cambioNoche")
  {
    dormitorio1.cambiarHorario('1');
  }
  else if (command == "Respetuoso")
  {
    consumoInvierno = 6405.2;
    consumoVerano = 7140.4;
  }
  else if (command == "Despistado")
  {
    consumoInvierno = 7734.2;
    consumoVerano = 8469.4;
  }
  else if (command == "Pasota")
  {
    consumoInvierno = 8522.5;
    consumoVerano = 9317.5;
  }
}