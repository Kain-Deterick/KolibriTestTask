#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDataStream>
#include <QMessageBox>
#include <QScrollBar>
#include <QListView>
#include <QTimer>
#include <QFile>
#include <QUiLoader>
#include <QDir>
#include <QThread>
#include <QProgressBar>
#include "shifrfile.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startModifiedFiles();
    void stopModifiedFiles();
    void selectSaveFolder();
    void selectWorkFolder();
    void updateProgress(QString file_path, quint64 byte);
    void modifiedFinished(QString file_path, QString new_file_path, QString error);

private:
    bool checkOutputDir();
    bool checkMask();
    bool checkFiles;
    void setInteractiveWidgets(QWidget* wiget, bool interactive);
    void modifiedFile(const QString _filePath);
    void startTimer();
    void CreateWidget(const QString filepath);
    void addToList(QString text, QColor color_row = Qt::white, QColor color_text = Qt::black);
    void addToList(QWidget* widget);
    QFileInfoList getFilesFromMask(QString dir_path, QString mask);
    QWidget* loadUI(QString file_path);

private:
    bool overwrite;
    bool fileDelite;
    QUiLoader ui_load;
    QTimer *timer;
    QMap<QString, QWidget*> file_widgets;
    Ui::MainWindow *ui;    
};
#endif // MAINWINDOW_H
