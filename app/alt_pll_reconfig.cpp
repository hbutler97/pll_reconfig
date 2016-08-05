#include <string>
#include <iostream>
#include <algorithm>
#include <memory>
#include "tclap/CmdLine.h"



int main(int argc, char** argv)
{
  try {
    std::auto_ptr<TCLAP::CmdLine> cmd(new TCLAP::CmdLine("Command description message", ' ', "0.9",false));
    TCLAP::ValueArg<unsigned int> onput_frequency("o",
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

    cmd->parse( argc, argv );
    
  } catch (TCLAP::ArgException &e)  // catch any exceptions
    { std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; exit(EXIT_FAILURE); }
  exit(EXIT_SUCCESS);
}

