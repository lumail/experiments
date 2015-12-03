#include <stdio.h>
#include <magic.h>

int main(int argc, char *argv[])
{
    int i;
    magic_t magic_cookie;
    magic_cookie = magic_open(MAGIC_MIME_TYPE);

    /*
     * Open library.
     */
    if (magic_cookie == NULL)
    {
        printf("unable to initialize magic library\n");
        return -1;
    }

    /*
     * Load the default database.
     */
    if (magic_load(magic_cookie, NULL) != 0)
    {
        printf("cannot load magic database - %s\n", magic_error(magic_cookie));
        magic_close(magic_cookie);
        return 1;
    }

    /*
     * Show MIME type of each file on the command line.
     */
    for (i = 1 ; i < argc ; i++)
    {
        const char *magic_full;
        magic_full = magic_file(magic_cookie, argv[i]);
        printf("%s\n", magic_full);
    }

    /*
     * All done.
     */
    magic_close(magic_cookie);
    return 0;
}
