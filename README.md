# ESP32_BloquesConstruccion

## 🧱 Resumen


## 🧱 Qué se necesita 

+ PMicrocontrolador ESP32 con WiFi.
+ Dispositivo de compilación y carga del programa (ordenador).
+ 2 sensores infrarrojos OKY3127 (típicos para Arduino).
+ 2 fotorresistencias de 5 mm + 2 resistencias de 10 kΩ.
+ 2 LED de 5 mm de diámetro + 2 resistencias de 220 Ω.

## 🧱 Instalación
1. Se requiere la instalación del Visual Studio Code ( https://code.visualstudio.com/docs/setup/windows ) y de la herramienta PlatformIO ( https://platformio.org/install/ide?install=vscode ).
2. Una vez instalado el SW, se debe descargar el proyecto disponible en el repositorio. Pulsar el menú extensible Code y hacer click en Download ZIP.
3. Se importa el proyecto pulsando "Import Arduino Project" en la interfaz de PlatformIO y se elige el proyecto y la placa "DOIT ESP32 DEVKIT V1".
4. En las líneas 39 y 40 del archivo main.cpp de la carpeta src, se deben poner los pines en los que se van a conectar los sensores y actuadores posteriormente. Para ello, se debe tener en cuenta el orden en que se mandan los datos en los argumentos de la función. Si se eliminan estas líneas, el sistema adjudica valores por defecto en el archivo ClaseDormitorio.h y ClaseHabitacion.h.
5. En la función configReset() del archivo Config.h (carpeta include), se deben poner el nombre y contraseña de la red WiFi disponible, así como una contraseña para el punto de acceso WiFi que la ESP32 crea. Los nuevos valores deben sustituir a los nombres entre comillas.
6. Para cargar los archivos de la carpeta data, se debe pulsar la herramienta Upload Filesystem Image de PlatformIO (pulsando su ícono a la izquierda salen todas las opciones del programa).
7. Se compila el proyecto.
8. Se conectan los componentes de la siguiente forma:
   https://raw.githubusercontent.com/clararubio20/ESP32_BloquesConstruccion/main/Im%C3%A1genes%20de%20la%20p%C3%A1gina/circuito.png
10. Se carga el proyecto en la placa y se abre el puerto serie. Si se han puesto las credenciales de la red WiFi correctamente, debería aparecer la dirección IP del WiFi (número de 12 dígitos separado por puntos).
11. Se este número y pega en la barra de búsqueda del navegador.
12. ¡El programa ya está listo para ser usado!

## 🧱 Uso
En el video XXXX se muestra el uso que se le puede dar a la aplicación. ¡Pregunta cualquier duda o interacciona con la comunidad!


## 🧱 Autoría

Este proyecto ha sido realizado por Clara Rubio Almagro para el Trabajo Fin de Grado de Ingeniería de Sistemas Electrónicos de la Universidad de Málaga, bajo la supervisión de Cristina Urdiales García.

## 🧱 Licencia
Este proyecto está licenciado bajo la Licencia GPU. Consulte el archivo LICENSE para obtener más información.
