#include <stdbool.h>
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <linux/limits.h>
#include <sys/stat.h>

#include "cfiletree.h"
#include "debug.h"

static
void path_join(char *out, const char *dir, char *name)
{
    size_t dirlen = strlen(dir);

    if (dirlen < 1)
        return;
    strncpy(out, dir, PATH_MAX - 1);
    if (out[dirlen - 1] != '/')
        out[dirlen++] = '/';
    strncpy(out + dirlen, name, PATH_MAX - dirlen);
    DEBUG("[%s]\n", out);
}

static
void print_stat(char *filepath)
{
    struct stat st;

    if (stat(filepath, &st))
        return;
    printf("%s, %zuB\n", filepath, st.st_size);
}

static
void read_entry(struct dirent *entry, const char *dirpath)
{
    bool succeed;
    char filepath[PATH_MAX] = { '\0' };

    if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
        return;
    path_join(filepath, dirpath, entry->d_name);
    if (*filepath == '\0')
        return;
    if (entry->d_type == DT_DIR)
        filetree_traverse(filepath);
    else
        print_stat(filepath);
}

bool filetree_traverse(const char *dirpath)
{
    struct dirent *entry;
    DIR *dir = opendir(dirpath);

    if (dir == NULL)
        return false;
    entry = readdir(dir);
    while (entry != NULL) {
        read_entry(entry, dirpath);
        entry = readdir(dir);
    }
    closedir(dir);
    return true;
}
