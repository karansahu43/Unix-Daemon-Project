/*
 *
 * FileName	function.h
 * Date		4/15/2020
 * Author	Karan Sahu
 * Email	kxs190007@utdallas.edu
 * Course	CS 3377.501 Sping 2020
 * Version	1.0
 * Copyright 2020, all rights reserved
 *
 * Description
 *
 * 	Header file used by mainhw5.cc , tclapfunction.cc 
 * 	
 */

#ifndef FUNCTION_H
#define FUNCTION_H
using  namespace std;
#include <string>
#include <map>


//enum for map keys
enum tclapnumbers{SWITCHDAEMONNUM, FILENAMEARGNUM, VERBOSENUM, LOGFILENUM, PASSWORDNUM, NUMVERSIONSNUM, WATCHDIRNUM};

//function prototypes
map<int, string>  tclapfunction(int , char**);
//void makeLower(string, string);
//void makeUpper(string, string);

#endif
