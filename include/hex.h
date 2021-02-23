#ifndef _TO_HEX_H_
#define _TO_HEX_H_

//#include "stdafx.h"

void toHexW(wchar_t *dest, void *source, int size);
void toHexA(char *dest, void *source, int size);

//user is resposible to call free() when the data is no longer used
wchar_t *toHexW(void *source, int size);
char *toHexA(void *source, int size);

//
//  Function to convert a Hexadecimal string to the equivalent binary content
//

/*
  return 0 if size match
  return - (negative value) if the size is smaller than the buffer size
  return + (positive value) if the size is larger than the buffer size
*/
int hexstr2bin_s(const char HexDataIn[], OUT unsigned char BinDataOut[], size_t BinDataOut_max_size);

void hexstr2bin(const char HexDataIn[], OUT unsigned char BinDataOut[], OUT OPTIONAL unsigned int *BinDataOut_len);
void hexwstr2bin(const wchar_t *HexDataIn, OUT unsigned char BinDataOut[], OUT OPTIONAL unsigned int *BinDataOut_len);
void hex_string_to_bin(const char *hex_str, OUT BYTE **output, OUT size_t *output_size);

//
//	To convert a binary string to a hex string
//
//void bin2hexstr(const unsigned char input[], int input_sz, char output[], int * output_sz);

BOOL is_hex(TCHAR c);

//
// return -1 if all the string is a valid hexa decimal characters
// return zero based index of the position of the invalid hexa decimal character
//
int get_non_hexa_decimal_position(LPCTSTR str);

#ifdef _UNICODE
#define toHex toHexW
#else
#define toHex toHexA
#endif

#endif