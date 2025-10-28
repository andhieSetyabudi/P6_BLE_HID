/*
 * device_config.h
 *
 *  Created on: 27 Okt 2025
 *      Author: dwisetyabudi
 */

#ifndef SOURCE_DEVICE_CONFIG_H_
#define SOURCE_DEVICE_CONFIG_H_


/* TLE493D connections (choose available BSP aliases). These can be mapped
 * to real GPIOs in the design.modus if different aliases are required.
 * One CS uses the default CYBSP_SPI_CS; the other two use user LED pins as
 * placeholders and should be updated for the real board wiring. */
#define VDD_EN_PIN   	 (P9_7)    /* placeholder, active low enable */
#define CS_SENSOR_1_PIN  (P9_3)
#define CS_SENSOR_2_PIN  (P9_4)
#define CS_SENSOR_3_PIN  (P9_5)

#define	SPI_MOSI_PIN	 (P9_0)
#define SPI_MISO_PIN	 (P9_1)	
#define SPI_CLK_PIN		 (P9_2)

#endif /* SOURCE_DEVICE_CONFIG_H_ */
