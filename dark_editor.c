#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//cursor struction(will be used in the future)
typedef struct {
	int pos_x;
	int pos_y;
} Cursor;

//function prototypes
void open_fullscreen(); //opens program in alternate screen buffer 
void close_fullscreen();//closes alternate screen buffer
void cmd_version(char version[], char data[]); //'--help' command func
void cmd_help();							   //'--version' command func

int main(int argc, char *argv[]) {
	char progVersion[] = "v0.03_3";
	char progReleaseDate[] = "16.08.2026"; 
	int stopReading;
	char *fileName = NULL;
	int lineCount = 1;
	char buffer[256];
	int totalLinesWritten = 0;

	if (argc < 2) { 														//checking a currecting of file name and commands
		fprintf(stderr, "Error: filename or command is not currect!\n");
		fprintf(stderr, "Current name can be %s <file_name.txt>\n", argv[0]);
		printf("Enter '--help' for more information.\n");
		return 1;
	}

	for (int j = 1; j < argc; j++) { 												//flags checking
	        if (strcmp(argv[j], "-h") == 0 || strcmp(argv[j], "--help") == 0) {
	            cmd_help();
	            return 0;
	        } else if (strcmp(argv[j], "-v") == 0 || strcmp(argv[j], "--version") == 0) {
	        	cmd_version(progVersion, progReleaseDate);
	        	return 0;
	        }
        }

	fileName = argv[1]; //takes and assigns a name to a file if argumment is a filename
	
	FILE *file = fopen(fileName, "r+"); //opens a file if it's
	if (file == NULL) {				//checks file being and creates that if a file's not found
		file = fopen(fileName, "w+");
		if (file == NULL) {
			fprintf(stderr, "Error: Cannot ope or create file");
			return 1;
		}
	}
	
	open_fullscreen(); //opens alternate screen buffer if main func argument is a filename
	//print a program's name, version and keybinding in fullscreen
	printf("=|Dark Editor %s|=====| filename: %s|=====|commands: Ctrl+D - save file and exit|==========\n", progVersion, fileName); 

	while (fgets(buffer, sizeof(buffer), file) != NULL) { //prints a file content with line numbers adding 
		printf("%d. ", lineCount);
		printf("%s", buffer);
		if (buffer[strlen(buffer) - 1] == '\n') {
			lineCount++;
		}
	}

	printf("%d. ", lineCount);
	fflush(stdout);

	fseek(file, 0, SEEK_END); 
	
	while ((stopReading = getchar()) != EOF) { //writes user's tiping to file
		fputc(stopReading, file);

		if (stopReading == '\n') { //adds a line number during tiping
			lineCount++;
			totalLinesWritten++;
			printf("%d. ", lineCount);
			fflush(stdout);
		}
	}

	fclose(file);
	
	if (totalLinesWritten == 1) {					   //show a number of written lines in file
		printf("\n%d line was written to file.\n", totalLinesWritten);
	} else {
		printf("\n%d lines were written to file.\n", totalLinesWritten);
	}

	for (int i = 1; i > 0; i--) { //timer to close alternate screen buffer
		fflush(stdout);
		sleep(1);
	}

	close_fullscreen();
	
	return 0;
}

void open_fullscreen() { //uses alternate screen buffer
	printf("\e[?1049h\e[H\e[2J");
	fflush(stdout);
}

void close_fullscreen() { //exit to command shell
	printf("\e[?1049l");
	fflush(stdout);
}

void cmd_version(char version[], char data[]) {		//using '--version or -v' argument shows porgram version 
	printf("Dark Editor %s from %s.\n", version, data);
}

void cmd_help() {									//using '--help or =v' argument shows program help manual
	printf("command list:\n");
	printf("-h, --help: show this manual;\n");
	printf("-v, --version: show version.\n");
}
