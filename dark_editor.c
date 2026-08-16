#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void open_fullscreen() {
	printf("\e[?1049h\e[H\e[2J");
	fflush(stdout);
}

void close_fullscreen() {
	printf("\e[?1049l");
	fflush(stdout);
}

void cmd_version(char version[], char data[]) {
	printf("Dark Editor %s from %s.\n", version, data);
}

void cmd_help() {
	printf("command list:\n");
	printf("-h, --help: show this manual;\n");
	printf("-v, --version: show version.\n");
}

int main(int argc, char *argv[]) {
	char progVersion[] = "v0.03_2";
	char progReleaseDate[] = "16.08.2026"; 
	int stopReading;
	char *fileName = NULL;
	int lineCount = 1;
	char buffer[256];
	int totalLinesWritten = 0;

	if (argc < 2) { //checking currect file name
		fprintf(stderr, "Error: filename or command is not currect!\n");
		fprintf(stderr, "Current name can be %s <file_name.txt>\n", argv[0]);
		printf("Enter '--help' for more information.\n");
		return 0;
	}

	for (int j = 1; j < argc; j++) {
	        if (strcmp(argv[j], "-h") == 0 || strcmp(argv[j], "--help") == 0) {
	            cmd_help();
	            return 0;
	        } else if (strcmp(argv[j], "-v") == 0 || strcmp(argv[j], "--version") == 0) {
	        	cmd_version(progVersion, progReleaseDate);
	        	return 0;
	        }
        }

	fileName = argv[1];
	
	FILE *input = fopen(fileName, "r"); //set user's filename to tife.txt

	if (input == NULL) {				//checks file being if file isn't created
		//fprintf(stderr, "FIle opening error");
		input = fopen(fileName, "a");
		fclose(input); 
	}
	
	open_fullscreen();
	
	printf("=|Dark Editor %s|=====| filename: %s|=====|commands: Ctrl+D - save file and exit|==========\n", progVersion, fileName);

	while (fgets(buffer, sizeof(buffer), input) != NULL) {
		printf("%d. ", lineCount);
		lineCount++;
		printf("%s", buffer);
	}

	printf("%d. ", lineCount);
	
	fclose(input);
	
	input = fopen(fileName, "a");
	
	while ((stopReading = getchar()) != EOF) { //writes user's tiping to file
		fputc(stopReading, input);

		if (stopReading == '\n') { //adds a line number during tiping(right now it doesn't work currently)
			lineCount++;
			totalLinesWritten++;
			printf("%d. ", lineCount);
		}
	}

	fclose(input);
	
	if (totalLinesWritten == 1) {					   //show a number of written lines in file
		printf("\n%d line was written to file.\n", totalLinesWritten);
	} else {
		printf("\n%d lines were written to file.\n", totalLinesWritten);
	}

	for (int i = 1; i > 0; i--) {
		fflush(stdout);
		sleep(1);
	}

	close_fullscreen();
	
	return 0;
}
