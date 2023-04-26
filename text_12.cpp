#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

char* user_realloc(char* text, int capacity, int textLen)
{
	char* new_text = (char*)malloc(capacity * sizeof(char));

	for (int i = 0; i < textLen; i++)
	{
		new_text[i] = text[i];
	}
	free(text);
	
	return new_text;
}

void get_text(FILE* stream, char terminator) {
	int textLen = 0;
	int capacity = 1;
	char* text = (char*)malloc(sizeof(char));

	char c;
	fscanf_s(stream, "%c", &c, 1);

	while (c != terminator)
	{
		text[textLen++] = c;
		if (textLen >= capacity)
		{
			capacity *= 2;
			text = user_realloc(text, capacity, textLen);
		}

		fscanf_s(stream, "%c", &c, 1);
	}

	text[textLen] = '\0';

	printf("%s%s", "You've wrote:", text);
	free(text);
}


int main()
{
	//get_text(stdin, '#');

	FILE* fp;
	fopen_s(&fp, "results.txt", "r");
	get_text(fp, '#');
	fclose(fp);
}