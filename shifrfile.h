#ifndef SHIFRFILE_H
#define SHIFRFILE_H

#include <QObject>
#include <QDataStream>
#include <QByteArray>
#include <QBuffer>
#include <QFile>
#include <QRegularExpression>
#include <QDir>

class ShifrFile : public QObject
{
    Q_OBJECT
public:
    ShifrFile(QObject *parent = nullptr);
    ShifrFile(QString _filePath, QObject *parent = nullptr);

    void setFilepath(QString file_path);
    void setXorKey(QString xor_key);
    void setOutputDir(QString path);
    void setOverwrite(bool mode);

    bool getOverwrite();
    QString getFilename();
    QString getFilepath();
    QString getXorKey();
    QString getOutputDir();
    quint64 getSizeFile();
    QString getLastError();

    bool startModified();
    QByteArray xorEncryptDecrypt(QByteArray data);
private:
    bool modifiedFile();
    bool openFile();

private:
    QString filePath;
    QString xorKey;
    QString outputDir;
    QString error_buf;
    bool overwrite;
    QFile file;

signals:
    void progressByte(QString file_path, quint64 byte);
    void finished(QString file_path, QString new_file_path, QString error);
};

#endif // SHIFRFILE_H
