#ifndef FILEWORKER_H
#define FILEWORKER_H

#include <QFile>
#include <QFileDialog>
#include <QRegularExpression>
#include <QDir>


class fileWorker
{
public:
    fileWorker(QString _filePath);
    ~fileWorker();

    bool openFile();
    QString getModifiedFileName();

    void setOverWrite(bool _mode);
    void setOutputDir(QString _path);
    void setFilePath(QString _filePath);
    void setFilesBSN();

    QString getErrorBuf();
    QString getOutputDir();
    quint64 getSizeFile();

    QFile sourceFile;
private:
    bool chechOriginFile(QStringList& list_filenames);
    qulonglong findMaxCounter(QStringList& list_filenames);

    //void addToList(QWidget* widget);

private:
    QString filePath;
    QString file_basename;
    QString file_suffix;
    QString file_name;

    QString outputDir;

    QString errorBuf;
    bool overWrite;
};

#endif // FILEWORKER_H
