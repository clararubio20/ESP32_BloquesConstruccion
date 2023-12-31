/*
* Archivo creado por: Clara Rubio Almagro
* Fecha de la ultima modificación: 15/06/2023
* Trabajo Fin de Grado
* Titulación: Sistemas electrónicos
* Universidad de Málaga
*/

/* Instancia de AsyncWebServer */
AsyncWebServer server(80);

// Cargar Información de las paginas al Servidor --------------------------------------
void InitServer(){
    // Con esto cargamos todos los css y páginas q influyan de forma estática en la esp (todos menos el html)
    /**********************************************/
    server.serveStatic("/bootstrap-responsive.min.css", SPIFFS, "/bootstrap-responsive.min.css").setDefaultFile("bootstrap-responsive.min.css");
    server.serveStatic("/bootstrap.min.css", SPIFFS, "/bootstrap.min.css").setDefaultFile("bootstrap.min.css");
    server.serveStatic("/styles.css", SPIFFS, "/styles.css").setDefaultFile("styles.css");
    server.serveStatic("/jquery.easy-pie-chart.css", SPIFFS, "/jquery.easy-pie-chart.css").setDefaultFile("jquery.easy-pie-chart.css");
    server.serveStatic("/bootstrap.min.js", SPIFFS, "/bootstrap.min.js").setDefaultFile("bootstrap.min.js");
    server.serveStatic("/jquery-1.9.1.min.js", SPIFFS, "/jquery-1.9.1.min.js").setDefaultFile("jquery-1.9.1.min.js");
    server.serveStatic("/jquery.easy-pie-chart.js", SPIFFS, "/jquery.easy-pie-chart.js").setDefaultFile("jquery.easy-pie-chart.js");
    server.serveStatic("/modernizr.min.js", SPIFFS, "/modernizr.min.js").setDefaultFile("modernizr.min.js");
    server.serveStatic("/sweetalert2.min.css", SPIFFS, "/sweetalert2.min.css").setDefaultFile("sweetalert2.min.css");
    server.serveStatic("/sweetalert2.min.js", SPIFFS, "/sweetalert2.min.js").setDefaultFile("sweetalert2.min.js");
    server.serveStatic("/scripts.js", SPIFFS, "/scripts.js").setDefaultFile("scripts.js");
    server.serveStatic("/glyphicons-halflings.png", SPIFFS, "/glyphicons-halflings.png").setDefaultFile("glyphicons-halflings.png");
    server.serveStatic("/glyphicons-halflings-white.png", SPIFFS, "/glyphicons-halflings-white.png").setDefaultFile("glyphicons-halflings-white.png");
    server.serveStatic("/logo.png", SPIFFS, "/logo.png").setDefaultFile("logo.png");
    /**********************************************/
    // Ahora si se carga el html de diferente forma
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      // Index.html
      File file = SPIFFS.open(F("/index.html"), "r");
      if (file){
        file.setTimeout(100);
        String s = file.readString();
        file.close();
        // Actualiza contenido dinamico del html
        s.replace(F("#id#"), id);
        s.replace(F("#serie#"), device_id);
        /* Bloque WIFI */
        s.replace(F("#WFEstatus#"), WiFi.status() == WL_CONNECTED ? F("<span class='label label-success'>CONECTADO</span>") : F("<span class='label label-important'>DESCONECTADO</span>"));
        s.replace(F("#WFSSID#"), WiFi.status() == WL_CONNECTED ? F(ssid) : F("--"));
        s.replace(F("#sysIP#"), ipStr(WiFi.status() == WL_CONNECTED ? WiFi.localIP() : WiFi.softAPIP()));
        s.replace(F("#WFDBM#"), WiFi.status() == WL_CONNECTED ? String(WiFi.RSSI()) : F("0"));
        s.replace(F("#WFPRC#"), WiFi.status() == WL_CONNECTED ? String(round(1.88 * (WiFi.RSSI() + 100)), 0) : F("0"));
        /* Bloque pie chart */
        s.replace(F("#SWFI#"), WiFi.status() == WL_CONNECTED ? String(round(1.88 * (WiFi.RSSI() + 100)), 0) : F("0"));
        s.replace(F("#PMEM#"), String(round(SPIFFS.usedBytes() * 100 / SPIFFS.totalBytes()), 0));
        s.replace(F("#ram#"), String(ESP.getFreeHeap() * 100 / ESP.getHeapSize()));
        s.replace(F("#cpu#"), String(TempCPU));
        /* Datos sensores y actuadores */
        s.replace(F("#led1#"), String(dormitorio1.leerEstadoLED()));
        s.replace(F("#led2#"), String(habitacion1.leerEstadoLED()));
        s.replace(F("#luzDorm#"), String(dormitorio1.leerLuz()));
        s.replace(F("#luzHab#"), String(habitacion1.leerLuz()));
        s.replace(F("#presDorm#"), String(dormitorio1.leerEstadoPresencia()));
        s.replace(F("#presHab#"), String(habitacion1.leerEstadoPresencia()));
        s.replace(F("#valorActDorm#"), String(dormitorio1.leerLuzAdec()));
        s.replace(F("#valorActHab#"), String(habitacion1.leerLuzAdec()));
        s.replace(F("#consumoDiaVerano#"), String(consumoVerano));
        s.replace(F("#consumoDiaInvierno#"), String(consumoInvierno));

        // Envia dados al navegador
        request->send(200, "text/html", s);  
      }else{
        request->send(500, "text/html", "<html><meta charset='UTF-8'><head><link href='bootstrap.min.css' rel='stylesheet' media='screen'><link rel='stylesheet' href='sweetalert2.min.css'>"
                                                                                 "<script src='jquery-1.9.1.min.js'><script src='bootstrap.min.js'></script></script><script src='sweetalert2.min.js'></script></head><body><script>"
                                                    "Swal.fire({title: 'Error!',"
                                                               " text: 'Error 500 Internal Server Error',"
                                                               " icon: 'error',"
                                                               " confirmButtonText: 'Cerrar'}).then((result) => {"
                                                                                                  "if (result.isConfirmed){"
                                                                                                       "window.location = '/';"
                                                                                                   "};"
                                                                                               "})"
                                                 "</script><body></html>");
        log(F("\nError: Config - ERROR leyendo el archivo"));
      }
    });
    /**********************************************/
    server.on("/configwifi", HTTP_GET, [](AsyncWebServerRequest *request){
        // Config
        File file = SPIFFS.open(F("/configwifi.html"), "r");
        if (file){
          file.setTimeout(100);
          String s = file.readString();
          file.close();
          // Atualiza el contenido al cargar
          s.replace(F("#id#"), id);
          s.replace(F("#ssid#"), ssid);
          //sección ap
          s.replace(F("#nameap#"), String(nameap));
          // Send data
          request->send(200, "text/html", s);
        }else{
          request->send(500, "text/html", "<html><meta charset='UTF-8'><head><link href='bootstrap.min.css' rel='stylesheet' media='screen'><link rel='stylesheet' href='sweetalert2.min.css'>"
                                                                                  "<script src='jquery-1.9.1.min.js'><script src='bootstrap.min.js'></script></script><script src='sweetalert2.min.js'></script></head><body><script>"
                                                      "Swal.fire({title: 'Error!',"
                                                                " text: 'Error 500 Internal Server Error',"
                                                                " icon: 'error',"
                                                                " confirmButtonText: 'Cerrar'}).then((result) => {"
                                                                                                    "if (result.isConfirmed){"
                                                                                                        "window.location = '/';"
                                                                                                    "};"
                                                                                                "})"
                                                  "</script><body></html>");
          log(F("\nError: Config - ERROR leyendo el archivo"));
        }
    });
    /**********************************************/
    /**********************************************/
    server.on("/confwifiSave", HTTP_POST, [](AsyncWebServerRequest *request){
        String response;
        StaticJsonDocument<300> doc;
        // Graba Configuración desde Config
        // Verifica número de campos recebidos
        // ESP32 envia 5 campos
        if (request->params() == 5){
          String s;
          // ID
          if(request->hasArg("id"))
          s = request->arg("id");
          s.trim();
          if (s == ""){
            s = deviceID();
          }
          strlcpy(id, s.c_str(), sizeof(id));
          // SSID
          if(request->hasArg("ssid"))
          s = request->arg("ssid");
          s.trim();
          if (s == ""){
            s = ssid;
          }
          strlcpy(ssid, s.c_str(), sizeof(ssid));
          // PW SSID
          if(request->hasArg("pw"))
          s = request->arg("pw");
          s.trim();
          if (s != ""){
            // Actualiza contraseña
            strlcpy(pw, s.c_str(), sizeof(pw));
          }
          // Nombre AP
          if(request->hasArg("nameap"))
          s = request->arg("nameap");
          s.trim();
          if (s != ""){
            // Atualiza ssid ap
            strlcpy(nameap, s.c_str(), sizeof(nameap));
          }
          // Contraseña AP
          if(request->hasArg("passwordap"))
          s = request->arg("passwordap");
          s.trim();
          if (s != ""){
            // Atualiza contraseña ap
            strlcpy(passwordap, s.c_str(), sizeof(passwordap));
          }
          // Graba configuracion
          if (configSave()){
            request->send(200, "text/html", "<html><meta charset='UTF-8'><head><link href='bootstrap.min.css' rel='stylesheet' media='screen'><link rel='stylesheet' href='sweetalert2.min.css'>"
                                            "<script src='jquery-1.9.1.min.js'><script src='bootstrap.min.js'></script></script><script src='sweetalert2.min.js'></script></head><body><script>"
                                                      "Swal.fire({title: 'Hecho!',"
                                                                " text: 'Configuración WIFI guardada, se requiere reiniciar el Equipo',"
                                                                " icon: 'success',"
                                                                " showCancelButton: true,"
                                                                " confirmButtonColor: '#3085d6',"
                                                                " cancelButtonColor: '#d33',"
                                                                " confirmButtonText: 'Si, reiniciar',"
                                                                " cancelButtonText: 'Cancelar',"
                                                                " reverseButtons: true"
                                                                " }).then((result) => {"
                                                                              "if (result.isConfirmed){"
                                                                                  "window.location = 'reboot';"
                                                                              "}else if ("
                                                                                  "result.dismiss === Swal.DismissReason.cancel"
                                                                                "){"
                                                                                  "history.back();"
                                                                                "}"
                                                                          "})"
                                                  "</script><body></html>");
          }else{
            request->send(200, "text/html", "<html><meta charset='UTF-8'><head><link href='bootstrap.min.css' rel='stylesheet' media='screen'><link rel='stylesheet' href='sweetalert2.min.css'>"
                                                                                  "<script src='jquery-1.9.1.min.js'><script src='bootstrap.min.js'></script></script><script src='sweetalert2.min.js'></script></head><body><script>"
                                                      "Swal.fire({title: 'Error!',"
                                                                " text: 'No se pudo guardar, Falló la configuración WIFI',"
                                                                " icon: 'error',"
                                                                " confirmButtonText: 'Cerrar'}).then((result) => {"
                                                                                                    "if (result.isConfirmed){"
                                                                                                        "history.back();"
                                                                                                    "};"
                                                                                                "})"
                                                  "</script><body></html>");
            log(F("\nError: ConfigSave - ERROR salvando Configuración"));
          }
        }else{
            request->send(200, "text/html", "<html><meta charset='UTF-8'><head><link href='bootstrap.min.css' rel='stylesheet' media='screen'><link rel='stylesheet' href='sweetalert2.min.css'>"
                                                                                  "<script src='jquery-1.9.1.min.js'><script src='bootstrap.min.js'></script></script><script src='sweetalert2.min.js'></script></head><body><script>"
                                                      "Swal.fire({title: 'Error!',"
                                                                " text: 'No se pudo guardar, Error de parámetros WIFI',"
                                                                " icon: 'error',"
                                                                " confirmButtonText: 'Cerrar'}).then((result) => {"
                                                                                                    "if (result.isConfirmed){"
                                                                                                        "history.back();"
                                                                                                    "};"
                                                                                                "})"
                                                  "</script><body></html>");
        }
    });
    /**********************************************/
    /**********************************************/
    server.on("/reconfig", HTTP_GET, [](AsyncWebServerRequest *request){
        // Reinicia Config
        configReset();
        // Graba la configuracion
        if (configSave()){
          request->send(200, "text/html", "<html><meta charset='UTF-8'><head><link href='bootstrap.min.css' rel='stylesheet' media='screen'><link rel='stylesheet' href='sweetalert2.min.css'>"
                                            "<script src='jquery-1.9.1.min.js'><script src='bootstrap.min.js'></script></script><script src='sweetalert2.min.js'></script></head><body><script>"
                                                    "Swal.fire({title: 'Hecho!',"
                                                                " text: 'Configuración restablecida, se requiere reiniciar el Equipo',"
                                                                " icon: 'success',"
                                                                " showCancelButton: true,"
                                                                " confirmButtonColor: '#3085d6',"
                                                                " cancelButtonColor: '#d33',"
                                                                " confirmButtonText: 'Si, reiniciar',"
                                                                " cancelButtonText: 'Cancelar',"
                                                                " reverseButtons: true"
                                                                " }).then((result) => {"
                                                                            "if (result.isConfirmed){"
                                                                                  "window.location = 'reboot';"
                                                                              "}else if ("
                                                                                "result.dismiss === Swal.DismissReason.cancel"
                                                                              "){"
                                                                                  "history.back();"
                                                                              "}"
                                                                          "})"
                                                  "</script><body></html>");
        }else{
          request->send(200, "text/html", "<html><meta charset='UTF-8'><head><link href='bootstrap.min.css' rel='stylesheet' media='screen'><link rel='stylesheet' href='sweetalert2.min.css'>"
                                                                                  "<script src='jquery-1.9.1.min.js'><script src='bootstrap.min.js'></script></script><script src='sweetalert2.min.js'></script></head><body><script>"
                                                    "Swal.fire({title: 'Error!',"
                                                                " text: 'Falló restablecer de la configuración',"
                                                                " icon: 'error',"
                                                                " confirmButtonText: 'Cerrar'}).then((result) => {"
                                                                                                  "if (result.isConfirmed){"
                                                                                                        "history.back();"
                                                                                                    "};"
                                                                                                "})"
                                                  "</script><body></html>");
          log(F("\nError: Reconfigurar - ERROR reinicio Configuración"));
        }
    });
    /**********************************************/
    server.onNotFound([](AsyncWebServerRequest *request) {
      request->send(404, "text/html", "<html><meta charset='UTF-8'><head><link href='bootstrap.min.css' rel='stylesheet' media='screen'><link rel='stylesheet' href='sweetalert2.min.css'>"
                                                                                  "<script src='jquery-1.9.1.min.js'><script src='bootstrap.min.js'></script></script><script src='sweetalert2.min.js'></script></head><body><script>"
                                                      "Swal.fire({title: 'Error 404!',"
                                                                " text: 'Página no encontrada',"
                                                                " icon: 'warning',"
                                                                " confirmButtonText: 'Cerrar'}).then((result) => {"
                                                                                                    "if (result.isConfirmed){"
                                                                                                        "history.back();"
                                                                                                    "};"
                                                                                                "})"
                                                  "</script><body></html>");
    });
    /**********************************************/
	  server.begin();
    log("\nInfo: HTTP server iniciado");
    /**********************************************/
    

}