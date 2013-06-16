#ifndef __DROIDCON__
#define __DROIDCON__

#include <sys/types.h>

ssize_t droidcon_getdata(void *buf, size_t count);

ssize_t droidcon_putdata(const void *buf, size_t count);

void droidcon_clear(void);

#endif /* __DROIDCON__ */
