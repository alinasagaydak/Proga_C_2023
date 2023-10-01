#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

char* user_realloc(char* text, int bufferSize, int textLen)
{
	char* new_text = (char*)malloc(bufferSize * sizeof(char));
	memcpy(new_text, text, textLen);
	free(text);

	return new_text;
}

char* get_text(FILE* stream, char terminator) {
	int textLen = 0;
	int bufferSize = 1;
	char* text = (char*)malloc(sizeof(char));

	char c;
	fscanf_s(stream, "%c", &c, 1);

	while (c != terminator)
	{
		text[textLen++] = c;
		if (textLen >= bufferSize)
		{
			bufferSize *= 2;
			text = user_realloc(text, bufferSize, textLen);
		}

		fscanf_s(stream, "%c", &c, 1);
	}

	text = user_realloc(text, textLen + 1, textLen);
	text[textLen] = '\0';

	printf("%s%s", "You've wrote: \n", text);

	return text;
}

void deleteSymbol(char* text, int index, int textLen)
{
	for (int j = index; j < textLen + 1; j++)
	{
		text[j] = text[j + 1];
	}
}

void addSpace(char* text, int index, int textLen)
{
	for (int j = textLen; j > index; j--)
	{
		text[j] = text[j - 1];
	}
	text[index] = ' ';
}

void correctSpaces(char* text, int textLen)
{
	for (int i = 0; i < textLen; i++)
	{
		while (text[i] == ' ' && text[i + 1] == ' ')
		{
			deleteSymbol(text, i, textLen);
		}
	}

	if (text[0] == ' ')
	{
		deleteSymbol(text, 0, textLen);
	}

	for (int i = 1; i < textLen; i++)
	{
		if (text[i] == ',' || text[i] == '.' || text[i] == '!' || text[i] == '?')
		{
			if (text[i - 1] == ' ')
			{
				deleteSymbol(text, i - 1, textLen);
			}
		}
	}

	for (int i = 1; i < textLen; i++)
	{
		if (text[i] == ',' || text[i] == '.' || text[i] == '!' || text[i] == '?')
		{
			if (text[i + 1] != ' ')
			{
				addSpace(text, i + 1, textLen);
			}
		}
	}
}

void correctLetters(char* text, int textLen)
{
	if ('a' <= text[0] && text[0] <= 'z')
		text[0] -= 32;

	for (int i = 0; i < textLen - 1; i++)
	{
		if (text[i] == '.' || text[i] == '!' || text[i] == '?')
		{
			if ('a' <= text[i + 2] && text[i + 2] <= 'z')
				text[i + 2] -= 32;
		}
	}

	for (int i = 2; i < textLen; i++)
	{
		if ('A' <= text[i] && text[i] <= 'Z')
		{
			if ((text[i - 2] != '.') && (text[i - 2] != '!') && (text[i - 2] != '?'))
				text[i] += 32;
		}
	}

	if ('A' <= text[1] && text[1] <= 'Z')
		text[1] += 32;
}

int main()
{
	// вручную выбрать откуда считывать текст. в файле должен быть стоп-символ (#)

	//get_text(stdin, '#');
	
	FILE* fp;
	fopen_s(&fp, "text.txt", "r");
	char* text = get_text(fp, '#');
	fclose(fp);

	printf("\n");
	correctSpaces(text, strlen(text));
	printf("%s\n", text);

	correctLetters(text, strlen(text));
	printf("%s\n", text);
	
	free(text);
}
