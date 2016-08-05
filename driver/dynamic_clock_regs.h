/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2003 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
*                                                                             *
******************************************************************************/

#ifndef __ALTERA_DYNAMIC_CLOCK_REGS_H__
#define __ALTERA_DYNAMIC_CLOCK_REGS_H__

#define SYSTEM_BUS_WIDTH (32)
#define __IO_CALC_ADDRESS_NATIVE(BASE, REGNUM) \
  ((void *)(((unsigned char*)BASE) + ((REGNUM) * (SYSTEM_BUS_WIDTH/8))))
#define IORD(BASE, REGNUM) \
  *(unsigned long*)(__IO_CALC_ADDRESS_NATIVE ((BASE), (REGNUM)))
#define IOWR(BASE, REGNUM, DATA) \
  *(unsigned long*)(__IO_CALC_ADDRESS_NATIVE ((BASE), (REGNUM))) = (DATA)

/* MODE register */
#define ALTERA_DYNAMIC_CLOCK_MODE_REG              0
#define IOADDR_ALTERA_DYNAMIC_CLOCK_MODE(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_MODE_REG)
#define IORD_ALTERA_DYNAMIC_CLOCK_MODE(base) IORD(base, ALTERA_DYNAMIC_CLOCK_MODE_REG) 
#define IOWR_ALTERA_DYNAMIC_CLOCK_MODE(base, data) IOWR(base, ALTERA_DYNAMIC_CLOCK_MODE_REG, data)
#define ALTERA_DYNAMIC_CLOCK_MODE_MSK           (0x1)
#define ALTERA_DYNAMIC_CLOCK_MODE_OFST          (0)
#define ALTERA_DYNAMIC_CLOCK_POLL_MODE          (0x1)
#define ALTERA_DYNAMIC_CLOCK_WAIT_MODE          (0)


/* Status register */
#define ALTERA_DYNAMIC_CLOCK_STATUS_REG              1
#define IOADDR_ALTERA_DYNAMIC_CLOCK_STATUS(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_STATUS_REG)
#define IORD_ALTERA_DYNAMIC_CLOCK_STATUS(base) IORD(base, ALTERA_DYNAMIC_CLOCK_STATUS_REG) 
#define IOWR_ALTERA_DYNAMIC_CLOCK_STATUS(base, data) IOWR(base, ALTERA_DYNAMIC_CLOCK_STATUS_REG, data)
#define ALTERA_DYNAMIC_CLOCK_STATUS_MSK           (0x1)
#define ALTERA_DYNAMIC_CLOCK_STATUS_OFST          (0)
#define ALTERA_DYNAMIC_CLOCK_STATUS_BUSY          (0)
#define ALTERA_DYNAMIC_CLOCK_STATUS_READY         (1)


/* Start register */
#define ALTERA_DYNAMIC_CLOCK_START_REG              2
#define IOADDR_ALTERA_DYNAMIC_CLOCK_START(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_START_REG)
#define IORD_ALTERA_DYNAMIC_CLOCK_START(base) IORD(base, ALTERA_DYNAMIC_CLOCK_START_REG) 
#define IOWR_ALTERA_DYNAMIC_CLOCK_START(base, data) IOWR(base, ALTERA_DYNAMIC_CLOCK_START_REG, data)
#define ALTERA_DYNAMIC_CLOCK_START_MSK           (0x1)
#define ALTERA_DYNAMIC_CLOCK_START_OFST          (0)
#define ALTERA_DYNAMIC_CLOCK_START               (0x1)



/* N_Counter register */
#define ALTERA_DYNAMIC_CLOCK_N_COUNTER_REG              3
#define IOADDR_ALTERA_DYNAMIC_CLOCK_N_COUNTER(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_N_COUNTER_REG)
#define IORD_ALTERA_DYNAMIC_CLOCK_N_COUNTER(base) IORD(base, ALTERA_DYNAMIC_CLOCK_N_COUNTER_REG) 
#define IOWR_ALTERA_DYNAMIC_CLOCK_N_COUNTER(base, data) IOWR(base, ALTERA_DYNAMIC_CLOCK_N_COUNTER_REG, data)
#define ALTERA_DYNAMIC_CLOCK_N_COUNTER_LOW_MSK           (0xFF)
#define ALTERA_DYNAMIC_CLOCK_N_COUNTER_LOW_OFST          (0)
#define ALTERA_DYNAMIC_CLOCK_N_COUNTER_HIGH_MSK          (0xFF)
#define ALTERA_DYNAMIC_CLOCK_N_COUNTER_HIGH_OFST         (8)
#define ALTERA_DYNAMIC_CLOCK_N_COUNTER_BYPASS_MSK        (0x1)
#define ALTERA_DYNAMIC_CLOCK_N_COUNTER_BYPASS_OFST       (16)
#define ALTERA_DYNAMIC_CLOCK_N_COUNTER_DIVISION_MSK      (0x1)
#define ALTERA_DYNAMIC_CLOCK_N_COUNTER_DIVISION_OFST     (17)


/* M_Counter register */
#define ALTERA_DYNAMIC_CLOCK_M_COUNTER_REG              4
#define IOADDR_ALTERA_DYNAMIC_CLOCK_M_COUNTER(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_M_COUNTER_REG)
#define IORD_ALTERA_DYNAMIC_CLOCK_M_COUNTER(base) IORD(base, ALTERA_DYNAMIC_CLOCK_M_COUNTER_REG) 
#define IOWR_ALTERA_DYNAMIC_CLOCK_M_COUNTER(base, data) IOWR(base, ALTERA_DYNAMIC_CLOCK_M_COUNTER_REG, data)
#define ALTERA_DYNAMIC_CLOCK_M_COUNTER_LOW_MSK           (0xFF)
#define ALTERA_DYNAMIC_CLOCK_M_COUNTER_LOW_OFST          (0)
#define ALTERA_DYNAMIC_CLOCK_M_COUNTER_HIGH_MSK           (0xFF)
#define ALTERA_DYNAMIC_CLOCK_M_COUNTER_HIGH_OFST          (8)
#define ALTERA_DYNAMIC_CLOCK_M_COUNTER_BYPASS_MSK           (0x1)
#define ALTERA_DYNAMIC_CLOCK_M_COUNTER_BYPASS_OFST          (16)
#define ALTERA_DYNAMIC_CLOCK_M_COUNTER_DIVISION_MSK      (0x1)
#define ALTERA_DYNAMIC_CLOCK_M_COUNTER_DIVISION_OFST     (17)


/* C_Counter register */
#define ALTERA_DYNAMIC_CLOCK_C_COUNTER_REG              5
#define IOADDR_ALTERA_DYNAMIC_CLOCK_C_COUNTER(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_C_COUNTER_REG)
#define IORD_ALTERA_DYNAMIC_CLOCK_C_COUNTER(base) IORD(base, ALTERA_DYNAMIC_CLOCK_C_COUNTER_REG) 
#define IOWR_ALTERA_DYNAMIC_CLOCK_C_COUNTER(base, data) IOWR(base, ALTERA_DYNAMIC_CLOCK_C_COUNTER_REG, data)
#define ALTERA_DYNAMIC_CLOCK_C_COUNTER_LOW_MSK           (0xFF)
#define ALTERA_DYNAMIC_CLOCK_C_COUNTER_LOW_OFST          (0)
#define ALTERA_DYNAMIC_CLOCK_C_COUNTER_HIGH_MSK          (0xFF)
#define ALTERA_DYNAMIC_CLOCK_C_COUNTER_HIGH_OFST         (8)
#define ALTERA_DYNAMIC_CLOCK_C_COUNTER_BYPASS_MSK        (0x1)
#define ALTERA_DYNAMIC_CLOCK_C_COUNTER_BYPASS_OFST       (16)
#define ALTERA_DYNAMIC_CLOCK_C_COUNTER_DIVISION_MSK      (0x1)
#define ALTERA_DYNAMIC_CLOCK_C_COUNTER_DIVISION_OFST     (17)
#define ALTERA_DYNAMIC_CLOCK_C_COUNTER_SELECT_MSK        (0x1F)
#define ALTERA_DYNAMIC_CLOCK_C_COUNTER_SELECT_OFST       (18)

#define ALTERA_DYNAMIC_CLOCK_C0_COUNTER_REG              10
#define IOADDR_ALTERA_DYNAMIC_CLOCK_C0_COUNTER(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_C0_COUNTER_REG)
#define ALTERA_DYNAMIC_CLOCK_C1_COUNTER_REG              11
#define ALTERA_DYNAMIC_CLOCK_C2_COUNTER_REG              12
#define ALTERA_DYNAMIC_CLOCK_C3_COUNTER_REG              13
#define ALTERA_DYNAMIC_CLOCK_C4_COUNTER_REG              14
#define ALTERA_DYNAMIC_CLOCK_C5_COUNTER_REG              15
#define ALTERA_DYNAMIC_CLOCK_C6_COUNTER_REG              16
#define ALTERA_DYNAMIC_CLOCK_C7_COUNTER_REG              17
#define ALTERA_DYNAMIC_CLOCK_C8_COUNTER_REG              18
#define ALTERA_DYNAMIC_CLOCK_C9_COUNTER_REG              19
#define ALTERA_DYNAMIC_CLOCK_C10_COUNTER_REG              20
#define ALTERA_DYNAMIC_CLOCK_C11_COUNTER_REG              21
#define ALTERA_DYNAMIC_CLOCK_C12_COUNTER_REG              22
#define ALTERA_DYNAMIC_CLOCK_C13_COUNTER_REG              23
#define ALTERA_DYNAMIC_CLOCK_C14_COUNTER_REG              24
#define ALTERA_DYNAMIC_CLOCK_C15_COUNTER_REG              25
#define ALTERA_DYNAMIC_CLOCK_C16_COUNTER_REG              26
#define ALTERA_DYNAMIC_CLOCK_C17_COUNTER_REG              27

#define ALTERA_DYNAMIC_CLOCK_C0_COUNTER                  (0)
#define ALTERA_DYNAMIC_CLOCK_C1_COUNTER                  (1)
#define ALTERA_DYNAMIC_CLOCK_C2_COUNTER                  (2)
#define ALTERA_DYNAMIC_CLOCK_C3_COUNTER                  (3)
#define ALTERA_DYNAMIC_CLOCK_C4_COUNTER                  (4)
#define ALTERA_DYNAMIC_CLOCK_C5_COUNTER                  (5)
#define ALTERA_DYNAMIC_CLOCK_C6_COUNTER                  (6)
#define ALTERA_DYNAMIC_CLOCK_C7_COUNTER                  (7)
#define ALTERA_DYNAMIC_CLOCK_C8_COUNTER                  (8)
#define ALTERA_DYNAMIC_CLOCK_C9_COUNTER                  (9)
#define ALTERA_DYNAMIC_CLOCK_C10_COUNTER                 (10)
#define ALTERA_DYNAMIC_CLOCK_C11_COUNTER                 (11)
#define ALTERA_DYNAMIC_CLOCK_C12_COUNTER                 (12)
#define ALTERA_DYNAMIC_CLOCK_C13_COUNTER                 (13)
#define ALTERA_DYNAMIC_CLOCK_C14_COUNTER                 (14)
#define ALTERA_DYNAMIC_CLOCK_C15_COUNTER                 (15)
#define ALTERA_DYNAMIC_CLOCK_C16_COUNTER                 (16)
#define ALTERA_DYNAMIC_CLOCK_C17_COUNTER                 (17)




  /* P_Shift register */
#define ALTERA_DYNAMIC_CLOCK_P_SHIFT_REG              6
#define IOADDR_ALTERA_DYNAMIC_CLOCK_P_SHIFT(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_P_SHIFT_REG)
#define IORD_ALTERA_DYNAMIC_CLOCK_P_SHIFT(base) IORD(base, ALTERA_DYNAMIC_CLOCK_P_SHIFT_REG) 
#define IOWR_ALTERA_DYNAMIC_CLOCK_P_SHIFT(base, data) IOWR(base, ALTERA_DYNAMIC_CLOCK_P_SHIFT_REG, data)
#define ALTERA_DYNAMIC_CLOCK_P_SHIFT_MSK           (0xFFFF)
#define ALTERA_DYNAMIC_CLOCK_P_SHIFT_OFST          (0)
#define ALTERA_DYNAMIC_CLOCK_P_SHIFT_C_SEL_MSK     (0x1F)
#define ALTERA_DYNAMIC_CLOCK_P_SHIFT_C_SEL_OFST    (16)
#define ALTERA_DYNAMIC_CLOCK_P_SHIFT_UPDOWN_MSK    (0x1)
#define ALTERA_DYNAMIC_CLOCK_P_SHIFT_UPDOWN_OFST   (17)




  /* M_Counter_Frac register */
#define ALTERA_DYNAMIC_CLOCK_M_COUNTER_FRAC_REG              7
#define IOADDR_ALTERA_DYNAMIC_CLOCK_M_COUNTER_FRAC(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_M_COUNTER_FRAC_REG)
#define IORD_ALTERA_DYNAMIC_CLOCK_M_COUNTER_FRAC(base) IORD(base, ALTERA_DYNAMIC_CLOCK_M_COUNTER_FRAC_REG) 
#define IOWR_ALTERA_DYNAMIC_CLOCK_M_COUNTER_FRAC(base, data) IOWR(base, ALTERA_DYNAMIC_CLOCK_M_COUNTER_FRAC_REG, data)
#define ALTERA_DYNAMIC_CLOCK_M_COUNTER_FRAC_MSK           (0xFFFFFFFF)
#define ALTERA_DYNAMIC_CLOCK_M_COUNTER_FRAC_OFST          (0)



  /* Bandwidth register */
#define ALTERA_DYNAMIC_CLOCK_BANDWIDTH_REG              8
#define IOADDR_ALTERA_DYNAMIC_CLOCK_BANDWIDTH(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_BANDWIDTH_REG)
#define IORD_ALTERA_DYNAMIC_CLOCK_BANDWIDTH(base) IORD(base, ALTERA_DYNAMIC_CLOCK_BANDWIDTH_REG) 
#define IOWR_ALTERA_DYNAMIC_CLOCK_BANDWIDTH(base, data) IOWR(base, ALTERA_DYNAMIC_CLOCK_BANDWIDTH_REG, data)
#define ALTERA_DYNAMIC_CLOCK_BANDWIDTH_MSK           (0xF)
#define ALTERA_DYNAMIC_CLOCK_BANDWIDTH_OFST          (0)



  /* C_Pump register */
#define ALTERA_DYNAMIC_CLOCK_C_PUMP_REG              9
#define IOADDR_ALTERA_DYNAMIC_CLOCK_C_PUMP(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_C_PUMP_REG)
#define IORD_ALTERA_DYNAMIC_CLOCK_C_PUMP(base) IORD(base, ALTERA_DYNAMIC_CLOCK_C_PUMP_REG) 
#define IOWR_ALTERA_DYNAMIC_CLOCK_C_PUMP(base, data) IOWR(base, ALTERA_DYNAMIC_CLOCK_C_PUMP_REG, data)
#define ALTERA_DYNAMIC_CLOCK_C_PUMP_MSK           (0x7)
#define ALTERA_DYNAMIC_CLOCK_C_PUMP_OFST          (0)


  /* Vco_Div register */
#define ALTERA_DYNAMIC_CLOCK_VCO_DIV_REG              28
#define IOADDR_ALTERA_DYNAMIC_CLOCK_VCO_DIV(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_VCO_DIV_REG)
#define IORD_ALTERA_DYNAMIC_CLOCK_VCO_DIV(base) IORD(base, ALTERA_DYNAMIC_CLOCK_VCO_DIV_REG) 
#define IOWR_ALTERA_DYNAMIC_CLOCK_VCO_DIV(base, data) IOWR(base, ALTERA_DYNAMIC_CLOCK_VCO_DIV_REG, data)
#define ALTERA_DYNAMIC_CLOCK_VCO_DIV_MSK           (0x1)
#define ALTERA_DYNAMIC_CLOCK_VCO_DIV_OFST          (0)



  /* Mif_Base_Div register */
#define ALTERA_DYNAMIC_CLOCK_MIF_BASE_DIV_REG              31
#define IOADDR_ALTERA_DYNAMIC_CLOCK_MIF_BASE_DIV(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_MIF_BASE_DIV_REG)
#define IORD_ALTERA_DYNAMIC_CLOCK_MIF_BASE_DIV(base) IORD(base, ALTERA_DYNAMIC_CLOCK_MIF_BASE_DIV_REG) 
#define IOWR_ALTERA_DYNAMIC_CLOCK_MIF_BASE_DIV(base, data) IOWR(base, ALTERA_DYNAMIC_CLOCK_MIF_BASE_DIV_REG, data)
#define ALTERA_DYNAMIC_CLOCK_MIF_BASE_DIV_MSK           (0x1FF)
#define ALTERA_DYNAMIC_CLOCK_MIF_BASE_DIV_OFST          (0)


  /* Frequency Counter register */
#define ALTERA_DYNAMIC_CLOCK_FREQ_REG              64
#define IOADDR_ALTERA_DYNAMIC_FREQ(base) \
  __IO_CALC_ADDRESS_NATIVE(base, ALTERA_DYNAMIC_CLOCK_FREQ_REG)
#define IORD_ALTERA_DYNAMIC_CLOCK_FREQ(base) IORD(base, ALTERA_DYNAMIC_CLOCK_FREQ_REG) 
#define IOWR_ALTERA_DYNAMIC_CLOCK_FREQ(base, data) IOWR(base, ALTERA_DYNAMIC_CLOCK_FREQ_REG, data)
#define ALTERA_DYNAMIC_CLOCK_FREQ_MSK           (0xFFFFF)
#define ALTERA_DYNAMIC_CLOCK_FREQ_OFST          (0)



#endif /*__ALTERA_DYNAMIC_CLOCK_REGS_H__*/
