/*
 * BMS_enum.h
 *
 *  Created on: 2023-12-29
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This file contains all typedef of enum
 */

#ifndef BMS_BMS_ENUM_H_
#define BMS_BMS_ENUM_H_

enum    SYS_STATE       {ON, OFF};
enum    CHARGE_MODE     {Fast, Balance};
enum    BATTERY_STATE   {None, Charging, Wait, Full};
enum    SLOT_SELECT     {Slot1, Slot2, Slot3};
enum    BUTTON_PRESS    {Long_Press, Short_Press};

#endif /* BMS_BMS_ENUM_H_ */
