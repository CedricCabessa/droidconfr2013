#include "libdroidcon.h"

int main(int argc, char *argv[])
{
    const char *in = "hello droidcon\n";
    char buffer[1024];
    droidcon_putdata(in, strlen(in));
    droidcon_getdata(buffer, 1024);
    printf("%s", buffer);
    droidcon_clear();

    return 0;
}
