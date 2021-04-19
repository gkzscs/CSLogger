#include "cslogger.h"


namespace cslogger
{
/******************************************** Macros **********************************************/


/************************************ Static variables **********************************************/
QString CSLogger::_sMsgPattern("【%1】%2 (`%3` at line: %3)");
QMap<CSLogger::LogLevel, QString> CSLogger::_sMapLevelStr;


CSLogger::CSLogger(LogLevel lv)
    : _logLevel(lv)
{
    init();
}

bool CSLogger::set_log_file_dir(const QString &strDir)
{
    _logDir = strDir;

    QDir dir;
    return dir.mkdir(strDir);
}

void CSLogger::set_log_file_generate_method(LogGenMethod method)
{
    _genMethod = method;
}

void CSLogger::set_log_file_generate_interval_time(int minute)
{
    _intervalGenTime = minute;
}

void CSLogger::set_log_file_generate_max_size(int maxSize)
{
    _maxFileSize = maxSize;
}

void CSLogger::log_fatal(const QString &msg)
{
    log_write(msg, Fatal);
}

void CSLogger::log_error(const QString &msg)
{
    log_write(msg, Error);
}

void CSLogger::log_warn(const QString &msg)
{
    log_write(msg, Warn);
}

void CSLogger::log_info(const QString &msg)
{
    log_write(msg, Information);
}

void CSLogger::log_debug(const QString &msg)
{
    log_write(msg, Debug);
}

void CSLogger::log_trace(const QString &msg)
{
    log_write(msg, Trace);
}

void CSLogger::set_level(LogLevel lv)
{
    _logLevel = lv;
}

void CSLogger::set_console(bool flag)
{
    _showConsole = flag;
}

bool CSLogger::create_file(const QString &url)
{
    QDir dir;
    return dir.mkpath(url);
}

bool CSLogger::open_file()
{
    if (_file.isOpen()) return true;

    return _file.open(QIODevice::WriteOnly | QIODevice::Append);
}

bool CSLogger::open_file(const QString &url, QIODevice::OpenMode mode)
{
    _file.setFileName(url);
    if (_file.isOpen()) return true;

    return _file.open(mode);
}

void CSLogger::close_file()
{
    _file.close();
}

bool CSLogger::need_create_new_file() const
{
    bool res = false;

    switch (_genMethod)
    {
    case CreateTime:
    {
        auto existTime = exists_time();
        if (existTime >= _intervalGenTime) res = true;
        break;
    }
    case FileSize:
    {
        auto fileSize = _file.size();
        if (fileSize >= _maxFileSize) res = true;
        break;
    }
    }

    return res;
}

bool CSLogger::auto_create_file()
{
    bool res = need_create_new_file();

    // Create log file
    // To do

    return res;
}

QString CSLogger::generate_new_file_name() const
{
    // Assign to `_genTime` by its interface
    _genTime.fromTime_t(QDateTime::currentDateTime().toTime_t());

    auto fileName = _genTime.toString(sclogFileNamePattern);
    return fileName;
}

/**
 * @brief calculate the seconds that current log file exists
 * @return existed seconds
 */
int CSLogger::exists_time() const
{
    auto now = QDateTime::currentDateTime().toTime_t();
    auto last = _genTime.toTime_t();
    auto intervalSec = static_cast<int>(now - last);

    return intervalSec;
}

void CSLogger::log_write(const QString &msg, LogLevel lv)
{
    if (_logLevel < lv) return;

    // Open file
    if (!open_file()) return;

    auto strLevel = _sMapLevelStr.value(lv);
    QString totalMsg = _sMsgPattern.arg(strLevel).arg(msg).arg(__FILE__).arg(__LINE__);

    // Write to file
    auto res = _file.write(totalMsg.toUtf8());
    if (res == -1) throw "Error occurred while writting to file:" + _file.fileName();
}

void CSLogger::init()
{
    // Assign to container
    if (_sMapLevelStr.isEmpty())
    {
        QStringList listStr;
        listStr << "OFF" << "FATAL" << "ERROR" << "WARN" << "INFO" << "DEBUG" << "TRACE" << "ALL";

        assert(listStr.size() == All-1);

        for (int i = 0, n = listStr.size(); i < n; ++i)
        {
            auto level = static_cast<LogLevel>(i);
            _sMapLevelStr.insert(level, listStr.at(i));
        }
    }

    // Basic settings
    set_level(_logLevel);
    set_console(false);
}

}   // `csloggger`
