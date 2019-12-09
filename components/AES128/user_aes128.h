#ifndef __USER_AES128_H_
#define __USER_AES128_H_


// #define the macros below to 1/0 to enable/disable the mode of operation.
//
// CBC_T enables AES encryption in CBC_T-mode of operation.
// CTR_T enables encryption in counter-mode.
// ECB_T enables the basic ECB_T 16-byte block algorithm. All can be enabled simultaneously.

// The #ifndef-guard allows it to be configured before #include'ing or at compile time.
#ifndef CBC_T
  #define CBC_T 0
#endif

#ifndef ECB_T
  #define ECB_T 0
#endif

#ifndef CTR_T
  #define CTR_T 1
#endif


#define AES128 1
//#define AES192 1
//#define AES256 1

#define AES_BLOCKLEN 16 //Block length in bytes AES is 128b block only

#if defined(AES256) && (AES256 == 1)
    #define AES_KEYLEN 32
    #define AES_keyExpSize 240
#elif defined(AES192) && (AES192 == 1)
    #define AES_KEYLEN 24
    #define AES_keyExpSize 208
#else
    #define AES_KEYLEN 16   // Key length in bytes
    #define AES_keyExpSize 176
#endif

struct AES_ctx
{
  uint8_t RoundKey[AES_keyExpSize];
#if (defined(CBC_T) && (CBC_T == 1)) || (defined(CTR_T) && (CTR_T == 1))
  uint8_t Iv[AES_BLOCKLEN];
#endif
};

void AES_init_ctx(struct AES_ctx* ctx, const uint8_t* key);
#if (defined(CBC_T) && (CBC_T == 1)) || (defined(CTR_T) && (CTR_T == 1))
void AES_init_ctx_iv(struct AES_ctx* ctx, const uint8_t* key, const uint8_t* iv);
void AES_ctx_set_iv(struct AES_ctx* ctx, const uint8_t* iv);
#endif

#if defined(ECB_T) && (ECB_T == 1)
// buffer size is exactly AES_BLOCKLEN bytes; 
// you need only AES_init_ctx as IV is not used in ECB_T 
// NB: ECB_T is considered insecure for most uses
void AES_ECB_encrypt(struct AES_ctx* ctx, uint8_t* buf);
void AES_ECB_decrypt(struct AES_ctx* ctx, uint8_t* buf);

#endif // #if defined(ECB_T) && (ECB_T == !)


#if defined(CBC_T) && (CBC_T == 1)
// buffer size MUST be mutile of AES_BLOCKLEN;
// Suggest https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme
// NOTES: you need to set IV in ctx via AES_init_ctx_iv() or AES_ctx_set_iv()
//        no IV should ever be reused with the same key 
void AES_CBC_encrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length);
void AES_CBC_decrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length);

#endif // #if defined(CBC_T) && (CBC_T == 1)


#if defined(CTR_T) && (CTR_T == 1)

// Same function for encrypting as for decrypting. 
// IV is incremented for every block, and used after encryption as XOR-compliment for output
// Suggesting https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme
// NOTES: you need to set IV in ctx with AES_init_ctx_iv() or AES_ctx_set_iv()
//        no IV should ever be reused with the same key 
void AES_CTR_xcrypt_buffer(struct AES_ctx* ctx, uint8_t* in, uint8_t* out, uint32_t length);

#endif // #if defined(CTR_T) && (CTR_T == 1)


#endif
