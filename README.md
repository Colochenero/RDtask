# Qt QML File Encryption/Decryption Application

## Overview

This desktop application provides AES-256-CBC encryption and decryption for any file on the user's system. It allows users to:
- Select any file from the system
- View file details (path, size, extension)
- Encrypt and decrypt the file using the OpenSSL library
- Save the output file with custom name and location

The UI is built using QML with reusable custom components .Backend logic is written in C++.

---

## Features

✅ Select any file on the computer  
✅ Show file details (path, size, extension)  
✅ Encrypt the file using AES-256-CBC with OpenSSL  
✅ Decrypt encrypted files and restore their original extension  
✅ Reusable and modular UI components  
✅ Smooth progress update and error handling using Qt signals/slots

---
## Encryption Specs
-Algorithm: AES (Advanced Encryption Standard)
-Key Size: 256 bits
-Mode: CBC (Cipher Block Chaining)
-Library: OpenSSL 

## Technologies Used

- **Qt 5/6** (QML + C++)
- **OpenSSL** (Encryption/Decryption using AES-256-CBC)
- **CMake / qmake** for build configuration

  ### Requirements

- Qt 5.15+ or Qt 6.x
- OpenSSL installed (ensure headers and shared libraries are accessible)
- C++17 compiler

---
