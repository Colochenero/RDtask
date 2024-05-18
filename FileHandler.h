#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QString>

class FileHandler : public QObject {
    Q_OBJECT
public:
    explicit FileHandler(QObject *parent = nullptr);

public slots:
    void encryptFile();
    void decryptFile();
    void setFileInfo();

signals:
    void filePathChanged(const QString &filePath);
    void fileSizeChanged(qint64 fileSize);
    void fileExtensionChanged(const QString &fileExtension);

private:
    QString m_filePath;
};

#endif // FILEHANDLER_H
