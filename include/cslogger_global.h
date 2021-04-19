#ifndef CSLOGGER_GLOBAL_H
#define CSLOGGER_GLOBAL_H

#include <QtCore/qglobal.h>


#ifdef CSLOGGER_LIB
#   define CSLOGGER_EXPORT  Q_DECL_EXPORT
#else
#   define CSLOGGER_EXPORT  Q_DECL_IMPORT
#endif


#endif // CSLOGGER_GLOBAL_H
