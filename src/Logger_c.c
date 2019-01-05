#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>

#define BUF_SIZE 256

char* logger_c_get_date()
{
    time_t now;
    struct tm *currentTime;
    static char result[BUF_SIZE];

    now = time(NULL);
    currentTime = localtime(&now);
    sprintf(result, "%i.%02i.%02i %02i:%02i:%02i",  // setting time as YYYY.MM.DD HH:MM:SS
            currentTime->tm_year + 1900,
            currentTime->tm_mon + 1,
            currentTime->tm_mday,
            currentTime->tm_hour,
            currentTime->tm_min,
            currentTime->tm_sec);
    return result;
}

char* logger_c_get_path()
{
    static char result[PATH_MAX];
    char *path_pointer;
    path_pointer = getcwd(result, PATH_MAX); // get current path

    if (path_pointer!=NULL)
    {
        free (path_pointer);    // do not need this anymore
        return result;
    }

    return NULL;
}
