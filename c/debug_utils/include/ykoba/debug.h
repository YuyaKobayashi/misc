
#pragma once

#ifdef DEBUG
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#define DPRINT(fmt, ...) do { \
    fprintf(stderr, "[DEBUG] %s()@%s.L%d: " fmt, __func__, __FILE__, __LINE__, ##__VA_ARGS__); \
} while(0)
#define DPRINT_ERRNO(fmt, ...) DPRINT("errno {%s}: " fmt, strerror(errno), ##__VA_ARGS__)

static int ykoba_dump_bin(const char *filename, const void *ptr, size_t size) {
    FILE *fp = NULL;

    assert(ptr);
    assert(filename);
    assert(size);

    fp = fopen(filename, "wb");
    if (!fp) {
        DPRINT_ERRNO("Failed to open dump file(%s) with write permission.", filename);
        return errno;
    }
    if (fwrite(ptr, 1, size, fp) != size) {
        DPRINT_ERRNO("Failed to dump memory (0x%p) to file (%s).", ptr, filename);
        fclose(fp);
        return errno;
    }

    fclose(fp);
    return 0;
}

static int ykoba_load_bin(const char *filename, void *ptr, size_t size) {
    FILE *fp = NULL;

    assert(ptr);
    assert(filename);
    assert(size);

    fp = fopen(filename, "rb");
    if (!fp) {
        DPRINT_ERRNO("Failed to open dump file(%s) with read permission.", filename);
        return errno;
    }
    if (fread(ptr, 1, size, fp) != size) {
        DPRINT_ERRNO("Failed to load file (%s) to file (0x%p).", filename, ptr);
        fclose(fp);
        return errno;
    }

    fclose(fp);
    return 0;
}


#else // DEBUG

#define DPRINT(fmt, ...) do {;} while(0)
#define DPRINT_ERRNO(fmt, ...) do {;} while(0)

static int ykoba_dump_bin(const char *filename, const void *ptr, size_t size) { return 0; }
static int ykoba_load_bin(const char *filename, void *ptr, size_t size) { return 0; }

#endif // DEBUG
