#include "alt_pll_reconfig_interface.h"



alt_pll_reconfig_interface::alt_pll_reconfig_interface(void):
  m_speed_grade(0),
  m_family("no family")
{
}



alt_pll_reconfig_interface::~alt_pll_reconfig_interface(void)
{
}

bool alt_pll_reconfig_interface::sys_file_exist(const std::string& file)
{
  struct stat buf;
  return (stat(file.c_str(), &buf) != -1);
}


