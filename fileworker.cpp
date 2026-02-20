#include "fileworker.h"

fileWorker::fileWorker(QString _filePath):
    filePath(_filePath), overWrite(false) {}

fileWorker::~fileWorker()
{
    sourceFile.close();
}
bool fileWorker::openFile()
{
    //qInfo(logInfo()) << "Class - fileWorker, openFile";

    sourceFile.setFileName(filePath);
    if (sourceFile.isOpen())
    {
        qInfo(logWarning()) << "Class - fileWorker, openFile::(Ошибка, файл уже открыт)";
        errorBuf = "Ошибка, файл уже открыт";
        return false;
    }

    if (!sourceFile.open(QIODevice::ReadOnly))
    {
        qInfo(logWarning()) << "Class - fileWorker, openFile::(Ошибка открытия файла)";
        errorBuf = "Ошибка открытия файла";
        return false;
    }

    setFilesBSN();
    return true;
}

QString fileWorker::getModifiedFileName()
{
    //qInfo(logInfo()) << "Class - fileWorker, getModifiedFileName";
    QString modifiedFileName;

    if (overWrite){
       modifiedFileName = outputDir + '/' + file_name;
    }
    else{
        QDir dir_save(outputDir);
        QStringList list_filenames = dir_save.entryList({file_basename + "*"}, QDir::Files);

        bool findOriginFile = chechOriginFile(list_filenames);
        qulonglong max_counter = findMaxCounter(list_filenames);;

        /* Если модифицированные файлы отсутствуют - задать имя исходного файла, иначе - задать имя файла со счетчиком*/
        QString add_text;
        if (findOriginFile || max_counter)
            add_text = "_" + QString::number(++max_counter);

        modifiedFileName = outputDir + '/' + file_basename + add_text + '.' + file_suffix;
    }
    return modifiedFileName;
}

bool fileWorker::chechOriginFile(QStringList& list_filenames)
{
    for (const QString &dir_filename : list_filenames){
        if (file_name == dir_filename)
        {
            return true;
        }
    }
    return false;
}

qulonglong fileWorker::findMaxCounter(QStringList& list_filenames)
{
    qulonglong maxCounter = 0;

    QRegularExpression regex(QString("^%1_(\\d+)$").arg(QRegularExpression::escape(file_basename)));

    for (const QString &dir_filename : list_filenames){
        QRegularExpressionMatch match = regex.match(QFileInfo(dir_filename).completeBaseName());
        if (match.hasMatch()) {
            int counter = match.captured(1).toInt();
            if (counter > maxCounter) {
               maxCounter = counter;
            }
        }
    }
    return maxCounter;
}

void fileWorker::setOverWrite(bool _mode){
    overWrite = _mode;
}

void fileWorker::setOutputDir(QString _path){
    outputDir = _path;
}

void fileWorker::setFilePath(QString _filePath)
{
    filePath = _filePath;
}

void fileWorker::setFilesBSN ()
{
    QFileInfo fileInfo(filePath);
    file_basename = fileInfo.completeBaseName();
    file_suffix = fileInfo.suffix();
    file_name = fileInfo.fileName();
}

QString fileWorker::getErrorBuf()
{
    return errorBuf;
}

QString fileWorker::getOutputDir(){
    return outputDir;
}

quint64 fileWorker::getSizeFile(){
    return QFileInfo(filePath).size();
}
