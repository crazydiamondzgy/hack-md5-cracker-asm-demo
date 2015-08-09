#include "md5.h"

extern void md5_memcpy (unsigned char *output, unsigned char *input, int len);
extern void md5_memset(unsigned char *output, int value, int len);
extern void md5_encode(unsigned char *output, uint32_t *input, int len);
extern void md5_transform(uint32_t state[4], unsigned char block[64]);

static unsigned char PADDING[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void MD5Update (MD5_CTX *context, unsigned char *input, unsigned int inputLen)
{
	unsigned int i, index, partLen;
	
	index = (unsigned int)((context->count[0] >> 3) & 0x3F);
	
	if ((context->count[0] += ((uint32_t)inputLen << 3)) < ((uint32_t)inputLen << 3))
		context->count[1]++;
	context->count[1] += ((uint32_t)inputLen >> 29);
	
	partLen = 64 - index;
	
	if (inputLen >= partLen) {
		md5_memcpy((unsigned char *)&context->buffer[index], (unsigned char *)input, partLen);
		md5_transform (context->state, context->buffer);
		
		for (i = partLen; i + 63 < inputLen; i += 64)
			md5_transform (context->state, &input[i]);
		
		index = 0;
	}
	else
		i = 0;
	
	md5_memcpy((unsigned char *)&context->buffer[index], (unsigned char *)&input[i], inputLen-i);
}

void MD5Final (unsigned char digest[16], MD5_CTX *context)
{
	unsigned char bits[8];
	unsigned int index, padLen;
	
	md5_encode (bits, context->count, 8);
	
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	MD5Update (context, PADDING, padLen);
	
	MD5Update (context, bits, 8);	
}