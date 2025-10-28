/*
 * sensor_poll.c
 *
 *  Created on: 27 Okt 2025
 *      Author: dwisetyabudi
 */
 
#include "sensor_poll.h"
#include "stdio.h"

uint8_t sensor_rx_buf[SENSOR_REG_BYTES];
sensor_data_t sensor1 = {0}, sensor2 = {0}, sensor3 = {0};
    
void poll_sensor(cyhal_spi_t *spi, cyhal_gpio_t cs_pin, uint8_t *rx, size_t len)
{
    cy_rslt_t res;
    /* Assert CS (active low) */
    cyhal_gpio_write(cs_pin, false);

    /* Send read command 0xC0 (start at reg 0x00, auto-increment) */
    uint8_t cmd = 0xC0;
    res = cyhal_spi_send(spi, cmd);
    if (res != CY_RSLT_SUCCESS)
    {
        printf("SPI send failed: 0x%08lx\r\n", (unsigned long)res);
    }

    /* Read bytes by sending dummy 0x00 */
    for (size_t i = 0; i < len; ++i)
    {
    uint8_t out = 0x00;
    uint8_t in = 0x00;
    /* tx pointer, tx_length, rx pointer, rx_length, write_fill */
    res = cyhal_spi_transfer(spi, &out, 1, &in, 1, 0x00);
        if (res != CY_RSLT_SUCCESS)
        {
            printf("SPI transfer failed: 0x%08lx\r\n", (unsigned long)res);
            rx[i] = 0;
        }
        else
        {
            rx[i] = in;
        }
    }

    /* Deassert CS */
    cyhal_gpio_write(cs_pin, true);
}

int16_t parse_magnetic(uint8_t msb, uint8_t lsb)
{
    int16_t value = (int16_t)(((uint16_t)msb << 6) | (lsb >> 2));
    if (value & 0x2000) /* sign bit for 14-bit value */
    {
        value |= 0xC000; /* sign extend */
    }
    return value;
}

uint16_t parse_temperature(uint8_t msb, uint8_t lsb)
{
    return (uint16_t)(((uint16_t)msb << 6) | (lsb >> 2));
}

void parse_sensor_data(uint8_t *rx, sensor_data_t *out)
{
    out->bx = parse_magnetic(rx[0], rx[1]);
    out->by = parse_magnetic(rx[2], rx[3]);
    out->bz = parse_magnetic(rx[4], rx[5]);
    out->temperature = parse_temperature(rx[6], rx[7]);
    out->diag = rx[9];
}

void print_sensor(const char *label, const sensor_data_t *s)
{
    printf("%s: Bx=%d, By=%d, Bz=%d, Temp=%u, Diag=0b%02x\r\n",
           label, s->bx, s->by, s->bz, (unsigned int)s->temperature, s->diag);
}

