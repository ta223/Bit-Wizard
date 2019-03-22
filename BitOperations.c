#include "Header.h"
#define INVALID_FILEPATH printf("Error:Invalid filepaths\n\n")

char *xor_string(const char *string){

    char *result = (char *)malloc(sizeof(char)*((strlen(string))+1));

    for(int i = 0; i < strlen(string);i++){

        char temp = string[i]^KEY2;
        if(isprint(temp) && string[i]!=KEY2)
            result[i] = temp;
        else
            result[i] = string[i];

    }

    result[strlen(string)] = '\0';

    return result;

}

/*crypts/decrypts txt files using xor bitwise operations*/
int File_XOR(char *FileName, char *password, char _key_) {

	FILE *fp = fopen(FileName,"r");
	FILE *temp = fopen("temp.txt","w");

	if (fp == NULL || temp == NULL) {
		printf("invalid file names\n");
		return -1;
	}

	char key = KEY;
    char *keyword = ".,1*;=*;:!872;";
    char str[1000];
    Bool password_encountered = FALSE, keyword_encountered = FALSE;

	while(1){

		fgets(str,1000,fp);

		if(feof(fp))
			break;

        if(keyword_encountered == FALSE && compare_string(str,keyword) == TRUE && password == NULL){
            printf("You do not have permission to decrypt this file\n");
            fclose(fp);
            fclose(temp);
            remove("temp.txt");
            return -1;
        }

		if (password !=NULL && password_encountered == FALSE && compare_string(str, password) == TRUE){
			key = KEY2;
            password_encountered = TRUE;
		}

		else{

            if (_key_ == KEY)
                key = KEY;

            if(_key_ == KEY2)
                key = KEY2;
		}

		for (int i = 0; i < (int )strlen(str); i++) {

			if( isprint(str[i]) && isprint(str[i]^key) && str[i]!=key)	//xor the characters
				str[i] = str[i]^key;

		}

		fprintf(temp,"%s",str);

	}

	fclose(fp);
	fclose(temp);


	if (remove((char *)FileName) == -1) {
		printf("error cannot remove original file %s\n\n",FileName);
		return -1;

	}

	if (rename("temp.txt", FileName) == -1) {
		printf("error renaming the file\n\n");
		return -1;
	}

	return 0;

}


int DebugBMP(const char *FileName) {

	FILE *image = fopen((char *)FileName, "rb");

	if (image == NULL)
		return -1;

	struct FileHeader fh;

	struct ImageHeader ih;

	fread(&fh, 1, 14, image);

	fread(&ih, 1, sizeof(ih), image);

	printf("cmd->BMP_FileData->%s\n:", FileName);

	printf("\tbfType = %c%c\n", fh.bfType[0], fh.bfType[1]);

	printf("\tbfSize = %d\n", fh.bfSize);

	printf("\tbfReserved1 = %d\n", fh.bfReserved1);

	printf("\tbfReserved2 = %d\n", fh.bfReserved2);

	printf("\tbfOffBits = %d\n", fh.bfOffBits);

	printf("\tbiSize = %d\n", ih.biSize);

	printf("\tbiWidth = %d\n", ih.biWidth);

	printf("\tbiHeight = %d\n", ih.biHeight);

	printf("\tbiPlanes = %d\n", ih.BiPlanes);

	printf("\tbiBitCount = %d\n", ih.biBitCount);

	printf("\tbiCompression = %d\n", ih.biCompression);

	printf("\tbiSizeImage = %ld\n", ih.biSizeImage);

	printf("\tbiXPelsPerMeter = %d\n", ih.biXPelsPerMeter);

	printf("\tbiYPelsPerMeter = %d\n", ih.biYPelsPerMeter);

	printf("\tbiClrUsed = %d\n", ih.biClrUsed);

	printf("\tbiClrImportantl = %d\n\n", ih.biClrImportantl);

	printf("\tprint pixel data?[y/n]:");

	char temp = getchar();

	fflush(stdin);

	if (temp == 'y') {

		printf("cmd->File Name:");

		char *Fname = Stdin_str();

		FILE *f = fopen((char *)Fname, "w");

		if (f == NULL)
			exit(-1);

		unsigned long int ImageSize = ih.biWidth*ih.biHeight;

		for (unsigned long int i = 0; i < ImageSize; i++) {

			byte color[3];

			fread(color, sizeof(color), 1, image);

			fprintf(f, "r = %d, g = %d, b = %d\n", color[2], color[1], color[0]);

		}

		fclose(f);

	}

	return 0;

}

/*xor the color of the pixels*/
int bmp_color_XOR(const char *FileName) {

	FILE *input_image = fopen((char *)FileName, "rb");
	char *NewFileName = "temp.bmp";
	FILE *output_image = fopen((char *)NewFileName, "wb");

	if (input_image == NULL || output_image == NULL) {
		printf("Error:Invalid filepaths\n\n");
		return -1;
	}

	struct FileHeader fh;
	struct ImageHeader ih;

	fread(&fh, 1, 14, input_image);
	fread(&ih, 1, sizeof(ih), input_image);

	fwrite(&fh, 1, 14, output_image);
	fwrite(&ih, 1, sizeof(ih), output_image);


	while (1) {

		byte color[3];

		fread(color, 1, sizeof(byte) * 3, input_image);

		//XOR the colors
		for (int j = 0; j < 3; j++) {

			byte temp = color[j];
			color[j] = color[j] ^ KEY;

			if (color[j] > 255 || color[j] < 0)
				color[j] = temp;

		}


		fwrite(color, 1, sizeof(byte) * 3, output_image);

		if (feof(input_image))
			break;
	}


	fclose(input_image);
	fclose(output_image);

	remove(FileName);
	rename("temp.bmp", FileName);

	system(FileName);

	return 0;

}

void fwrite_info(FILE *fp, struct FileHeader fh, struct ImageHeader ih, char *password) {

    fprintf(fp,"PROTECTED_FILE\n");
	fprintf(fp, "%s\n", password);
	fprintf(fp,"%d\n", fh.bfSize);
	fprintf(fp,"%d\n", fh.bfReserved1);
	fprintf(fp,"%d\n", fh.bfReserved2);
	fprintf(fp,"%d\n", fh.bfOffBits);
	fprintf(fp,"%d\n", ih.biSize);
	fprintf(fp,"%d\n", ih.biWidth);
	fprintf(fp,"%d\n", ih.biHeight);
	fprintf(fp,"%d\n", ih.BiPlanes);
	fprintf(fp,"%d\n", ih.biBitCount);
	fprintf(fp,"%d\n", ih.biCompression);
	fprintf(fp,"%ld\n", ih.biSizeImage);
	fprintf(fp,"%d\n", ih.biXPelsPerMeter);
	fprintf(fp,"%d\n", ih.biYPelsPerMeter);
	fprintf(fp,"%d\n", ih.biClrUsed);
	fprintf(fp,"%d\n", ih.biClrImportantl);

}

/*encrypt bmp files*/
int bmp_crypt(const char *FileName, char *password) {

	FILE *input_image = fopen((char *)FileName, "rb");

	if (input_image == NULL ) {
		INVALID_FILEPATH;
		printf("could not open input image\n");
		return -1;
	}

	char *NewFileName = (char *)malloc(sizeof(char)*(strlen(FileName)+1));	//txt file
	NewFileName = strcpy(NewFileName, FileName);	//now .bmp will be modified to .txt
	NewFileName[strlen(NewFileName) - 1] = 't';
	NewFileName[strlen(NewFileName) - 2] = 'x';
	NewFileName[strlen(NewFileName) - 3] = 't';

	FILE *output_image = fopen((char *)NewFileName, "w");

	if (output_image == NULL) {
		INVALID_FILEPATH;
		printf("could not open output image\n");
		return -1;
	}

	struct FileHeader fh;
	struct ImageHeader ih;

	fread(&fh, 1, 14, input_image);
	fread(&ih, 1, sizeof(ih), input_image);

	fwrite_info((FILE *)output_image, fh, ih, password);
	while (1) {

		byte color[3];

		fread(color, 1, sizeof(byte) * 3, input_image);

		if (feof(input_image))
			break;

		fprintf(output_image, "%d,%d,%d\n", color[0], color[1], color[2]);

	}

	fclose(input_image);
	fclose(output_image);

	remove(FileName);

	File_XOR(NewFileName, password, KEY);
	system(NewFileName);

	free(NewFileName);

	return 0;

}

void fread_info(FILE *fp, struct FileHeader *fh, struct ImageHeader *ih, char *password) {

	fh->bfType[0] = 'B';
	fh->bfType[1] = 'M';

	char str[100];

	fgets(str, 100, fp);    //reads protected keyword

	fgets(str, 100, fp);    //reads password

	for (int i = 0; i < strlen(str); i++)
		password[i] = str[i];

	fgets(str, 100, fp);
	fh->bfSize = atof(str);

	fgets(str, 100, fp);
	fh->bfReserved1 = atof(str);

	fgets(str, 100, fp);
	fh->bfReserved2 = atof(str);

	fgets(str, 100, fp);
	fh->bfOffBits = atof(str);

	fgets(str, 100, fp);
	ih->biSize = atof(str);

	fgets(str, 100, fp);
	ih->biWidth = atof(str);

	fgets(str, 100, fp);
	ih->biHeight = atof(str);

	fgets(str, 100, fp);
	ih->BiPlanes = atof(str);

	fgets(str, 100, fp);
	ih->biBitCount = atof(str);

	fgets(str, 100, fp);
	ih->biCompression = atof(str);

	fgets(str, 100, fp);
	ih->biSizeImage = atof(str);

	fgets(str, 100, fp);
	ih->biXPelsPerMeter = atof(str);

	fgets(str, 100, fp);
	ih->biYPelsPerMeter = atof(str);

	fgets(str, 100, fp);
	ih->biClrUsed = atof(str);

	fgets(str, 100, fp);
	ih->biClrImportantl = atof(str);


}

int bmp_decrypt(const char *FileName, char *user_password) {


    char *temp_pass = malloc(sizeof(char)*(strlen(user_password)+1));
    for(int i = 0; i < strlen(user_password);i++){

        if(isprint(user_password[i]^KEY2) && user_password[i]!=KEY2)
            temp_pass[i] = user_password[i]^KEY2;

        else
            temp_pass[i] = user_password[i];
    }

    temp_pass[strlen(user_password)] = '\0';

	if (File_XOR((char *)FileName, temp_pass, KEY) == -1) {	//decrypt the txt file
		printf("decrypt operation aborted\n\n");
		return -1;
	}

	FILE *input_image = fopen((char *)FileName, "r");

	if (input_image == NULL) {
		INVALID_FILEPATH;
		return -1;
	}

	struct FileHeader fh;
	struct ImageHeader ih;

	char *password = (char *)malloc(sizeof(char)*(strlen(user_password) + 1));
	fread_info(input_image, &fh, &ih, password);
	fh.bfOffBits = 0;
	password[strlen(user_password)] = '\0';

	if (compare_string(password, user_password) == FALSE) {

		printf("Error:Invalid password\n\n");
		fclose(input_image);
		return -1;

	}



	char *NewFileName = (char *)malloc(sizeof(char)*(strlen(FileName) + 1));
	NewFileName[strlen(FileName)] = '\0';
	NewFileName = strcpy(NewFileName, FileName);	//now .bmp will be modified to .txt
	NewFileName[strlen(NewFileName) - 1] = 'p';
	NewFileName[strlen(NewFileName) - 2] = 'm';
	NewFileName[strlen(NewFileName) - 3] = 'b';

	FILE *output_image = fopen((char *)NewFileName, "wb");

	if (output_image == NULL) {
		INVALID_FILEPATH;
		return -1;
	}

	fwrite(&fh, 1, 14, output_image);
	fwrite(&ih, 1, sizeof(ih), output_image);

	while (1) {

		byte color[3];

		char str[100];
		fgets(str, 100, input_image);

		if (feof(input_image))
			break;

		if (str[strlen(str) - 1] == '\n')
			str[strlen(str) - 1] = '\0';

		sscanf(str, "%d,%d,%d", &color[0], &color[1], &color[2]);

		fwrite(color, 1, sizeof(byte) * 3, output_image);

	}

	fclose(input_image);
	fclose(output_image);

	remove(FileName);
	system(NewFileName);

	return 0;

}

int CopyBMP(const char *FileName, const char *NewFileName) {

	FILE *input_image = fopen((char *)FileName, "rb");
	FILE *output_image = fopen((char *)NewFileName, "wb");

	if (input_image == NULL || output_image == NULL)
		return -1;

	struct FileHeader fh;
	struct ImageHeader ih;

	fread(&fh, 1, 14, input_image);
	fread(&ih, 1, sizeof(ih), input_image);

	fwrite(&fh, 1, 14, output_image);
	fwrite(&ih, 1, sizeof(ih), output_image);


	while (1) {

		byte color[3];
		fread(color, 1, sizeof(color), input_image);

		if (feof(input_image))
			break;

		fwrite(color, 1, sizeof(color), output_image);


	}


	fclose(input_image);
	fclose(output_image);

	return 0;

}

/*Modify the color of a single pixel of a BMP file - There is a bug, the program doesn't calculate the desired position of the pixel, need to figure out what coordinate system BMP files use */

void ModPixel(const char *FileName,struct Point *Pixel_Offset, byte new_color[3]) {

	FILE *input_image = fopen((char *)FileName, "rb");
	FILE *output_image = fopen("temp.bmp", "wb");

	if (input_image == NULL || output_image == NULL)
		return ;

	struct FileHeader fh;
	struct ImageHeader ih;

	fread(&fh, 1, 14, input_image);
	fread(&ih, 1, sizeof(ih), input_image);

	int w = ih.biWidth;	//width of the image

	const unsigned long int target_px = Pixel_Offset->y * w + Pixel_Offset->x;	//the pixel position int the 1D array, row*width + col
	unsigned long int index = 0;

	printf("targetpx:%ld\n", target_px);

	fwrite(&fh, 1, 14, output_image);
	fwrite(&ih, 1, sizeof(ih), output_image);

	byte color[3];

	while (1) {

		fread(color, 1, sizeof(color), input_image);

		if (feof(input_image))
			break;

		if (index == target_px) {	//change the selected pixel to the selected color

			for (int ctr = 0; ctr < 3; ctr++)
				color[2 - ctr] = new_color[ctr];

		}

		fwrite(color, 1, sizeof(color), output_image);

		index++;

	}

	fclose(input_image);
	fclose(output_image);

	printf("BMP file succesfully modified\n\n");
	remove(FileName);
	rename("temp.bmp", FileName);
	system(FileName);

}

/*stacks 3 bytes to form an integer of 32 bits (here 32 bits used actually but the 3rd byte's bits will be all 0, because C doesn't have uint24_t)*/
uint32_t StackBytes(byte color[3]) {

	uint16_t two_bytes = ((uint16_t)color[0] << 8) | color[1];	//transforms color[2] in 16 bits integer with last byte all 0, then performs an OR operation to with color[1] to store color[1] in the last byte on the right side

	uint32_t result = ((uint32_t)two_bytes << 8) | color[2];	//does the same operation as above to add the 3rd byte

	return result;

}


/*Modify a color from a image*/
void ModColor(const char *FileName, byte color_replace[3], byte new_color[3]) {

	FILE *input_image = fopen((char *)FileName, "rb");
	FILE *output_image = fopen("temp.bmp", "wb");

	if (input_image == NULL || output_image == NULL)
		return;

	struct FileHeader fh;
	struct ImageHeader ih;
	fread(&fh, 1, 14, input_image);
	fread(&ih, 1, sizeof(ih), input_image);
	fwrite(&fh, 1, 14, output_image);
	fwrite(&ih, 1, sizeof(ih), output_image);
	byte color[3];

	unsigned long int i = 0;	//counter, gets incremented the color to replace has been found | signals that the program has actually found the color to replace

	while (1) {

		fread(color, 1, sizeof(color), input_image);


		if (feof(input_image))
			break;

		/*check if this is the color to modify using byte stacking method*/

		if (StackBytes(color) == StackBytes(color_replace)) {	//this bascially takes the 3 values of colors and builds a uint32 data, then the value of the uint32 data is checked for both color and color_replace, if they match, they are the same color, this way a for loop is not needed to check if the two color match

			for (int ctr = 0; ctr < 3; ctr++)
				color[ctr] = new_color[ctr];

			i++;

		}

		fwrite(color, 1, sizeof(color), output_image);

	}

	fclose(input_image);
	fclose(output_image);
	remove(FileName);
	rename("temp.bmp", FileName);

	if (i != 0)
		printf("BMP file succesfully modified\n\n");

	else
		printf("Color not found\n");

	system(FileName);

}

