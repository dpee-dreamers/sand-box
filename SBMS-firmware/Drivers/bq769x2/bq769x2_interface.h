/*
 * bq769x2_interface.h
 *
 *  Created on: Mar 18, 2024
 *      Author: bobo
 */

#ifndef BQ769X2_BQ769X2_INTERFACE_H_
#define BQ769X2_BQ769X2_INTERFACE_H_

/*
 * Copyright (c) The Libre Solar Project Contributors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdbool.h>
#include <stdint.h>
#include "bms.h"

/**
 * Set bq769x2 config update mode
 *
 * @param config_update True if config update mode should be entered
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_config_update_mode(const device_t *dev, bool config_update);

/**
 * Read 8-bit unsigned integer via direct command from bq769x2 IC
 *
 * @param reg_addr The address to read the bytes from
 * @param value Pointer to where the value should be stored
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_direct_read_u1(const device_t *dev, const uint8_t reg_addr, uint8_t *value);

/**
 * Read 16-bit unsigned integer via direct command from bq769x2 IC
 *
 * @param reg_addr The address to read the bytes from
 * @param value Pointer to where the value should be stored
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_direct_read_u2(const device_t *dev, const uint8_t reg_addr, uint16_t *value);

/**
 * Read 16-bit integer via direct command from bq769x2 IC
 *
 * @param reg_addr The address to read the bytes from
 * @param value Pointer to where the value should be stored
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_direct_read_i2(const device_t *dev, const uint8_t reg_addr, int16_t *value);

/**
 * Execute subcommand without data (command-only) in bq769x2 IC
 *
 * @param subcmd The subcommand to execute
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_subcmd_cmd_only(const device_t *dev, const uint16_t subcmd);

/**
 * Read 8-bit unsigned integer via subcommand from bq769x2 IC
 *
 * @param subcmd The subcommand to read the bytes from
 * @param value Pointer to where the value should be stored
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_subcmd_read_u1(const device_t *dev, const uint16_t subcmd, uint8_t *value);

/**
 * Read 16-bit unsigned integer via subcommand from bq769x2 IC
 *
 * @param subcmd The subcommand to read the bytes from
 * @param value Pointer to where the value should be stored
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_subcmd_read_u2(const device_t *dev, const uint16_t subcmd, uint16_t *value);

/**
 * Read 32-bit unsigned integer via subcommand from bq769x2 IC
 *
 * @param subcmd The subcommand to read the bytes from
 * @param value Pointer to where the value should be stored
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_subcmd_read_u4(const device_t *dev, const uint16_t subcmd, uint32_t *value);

/**
 * Read 16-bit signed integer via subcommand from bq769x2 IC
 *
 * @param subcmd The subcommand to read the bytes from
 * @param value Pointer to where the value should be stored
 *
 * @returns 0 if successful, negative errno otherwise
 */
static inline int bq769x2_subcmd_read_i2(const device_t *dev, const uint16_t subcmd,
                                         int16_t *value)
{
    return bq769x2_subcmd_read_u2(dev, subcmd, (uint16_t *)value);
}

/**
 * Read 32-bit signed integer via subcommand from bq769x2 IC
 *
 * @param subcmd The subcommand to read the bytes from
 * @param value Pointer to where the value should be stored
 *
 * @returns 0 if successful, negative errno otherwise
 */
static inline int bq769x2_subcmd_read_i4(const device_t *dev, const uint16_t subcmd,
                                         int32_t *value)
{
    return bq769x2_subcmd_read_u4(dev, subcmd, (uint32_t *)value);
}

/**
 * Write 8-bit unsigned integer via subcommand to bq769x2 IC
 *
 * @param subcmd The subcommand to write the bytes to
 * @param value Value that should be written
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_subcmd_write_u1(const device_t *dev, const uint16_t subcmd, uint8_t value);

/**
 * Write 16-bit unsigned integer via subcommand to bq769x2 IC
 *
 * @param subcmd The subcommand to write the bytes to
 * @param value Value that should be written
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_subcmd_write_u2(const device_t *dev, const uint16_t subcmd, uint16_t value);

/**
 * Write 16-bit signed integer via subcommand to bq769x2 IC
 *
 * @param subcmd The subcommand to write the bytes to
 * @param value Value that should be written
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_subcmd_write_i2(const device_t *dev, const uint16_t subcmd, int16_t value);

/**
 * Read 8-bit unsigned integer from bq769x2 data memory
 *
 * @param reg_addr The data memory register address to read the value from
 * @param value Pointer to where the value should be stored
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_datamem_read_u1(const device_t *dev, const uint16_t reg_addr, uint8_t *value);

/**
 * Read 16-bit unsigned integer from bq769x2 data memory
 *
 * @param reg_addr The data memory register address to read the value from
 * @param value Pointer to where the value should be stored
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_datamem_read_u2(const device_t *dev, const uint16_t reg_addr, uint16_t *value);

/**
 * Read 8-bit signed integer from bq769x2 data memory
 *
 * @param reg_addr The data memory register address to read the value from
 * @param value Pointer to where the value should be stored
 *
 * @returns 0 if successful, negative errno otherwise
 */
static inline int bq769x2_datamem_read_i1(const device_t *dev, const uint16_t reg_addr,
                                          int8_t *value)
{
    return bq769x2_datamem_read_u1(dev, reg_addr, (uint8_t *)value);
}

/**
 * Read 16-bit signed integer from bq769x2 data memory
 *
 * @param reg_addr The data memory register address to read the value from
 * @param value Pointer to where the value should be stored
 *
 * @returns 0 if successful, negative errno otherwise
 */
static inline int bq769x2_datamem_read_i2(const device_t *dev, const uint16_t reg_addr,
                                          int16_t *value)
{
    return bq769x2_datamem_read_u2(dev, reg_addr, (uint16_t *)value);
}

/**
 * Read 32-bit float from bq769x2 data memory
 *
 * @param reg_addr The data memory register address to read the value from
 * @param value Pointer to where the value should be stored
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_datamem_read_f4(const device_t *dev, const uint16_t reg_addr, float *value);

/**
 * Write 8-bit unsigned integer to bq769x2 data memory
 *
 * @param reg_addr The data memory register address to
 * write the bytes to
 * @param value Value that should be written
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_datamem_write_u1(const device_t *dev, const uint16_t reg_addr, uint8_t value);

/**
 * Write 16-bit unsigned integer to bq769x2 data memory
 *
 * @param reg_addr The data memory register address to
 * write the bytes to
 * @param value Value that should be written
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_datamem_write_u2(const device_t *dev, const uint16_t reg_addr, uint16_t value);

/**
 * Write 8-bit signed integer to bq769x2 data memory
 *
 * @param reg_addr The data memory register address to
 * write the bytes to
 * @param value Value that should be written
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_datamem_write_i1(const device_t *dev, const uint16_t reg_addr, int8_t value);

/**
 * Write 16-bit signed integer to bq769x2 data memory
 *
 * @param reg_addr The data memory register address to
 * write the bytes to
 * @param value Value that should be written
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_datamem_write_i2(const device_t *dev, const uint16_t reg_addr, int16_t value);

/**
 * Write 32-bit float to bq769x2 data memory
 *
 * @param reg_addr The data memory register address to
 * write the bytes to
 * @param value Value that should be written
 *
 * @returns 0 if successful, negative errno otherwise
 */
int bq769x2_datamem_write_f4(const device_t *dev, const uint16_t reg_addr, float value);

#endif /* BQ769X2_BQ769X2_INTERFACE_H_ */
