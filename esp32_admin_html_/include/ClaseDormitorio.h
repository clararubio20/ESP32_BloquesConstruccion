/*
* Archivo creado por: Clara Rubio Almagro
* Fecha de la ultima modificación: 15/06/2023
* Trabajo Fin de Grado
* Titulación: Sistemas electrónicos
* Universidad de Málaga
*/

class ClaseDormitorio
{
    private:
        unsigned int pinLED, pinIFR, pinLDR, luzAdec;
        char estadoLED, estadoPresencia, esNoche;
        float luz;
    public:
        ClaseDormitorio();
        ~ClaseDormitorio();
        void configuracionInicial(unsigned int pLED,unsigned int pIFR,unsigned int pLDR, unsigned int luzA, char estLED, char estPresencia, char Noche, float l);
        void configPines();
        void encederLED();
        void apagarLED();
        void cambiarEstadoLED(char estado);
        void cambiarEstadoPresencia(char estado);
        void cambiarHorario(char estado);
        void cambiarLuz(float l);
        void cambiarLuzAdec(unsigned int l);
        unsigned int leerLuzAdec();
        float leerLuz();
        char leerEstadoLED();
        char leerEstadoPresencia();
        char leerHorario();
        unsigned int leerPinLDR();
        unsigned int leerPinIFR();
};

ClaseDormitorio::ClaseDormitorio()
{
    pinLED = 12;
    pinIFR = 27;
    pinLDR = 35;
    luzAdec = 50;
    estadoLED = '0';
    estadoPresencia = '0';
    esNoche = '0';
    luz = 0;
}

ClaseDormitorio::~ClaseDormitorio(){}

void ClaseDormitorio::configuracionInicial(unsigned int pLED,unsigned int pIFR,unsigned int pLDR, unsigned int luzA, char estLED, char estPresencia, char Noche,  float l)
{
    pinLED = pLED;
    pinIFR = pIFR;
    pinLDR = pLDR;
    luzAdec = luzA;
    estadoLED = estLED;
    estadoPresencia = estPresencia;
    luz = l;
    esNoche = Noche;
}

void ClaseDormitorio::configPines()
{
    pinMode(pinLED, OUTPUT);
    pinMode(pinIFR, INPUT);
    pinMode(pinLDR, INPUT);
}

void ClaseDormitorio::encederLED()
{
    digitalWrite(pinLED, HIGH);
    estadoLED = '1';
}

void ClaseDormitorio::apagarLED()
{
    digitalWrite(pinLED, LOW);
    estadoLED = '0';
}

void ClaseDormitorio::cambiarEstadoLED(char estado)
{
    estadoLED = estado;
}

void ClaseDormitorio::cambiarEstadoPresencia(char estado)
{
    estadoPresencia = estado;
}

void ClaseDormitorio::cambiarHorario(char estado)
{
    esNoche = estado;
}

void ClaseDormitorio::cambiarLuz(float l)
{
    luz = l;
}

void ClaseDormitorio::cambiarLuzAdec(unsigned int l)
{
    luzAdec = l;
}

unsigned int ClaseDormitorio::leerLuzAdec()
{
    return luzAdec;
}

float ClaseDormitorio::leerLuz()
{
    return luz;
}

char ClaseDormitorio::leerEstadoLED()
{
    return estadoLED;
}

char ClaseDormitorio::leerEstadoPresencia()
{
    return estadoPresencia;
}

char ClaseDormitorio::leerHorario()
{
    return esNoche;
}

unsigned int ClaseDormitorio::leerPinLDR()
{
    return pinLDR;
}

unsigned int ClaseDormitorio::leerPinIFR()
{
    return pinIFR;
}

