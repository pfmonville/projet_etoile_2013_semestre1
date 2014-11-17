#ifndef PLATFORM_H_INCLUDED
#define LATFORM_H_INCLUDED

/**@todo Remove useless lines, check if warning should be error, or remove the "try to compile" policy
   @todo Test it on lot of platform in order to be sure all works as expected.
   @todo Should try to add macros for "forceinline" for example.
   @todo Add "restrict" keyword **/
///@note Early version, do not rely on it too much !

#define GCC_COMPILER     1
#define MVSC_COMPILER    2
#define ICC_COMPILER     3
#define BORLAND_COMPILER 4

#define LINUX   1
#define WINDOWS 2
#define MAC     3

#define UNKOWN "unknown"

/*#if defined( __STDC__ ) && !defined( __cplusplus )
#   error "This project require a C++ compiler !"
#endif
#if defined( __cplusplus ) && ( __cplusplus == 199711L )
#   warning "This project require a C++11 compliant compiler in order to build properly, error may occure.\
             If your compiler support C++11, please turn C++11 support option on !"
#   define DAWN_SUPORT = PARTIAL // Necessary ?
#else
#   define DAWN_SUPPORT = FULL
#endif
*/

#if defined( __GNUC__ ) || defined( __MINGW__ )
#   define FUNCTION __PRETTY_FUNCTION__
#   if defined( __MINGW__ )
#       define COMPILER_NAME "MinGW"
#   else
#       define COMPILER_NAME "gcc"
#   endif
#   define COMPILER GCC_COMPILER
#   if defined( __GNUC_PATCHLEVEL__ )
#       define COMPILER_VERSION ( __GNUC__ * 10000 \
                                     + __GNUC_MINOR__ * 100 \
                                     + __GNUC_PATCHLEVEL__ )
#   else
#       define COMPILER_VERSION ( __GNUC__ * 10000 \
                                     + __GNUC__ * 100 )
#   endif
#   if( DAWN_VERSION < 40500 )
#       define DEPRECATED(msg) __attribute__( ( deprecated ) )
#   else
#       define DEPRECATED(msg) __attribute__( ( deprecated(msg) ) )
#   endif
#elif defined( _MSC_VER )
#   define FUNCTION __FUNCSIG__
#   define COMPILE_NAME "Microsoft compiler"
#   define COMPILER MVSC_COMPILER
#   if( ( _MSC_VER <= 1200 ) )
#       define COMPILER_VERSION _MSC_VER
#   else
#       define COMPILER_VERSION _MSC_FULL_VER
#   endif
#   define DEPRECATED(msg) __delcspec( deprecated(msg) )
#elif defined( __BORLANDC__ )
#   define FUNCTION __FUNC__
#   define COMPILER_NAME "Borland"
#   define COMPILER BORLAND_COMPILER
#   define COMPILER_VERSION __BORLANDC__
#   define DEPRECATED(t)
#elif defined( __INTEL_COMPILER ) || defined( __ICL )
#   define FUNCTION __PRETTY_FUNCTION__
#   define COMPILER_NAME "Intel compiler"
#   define COMPILER ICC_COMPILER
#   define COMPILER_VERSION __INTEL_COMPILER
#   define DEPRECATED(msg) __attribute__( ( deprecated ) )
#else
#   warning "Unknown compiler, there might be some troubles during compilation"
#   ifdef( __func__ ) // standard since C++ 11 but compiler may not support it
#       define FUNCTION __func__
#   else
#       warning "Compiler is not AINSI C99 standard, can't use __func__. Some debug functions will be disabled"
#   endif
#   define COMPILER_NAME UNKNWON
#   define COMPILER UNKNOWN
#   define COMPILER_VERSION UNKNOWN
#   warning "Compiler not recongnized, results may be unexpected"
#   define DEPRECATED(t)
#endif

#if defined( __gnu_linux__ ) || defined( __linux__ )
#   define OS_NAME "Linux"
#   define OS LINUX
#elif defined( macintosh ) || defined( Macintosh ) || ( defined( __APPLE__ ) && defined( __MACH__ ) )
#   define OS_NAME "Mac"
#   define OS MAC
#elif defined( _WIN32 )
#   define OS_NAME "Windows"
#   define OS WINDOWS
#else
#   define OS_NAME UNKNOWN
#   define OS UNKNOWN
#   warning "Operating system not recognized. Unexpected results might happen"
#endif

#if( OS == LINUX || OS == MAC ) && \
    COMPILER_VERSION >= 4000 && \
    ( COMPILER == ICC_COMPILER || DAWN_COMPILER == GCC_COMPILER )
#       define EXPORT __attribute__( ( visibility( "default" ) ) )
#       define IMPORT __attribute__( ( visibility( "default" ) ) )
#       define LOCAL __attribute__( ( visibility( "hiddent" ) ) )
#elif( OS == WINDOWS )
#   define EXPORT __declspec( dllexport )
#   define IMPORT __declspec( dllimport )
#   define LOCAL
#else
#   define EXPORT
#   define IMPORT
#   define LOCAL
#endif

#if !defined( BUILD_STATIC ) && !defined( IMPORT_LIBRARY )
#   define API EXPORT
#elif defined( IMPORT_LIBRARY )
#   define API IMPORT
#else
#   define DAWN_API
#endif

#if defined( __amd64__ ) || defined( __x86_64__ ) || defined( _M_X64__ ) || defined( _M_AMD64) || \
    defined( _ia64__ ) || defined( _M_IA64 ) || defined( __itanium__ )
#   define PLATFORM_X64
#else
#   define PLATFORM_X86
#endif


#endif // PLATFORM_H_INCLUDED
