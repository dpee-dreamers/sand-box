/*
 * helper.h
 *
 *  Created on: Mar 18, 2024
 *      Author: bobo
 */

#ifndef INC_HELPER_H_
#define INC_HELPER_H_

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
/*
 * VS Code intellisense can't cope with all the Zephyr macro layers for logging, so provide it
 * with something more simple and make it silent.
 */

#define LOG_DBG(...) printf(__VA_ARGS__)

#define LOG_INF(...) printf(__VA_ARGS__)

#define LOG_WRN(...) printf(__VA_ARGS__)

#define LOG_ERR(...) printf(__VA_ARGS__)

#define LOG_MODULE_REGISTER(...)


//#include <zephyr/logging/log.h>

/**
 * Interpolation in a look-up table. Values of a must be monotonically increasing/decreasing
 *
 * @returns interpolated value of array b at position value_a
 */
float interpolate(const float a[], const float b[], size_t size, float value_a);

/**
 * Convert byte to bit-string
 *
 * Attention: Uses static buffer, not thread-safe
 *
 * @returns pointer to bit-string (8 characters + null-byte)
 */
const char *byte2bitstr(uint8_t b);

/**
 * @brief Check if a buffer is entirely zeroed.
 *
 * @param buf A pointer to the buffer (uint8_t*) to be checked.
 * @param size The size of the buffer in bytes.
 * @returns true if the buffer is entirely zeroed, false if not.
 */
bool is_empty(uint8_t *buf, size_t size);

#endif /* INC_HELPER_H_ */
