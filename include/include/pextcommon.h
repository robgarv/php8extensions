#ifndef _PEXTCOMMON_H
#define _PEXTCOMMON_H

#include <iostream>
#include <fstream>
#include <sstream>

// commonly used definitions and macros

// GDB_BLOCK Macro
#define GDB_BLOCK \
{ \
  std::ostringstream _ssfilename; \
  _ssfilename << getenv( "HOME" ) << "/tmp/gdb.block"; \
  struct stat _gdbstat; \
  int updatepid = 1; \
  while ( stat( _ssfilename.str().c_str(), &_gdbstat ) == 0 ) \
  { \
    if ( updatepid ) \
    { \
      std::ofstream blockfile; \
      blockfile.open(_ssfilename.str().c_str() ); \
      blockfile << getpid() << "\n"; \
      blockfile.close(); \
      updatepid = 0; \
    } \
    sleep( 1 ); \
  } \
}

// Some console output support
#define _USE_STDOUT
#ifdef _USE_STDOUT
    #define _PRINTIT( __label, _x_msg_stream ) \
    do { \
        std::cout << __label << "(S): " << _x_msg_stream.str() << std::endl; \
    } while( 0 )
#else
    #define _PRINTIT( __label, _x_msg_stream ) \
    do { \
        php_printf( __label << "(P): %s", _x_msg_stream.str().c_str()); \
    } while( 0 )
#endif

#define WARNS( _Expression ) \
do { \
  std::ostringstream __x_Msg; \
  __x_Msg << _Expression; \
  _PRINTIT( "WARNING", __x_Msg ); \
} while( 0 )


#define STATUS( _Expression ) \
do { \
  std::ostringstream __x_Msg; \
  __x_Msg << _Expression; \
  _PRINTIT( "STATUS", __x_Msg ); \
} while( 0 )


#endif
