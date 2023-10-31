/*
 * BMS_VAR.h
 *
 *  Created on: 2023-10-30
 *      Author: Tao Ran
 *              UBC Okanagan School of Engineering
 * Description: This file stores all external reference to BMS fundamental settings
 */

#ifndef BMS_BMS_EXT_H_
#define BMS_BMS_EXT_H_

//  ADC
extern  float   ADC_Convert_Offset_0,
                ADC_Convert_Offset_1,
                ADC_Convert_Offset_2,
                ADC_Convert_Offset_3;
extern  float   ADC_0, ADC_1, ADC_2, ADC_3;

//  System Control
extern  enum    S_STATE SysState;
//  Slot Info
extern  struct  SLOT    Slot_1, Slot_2, Slot_3;

#endif /* BMS_BMS_EXT_H_ */
