#    define int8_t   char
#    define uint8_t  unsigned char
#    define int16_t  short
#    define uint16_t unsigned short
#    define int32_t  int
#    define uint32_t unsigned int
#    define int64_t  __int64
#    define uint64_t unsigned __int64

typedef struct {
  uint32_t state[4];
  uint32_t count[2];
  unsigned char buffer[64];
} MD5_CTX;

void MD5Init(MD5_CTX *context);
void MD5Update(MD5_CTX *context, unsigned char *, unsigned int);
void MD5Final(unsigned char [16], MD5_CTX *);
