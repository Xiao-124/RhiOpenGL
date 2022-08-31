#pragma once

#include <QtCore/qglobal.h>
#ifdef  _GLEW_USE
#include <GL/glew.h>
#else 
#include <qopenglfunctions.h>
#include <qopenglcontext.h>
#include <qopenglfunctions_4_5_core.h>
#include <qopenglfunctions_4_5_compatibility.h>
#include <qopenglextrafunctions.h>
#include <qopenglwindow.h>
#endif // ! _GLEW_USE



#ifndef BUILD_STATIC
# if defined(RHIOPENGL_LIB)
#  define RHI_EXPORT Q_DECL_EXPORT
# else
#  define RHI_EXPORT Q_DECL_IMPORT
# endif
#else
# define RHI_EXPORT
#endif
