// android/app/src/main/java/com/privyx/PrivyxCryptoPackage.kt
package com.privyx.crypto

import com.facebook.react.bridge.Promise
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactMethod
import com.facebook.react.bridge.ReactContextBaseJavaModule
import com.facebook.react.bridge.WritableNativeMap

class PrivyxCryptoModule(reactContext: ReactApplicationContext) :
    ReactContextBaseJavaModule(reactContext) {

    override fun getName() = "PrivyxCrypto"

    companion object {
        init {
            System.loadLibrary("privyx_crypto")
        }

        // JNI declarations
        @JvmStatic
        private external fun jniGenerateX25519KeyPair(): Array<String>
        @JvmStatic
        private external fun jniX25519DeriveSecret(privKey: String, pubKey: String): String
        @JvmStatic
        private external fun jniGenerateMlKemKeyPair(): Array<String>
        @JvmStatic
        private external fun jniMlKemEncapsulate(pubKey: String): Array<String>
        @JvmStatic
        private external fun jniMlKemDecapsulate(privKey: String, ct: String): String
        @JvmStatic
        private external fun jniDeriveHybridSecret(x25519: String, mlkem: String): String
        @JvmStatic
        private external fun jniEncrypt(pt: String, ss: String, iv: String): String
        @JvmStatic
        private external fun jniDecrypt(ct: String, iv: String, ss: String): String
        @JvmStatic
        private external fun jniGenerateIV(): String
    }

    @ReactMethod
    fun generateX25519KeyPair(promise: Promise) {
        try {
            val keys = jniGenerateX25519KeyPair()
            val result = WritableNativeMap()
            result.putString("publicKey", keys[0])
            result.putString("privateKey", keys[1])
            promise.resolve(result)
        } catch (e: Exception) {
            promise.reject("CRYPTO_ERROR", e.message, e)
        }
    }

    @ReactMethod
    fun generateMlKemKeyPair(promise: Promise) {
        try {
            val keys = jniGenerateMlKemKeyPair()
            val result = WritableNativeMap()
            result.putString("publicKey", keys[0])
            result.putString("privateKey", keys[1])
            promise.resolve(result)
        } catch (e: Exception) {
            promise.reject("CRYPTO_ERROR", e.message, e)
        }
    }

    @ReactMethod
    fun x25519DeriveSecret(privateKey: String, publicKey: String, promise: Promise) {
        try {
            promise.resolve(jniX25519DeriveSecret(privateKey, publicKey))
        } catch (e: Exception) {
            promise.reject("CRYPTO_ERROR", e.message, e)
        }
    }

    @ReactMethod
    fun mlKemEncapsulate(publicKey: String, promise: Promise) {
        try {
            val result = jniMlKemEncapsulate(publicKey)
            val map = WritableNativeMap()
            map.putString("sharedSecret", result[0])
            map.putString("ciphertext", result[1])
            promise.resolve(map)
        } catch (e: Exception) {
            promise.reject("CRYPTO_ERROR", e.message, e)
        }
    }

    @ReactMethod
    fun mlKemDecapsulate(privateKey: String, ciphertext: String, promise: Promise) {
        try {
            promise.resolve(jniMlKemDecapsulate(privateKey, ciphertext))
        } catch (e: Exception) {
            promise.reject("CRYPTO_ERROR", e.message, e)
        }
    }

    @ReactMethod
    fun deriveHybridSecret(x25519Secret: String, mlkemSecret: String, promise: Promise) {
        try {
            promise.resolve(jniDeriveHybridSecret(x25519Secret, mlkemSecret))
        } catch (e: Exception) {
            promise.reject("CRYPTO_ERROR", e.message, e)
        }
    }

    @ReactMethod
    fun encrypt(plaintext: String, sharedSecret: String, iv: String, promise: Promise) {
        try {
            promise.resolve(jniEncrypt(plaintext, sharedSecret, iv))
        } catch (e: Exception) {
            promise.reject("CRYPTO_ERROR", e.message, e)
        }
    }

    @ReactMethod
    fun decrypt(ciphertext: String, iv: String, sharedSecret: String, promise: Promise) {
        try {
            promise.resolve(jniDecrypt(ciphertext, iv, sharedSecret))
        } catch (e: Exception) {
            promise.reject("CRYPTO_ERROR", e.message, e)
        }
    }

    @ReactMethod
    fun generateIV(promise: Promise) {
        try {
            promise.resolve(jniGenerateIV())
        } catch (e: Exception) {
            promise.reject("CRYPTO_ERROR", e.message, e)
        }
    }
}
