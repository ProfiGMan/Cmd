#include "cmd.h"
#include "log.h"
#include <QFile>
#include <stdlib.h>
#include <QtGlobal>
#include <QProcess>
#if WIN
#include <windows.h>
//#include <Processthreadsapi.h>
#include <winbase.h>
//#include <TCHAR.H>
#include <w32api.h>
#endif

QPair<int, QString> cmd::exec(QString command) {
    qDebug() << QObject::tr("@|Executing \"%1\"").arg(command);
    QString _output = "";
    QProcess proc;
    bool succes = true, started = true;
    proc.start(command + " 2>&1");
    int _res = 22;
    if(!proc.waitForStarted()) {
        qCritical() << (_output = QObject::tr("Command could not start"));
        succes = false;
        started = false;
    }
    else if(!proc.waitForFinished()) {
        qCritical() << (_output = QObject::tr("Command could not finish"));
        succes = false;
        started = false;
    }
    else if(proc.exitStatus() == QProcess::CrashExit) {
        succes = false;
        qCritical() << (_output = QObject::tr("Application has crashed"));
    }
    if(succes) qDebug() << QObject::tr("Executing ended succesfull");
    else qCritical() << QObject::tr("Executing ended unsuccesfull");

    if(started) {
        QByteArray out;
        _output = ((out = proc.readAllStandardOutput()).isEmpty() ? "" : out.data()) + _output;
        _res = (proc.exitStatus() == QProcess::CrashExit) ? 1 : proc.exitCode();
        qDebug() << _output;
        if(_res) {
            qWarning() << QObject::tr("Returned value is ") << _res;
        }
        else {
            qDebug() << QObject::tr("Returned value is ") << _res;
        }
    }

    return QPair<int, QString>(_res, _output);
}
















