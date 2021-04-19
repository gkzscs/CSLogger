#ifndef CSLOGGER_COMDEF_HPP
#define CSLOGGER_COMDEF_HPP

#include <QObject>
#include <QString>


namespace cslogger
{

static const QString sclogFileNamePattern("yyyy-MM-dd hh:mm:ss");


// Eliminate unused variable warnings
inline void eliminateUnusedWarning()
{
#define EUW(x)  (void)x
    EUW(sclogFileNamePattern);
#undef EUW
}

}   // End of `cslogger`


#endif // CSLOGGER_COMDEF_HPP
