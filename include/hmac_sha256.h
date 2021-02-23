#pragma once
#define HMAC_SHA256_DIGEST_SIZE 32  /* Same as SHA-256's output size. */

void
hmac_sha256(BYTE out[HMAC_SHA256_DIGEST_SIZE],
	const BYTE *data, size_t data_len,
	const BYTE *key, size_t key_len);
