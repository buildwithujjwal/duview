#include <stdio.h>    // Standard I/O functions
#include <string.h>   // strcmp() for comparing entry names
#include <dirent.h>   // Directory handling functions and structures
#include <sys/stat.h> // stat() and struct stat for file metadata

// Recusively calculates teh total size (in bytes) of a directory, including every file in nested subdirectory.
long long calculate_size(const char *path) {

    long long total = 0;
    
    DIR *dir = opendir(path);

    // if cant open it, treat its contribution 0.
    if (dir == NULL) {
        return 0;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {

        // Skip "current directory" and "parent directory" entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Build the full path for this entry
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat info;

        // skip if cant read metadata for
        if (stat(full_path, &info) != 0) {
            continue;
        }

        // Directory: recurse into it, add whatever it totals to | File: add its size directly
        if(S_ISDIR(info.st_mode)) {
            total += calculate_size(full_path);
        }
        else {
            total += info.st_size;
        }
    }

    closedir(dir);
    return total;
}

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";

    long long size = calculate_size(path);

    if(strcmp(path, ".") == 0) {
        printf("Total size of Current directory: %lld bytes\n", size);
    }
    else {
        printf("Total size of %s: %lld bytes\n", path, size);
    }

    return 0;
}