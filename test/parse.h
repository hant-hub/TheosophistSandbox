#ifndef PARSE_H
#define PARSE_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define ARR_SIZE(x) sizeof(x)/sizeof(x[0])

typedef float f32;
typedef double f64;
typedef long double f128;

typedef uint32_t u32;
typedef uint64_t u64;

typedef uint_fast8_t u8_f;
typedef uint_fast16_t u16_f;
typedef uint_fast32_t u32_f;

typedef int32_t i32;
typedef int64_t i64;

//typedef uint8_t bool;
//const bool true = 1;
//const bool false = 0;

#define SM_INLINE static inline
#define SM_PI 3.14159265358979323846
#define SM_2_PI 6.28318530717958647692

typedef enum {
    TOKEN_UNINITIALIZED = 0,
    TOKEN_NEWLINE,
    TOKEN_WHITESPACE,
    TOKEN_WORD,
    TOKEN_NUMERIC,
    TOKEN_PUNCTUATION,
    TOKEN_EOB
} TokenType;


typedef struct {
    char* pos;
    u32 length;
    TokenType type;
} Token;

typedef struct {
    u64 size;
    char* Base;
    char* At;
} Tokenizer;

//maybe later cause its cool
//Could be useful for like evaluating math
//expressions which would be sick
Token GetToken(Tokenizer* t);


#endif
