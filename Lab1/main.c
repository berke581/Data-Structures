#include <stdio.h>
#include <string.h>

#define  SIZE 15


int minu(int a, int b)
{ return (a < b)? a: b; }

int min(int a, int b, int c)
{ return minu(minu(a, b), c); }

int max(int a, int b)
{ return (a > b)? a: b; }

void reverseStr(char* in_str, char* out_str);

void fillArray(char arr[][15], char out_arr[][15]);
void printArray(char arr[][15]);
void searchArray(char arr[][15], char* key, char out_arr[][15]);

void checkL2R(char arr[][15], char* key, char out_arr[][15]);
void checkR2L(char arr[][15], char* key, char out_arr[][15]);
void checkU2D(char arr[][15], char* key, char out_arr[][15]);
void checkD2U(char arr[][15], char* key, char out_arr[][15]);

void checkLDiag(char arr[][15], char* key, char out_arr[][15]);
void checkLDiagR(char arr[][15], char* key, char out_arr[][15]);
void checkRDiag(char arr[][15], char* key, char out_arr[][15]);
void checkRDiagR(char arr[][15], char* key, char out_arr[][15]);

int main(void)
{
	char arr[15][15] = {0};
	char result_arr[15][15];

	fillArray(arr, result_arr);

	char searchKey[20];
	scanf("%19s", searchKey);

	searchArray(arr, searchKey, result_arr);

	printArray(result_arr);

	return 0;
}

void fillArray(char arr[][15], char out_arr[][15])
{
	char input, discard;

	for (size_t i = 0; i < SIZE; ++i)
	{
		for (size_t j = 0; j < SIZE; ++j)
		{
			scanf("%c%c", &input, &discard);
			arr[i][j] = input;
		}
	}

	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			out_arr[i][j] = '*';
}

void printArray(char arr[][15])
{
	for (size_t i = 0; i < SIZE; ++i)
	{
		for (size_t j = 0; j < SIZE; ++j)
		{
			printf("%c", arr[i][j]);
		}

		puts("");
	}
}

void searchArray(char arr[][15], char* key, char out_arr[][15])
{
	if ( strlen(key) > 15 )
		return;

	checkL2R(arr, key, out_arr);
	checkR2L(arr, key, out_arr);
	checkU2D(arr, key, out_arr);
	checkD2U(arr, key, out_arr);

	checkLDiag(arr, key, out_arr);
	checkLDiagR(arr, key, out_arr);
	checkRDiag(arr, key, out_arr);
	checkRDiagR(arr, key, out_arr);
}

void checkL2R(char arr[][15], char* key, char out_arr[][15])
{
	for (size_t y = 0; y < SIZE; ++y)
	{
		char* posInRow = strstr(arr[y], key);

		for (size_t x = 0; x < SIZE; ++x)
		{
			if (&arr[y][x] >= posInRow && &arr[y][x] <= posInRow + strlen(key) - 1)
				out_arr[y][x] = arr[y][x];

		}
	}
}

void checkR2L(char arr[][15], char* key, char out_arr[][15])
{
	char temp[20];

	for (int i = 0; i < strlen(key); ++i)
		temp[i] = key[i];

	reverseStr(key, temp);

	for (size_t y = 0; y < SIZE; ++y)
	{
		char* posInRow = strstr(arr[y], temp);

		for (size_t x = 0; x < SIZE; ++x)
		{
			if (&arr[y][x] >= posInRow && &arr[y][x] <= posInRow + strlen(key) - 1)
				out_arr[y][x] = arr[y][x];
		}
	}
}

void checkU2D(char arr[][15], char* key, char out_arr[][15])
{
	for (size_t x = 0; x < SIZE; ++x)
	{
		char col[15];

		for (int i = 0; i < SIZE; ++i)
		{
			col[i] = arr[i][x];
		}

		char* posInRow = strstr(col, key);

		for (size_t y = 0; y < SIZE; ++y)
		{
			if (y >= posInRow - col && y <= strlen(key) - 1)
				out_arr[y][x] = arr[y][x];
		}
	}
}

void checkD2U(char arr[][15], char* key, char out_arr[][15])
{
	for (size_t x = 0; x < SIZE; ++x)
	{
		char col[15];

		for (int i = 0; i < SIZE; ++i)
		{
			col[i] = arr[i][x];
		}

		char temp[20];

		for (int i = 0; i < strlen(key); ++i)
			temp[i] = key[i];

		reverseStr(key, temp);

		char* posInRow = strstr(col, temp);

		for (size_t y = 0; y < SIZE; ++y)
		{
			if (y < posInRow - col + strlen(key) && y >= posInRow - col)
				out_arr[y][x] = arr[y][x];
		}
	}
}


void checkLDiag(char arr[][15], char* key, char out_arr[][15])
{
	for (int line=1; line<=(SIZE + SIZE -1); line++)
	{
		int start_col =  max(0, line-SIZE);
		int count = min(line, (SIZE-start_col), SIZE);

		char temp[20];
		int j;

		for (j=0; j<count; j++)
			temp[j] = arr[minu(SIZE, line)-j-1][start_col+j];

		temp[j] = '\0';

		for (j=0; j<count; j++)
		{
			int pos = strstr(temp, key) - temp;

			if (strstr(temp, key) && line >= line - pos && line <= line - pos + strlen(key) && j >= pos && j < pos + strlen(key))
				out_arr[minu(SIZE, line)-j-1][start_col+j] = arr[minu(SIZE, line)-j-1][start_col+j];
		}
	}
}

void checkLDiagR(char arr[][15], char* key, char out_arr[][15])
{
	for (int line=1; line<=(SIZE + SIZE -1); line++)
	{
		int start_col =  max(0, line-SIZE);
		int count = min(line, (SIZE-start_col), SIZE);

		char temp[20];
		int j;

		for (j=0; j<count; j++)
			temp[j] = arr[minu(SIZE, line)-j-1][start_col+j];

		temp[j] = '\0';

		char temp2[20];

		for (int i = 0; i < strlen(key); ++i)
			temp2[i] = key[i];

		reverseStr(key, temp2);

		for (j=0; j<count; j++)
		{
			int pos = strstr(temp, temp2) - temp;

			if (strstr(temp, temp2) && line >= line - pos && line <= line - pos + strlen(key) && j >= pos && j < pos + strlen(key))
				out_arr[minu(SIZE, line)-j-1][start_col+j] = arr[minu(SIZE, line)-j-1][start_col+j];
		}
	}
}

void checkRDiag(char arr[][15], char* key, char out_arr[][15])
{
	for (int line=0; line<=(SIZE + SIZE -1); line++)
	{
		int start_col =  max(0, line-SIZE);
		int count = min(line, (SIZE-start_col), SIZE);

		char temp[20];
		int j;

		for (j=0; j<count; j++)
			temp[j] = arr[max(0, SIZE-line)+j][start_col+j];

		temp[j] = '\0';

		for (int j=0; j<count; ++j)
		{
			int pos = strstr(temp, key) - temp;

			if (strstr(temp, key) && line >= line - pos && line <= line - pos + strlen(key) && j >= pos && j < pos + strlen(key))
				out_arr[max(0, SIZE-line)+j][start_col+j] = arr[max(0, SIZE-line)+j][start_col+j];
		}
	}
}

void checkRDiagR(char arr[][15], char* key, char out_arr[][15])
{
	for (int line=0; line<=(SIZE + SIZE -1); line++)
	{
		int start_col =  max(0, line-SIZE);
		int count = min(line, (SIZE-start_col), SIZE);

		char temp[20];
		int j;

		for (j=0; j<count; j++)
			temp[j] = arr[max(0, SIZE-line)+j][start_col+j];

		temp[j] = '\0';

		char temp2[20];

		for (int i = 0; i < strlen(key); ++i)
			temp2[i] = key[i];

		reverseStr(key, temp2);

		for (int j=0; j<count; ++j)
		{
			int pos = strstr(temp, temp2) - temp;

			if (strstr(temp, temp2) && line >= line - pos && line <= line - pos + strlen(key) && j >= pos && j < pos + strlen(key))
				out_arr[max(0, SIZE-line)+j][start_col+j] = arr[max(0, SIZE-line)+j][start_col+j];
		}
	}
}

void reverseStr(char* in_str, char* out_str)
{
	int i = 0;

	for (char* ptr = in_str + strlen(in_str) - 1; ptr >= in_str; --ptr)
	{
		out_str[i++] = *ptr;
	}

	out_str[i] = '\0';
}

