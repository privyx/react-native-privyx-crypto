#ifndef libprivyx_crypto_h
#define libprivyx_crypto_h

#include <stddef.h>

void privyx_free_string(char *s);

void privyx_generate_x25519_keypair(char **out_pub, char **out_priv);
char *privyx_x25519_derive_secret(const char *private_key, const char *public_key);
void privyx_generate_mlkem_keypair(char **out_pub, char **out_priv);
void privyx_mlkem_encapsulate(const char *public_key, char **out_shared, char **out_ct);
char *privyx_mlkem_decapsulate(const char *private_key, const char *ciphertext);
char *privyx_derive_hybrid_secret(const char *x25519_secret, const char *mlkem_secret);
char *privyx_encrypt(const char *plaintext, const char *shared_secret, const char *iv);
char *privyx_decrypt(const char *ciphertext, const char *iv, const char *shared_secret);
char *privyx_generate_iv(void);

#endif
