#pragma once

#include "defines.h"

#define sgArrSize(__ARR) sizeof(__ARR) / sizeof(__ARR[0])

static void sgLog(const char *message, ...)
{
    va_list args;
    va_start(args, message);
    printf("%s", "|SoGL| :: ");
    vprintf(message, args);
    printf("\n\n");
    va_end(args);
}

#define sgLogInit(MESSAGE, ...) \
    sgLog("|INIT| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define sgLogInfo(MESSAGE, ...) \
    sgLog("|INFO| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define sgLogSuccess(MESSAGE, ...) \
    sgLog("|SUCCESS| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define sgLogWarning(MESSAGE, ...) \
    sgLog("|WARNING| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

#define sgLogError(MESSAGE, ...) \
    sgLog("|ERROR| :: %s() :: " MESSAGE, __FUNCTION__, ##__VA_ARGS__)

char *sgReadFile(const char *path) {
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        sgLogError("ReadFile :: UNABLE TO ACCESS FILE[%s]",path);
        return NULL;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        sgLogError("ReadFile :: UNABLE TO SEEK IN FILE[%s]",path);
        fclose(file );
        return NULL;
    }

    long len = ftell(file);
    if (len == -1) {
        sgLogError("ReadFile :: UNABLE TO DETERMINE SIZE OF FILE[%s]",path);
        fclose(file);
        return NULL;
    }
    rewind(file);

    char *fileContent = malloc(len+1);
    if (fileContent == NULL) {
        sgLogError("ReadFile :: MEMORY ALLOCATION]");
        return NULL;
    }

    size_t readSize = fread(fileContent, 1, len, file);
    if (readSize < (size_t)len) {
        sgLogError("ReadFile :: UNABLE TO READ FILE[%s] :: READ [%zu/%ld]",path, readSize, len);
        return NULL;
    }
    fileContent[len] = '\0';
    fclose(file);

    return fileContent;
}

// function to print decimal as binary
void bin(unsigned n) {
    if (n>1) {
            bin(n>>1);
    } printf("DECIMAL[%d] || BINARY[%d]\n", n, n&1);
}