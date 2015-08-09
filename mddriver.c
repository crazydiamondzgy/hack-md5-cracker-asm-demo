#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "md5.h"

static void MDPrint (unsigned char digest[16])
{
	unsigned int i;
	
	for (i = 0; i < 16; i++)
		printf ("%02x", digest[i]);
}

static void MD5String (char *string)
{
	MD5_CTX context;
	unsigned char digest[16];
	unsigned int len = strlen (string);
	
	MD5Init (&context);
	MD5Update (&context, string, len);
	MD5Final (digest, &context);
	
	printf ("MD5 (\"%s\") = ", string);
	MDPrint (digest);
	printf ("\n");
}

int main()
{
	char all_chars[] = "0123456789";
	char tmp[128];
	int spacelen = strlen(all_chars);
	int pwlen = 8;
	char *tmpspace[8+1];
	int i;
	unsigned char digest[16];

	MD5_CTX context;
	DWORD dwTime = GetTickCount();
	
	memset(tmp, '\0', sizeof(tmp));
	
	tmpspace[0]=&all_chars[0];
	for (i=1; i<=pwlen; i++) {
		tmpspace[i]=0;
	}
	
	while(!tmpspace[pwlen]) {
		for (i=0; i<=pwlen; i++) {
			if(tmpspace[i] != 0)
				tmp[i]=*tmpspace[i];
			else 
				break;
		}
		
		MD5Init (&context);
		MD5Update (&context, (unsigned char*)tmp, strlen(tmp));
		MD5Final (digest, &context);
		
		tmpspace[0]++;
		
		for (i=0; i<pwlen; i++) {
			if (tmpspace[i] > &all_chars[spacelen -1]) {
				tmpspace[i] = &all_chars[0];
				if (tmpspace[i+1] !=0)
					tmpspace[i+1]++;
				else
					tmpspace[i+1] = &all_chars[0];
			}
		}
	}
	
	dwTime = GetTickCount() - dwTime;
	printf("spend time: %d seconds\n",dwTime/1000);

	printf ("MD5 test suite:\n");
	
	MD5String("");
	MD5String("a");
	MD5String("abc");
	MD5String("message digest");
	MD5String("abcdefghijklmnopqrstuvwxyz");
	MD5String("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	MD5String("12345678901234567890123456789012345678901234567890123456789012345678901234567890");

	getchar();
}
