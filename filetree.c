#include <stdbool.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include <linux/limits.h>
#include <sys/stat.h>

#include "cfiletree.h"

static
bool filetree_read_dir(
    const char *dir_path,
    struct dirent *entry,
    char *file_path
)
{
    int written;

    if (!strcmp(entry->d_name, "."))
        return true;
    if (!strcmp(entry->d_name, ".."))
        return true;
    written = snprintf(file_path, PATH_MAX, "%s/%s", dir_path, entry->d_name);
    return written != -1;
}

static
void print_stat(char *filepath)
{
    struct stat st;

    if (stat(filepath, &st))
        return;
    printf("-> %zu\n", sizeof(struct stat));
    printf("%s, %zuB\n", filepath, st.st_size);
}

bool filetree_traverse(const char *dir_path)
{
    struct dirent *entry;
    char file_path[PATH_MAX] = { 0 };
    DIR *dir = opendir(dir_path);
    static int count = 0;

    count++;

    if (dir == NULL)
        return false;
    entry = readdir(dir);
    while (entry != NULL) {
        if (!filetree_read_dir(dir_path, entry, file_path)) {
            entry = readdir(dir);
            continue;
        }
        if (entry->d_type == DT_DIR)
            filetree_traverse(file_path);
        else
            print_stat(file_path);
        entry = readdir(dir);
    }
    closedir(dir);
    return true;
}
