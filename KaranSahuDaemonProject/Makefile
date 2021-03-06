#!/usr/bin/make -f
#
# Filename:		Makefile
# Date:			04/15/2020
# Author:		Karan Sahu
# Email:		kxs190007@utdallas.edu
# Version:		1.0
# Copyright:		2019, All Rights Reserved
#
# Description:
#
#	Builds for HW 5 mainhw5.cc, function.h and tclap.cc
#
# Flags for the C++ implicit rules
CC = g++
CCFLAGS =-Wall

CXXFLAGS = -I ~/include -I rude

LDFLAGS = -L ~/lib
LDLIBS = -l rudeconfig
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters
PROJECTNAME = KaranSahuHW5

EXECFILE = Karanproject5

OBJS = DaemonProject.o 
# Because we are insane, keep the intermediate files so we can look at
# them If we comment this out (or remove it), the intermediate scan.c
# file is automatically deleted.

 



all:  DaemonProject

clean:
	rm -f $(OBJS) $(EXECFILE) *~ \#* scanner scan.c


backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

test:
	echo $(shell basename 'pwd')

DaemonProject: DaemonProject.cc
	g++ -static -o DaemonProject tclapfunction.cc -I ~/include DaemonProject.cc -I ~/include -I rude -Wall -L ~/lib -l rudeconfig

#%o:%cc
#	$(CC) -M -MF $*P $<
#	$(CC) -c $(CXXFLAGS) $(CCFLAGS) $(LDFLAGS) $(LDLIBS) $< -o $@	

#$(EXECFILE):	$(OBJS)
#	$(CC) -o $@ $(OBJS)


-include $(OBJS:%.o=%.P)

