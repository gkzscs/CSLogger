#ifndef CSMARKDOWNLOGGER_H
#define CSMARKDOWNLOGGER_H

#include "Logger/cslogger.h"


namespace cslogger
{

class CSMarkdownLogger : public CSLogger
{
public:
    using CSLogger::CSLogger;

public:
    void log_fatal(const QString &msg) override;
    void log_error(const QString &msg) override;
    void log_warn(const QString &msg) override;
    void log_info(const QString &msg) override;
    void log_debug(const QString &msg) override;
    void log_trace(const QString &msg) override;

protected:
    QString convert_time_2_file_name(const QString &time) const override;
    void log_write(const QString &msg, LogLevel lv) override;

};

}   // `cslogger`

#endif // CSMARKDOWNLOGGER_H
