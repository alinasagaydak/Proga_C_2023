#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#define MAX_BUFFER 256
#define MAX_STRLEN 128

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
		while(text[i] == ' ' && text[i + 1] == ' ')
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

void test_add_space() {
	char input_string[MAX_STRLEN] = "helloworld!";
	char expected_string[MAX_STRLEN] = "hello world!";
	addSpace((char*)&input_string, 5, strlen((char*)&input_string));
	for (int i = 0; i < strlen((char*)&input_string); i++) {
		if (input_string[i] != expected_string[i]) {
			printf("error\n");
			printf("space wasn't be added");

			exit(1);
		}
	}
}

void test_delete_symbol() {
	char input_string[MAX_STRLEN] = "heello world";
	char expected_string[MAX_STRLEN] = "hello world";
	deleteSymbol((char*)&input_string, 1, strlen((char*)&input_string));
	for (int i = 0; i < strlen((char*)&input_string); i++)
	{
		if (input_string[i] != expected_string[i])
		{
			printf("erroe\n");
			printf("symbol wasn't be deleted\n");

			exit(1);
		}
	}
}

void test_correct_letters() {
	char input_string[MAX_STRLEN] = "hEllo! wORld!";
	char expected_string[MAX_STRLEN] = "Hello! World!";
	correctLetters((char*)&input_string, strlen((char*)&input_string));
	for (int i = 0; i < strlen((char*)&input_string); i++)
	{
		if (input_string[i] != expected_string[i])
		{
			printf("error\n");
			printf("letters weren't be deleted\n");

			exit(1);
		}
	}
}

int main()
{
	test_add_space();
	test_delete_symbol();
	test_correct_letters();
	
	char text[MAX_BUFFER] = "     hEllo     world    !i love PrOgRaMmiNG .";
	int textLen = strlen(text);
	if (textLen > MAX_STRLEN)
	{
		printf("The string is too long");
		exit(0);
	}

	printf("%s\n", text);
	
	correctSpaces(text, textLen);
	printf("%s\n", text);

	correctLetters(text, textLen);
	printf("%s\n", text);

}