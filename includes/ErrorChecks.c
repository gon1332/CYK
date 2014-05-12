#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ErrorChecks.h"

/* void __safeCall (void *err,        ..(in). Return value from function call
 *		    const char *file, ..(in). The file in which the call occured
 *		    const int line)   ..(in). The line in the file in which the call occured
 *
 * Checks if everything is ok. If not, it stops the execution.
 */
extern void __safeCall (void *err, const char *file, const int line)
{
#ifdef ERROR_CHECK
	if (NULL == err) {
		char err_msg[60];
		memset(err_msg, '\0', 60);
		sprintf(err_msg, "SafeCall() failed at %s:%i ", file, line);
		perror(err_msg);
		exit(-1);
	}
#endif

	return;
}
