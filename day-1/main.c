#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <stdint.h>

typedef struct {
	char *buffer;
	size_t length;
} Line;

Line readLine(FILE *file);

int main(void)
{
	unsigned int sum = 0;
	FILE *fptr = fopen("input.txt", "r");
	if (fptr == NULL) {
		printf("Error: can not open file");
	}
	char number_char[3];
	number_char[2] = '\0';

	Line line = readLine(fptr);
	
	while (line.buffer && line.length != 0) {
		for (size_t i = 0; i < line.length; ++i)
			if (isdigit(line.buffer[i])) {
				number_char[0] = line.buffer[i];
				break;
			}

		for (size_t i = line.length - 1; i != SIZE_MAX; --i)
			if (isdigit(line.buffer[i])) {
				number_char[1] = line.buffer[i];
				break;
			}

		int number = atoi(number_char);

		printf("%s", line.buffer);
		printf(" | %d += %d", sum, number);
		printf("\n");


		sum += number;
		free(line.buffer);
		line = readLine(fptr);
	}

	fclose(fptr);

	printf("--------------------------------------------------\n");
	printf("Answer: %d\n", sum);

	return 0;
}

Line readLine(FILE *file)
{
	Line line;

	char *buffer = (char*)malloc(128*sizeof(char));
	char ch = getc(file);
	int cursor = 0;

	while ((ch != '\n') && (ch != EOF)) {
		buffer[cursor] = ch;
		cursor++;

		ch = getc(file);
	}

	if (ch == EOF) {
		line = (Line) {
			NULL,
			0
		};

		return line;
	}

	buffer[cursor] = '\0';
	buffer = realloc(buffer, cursor + 1);	

	line = (Line) {
		buffer,
		cursor + 1
	};

	return line;
}
