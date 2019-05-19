#include "crypto.h"
#include "hardware/random.h"
#include <hydrogen.h>

static const char* CONTEXT = "General";
const size_t CRYPTO_KEY_SIZE = hydro_secretbox_KEYBYTES;
const size_t CRYPTO_HEADER_SIZE = hydro_secretbox_HEADERBYTES;
const int CRYPTO_SUCCESS = 0;
const int CRYPTO_MESSAGE_FORGED = 1;

void key_generate(void *key) {
    hydro_secretbox_keygen((uint8_t*)key);
}

int encrypt(const void *plain, const size_t plain_bytes, const void *key, 
               void *encrypted, const uint64_t msg_id)
{
    hydro_secretbox_encrypt((uint8_t*)encrypted, plain, plain_bytes, 
                            msg_id, CONTEXT, (const uint8_t*)key);
    return CRYPTO_SUCCESS;
}

int decrypt(const void *encrypted, const size_t encrypted_bytes, const void *key,
               void *plain, const uint64_t msg_id)
{
    if (hydro_secretbox_decrypt(plain, (const uint8_t*)encrypted, encrypted_bytes, 
                                msg_id, CONTEXT, (const uint8_t*)key) != 0) {
        return CRYPTO_MESSAGE_FORGED;
    }
    return CRYPTO_SUCCESS;
}
