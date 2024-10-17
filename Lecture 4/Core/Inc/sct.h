/*
 * sct.h
 *
 *  Created on: Oct 10, 2024
 *      Author: 240609
 */

#ifndef INC_SCT_H_
#define INC_SCT_H_

#include "main.h"


void sct_init();

void sct_led(uint32_t value);

void sct_value(uint16_t value, uint8_t led);


#endif /* INC_SCT_H_ */