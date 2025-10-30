/*
 * servo.h
 *
 *  Created on: 30 oct. 2025
 *      Author: GastonCapdevila
 */

#ifndef HEADERS_SERVO_H_
#define HEADERS_SERVO_H_

#define SERVO_PULSE_CYCLE 	20000 	// PWM PERIOD 20 ms
#define SERVO_PW_MIN 		500		// SERVO MIN PULSE WIDTH 0.5 ms
#define SERVO_PW_MAX 		2400	// SERVO MAX PULSE WIDTH 2.4 ms
#define SERVO_PW_CENTER   	1500

void ServoInit(void);									// INICIALIZACION DEL SERVO
void delay_ms(uint32_t ms);								// FUNCION DELAY
void ConfigServoTimer(void);							// CONFIGURACION DEL TIMER QUE MANEJA LA PWM
void ServoSetPulse(uint32_t pw);						// FUNCION PARA CAMBIAR EL PW (MOVER MOTOR)
void MoverServo(uint32_t delta_pw, uint32_t delay_ms);	// FUNCION PARA MOVER EL SERVO

#endif /* HEADERS_SERVO_H_ */
