
/*******************************************************************************************************
 * file			: apds9930.h
 * API files	: apds9930.h and apds9930.c
 * date 		: 19/07/2021
 * authors		: Pedro Barbosa Bahia and Pietro Zanetti
 * license		: GNU General Public License v3.0
 * university	: Universidade Federal de Minas Gerais (UFMG) - Brazil
 *
 * This API was an assignment for UFMG's course "Embbedded Systems Programing"
 * instructed by Prof. Ricardo de Oliveira Duarte -
 * - Departamento de Engenharia Eletr�nica (Electronics Engineering)
 *
 * API inspired includes a ssd1306 library by Tilen Majerle<tilen@majerle.eu> and Alexander Lutsai<s.lyra@ya.ru>
 * Also
 *******************************************************************************************************
 * API hardware and software requisites:
 *
 * STMicroelectronics' nucleo64 STM32F401 kit (code can be adapted to other kits)
 * APDS9930 Proximity Sensor
 * SSD1306 OLED
 *******************************************************************************************************
 */

#ifndef INC_APDS9930_H_
#define INC_APDS9930_H_



/* I2C address */
#ifndef APDS9930_I2C_ADDR
#define APDS9930_I2C_ADDR         0x72	//0x32<<1
#endif


#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "stdbool.h"
#include "stdint.h"
#include "ssd1306.h"


#ifndef WEN
#define WEN  8 // Enable Wait
#endif

#ifndef PEN
#define PEN  4 // Enable Wait
#endif

#ifndef AEN
#define AEN  2 // Enable Wait
#endif

#ifndef PON
#define PON  1 // Enable Wait
#endif

//Initializing variables
extern int count;	  // counter
extern uint16_t PIHT; //Proximity Interrupt High Threshold
extern uint16_t PILT; //Proximity Interrupt Low Threshold
extern uint16_t AIHT; //ALS Interrupt High Threshold
extern uint16_t AILT; //ALS Interrupt Low Threshold
extern int limit;	  //limit of Prox interrupt before Sleep mode begin
extern int bright; 	  //screen brightness

bool APDS9930_Init();
/* Define initialization values.
 * Section "Basic Software Operation" from  APDS9930's datasheet
 */

bool APDS9930_WriteRegData(uint8_t reg, uint8_t data);

/* Write 8-bit data in one APDS9930 internal register.
 */

bool APDS9930_WriteWordData(uint8_t reg, uint16_t data);
/* Write 16-bit data in two APDS9930 internal register.
 */

uint8_t APDS9930_ReadRegData(uint8_t reg);
/* Return 8-bit data written in one APDS9930 internal register.
 *
 */

uint16_t APDS9930_ReadWordData(uint8_t reg_adr);
/* Return 16-bit data written in two APDS9930 internal register.
 *
 */

bool set_PIT(uint16_t low, uint16_t high);
/*
set values of lower and upper thresholds of Proximity Sensor
*/

int which_INT();
/*
 * get interruption origin
 *	0 - no interruption
 *	1 - ALS interruption
 *	2 - Proximity interruption
 */


uint16_t Prox_data();
/*
 * get actual Proximity measured data
 */

void interrup_treat();
/* begin interrupt treatment
 * define cause of interruption
 */

void Prox_treat(uint16_t data, uint16_t high, uint16_t low);
/*  trigger by Proximity Sensor interrupt. Define which threshold was passed and
 * turn off the led if it was the high threshold. Do nothing if it was the low one
 */

bool clear_INT();
/*Interrupt clear
*/


#endif /* INC_APDS9930_H_ */
