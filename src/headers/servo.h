#ifndef HEADERS_SERVO_H_
#define HEADERS_SERVO_H_

#include "../headers/pcb.h"
#include "../headers/timers.h"

#define SERVO_PULSE_CYCLE   20000   // 20ms = 20000µs
#define SERVO_PW_MIN        500    	// 0.5ms
#define SERVO_PW_MAX        2500    // 2.5ms
#define SERVO_PW_CENTER     1500    // 1.5ms

void ServoInit(void);
void DelayMs(uint32_t ms);
void ServoSetPulse(uint32_t pw);
void MoverServoCompleto(uint32_t delta_pw, uint32_t delay_ms);
void MoverServoUnPaso(uint32_t delta_pw, uint32_t delay_ms);
void ServoSetAngulo(uint32_t pw_us);
uint32_t ServoGetAngulo(void);

#endif /* HEADERS_SERVO_H_ */
