#ifndef ERRORCHECKS_H_EWXY1G30
#define ERRORCHECKS_H_EWXY1G30

#define ERROR_CHECK
#define SafeCall(err)	__safeCall(err, __FILE__, __LINE__)


extern void __safeCall (void *err, const char *file, const int line);

#endif /* ERRORCHECKS_H_EWXY1G30 */
