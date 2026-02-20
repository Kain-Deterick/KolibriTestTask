#include "mainwindow.h"

#include <QApplication>

QScopedPointer<QFile>   m_logFile;

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qInstallMessageHandler(messageHandler);

    MainWindow w;
    w.show();
    return a.exec();
}


void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString nameFile = qApp->applicationDirPath() + "/server_log.log";

    m_logFile.reset(new QFile(nameFile));

    m_logFile.data()->open(QFile::Append | QFile::Text);

    QTextStream out(m_logFile.data());

    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");

    switch (type)
    {
    case QtInfoMsg:     out << "INF "; break;
    case QtDebugMsg:    out << "DBG "; break;
    case QtWarningMsg:  out << "WRN "; break;
    case QtCriticalMsg: out << "CRT "; break;
    case QtFatalMsg:    out << "FTL "; break;
    }

    out << context.category << ": " << msg << "\n";
    out.flush();    // Очищаем буферизированные данные
}
