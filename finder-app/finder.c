#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#define MAX_LINE_LENGTH 1024

int search_file(const char* filepath, const char* searchstr) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int matches = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, searchstr) != NULL) {
            matches++;
        }
    }

    fclose(file);
    return matches;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <directory> <searchstr>\n", argv[0]);
        return 1;
    }

    const char* dir_path = argv[1];
    const char* searchstr = argv[2];

    DIR* dir = opendir(dir_path);
    if (!dir) {
        fprintf(stderr, "Error opening directory: %s\n", strerror(errno));
        return 1;
    }

    struct dirent* entry;
    int total_files = 0;
    int total_matches = 0;
    char filepath[PATH_MAX];

    while ((entry = readdir(dir)) != NULL) {
        // Skip . and .. directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct full file path
        snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, entry->d_name);

        // Count regular files only
        if (entry->d_type == DT_REG) {
            total_files++;
            total_matches += search_file(filepath, searchstr);
        }
    }

    closedir(dir);

    printf("The number of files are %d and the number of matching lines are %d\n",
           total_files, total_matches);

    return 0;
}
