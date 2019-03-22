#include "Header.h"

Bool check_file_extension(const char *FileName, char *extension) {

	char *_ext;

	if (compare_string(extension, "bmp"))
		_ext = "bmp";

	if (compare_string(extension, "txt"))
		_ext = "txt";

	if (FileName[strlen(FileName) - 1] == _ext[2] && FileName[strlen(FileName) - 2] == _ext[1] && FileName[strlen(FileName) - 3] == _ext[0])
		return TRUE;

	else {

		printf("\nError:invalid file extension. File must be in %s format\n",_ext);
		return FALSE;
	}



}

int main() {

	srand(time(NULL));

	while (1) {

		fflush(stdin);

		printf("\n[cmd]:");

		char *cmd = Stdin_str();

		if (compare_string((char *)cmd, "crypt:bmp") == TRUE) {

			char *FileName, *password;

			do {
				printf("\nFileName:");
				FileName = Stdin_str();

			} while (check_file_extension(FileName, "bmp") == FALSE);

			printf("\nset password:");
			password = Stdin_str();

			bmp_crypt(FileName, password);

		}

		if (compare_string((char *)cmd, "decrypt:bmp") == TRUE) {

			char *FileName, *password;

			do {
				printf("\nFileName:");
				FileName = Stdin_str();

			} while (check_file_extension(FileName, "txt") == FALSE);

			printf("\npassword:");
			password = Stdin_str();
			bmp_decrypt(FileName, password);

		}


		if (compare_string((char *)cmd, "bmp:fileheader")) {

			char *FileName;

			do {
				printf("\nFileName:");
				FileName = Stdin_str();

			} while (check_file_extension(FileName, "bmp") == FALSE);

			DebugBMP((char *)FileName);

		}


		if (compare_string((char *)cmd, "change_pixel_color")) {

			struct Point Offset;
			uint8_t new_color[3];

			char *FileName;

			do {
				printf("\nFileName:");
				FileName = Stdin_str();

			} while (check_file_extension(FileName, "bmp") == FALSE);

			printf("pixel offset[x,y]:");
			char *num = Stdin_str();

			if(num[strlen(num)-1]=='\n')
				num[strlen(num) - 1] = '\0';

			sscanf(num, "%d,%d", &Offset.x, &Offset.y);

			printf("%d,%d\n", Offset.x, Offset.y);

			printf("\nNew color[r,g,b]:");
			char *str = Stdin_str();

			if (str[strlen(str) - 1] == '\n')
				str[strlen(str) - 1] = '\0';

			sscanf(str, "%d,%d,%d", &new_color[0], &new_color[1], &new_color[2]);

			ModPixel(FileName, &Offset, new_color);

		}

		if (compare_string((char *)cmd, "change_color")) {

			byte new_color[3];

			char *FileName;

			do {
				printf("\nFileName:");
				FileName = Stdin_str();

			} while (check_file_extension(FileName,"bmp") == FALSE);

			printf("\nColor to replace[b,g,r]:");
			char *str = Stdin_str();
			byte color[3];

			if (str[strlen(str) - 1] == '\n')
				str[strlen(str) - 1] = '\0';

			sscanf(str, "%d,%d,%d", &color[0], &color[1], &color[2]);

			printf("\nNew color[b,g,r]:");
			str = Stdin_str();

			if (str[strlen(str) - 1] == '\n')
				str[strlen(str) - 1] = '\0';

			sscanf(str, "%d,%d,%d", &new_color[0], &new_color[1], &new_color[2]);


			ModColor(FileName, color, new_color);

		}


		if (compare_string((char *)cmd, "^txt")) {

			printf("\nFileName:");
			char *FileName = Stdin_str();
			File_XOR(FileName,NULL, KEY2);
			char *msg = FileStream_str(FileName);
			printf("%s",msg);
			system(FileName);

		}

		if (compare_string((char *)cmd, "exit"))
			break;

		if (compare_string((char *)cmd, "cls"))
			system("cls");


	}/*end while*/


	return 0;
}
