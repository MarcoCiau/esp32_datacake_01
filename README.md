# 🔥 ESP32 + Datacake IoT Dashboard

Proyecto de IoT que envía datos de sensores desde un ESP32 a Datacake para visualización en tiempo real. Perfecto para crear dashboards profesionales en menos de 30 segundos.

## 📋 Descripción

Este proyecto muestra cómo conectar un ESP32 a Datacake para enviar datos de sensores (temperatura, humedad, presión y altitud) y visualizarlos en un dashboard en tiempo real. Soporta tanto datos simulados como sensores reales BME280.

## 🎥 Video Tutorial

Visita mi canal de YouTube [@mciau_tech](https://www.youtube.com/@mciau_tech) para ver el tutorial completo sobre cómo crear un dashboard en Datacake.

## 🚀 Características

- ✅ Conexión WiFi automática
- ✅ Envío de datos cada 10 segundos
- ✅ Soporte para datos simulados o sensor BME280 real
- ✅ Integración con Datacake API
- ✅ Formato JSON estructurado
- ✅ Logging en Serial Monitor
- ✅ Configuración centralizada de credenciales
- ✅ Módulo BME280 con funciones C simples (no OOP)

## 📦 Componentes Necesarios

- ESP32 (cualquier variante)
- Cable USB para programación
- Conexión WiFi
- Cuenta en [Datacake](https://datacake.co)
- (Opcional) Sensor BME280 para datos reales

## ⚙️ Configuración

### 1. Instalar Dependencias

Este proyecto usa PlatformIO. Las dependencias se instalan automáticamente:

- `WiFi` (incluido en ESP32 Arduino Core)
- `HTTPClient` (incluido en ESP32 Arduino Core)
- `ArduinoJson` (se instala automáticamente)
- `Adafruit BME280 Library` (se instala automáticamente si usas sensor real)

### 2. Configurar Credenciales

Edita `include/credentials.h` y actualiza tus credenciales:

```cpp
// WiFi Credentials
#define WIFI_SSID "TU_WIFI_SSID"
#define WIFI_PASSWORD "TU_WIFI_PASSWORD"

// Datacake Configuration
#define DATACAKE_SERVER_URL "https://api.datacake.co/integrations/api/TU_URL_AQUI"
#define DATACAKE_DEVICE_ID "TU_DEVICE_ID_AQUI"
```

### 3. Configurar Datacake

1. Crea una cuenta en [Datacake](https://datacake.co)
2. Crea un nuevo dispositivo
3. Agrega los siguientes campos:
   - `device` (String)
   - `temperature` (Float)
   - `humidity` (Float)
   - `pressure` (Float)
   - `altitude` (Float)
4. Copia la URL de integración API de tu dispositivo
5. Actualiza `DATACAKE_SERVER_URL` y `DATACAKE_DEVICE_ID` en `include/credentials.h`

### 4. Seleccionar Modo: Simulado o Sensor Real

#### Opción A: Usar Datos Simulados

Para usar datos simulados, descomenta la línea del build flag en `platformio.ini`:

```ini
build_flags =
    -DUSE_SIMULATED_DEVICE  ; Descomentado = usa datos simulados
```

**Nota:** Con esta configuración, no necesitas conectar ningún sensor físico.

#### Opción B: Usar Sensor BME280 Real (Por Defecto)

El proyecto viene configurado para usar el sensor BME280 real. En `platformio.ini`, la línea del build flag está comentada:

```ini
build_flags =
    ; -DUSE_SIMULATED_DEVICE  ; Comentado = usa sensor BME280 real
```

1. Conecta el sensor BME280 al ESP32:
   - **VCC** → 3.3V
   - **GND** → GND
   - **SDA** → GPIO 21
   - **SCL** → GPIO 22

2. El sensor intentará automáticamente ambos I2C addresses (0x76 y 0x77)

**Resumen:**
- **Flag comentado** (`; -DUSE_SIMULATED_DEVICE`) = **Sensor BME280 real** (modo actual)
- **Flag descomentado** (`-DUSE_SIMULATED_DEVICE`) = **Datos simulados**

## 📊 Datos Enviados

El ESP32 envía los siguientes datos según el modo configurado:

| Campo | Tipo | Rango (Simulado) | Descripción |
|-------|------|------------------|-------------|
| `device` | String | - | ID del dispositivo en Datacake |
| `temperature` | Float | 20.0 - 35.0 °C | Temperatura ambiente |
| `humidity` | Float | 30.0 - 90.0 % | Humedad relativa |
| `pressure` | Float | 980.0 - 1020.0 hPa | Presión atmosférica |
| `altitude` | Float | 40.0 - 60.0 m | Altitud calculada |

**Nota:** Si usas el sensor BME280 real, los valores serán los medidos por el sensor.

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
├── include/
│   └── credentials.h     # Credenciales WiFi y Datacake
├── lib/
│   └── bme280/
│       ├── bme280.h      # Header del módulo BME280
│       └── bme280.cpp     # Implementación del módulo BME280
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
  "device": "aae610a1-fdcf-4b32-b422-314449b3693a",
  "temperature": 23.5,
  "humidity": 65.2,
  "pressure": 1013.25,
  "altitude": 520.8
}
```

**Campos:**
- `device`: ID del dispositivo en Datacake (String)
- `temperature`: Temperatura en grados Celsius (Float)
- `humidity`: Humedad relativa en porcentaje (Float)
- `pressure`: Presión atmosférica en hectopascales (Float)
- `altitude`: Altitud calculada en metros (Float)

## 🐛 Solución de Problemas

### No se conecta a WiFi
- Verifica que las credenciales en `include/credentials.h` sean correctas
- Asegúrate de que el ESP32 esté dentro del rango del router
- Revisa el Serial Monitor para mensajes de error

### Error al enviar datos
- Verifica que la URL de Datacake en `include/credentials.h` sea correcta
- Revisa que el Device ID sea válido
- Comprueba que los campos existan en Datacake con los nombres exactos

### No aparecen datos en el dashboard
- Espera unos segundos para que los datos se procesen
- Verifica que los nombres de los campos coincidan exactamente
- Revisa el Serial Monitor para ver qué JSON se está enviando

### Error con sensor BME280
- Verifica las conexiones del sensor (VCC, GND, SDA, SCL)
- Asegúrate de que el sensor esté alimentado con 3.3V
- Comprueba que el build flag `USE_SIMULATED_DEVICE` esté comentado en `platformio.ini`
- El sensor intentará ambos I2C addresses (0x76 y 0x77) automáticamente
- Revisa el Serial Monitor para mensajes de inicialización del sensor

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

