#include <stdio.h>
#include <stdlib.h>

int main() {
	int stopReading;
	char fileName[255];
	int lineCount = 1;
	int totalLinesWritten = 0;
	
	printf("'DarkEditor v0.02'\n"); //descroption
	printf("this is a testing project.\nThis text editor is written by tg-@Dark30190 and Google Gemini,\nwhile He's learning C.\n");
	printf("write at telegram,if you see the problems in this programm\nor have ideas to add new features.\n");
	
	printf("Enter your file name: "); //accepts a name of file from user
	scanf("%99s", fileName);

	while ((stopReading = getchar()) != '\n' && stopReading != EOF); //removes the line break from the name

	FILE *input = fopen(fileName, "a"); //set user's filename to tife.txt
	if (input == NULL) {				//checks file being if file isn't created
		printf("FIle opening error"); 
		return 1;
	}

	printf("click Ctrl+D on Linux/macOS or Ctrl+Z on Windows to end tiping.\n");

	printf("%d. ", lineCount); //print a number of first line

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
		printf("\n%d lines was written to file.\n", totalLinesWritten);
	}
	
	return 0;
}
