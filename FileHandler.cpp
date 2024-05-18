#include "FileHandler.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QFileDialog>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

FileHandler::FileHandler(QObject *parent) : QObject(parent) {
    // Initialize OpenSSL algorithms
    OpenSSL_add_all_algorithms();
}

const QByteArray CONST_KEY = QByteArray::fromHex("00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff");

void FileHandler::setFileInfo() {
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Select a File", "", "All Files (*)");
    if (filePath.isEmpty()) {
        qDebug() << "No file selected";
        return;
    }

    m_filePath = filePath;
    QFileInfo fileInfo(filePath);

    qDebug() << "Emitting filePathChanged with:" << fileInfo.absoluteFilePath();
    qDebug() << "Emitting fileSizeChanged with:" << fileInfo.size();
    qDebug() << "Emitting fileExtensionChanged with:" << fileInfo.suffix();

    emit filePathChanged(fileInfo.absoluteFilePath());
    emit fileSizeChanged(fileInfo.size());
    emit fileExtensionChanged(fileInfo.suffix());
}

void FileHandler::encryptFile() {
    if (m_filePath.isEmpty()) {
        qDebug() << "No file selected";
        return;
    }

    QString destPath = QFileDialog::getSaveFileName(nullptr, "Save Encrypted File", "", "All Files (*)");
    if (destPath.isEmpty()) {
        qDebug() << "No destination file selected";
        return;
    }

    QFile inFile(m_filePath);
    QFile outFile(destPath);
    if (!inFile.open(QFile::ReadOnly) || !outFile.open(QFile::WriteOnly)) {
        qDebug() << "Failed to open files";
        return;
    }

    QByteArray iv(16, 0);  // AES block size (16 bytes)
    RAND_bytes(reinterpret_cast<unsigned char*>(iv.data()), iv.size());

    outFile.write(iv); // Write IV to output file for decryption

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, reinterpret_cast<const unsigned char*>(CONST_KEY.data()), reinterpret_cast<const unsigned char*>(iv.data()));

    const int bufferSize = 4096;
    unsigned char inBuffer[bufferSize];
    unsigned char outBuffer[bufferSize + EVP_MAX_BLOCK_LENGTH];
    int inLen, outLen;

    while ((inLen = inFile.read(reinterpret_cast<char*>(inBuffer), bufferSize)) > 0) {
        if (!EVP_EncryptUpdate(ctx, outBuffer, &outLen, inBuffer, inLen)) {
            qDebug() << "Encryption failed";
            EVP_CIPHER_CTX_free(ctx);
            inFile.close();
            outFile.close();
            return;
        }
        outFile.write(reinterpret_cast<char*>(outBuffer), outLen);
    }

    if (!EVP_EncryptFinal_ex(ctx, outBuffer, &outLen)) {
        qDebug() << "Final encryption failed";
        EVP_CIPHER_CTX_free(ctx);
        inFile.close();
        outFile.close();
        return;
    }
    outFile.write(reinterpret_cast<char*>(outBuffer), outLen);

    EVP_CIPHER_CTX_free(ctx);
    inFile.close();
    outFile.close();

    qDebug() << "Encryption completed";
}

void FileHandler::decryptFile() {
    if (m_filePath.isEmpty()) {
        qDebug() << "No file selected";
        return;
    }

    QString destPath = QFileDialog::getSaveFileName(nullptr, "Save Decrypted File", "", "All Files (*)");
    if (destPath.isEmpty()) {
        qDebug() << "No destination file selected";
        return;
    }

    QFile inFile(m_filePath);
    QFile outFile(destPath);
    if (!inFile.open(QFile::ReadOnly) || !outFile.open(QFile::WriteOnly)) {
        qDebug() << "Failed to open files";
        return;
    }

    QByteArray iv(16, 0);  // AES block size (16 bytes)
    if (inFile.read(iv.data(), iv.size()) != iv.size()) {
        qDebug() << "Failed to read IV";
        inFile.close();
        outFile.close();
        return;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, reinterpret_cast<const unsigned char*>(CONST_KEY.data()), reinterpret_cast<const unsigned char*>(iv.data()));

    const int bufferSize = 4096;
    unsigned char inBuffer[bufferSize];
    unsigned char outBuffer[bufferSize + EVP_MAX_BLOCK_LENGTH];
    int inLen, outLen;

    while ((inLen = inFile.read(reinterpret_cast<char*>(inBuffer), bufferSize)) > 0) {
        if (!EVP_DecryptUpdate(ctx, outBuffer, &outLen, inBuffer, inLen)) {
            qDebug() << "Decryption failed";
            EVP_CIPHER_CTX_free(ctx);
            inFile.close();
            outFile.close();
            return;
        }
        outFile.write(reinterpret_cast<char*>(outBuffer), outLen);
    }

    if (!EVP_DecryptFinal_ex(ctx, outBuffer, &outLen)) {
        qDebug() << "Final decryption failed";
        EVP_CIPHER_CTX_free(ctx);
        inFile.close();
        outFile.close();
        return;
    }
    outFile.write(reinterpret_cast<char*>(outBuffer), outLen);

    EVP_CIPHER_CTX_free(ctx);
    inFile.close();
    outFile.close();

    qDebug() << "Decryption completed";
}
