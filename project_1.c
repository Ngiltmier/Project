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

				//declare variables to store the information we want from the proc/PID/stat file
				int pid;
				int ppid;
				char exName[255];
				unsigned long vsize;

				//scan the proc/PID/stat file ignoring data we don't want
				if (fscanf(fp, "%d %s %*s %d %*d %*d %*d %*d %*u %*u %*u %*u %*u %*u %*u %*d %*d %*d %*d %*d %*d %*u %lu", &pid, exName, &ppid, &vsize) == EOF) {
					perror("sscanf");
				} else {
					printf("pid: %d | exName: %s | ppid: %d | vsize: %lu\n", pid, exName, ppid, vsize);
				} 	
			}
			fclose(fp);
		}
	}

	closedir(dr);
	return 0;
}


