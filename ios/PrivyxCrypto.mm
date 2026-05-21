#import <React/RCTBridgeModule.h>

extern "C" {
#include "../include/libprivyx_crypto.h"
}

@interface PrivyxCrypto : NSObject <RCTBridgeModule>
@end

@implementation PrivyxCrypto

RCT_EXPORT_MODULE()

+ (BOOL)requiresMainQueueSetup { return NO; }

RCT_EXPORT_METHOD(generateX25519KeyPair:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    char *pubKey = NULL;
    char *privKey = NULL;
    privyx_generate_x25519_keypair(&pubKey, &privKey);

    NSString *pubStr = [NSString stringWithUTF8String:pubKey];
    NSString *privStr = [NSString stringWithUTF8String:privKey];
    privyx_free_string(pubKey);
    privyx_free_string(privKey);

    resolve(@{ @"publicKey": pubStr, @"privateKey": privStr });
}

RCT_EXPORT_METHOD(generateMlKemKeyPair:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    char *pubKey = NULL;
    char *privKey = NULL;
    privyx_generate_mlkem_keypair(&pubKey, &privKey);

    NSString *pubStr = [NSString stringWithUTF8String:pubKey];
    NSString *privStr = [NSString stringWithUTF8String:privKey];
    privyx_free_string(pubKey);
    privyx_free_string(privKey);

    resolve(@{ @"publicKey": pubStr, @"privateKey": privStr });
}

RCT_EXPORT_METHOD(x25519DeriveSecret:(NSString *)privateKey
                  publicKey:(NSString *)publicKey
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    char *result = privyx_x25519_derive_secret(privateKey.UTF8String, publicKey.UTF8String);
    NSString *str = [NSString stringWithUTF8String:result];
    privyx_free_string(result);
    resolve(str);
}

RCT_EXPORT_METHOD(mlKemEncapsulate:(NSString *)publicKey
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    char *shared = NULL;
    char *ct = NULL;
    privyx_mlkem_encapsulate(publicKey.UTF8String, &shared, &ct);

    NSString *sharedStr = [NSString stringWithUTF8String:shared];
    NSString *ctStr = [NSString stringWithUTF8String:ct];
    privyx_free_string(shared);
    privyx_free_string(ct);

    resolve(@{ @"sharedSecret": sharedStr, @"ciphertext": ctStr });
}

RCT_EXPORT_METHOD(mlKemDecapsulate:(NSString *)privateKey
                  ciphertext:(NSString *)ciphertext
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    char *result = privyx_mlkem_decapsulate(privateKey.UTF8String, ciphertext.UTF8String);
    NSString *str = [NSString stringWithUTF8String:result];
    privyx_free_string(result);
    resolve(str);
}

RCT_EXPORT_METHOD(deriveHybridSecret:(NSString *)x25519Secret
                  mlkemSecret:(NSString *)mlkemSecret
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    char *result = privyx_derive_hybrid_secret(x25519Secret.UTF8String, mlkemSecret.UTF8String);
    NSString *str = [NSString stringWithUTF8String:result];
    privyx_free_string(result);
    resolve(str);
}

RCT_EXPORT_METHOD(encrypt:(NSString *)plaintext
                  sharedSecret:(NSString *)sharedSecret
                  iv:(NSString *)iv
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    char *result = privyx_encrypt(plaintext.UTF8String, sharedSecret.UTF8String, iv.UTF8String);
    NSString *str = [NSString stringWithUTF8String:result];
    privyx_free_string(result);
    resolve(str);
}

RCT_EXPORT_METHOD(decrypt:(NSString *)ciphertext
                  iv:(NSString *)iv
                  sharedSecret:(NSString *)sharedSecret
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    char *result = privyx_decrypt(ciphertext.UTF8String, iv.UTF8String, sharedSecret.UTF8String);
    NSString *str = [NSString stringWithUTF8String:result];
    privyx_free_string(result);
    resolve(str);
}

RCT_EXPORT_METHOD(generateIV:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    char *result = privyx_generate_iv();
    NSString *str = [NSString stringWithUTF8String:result];
    privyx_free_string(result);
    resolve(str);
}

@end
