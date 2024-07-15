#ifndef CUE_H
#define CUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

enum {
    CUE_OK = 0,
    CUE_FILE_NOT_FOUND,
    CUE_TRACK_FILE_NOT_FOUND
};

enum {
    CUE_4CH = 0,
    CUE_AIFF,
    CUE_AUDIO,
    CUE_BINARY,
    CUE_CATALOG,
    CUE_CDG,
    CUE_CDI_2336,
    CUE_CDI_2352,
    CUE_CDTEXTFILE,
    CUE_DCP,
    CUE_FILE,
    CUE_FLAGS,
    CUE_INDEX,
    CUE_ISRC,
    CUE_MODE1_2048,
    CUE_MODE1_2352,
    CUE_MODE2_2336,
    CUE_MODE2_2352,
    CUE_MOTOROLA,
    CUE_MP3,
    CUE_PERFORMER,
    CUE_POSTGAP,
    CUE_PRE,
    CUE_PREGAP,
    CUE_REM,
    CUE_SCMS,
    CUE_SONGWRITER,
    CUE_TITLE,
    CUE_TRACK,
    CUE_WAVE,
    CUE_NONE = 255
};

enum {
    LD_BUFFERED,
    LD_FILE
};

enum {
    TS_FAR = 0,
    TS_DATA,
    TS_AUDIO,
    TS_PREGAP
};

struct cue_file {
    char* name;
    int buf_mode;
    void* buf;
    size_t size;
    uint32_t start;
    list_t* tracks;
};

struct cue_track {
    int number;
    int mode;

    int32_t index[2];
    uint32_t pregap;
    uint32_t start;
    uint32_t end;

    struct cue_file* file;
};

struct cue_state {
    list_t* files;
    list_t* tracks;

    char c;
    FILE* file;
};

struct cue_state* cue_create(void);
void cue_init(struct cue_state* cue);
int cue_parse(struct cue_state* cue, const char* path);
int cue_load(struct cue_state* cue, int mode);

// Disc interface
int cue_read(struct cue_state* cue, uint32_t lba, void* buf);
int cue_query(struct cue_state* cue, uint32_t lba);
int cue_get_track_number(struct cue_state* cue, uint32_t lba);
int cue_get_track_count(struct cue_state* cue);
int cue_get_track_lba(struct cue_state* cue, int track);
void cue_destroy(struct cue_state* cue);

#ifdef __cplusplus
}
#endif

#endif