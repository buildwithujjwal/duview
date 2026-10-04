#include <stdio.h>  // Standard I/O functions
#include <string.h> // strcmp() for comparing entry names
#include <dirent.h> // Directory handling functions and structures
#include <sys/stat.h> // stat() and struct stat for file metadata

int main(int argc, char *argv[]) {
    
    // Use the provided path, or default to the current directory
    const char *path = (argc > 1) ? argv[1] : ".";

    // Open the target directory
    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("Could not open directory: %s\n", path);
        return 1;
    }

    struct dirent *entry;

    // Walk through every entry in the directory
    while ((entry = readdir(dir)) != NULL) {

        // Skip the "current directory" and "parent directory" entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Build the full path
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        // Look up metadata for this full path
        struct stat info;
        if (stat(full_path, &info) != 0) {
            printf("%s - could not read info\n", entry->d_name);
            continue;
        }

        // Print differently depending on whether it's a directory or a file
        if (S_ISDIR(info.st_mode)) {
            printf("[DIR] %s\n", entry->d_name);
        }
        else {
            printf("[FILE] %s - %lld bytes\n", entry->d_name, (long long)info.st_size);
        }
    }

    closedir(dir);
    return 0;




}