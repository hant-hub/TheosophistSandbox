#include "parse.h"
#include <stdio.h>

const char* bname = "EssentialTest";
const char* vname = "VarTest";


#define NUM_RESULTS 10
const int numresults = NUM_RESULTS;

//each result is zero or one
//to indicate the pass or fail of each test.
int results[NUM_RESULTS] = {0};


const char* strtable[3] = {
    "This is one possible feedback",
    "this is another",
    "This is a third"
};

char buffer[200] = {0};


//writes into result buffer
void EssentialTest(char* buf, int size) {

    Tokenizer tok = (Tokenizer) {
        .size = size,
        .Base = buf,
        .At = buf,
    };

    Token t;
    int i = 0;
    WordLineCounterState counter = {0};
    LineCounterState linecount = {0};
    MatchSubState substr = {0};
    StrInSetState strset = {0};
    MatchStringState matchs = {0};

    int linevals[] = {1, 2, 3};
    char* match = "THM";
    char* include = "What";

    char* wordset[] = {
        "There",
        "He",
        "Her",
        "Naught",
        "What",
        "Maybe",
        "for"
    };

    while (1) {
        t = GetToken(&tok);
        CountWordsPerLine(&counter, linevals, ARR_SIZE(linevals), t);
        CountLines(&linecount, t);
        MatchSubstr(&substr, match, t);
        StrInSet(&strset, wordset, ARR_SIZE(wordset), t);
        MatchString(&matchs, include, t);
        if (t.type == TOKEN_EOB) break;
        //if (t.type == TOKEN_WORD) {
        //    sprintf(buffer, "Token Length: %d", t.length);
        //}
    }

    results[0] = ARR_SIZE(linevals) - counter.incorrect;
    results[1] = linecount.linecount;
    results[2] = substr.needlepos;
    results[3] = strset.mismatch;
    results[4] = matchs.matched;
}

//index into array of strings
int VarTest(char* buf, int size) {
    Tokenizer tok = (Tokenizer) {
        .size = size,
        .Base = buf,
        .At = buf
    };

    Token t;
    int i = 0;
    while (1) {
        t = GetToken(&tok);
        i++;
        if (t.type == TOKEN_EOB) break;
    }

    //This is necessary for clipping
    //If this isn't stored into a variable
    //it evaluates to zero instead
    int j = ARR_SIZE(strtable);
    return i;

}


