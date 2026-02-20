#ifndef SHIFRFILE_H
#define SHIFRFILE_H

#include <QObject>
#include <QDataStream>
#include <QByteArray>
#include <QBuffer>
#include <QFile>
#include <QRegularExpression>
#include <QDir>
#include <QLabel>
#include <QMutex>
#include <memory.h>

#include "fileworker.h"

class ShifrFile : public QObject
{
    Q_OBJECT

public:
    explicit ShifrFile(QObject *parent = nullptr);
    ShifrFile(const QString _filePath, QObject *parent = nullptr);

    void setXorKey(QString xor_key);
    void setOverwrite(bool mode);
    void setOutputDir(QString path);

    bool getOverwrite();
    QString getXorKey();
    QString getOutputDir();
    QString getLastError();

public slots:
    bool workWithFile();

signals:
    void progressByte(QString file_path, quint64 byte);
    void fileFinished(QString file_path, QString new_file_path, QString error);

private:
    QString filePath;
    QString xorKey;
    QString outputDir;
    QString error_buf;
    QMutex mutex;
    bool overWrite;

private:
    bool createModifiedFile (const std::shared_ptr<fileWorker>& fileW);
    QByteArray xorEncryptDecrypt(QByteArray data);
};

#endif // SHIFRFILE_H
