#include "shifrfile.h"

ShifrFile::ShifrFile(QObject *parent):
    QObject{parent} {}

ShifrFile::ShifrFile(const QString _filePath, QObject *parent):
    filePath(_filePath), QObject{parent} {}


bool ShifrFile::workWithFile()
{
    QMutexLocker locker(&mutex);

    //qInfo(logInfo()) << "Class - ShifrFile, workWithFile";

    std::shared_ptr<fileWorker> file = std::make_shared<fileWorker>(filePath);
    file->setOutputDir(outputDir);
    file->setOverWrite(overWrite);

    if(!file->openFile())
    {
        emit fileFinished(filePath, "", file->getErrorBuf());
        return false;
    }

    return createModifiedFile(file);
}

bool ShifrFile::createModifiedFile(const std::shared_ptr<fileWorker>& fileW)
{
    //qInfo(logInfo()) << "Class - ShifrFile, createModifiedFile";

    QFile modifiedFile;
    modifiedFile.setFileName(fileW->getModifiedFileName());

    if (!modifiedFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        //qInfo(logWarning()) << "Class - ShifrFile, createModifiedFile::Ошибка открытия модифицированного файла";
        error_buf = "Ошибка открытия модифицированного файла";
        emit fileFinished(filePath, modifiedFile.fileName(), error_buf);
        return false;
    }

    while(!fileW->sourceFile.atEnd()){
        QByteArray buffer = fileW->sourceFile.read(4960),
            result_xor = xorEncryptDecrypt(buffer);
        modifiedFile.write(result_xor);
        emit progressByte(filePath, result_xor.size());
    }

    modifiedFile.close();
    emit fileFinished(filePath, modifiedFile.fileName(), error_buf);
    return true;
}


QByteArray ShifrFile::xorEncryptDecrypt(QByteArray data){
    QByteArray xor_key_byte = QByteArray::fromHex(xorKey.toUtf8()), result;
    for (int i = 0; i < data.size(); ++i)
        result.append(data[i] ^ xor_key_byte[i % xor_key_byte.size()]);
    return result;
}

void ShifrFile::setXorKey(QString xor_key){
    this->xorKey = xor_key;
}

void ShifrFile::setOutputDir(QString path){
    outputDir = path;
}

void ShifrFile::setOverwrite(bool mode){
    overWrite = mode;
}

QString ShifrFile::getXorKey(){
    return xorKey;
}

QString ShifrFile::getOutputDir(){
    return outputDir;
}

bool ShifrFile::getOverwrite(){
    return overWrite;
}

QString ShifrFile::getLastError(){
    return error_buf;
}
