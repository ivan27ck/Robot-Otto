#include "librerias/WiFiWebServer.h"
#include "librerias/ServoControl.h"


// Variables globales
WebServer server(80);
bool startMovement = false;
bool startMovement2 = false;
bool isInitialized = false;

const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>OTTO</title>
    <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@300;400;500&display=swap" rel="stylesheet">
    <link rel="icon" href="https://i.postimg.cc/cCkzW2ty/Robot-Otto.png" type="image/x-icon">
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            height: 100vh;
            background-color: #1F3B4D;
            background-image: url('https://i.postimg.cc/Kcrzk8Dm/Space-Background.jpg');
            background-repeat: no-repeat;
            background-size: cover;
        }

        button {
            padding: 15px 30px;
            font-size: 18px;
            font-weight: bold;
            color: #fff;
            background-color: #333;
            border: none;
            border-radius: 25px;
            cursor: pointer;
            transition: all 0.2s ease;
            box-shadow: 0 0 10px rgba(255, 0, 255, 0.4), 0 0 5px rgba(255, 132, 0, 0.968);
            outline: none;
            text-shadow: 0 0 10px rgba(255, 255, 255, 0.4);
            margin-top: 10px;
        }

        .robot-container {
            display: flex;
            flex-direction: column;
            align-items: center;
            background-color: #444;
            width: 300px;
            height: 400px;
            position: relative;
        }

        .eye {
            position: absolute;
            width: 80px;
            height: 80px;
            background-color: black;
            border-radius: 50%;
            box-shadow: 0 0 30px rgba(3, 237, 77, 0.7);
            bottom: 50px;
            animation: 0.2s BeProud ease alternate infinite;
        }

        .eye::after {
            content: '';
            position: absolute;
            top: 25%;
            left: 25%;
            width: 30px;
            height: 30px;
            background-color: white;
            border-radius: 50%;
            box-shadow: 0 0 20px rgba(4, 225, 30, 0.8);
            animation: 0.2s BeProud ease alternate infinite;
        }

        .eye.left {
            top: 84px;
            left: 5px;
        }

        .eye.right {
            top: 84px;
            right: 5px;

        }

        .control-buttons {
            position: absolute;
            bottom: 40px;
            left: 50%;
            transform: translateX(-50%);
            display: flex;
            gap: 10px;
        }

        .control-buttons button {
            padding: 10px 20px;
            background-color: black;
            color: white;
            border: none;
            border-radius: 70px;
            cursor: pointer;
            font-size: 16px;
            box-shadow: 0px 10px 20px rgba(67, 63, 130, 0.738);
        }

        button:hover {
            color: #000;
            background-color: rgb(255, 128, 0);
            box-shadow: 0 0 10px rgba(255, 170, 0, 0.8), 0 0 15px rgba(0, 0, 255, 0.8);
        }
    </style>
</head>
<body>

    <div class="robot-container" id="robot-container">
        <div class="eye left"></div>
        <div class="eye right"></div>
        <img src="https://i.postimg.cc/cCkzW2ty/Robot-Otto.png" alt="Robot Otto" class="robot-image">
        <div class="control-buttons">
            <button onclick="sendCommand('St'); changeEyeColor('black', '#FFECB3', '0 0 20px rgba(255, 255, 0, 0.7)', '0 0 15px rgba(255, 255, 153, 0.8)')">bailar</button>
            <button onclick="sendCommand('ba'); changeEyeColor('black', '#B6FFB6', '0 0 20px rgba(0, 255, 0, 0.7)', '0 0 15px rgba(58, 217, 58, 0.8)')">caminar</button>
            <button onclick="sendCommand('Sp'); changeEyeColor('black', '#ffffff', '0 0 30px rgba(237, 10, 3, 0.7)', '0 0 20px rgba(225, 4, 4, 0.8)');">Detener</button>
        </div>
    </div>

    <script>
    function sendCommand(command) {
        fetch('http://10.214.106.120/command?command=' + command)
            .then(response => response.text())
            .then(data => {
                alert("Comando enviado: " + data);
            })
            .catch(error => {

            });
    }

    function changeEyeColor(eyeColor, pupilColor, eyeShadow, pupilShadow) {

    const eyes = document.querySelectorAll('.eye');
    eyes.forEach(eye => {
        eye.style.backgroundColor = eyeColor;
        eye.style.boxShadow = eyeShadow;
    });

    const style = document.createElement('style');
    style.innerHTML = `
        .eye::after {
            background-color: ${pupilColor} !important;
            box-shadow: ${pupilShadow} !important;
        }
    `;
    document.head.appendChild(style);
}




    </script>
</body>
</html>


)rawliteral";

// Configuración de WiFi
void setupWiFi(const char* ssid, const char* password, IPAddress local_IP, IPAddress gateway, IPAddress subnet) {
    if (!WiFi.config(local_IP, gateway, subnet)) {
        Serial.println("Error al configurar IP estática");
    }
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectado a la red WiFi");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());

    if (!MDNS.begin("ottoInventores")) {
        Serial.println("Error al configurar mDNS");
        return;
    }
    Serial.println("mDNS configurado. Puedes acceder usando http://mirobot.local");
}

// Configuración del servidor web
void setupWebServer() {
    server.on("/", handleRoot);
    server.on("/command", handleCommand);
    server.begin();
    Serial.println("Servidor web iniciado");
}

// Controlador de la página principal
void handleRoot() {
    server.send(200, "text/html", webpage);
}

// Controlador de comandos
void handleCommand() {
    if (server.hasArg("command")) {
        String command = server.arg("command");
        Serial.println("Comando recibido: " + command);

        if (command == "Sp") {
            startMovement = false;
            startMovement2 = false;
            // Detener los servos
            servoMotorInf1.write(90);
            servoMotorInf2.write(90);
            servoMotorSup1.write(90);
            servoMotorSup2.write(90);
        } else if (command == "St") {
            startMovement = true;
            isInitialized = false;
        } else if (command == "ba") {
            startMovement2 = true;
            isInitialized = false;
        } else {
            server.send(400, "text/plain", "Comando no reconocido");
        }
    } else {
        server.send(400, "text/plain", "Comando no encontrado");
    }
}
