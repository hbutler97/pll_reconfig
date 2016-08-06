#include <string>
#include <iostream>
#include <algorithm>
#include <memory>
#include "tclap/CmdLine.h"
#include "alt_pll_reconfig.h"
#include "alt_pll_reconfig_interface.h"
#include "alt_pll_reconfig_list.h"



int main(int argc, char** argv)
{

  try {
    std::auto_ptr<TCLAP::CmdLine> cmd(new TCLAP::CmdLine(ALT_PLL_RECONFIG_USAGE,
							 ALT_PLL_RECONFIG_DELIMITER,
							 ALT_PLL_RECONFIG_VERSION));
    TCLAP::ValueArg<unsigned int> output_frequency("o",
						  "output_frequency",
						  "Desired Pll Output frequency in KHz",
						  true,
						  100000,
						  "Integer",
						  *cmd,
						  NULL);
    TCLAP::ValueArg<unsigned int> input_frequency("i",
						  "input_frequency",
						  "Pll reference input frequency in KHz",
						  true,
						  50000,
						  "Integer",
						  *cmd,
						  NULL);

     TCLAP::ValueArg<unsigned int> speed_grade("s",
					       "speed_grade",
					       "Device Speed Grade",
					       true,
					       6,
					       "Integer",
					       *cmd,
					       NULL);

     TCLAP::ValueArg<std::string> family("f",
					 "family",
					 "Device Family",
					 true,
					 "cyclonev",
					 "String",
					 *cmd,
					 NULL);

    cmd->parse( argc, argv );
    bool found = false;
    alt_pll_reconfig_interface* reconfig_interface = NULL;
    std::auto_ptr<alt_pll_reconfig_list> reconfig_list(new alt_pll_reconfig_list());

    for(unsigned int i = 0; i < reconfig_list->get_reconfig_list()->size() && !found; i++){
      if(reconfig_list->get_reconfig_list()->at(i)->is_supported_family(family.getValue()))
	{
	  reconfig_interface = reconfig_list->get_reconfig_list()->at(i);
	  found = true;
	}
    }
    if(!found) //add a supported family print statement
      throw TCLAP::ArgException("Invalided Family", family.getName());
    reconfig_interface->set_family(family.getValue());
    
    if(!reconfig_interface->check_speedgrade(speed_grade.getValue())) //add supported speed grades
      throw TCLAP::ArgException("Invalided Speed Grade", speed_grade.getName());
    reconfig_interface->set_speedgrade(speed_grade.getValue());

    if(!reconfig_interface->check_fout(output_frequency.getValue()*1000)) //add supported fouts
      throw TCLAP::ArgException("Invalided fout", output_frequency.getName());
    reconfig_interface->set_fout(output_frequency.getValue() * 1000);

    if(!reconfig_interface->check_fref(input_frequency.getValue()*1000)) //add supported fins
      throw TCLAP::ArgException("Invalided fin", input_frequency.getName());
    reconfig_interface->set_fref(input_frequency.getValue() * 1000);

    if(!reconfig_interface->calculate_pll_parameters()) //add a proper exception
      throw TCLAP::ArgException("***Howard add a proper exception", input_frequency.getName());
    reconfig_interface->request_new_settings();
    //add unhandled exception
  } catch (TCLAP::ArgException &e)  // catch any exceptions
    { std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; exit(EXIT_FAILURE); }
  exit(EXIT_SUCCESS);
}

