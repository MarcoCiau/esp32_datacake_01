# 🔥 ESP32 + Datacake IoT Dashboard

Proyecto de IoT que envía datos de sensores desde un ESP32 a Datacake para visualización en tiempo real. Perfecto para crear dashboards profesionales en menos de 30 segundos.

## 📋 Descripción

Este proyecto muestra cómo conectar un ESP32 a Datacake para enviar datos de sensores (temperatura, batería, humedad y CO2) y visualizarlos en un dashboard en tiempo real.

## 🎥 Video Tutorial

Visita mi canal de YouTube [@mciau_tech](https://www.youtube.com/@mciau_tech) para ver el tutorial completo sobre cómo crear un dashboard en Datacake.

## 🚀 Características

- ✅ Conexión WiFi automática
- ✅ Envío de datos cada 10 segundos
- ✅ Datos simulados de sensores (temperatura, batería, humedad, CO2)
- ✅ Integración con Datacake API
- ✅ Formato JSON estructurado
- ✅ Logging en Serial Monitor

## 📦 Componentes Necesarios

- ESP32 (cualquier variante)
- Cable USB para programación
- Conexión WiFi
- Cuenta en [Datacake](https://datacake.co)

## ⚙️ Configuración

### 1. Instalar Dependencias

Este proyecto usa PlatformIO. Las dependencias se instalan automáticamente, pero asegúrate de tener:

- `WiFi` (incluido en ESP32 Arduino Core)
- `HTTPClient` (incluido en ESP32 Arduino Core)
- `ArduinoJson` (se instala automáticamente)

### 2. Configurar WiFi

Edita `src/main.cpp` y actualiza tus credenciales WiFi:

```cpp
const char* ssid = "TU_WIFI_SSID";
const char* password = "TU_WIFI_PASSWORD";
```

### 3. Configurar Datacake

1. Crea una cuenta en [Datacake](https://datacake.co)
2. Crea un nuevo dispositivo
3. Agrega los siguientes campos:
   - `temperature` (Float)
   - `battery` (Float)
   - `humidity` (Float)
   - `co2` (Integer)
4. Copia la URL de integración API de tu dispositivo
5. Actualiza la variable `serverName` en `src/main.cpp`:

```cpp
const char* serverName = "https://api.datacake.co/integrations/api/TU_URL_AQUI";
```

### 4. Obtener Device ID

Reemplaza el Device ID en el código:

```cpp
jsonDoc["device"] = "TU_DEVICE_ID_AQUI";
```

## 📊 Datos Enviados

El ESP32 envía los siguientes datos simulados:

| Campo | Tipo | Rango | Descripción |
|-------|------|-------|-------------|
| `temperature` | Float | 20.0 - 35.0 °C | Temperatura ambiente |
| `battery` | Float | 3.00 - 4.20 V | Voltaje de batería |
| `humidity` | Float | 30.0 - 90.0 % | Humedad relativa |
| `co2` | Integer | 400 - 2000 ppm | Concentración de CO2 |

## 🎨 Crear Dashboard en Datacake

1. Ve a tu dispositivo en Datacake
2. Abre la sección "Dashboard"
3. Agrega widgets:
   - **Value Widget**: Para mostrar valores actuales
   - **Chart Widget**: Para ver el historial de datos
4. Selecciona los campos correspondientes
5. ¡Listo! Tu dashboard está funcionando

## 📝 Estructura del Proyecto

```
esp32_datacake_01/
├── src/
│   └── main.cpp          # Código principal
├── platformio.ini        # Configuración de PlatformIO
└── README.md             # Este archivo
```

## 🔧 Compilar y Subir

1. Abre el proyecto en PlatformIO
2. Conecta tu ESP32 por USB
3. Compila y sube el código
4. Abre el Serial Monitor (115200 baud)

## 📡 Formato JSON

El ESP32 envía datos en el siguiente formato:

```json
{
  "device": "4e294ca5-94e0-49db-b2bf-7b87e01f723a",
  "temperature": 25.3,
  "battery": 3.85,
  "humidity": 65.2,
  "co2": 450
}
```

## 🐛 Solución de Problemas

### No se conecta a WiFi
- Verifica que las credenciales sean correctas
- Asegúrate de que el ESP32 esté dentro del rango del router

### Error al enviar datos
- Verifica que la URL de Datacake sea correcta
- Revisa que el Device ID sea válido
- Comprueba que los campos existan en Datacake

### No aparecen datos en el dashboard
- Espera unos segundos para que los datos se procesen
- Verifica que los nombres de los campos coincidan exactamente

## 📚 Recursos

- [Documentación de Datacake](https://docs.datacake.co)
- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
- [ArduinoJson Documentation](https://arduinojson.org)

## 🤝 Contribuciones

¡Las contribuciones son bienvenidas! Si tienes sugerencias o mejoras, no dudes en abrir un issue o pull request.

## 📺 Más Proyectos IoT

Visita [@mciau_tech](https://www.youtube.com/@mciau_tech) en YouTube para más proyectos de IoT, tutoriales y contenido técnico.

## 📄 Licencia

Este proyecto es de código abierto y está disponible para uso educativo y personal.

---

**Creado con ❤️ para la comunidad IoT**

