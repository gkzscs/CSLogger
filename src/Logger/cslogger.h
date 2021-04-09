#ifndef CSLOGGER_H
#define CSLOGGER_H

#include "cslogger_comdef.hpp"


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

public:
    void log_fatal(const QString &msg);
    void log_error(const QString &msg);
    void log_warn(const QString &msg);
    void log_info(const QString &msg);
    void log_debug(const QString &msg);

    void setLevel(LogLevel lv);
    void setConsole(bool flag);

protected:

};

}   // End of `cslogger`


#endif // CSLOGGER_H
