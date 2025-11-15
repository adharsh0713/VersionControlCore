#include "../include/utils.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <direct.h>
// Path to commits log
#define LOGFILE_PATH "data/commits.log"

// ----------- Generate current timestamp ------------
void getCurrentTimestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

// ----------- Safe malloc wrapper ------------
void* safeMalloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed. Exiting.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// ----------- Trim newline ------------
void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

// ----------- Escape JSON-unsafe characters ------------
void escapeJsonString(const char *input, char *output, size_t size) {
    size_t j = 0;
    for (size_t i = 0; i < strlen(input) && j < size - 2; i++) {
        if (input[i] == '"' || input[i] == '\\')
            output[j++] = '\\';
        output[j++] = input[i];
    }
    output[j] = '\0';
}

// ----------- Ensure log file exists ------------
void ensureLogFile() {
    struct stat st = {0};

    // Create data/ directory if missing
    if (stat("data", &st) == -1){
        #ifdef _WIN32
            _mkdir("data");
        #else
            mkdir("data", 0777);
        #endif
    }

    // Ensure commits.log file exists
    FILE *file = fopen(LOGFILE_PATH, "a");
    if (file)
        fclose(file);
}

// ----------- Unified JSON logger ------------
void logJsonEvent(const char *eventType, const char *branch, const char *message, int commitId) {
    ensureLogFile();

    FILE *f = fopen(LOGFILE_PATH, "a");
    if (!f) return;

    char safeMessage[512];
    escapeJsonString(message ? message : "", safeMessage, sizeof(safeMessage));

    char timestamp[64];
    getCurrentTimestamp(timestamp, sizeof(timestamp));

    fprintf(f,
        "{ \"timestamp\": \"%s\", \"event\": \"%s\", \"branch\": \"%s\", \"message\": \"%s\", \"commit\": %d }\n",
        timestamp, eventType,
        branch ? branch : "",
        safeMessage,
        commitId
    );

    fclose(f);
}
