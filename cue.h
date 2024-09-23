/*
    Tiny BIN/CUE parsing and loading library

    MIT License

    Copyright (c) 2024 Allkern (Lisandro Alarcón)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

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
    CUE_TRACK_FILE_NOT_FOUND,
    CUE_NULL_BUFFER
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
    LD_BUFFERED_EXT,
    LD_FILE
};

enum {
    TS_FAR = 0,
    TS_DATA,
    TS_AUDIO,
    TS_PREGAP
};

typedef struct cue_file {
    char* name;
    char* name_backup;
    int buf_mode;
    void* buf;
    size_t size;
    uint32_t start;
    list_t* tracks;
} cue_file;

typedef struct cue_track {
    int number;
    int mode;

    int32_t index[2];
    uint32_t pregap;
    uint32_t start;
    uint32_t end;

    struct cue_file* file;
} cue_track;

typedef struct cue_state {
    list_t* files;
    list_t* tracks;

    char c;
    FILE* file;
} cue_state;

cue_state* cue_create(void);
void cue_init(cue_state* cue);
int cue_parse(cue_state* cue, const char* path);
int cue_load(cue_state* cue, int mode, char* ext_buffer);

// Disc interface
int cue_read(cue_state* cue, uint32_t lba, void* buf);
int cue_query(cue_state* cue, uint32_t lba);
int cue_get_track_number(cue_state* cue, uint32_t lba);
int cue_get_track_count(cue_state* cue);
int cue_get_track_lba(cue_state* cue, uint32_t track);
void cue_destroy(cue_state* cue);

#ifdef __cplusplus
}
#endif

#endif