import NativePrivyxCrypto from './NativePrivyxCrypto';

export const generateX25519KeyPair = () => NativePrivyxCrypto.generateX25519KeyPair();
export const generateMlKemKeyPair = () => NativePrivyxCrypto.generateMlKemKeyPair();
export const x25519DeriveSecret = (privateKey: string, publicKey: string) =>
  NativePrivyxCrypto.x25519DeriveSecret(privateKey, publicKey);
export const mlKemEncapsulate = (publicKey: string) => NativePrivyxCrypto.mlKemEncapsulate(publicKey);
export const mlKemDecapsulate = (privateKey: string, ciphertext: string) =>
  NativePrivyxCrypto.mlKemDecapsulate(privateKey, ciphertext);
export const deriveHybridSecret = (x25519Secret: string, mlkemSecret: string) =>
  NativePrivyxCrypto.deriveHybridSecret(x25519Secret, mlkemSecret);
export const encrypt = (plaintext: string, sharedSecret: string, iv: string) =>
  NativePrivyxCrypto.encrypt(plaintext, sharedSecret, iv);
export const decrypt = (ciphertext: string, iv: string, sharedSecret: string) =>
  NativePrivyxCrypto.decrypt(ciphertext, iv, sharedSecret);
export const generateIV = () => NativePrivyxCrypto.generateIV();
