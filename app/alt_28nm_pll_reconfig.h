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
 
#ifndef __ALT_28NM_PLL_RECONFIG_H__
#define __ALT_28NM_PLL_RECONFIG_H__

#include "alt_pll_reconfig_interface.h"
#include <vector>
#include <fstream>

class alt_28nm_pll_reconfig : public virtual alt_pll_reconfig_interface
{
 public:
  alt_28nm_pll_reconfig(void);
  alt_28nm_pll_reconfig(std::string family);
  ~alt_28nm_pll_reconfig(void);
   bool calculate_pll_parameters(void);
   bool is_supported_family(std::string family);
   bool check_fref(unsigned int fref);
   bool check_fout(unsigned int fout);
   bool check_speedgrade(unsigned int speedgrade);
   std::string get_supported_families_string(void);
   void load_legal_values(void);
   //calling load here is kind of bad as the sequence necessary is not obvious
   //I need to know the family and the speed grade prior to loading legal values
   void set_speedgrade(unsigned int speedgrade){m_speed_grade = speedgrade;load_legal_values();};
   bool request_new_settings(void);
 private:
   std::vector<std::string> m_families;
   std::vector<unsigned int> m_speed_grades;
   
   void init_family_list(void)
   {
     m_families.push_back("cyclonev");

     m_speed_grades.push_back(6);
     m_speed_grades.push_back(7);
     m_speed_grades.push_back(8);
   }
   std::string m_frequency_sys_file;
   std::string m_parameters_sys_file;
   std::string m_lock_sys_file;
   std::ifstream m_frequency_sys_stream;
   std::ifstream m_lock_sys_stream;
   std::ofstream m_parameters_sys_stream;
   unsigned int m_bandwidth, m_vco_div, m_c_pump;

 protected:
};

#endif /*__ALT_28NM_PLL_RECONFIG_H__*/
