import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  generateX25519KeyPair(): Promise<{ publicKey: string; privateKey: string }>;
  generateMlKemKeyPair(): Promise<{ publicKey: string; privateKey: string }>;
  x25519DeriveSecret(privateKey: string, publicKey: string): Promise<string>;
  mlKemEncapsulate(publicKey: string): Promise<{ sharedSecret: string; ciphertext: string }>;
  mlKemDecapsulate(privateKey: string, ciphertext: string): Promise<string>;
  deriveHybridSecret(x25519Secret: string, mlkemSecret: string): Promise<string>;
  encrypt(plaintext: string, sharedSecret: string, iv: string): Promise<string>;
  decrypt(ciphertext: string, iv: string, sharedSecret: string): Promise<string>;
  generateIV(): Promise<string>;
}

export default TurboModuleRegistry.getEnforcing<Spec>('PrivyxCrypto');
