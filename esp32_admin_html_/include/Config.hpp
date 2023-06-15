/*
* Archivo creado por: Clara Rubio Almagro
* Fecha de la ultima modificación: 15/06/2023
* Trabajo Fin de Grado
* Titulación: Sistemas electrónicos
* Universidad de Málaga
*/

/* RESETEO DE VALORES */
void configReset(){
    /* CLIENTE */
    strcpy(id,"id");
    strcpy(ssid,"nombre");
    strcpy(pw,"contraseña");
    /* AP */
    strlcpy(nameap, deviceID().c_str(), sizeof(nameap));
    strlcpy(passwordap, "contraseñaAP", sizeof(passwordap));
}

/* LECTURA DE VALORES */
boolean configRead(){
    // Lee la configuración
    StaticJsonDocument<JSON_CONFIG> jsonConfig;
    File file = SPIFFS.open("/Config.json", "r");
    if (deserializeJson(jsonConfig, file)){
        // Si falla la lectura inicia valores por defecto
        configReset();
        log("\nError: Falló la lectura de la configuración, iniciando valores por defecto");
        return false;
    }else{
        /* CLIENTE */
        strlcpy(id, jsonConfig["id"] | "", sizeof(id));
        strlcpy(ssid, jsonConfig["ssid"] | "", sizeof(ssid));
        strlcpy(pw, jsonConfig["pw"] | "", sizeof(pw));
        /* AP */
        strlcpy(nameap, jsonConfig["nameap"] | "", sizeof(nameap));
        strlcpy(passwordap, jsonConfig["passwordap"] | "", sizeof(passwordap));
        file.close();
        log("\nInfo: Lectura correcta configuración general");
        return true;
    }
}

boolean configSave(){
    // Graba configuración
    StaticJsonDocument<JSON_CONFIG> jsonConfig;
    File file = SPIFFS.open("/Config.json", "w+");
    if (file){
        /* CLIENTE */
        jsonConfig["id"] = id;
        jsonConfig["ssid"] = ssid;
        jsonConfig["pw"] = pw;
        /* AP */
        jsonConfig["nameap"] = nameap;
        jsonConfig["passwordap"] = passwordap;
        serializeJsonPretty(jsonConfig, file);
        file.close();
        log("\nInfo: Grabando configuración general");
        return true;
    }else{
      log("\nError: Falló el grabado de la configuración general");
      return false;
    }    
}
