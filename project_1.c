//Noah Giltmier and Garrett Brenner
//project_1
//csci 340

#include <stdio.h>
#include <stdlib.h>
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
		if (atoi(de->d_name) != 0) {		
			printf("%s\n", de->d_name);
		}
	}

	closedir(dr);
	return 0;
}


