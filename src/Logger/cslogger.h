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

#include "cslogger_global.h"
#include "cslogger_comdef.hpp"

#include <QMap>
#include <QFile>
#include <QDir>
#include <QDateTime>


namespace cslogger
{

class CSLOGGER_EXPORT CSLogger
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

    enum LogGenMethod
    {
        CreateTime,
        FileSize
    };

public:
    CSLogger(LogLevel lv = All);
    virtual ~CSLogger();

    bool set_log_file_dir(const QString &strDir);
    void set_log_file_generate_method(LogGenMethod method);
    void set_log_file_generate_interval_time(unsigned minute);
    void set_log_file_generate_max_size(unsigned maxSize);

public:
    virtual void log_fatal(const QString &msg);
    virtual void log_error(const QString &msg);
    virtual void log_warn(const QString &msg);
    virtual void log_info(const QString &msg);
    virtual void log_debug(const QString &msg);
    virtual void log_trace(const QString &msg);

    void set_level(LogLevel lv);
    void set_console(bool flag);

protected:
    bool create_file();
    bool create_file(const QString &fileName);
    bool open_file();
    bool open_file(const QString &url, QIODevice::OpenMode mode = QIODevice::WriteOnly | QIODevice::Append);
    void close_file();

    bool need_create_new_file() const;
    QString generate_new_file_name();
    QString generate_new_file_path();
    QString find_latest_file_name() const;
    QString get_available_file_name();
    QString convert_file_name_2_path(const QString &fileName) const;

    int exists_time() const;

    virtual QString convert_time_2_file_name(const QString &time) const;
    virtual void log_write(const QString &msg, LogLevel lv);

private:
    void init();
    void init_generate_time();

protected:
    bool _showConsole;
    unsigned _maxFileSize;
    unsigned _intervalGenTime;

    LogLevel _logLevel;
    LogGenMethod _genMethod;
    QString _logDir;

    QFile _file;
    QDateTime _genTime;

    static QString _sMsgPattern;
    static QMap<LogLevel, QString> _sMapLevelStr;

};

}   // End of `cslogger`


#endif // CSLOGGER_H
