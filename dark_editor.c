//Dark Editor v0.03
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void open_fullscreen() {
	printf("\e[?1049h\e[H\e[2J");
	fflush(stdout);
}

void close_fullscreen() {
	printf("\e[?1049l");
	fflush(stdout);
}

int main(int argc, char *argv[]) {
	int stopReading;
	char *fileName = argv[1];
	int lineCount = 1;
	char buffer[256];
	int totalLinesWritten = 0;

	open_fullscreen();

	if (argc < 2) { //checking currect file name
		fprintf(stderr, "Error: filename is not currect!\n");
		fprintf(stderr, "Current name can be %s <file_name.txt>\n", argv[0]);
		return 0;
	}
	
	FILE *input = fopen(fileName, "r"); //set user's filename to tife.txt

	if (input == NULL) {				//checks file being if file isn't created
		fprintf(stderr, "FIle opening error"); 
		return 1;
	}
	
	printf("=|Dark Editor v0.03|=====| filename: %s|=====|commands: Ctrl+D - save file and exit|==========\n", fileName);

	//printf("%d. ", lineCount); //print a number of first line

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
		//printf("\rTime ramaining: %d s...", i);
		fflush(stdout);
		sleep(1);
	}

	close_fullscreen();
	
	return 0;
}
