#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

#define KEY '~'
#define KEY2 '!'	//for password encryption


typedef uint8_t byte;
typedef int Bool;

struct Point {

	int x, y;

};


struct ColorStruct{

	byte color[3];

};

/*BMP format = http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm*/

/*Allocation of 14 bytes for file header*/

struct FileHeader {

	unsigned char bfType[2];	/*characters "BM" | 2 bytes */
	unsigned int bfSize;	/*dimension of file in bytes | 4 bytes*/
	unsigned short int bfReserved1, bfReserved2;	/* reserved bytes, 0 default | 4 bytes in total*/
	uint32_t bfOffBits;	/*Initial Pixel field offset | 4 bytes*/

};

/*Allocation of 40 bytes for Info header*/
struct ImageHeader {

	unsigned int biSize;	/*size of header = 40 | 4 bytes */
	unsigned int biWidth; /* image width in number of pixels | 4 bytes */
	unsigned int biHeight;	/*image height in number of pixels | 4 bytes*/
	unsigned short int BiPlanes;	/*minimum val = 1 | 2 bytes*/
	unsigned short int biBitCount;	/*Bits per pixels 1,4,8,16,32 | 2 bytes*/
	unsigned int biCompression;	/*Compression type,  0 = RGB (No compression), 1 = RLE8, 2 = RLE4, 3 = BITFIELDS | 4 bytes*/
	unsigned long int biSizeImage;	/*Size of image| 4 bytes*/
	unsigned int biXPelsPerMeter, biYPelsPerMeter;	/*resolution in pixels per meter for x and y| 4 bytes*/
	unsigned int biClrUsed;	/* Number of colors actually used | 4 bytes*/
	unsigned int biClrImportantl;	/* number of significant colors | 4 bytes*/

};


extern void fflush_stdin(void);
extern char *Stdin_str();
extern Bool compare_string(const char *str1, const char *str2);
extern double GetDouble();
extern int GetInt();
extern char *FileStream_str(const char *FileName);
extern int File_XOR(char *FileName, char *password, char _key_);
extern int DebugBMP(const char *FileName);
extern int bmp_color_XOR(const char *FileName);
extern int bmp_crypt(const char *FileName, char *password);
extern int bmp_decrypt(const char *FileName, char *user_password);
extern int CopyBMP(const char *FileName, const char *NewFileName);
extern void ModPixel(const char *FileName, struct Point *Pixel_Offset, byte new_color[3]);
extern uint32_t StackBytes(byte color[3]);
extern void ModColor(const char *FileName, byte color_replace[3], byte new_color[3]);
