# Proyecto Robot Otto - Control por WiFi

Este es un proyecto para controlar un robot Otto basado en un ESP32 mediante una interfaz web y un sensor ultrasónico para detección de obstáculos. El robot puede caminar, bailar y detenerse, todo controlado remotamente desde una página web.

## Estructura del Proyecto

El proyecto consta de 5 archivos organizados en dos carpetas:

- **Carpeta principal**:
  - `main.ino`: Archivo principal de Arduino que inicializa el sistema y ejecuta la lógica del robot.
- **Carpeta `librerias`**:
  - `ServoControl.h`: Cabecera para el control de los servomotores.
  - `ServoControl.cpp`: Implementación del control de servos.
  - `WiFiWebServer.h`: Cabecera para la configuración del WiFi y el servidor web.
  - `WiFiWebServer.cpp`: Implementación del servidor web y la interfaz HTML.

## Requisitos

### Hardware
- ESP32 (cualquier modelo con soporte PWM y WiFi).
- 4 servomotores (SG90 o similares):
  - `servoMotorInf1` (pin 21): Pierna inferior izquierda.
  - `servoMotorInf2` (pin 22): Pierna inferior derecha.
  - `servoMotorSup1` (pin 23): Pierna superior izquierda.
  - `servoMotorSup2` (pin 19): Pierna superior derecha.
- Sensor ultrasónico HC-SR04:
  - Trigger (pin 12).
  - Echo (pin 13).
- Conexión WiFi (red configurada en el código).

### Software
- Arduino IDE con soporte para ESP32.
- Librerías necesarias (instálalas desde el gestor de librerías del IDE):
  - `ESP32Servo` (para controlar los servos).
  - `WiFi` (incluida con el soporte ESP32).
  - `WebServer` (para el servidor web).
  - `ESPmDNS` (para acceso vía `ottoInventores.local`).

## Configuración Inicial

1. **Clonar el repositorio**:
   ```bash
   git clone <URL_DEL_REPOSITORIO>

2. Abrir el proyecto:
Abre main.ino en el Arduino IDE. Asegúrate de que los archivos de la carpeta librerias estén en el mismo directorio.

3. Configurar
-Configurar WiFi:
-Edita las siguientes líneas en main.ino con los datos de tu red:
-const char* ssid = "iCUCEI"; // Nombre de tu red WiFi
-const char* password = "";   // Contraseña de tu red (si no hay, déjalo vacío)
-La IP estática está configurada como 10.214.106.120. Si tu red usa otro rango, modifica estas líneas del archivo main:
IPAddress local_IP(10, 214, 106, 120);
IPAddress gateway(10, 214, 127, 254);
IPAddress subnet(255, 255, 192, 0);

Cómo Funciona
Componentes Principales
Servos: Controlados por ServoControl.cpp. Los movimientos se definen en moveServo y se ejecutan en main.ino.
WiFi y Web: Configurados en WiFiWebServer.cpp. La página HTML está embebida en el código y responde a comandos enviados por HTTP.
Sensor Ultrasónico: Detecta obstáculos a menos de 15 cm y detiene al robot automáticamente.
Comandos Web
Bailar (St): Activa una secuencia de movimientos repetitivos en los servos.
Caminar (ba): Simula pasos alternando las piernas.
Detener (Sp): Para todos los movimientos y centra los servos en 90°.
