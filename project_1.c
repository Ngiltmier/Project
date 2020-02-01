//Noah Giltmier and Garrett Brenner
//project_1
//csci 340

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

struct Process {
	int pid;
	int ppid;
	char *exName;
	unsigned long vsize;
};

void printTabs(int level) {
	for (int i = 0; i < level; i++) {
		printf("\t");
	}
}

void findNeighbors(struct Process* listOfProcesses[], struct Process* node) {

}

void printTree(int level, struct Process* node) {
	//DFS
	//"visit" node
	printTabs(level);
	printf("(%d) %s, %lu kb\n", node->pid, node->exName, node->vsize);
}

int main(int argc, char ** argv) {

	struct dirent * de;	//Pointer for directory entry

	//**********READ #1: FIND THE SIZE**********

	//opendir() returns a pointer of DIR type
	DIR * dr = opendir("/proc");

	//opendir() returns null if it couldn't open	
	if (dr == NULL) {
		printf("Could not open current directory");
		return 0;
	}

	//keep track of the number of process folders to correctly size an array of Processes
	int max = 0;

	while ((de = readdir(dr)) != NULL) {
		//check to see if the current directory is an integer
		//all processes are integers
		if (atoi(de->d_name) != 0) {
			max++;
		}
	}


	//**********READ #2: APPEND TO LIST OF PROCESSES**********

	//opendir() returns a pointer of DIR type
	dr = opendir("/proc");

	//opendir() returns null if it couldn't open	
	if (dr == NULL) {
		printf("Could not open current directory");
		return 0;
	}

	//create an array of Process structs
	struct Process listOfProcesses[max];
	
	int i = 0;
	while ((de = readdir(dr)) != NULL) {
		//check to see if the current directory is an integer
		//all processes are integers
		if (atoi(de->d_name) != 0) {		
					
			//printf("Scanning <%s>...\n", de->d_name);

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
					//printf("pid: %d | exName: %s | ppid: %d | vsize: %lu\n", pid, exName, ppid, vsize);
					struct Process p = {.pid = pid, .exName = exName, .ppid = ppid, .vsize = vsize};
					listOfProcesses[i] = p;
					i++;
				} 	
			}
			
			fclose(fp);
		}
	}
	closedir(dr);
	
	//printf("list[0]: memoryLoc = %p , pid = %d", &listOfProcesses[0], listOfProcesses[0].pid);
	printTree(0, &listOfProcesses[0]);

	return 0;
}


