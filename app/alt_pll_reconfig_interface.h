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

#ifndef __ALT_PLL_RECONFIG_INTERFACE_H__
#define __ALT_PLL_RECONFIG_INTERFACE_H__
#include <string>
class alt_pll_reconfig_interface
{
 public:
  alt_pll_reconfig_interface(void);
  alt_pll_reconfig_interface(std::string family);
  virtual ~alt_pll_reconfig_interface(void);
  virtual void calculate_pll_parameters(unsigned int fref, unsigned int fout) = 0;
  virtual bool is_supported_family(std::string family) = 0;
  virtual bool check_fref(unsigned int fref) = 0;
  virtual bool check_fout(unsigned int fout) = 0;
  virtual bool check_speedgrade(unsigned int speedgrade) = 0;
  virtual std::string get_supported_families_string(void) = 0;
  virtual void load_legal_values(void) = 0;
  virtual void set_speedgrade(unsigned int speedgrade) = 0;
  void set_family(std::string family){m_family = family;};

 private:
 protected:
  unsigned int m_speed_grade;
  unsigned int m_fout_min;
  unsigned int m_fout_max;
  unsigned int m_fref_min;
  unsigned int m_fref_max;
  unsigned int m_fpfd_min;
  unsigned int m_fpfd_max;
  unsigned int m_fvco_max;
  unsigned int m_fvco_min;
  unsigned int m_c_min;
  unsigned int m_c_max;
  unsigned int m_n_min;
  unsigned int m_n_max;
  unsigned int m_m_min;
  unsigned int m_m_max;



  std::string m_family;
};
#endif /*__ALT_PLL_RECONFIG_INTERFACE_H__*/
