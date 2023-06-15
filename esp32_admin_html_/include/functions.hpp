/*
* Archivo creado por: Clara Rubio Almagro
* Fecha de la ultima modificación: 15/06/2023
* Trabajo Fin de Grado
* Titulación: Sistemas electrónicos
* Universidad de Málaga
* Este archivo guarda las funciones globales del programa
*/

/* IMPRIME POR PUERTO SERIE */
void log(String s){
    Serial.println(s);
}

// Devuelve IPAddress en formato "n.n.n.n" de IP a String
String ipStr(const IPAddress &ip){
    String sFn = "";
    for (byte bFn = 0; bFn < 3; bFn++)
    {
        sFn += String((ip >> (8 * bFn)) & 0xFF) + ".";
    }
    sFn += String(((ip >> 8 * 3)) & 0xFF);
    return sFn;    
}

// De HEX a String
String hexStr(const unsigned long &h, const byte &l = 8){
    String s;
    s= String(h, HEX);
    s.toUpperCase();
    s = ("00000000" + s).substring(s.length() + 8 -l);
    return s;
}

// Create a Unique ID from MAC address
String idUnique(){
    // Devuelve los ultimos 4 Bytes del MAC rotados
    char idunique[15];
    uint64_t chipid = ESP.getEfuseMac();
    uint64_t chip = (uint16_t)(chipid >> 32);
    snprintf(idunique, 15, "%04X", chip);
    return idunique;
}

// ID del Dispositivo para La Base de Datos
const String device_id = hexStr(ESP.getEfuseMac()) + "CE" + String(idUnique()); 
// ESP32 utiliza funcion getEfuseMac()
String deviceID(){
    return "ESP32" + hexStr(ESP.getEfuseMac()) + String(idUnique());
}

/* CONFIGURACIÓN DE PINES */
void configPines(){
    dormitorio1.configPines();
    habitacion1.configPines();
}

/* MÁQUINA DE ESTADOS DEL DORMITORIO */
void dormitorio()
{
    if (dormitorio1.leerHorario() == '0')
    {
        if (dormitorio1.leerEstadoPresencia() == '1')
        {
            if (dormitorio1.leerLuz() < dormitorio1.leerLuzAdec())
            {
                dormitorio1.encederLED();
            }
            else
            {
                dormitorio1.apagarLED();
            }
        }
        else
        {
            dormitorio1.apagarLED();
        }
    }
}

/* MÁQUINA DE ESTADOS DE LA HABITACION */
void habitacion()
{
    if (habitacion1.leerEstadoPresencia() == '1')
        {
            if (habitacion1.leerLuz() < habitacion1.leerLuzAdec())
        {
            habitacion1.encederLED();
        }
        else
        {
            habitacion1.apagarLED();
        }
    }
    else
    {
        habitacion1.apagarLED();
    }
}

