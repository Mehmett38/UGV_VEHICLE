/**
 *  @brief crc15.h
 *  @data Created on: 19 Oca 2024
 *  @author: Mehmet Dinçer
 */

#ifndef LTC681X_CRC_CRC15_H_
#define LTC681X_CRC_CRC15_H_

#include <stdint.h>

#define CRC15_POLY  (0x4599)

void init_PEC15_Table();
uint16_t AE_pec15(uint8_t* data, uint16_t len);

#endif /* LTC681X_CRC_CRC15_H_ */
