#pragma once

#include "hardware/random.h"

#include <cstddef>
#include <cstdint>

// Size of key buffer in bytes.
extern const size_t CRYPTO_KEY_SIZE;

/**
 * Header size of encrypted message.
 * The size of encrypted buffer should be the
 * size of plain message in bytes + HEADER_SIZE.
 * The size of decrypted buffer should be the
 * size of encrypted message in bytes - HEADER_SIZE.
 */
extern const size_t CRYPTO_HEADER_SIZE;

/*
 * Operation success return codes.
 */
extern const int CRYPTO_SUCCESS;
extern const int CRYPTO_MESSAGE_FORGED;

/**
 * @brief Initialize the crypto library.
 *
 * @param random An instance of Random class to use to initialize
 *        the library.
 */
void crypto_init(Random &random);

/**
 * @brief Generate an encryption key.
 *
 * @param key Pointer to a buffer to write key to.
 *        The size of the key buffer should be KEY_SIZE.
 */
void key_generate(void *key);

/**
 * @brief Encrypt a message.
 *
 * @param plain Pointer to the plain message data.
 * @param plain_bytes Size of plain data in bytes.
 * @param key Pointer to key data.
 * @param encrypted Pointer to a buffer to write encrypted message to.
 *        The size of encrypted buffer should equal to plain_bytes + HEADER_SIZE.
 * @param msg_id Optional user purpose message id.
 * 
 * @return Return success code of the operation.
 */
int encrypt(const void *plain, const size_t plain_bytes, const void *key,
            void *encrypted, const uint64_t msg_id = 0);
            
/**
 * @brief Decrypt a message.
 *
 * @param encrypted Pointer to the encrypted message data.
 * @param encrypted_bytes Size of encrypted data in bytes.
 * @param key Pointer to key data.
 * @param plain Pointer to a buffer to write decrypted message to.
 *        The size of decrypted buffer should equal to encrypted_bytes - HEADER_SIZE.
 * @param msg_id Optional expected message id.
 * 
 * @return Return success code of the operation.
 */
int decrypt(const void *encrypted, const size_t encrypted_bytes, const void *key,
            void *plain, const uint64_t msg_id = 0);