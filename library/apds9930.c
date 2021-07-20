#include "apds9930.h"


extern I2C_HandleTypeDef hi2c3;   //I2C port, change the number to select the right interface

/*Pseudo-code from datasheet
 *
 * uint8 ATIME, PIME, WTIME, PPULSE;
ATIME = 0xff; // 2.7 ms � minimum ALS integration time
WTIME = 0xff; // 2.7 ms � minimum Wait time
PTIME = 0xff; // 2.7 ms � minimum Prox integration time
PPULSE = 1; // Minimum prox pulse count
WriteRegData(0, 0); //Disable and Powerdown
WriteRegData (1, ATIME);
WriteRegData (2, PTIME);
WriteRegData (3, WTIME);
WriteRegData (0xe, PPULSE);
uint8 PDRIVE, PDIODE, PGAIN, AGAIN;
PDRIVE = 0; //100mA of LED Power
PDIODE = 0x20; // CH1 Diode
PGAIN = 0; //1x Prox gain
AGAIN = 0; //1x ALS gain
WriteRegData (0xf, PDRIVE | PDIODE | PGAIN | AGAIN);
uint8 WEN, PEN, AEN, PON;
WEN = 8; // Enable Wait
PEN = 4; // Enable Prox
AEN = 2; // Enable ALS
PON = 1; // Enable Power On
WriteRegData (0, WEN | PEN | AEN | PON); // WriteRegData(0,0x0f);
Wait(12); //Wait for 12 ms
int CH0_data, CH1_data, Prox_data;
CH0_data = Read_Word(0x14);
CH1_data = Read_Word(0x16);
Prox_data = Read_Word(0x18);
WriteRegData(uint8 reg, uint8 data)
{
m_I2CBus.WriteI2C(0x39, 0x80 | reg, 1, &data);
}
uint16 Read_Word(uint8 reg);
{
uint8 barr[2];
m_I2CBus.ReadI2C(0x39, 0xA0 | reg, 2, ref barr);
return (uint16)(barr[0] + 256 * barr[1]);
}*/

/*/////////////////////////////////////////////////

APDS 9930 registers address notation:
CMD + TYPE + ADDRESS
CMD -> 1 bit: (1) - define register address
			  (0) - read register data
TYPE -> 2 bits: (00) - repeated byte protocol (read/write byte)
				(01) - Auto-Increment protocol (read/write word)
				(11) - interrupt clear
ADDRESS -> 5-bits: address of next operation register
				   (00111) - Prox and ALS interrupt clear


///////////////////////////////////////////////*/



bool APDS9930_WriteRegData(uint8_t reg_adr, uint8_t data){

	HAL_StatusTypeDef ref;				//check operation completeness
	reg_adr = (reg_adr) | 0x80;			// convert to APDS byte reg address
	ref = HAL_I2C_Mem_Write(&hi2c3, 	APDS9930_I2C_ADDR,   reg_adr, 	I2C_MEMADD_SIZE_8BIT , 	&data, 	I2C_MEMADD_SIZE_8BIT, 	10);
	if(ref!=HAL_OK)
		return false;
	return true;
}

bool APDS9930_WriteWordData(uint8_t reg_adr, uint16_t data){

	HAL_StatusTypeDef ref;		//check operation completeness
	uint8_t barr[2];
	barr[0] = data & 0xff;
	barr[1] = (data >> 8) & 0xff;
	reg_adr = (reg_adr) | 0xA0;			// convert to APDS reg address
	ref = HAL_I2C_Mem_Write(&hi2c3, APDS9930_I2C_ADDR,   reg_adr, 	I2C_MEMADD_SIZE_16BIT , barr, 	I2C_MEMADD_SIZE_16BIT, 	10);
	if(ref!=HAL_OK)
		return false;
	return true;
}

uint8_t APDS9930_ReadRegData(uint8_t reg_adr){

	HAL_StatusTypeDef ref;		//check operation completeness
	 ref = 0x01;
	uint8_t data;
	reg_adr = reg_adr | 0x80;						// convert to APDS reg address
	ref = HAL_I2C_Mem_Read(&hi2c3, (APDS9930_I2C_ADDR | 0x01), reg_adr , 	I2C_MEMADD_SIZE_8BIT ,  &data, 	1, 10);
	if(ref!=HAL_OK)
		return 0x00;     //default value of error se to to 0
	return (uint8_t)data;
}

uint16_t APDS9930_ReadWordData(uint8_t reg_adr){

	HAL_StatusTypeDef ref;		//check operation completeness
	uint8_t barr[2];
	reg_adr = reg_adr | 0xA0;						// convert to APDS reg address
	ref = HAL_I2C_Mem_Read(&hi2c3, (APDS9930_I2C_ADDR | 0x01), reg_adr , 	I2C_MEMADD_SIZE_16BIT ,  barr, 	2, 10);
	if(ref!=HAL_OK)
		return 0x0000;     //default value of error se to to 0
	return (uint16_t)(barr[0] + 256 * barr[1]);

}

bool APDS9930_Init(){


	HAL_StatusTypeDef ref;		//check operation completeness
	uint8_t ATIME, WTIME, PTIME,PPULSE;
	ATIME = 0xff; // 2.7 ms � minimum ALS integration time
	WTIME = 0xff; // 2.7 ms � minimum Wait time
	PTIME = 0xff; // 2.7 ms � minimum Prox integration time
	PPULSE = 1; // Minimum prox pulse count

	ref = APDS9930_WriteRegData(0, 0); //Disable and Powerdown
	if(ref!=HAL_OK)
			return false;

	ref = APDS9930_WriteRegData (1, ATIME);
	if(ref!=HAL_OK)
			return false;

	ref = APDS9930_WriteRegData (2, PTIME);
	if(ref!=HAL_OK)
			return false;

	ref = APDS9930_WriteRegData (3, WTIME);
	if(ref!=HAL_OK)
			return false;

	ref = APDS9930_WriteRegData (0xe, PPULSE);
	if(ref!=HAL_OK)
			return false;

	uint8_t PDRIVE, PDIODE, PGAIN, AGAIN;
	PDRIVE = 0; //100mA of LED Power
	PDIODE = 0x20; // CH1 Diode
	PGAIN = 0; //1x Prox gain
	AGAIN = 0; //1x ALS gain
	ref = APDS9930_WriteRegData (0xf, PDRIVE | PDIODE | PGAIN | AGAIN);
	if(ref!=HAL_OK)
			return false;


	/*uint8_t WEN, PEN, AEN, PON;
	WEN = 8; // Enable Wait
	PEN = 4; // Enable Prox
	AEN = 2; // Enable ALS
	PON = 1; // Enable Power On*/
	ref = APDS9930_WriteRegData (0, WEN | PEN | AEN | PON); // APDS9930_WriteRegData(0,0x0f);
	if(ref!=HAL_OK)
			return false;
	HAL_Delay(12); //Wait for 12 ms

	return true;
}

bool set_PIT(uint16_t low, uint16_t high){
	bool chk;
	chk = APDS9930_WriteWordData(8, low);
	if(chk!=HAL_OK)
		return false;
	chk = APDS9930_WriteWordData(0xa, high);
	if(chk!=HAL_OK)
		return false;
	return true;
}

int which_INT(){
	uint8_t result;
	result = APDS9930_ReadRegData(0x13);		//check status register
	if ((result & 0x20) == 0x20)   //Proximity Interrupt
				return 2;
	if ((result & 0x10) == 0x10) //ALS interrupt
		return 1;
	return 0;
}

uint16_t Prox_data(){
	uint16_t chk;
	chk = APDS9930_ReadWordData(0x18);
	return chk;

}

bool clear_INT(){
	uint8_t c_command;
	HAL_StatusTypeDef ref;			//check operation completeness
	c_command = 0x80 | 0x60 | 0x07; //CMD + TYPE + SPECIAL COMMAND (CLEAR)
	ref = HAL_I2C_Master_Transmit(&hi2c3, 	APDS9930_I2C_ADDR, 		&c_command, 1 , 10);
	if(ref!=HAL_OK)
		return false;
	return true;
};

void interrup_treat(){
	int cause = which_INT(); //0-> no int, 1-> ALS int, 2-> Prox int
	uint16_t data, high, low;
	if(cause==2){
			data = Prox_data();
			low = APDS9930_ReadWordData(8);
			high = APDS9930_ReadWordData(0xa);
			Prox_treat(data, high, low);
	}
	bool clear;
	clear = clear_INT();
}

void Prox_treat(uint16_t data, uint16_t high, uint16_t low){
	if(data>high)
		SSD1306_OFF(); //turn off display
	if(data<low)
		data = data + 1;			  //do nothing
}









