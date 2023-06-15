/*
* Archivo creado por: Clara Rubio Almagro
* Fecha de la ultima modificación: 15/06/2023
* Trabajo Fin de Grado
* Titulación: Sistemas electrónicos
* Universidad de Málaga
* Este archivo guarda las variables globales del programa
*/

// Variable para no bloquear la reconexion del MQTT
long lastSendWS = 0; 
// Tamaño del Objeto JSON
const size_t JSON_CONFIG = JSON_OBJECT_SIZE(5) + 500;
// ID del dispositivo           
char id[30];
// Red WiFi
char ssid[30];
// Contraseña da Red WiFi                  
char pw[30];
// Para ssid AP
char nameap[31]; 
// Para ssid AP Password       
char passwordap[63];   
// Nuevas Variables declaradas
// Variable para Temperatura de CPU
float TempCPU; 
//nuevas variables
// Tamaño del mensaje 
char payload[255];
char botonLed[30];  


/* Sensor Temp Interno CPU */
//Para ESP32 temperatura del CPU
#ifdef __cplusplus
extern "C"
{
#endif
    uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();


/* Instancias */
const byte DNSSERVER_PORT = 53;
DNSServer dnsServer;


/* VARIABLES DE ESCRITURA Y LECTURA DE SENSORES Y ACTUADORES*/
bool modo = false; // En false modo manual
float consumoVerano = 8469.4;
float consumoInvierno = 7734.2;

/* HABITACIONES */
ClaseDormitorio dormitorio1;
ClaseHabitacion habitacion1;

