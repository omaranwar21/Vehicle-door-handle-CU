/*
 * ====================================================================================================================================
 *  * Lab - 04_1 Gpio Driver
 * 	Gpio.c
 *	Name : Omar Ahmed Anwar Mansour
 *  Section: 2
 *  B.N: 2
 *  ===================================================================================================================================
 */

#include "Gpio.h"

#include "Utils.h"


uint32 gpioAddresses[5] = {GPIOA_BASE_ADDR, GPIOB_BASE_ADDR, GPIOC_BASE_ADDR, GPIOD_BASE_ADDR, GPIOE_BASE_ADDR};

void Gpio_ConfigPin(uint8 PortName, uint8 PinNum, Gpio_PinMode PinMode,
		Gpio_DefaultState DefaultState, Gpio_PullState pullState) {

	uint8 portID = PortName - GPIO_A;

	GPIO_Reg *GPIO_Port = (GPIO_Reg *)gpioAddresses[portID];

	GPIO_Port->GPIOx_MODER &= ~(0x03 << (PinNum * 2));
	GPIO_Port->GPIOx_MODER |= (PinMode << (PinNum * 2));

	GPIO_Port->GPIOx_OTYPER &= ~(0x01 << PinNum);
	GPIO_Port->GPIOx_OTYPER |= (DefaultState << PinNum);

	GPIO_Port->GPIOx_PUPDR &= ~(0x03 << (PinNum * 2));
	GPIO_Port->GPIOx_PUPDR |= (pullState << (PinNum * 2));

}

Gpio_WriteDataFlag GPIO_WritePinValue(uint8 PortName, uint8 PinNum, Gpio_Data Data) {

	uint8 portID = PortName - GPIO_A;

	GPIO_Reg *GPIO_Port = (GPIO_Reg *)gpioAddresses[portID];

	if (( (GPIO_Port->GPIOx_MODER) & (0x03 << (PinNum * 2))) >> (PinNum*2) != GPIO_OUTPUT)
	{
		return NOK;
	}

	GPIO_Port->GPIOx_ODR &= ~(0x1 << PinNum);
	GPIO_Port->GPIOx_ODR |= (Data << PinNum);

	return OK;
}

Gpio_Data GPIO_ReadPinState(uint8 PortName, uint8 PinNum){

	uint8 portID = PortName - GPIO_A;

	GPIO_Reg *GPIO_Port = (GPIO_Reg *)gpioAddresses[portID];

	Gpio_Data data;
	if ( ((GPIO_Port->GPIOx_MODER & (0x03 << (PinNum * 2))) >> (PinNum*2) ) == GPIO_OUTPUT) {
		data = ( (GPIO_Port->GPIOx_ODR) & (1 << PinNum))? GPIO_DATA_FALLING : GPIO_DATA_RISING;
	}
	else if ( ((GPIO_Port->GPIOx_MODER & (0x03 << (PinNum * 2))) >> (PinNum*2) ) == GPIO_INPUT){
		data = ( (GPIO_Port->GPIOx_IDR) & (1 << PinNum))? GPIO_DATA_RISING : GPIO_DATA_FALLING;
	}
	return data;

}





