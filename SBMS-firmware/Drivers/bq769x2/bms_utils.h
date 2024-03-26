/*
 * bms_utils.h
 *
 *  Created on: Mar 23, 2024
 *      Author: bobo
 */

#ifndef BQ769X2_BMS_UTILS_H_
#define BQ769X2_BMS_UTILS_H_

#define BITS_PER_LONG	(32)

#define ARRAY_SIZE(array) \
    (sizeof(array) / sizeof(*array))

#define BIT(nr) (1UL << (nr))

#define CLAMP(value, low, high) (((value)<(low))?(low):(((value)>(high))?(high):(value)))

#define GENMASK(high, low) (((1UL << ((high) - (low) + 1)) - 1) << (low))

#define IN_RANGE(n, low, high) ((n) >= (low) && (n) <= (high) ? 1 : 0)

#define __maybe_unused  __attribute__((unused))

uint8_t crc8_ccitt(const void * data, size_t size);

static unsigned int find_msb_set(uint32_t op)
{
	if (op == 0) {
		return 0;
	}

	return 32 - __builtin_clz(op);
};



#endif /* BQ769X2_BMS_UTILS_H_ */
