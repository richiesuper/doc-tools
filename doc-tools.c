#include <stdio.h>
#include <stdlib.h>

void count_lines(char *filename);
void count_sentences(char *filename);
void count_words(char *filename);

int main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr,
			"Usage: %s MODE FILE\n\n"
			"MODE:\n"
			"l\tcounts the number of lines in FILE\n"
			"s\tcounts the number of sentences in FILE\n"
			"w\tcounts the number of words in FILE\n",
			argv[0]);
		return -1;
	}

	switch (argv[1][0]) {
		default:
			fprintf(stderr,
				"Invalid mode!\n\n"
				"MODE:\n"
				"l\tcounts the number of lines in FILE\n"
				"s\tcounts the number of sentences in FILE\n"
				"w\tcounts the number of words in FILE\n");
			return -2;
			break;
		case 'l':
			count_lines(argv[2]);
			break;
		case 's':
			count_sentences(argv[2]);
			break;
		case 'w':
			count_words(argv[2]);
			break;
	}

	return 0;
}

void count_lines(char *filename)
{
	FILE *fp;
	char c;
	size_t count = 0;
	fp = fopen(filename, "r");

	if (!fp) {
		perror(filename);
		exit(-3);
	}

	while ((c = fgetc(fp)) != EOF) {
		if (c == '\n') {
			count++;
		}
	}

	printf("Line count of %s:\t%zu line(s)\n", filename, count);
}

void count_sentences(char *filename)
{
	FILE *fp;
	char c;
	size_t countDecl = 0, countInterro = 0, countImp = 0;

	fp = fopen(filename, "r");

	if (!fp) {
		perror(filename);
		exit(-3);
	}

	while ((c = fgetc(fp)) != EOF) {
		switch (c) {
			default:
				break;
			case '.':
				countDecl++;
				break;
			case '?':
				countInterro++;
				break;
			case '!':
				countImp++;
				break;
		}
	}

	printf("Sentence count of %s:\n"
			"Declarative  :\t%zu sentence(s)\n"
			"Interrogative:\t%zu sentence(s)\n"
			"Imperative   :\t%zu sentence(s)\n"
			"Total count  :\t%zu sentence(s)\n",
			filename, countDecl, countInterro, countImp,
			countDecl + countInterro + countImp);
}

void count_words(char *filename)
{
	FILE *fp;
	char c1 = '\0', c2;
	size_t count = 0;
	fp = fopen(filename, "r");

	if (!fp) {
		perror(filename);
		exit(-3);
	}

	while ((c2 = fgetc(fp)) != EOF) {
		if (c1 != ' ' && c1 != '\n') {
			if (c2 == ' ' || c2 == '\n') {
				count++;
			}
		}

		c1 = c2;
	}

	printf("Word count of %s:\t%zu word(s)\n", filename, count);
}
