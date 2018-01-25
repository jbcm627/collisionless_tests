
#include "sheet.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
 
void runSim(SheetSimulation::Specs specs, std::string out_base_dir)
{
  std::string mkdir_cmd ("mkdir -p " + out_base_dir + "; rm -f " + out_base_dir + "/*.gz");
  const int ret = system(mkdir_cmd.c_str());
  if(-1==ret) std::cout << "Unable to make dir: " + out_base_dir << std::endl;

  std::cout << std::setprecision(17);
  std::cout << "Initializing new sheet class with dir " << out_base_dir << "..." << std::flush;
  SheetSimulation sheet (specs, SheetSimulation::Verbosity::none);
  sheet.initializeFields();
  sheet.writeInfo(out_base_dir);
  std::cout << " done." << std::endl;

  int t_steps = 800;
  for(int t=0; t<=t_steps; ++t)
  {
    std::cout << "\rRunning step " << t << "..." << std::flush;
    sheet.writeStrips(out_base_dir + "/strips");
    if(t % (t_steps/4) == 0)
    {
      std::string t_str = std::to_string(t);
      std::cout << std::endl << "Writing step " << t_str << std::endl;
      sheet.writeDensity(out_base_dir + "/step_" + t_str + "_density.dat");
      sheet.writePositions(out_base_dir + "/step_" + t_str + "_positions.dat");
      sheet.writedphis(out_base_dir + "/step_" + t_str + "_dphis.dat");
    }
    sheet.RKStep();
  }
  std::cout << std::endl << "Done!" << std::endl;

  sheet.printTimingInformation();
}

void runResolutionTests(SheetSimulation::Specs specs)
{
  specs.initialization_type = SheetSimulation::initializationType::overdensity1d;
  SheetSimulation::Specs specs_alt;

  // TSC deposition scheme
  specs_alt = specs;
  specs_alt.ns1 = 64;
  specs_alt.nx = 64;
  specs_alt.carriers_per_dx = 0;
  runSim(specs_alt, "sim_ns064_nx064_cpdx0");

  // double resolution
  specs_alt = specs;
  specs_alt.ns1 = 128;
  specs_alt.nx = 128;
  specs_alt.carriers_per_dx = 0;
  runSim(specs_alt, "sim_ns128_nx128_cpdx0");

  // more resolution
  specs_alt = specs;
  specs_alt.ns1 = 256;
  specs_alt.nx = 256;
  specs_alt.carriers_per_dx = 0;
  runSim(specs_alt, "sim_ns256_nx256_cpdx0");


  // more resolution n-body
  specs_alt = specs;
  specs_alt.ns1 = 4096;
  specs_alt.nx = 4096;
  specs_alt.carriers_per_dx = 0;
  runSim(specs_alt, "sim_ns4096_nx4096_cpdx0");


  // 4 carriers per dx
  specs_alt = specs;
  specs_alt.ns1 = 64;
  specs_alt.nx = 64;
  specs_alt.carriers_per_dx = 32;
  runSim(specs_alt, "sim_ns064_nx064_cpdx32");

  // 4 carriers per dx, higher res.
  specs_alt = specs;
  specs_alt.carriers_per_dx = 32;
  specs_alt.ns1 = 128;
  specs_alt.nx = 128;
  runSim(specs_alt, "sim_ns128_nx128_cpdx32");

  // more res
  specs_alt = specs;
  specs_alt.carriers_per_dx = 32;
  specs_alt.ns1 = 256;
  specs_alt.nx = 256;
  runSim(specs_alt, "sim_ns256_nx256_cpdx32");
}

void runUniformTests(SheetSimulation::Specs specs)
{
  specs.initialization_type = SheetSimulation::initializationType::uniform1dv;
  SheetSimulation::Specs specs_alt;

  specs_alt = specs;
  specs_alt.ns1 = 3;
  specs_alt.nx = 64;
  specs_alt.carriers_per_dx = 0;
  runSim(specs_alt, "sim_ns1_nx064_cpdx0");

  specs_alt = specs;
  specs_alt.ns1 = 3;
  specs_alt.nx = 64;
  specs_alt.carriers_per_dx = 2;
  runSim(specs_alt, "sim_ns1_nx064_cpdx2");

  specs_alt = specs;
  specs_alt.ns1 = 3;
  specs_alt.nx = 64;
  specs_alt.carriers_per_dx = 2;
  specs_alt.carrier_count_scheme = SheetSimulation::carrierCountScheme::per_ds;
  runSim(specs_alt, "sim_ns1_nx064_cpds2");


  specs_alt = specs;
  specs_alt.ns1 = 3;
  specs_alt.nx = 128;
  specs_alt.carriers_per_dx = 0;
  runSim(specs_alt, "sim_ns1_nx128_cpdx0");

  specs_alt = specs;
  specs_alt.ns1 = 3;
  specs_alt.nx = 128;
  specs_alt.carriers_per_dx = 4;
  runSim(specs_alt, "sim_ns1_nx128_cpdx4");

  specs_alt = specs;
  specs_alt.ns1 = 3;
  specs_alt.nx = 128;
  specs_alt.carriers_per_dx = 4;
  specs_alt.carrier_count_scheme = SheetSimulation::carrierCountScheme::per_ds;
  runSim(specs_alt, "sim_ns1_nx128_cpds4");


  specs_alt = specs;
  specs_alt.ns1 = 3;
  specs_alt.nx = 256;
  specs_alt.carriers_per_dx = 0;
  runSim(specs_alt, "sim_ns1_nx256_cpdx0");

  specs_alt = specs;
  specs_alt.ns1 = 3;
  specs_alt.nx = 256;
  specs_alt.carriers_per_dx = 8;
  runSim(specs_alt, "sim_ns1_nx256_cpdx8");

  specs_alt = specs;
  specs_alt.ns1 = 3;
  specs_alt.nx = 256;
  specs_alt.carriers_per_dx = 8;
  specs_alt.carrier_count_scheme = SheetSimulation::carrierCountScheme::per_ds;
  runSim(specs_alt, "sim_ns1_nx256_cpds8");

}


void runUniformTests2(SheetSimulation::Specs specs)
{
  specs.initialization_type = SheetSimulation::initializationType::uniform1dv;
  SheetSimulation::Specs specs_alt;

  specs_alt = specs;
  specs_alt.ns1 = 63;
  specs_alt.nx = 64;
  specs_alt.carriers_per_dx = 0;
  runSim(specs_alt, "sim_ns063_nx064_cpdx0");

  specs_alt = specs;
  specs_alt.ns1 = 63;
  specs_alt.nx = 64;
  specs_alt.carriers_per_dx = 2;
  runSim(specs_alt, "sim_ns063_nx064_cpdx2");

  specs_alt = specs;
  specs_alt.ns1 = 63;
  specs_alt.nx = 64;
  specs_alt.carriers_per_dx = 2;
  specs_alt.carrier_count_scheme = SheetSimulation::carrierCountScheme::per_ds;
  runSim(specs_alt, "sim_ns063_nx064_cpds2");


  specs_alt = specs;
  specs_alt.ns1 = 127;
  specs_alt.nx = 128;
  specs_alt.carriers_per_dx = 0;
  runSim(specs_alt, "sim_ns127_nx128_cpdx0");

  specs_alt = specs;
  specs_alt.ns1 = 127;
  specs_alt.nx = 128;
  specs_alt.carriers_per_dx = 4;
  runSim(specs_alt, "sim_ns127_nx128_cpdx4");

  specs_alt = specs;
  specs_alt.ns1 = 127;
  specs_alt.nx = 128;
  specs_alt.carriers_per_dx = 4;
  specs_alt.carrier_count_scheme = SheetSimulation::carrierCountScheme::per_ds;
  runSim(specs_alt, "sim_ns127_nx128_cpds4");


  specs_alt = specs;
  specs_alt.ns1 = 255;
  specs_alt.nx = 256;
  specs_alt.carriers_per_dx = 0;
  runSim(specs_alt, "sim_ns255_nx256_cpdx0");

  specs_alt = specs;
  specs_alt.ns1 = 255;
  specs_alt.nx = 256;
  specs_alt.carriers_per_dx = 8;
  runSim(specs_alt, "sim_ns255_nx256_cpdx8");

  specs_alt = specs;
  specs_alt.ns1 = 255;
  specs_alt.nx = 256;
  specs_alt.carriers_per_dx = 8;
  specs_alt.carrier_count_scheme = SheetSimulation::carrierCountScheme::per_ds;
  runSim(specs_alt, "sim_ns255_nx256_cpds8");

}


int main(int argc, char **argv)
{
  std::cout << "Beginning simulations." << std::endl;

  SheetSimulation::Specs specs = {0};
  specs.nx = 1; specs.ny = 1; specs.nz = 1;
  specs.ns1 = 1; specs.ns2 = 1; specs.ns3 = 1;
  specs.lx = 1.0; specs.ly = 1.0; specs.lz = 1.0;
  specs.carriers_per_dx = 4;
  specs.carriers_per_dy = 0;
  specs.carriers_per_dz = 0;
  specs.dt = 0.02;
  specs.deposit = SheetSimulation::depositScheme::PCS;
  specs.carrier_count_scheme = SheetSimulation::carrierCountScheme::per_dx;

  // runResolutionTests(specs);  
  // runUniformTests(specs);
  runUniformTests2(specs);

  return 0;
}
