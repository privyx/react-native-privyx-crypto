# react-native-privyx-crypto

Post-quantum hybrid cryptography for React Native.

Combines **X25519** (ECDH) + **ML-KEM-768** (post-quantum KEM) with **AES-256-GCM** encryption. Uses prebuilt native binaries — no Rust toolchain required.

## Installation

```bash
npm install react-native-privyx-crypto
```

For iOS, after installing:

```bash
cd ios && pod install
```

## Usage

```ts
import {
  generateX25519KeyPair,
  generateMlKemKeyPair,
  x25519DeriveSecret,
  mlKemEncapsulate,
  mlKemDecapsulate,
  deriveHybridSecret,
  encrypt,
  decrypt,
  generateIV,
} from 'react-native-privyx-crypto';
```

### Key Generation

```ts
// Generate X25519 (ECDH) key pair
const x25519 = await generateX25519KeyPair();
// { publicKey: 'base64...', privateKey: 'base64...' }

// Generate ML-KEM-768 (post-quantum) key pair
const mlkem = await generateMlKemKeyPair();
// { publicKey: 'base64...', privateKey: 'base64...' }
```

### Key Exchange (Initiator)

```ts
// Alice derives shared secret using her private key + Bob's public keys
const x25519Secret = await x25519DeriveSecret(alice.privateKey, bob.x25519PublicKey);

const mlkemEnc = await mlKemEncapsulate(bob.mlkemPublicKey);
// { sharedSecret: 'base64...', ciphertext: 'base64...' }

const hybridSecret = await deriveHybridSecret(x25519Secret, mlkemEnc.sharedSecret);
```

### Key Exchange (Responder)

```ts
// Bob derives shared secret using his private key + Alice's ciphertext
const x25519Secret = await x25519DeriveSecret(bob.privateKey, alice.x25519PublicKey);

const mlkemSecret = await mlKemDecapsulate(bob.mlkemPrivateKey, mlkemCiphertext);

const hybridSecret = await deriveHybridSecret(x25519Secret, mlkemSecret);
```

Both parties arrive at the same `hybridSecret`.

### Encrypt / Decrypt

```ts
const iv = await generateIV();
const ciphertext = await encrypt('Hello, post-quantum world!', hybridSecret, iv);

const plaintext = await decrypt(ciphertext, iv, hybridSecret);
```

## API

All functions return `Promise`. All keys and ciphertexts are base64-encoded strings.

| Function | Returns |
|---|---|
| `generateX25519KeyPair()` | `{ publicKey, privateKey }` |
| `generateMlKemKeyPair()` | `{ publicKey, privateKey }` |
| `x25519DeriveSecret(privateKey, publicKey)` | `string` (shared secret) |
| `mlKemEncapsulate(publicKey)` | `{ sharedSecret, ciphertext }` |
| `mlKemDecapsulate(privateKey, ciphertext)` | `string` (shared secret) |
| `deriveHybridSecret(x25519Secret, mlkemSecret)` | `string` (SHA-256 hybrid) |
| `encrypt(plaintext, sharedSecret, iv)` | `string` (base64 ciphertext) |
| `decrypt(ciphertext, iv, sharedSecret)` | `string` (plaintext) |
| `generateIV()` | `string` (base64 12-byte IV) |

## Supported Platforms

| Platform | Architectures |
|---|---|
| Android | arm64-v8a, armeabi-v7a, x86_64 |
| iOS (device) | arm64 |
| iOS (simulator) | arm64-sim, x86_64-sim |

## Requirements

- React Native >= 0.71
- Android minSdk 24+
- iOS 15.1+

## License

MIT
