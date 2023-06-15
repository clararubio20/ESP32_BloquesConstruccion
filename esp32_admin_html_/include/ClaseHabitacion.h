/*
* Archivo creado por: Clara Rubio Almagro
* Fecha de la ultima modificación: 15/06/2023
* Trabajo Fin de Grado
* Titulación: Sistemas electrónicos
* Universidad de Málaga
*/

class ClaseHabitacion
{
    private:
        unsigned int pinLED, pinIFR, pinLDR, luzAdec;
        char estadoLED, estadoPresencia;
        float luz;
    public:
        ClaseHabitacion();
        ~ClaseHabitacion();
        void configuracionInicial(unsigned int pLED,unsigned int pIFR,unsigned int pLDR, unsigned int luzA, char estLED, char estPresencia,  float l);
        void configPines();
        void encederLED();
        void apagarLED();
        void cambiarEstadoLED(char estado);
        void cambiarEstadoPresencia(char estado);
        void cambiarLuz(float l);
        void cambiarLuzAdec(unsigned int l);
        unsigned int leerLuzAdec();
        float leerLuz();
        char leerEstadoLED();
        char leerEstadoPresencia();
        unsigned int leerPinLDR();
        unsigned int leerPinIFR();
};

ClaseHabitacion::ClaseHabitacion()
{
    pinLED = 13;
    pinIFR = 33;
    pinLDR = 34;
    luzAdec = 50;
    estadoLED = '0';
    estadoPresencia = '0';
    luz = 0;
}

ClaseHabitacion::~ClaseHabitacion(){}

void ClaseHabitacion::configuracionInicial(unsigned int pLED,unsigned int pIFR,unsigned int pLDR, unsigned int luzA, char estLED, char estPresencia,  float l)
{
    pinLED = pLED;
    pinIFR = pIFR;
    pinLDR = pLDR;
    luzAdec = luzA;
    estadoLED = estLED;
    estadoPresencia = estPresencia;
    luz = l;
}

void ClaseHabitacion::configPines()
{
    pinMode(pinLED, OUTPUT);
    pinMode(pinIFR, INPUT);
    pinMode(pinLDR, INPUT);
}

void ClaseHabitacion::encederLED()
{
    digitalWrite(pinLED, HIGH);
    estadoLED = '1';
}

void ClaseHabitacion::apagarLED()
{
    digitalWrite(pinLED, LOW);
    estadoLED = '0';
}

void ClaseHabitacion::cambiarEstadoLED(char estado)
{
    estadoLED = estado;
}

void ClaseHabitacion::cambiarEstadoPresencia(char estado)
{
    estadoPresencia = estado;
}

void ClaseHabitacion::cambiarLuz(float l)
{
    luz = l;
}

void ClaseHabitacion::cambiarLuzAdec(unsigned int l)
{
    luzAdec = l;
}

unsigned int ClaseHabitacion::leerLuzAdec()
{
    return luzAdec;
}

float ClaseHabitacion::leerLuz()
{
    return luz;
}

char ClaseHabitacion::leerEstadoLED()
{
    return estadoLED;
}

char ClaseHabitacion::leerEstadoPresencia()
{
    return estadoPresencia;
}

unsigned int ClaseHabitacion::leerPinLDR()
{
    return pinLDR;
}

unsigned int ClaseHabitacion::leerPinIFR()
{
    return pinIFR;
}
