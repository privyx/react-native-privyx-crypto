// native/privyx-crypto/src/jni.c
#include <jni.h>
#include <stdlib.h>
#include <string.h>

// Declarations from Rust FFI
extern void privyx_generate_x25519_keypair(char **out_pub, char **out_priv);
extern char *privyx_x25519_derive_secret(const char *private_key, const char *public_key);
extern void privyx_generate_mlkem_keypair(char **out_pub, char **out_priv);
extern void privyx_mlkem_encapsulate(const char *public_key, char **out_shared, char **out_ct);
extern char *privyx_mlkem_decapsulate(const char *private_key, const char *ciphertext);
extern char *privyx_derive_hybrid_secret(const char *x25519_secret, const char *mlkem_secret);
extern char *privyx_encrypt(const char *plaintext, const char *shared_secret, const char *iv);
extern char *privyx_decrypt(const char *ciphertext, const char *iv, const char *shared_secret);
extern char *privyx_generate_iv(void);
extern void privyx_free_string(char *s);

// Helper: convert Java string to malloc'd C string
static char *jstring_to_c(JNIEnv *env, jstring js) {
    const char *utf = (*env)->GetStringUTFChars(env, js, NULL);
    char *c = strdup(utf);
    (*env)->ReleaseStringUTFChars(env, js, utf);
    return c;
}

// Helper: convert C string to Java string, then free the C string
static jstring c_to_jstring_free(JNIEnv *env, char *cs) {
    jstring js = (*env)->NewStringUTF(env, cs);
    privyx_free_string(cs);
    return js;
}

JNIEXPORT jobjectArray JNICALL
Java_com_privyx_crypto_PrivyxCryptoModule_jniGenerateX25519KeyPair(JNIEnv *env, jclass clazz) {
    char *pub = NULL, *priv = NULL;
    privyx_generate_x25519_keypair(&pub, &priv);

    jclass strClass = (*env)->FindClass(env, "java/lang/String");
    jobjectArray arr = (*env)->NewObjectArray(env, 2, strClass, NULL);
    (*env)->SetObjectArrayElement(env, arr, 0, (*env)->NewStringUTF(env, pub));
    (*env)->SetObjectArrayElement(env, arr, 1, (*env)->NewStringUTF(env, priv));
    privyx_free_string(pub);
    privyx_free_string(priv);
    return arr;
}

JNIEXPORT jstring JNICALL
Java_com_privyx_crypto_PrivyxCryptoModule_jniX25519DeriveSecret(JNIEnv *env, jclass clazz, jstring priv, jstring pub) {
    char *cpriv = jstring_to_c(env, priv);
    char *cpub = jstring_to_c(env, pub);
    char *result = privyx_x25519_derive_secret(cpriv, cpub);
    free(cpriv);
    free(cpub);
    return c_to_jstring_free(env, result);
}

JNIEXPORT jobjectArray JNICALL
Java_com_privyx_crypto_PrivyxCryptoModule_jniGenerateMlKemKeyPair(JNIEnv *env, jclass clazz) {
    char *pub = NULL, *priv = NULL;
    privyx_generate_mlkem_keypair(&pub, &priv);

    jclass strClass = (*env)->FindClass(env, "java/lang/String");
    jobjectArray arr = (*env)->NewObjectArray(env, 2, strClass, NULL);
    (*env)->SetObjectArrayElement(env, arr, 0, (*env)->NewStringUTF(env, pub));
    (*env)->SetObjectArrayElement(env, arr, 1, (*env)->NewStringUTF(env, priv));
    privyx_free_string(pub);
    privyx_free_string(priv);
    return arr;
}

JNIEXPORT jobjectArray JNICALL
Java_com_privyx_crypto_PrivyxCryptoModule_jniMlKemEncapsulate(JNIEnv *env, jclass clazz, jstring pub) {
    char *cpub = jstring_to_c(env, pub);
    char *shared = NULL, *ct = NULL;
    privyx_mlkem_encapsulate(cpub, &shared, &ct);
    free(cpub);

    jclass strClass = (*env)->FindClass(env, "java/lang/String");
    jobjectArray arr = (*env)->NewObjectArray(env, 2, strClass, NULL);
    (*env)->SetObjectArrayElement(env, arr, 0, (*env)->NewStringUTF(env, shared));
    (*env)->SetObjectArrayElement(env, arr, 1, (*env)->NewStringUTF(env, ct));
    privyx_free_string(shared);
    privyx_free_string(ct);
    return arr;
}

JNIEXPORT jstring JNICALL
Java_com_privyx_crypto_PrivyxCryptoModule_jniMlKemDecapsulate(JNIEnv *env, jclass clazz, jstring priv, jstring ct) {
    char *cpriv = jstring_to_c(env, priv);
    char *cct = jstring_to_c(env, ct);
    char *result = privyx_mlkem_decapsulate(cpriv, cct);
    free(cpriv);
    free(cct);
    return c_to_jstring_free(env, result);
}

JNIEXPORT jstring JNICALL
Java_com_privyx_crypto_PrivyxCryptoModule_jniDeriveHybridSecret(JNIEnv *env, jclass clazz, jstring x, jstring m) {
    char *cx = jstring_to_c(env, x);
    char *cm = jstring_to_c(env, m);
    char *result = privyx_derive_hybrid_secret(cx, cm);
    free(cx);
    free(cm);
    return c_to_jstring_free(env, result);
}

JNIEXPORT jstring JNICALL
Java_com_privyx_crypto_PrivyxCryptoModule_jniEncrypt(JNIEnv *env, jclass clazz, jstring pt, jstring ss, jstring iv) {
    char *cpt = jstring_to_c(env, pt);
    char *css = jstring_to_c(env, ss);
    char *civ = jstring_to_c(env, iv);
    char *result = privyx_encrypt(cpt, css, civ);
    free(cpt);
    free(css);
    free(civ);
    return c_to_jstring_free(env, result);
}

JNIEXPORT jstring JNICALL
Java_com_privyx_crypto_PrivyxCryptoModule_jniDecrypt(JNIEnv *env, jclass clazz, jstring ct, jstring iv, jstring ss) {
    char *cct = jstring_to_c(env, ct);
    char *civ = jstring_to_c(env, iv);
    char *css = jstring_to_c(env, ss);
    char *result = privyx_decrypt(cct, civ, css);
    free(cct);
    free(civ);
    free(css);
    return c_to_jstring_free(env, result);
}

JNIEXPORT jstring JNICALL
Java_com_privyx_crypto_PrivyxCryptoModule_jniGenerateIV(JNIEnv *env, jclass clazz) {
    return c_to_jstring_free(env, privyx_generate_iv());
}
