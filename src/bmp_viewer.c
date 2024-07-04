#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#define OUTPUT_ALIGNMENT 20
#define HEADER_SIZE (14 + 40) // BMPFILEHEADER + BMPINFO of BMP version3

#pragma pack(2)
typedef struct bmp_header_version3_t {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;

    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
}bmp_header_version3;
#pragma pack()

static int print_bmp_header(bmp_header_version3* bmp_header);
static void error(const char* error_message, int exit_code);

/**
 * @return:
 * 0 - BMP header was printed successfully
 * 1 - file name argument is missing or more than 1 argument was given
 * 2 - occured error when opening file
 * 3 - BMP version is not supported
 * 4 - file format is uncorrect
 */
int main(int argc, char** argv) {
    if (argc < 2) {
        error("File name is required\n", 1);
    }
    if (argc > 2) {
        error("Only one file per time is available\n", 1);
    }
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        error("Erroor occured when opening file\n", 2);
    }

    bmp_header_version3 bmp_header;
    if (fread(&bmp_header, HEADER_SIZE, 1, fp) != 1) {
        error("File format is uncorrect\n", 4);
    }
    int exit_code = print_bmp_header(&bmp_header);
    switch (exit_code) {
        case 1: error("Internal error was occured\n", 1);
            break;

        case 3: error("BMP version is CORE (unsupported)\n", 3);
            break;

        case 4: error("File format is uncorrect\n", 4);
            break;
    }
    return 0;
}

static void error(const char* error_message, int exit_code) {
    fputs(error_message, stderr);
    exit(exit_code);
}

/**
 * Print humanity-readable description of bmp header (version 3,4,5 only)
 * @return:
 * 0 - BMP header was printed successfully
 * 1 - bmp header arg is NULL
 * 3 - BMP version is CORE (unsupported)
 * 4 - file format is uncorrect
 */
static int print_bmp_header(bmp_header_version3* bmp_header) {
    if (bmp_header == NULL) {
        return 1;
    }

    switch (bmp_header->biSize) {
        case 12:
            return 3;

        case 40:
            printf("\t%-*s : %u\n", OUTPUT_ALIGNMENT, "BMP version", 3);
            break;

        case 108:
            printf("\t%-*s : %u\n", OUTPUT_ALIGNMENT, "BMP version", 4);
            break;

        case 124:
            printf("\t%-*s : %u\n", OUTPUT_ALIGNMENT, "BMP version", 5);
            break;

        default:
            return 4;
    }
    printf("\t%-*s : %u\n", OUTPUT_ALIGNMENT, "File size", bmp_header->bfSize);
    printf("\t%-*s : %u\n", OUTPUT_ALIGNMENT, "Image Size", bmp_header->biSizeImage);
    printf("\t%-*s : %d\n", OUTPUT_ALIGNMENT, "Width", bmp_header->biWidth);
    printf("\t%-*s : %d\n", OUTPUT_ALIGNMENT, "Height", bmp_header->biHeight);
    char compressions[7][15] = { "none", "RLE8", "RLE4", "BITFIELDS", "JPEG", "PNG", "ALPHABITFIELDS" };
    if (bmp_header->biCompression <= 6) {
        printf("\t%-*s : %s\n", OUTPUT_ALIGNMENT, "Compression", compressions[bmp_header->biCompression]);
    }
    else {
        printf("\t%-*s : %s\n", OUTPUT_ALIGNMENT, "Compression", "uncorrect");
    }
    printf("\t%-*s : %u\n", OUTPUT_ALIGNMENT, "Bit/pixel", bmp_header->biBitCount);
    printf("\t%-*s : %dx%d\n", OUTPUT_ALIGNMENT, "Pixels/meter", bmp_header->biXPelsPerMeter, bmp_header->biYPelsPerMeter);
    return 0;
}
