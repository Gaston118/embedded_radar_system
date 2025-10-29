# 🛰️ Radar Ultrasónico con LPC

Proyecto académico desarrollado sobre una **placa LPC1769** que implementa un **radar ultrasónico** utilizando periféricos integrados del microcontrolador: **PWM**, **ADC**, **DAC** y **Timers**.  
El sistema permite controlar un servomotor para realizar el barrido del radar, generar los pulsos de disparo ultrasónico y medir distancias mediante tiempo de vuelo (ToF).

---

## 📘 Descripción General

El radar funciona haciendo girar un servomotor en un rango de 180°, mientras un sensor ultrasónico mide la distancia a los objetos en cada ángulo.  
Los datos obtenidos pueden representarse visualmente o transmitirse para análisis externo.

El proyecto integra varios periféricos:
- **PWM / Timer:** control de posición del servomotor.  
- **GPIO / Timer Capture:** generación y medición del pulso ultrasónico.  
- **ADC:** lectura de una señal analógica para variar dinámicamente la velocidad de barrido.  
- **DAC:** generación de una señal de referencia o modulación asociada al movimiento del servo.  

---

## ⚙️ Funcionamiento

1. El **timer principal** genera la señal PWM que posiciona el servomotor entre 0° y 180°.  
2. En cada posición, se activa un **pulso de trigger** (≈10 µs) hacia el sensor ultrasónico.  
3. El **modo capture del timer** mide el tiempo entre el pulso de salida y el eco recibido.  
4. A partir de ese tiempo, se calcula la distancia del objeto detectado.  
5. El **ADC** permite variar la velocidad de barrido según una entrada analógica.  
6. El **DAC** genera una salida proporcional a la distancia o velocidad, útil para visualización o depuración.

---

## 🧩 Hardware Utilizado

- Placa **LPC1769**  
- Sensor ultrasónico **HC-SR04** 
- Servomotor **SG90**  
- Fuente de alimentación 3.3 V  
- Conexión serial o USB para monitoreo de datos

---

## 🧑‍💻 Autores
- Capdevila Gaston
- Viberti Tomas

Proyecto desarrollado como parte de la materia **Electronica Digital 3**.  
Plataforma: **MCUXpresso IDE + LPCXpresso Board**.  
Año: **2025**



