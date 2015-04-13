/*

##############################################################################
#                                                                            #
#              FLUKE: Fields Layered Under Kohn-sham Electrons               #
#                             By: Eric G. Kratz                              #
#                                                                            #
##############################################################################

 FLUKE wrapper functions for NWChem.

 Reference for NWChem:
 

*/

//MM utility functions


//MM wrapper functions
double NWChemForces(vector<QMMMAtom>& Struct, vector<Coord>& Forces,
       QMMMSettings& QMMMOpts, int Bead)
{
  //Runs NWChem force calculations
  fstream ofile,ifile;
  string dummy; //Generic string
  stringstream call;
  call.copyfmt(cout);
  double E = 0.0;
  int sys; //Dummy return for system calls
  
  //Change units
  E *= Har2eV;
  return E;
};

void NWChemCharges(vector<QMMMAtom>& Struct, QMMMSettings& QMMMOpts,
       int Bead)
{
  //Calculates atomic charges with NWChem
  fstream ofile,ifile;
  string dummy; //Generic string
  stringstream call;
  call.copyfmt(cout);
  double E = 0.0;
  int sys; //Dummy return for system calls
  
  return;
};

double NWChemEnergy(vector<QMMMAtom>& Struct, QMMMSettings& QMMMOpts,
       int Bead)
{
  //Runs NWChem energy calculations
  fstream ofile,ifile;
  string dummy; //Generic string
  stringstream call;
  call.copyfmt(cout);
  double E = 0.0;
  int sys; //Dummy return for system calls
  //Create NWChem input
  call.str("");
  call << "QMMM_" << Bead << ".nw";
  ofile.open(call.str().c_str(),ios_base::out);
  ofile << "start QMMM_" << Bead << '\n';
  ofile << "charge " << QMMMOpts.Charge << '\n';
  ofile << "geometry" << '\n';
  for (int i=0;i<Natoms;i++)
  {
    if (Struct[i].QMregion or Struct[i].PAregion)
    {
      ofile << " " << Struct[i].QMTyp;
      ofile << " " << Struct[i].P[Bead].x;
      ofile << " " << Struct[i].P[Bead].y;
      ofile << " " << Struct[i].P[Bead].z;
      ofile << '\n';
    }
  }
  ofile << "end" << '\n';
  if (CheckFile("BASIS"))
  {
    //Add basis set and ecp info
    ifile.open("BASIS",ios_base::in);
    if (ifile.good());
    {
      while (!ifile.eof())
      {
        //Copy BASIS line by line, if BASIS exists
        getline(ifile,dummy);
        ofile << dummy << '\n';
      }
    }
    ifile.close();
  }
  else
  {
    ofile << "basis" << '\n';
    ofile << " * library " << QMMMOpts.Basis;
    ofile << '\n';
    ofile << "end" << '\n';
  }
  if (CHRG == 1)
  {
    ofile << "bq mmchrg" << '\n';
    for (int i=0;i<Natoms;i++)
    {
      if (Struct[i].MMregion)
      {
        ofile << fixed; //Forces numbers to be floats
        ofile << " " << setprecision(12) << Struct[i].P[Bead].x;
        ofile << " " << setprecision(12) << Struct[i].P[Bead].y;
        ofile << " " << setprecision(12) << Struct[i].P[Bead].z;
        ofile << " " << setprecision(12) << Struct[i].MP[Bead].q;
        ofile.copyfmt(cout);
        ofile << '\n';
      }
    }
    ofile << "end" << '\n';
    ofile << "set mmchrg" << '\n';
  }
  if (AMOEBA == 1)
  {
    ofile << "bq mmchrg" << '\n';
    for (int i=0;i<Natoms;i++)
    {
      if (Struct[i].MMregion)
      {
        ofile << fixed; //Forces numbers to be floats
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].x1;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].y1;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].z1;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].q1;
        ofile << '\n';
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].x2;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].y2;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].z2;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].q2;
        ofile << '\n';
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].x3;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].y3;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].z3;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].q3;
        ofile << '\n';
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].x4;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].y4;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].z4;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].q4;
        ofile << '\n';
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].x5;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].y5;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].z5;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].q5;
        ofile << '\n';
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].x6;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].y6;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].z6;
        ofile << " " << setprecision(12) << Struct[i].PC[Bead].q6;
        ofile.copyfmt(cout);
        ofile << '\n';
      }
    }
    ofile << "end" << '\n';
    ofile << "set mmchrg" << '\n';
  }
  ofile << "dft" << '\n';
  ofile << " mult " << QMMMOpts.Spin << '\n';
  ofile << " direct" << '\n';
  ofile << " xc " << QMMMOpts.Func << '\n';
  ofile << "end" << '\n';
  ofile << "task dft energy" << '\n';
  ofile.flush();
  ofile.close();
  //Calculate energy
  call.str("");
  
  //Parse output
  call.str("");
  
  ifile.open(call.str().c_str(),ios_base::in);
  //Clean up files
  call.str("");
  
  sys = system(call.str().c_str());
  //Change units and return
  E *= Har2eV;
  return E;
};

double NWChemOpt(vector<QMMMAtom>& Struct, QMMMSettings& QMMMOpts, int Bead)
{
  //Runs NWChem optimizations
  fstream ofile,ifile;
  string dummy; //Generic string
  stringstream call;
  call.copyfmt(cout);
  double E = 0.0;
  int sys; //Dummy return for system calls
  
  //Change units
  E *= Har2eV;
  return E;
};
