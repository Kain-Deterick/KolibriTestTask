#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qInfo(logInfo()) << "Class - MainWindow, Constructor.";

    ui->setupUi(this);
    ui->surveyTime->setEnabled(false);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::startModifiedFiles);

    connect(ui->periodMode, &QCheckBox::toggled, ui->surveyTime, [this](bool checked){
        ui->surveyTime->setEnabled(checked);
    });

    connect(ui->chooseWorkDir,&QPushButton::clicked, this,  &MainWindow::selectWorkFolder);
    connect(ui->chooseOutputDir,&QPushButton::clicked, this,  &MainWindow::selectSaveFolder);
    connect(ui->Start, &QPushButton::clicked, this, &MainWindow::startModifiedFiles);
    connect(ui->Stop, &QPushButton::clicked, this, &MainWindow::stopModifiedFiles);
    connect(ui->listWidget->model(), &QAbstractItemModel::rowsInserted, ui->listWidget, &QListWidget::scrollToBottom);

    ui->Stop->setVisible(false);
    ui->workDir->setText(QDir::currentPath());

    ui->xorValue->setText("0000000000000000");
    ui->xorValue->setInputMask(">HH.HH.HH.HH.HH.HH.HH.HH");
}

MainWindow::~MainWindow()
{
    qInfo(logInfo()) << "Class - MainWindow, Destructor.";

    delete ui;
}

void MainWindow::selectWorkFolder()
{
    qInfo(logInfo()) << "Class - MainWindow, selectWorkFolder.";

    QString path = QFileDialog::getExistingDirectory(this);
    path.isEmpty() ? ui->workDir->setText(QDir::currentPath()) : ui->workDir->setText(path);
}

void MainWindow::selectSaveFolder()
{
    qInfo(logInfo()) << "Class - MainWindow, selectSaveFolder.";

    QString path = QFileDialog::getExistingDirectory(this);
    ui->outputDir->setText(path);
}

void MainWindow::startModifiedFiles()
{
    qInfo(logInfo()) << "Class - MainWindow, startModifiedFiles.";

    if (!checkOutputDir()) return;
    if (!checkMask()) return;

    QFileInfoList files = getFilesFromMask(ui->workDir->text(), ui->mask->text());
    if (files.isEmpty())
    {
        qInfo(logWarning()) << "Class - MainWindow, startModifiedFiles::files.isEmpty()";
        addToList("Файлы по заданной маске не найдены");
    }
    for (auto& file_info: files)
    {
        modifiedFile(file_info.filePath());
    }

    startTimer();
}

void MainWindow::stopModifiedFiles()
{
    qInfo(logInfo()) << "Class - MainWindow, stopModifiedFiles.";

    timer->stop();
    ui->Start->setVisible(true);
    ui->Stop->setVisible(false);
    setInteractiveWidgets(ui->Setting, true);
}

void MainWindow::setInteractiveWidgets(QWidget* widget, bool interactive)
{
    qInfo(logInfo()) << "Class - MainWindow, setInteractiveWidgets.";

    if (widget){
        QList<QWidget*> children = ui->Setting->findChildren<QWidget*>();
        for (QWidget* child : children)
            child->setAttribute(Qt::WA_TransparentForMouseEvents, !interactive);
    }
}

bool MainWindow::checkOutputDir()
{
    qInfo(logInfo()) << "Class - MainWindow, checkOutputDir.";

    if(ui->outputDir->text().isEmpty())
    {
        qInfo(logWarning()) << "Class - MainWindow, checkOutputDir::(files.isEmpty(Путь для сохранения файлов не выбран))";
        QMessageBox::warning(this, "Ошибка", "Путь для сохранения файлов не выбран");
        return false;
    }
    return true;
}

bool MainWindow::checkMask()
{
    qInfo(logInfo()) << "Class - MainWindow, checkMask.";

    QString xor_key = ui->xorValue->text().replace(".", "");
    size_t count_point = (ui->xorValue->maxLength())- (ui->xorValue->text().count("."));
    if (xor_key.size() != count_point)
    {
        qInfo(logWarning()) << "Class - MainWindow, checkMask::XOR";
        QMessageBox::warning(this, "Ошибка", "Значение XOR должно иметь " + QString::number(count_point) + " символов");
        return false;
    }
    return true;
}

QFileInfoList MainWindow::getFilesFromMask(QString dir_path, QString mask)
{
    qInfo(logInfo()) << "Class - MainWindow, getFilesFromMask";
    QDir dir(dir_path);
    QStringList list_mask = ui->mask->text().split(',');
    for (QString &maskValue: list_mask){
        maskValue = maskValue.trimmed();
        if (maskValue.startsWith("."))
            maskValue = '*' + maskValue;
    }
    dir.setNameFilters(list_mask);
    return dir.entryInfoList(QDir::Files);
}

void MainWindow::modifiedFile(const QString filePath)
{
    qInfo(logInfo()) << "Class - MainWindow, modifiedFile";

    CreateWidget(filePath);

    ShifrFile* modified_file = new ShifrFile(filePath);
    modified_file->setOutputDir(ui->outputDir->text());
    modified_file->setOverwrite(ui->overWriteValue->isChecked());
    modified_file->setXorKey(ui->xorValue->text());


    QThread* thread = new QThread(this);
    modified_file->moveToThread(thread);

    connect(thread, &QThread::started, modified_file, &ShifrFile::workWithFile);
    connect(modified_file, &ShifrFile::progressByte, this, &MainWindow::updateProgress);
    connect(modified_file, &ShifrFile::fileFinished, this, &MainWindow::modifiedFinished);
    connect(modified_file, &ShifrFile::fileFinished, thread, &QThread::quit);
    connect(modified_file, &ShifrFile::fileFinished, modified_file, &ShifrFile::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    thread->start();

}

void MainWindow::CreateWidget(const QString filepath)
{
    qInfo(logInfo()) << "Class - MainWindow, CreateWidget";
    if (file_widgets.contains(filepath)) {
        qInfo(logWarning()) << "Class - MainWindow,  CreateWidget::(Уже обрабатывается!)";
        addToList(filepath + ": Уже обрабатывается!", QColor(255, 165, 0, 40));
        return;
    }
    QWidget* widget = loadUI(":/fileProgress.ui");
    if (!widget)
    {
        qInfo(logWarning()) << "Class - MainWindow,  CreateWidget::(!widget)";
        return;
    }
    addToList(widget);

    file_widgets[filepath] = widget;
    widget->findChild<QLabel*>("L_filePath")->setText(filepath);
    widget->findChild<QLabel*>("L_Size")->setText(QString::number(QFileInfo(filepath).size()));
    widget->findChild<QLabel*>("L_Result")->setText("В обработке...");
}

void MainWindow::updateProgress(QString file_path, quint64 byte){
    if (file_widgets.contains(file_path)) {
        QWidget *widget = file_widgets[file_path];
        int size = widget->findChild<QLabel*>("L_Size")->text().toInt(),
            cur_size = widget->findChild<QLabel*>("L_ProcessSize")->text().toInt(),
            value = (cur_size + byte) * 100 / size;
        widget->findChild<QProgressBar*>("progressBar")->setValue(value);
        widget->findChild<QLabel*>("L_ProcessSize")->setText(QString::number(cur_size + byte));
    }
}

void MainWindow::modifiedFinished(QString file_path, QString new_file_path, QString error){
    qInfo(logInfo()) << "Class - MainWindow, modifiedFinished";

    if (file_widgets.contains(file_path)) {
        QWidget *widget = file_widgets[file_path];
        if (error.isEmpty())
        {
            widget->findChild<QLabel*>("L_Result")->setText("Успешно сохранено \"" + new_file_path + "\"");
            widget->findChild<QProgressBar*>("progressBar")->setValue(100);
        }
        else
            widget->findChild<QLabel*>("L_Result")->setText(error);
        file_widgets.remove(file_path);

        if (ui->fileDeleteValue->isChecked()){
            QFile file(file_path);
            bool flag_remove = file.remove();
            if (!flag_remove)
                addToList(file_path + ": « Файл не может быть удален »", QColor(255, 0, 0, 40));
            addToList(file_path + ": « Файл успешно удален »", QColor(0, 255, 0, 40));
        }
    }
}

void MainWindow::startTimer()
{
    qInfo(logInfo()) << "Class - MainWindow, startTimer";

    if (ui->periodMode->isChecked() && !timer->isActive()){
        timer->start(ui->surveyTime->value());
        ui->Start->setVisible(false);
        ui->Stop->setVisible(true);
        setInteractiveWidgets(ui->Setting, false);
    }
}

void MainWindow::addToList(QString text, QColor color_row, QColor color_text){
    qInfo(logInfo()) << "Class - MainWindow, addToList(Text)";

    ui->listWidget->addItem(text);
    QListWidgetItem *item = ui->listWidget->item(ui->listWidget->count() - 1);
    item->setForeground(QBrush(color_text));
    //item->setBackground(QBrush(color_row));
}

void MainWindow::addToList(QWidget *widget){
    qInfo(logInfo()) << "Class - MainWindow, addToList(QWidget)";

    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
    item->setSizeHint(widget->sizeHint());
    ui->listWidget->setItemWidget(item, widget);
}

QWidget* MainWindow::loadUI(QString file_path){
    QFile ui_file(file_path);
    QWidget* widget = ui_load.load(&ui_file, this);
    return widget;
}








