/*
* Archivo creado por: Clara Rubio Almagro
* Fecha de la ultima modificación: 15/06/2023
* Trabajo Fin de Grado
* Titulación: Sistemas electrónicos
* Universidad de Málaga
*/

void configWiFi(){
    /* AP */
    WiFi.setHostname(deviceID().c_str());
    WiFi.softAP(nameap, passwordap);
    log("\nInfo: WiFi AP " + deviceID() + " - IP " + ipStr(WiFi.softAPIP()));
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(DNSSERVER_PORT, "*", WiFi.softAPIP());
    
    /* CLIENTE */
    // DESCOMENTAR SI HAY PROBLEMAS PARA CONECTARSE AL WIFI Y SE QUIERE PONER LOS VALORES DE AHÍ
    //configReset();
    WiFi.begin(ssid, pw);
    log("\nInfo: Conectando WiFi " + String(ssid));
    byte b = 0;
    while (WiFi.status() != WL_CONNECTED && b < 60){
        b++;
        delay(500);
    }
    if (WiFi.status() == WL_CONNECTED){
        log("\nInfo: WiFi conectado (" + String(WiFi.RSSI()) + ") IP " + ipStr(WiFi.localIP()));
    }else{
        log(F("\nError: WiFi no conectado"));
    }
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
  log("\nInfo: Intentando conectar al WiFi");
  WiFi.disconnect();
  WiFi.begin(ssid, pw);
}