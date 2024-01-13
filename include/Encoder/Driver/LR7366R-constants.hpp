#pragma once
#include <cstdint>

//LS7366R to 90s8515 and ATmega32 SPI interface example
/***MDR0 configuration data - the configuration byte is formed with***
***single segments taken from each group and ORing all together.***/
// Count modes
const uint8_t NQUAD = 0x00; // non-quadrature mode
const uint8_t QUADRX1 = 0x01; // X1 quadrature mode
const uint8_t QUADRX2 = 0x02; // X2 quadrature mode
const uint8_t QUADRX4 = 0x03; // X4 quadrature mode

// Running modes
const uint8_t FREE_RUN = 0x00;
const uint8_t SINGE_CYCLE = 0x04;
const uint8_t RANGE_LIMIT = 0x08;
const uint8_t MODULO_N = 0x0C;

// Index modes
const uint8_t DISABLE_INDX = 0x00; // index_disabled
const uint8_t INDX_LOADC = 0x10; // index_load_CNTR
const uint8_t INDX_RESETC = 0x20; // index_reset_CNTR
const uint8_t INDX_LOADO = 0x30; // index_load_OL
const uint8_t ASYNCH_INDX = 0x00; // asynchronous index
const uint8_t SYNCH_INDX = 0x80; // synchronous index

// Clock filter modes
const uint8_t FILTER_1 = 0x00; // filter clock frequency division factor 1
const uint8_t FILTER_2 = 0x80; // filter clock frequency division factor 2

// MDR1 configuration data; any of these can be ORed together
// Flag modes
const uint8_t NO_FLAGS = 0x00; // all flags disabled
const uint8_t IDX_FLAG = 0x10; // IDX flag
const uint8_t CMP_FLAG = 0x20; // CMP flag
const uint8_t BW_FLAG = 0x40; // BW flag
const uint8_t CY_FLAG = 0x80; // CY flag

// 1 to 4 bytes data-width
const uint8_t BYTE_4 = 0x00;

// four byte mode
const uint8_t BYTE_3 = 0x01; // three byte mode
const uint8_t BYTE_2 = 0x02; // two byte mode
const uint8_t BYTE_1 = 0x03; // one byte mode

// Enable/disable counter
const uint8_t EN_CNTR = 0x00; // counting enabled
const uint8_t DIS_CNTR = 0x04; // counting disabled

// LS7366R op-code list
const uint8_t CLR_MDR0 = 0x08;
const uint8_t CLR_MDR1 = 0x10;
const uint8_t CLR_CNTR = 0x20;
const uint8_t CLR_STR = 0x30;
const uint8_t READ_MDR0 = 0x48;
const uint8_t READ_MDR1 = 0x50;
const uint8_t READ_CNTR = 0x60;
const uint8_t READ_OTR = 0x68;
const uint8_t READ_STR = 0x70;
const uint8_t WRITE_MDR1 = 0x90;
const uint8_t WRITE_MDR0 = 0x88;
const uint8_t WRITE_DTR = 0x98;
const uint8_t LOAD_CNTR = 0xE0;
const uint8_t LOAD_OTR = 0xE4;