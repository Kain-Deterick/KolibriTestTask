#include "shifrfile.h"

ShifrFile::ShifrFile(QObject *parent):
    overwrite(false), QObject{parent} {}

ShifrFile::ShifrFile(QString _filePath, QObject *parent):
    filePath(_filePath), overwrite(false), QObject{parent} {}


bool ShifrFile::startModified(){
    if (!openFile()){
        emit finished(filePath, "", error_buf);
        return false;
    }

    QFile modifiedFile;
    QFileInfo fileInfo(filePath);
    QString file_basename = fileInfo.completeBaseName();
    QString file_suffix = fileInfo.suffix();
    QString file_name = fileInfo.fileName();

    if (overwrite){
         modifiedFile.setFileName(outputDir + '/' + file_name);
    }
    else{
        QDir dir_save(outputDir);
        QStringList list_filename = dir_save.entryList({file_basename + "*"}, QDir::Files);
        QRegularExpression regex(QString("^%1_(\\d+)$").arg(QRegularExpression::escape(file_basename)));
        qulonglong max_counter = 0;
        bool find_filename = false;
        for (const QString &dir_filename : list_filename){
            if (!find_filename && file_name == dir_filename)
                find_filename = true;
            QRegularExpressionMatch match = regex.match(QFileInfo(dir_filename).completeBaseName());
            if (match.hasMatch()) {
                int counter = match.captured(1).toInt();
                if (counter > max_counter) {
                    max_counter = counter;
                }
            }
        }

        /* Если модифицированные файлы отсутствуют - задать имя исходного файла, иначе - задать имя файла со счетчиком*/
        QString add_text;
        if (find_filename || max_counter)
            add_text = "_" + QString::number(++max_counter);
        modifiedFile.setFileName(outputDir + '/' + file_basename + add_text + '.' + file_suffix);
    }

    if (!modifiedFile.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        error_buf = "Ошибка открытия модифицированного файла";
        emit finished(filePath, modifiedFile.fileName(), error_buf);
        return false;
    }

    while(!file.atEnd()){
        QByteArray buffer = file.read(4960),
            result_xor = xorEncryptDecrypt(buffer);
        modifiedFile.write(result_xor);
        emit progressByte(filePath, result_xor.size());
    }

    file.close();
    modifiedFile.close();
    emit finished(filePath, modifiedFile.fileName(), error_buf);
}

bool ShifrFile::openFile(){
    file.setFileName(filePath);
    if (file.isOpen()){
        error_buf = "Ошибка, файл уже открыт";
        return false;
    }

    if (!file.open(QIODevice::ReadOnly)){
        error_buf = "Ошибка открытия файла";
        return false;
    }
    return true;
}

QByteArray ShifrFile::xorEncryptDecrypt(QByteArray data){
    QByteArray xor_key_byte = QByteArray::fromHex(xorKey.toUtf8()), result;
    for (int i = 0; i < data.size(); ++i)
        result.append(data[i] ^ xor_key_byte[i % xor_key_byte.size()]);
    return result;
}

void ShifrFile::setFilepath(QString file_path){
    this->filePath = file_path;
}

void ShifrFile::setXorKey(QString xor_key){
    this->xorKey = xor_key;
}

void ShifrFile::setOutputDir(QString path){
    outputDir = path;
}

void ShifrFile::setOverwrite(bool mode){
    overwrite = mode;
}

QString ShifrFile::getFilepath(){
    return filePath;
}

QString ShifrFile::getFilename(){
    return QFileInfo(filePath).completeBaseName();
}

QString ShifrFile::getXorKey(){
    return xorKey;
}

QString ShifrFile::getOutputDir(){
    return outputDir;
}

bool ShifrFile::getOverwrite(){
    return overwrite;
}

QString ShifrFile::getLastError(){
    return error_buf;
}

quint64 ShifrFile::getSizeFile(){
    return QFileInfo(filePath).size();
}

