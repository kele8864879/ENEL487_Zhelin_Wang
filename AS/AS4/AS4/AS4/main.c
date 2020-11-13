/**********************************************************************
 *
 * Filename:    main.c
 *
 * Description: A simple test program for the CRC implementations.
 *
 * Notes:       To test a different CRC standard, modify crc.h.
 *
 *
 * Copyright (c) 2000 by Michael Barr.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "crc.h"



main(void)
{
	clock_t start, finish; // used to pick time by clock()
	float  duration;		// Start - Finish
	int size = 0;           // File size init
	char* test;				//pointer to save file
	FILE* fp;				//pointer to open txt

	fp = fopen("wrnpc11.txt", "r");
	if (fp == NULL)
		return 1;

	//get file size
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);

	// regester a space to save file
	test = (char*)malloc(sizeof(char) * size);

	//READfile
	fseek(fp, 0, SEEK_SET);
	fread(test, size, sizeof(char), fp);
	fclose(fp);
	
	/*
	 * Print the check value for the selected CRC algorithm.
	 */
	printf("The check value for the %s standard is 0x%X\n", CRC_NAME, CHECK_VALUE);

	/*
	 * Compute the CRC of the test message, slowly.
	 */
	start = clock();
	printf("The crcSlow() of \"wrnpc11\" is 0x%X\n", crcSlow(test, strlen(test)));
	finish = clock();
	duration = (float)(finish - start) / CLOCKS_PER_SEC;
	printf("crsSlow runs %f seconds\n", duration);
	/*
	 * Compute the CRC of the test message, more efficiently.
	 */
	crcInit();
	start = clock();
	printf("The crcFast() of \"wrnpc11\" is 0x%X\n", crcFast(test, strlen(test)));
	finish = clock();
	duration = (float)(finish - start) / CLOCKS_PER_SEC;
	printf("crsFast runs %f seconds\n", duration);
	
	free(test);
}   /* main() */