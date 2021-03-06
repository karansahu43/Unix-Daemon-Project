/*
 * FileName	mainhw5.cc
 * Date		4/15/2020
 * Author	Karan Sahu
 * Email	kxs190007@utdallas.edu
 * Course	CS 3377.501 Sping 2020
 * Version	1.0
 * Copyright 2020, all rights reserved
 *
 * Description
 * HW number 5 for cs 3377  * 	
 * 	*/

#include <iostream>
#include "function.h"
#include "rude/config.h"
#include <unistd.h>
#include <fstream>
#include <bits/stdc++.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <sys/inotify.h>
#include <ctime>


#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

map <int, string> tclapmap; 

using namespace std;
using namespace rude;

bool daemonloop = true;
int logcheck = 0;
string temp;

void my_handler(int);

int main(int argc, char* argv[])
{

		
	// Parses command line and returns map with all relavent information in the form of a map 
	tclapmap = tclapfunction(argc, argv);

	Config config;
	
	if(config.load("cs3377dirmond.conf")){
	config.setSection("Parameters");
	cout << config.getStringValue("Verbose") << " should print true" << endl;
	tclapmap[VERBOSENUM]= config.getStringValue("Verbose") ;
	tclapmap[LOGFILENUM]= config.getStringValue("LogFile") ;
	tclapmap[PASSWORDNUM]= config.getStringValue("Password") ;
	tclapmap[NUMVERSIONSNUM]= config.getStringValue("NumVersions") ;
	tclapmap[WATCHDIRNUM]= config.getStringValue("WatchDir") ;
	}
	

	//CallsmakeUpper(tclapmap[INFILEARGNUM], tclapmap[OUTFILEARGNUM]);
       // if -d option was passed by user
	if(tclapmap[SWITCHDAEMONNUM]== "true")
	{
		ofstream childpidfile;

		
		pid_t forkvalue;

		
		forkvalue = fork();
		if(forkvalue == -1) //Error No child created
		{
			cout <<"there was an error in the fork no child was created.";
			return 1;
	
	}
		else if(forkvalue == 0) // I am the child
		{
			childpidfile.open("cs3377dirmond.pid");
			cout << "this is the child. My pid is: " << getpid() << endl;
			cout << "Child going into daemon function\n";
			childpidfile << getpid() << endl;
			childpidfile.close();

			
		}
		else //I am the parent 
		{
			cout << "This is the parent.  My pid is: " << getpid() << endl;
			cout << "Parent Exiting\n";
			return 0;
		}

	}
	ofstream daemonfile;
	daemonfile.open(config.getStringValue("LogFile"));



//////////////////////////////////////////Inotify//////////////////////////////////

	
	char buffer[EVENT_BUF_LEN];
	int fd, wd, length, i=0;
	fd = inotify_init();


////////////////////////////////////////////////////////////////////////////////////////

	
	system("mkdir ~/temp/WatchDir/.version");

	int logcounter = 1;

	cout << endl << "kill -2 <pid>: This will remove the pid file, close the log file and end the daemon" << endl;
	cout << "kill -1 <pid>: Will Reread conf file" << endl;

	signal(SIGTERM, my_handler);
	signal(SIGINT, my_handler);
	signal(SIGHUP, my_handler);
	
	while(daemonloop){	
	if(logcheck == 0 ||tclapmap[VERBOSENUM]== "true" )
	{
		daemonfile << endl << endl << "If Verbose is true or conf file was edited then conf file will be printed!" << endl << endl;
		daemonfile << "Verbose is: " << tclapmap[VERBOSENUM] << endl;
		daemonfile << "Log file name is: " << tclapmap[LOGFILENUM] << endl;
		daemonfile << "Version is: " << tclapmap[NUMVERSIONSNUM] << endl;
		daemonfile << "Watch directory path is: " << tclapmap[WATCHDIRNUM] << endl;
		daemonfile << "Log count is: " << logcounter << endl << endl;
		logcounter = logcounter +1;		
	

			logcheck =1;
	}
	wd = inotify_add_watch( fd,  config.getStringValue("WatchDir"), IN_MODIFY);
	
	if(daemonloop){length = read( fd, buffer, EVENT_BUF_LEN );}
	if (length <0){ cout << endl << "an error has occured with read for inotify" << endl;}


	struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ]; 
	if ( event->len ) {
      		if ( event->mask & IN_MODIFY ) {

	
          			daemonfile << endl << endl <<  "File modified: " << event->name << endl;
	

				time_t tt;
				struct tm * ti;
				time (&tt);
				ti = localtime(&tt);
				string t = asctime(ti);

	
				int j= 0;
				while(j <= 22){
				if(t[j]== ' '){ t[j] = '-';}
				j++;
				}
							
				string a = "";
				char *tempc = event->name;
				a = tempc;
	
				temp = "cp ~/temp/WatchDir/" + a + " ~/temp/WatchDir/.version/"+ a + t;
				const char *command =  temp.c_str();
				system(command); 
				
       			 }


	}
	

	

 


	}
	cout << endl << "made it out of deamon loop" << endl;
	inotify_rm_watch(fd, wd);
	close( fd );
	daemonfile.close();


	return 0;
	
}









void my_handler(int s){

if(s==15){
	cout << s << endl;
	signal(SIGTERM, my_handler);
	}
if(s==2){
	cout << endl << "Removing pid file, closing log file and ending daemon" << endl;
	cout << endl << endl << "There may be a block from the inotify read so to end the block and end the daemon another file change must be made in the Watch Directory" << endl << endl;
	
	if(remove("cs3377dirmond.pid")!= 0)
		cout << endl << "An error occured" << endl;
	daemonloop = false;


	}
if(s==1){
	Config configd;

	if(configd.load("cs3377dirmond.conf")){
	configd.setSection("Parameters");

	tclapmap[VERBOSENUM]= configd.getStringValue("Verbose") ;
	tclapmap[LOGFILENUM]= configd.getStringValue("LogFile") ;
	tclapmap[PASSWORDNUM]= configd.getStringValue("Password") ;
	tclapmap[NUMVERSIONSNUM]= configd.getStringValue("NumVersions") ;
	tclapmap[WATCHDIRNUM]= configd.getStringValue("WatchDir") ;
	}
	logcheck = 0;
	}


}


	


