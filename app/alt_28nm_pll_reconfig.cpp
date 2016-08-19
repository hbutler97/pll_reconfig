#include <iostream>
#include <algorithm>
#include <assert.h>
#include "alt_28nm_pll_reconfig.h"
#include <string>
#include <unistd.h>




alt_28nm_pll_reconfig::alt_28nm_pll_reconfig(void):
  m_frequency_sys_file("/sys/bus/platform/drivers/dynamic_clock/frequency"),
  m_parameters_sys_file("/sys/bus/platform/drivers/dynamic_clock/parameters"),
  m_lock_sys_file("/sys/bus/platform/drivers/dynamic_clock/lock_status"),
  m_bandwidth(7),
  m_vco_div(0),
  m_c_pump(1)
{
  init_family_list();
}

bool alt_28nm_pll_reconfig::calculate_pll_parameters(void)
{
  //add some protection to make sure all input has been validated
  //double check on vco_div
  bool status(false);
  unsigned int fref_calculated(0);
  
  std::cout << "Finding Legal PLL parameters for:" << std::endl;
  std::cout << "Device Family: " << m_family << std::endl;
  std::cout << "Device Speed Grade: " << m_speed_grade << std::endl;
  std::cout << "PLL Ref Clock Frequency: " << m_fref/1000 << " KHz" << std::endl;
  std::cout << "Requested PLL Output Frequency: " << m_fout/1000 << " KHz" << std::endl;
 
  for(unsigned long long c = m_c_min; c <= m_c_max && !status; c++){
    m_fvco = m_fout * c;
    if(m_fvco >= m_fvco_min && m_fvco <= m_fvco_max){
      //      m_vco_div = (m_fvco > m_fvco_max)?1:0;
      for(unsigned long long m = m_m_min; m <= m_m_max && !status; m++){
	//got some integer devision here which could be a problem
	//	m_fpfd = (m_vco_div == 1)?((m_fvco >> 1)/m):(m_fvco/m);
	m_fpfd = (m_fvco/m);
	if(m_fpfd >= m_fpfd_min && m_fpfd <= m_fpfd_max){
	  for(unsigned long long n = m_n_min; n < m_n_max && !status; n++){
	    fref_calculated = m_fpfd * n;
	    if(fref_calculated == m_fref){
	      status = true;
	      m_m_count = m;
	      m_n_count = n;
	      m_c_count = c;
	    }
	  }
	}
      }
    }
    
    if(c == m_c_max && !status){
      //      std::cout << "Can't synthesize requested clock: " << m_fout/1000 << std::endl;
      unsigned int remainder = m_fout % 100;
      m_fout = m_fout + 100 - remainder;
      //      std::cout << "." << std::flush;
      //      std::cout << "Rounding by 10KHz to requested value: " << m_fout/1000 << std::endl;
      c = m_c_min;
    }
  }
  
  std::cout << std::endl;
  if(status){
    m_m_bypass = (m_m_count == 1)?true:false;
    m_n_bypass = (m_n_count == 1)?true:false;
    m_c_bypass = (m_c_count == 1)?true:false;
    
    m_m_odd = (m_m_count & 0x1)?true:false;
    m_n_odd = (m_n_count & 0x1)?true:false;
    m_c_odd = (m_c_count & 0x1)?true:false;

    //divide counts by 2 for their high low register values
    m_m_high = m_m_low = m_m_count >> 1;
    m_c_high = m_c_low = m_c_count >> 1;
    m_n_high = m_n_low = m_n_count >> 1;
    //add 1 to the high registers if the count value is odd
    m_m_high = (m_m_odd)?m_m_high + 1: m_m_high;
    m_n_high = (m_n_odd)?m_n_high + 1: m_n_high;
    m_c_high = (m_c_odd)?m_c_high + 1: m_c_high;
	
  }
  return status;
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

bool alt_28nm_pll_reconfig::request_new_settings(void)
{
  bool status(true);
  std::string freq;
  std::string lock_status;
  std::string calculated_parameters_string(std::to_string(m_m_high) + " " + std::to_string(m_m_low) + " " + std::to_string(m_m_bypass) + " " + std::to_string(m_m_odd)
					   + " " + std::to_string(m_n_high) + " " + std::to_string(m_n_low) + " " + std::to_string(m_n_bypass) + " " + std::to_string(m_n_odd)
					   + " " + std::to_string(m_c_high) + " " + std::to_string(m_c_low) + " " + std::to_string(m_c_bypass) + " " + std::to_string(m_c_odd)
					   + " " + std::to_string(m_bandwidth) + " " + std::to_string(m_vco_div) + " " + std::to_string(m_c_pump));

  if(sys_file_exist(m_frequency_sys_file) &&
     sys_file_exist(m_parameters_sys_file) &&
     sys_file_exist(m_lock_sys_file)){
    m_frequency_sys_stream.open(m_frequency_sys_file.c_str());
    if(!m_frequency_sys_stream.is_open())
      std::cout << "sys file not open" << std::endl; //add some error logic
   
    m_parameters_sys_stream.open(m_parameters_sys_file.c_str());
    if(!m_parameters_sys_stream.is_open())
      std::cout << "sys file not open" << std::endl; //add some error logic

    m_lock_sys_stream.open(m_lock_sys_file.c_str());
    if(!m_lock_sys_stream.is_open())
      std::cout << "sys file not open" << std::endl; //add some error logic
    
    m_frequency_sys_stream >> freq;
    std::cout << "Current PLL Output Frequency: " << freq << std::endl;
    m_parameters_sys_stream << calculated_parameters_string << std::endl << std::flush;

    sleep(2);//allow the frequency counter some time
    m_frequency_sys_stream.clear();
    m_frequency_sys_stream.seekg(0, std::ios::beg);
    m_frequency_sys_stream >> freq;
    
    m_lock_sys_stream >> lock_status;
    
    status =(abs((atoi(freq.c_str())) - m_fout/1000) <= 2 && lock_status == "Locked")?true:false;

    (status)?std::cout << "Pass: ":std::cout << "Fail: ";
    
    std::cout << "New PLL Output Frequency: " << freq << std::endl;
    std::cout << "Applied these PLL Parameters: " << calculated_parameters_string << std::endl;
    std::cout << "PLL Lock Status: " << lock_status << std::endl;


  }else{
    std::cout << "The alt_pll_reconfig kernel module doesn't appear to be installed." << std::endl;
    std::cout << "Install the driver and run the following command to modify the pll output frequency: " << std::endl
	      << "echo \"" << calculated_parameters_string  << "\" > "
    	      << m_parameters_sys_file << std::endl << std::endl;
    std::cout << "Check the results by running the following command:" << std::endl;
    std::cout << "cat " << m_frequency_sys_file << std::endl;
    status = true;
  }
  
    
  return  status;
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
  m_c_max = 512UL;
  m_n_min = 0x1;
  m_n_max = 512UL;
  m_m_min = 0x1;
  m_m_max = 512UL;
  m_fpfd_min = 5000000UL;
  m_fpfd_max = 325000000UL;
  m_fref_min = 25000000UL; //comeback and check this value
  switch(m_speed_grade)
  {
  case 6:
     m_fout_min = 1000UL;
     m_fvco_max = 1600000000UL;
     m_fout_max = 1600000000UL;
     m_fref_max = 800000000UL;
    break;
  case 7:
     m_fout_min = 1000UL;
     m_fvco_max = 1600000000UL;
     m_fout_max = 1340000000UL;
     m_fref_max = 700000000UL;
    break;
  case 8:
     m_fout_min = 1000UL;
     m_fout_max = 1066000000UL;
     m_fvco_max = 1300000000UL;
     m_fref_max = 650000000UL;

    break;
  default:
    assert(false);
  }
}
