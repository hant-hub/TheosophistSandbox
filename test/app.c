#include "parse.h"

const char* bname = "EssentialTest";
const char* vname = "VarTest";


#define NUM_RESULTS 10
const int numresults = NUM_RESULTS;

//each result is zero or one
//to indicate the pass or fail of each test.
int results[NUM_RESULTS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};


const char* strtable[3] = {
    "This is one possible feedback",
    "this is another",
    "This is a third"
};


//writes into result buffer
void EssentialTest(char* buf, int size) {

    Tokenizer tok = (Tokenizer) {
        .size = size,
        .Base = buf,
        .At = buf,
    };

    Token t;
    int i = 0;
    while ((t = GetToken(&tok)).type != TOKEN_EOB) {
       i++; 
    }

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
    while ((t = GetToken(&tok)).type != TOKEN_EOB) {
       i++; 
    }

    //This is necessary for clipping
    //If this isn't stored into a variable
    //it evaluates to zero instead
    int j = ARR_SIZE(strtable);
    return i % j;

}


