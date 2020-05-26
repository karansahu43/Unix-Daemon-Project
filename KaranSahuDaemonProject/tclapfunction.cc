/*
 * FileName	tclapfunction.cc
 * Date		4/15/2020
 * Author	Karan Sahu
 * Email	kxs190007@utdallas.edu
 * Course	CS 3377.501 Sping 2020
 * Version	1.0
 * Copyright 2020, all rights reserved
 *
 * Description
 *
 * 	Parses command line arguments and returns parsed command line in a map or if there is a problem displays help page 
 * 	
 * 	*/

#include <iostream>
#include "tclap/CmdLine.h"
#include <map>
#include "function.h"
#include <stdlib.h>


using namespace std;
map<int, string> tclapfunction(int argc, char** argv)
{
	
	map <int, string> tclapmap; //To get values from the map use enum tclapnumber values as keys tp get the stored value.
	try{

		TCLAP::CmdLine cmd("CS3377.501 Program 5", ' ', "1.0");
		

		TCLAP::SwitchArg daemonSwitch("d","daemon","Run in daemon mode",cmd,false);
		
				
		TCLAP::ValueArg<string>  filenameArg("o","configfile","the name of the configfile", false,"cs3377dirmond.conf","config filename");

		cmd.add(filenameArg);
				
	

		cmd.parse( argc, argv);
		if(daemonSwitch.getValue())
			tclapmap[SWITCHDAEMONNUM]= "true";
		else
			tclapmap[SWITCHDAEMONNUM]= "false";

		tclapmap[FILENAMEARGNUM]  = filenameArg.getValue();

	


	     } catch (TCLAP::ArgException &e) //Catch any exceptions

	     {
	     	cerr << "error: " << e.error() << " for arg" << e.argId() << endl; 
	     }
	
		return tclapmap;
}




