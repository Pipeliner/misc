#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdint.h>

int print_file_info(const char *path, const struct stat *st)
{
    printf("%s %ju\n", path, (uintmax_t) st->st_uid);
}

int list_directory(const char *directory_name) {
    DIR *dp;
    struct dirent *ep;
    struct stat st;

    dp = opendir(directory_name);
    if (dp != NULL)
    {
        while (ep = readdir(dp))
        {

            if (stat(ep->d_name, &st))
            {
                perror("stat error!");
            }
            print_file_info(ep->d_name, &st);
        }

        closedir(dp);
    }
    else
        perror ("Couldn't open the directory");

    return 0;
}

int main (void)
{
    list_directory(".");

}
