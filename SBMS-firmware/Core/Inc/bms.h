/*
 * bms.h
 *
 *  Created on: Mar 18, 2024
 *      Author: bobo
 */

#ifndef INC_BMS_H_
#define INC_BMS_H_

#include <stdbool.h>
#include <stdint.h>

#include "bms_common.h"
//#include  "bms_ic.h"

/* fixed number of OCV vs. SOC points */
#define OCV_POINTS 21
#define CONFIG_BMS_IC_MAX_CELLS 16
#define CONFIG_BMS_IC_MAX_THERMISTORS 3

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
/**
 * BMS IC operation modes
 */
enum bms_ic_mode
{
    /** Normal operation */
    BMS_IC_MODE_ACTIVE,
    /** Low-power mode with FETs still enabled */
    BMS_IC_MODE_IDLE,
    /** Low-power mode with FETs off, but regulators still enabled, e.g. to power host MCU */
    BMS_IC_MODE_STANDBY,
    /** Lowest power mode with all FETs and regulators disabled */
    BMS_IC_MODE_OFF,
};

/**
 * BMS configuration values, stored in RAM.
 */
struct bms_ic_conf
{
    /* Cell voltage limits */
    /** Cell target charge voltage (V) */
    float cell_chg_voltage_limit;
    /** Cell discharge voltage limit (V) */
    float cell_dis_voltage_limit;
    /** Cell over-voltage limit (V) */
    float cell_ov_limit;
    /** Cell over-voltage error reset threshold (V) */
    float cell_ov_reset;
    /** Cell over-voltage delay (ms) */
    uint32_t cell_ov_delay_ms;
    /** Cell under-voltage limit (V) */
    float cell_uv_limit;
    /** Cell under-voltage error reset threshold (V)*/
    float cell_uv_reset;
    /** Cell under-voltage delay (ms) */
    uint32_t cell_uv_delay_ms;

#ifdef CONFIG_BMS_IC_CURRENT_MONITORING
    /* Current limits */
    /** Charge over-current limit (A) */
    float chg_oc_limit;
    /** Charge over-current delay (ms) */
    uint32_t chg_oc_delay_ms;
    /** Discharge over-current limit (A) */
    float dis_oc_limit;
    /** Discharge over-current delay (ms) */
    uint32_t dis_oc_delay_ms;
    /** Discharge short circuit limit (A) */
    float dis_sc_limit;
    /** Discharge short circuit delay (us) */
    uint32_t dis_sc_delay_us;
#endif

    /* Cell temperature limits */
    /** Discharge over-temperature (DOT) limit (°C) */
    float dis_ot_limit;
    /** Discharge under-temperature (DUT) limit (°C) */
    float dis_ut_limit;
    /** Charge over-temperature (COT) limit (°C) */
    float chg_ot_limit;
    /** Charge under-temperature (CUT) limit (°C) */
    float chg_ut_limit;
    /** Temperature limit hysteresis (°C) */
    float temp_limit_hyst;

    /* Balancing settings */
    /** Balancing cell voltage target difference (V) */
    float bal_cell_voltage_diff;
    /** Minimum cell voltage to start balancing (V) */
    float bal_cell_voltage_min;
    /** Current threshold to be considered idle (A) */
    float bal_idle_current;
    /** Minimum idle duration before balancing (s) */
    uint16_t bal_idle_delay;

    /* Built-in voltage regulator settings */
    /**
     * Bitfield to enable/disable built-in voltage regulators (usually LDOs). The bit positions
     * correspond to the regulator numbers in the manufacturer datasheet (e.g. 0x2 would enable
     * REG1).
     */
    uint8_t vregs_enable;

    /* Alert settings */
    /** Error flags which should trigger an alert action (if supported by the IC) */
    uint32_t alert_mask;
};

/**
 * Current BMS IC status including measurements and error flags
 */
struct bms_ic_data
{
    /** Single cell voltages (V) */
    float cell_voltages[CONFIG_BMS_IC_MAX_CELLS];
    /** Maximum cell voltage (V) */
    float cell_voltage_max;
    /** Minimum cell voltage (V) */
    float cell_voltage_min;
    /** Average cell voltage (V) */
    float cell_voltage_avg;
    /** Battery internal stack voltage (V) */
    float total_voltage;
#ifdef CONFIG_BMS_IC_SWITCHES
    /** Battery external pack voltage (V) */
    float external_voltage;
#endif

//#ifdef CONFIG_BMS_IC_CURRENT_MONITORING
    /** Module/pack current, charging direction has positive sign (A) */
    float current;
//#endif

    /** Cell temperatures (°C) */
    float cell_temps[CONFIG_BMS_IC_MAX_THERMISTORS];
    /** Maximum cell temperature (°C) */
    float cell_temp_max;
    /** Minimum cell temperature (°C) */
    float cell_temp_min;
    /** Average cell temperature (°C) */
    float cell_temp_avg;
    /** Internal BMS IC temperature (°C) */
    float ic_temp;
#ifdef CONFIG_BMS_IC_SWITCHES
    /** MOSFET temperature (°C) */
    float mosfet_temp;
#endif

    /** Actual number of cells connected (may be less than CONFIG_BMS_IC_MAX_CELLS) */
    uint8_t connected_cells;

    /** Actual number of thermistors used (may be less than CONFIG_BMS_IC_MAX_THERMISTORS) */
    uint8_t used_thermistors;

    /** Balancing channels on/off status */
    uint32_t balancing_status;

    /** BMS errors stored as BMS_ERR_* flags */
    uint32_t error_flags;
};
/**
 * Possible BMS states
 */
enum bms_state
{
    BMS_STATE_OFF,      ///< Off state (charging and discharging disabled)
    BMS_STATE_CHG,      ///< Charging state (discharging disabled)
    BMS_STATE_DIS,      ///< Discharging state (charging disabled)
    BMS_STATE_NORMAL,   ///< Normal operating mode (both charging and discharging enabled)
    BMS_STATE_SHUTDOWN, ///< BMS starting shutdown sequence
};

/**
 * Battery cell types
 */
enum bms_cell_type
{
    CELL_TYPE_CUSTOM = 0, ///< Custom settings
    CELL_TYPE_LFP,        ///< LiFePO4 Li-ion cells (3.3 V nominal)
    CELL_TYPE_NMC,        ///< NMC/Graphite Li-ion cells (3.7 V nominal)
    CELL_TYPE_LTO         ///< NMC/Titanate (2.4 V nominal)
};

/**
 * Battery Management System context information
 */
struct bms_context
{
    /** Current state of the battery */
    enum bms_state state;

    /** Manual enable/disable setting for charging */
    bool chg_enable;
    /** Manual enable/disable setting for discharging */
    bool dis_enable;

    /** CV charging to cell_chg_voltage_limit finished */
    bool full;
    /** Battery is discharged below cell_dis_voltage_limit */
    bool empty;

    /** Calculated State of Charge (%) */
    float soc;

    /** Nominal capacity of battery pack (Ah) */
    float nominal_capacity_Ah;

    /**
     * Pointer to an array containing the Open Circuit Voltage of the cell vs. SOC. The array
     * must be spaced the same as the soc_points.
     */
    float *ocv_points;

    /** Pointer to an array containing the State of Charge points for the OCV. */
    float *soc_points;

    /** BMS IC device pointer */
    const struct device *ic_dev;

    /** BMS IC configuration applied during start-up. */
    struct bms_ic_conf ic_conf;

    /** BMS IC data read from the device. */
    struct bms_ic_data ic_data;
};

/**
 * @brief Runtime device structure (in ROM) per driver instance
 */

/**
 * Initialization of struct bms_ic_conf with typical default values for the given cell type.
 *
 * @param bms Pointer to BMS object.
 * @param type One of enum CellType (defined as int so that it can be set via Kconfig).
 * @param nominal_capacity Nominal capacity of the battery pack.
 */
void bms_init_config(struct bms_context *bms, enum bms_cell_type type, float capacity_Ah);

/**
 * Main BMS state machine
 *
 * @param bms Pointer to BMS object.
 */
void bms_state_machine(struct bms_context *bms);

/**
 * Update SOC based on most recent current measurement
 *
 * Function should be called each time after a new current measurement was obtained.
 *
 * @param bms Pointer to BMS object.
 */
void bms_soc_update(struct bms_context *bms);

/**
 * Reset SOC to specified value or calculate based on average cell open circuit voltage
 *
 * @param bms Pointer to BMS object.
 * @param percent 0-100 %, -1 for calculation based on OCV
 */
void bms_soc_reset(struct bms_context *bms, int percent);

/**
 * Charging error flags check
 *
 * @returns true if any charging error flag is set
 */
bool bms_chg_error(uint32_t error_flags);

/**
 * Discharging error flags check
 *
 * @returns true if any discharging error flag is set
 */
bool bms_dis_error(uint32_t error_flags);

/**
 * Check if charging is allowed
 *
 * @returns true if no charging error flags are set
 */
bool bms_chg_allowed(struct bms_context *bms);

/**
 * Check if discharging is allowed
 *
 * @param bms Pointer to BMS object.
 *
 * @returns true if no discharging error flags are set
 */
bool bms_dis_allowed(struct bms_context *bms);


#endif /* INC_BMS_H_ */
