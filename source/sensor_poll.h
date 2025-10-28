/*
 * sensor_poll.h
 *
 *  Created on: 27 Okt 2025
 *      Author: dwisetyabudi
 */

#ifndef SOURCE_SENSOR_POLL_H_
#define SOURCE_SENSOR_POLL_H_


#include "cyhal.h"
#include "cybsp.h"

/* Number of bytes to read from sensor (10 in Arduino sketch) */
#define SENSOR_REG_BYTES  (10)

/* sensor data struct - file scope so helper functions can use it */
typedef struct {
    int16_t bx, by, bz;
    uint16_t temperature;
    uint8_t diag;
} sensor_data_t;


extern uint8_t sensor_rx_buf[SENSOR_REG_BYTES];
extern sensor_data_t sensor1, sensor2, sensor3;

void poll_sensor(cyhal_spi_t *spi, cyhal_gpio_t cs_pin, uint8_t *rx, size_t len);
int16_t parse_magnetic(uint8_t msb, uint8_t lsb);
uint16_t parse_temperature(uint8_t msb, uint8_t lsb);
void parse_sensor_data(uint8_t *rx, sensor_data_t *out);
void print_sensor(const char *label, const sensor_data_t *s);

#endif /* SOURCE_SENSOR_POLL_H_ */
