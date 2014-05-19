#ifndef __ERROR_CHECKS__
#define __ERROR_CHECKS__

#define ERROR_CHECK
#define SafeCall(err)	__safeCall(err, __FILE__, __LINE__)


extern void __safeCall (void *err, const char *file, const int line);

#endif /* __ERROR_CHECKS__ */
