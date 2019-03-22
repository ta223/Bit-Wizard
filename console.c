#include "Header.h"

void fflush_stdin(void) {

	char c;

	while ((c = getchar()) != '\n' && c != EOF);

}



char *Stdin_str() {

	char *str = (char *)malloc(sizeof(char) * 2);

	if (str == NULL) {

		fprintf(stderr, "System error: Insufficient memory\n");
		system("pause");
		exit(-1);

	}

	size_t used = 0, allocated = sizeof(char);

	int i = 0;

	char temp;

	while (1) {

		if (used == allocated)
			str = (char *)realloc(str, allocated += sizeof(char));

		temp = getchar();

		if (temp == '\n' || temp == '\t' || temp == EOF)
			break;

		str[i++] = temp;

		used += sizeof(char);

	}

	fflush_stdin();

	str[i] = '\0';

	return str;

}

Bool compare_string(const char *str1, const char *str2) {

	for (int i = 0; i < (int )strlen(str2); i++) {

		if (*(str1 + i) != '\n' &&  *(str1 + i) != *(str2 + i))
			return FALSE;

	}

	return TRUE;
}

double GetDouble() {

	char *Numstr;



	while (1) {

		Numstr = Stdin_str();

		if (compare_string((char *)Numstr, "zero"))
			return 0;

		if (atof(Numstr) == 0.0) {

			printf("\tInput Error: invalid number\n");

			printf("\tInput Enter the number again:");

			continue;

		}

		else
			return atof(Numstr);


	}



}

int GetInt() {

	char *Numstr;

	while (1) {

		Numstr = Stdin_str();

		if (compare_string((char *)Numstr, "zero"))
			return 0;

		if (atoi(Numstr) == 0) {

			printf("\tInput Error: invalid number\n");

			printf("\tInput Enter the number again:");

			continue;

		}

		else
			return atoi(Numstr);

	}


}

char *FileStream_str(const char *FileName) {

	FILE *fp = fopen((char *)FileName, "r");

	if (fp == NULL) {

		fprintf(stderr, "System error: File inexisent or invalid address in memory\n");

		return NULL;

	}

	char *str = (char *)(malloc(sizeof(char) * 2));

	if (str == NULL) {

		fprintf(stderr, "System error: Insufficient memory\n");

		exit(-1);

	}

	size_t used = 0, allocated = sizeof(char);

	int i = 0;

	char temp;

	while (1) {

		if (used == allocated)
			str = (char *)(realloc(str, allocated += sizeof(char)));

		temp = fgetc(fp);

		if (temp == EOF)
			break;

		str[i++] = temp;

		used += sizeof(char);

	}

	str[i] = '\0';

	fclose(fp);

	return str;

}
