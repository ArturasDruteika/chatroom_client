#include <cstdio>
#include <cstdlib>


void error(const char *msg)
{
    perror(msg);
    exit(0);
}