/* *****************************************************************************

 * Description : BASE64 encoding and decoding

 * Date             : 06-08-21 21:00 

 * Author          :  aishen944

 * Copryright   :  

********************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BASE64_PAD64 '='

char base64_alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                          'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                          'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a',
                          'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                          'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                          't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1',
                          '2', '3', '4', '5', '6', '7', '8', '9', '+',
                          '/'};

unsigned char base64_suffix_map[256] = {
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255,  62, 255, 255, 255,  63,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 255, 255,
     255, 255, 255, 255, 255,  0,   1,    2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,
     15,   16,  17,  18,  19,  20,  21,  22,  23,  24,  25, 255, 255, 255, 255, 255, 255,  26,  27,  28,
     29,   30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
     49,   50,  51, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};


/*
static char cmove_bits(unsigned char src, unsigned int lnum, unsigned int rnum) {
   src <<= lnum;
   src >>= rnum;
   return src;
}
*/

#define cmove_bits(s, l, r)	((((s << (l)) & 0xFF) >> (r)) & 0xFF)
//#define cmove_bits(s, l, r) (unsigned char)((unsigned char)((unsigned char)(s) << (unsigned int)(l)) >> (unsigned int)(r))

int base64_encode(char *out, const char *data, int insize) 
{
	char *retpos;
	int m, padnum = 0, retsize, dlen = insize;

	if(dlen == 0) return 0;

	/* Account the result buffer size and alloc the memory for it. */
	if((dlen % 3) != 0)
		padnum = 3 - dlen % 3;
	retsize = (dlen + padnum) + ((dlen + padnum) * 1/3);
	if ( !out ) return retsize;

	retpos = out;

	/* Starting to convert the originality characters to BASE64 chracaters. 
		Converting process keep to 4->6 principle. */
	for(m = 0; m < (dlen + padnum); m += 3) {
		/* When data is not suffice 24 bits then pad 0 and the empty place pad '='. */
		*(retpos) = base64_alphabet[cmove_bits(*data, 0, 2)];
		if(m == dlen + padnum - 3 && padnum != 0) {  /* Whether the last bits-group suffice 24 bits. */
			if(padnum == 1) {   /* 16bit need pad one '='. */
				*(retpos + 1) = base64_alphabet[cmove_bits(*data, 6, 2) + cmove_bits(*(data + 1), 0, 4)];
				*(retpos + 2) = base64_alphabet[cmove_bits(*(data + 1), 4, 2)];
				*(retpos + 3) = BASE64_PAD64;
			} else if(padnum == 2) { /* 8bit need pad two'='. */
				*(retpos + 1) = base64_alphabet[cmove_bits(*data, 6, 2)];
				*(retpos + 2) = BASE64_PAD64;
				*(retpos + 3) = BASE64_PAD64;
			}
		} else {  /* 24bit normal. */
			*(retpos + 1) = base64_alphabet[cmove_bits(*data, 6, 2) + cmove_bits(*(data + 1), 0, 4)];
			*(retpos + 2) = base64_alphabet[cmove_bits(*(data + 1), 4, 2) + cmove_bits(*(data + 2), 0, 6)];
			*(retpos + 3) = base64_alphabet[*(data + 2) & 0x3f];
		}

		retpos += 4;
		data += 3;
	}

	return retsize;
}

int base64_decode(char *out, const char *bdata, int insize) 
{
   char *retpos;
   int m, padnum = 0, retsize = 0;

   if(insize == 0) return 0;
   if(insize % 4 != 0) return 0;

   /* Whether the data have invalid base-64 characters? */
   for(m = 0; m < insize; ++m) {
      if(bdata[m] != BASE64_PAD64 && (unsigned char)base64_suffix_map[bdata[m]] == 255)
         goto LEND;
   }

   /* Account the output size. */
   if(bdata[insize - 1] ==  '=')  padnum = 1;
   if(bdata[insize - 1] == '=' && bdata[insize - 2] ==  '=') padnum = 2;
   retsize = (insize - 4) - (insize - 4) / 4 + (3 - padnum);
   if ( !out ) return retsize;
   retpos = out; 

   /* Begging to decode. */
   for(m = 0; m < insize; m += 4) {
      *retpos = cmove_bits(base64_suffix_map[*bdata], 2, 0) + cmove_bits(base64_suffix_map[*(bdata + 1)], 0, 4);
      if(m == insize - 4 && padnum != 0) {  /* Only deal with last four bits. */
         if(padnum == 1)   /* Have one pad characters, only two availability characters. */
            *(retpos + 1) = cmove_bits(base64_suffix_map[*(bdata + 1)], 4, 0) + cmove_bits(base64_suffix_map[*(bdata + 2)], 0, 2);
         /*
         Have two pad characters, only two availability characters.
         if(padnum == 2) { 
         }
         */
         retpos += 3 - padnum;
      } else {
         *(retpos + 1) = cmove_bits(base64_suffix_map[*(bdata + 1)], 4, 0) + cmove_bits(base64_suffix_map[*(bdata + 2)], 0, 2);
         *(retpos + 2) = cmove_bits(base64_suffix_map[*(bdata + 2)], 6, 0) + base64_suffix_map[*(bdata + 3)];
         retpos += 3;
      }
      bdata += 4;
   }


   LEND: return retsize;
}

