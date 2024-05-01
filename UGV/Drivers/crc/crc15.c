/**
 *  @brief crc15.c
 *  @data Created on: 19 Oca 2024
 *  @author: Mehmet Din�er
 */


#include "crc15.h"


uint16_t pec15Table[256];


void init_PEC15_Table()
{
    uint16_t remainder;
    uint16_t i;
    uint16_t bit;
    for (i = 0; i < 256; i++)
    {
        remainder = i << 7;
        for (bit = 8; bit > 0; --bit)
        {
            if (remainder & 0x4000)
            {
                remainder = ((remainder << 1));
                remainder = (remainder ^ CRC15_POLY);
            }
            else
            {
                remainder = ((remainder << 1));
            }
        }
        pec15Table[i] = remainder & 0xFFFF;
    }
}

uint16_t AE_pec15(uint8_t* data, uint16_t len)
{
    uint16_t remainder, address;
    remainder = 16;//PEC seed
    int i;
    for (i= 0; i < len; i++)
    {
        /**
         * @brief history of data[i*2 + 1]
         * @NOTE TMS570Ls spi working with 16bit variables so we need to
         * @Note cast to uint8_t so we take the 2 offset but
         * @Note TMS570 use big endien memory layout so we have to add +1
         */
        address = ((remainder >> 7) ^ data[i]) & 0xff;//calculate PEC table address remainder = (remainder << 8 ) ^ pec15Table[address];
        remainder = (remainder << 8) ^ pec15Table[address];
    }
    return (remainder * 2);//The CRC15 has a 0 in the LSB so the final value must be multiplied by 2
}
