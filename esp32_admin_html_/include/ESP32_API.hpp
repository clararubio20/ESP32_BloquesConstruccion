/*
* Archivo creado por: Clara Rubio Almagro
* Fecha de la ultima modificación: 15/06/2023
* Trabajo Fin de Grado
* Titulación: Sistemas electrónicos
* Universidad de Málaga
*/

/* Websocket */
AsyncWebSocket ws("/ws");

/* Función enviar JSON al Websocket */
void WsMessage(String status, String descriptor )
{
  if(descriptor != ""){
    String response;
    StaticJsonDocument<300> doc;
    doc["status"] = status;
    doc["descriptor"] = descriptor;
    serializeJson(doc, response);
    ws.textAll(response);
  }else{
    ws.textAll(status);
  }
}

void LedDormOn(AsyncWebSocketClient * client, String request)
{
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, request);
  dormitorio1.encederLED();
}

void LedDormOff(AsyncWebSocketClient * client, String request)
{
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, request);
  dormitorio1.apagarLED();
}

void LedHabOn(AsyncWebSocketClient * client, String request)
{
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, request);
  habitacion1.encederLED();
}

void LedHabOff(AsyncWebSocketClient * client, String request)
{
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, request);
  habitacion1.apagarLED();
}

void configData(AsyncWebSocketClient * client, String request)
{
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, request);
  dormitorio1.cambiarLuzAdec(doc["valueDorm"]);
  habitacion1.cambiarLuzAdec(doc["valueHab"]);
}