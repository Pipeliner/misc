#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdint.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int print_file_info(const char *path, const struct stat *st)
{
    //printf("%s %ju\n", path, (uintmax_t) st->st_uid);
    mode_t mode = st->st_mode;
    mode_t file_type = mode & S_IFMT;

    switch (file_type)
    {
        case S_IFREG:
            putchar('-');
            break;
        case S_IFBLK:
            putchar('b');
            break;
        case S_IFCHR:
            putchar('c');
            break;
        case S_IFDIR:
            putchar('d');
            break;
        case S_IFIFO:
            putchar('p');
            break;
        case S_IFLNK:
            putchar('l');
            break;
        case S_IFSOCK:
            putchar('s');
            break;
        default:
            putchar('?');
            break;
    }



#define PUT_RW_BIT(field, field_char) \
    putchar(mode & field ? field_char : '-');

#define PUT_X_BIT(field, set_field, field_char, set_field_char) \
    putchar(mode & set_field ? set_field_char : (mode & field ? field_char : '-'));

    PUT_RW_BIT(S_IRUSR, 'r');
    PUT_RW_BIT(S_IWUSR, 'w');
    PUT_X_BIT(S_IXUSR, S_ISUID, 'x', 'S');

    PUT_RW_BIT(S_IRGRP, 'r');
    PUT_RW_BIT(S_IWGRP, 'w');
    PUT_X_BIT(S_IXGRP, S_ISGID, 'x', 'S');

    PUT_RW_BIT(S_IROTH, 'r');
    PUT_RW_BIT(S_IWOTH, 'w');
    PUT_X_BIT(S_IXOTH, S_ISVTX, 'x', 'T');

    putchar('\t');

    printf("%d\t", st->st_nlink);

    uid_t uid = st->st_uid;
    struct passwd *pw = getpwuid(uid);
    fputs(pw->pw_name, stdout);

    putchar('\t');

    gid_t  gid = st->st_gid;
    struct group *gr = getgrgid(gid);
    fputs(gr->gr_name, stdout);

    putchar('\t');

    printf("%d\t", st->st_size);

    struct tm *mtime = localtime(&st->st_mtime);
    const int MTIME_STRING_LENGTH=200;
    char mtime_string[MTIME_STRING_LENGTH];

    strftime(mtime_string, MTIME_STRING_LENGTH, "%b %e  %Y\t", mtime);
    fputs(mtime_string, stdout);

    puts(path);
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
