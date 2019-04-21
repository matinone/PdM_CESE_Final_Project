# PdM_CESE_Final_Project
Repository for the final project of the subject "Microcontroller Programming", a course part of the Specialization Career in Embedded Systems (CESE), offered by the University of Buenos Aires (UBA). 

Repositorio para el proyecto final de la materia "Programación de Microcontroladores", un curso parte de la Carrera de Especialización en Sistemas Embebidos (CESE), de la Universidad de Buenos Aires (UBA).

## Descripción
En el trabajo final de la CESE se va a comunicar el microcontrolador utilizado (ESP32) con la placa de control de un electrodoméstico mediante comunicación serie (I2C o SPI, a determinar). A su vez el microcontrolador recibiría comandos por WiFi o Bluetooth y en base a eso ejecutaría acciones y enviaría comandos a la placa de control del electrodoméstico.

Para emular esto usando el hardware que se tiene ahora (no se cuenta ni con el microcontrolador que se va a utilizar, que incluye la comunicación WiFi/Bluetooth, ni con la placa del electrodoméstico), la EDU-CIAA recibiría comandos por UART (en vez de WiFi/Bluetooth), ejecutaría acciones básicas a modo de ejemplo (prender LEDs o usar el ADC de forma simple) y enviaría comandos por SPI, I2C o UART (sólo uno de estos protocolos) a un Arduino (en vez de a la placa del electrodoméstico, se usa un Arduino ya que es el único otro microcontrolador con el que se cuenta en este momento). En el Arduino habría un programa simple que recibiría los comandos y devolvería una respuesta específica de acuerdo al comando recibido. En la EDU-CIAA nuevamente se tomarían medidas de acuerdo a la respuesta recibida por SPI, I2C o UART.

Debido a que las interafaces SPI e I2C de Arduino funcionan a 5V, y las de la EDU-CIAA a 3.3V, se decide utilizar solamente comunicación UART, ya que no se cuentan con los componentes necesarios para hacer la conversión de niveles. Para que ambas placas puedan comunicarse por UART, se desarrolla un programa en Python que se encarga de redirigir adecuadamente los mensajes que la EDU-CIAA envía a Arduino, y viceversa, pasando siempre a través de la PC.

