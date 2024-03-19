/*
 * bms_ic.h
 *
 *  Created on: Mar 18, 2024
 *      Author: bobo
 */

#ifndef INC_BMS_IC_H_
#define INC_BMS_IC_H_

#include "bms.h"

#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

/* Caution: Maximum number of flags is 31 (BIT(30)) because the flags must fit to an int32_t */
#define BMS_IC_CONF_VOLTAGE_LIMITS BIT(0)
#define BMS_IC_CONF_TEMP_LIMITS    BIT(1)
#define BMS_IC_CONF_CURRENT_LIMITS BIT(2)
#define BMS_IC_CONF_BALANCING      BIT(3)
#define BMS_IC_CONF_ALERTS         BIT(4)
#define BMS_IC_CONF_VOLTAGE_REGS   BIT(5)
#define BMS_IC_CONF_ALL            GENMASK(5, 0)

#define BMS_IC_DATA_CELL_VOLTAGES BIT(0)
#define BMS_IC_DATA_PACK_VOLTAGES BIT(1)
#define BMS_IC_DATA_TEMPERATURES  BIT(2)
#define BMS_IC_DATA_CURRENT       BIT(3)
#define BMS_IC_DATA_BALANCING     BIT(4)
#define BMS_IC_DATA_ERROR_FLAGS   BIT(5)
#define BMS_IC_DATA_ALL           GENMASK(5, 0)

#define BMS_IC_BALANCING_OFF  (0)
#define BMS_IC_BALANCING_AUTO (UINT32_MAX)

/**
 * @cond INTERNAL_HIDDEN
 *
 * Zephyr driver API function pointer declarations (see further down for documentation)
 */

typedef int (*bms_ic_api_configure)(const struct device *dev, struct bms_ic_conf *ic_conf,
                                    uint32_t flags);

typedef void (*bms_ic_api_assign_data)(const struct device *dev, struct bms_ic_data *ic_data);

typedef int (*bms_ic_api_read_data)(const struct device *dev, uint32_t flags);

typedef int (*bms_ic_api_set_switches)(const struct device *dev, uint8_t switches, bool enabled);

typedef int (*bms_ic_api_balance)(const struct device *dev, uint32_t cells);

typedef int (*bms_ic_api_set_mode)(const struct device *dev, enum bms_ic_mode mode);

typedef int (*bms_ic_api_read_mem)(const struct device *dev, const uint16_t addr, uint8_t *data,
                                   const size_t len);

typedef int (*bms_ic_api_write_mem) (const struct device *dev, const uint16_t addr,
                                    const uint8_t *data, const size_t len);

typedef int (*bms_ic_api_debug_print_mem) (const struct device *dev);

struct bms_ic_driver_api
{
    bms_ic_api_configure        configure;
    bms_ic_api_assign_data      assign_data;
    bms_ic_api_read_data        read_data;
    bms_ic_api_set_switches     set_switches;
    bms_ic_api_balance          balance;
    bms_ic_api_set_mode         set_mode;
    bms_ic_api_read_mem         read_mem;
    bms_ic_api_write_mem        write_mem;
    bms_ic_api_debug_print_mem  debug_print_mem;
};

/**
 * @endcond
 */

/**
 * @brief Write config to IC.
 *
 * Most BMS ICs can apply configuration values only in discrete steps or with limited resolution.
 * The actually applied configuration is written back to ic_conf.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param ic_conf BMS configuration to apply.
 * @param flags Flags to specify which parts of the configuration should be applied. See
 *              BMS_IC_CONF_* defines for valid flags.
 *
 * @retval appl_flags successfully applied configuration flags (may be different than requested)
 * @retval -ENOTSUP if none of the requested flags is supported
 * @retval -EIO for communication error
 */
static inline int bms_ic_configure(const struct device *dev, struct bms_ic_conf *ic_conf,
                                   uint32_t flags)
{
    const struct bms_ic_driver_api *api = (const struct bms_ic_driver_api *)dev->api;

    if (api->configure == NULL) {
        return -ENOSYS;
    }

    return api->configure(dev, ic_conf, flags);
}

/**
 * @brief Assign bms_ic_data object to use for reading data from the IC.
 *
 * This data is updated by calls to @a bms_ic_read_data.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param ic_data Pointer to a statically allocated bms_ic_data object.
 *
 * @return 0 for success or negative error code otherwise.
 */
static inline void bms_ic_assign_data(const struct device *dev, struct bms_ic_data *ic_data)
{
    const struct bms_ic_driver_api *api = (const struct bms_ic_driver_api *)dev->api;

    api->assign_data(dev, ic_data);
}

/**
 * @brief Read data from the IC.
 *
 * @a bms_ic_assign_data must be called before using this function.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param flags Flags to specify which parts of the data should be updated. See BMS_IC_DATA_*
 *              defines for valid flags.
 *
 * @retval 0 for success
 * @retval -EINVAL if not all requested data is provided by the IC
 * @retval -EIO for communication error
 * @retval -ENOMEM if the data was not assigned with @a bms_ic_assign_data
 */
static inline int bms_ic_read_data(const struct device *dev, uint32_t flags)
{
    const struct bms_ic_driver_api *api = (const struct bms_ic_driver_api *)dev->api;

    return api->read_data(dev, flags);
}

#ifdef CONFIG_BMS_IC_SWITCHES
/**
 * @brief Switch the specified MOSFET(s) on or off.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param switches MOSFET(s) to switch on/off.
 * @param enabled If the MOSFET(s) should be enabled (on) or disabled (off)
 *
 * @return 0 for success or negative error code otherwise.
 */
static inline int bms_ic_set_switches(const struct device *dev, uint8_t switches, bool enabled)
{
    const struct bms_ic_driver_api *api = (const struct bms_ic_driver_api *)dev->api;

    if (api->set_switches == NULL) {
        return -ENOSYS;
    }

    return api->set_switches(dev, switches, enabled);
}
#endif

/**
 * @brief Update the balancing operation of the IC.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param cells Bitset defining the cell(s) to be balanced. Set to BMS_IC_BALANCING_OFF to disable
 *              balancing and BMS_IC_BALANCING_AUTO to enable automatic balancing.
 *
 * @return 0 for success or negative error code otherwise.
 */
static inline int bms_ic_balance(const struct device *dev, uint32_t cells)
{
    const struct bms_ic_driver_api *api = (const struct bms_ic_driver_api *)dev->api;

    return api->balance(dev, cells);
}

/**
 * @brief Request the IC to go into specified operating mode.
 *
 * Usually used to set the device into different sleep modes for reduced power consumption.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param mode Desired BMS IC operating mode.
 *
 * @return 0 for success or negative error code otherwise.
 */
static inline int bms_ic_set_mode(const struct device *dev, enum bms_ic_mode mode)
{
    const struct bms_ic_driver_api *api = (const struct bms_ic_driver_api *)dev->api;

    if (api->set_mode == NULL) {
        return -ENOSYS;
    }

    return api->set_mode(dev, mode);
}

static inline int bms_ic_read_mem(const struct device *dev, const uint16_t addr, uint8_t *data,
                                  const size_t len)
{
    const struct bms_ic_driver_api *api = (const struct bms_ic_driver_api *)dev->api;

    if (api->read_mem == NULL) {
        return -ENOSYS;
    }

    return api->read_mem(dev, addr, data, len);
}

static inline int bms_ic_write_mem(const struct device *dev, const uint16_t addr,
                                   const uint8_t *data, const size_t len)
{
    const struct bms_ic_driver_api *api = (const struct bms_ic_driver_api *)dev->api;

    if (api->write_mem == NULL) {
        return -ENOSYS;
    }

    return api->write_mem(dev, addr, data, len);
}

static inline int bms_ic_debug_print_mem(const struct device *dev)
{
    const struct bms_ic_driver_api *api = (const struct bms_ic_driver_api *)dev->api;

    if (api->debug_print_mem == NULL) {
        return -ENOSYS;
    }

    return api->debug_print_mem(dev);
}


#endif /* INC_BMS_IC_H_ */
