#ifdef LIBRNPCALC_EXPORTS
#define LIBRNPCALC_API __declspec(dllexport)
#else
#define LIBRNPCALC_API __declspec(dllimport)
#endif

LIBRNPCALC_API double calculate(string expr);
extern "C" LIBRNPCALC_API double calculate(const char* expr);