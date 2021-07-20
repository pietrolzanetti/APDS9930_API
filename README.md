# APDS9930_API

## Introduction
This API was developed as a work in the discipline of Embedded Systems Programming at UFMG - Prof. Ricardo de Oliveira Duarte - Department of Electronic EngineeringLibrary is 
developed and tested with STM32F1xx (Nucleo 64 board). 

## Hardware requirements
* STM32F41xx microntroller;
* APDS-9930 ALS IR RGB and Gesture Sensor Proximity Sensor;
* 0.96 Inch Yellow and Blue I2C IIC Serial 128X64 OLED Display;

## Connections
The following image shows the connection diagram btween the hardware elements. 

![Connection diagram](Images/C_Diagram.png)

## STM32CubeMX configuration
Pinout view:

![Connection diagram](Images/Pinout.jpg)

GPIO Mode and Configuration:

![Connection diagram](Images/EXTI.jpg)

![Connection diagram](Images/GPIO.jpg)

I2C1 Mode and Configuration:

![Connection diagram](Images/i2c1.PNG)

I2C1 and I2C2 Mode and Configuration/ Parameter Settings:

![Connection diagram](Images/i2c_c.PNG)

  
## API usage
1. Download APDS9930.c from the APDS9930_API/Core/Src and APDS9930.h from the APDS_API/Core/Inc 
directory;
2. Copy APDS9930.h to your projec's Inc directory and the APDS9930.c to your projec's Src directory;
3. Include where you expect to use.

## API functions
```C
bool APDS9930_Init();
```
 Define initialization values.
 
 
 ```C
 bool APDS9930_WriteRegData(uint8_t reg, uint8_t data);
 ```
Write 8-bit data in one APDS9930 internal register.

Parameters:
  * ```reg```: Internal memory address;
  * ```data```: Data buffer;
 
 
```C
bool APDS9930_WriteWordData(uint8_t reg, uint16_t data);
```
Write 16-bit data in two APDS9930 internal register

Parameters:
  * ```reg```: Internal memory address;
  * ```data```: Data buffer;


```C
uint8_t APDS9930_ReadRegData(uint8_t reg);
```
Return 8-bit data written in one APDS9930 internal register.

Parameters:
  * ```reg```: Internal memory address;


```C
uint16_t APDS9930_ReadWordData(uint8_t reg_adr);
```
Return 16-bit data written in two APDS9930 internal register.

Parameters:
  * ```reg_adr```: Internal memory address;.


