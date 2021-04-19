#ifndef CSLOGGER_H
#define CSLOGGER_H

/***********************************************************************************************
 * @author: cs
 * @date: 2021-4-19
 * @brief:
 * contains below functions:
 * - multiple threads
 * - multiple file type
 * - custom log level
***********************************************************************************************/

#include "cslogger_comdef.hpp"

#include <QMap>
#include <QFile>
#include <QDir>


namespace cslogger
{

class CSLogger
{
public:
    enum LogLevel
    {
        Off,
        Fatal,
        Error,
        Warn,
        Information,
        Debug,
        Trace,
        All
    };

public:
    CSLogger(LogLevel lv = All);

    bool set_log_file_dir(const QString &strDir);

public:
    void log_fatal(const QString &msg);
    void log_error(const QString &msg);
    void log_warn(const QString &msg);
    void log_info(const QString &msg);
    void log_debug(const QString &msg);
    void log_trace(const QString &msg);

    void set_level(LogLevel lv);
    void set_console(bool flag);

protected:
    bool create_file(const QString &url);
    bool open_file();
    bool open_file(const QString &url, QIODevice::OpenMode mode = QIODevice::WriteOnly | QIODevice::Append);
    void log_write(const QString &msg, LogLevel lv);

private:
    void init();

protected:
    bool _showConsole;
    LogLevel _logLevel;
    QString _logDir;

    QFile _file;

    static QString _sMsgPattern;
    static QMap<LogLevel, QString> _sMapLevelStr;

};

}   // End of `cslogger`


#endif // CSLOGGER_H
