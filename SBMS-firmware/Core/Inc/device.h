/*
 * device.h
 *
 *  Created on: Mar 18, 2024
 *      Author: bobo
 */

#ifndef INC_DEVICE_H_
#define INC_DEVICE_H_

#include <stdbool.h>
#include <stdint.h>

struct device_state {

	uint8_t init_res;

	bool initialized : 1;
};

struct device{
	/** Name of the device instance */
	const char *name;
	/** Address of device instance config information */
	const void *config;
	/** Address of the API structure exposed by the device instance */
	const void *api;
	/** Address of the common device state */
	struct device_state *state;
	/** Address of the device instance private data */
	void *data;
};
#endif /* INC_DEVICE_H_ */
