/*
 * bq769x2_priv.h
 *
 *  Created on: Mar 18, 2024
 *      Author: bobo
 */

#ifndef BQ769X2_BQ769X2_PRIV_H_
#define BQ769X2_BQ769X2_PRIV_H_

//#include <drivers/bms_ic.h>
#include <stdint.h>
#include <string.h>

#ifndef STM32F4XX_H
#include "stm32f4xx_hal.h"
#endif

#ifndef STM324XX_HAL_I2C_H
#include "stm32f4xx_hal_i2c.h"
#endif

#include "bms_ic.h"


typedef struct {

    /** @TODO: need to be check again */
	//const device_t *bus;
	I2C_HandleTypeDef	*i2cHandle;

	uint16_t addr;
} i2c_spec_t;

/**
 * Writes multiple bytes to bq769x2 IC registers
 *
 * @param reg_addr The address to write to
 * @param data The pointer to the data buffer
 * @param num_bytes Number of bytes to write
 *
 * @returns 0 if successful, negative errno otherwise
 */

typedef int (*bq769x2_write_bytes_t)(const device_t *dev, const uint8_t reg_addr,
                                     const uint8_t *data, const size_t num_bytes);

/**
 * Reads multiple bytes from bq769x2 IC registers
 *
 * @param reg_addr The address to read the bytes from
 * @param data The pointer to where the data should be stored
 * @param num_bytes Number of bytes to read
 *
 * @returns 0 if successful, negative errno otherwise
 */
typedef int (*bq769x2_read_bytes_t)(const device_t *dev, const uint8_t reg_addr, uint8_t *data,
                                    const size_t num_bytes);

/* read-only driver configuration */
typedef struct {
    i2c_spec_t i2c;

    /** @TODO: need to be check again */
    //struct gpio_dt_spec alert_gpio;

    uint32_t shunt_resistor_uohm;
    uint32_t board_max_current;
    uint16_t used_cell_channels;
    uint8_t pin_config[9];
    uint8_t cell_temp_pins[CONFIG_BMS_IC_MAX_THERMISTORS];
    uint8_t num_cell_temps;
    uint8_t fet_temp_pin;
    bool crc_enabled;
    bool auto_pdsg;
    uint8_t reg12_config;
    bq769x2_write_bytes_t write_bytes;
    bq769x2_read_bytes_t read_bytes;
} bms_ic_bq769x2_config_t;

/* driver run-time data */
typedef struct {
    bms_ic_data_t *ic_data;
    bool config_update_mode_enabled;
} bms_ic_bq769x2_data_t;


#endif /* BQ769X2_BQ769X2_PRIV_H_ */
