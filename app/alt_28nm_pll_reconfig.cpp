#include <iostream>
#include <algorithm>
#include <assert.h>
#include "alt_28nm_pll_reconfig.h"



alt_28nm_pll_reconfig::alt_28nm_pll_reconfig(void)
{
  init_family_list();
}

void alt_28nm_pll_reconfig::calculate_pll_parameters(unsigned int fref, unsigned int fout)
{
  std::cout <<"calculate_pll_parameters" << fref << fout << std::endl;
}

alt_28nm_pll_reconfig::~alt_28nm_pll_reconfig(void)
{
    std::cout <<"destructor" << std::endl;
}

std::string alt_28nm_pll_reconfig::get_supported_families_string(void)
{
  std::string return_string;
  for(unsigned int i = 0; i < m_families.size(); i++){
    return_string.append(m_families[i]);
    return_string.append(" ");
  }
  return return_string;
}

bool alt_28nm_pll_reconfig::is_supported_family(std::string family)
{
  std::string fam = family;
  std::transform(fam.begin(), fam.end(),fam.begin(), ::tolower);
  return  std::find(m_families.begin(), m_families.end(),fam) != m_families.end();
}

bool alt_28nm_pll_reconfig::check_fref(unsigned int fref)
{
  return  (fref <= m_fref_max && fref >= m_fref_min);
}

bool alt_28nm_pll_reconfig::check_fout(unsigned int fout)
{
  return (fout <= m_fout_max && fout >= m_fout_min);
}

bool alt_28nm_pll_reconfig::check_speedgrade(unsigned int speedgrade)
{
  //family hasn't been set yet.  We can't check for valid speed grade until we know the family...
  assert(m_family != "no family");
  return  std::find(m_speed_grades.begin(), m_speed_grades.end(),speedgrade) != m_speed_grades.end();
}

void alt_28nm_pll_reconfig::load_legal_values(void)
{
  //add some protection on input values
  //insure we are 28nm
  //insure speed grade is legal
  //really shouldn't bury legal values here
  m_c_min = 0x1;
  m_c_max = 0xFFFF;
  m_n_min = 0x1;
  m_n_max = 0xFFFF;
  m_m_min = 0x1;
  m_m_max = 0xFFFF;
  m_fpfd_min = 5000000;
  m_fpfd_max = 325000000;
  m_fref_min = 25000000; //comeback and check this value
  switch(m_speed_grade)
  {
  case 6:
     m_fout_min = 1000;
     m_fvco_max = 1600000000;
     m_fout_max = 1600000000;
     m_fref_max = 800000000;
    break;
  case 7:
     m_fout_min = 1000;
     m_fvco_max = 1600000000;
     m_fout_max = 1340000000;
     m_fref_max = 700000000;
    break;
  case 8:
     m_fout_min = 1000;
     m_fout_max = 1066000000;
     m_fvco_max = 1300000000;
     m_fref_max = 650000000;

    break;
  default:
    assert(false);
  }
}
