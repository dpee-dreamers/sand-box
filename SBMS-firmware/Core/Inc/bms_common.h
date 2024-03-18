/*
 * bms_common.h
 *
 *  Created on: Mar 18, 2024
 *      Author: bobo
 */

#ifndef INC_BMS_COMMON_H_
#define INC_BMS_COMMON_H_

#define BMS_SWITCH_CHG  BIT(0)
#define BMS_SWITCH_DIS  BIT(1)
#define BMS_SWITCH_PDSG BIT(2)
#define BMS_SWITCH_PCHG BIT(3)

/*
 * BMS error flags
 */
#define BMS_ERR_CELL_UNDERVOLTAGE BIT(0)  ///< Cell undervoltage flag
#define BMS_ERR_CELL_OVERVOLTAGE  BIT(1)  ///< Cell overvoltage flag
#define BMS_ERR_SHORT_CIRCUIT     BIT(2)  ///< Pack short circuit (discharge direction)
#define BMS_ERR_DIS_OVERCURRENT   BIT(3)  ///< Pack overcurrent (discharge direction)
#define BMS_ERR_CHG_OVERCURRENT   BIT(4)  ///< Pack overcurrent (charge direction)
#define BMS_ERR_OPEN_WIRE         BIT(5)  ///< Cell open wire
#define BMS_ERR_DIS_UNDERTEMP     BIT(6)  ///< Temperature below discharge minimum limit
#define BMS_ERR_DIS_OVERTEMP      BIT(7)  ///< Temperature above discharge maximum limit
#define BMS_ERR_CHG_UNDERTEMP     BIT(8)  ///< Temperature below charge maximum limit
#define BMS_ERR_CHG_OVERTEMP      BIT(9)  ///< Temperature above charge maximum limit
#define BMS_ERR_INT_OVERTEMP      BIT(10) ///< Internal temperature above limit (e.g. BMS IC)
#define BMS_ERR_CELL_FAILURE      BIT(11) ///< Cell failure (too high voltage difference)
#define BMS_ERR_DIS_OFF           BIT(12) ///< Discharge FET is off even though it should be on
#define BMS_ERR_CHG_OFF           BIT(13) ///< Charge FET is off even though it should be on
#define BMS_ERR_FET_OVERTEMP      BIT(14) ///< MOSFET temperature above limit
#define BMS_ERR_ALL               GENMASK(14, 0)


#endif /* INC_BMS_COMMON_H_ */
