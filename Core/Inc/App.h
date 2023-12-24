/*
 * App.h
 *
 *  Created on: Dec 20, 2023
 *      Author: Jabber
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "waveplayer.h"
#include "File_Handling.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "i2s.h"
#include "tim.h"
#include "usb_host.h"
#include "gpio.h"
#include "LiquidCrystal_I2C.h"

// Function Prototypes
void app_main();

#ifdef __cplusplus
}
#endif
#endif /* INC_APP_H_ */
