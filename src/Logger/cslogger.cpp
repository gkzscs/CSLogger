#pragma execution_character_set("utf-8")
#include "cslogger.h"


namespace cslogger
{
/******************************************** Macros **********************************************/


/************************************ Static variables **********************************************/
QString CSLogger::_sMsgPattern("【%1】%2 (`%3` at line: %4)\r\n");
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

void CSLogger::set_log_file_generate_interval_time(unsigned minute)
{
    _intervalGenTime = minute;
}

void CSLogger::set_log_file_generate_max_size(unsigned maxSize)
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

bool CSLogger::create_file()
{
    bool res = need_create_new_file();
    if (!res) return res;

    // Create new log file
    auto fileName = generate_new_file_name();
    res = create_file(fileName);

    return res;
}

bool CSLogger::create_file(const QString &fileName)
{
    // Make path before creating file
    QDir dir;
    auto res = dir.mkpath(_logDir);
    if (!res) return res;

    // Create file
    auto filePath = convert_file_name_2_path(fileName);

    QFile file(filePath);
    res =  file.open(QIODevice::NewOnly);
    file.close();

    return res;
}

bool CSLogger::open_file()
{
    // Check if the file is open
    auto res = need_create_new_file();
    if (!res && _file.isOpen()) return true;

    // Get available file path and open the file
    auto fileName = get_available_file_name();
    auto filePath = convert_file_name_2_path(fileName);

    // Create new file if needed
    if (res) create_file(filePath);

    return open_file(filePath, QIODevice::WriteOnly | QIODevice::Append);
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
        if (existTime >= static_cast<int>(_intervalGenTime*60)) res = true;
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

QString CSLogger::generate_new_file_name()
{
    // Assign to `_genTime` by its interface
    _genTime.setSecsSinceEpoch(QDateTime::currentSecsSinceEpoch());
    auto strTime = _genTime.toString(sclogFileNamePattern);

    return convert_time_2_file_name(strTime);
}

QString CSLogger::generate_new_file_path()
{
    auto fileName = generate_new_file_name();
    return (_logDir + "/" + fileName);
}

QString CSLogger::find_latest_file_name() const
{
    QDir dir(_logDir);
    auto listFile = dir.entryList(QDir::NoFilter, QDir::Time);

    if (listFile.isEmpty()) return nullptr;
    return listFile.last();
}

QString CSLogger::convert_time_2_file_name(const QString &time) const
{
    static const QString suffix = ".txt";
    QString fileName = QString("%1%2").arg(time).arg(suffix);

    return fileName;
}

/**
 * @brief get current available log file's name, this file must be latest and not out of date
 * @return available latest file name
 */
QString CSLogger::get_available_file_name()
{
    bool res = need_create_new_file();
    if (!res)
    {
        return find_latest_file_name();
    }

    return generate_new_file_name();
}

QString CSLogger::convert_file_name_2_path(const QString &fileName) const
{
    auto filePath = _logDir + "/" +fileName;
    return filePath;
}

/**
 * @brief calculate the seconds that current log file exists
 * @return existed seconds
 */
int CSLogger::exists_time() const
{
    auto now = QDateTime::currentSecsSinceEpoch();
    auto last = _genTime.toSecsSinceEpoch();
    auto intervalSec = static_cast<int>(now - last);

    return intervalSec;
}

/**
 * @brief the most important code that used for writting log
 * @param [msg] message to be written into log file
 * @param [lv] log level
 */
void CSLogger::log_write(const QString &msg, LogLevel lv)
{
    if (_logLevel < lv) return;

    // Auto open log file
    auto res = open_file();
    if (!res)
    {
        auto error = _file.errorString();
        throw _file.errorString();
    }

    // Assemble message string
    auto strLevel = _sMapLevelStr.value(lv);
    QString totalMsg = _sMsgPattern.arg(strLevel).arg(msg).arg(__FILE__).arg(__LINE__);

    // Write to file immediately
    qint64 n = _file.write(totalMsg.toUtf8());
    _file.flush();

    if (n == -1) throw "Error occurred while writting to file:" + _file.fileName();
}

void CSLogger::init()
{
    // Assign to container
    if (_sMapLevelStr.isEmpty())
    {
        QStringList listStr;
        listStr << "OFF" << "FATAL" << "ERROR" << "WARN" << "INFO" << "DEBUG" << "TRACE" << "ALL";

        assert(listStr.size() == All+1);

        for (int i = 0, n = listStr.size(); i < n; ++i)
        {
            auto level = static_cast<LogLevel>(i);
            _sMapLevelStr.insert(level, listStr.at(i));
        }
    }

    // Basic settings
    set_log_file_dir("./cslog");
    set_log_file_generate_method(CreateTime);
    set_log_file_generate_interval_time(1);
    set_log_file_generate_max_size(1024);
    set_level(_logLevel);
    set_console(false);

    // Initialize generate time
    init_generate_time();
}

void CSLogger::init_generate_time()
{
    // Initialize `_genTime` with earlier time
    auto fileName = find_latest_file_name();
    if (fileName.isEmpty())
    {
        _genTime.setSecsSinceEpoch(QDateTime::currentSecsSinceEpoch() - _intervalGenTime);
        return;
    }

    // If exists file, then get latest file created time
    auto filePath = convert_file_name_2_path(fileName);

    QFileInfo fileInfo(filePath);
    _genTime = fileInfo.created();
}

}   // `csloggger`
