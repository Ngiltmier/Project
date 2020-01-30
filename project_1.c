//Noah Giltmier and Garrett Brenner
//project_1
//csci 340

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


int main(int argc, char ** argv) {

	struct dirent * de;	//Pointer for directory entry

	//opendir() returns a pointer of DIR type
	DIR * dr = opendir("/proc");

	//opendir() returns null if it couldn't open	
	if (dr == NULL) {
		printf("Could not open current directory");
		return 0;
	}

	while ((de = readdir(dr)) != NULL) {
		//check to see if the current directory is an integer
		//all processes are integers
		if (atoi(de->d_name) != 0) {		
			printf("Scanning <%s>...\n", de->d_name);

			//creates a string fileName = "/proc/currentProcID/stat"
			char fileName[50];
			strcpy(fileName, "/proc/");
			strcat(fileName, de->d_name);
			strcat(fileName, "/stat");

			//open the current file for reading			
			FILE *fp;
			fp = fopen(fileName, "r");
			
			//check to see if something went wrong
			//if it did, I really don't know what to do about that lol
			if (fp == NULL) {
				printf("\tThis file is NULL\n");
			} else {
				//scan all the content of the file
				//documentation can be found at: https://www.redhat.com/archives/axp-list/2001-January/msg00355.html

				//CURRENT OBJECTIVE: FIND THE SIZE OF THE PROCESS IN KB

				//ATTEMPT1:
				/*
				int pid,ppid,pgrp,session,tty_nr,tpgid;
				unsigned int flags;
				unsigned long minflt,cminflt,majflt,cmajflt;
				char cm[255],stat;
				if (fscanf(fp,"%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu",
					&pid,cm,&stat,&ppid,&pgrp,&session,&tty_nr,&tpgid,&flags,
					&minflt,&cminflt,&majflt,&cmajflt) == EOF) {
					perror("fscanf");}
					//,&(st->utime),&(st->stime)
				else {
					printf("pid: %d | command name: %s | ppid: %d | size: \n", pid,cm,ppid);			
				}
				*/

				//ATTEMPT2:
				int pid,ppid;
				char exName[255];
				unsigned int vsize;

				if (fscanf(fp, "%d %s %d %*lu %*d %*lu %*d %u",
						&pid, exName, &ppid, &vsize) == EOF) {
					perror("sscanf");
				} else {
					printf("pid: %d | command name: %s | ppid: %d | size: %u\n", pid, exName, ppid, vsize);
				}

				
			}

			fclose(fp);
		}
	}

	closedir(dr);
	return 0;
}


