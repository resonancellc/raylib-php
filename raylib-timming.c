/* If defined, the following flags inhibit definition of the indicated items.*/
#define NOGDICAPMASKS     // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOVIRTUALKEYCODES // VK_*
#define NOWINMESSAGES     // WM_*, EM_*, LB_*, CB_*
#define NOWINSTYLES       // WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
#define NOSYSMETRICS      // SM_*
#define NOMENUS           // MF_*
#define NOICONS           // IDI_*
#define NOKEYSTATES       // MK_*
#define NOSYSCOMMANDS     // SC_*
#define NORASTEROPS       // Binary and Tertiary raster ops
#define NOSHOWWINDOW      // SW_*
#define OEMRESOURCE       // OEM Resource values
#define NOATOM            // Atom Manager routines
#define NOCLIPBOARD       // Clipboard routines
#define NOCOLOR           // Screen colors
#define NOCTLMGR          // Control and Dialog routines
#define NODRAWTEXT        // DrawText() and DT_*
#define NOGDI             // All GDI defines and routines
#define NOKERNEL          // All KERNEL defines and routines
#define NOUSER            // All USER defines and routines
/*#define NONLS             // All NLS defines and routines*/
#define NOMB              // MB_* and MessageBox()
#define NOMEMMGR          // GMEM_*, LMEM_*, GHND, LHND, associated routines
#define NOMETAFILE        // typedef METAFILEPICT
#define NOMINMAX          // Macros min(a,b) and max(a,b)
#define NOMSG             // typedef MSG and associated routines
#define NOOPENFILE        // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL          // SB_* and scrolling routines
#define NOSERVICE         // All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND           // Sound driver routines
#define NOTEXTMETRIC      // typedef TEXTMETRIC and associated routines
#define NOWH              // SetWindowsHook and WH_*
#define NOWINOFFSETS      // GWL_*, GCL_*, associated routines
#define NOCOMM            // COMM driver routines
#define NOKANJI           // Kanji support stuff.
#define NOHELP            // Help engine interface.
#define NOPROFILER        // Profiler interface.
#define NODEFERWINDOWPOS  // DeferWindowPos routines
#define NOMCX             // Modem Configuration Extensions

/* Type required before windows.h inclusion  */
typedef struct tagMSG *LPMSG;

#include "php.h"

#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_DEBUG

#include "raylib.h"
#include "raylib-timming.h"
#include "raylib-utils.h"


//------------------------------------------------------------------------------------------------------
//-- raylib Timming PHP Custom Object
//------------------------------------------------------------------------------------------------------
zend_object_handlers php_raylib_timming_object_handlers;

void php_raylib_timming_free_storage(zend_object *object TSRMLS_DC)
{
    php_raylib_timming_object *intern = php_raylib_timming_fetch_object(object);

    zend_object_std_dtor(&intern->std);
}

zend_object * php_raylib_timming_new(zend_class_entry *ce TSRMLS_DC)
{
    php_raylib_timming_object *intern;
    intern = (php_raylib_timming_object*) ecalloc(1, sizeof(php_raylib_timming_object) + zend_object_properties_size(ce));

    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    object_properties_init(&intern->std, ce);

    intern->std.handlers = &php_raylib_timming_object_handlers;

    return &intern->std;
}

PHP_METHOD(Timming, __construct)
{
    zend_string *fileName;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_STR(fileName)
    ZEND_PARSE_PARAMETERS_END();

    php_raylib_timming_object *intern = Z_TIMMING_OBJ_P(ZEND_THIS);
}

//void SetTargetFPS(int fps);
PHP_METHOD(Timming, setTargetFPS)
{
    zend_long fps;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(fps)
    ZEND_PARSE_PARAMETERS_END();

    SetTargetFPS(zend_long_2int(fps));
}

//int GetFPS(void);
PHP_METHOD(Timming, getFps)
{
    RETURN_LONG(GetFPS());
}

//float GetFrameTime(void);
PHP_METHOD(Timming, getFrameTime)
{
    RETURN_DOUBLE(GetFrameTime());
}

//double GetTime(void);
PHP_METHOD(Timming, getTime)
{
    RETURN_DOUBLE(GetTime());
}

const zend_function_entry php_raylib_timming_methods[] = {
        PHP_ME(Timming, __construct, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(Timming, setTargetFPS, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Timming, getFps, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Timming, getFrameTime, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(Timming, getTime, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

void php_raylib_timming_startup(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "raylib", "Timming", php_raylib_timming_methods);
    php_raylib_timming_ce = zend_register_internal_class(&ce TSRMLS_CC);
    php_raylib_timming_ce->create_object = php_raylib_timming_new;

    memcpy(&php_raylib_timming_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    php_raylib_timming_object_handlers.offset = XtOffsetOf(php_raylib_timming_object, std);
    php_raylib_timming_object_handlers.free_obj = &php_raylib_timming_free_storage;
    php_raylib_timming_object_handlers.clone_obj = NULL;
}