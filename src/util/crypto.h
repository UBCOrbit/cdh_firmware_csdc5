#pragma once

#include <cstddef>
#include <cstdint>

extern const size_t KEY_SIZE;
// If a function returns this, the output buffer has invalid data.
// This happens when an invalid key is used for decryption.
extern const size_t INVALID_SIZE;

/**
 * @brief Generate an encryption key.
 *
 * @param key Pointer to a buffer to write key to.
 */
void key_generate(void *key);

/**
 * @brief Encrypt a message.
 *
 * @param plain Pointer to the plain message data.
 * @param plain_bytes Size of plain data in bytes.
 * @param key Pointer to key data.
 * @param encrypted Pointer to a buffer to write encrypted message to.
 * @param msg_id Optional user purpose message id.
 * 
 * @return Size of decrypted in bytes.
 */
size_t encrypt(const void *plain, const size_t plain_bytes, const void *key,
               void *encrypted, const uint64_t msg_id = 0);
            
/**
 * @brief Decrypt a message.
 *
 * @param encrypted Pointer to the encrypted message data.
 * @param encrypted_bytes Size of encrypted data in bytes.
 * @param key Pointer to key data.
 * @param plain Pointer to a buffer to write decrypted message to.
 * @param msg_id Optional expected message id.
 * 
 * @return Size of decrypted in bytes.
 */
size_t decrypt(const void *encrypted, const size_t encrypted_bytes, const void *key,
               void *plain, const uint64_t msg_id = 0);