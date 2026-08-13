#include <stdio.h>
#include <stdlib.h>

int main() {
	int stopReading;
	char fileName[255];
	char *pFileName[255];
	// int i = 1;
	// char lines[5] = "line";
	
	printf("'DarkEditor v0.01'\n");
	printf("this is a testing project.\nThis text editor is written by tg-@Dark30190 and Google Gemini,\nwhile He's learning C.\n");
	printf("write at telegram,if you see the problems in this programm\nor have ideas to add new features.\n");
	
	printf("Enter your file name: "); //accepts a name of file from user
	scanf("%99s", *pFileName);
	free(pFileName);

	while ((stopReading = getchar()) != '\n' && stopReading != EOF); //removes the line break from the name

	FILE *input = fopen(fileName, "a"); //set user's filename to tife.txt
	if (input == NULL) {				//checks file being if file isn't created
		printf("FIle opening error"); 
		return 1;
	}

	printf("click Ctrl+D on Linux/macOS or Ctrl+Z on Windows to end tiping.\n");
	
	while ((stopReading = getchar()) != EOF) { //writes user's tiping to file
		// printf("%d. ", i);  				   //adds a line number during tiping(right now it doesn't work currently)
		fputc(stopReading, input);
		// i = i + 1;
	}

	// if (i == 0 || i == 1) {					   //show a number of written lines in file
	// 	printf("\n%d %s was written to file.\n", i, lines);
	// } else {
	// 	printf("\n%d %ss was written to file.\n", i, lines);
	// }
	// 
	fclose(input);	

	return 0;
}
