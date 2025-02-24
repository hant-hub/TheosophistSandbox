#include <dlfcn.h>
#include <ncurses.h>
#include <stdio.h>

typedef void (*boolcheck)(char*, int);
typedef int (*varcheck)(char*, int);

void boolstub(char* buf, int size) {
}

int varstub(char* buf, int size) {
    return -1;
}

static int top;
static char buffer[100];

typedef struct {
    void* lib;
    int* results;
    int numresults;
    boolcheck e;
    varcheck o;
} SharedLib;


void LoadLib(SharedLib* s);
void UnloadLib(SharedLib* s);

int main() {

    SharedLib s = {
        .e = boolstub,
        .o = varstub
    };

    LoadLib(&s);
    getchar();

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    halfdelay(5);

    WINDOW* text = newwin(10, 40, 10, 10);
    WINDOW* border = newwin(12, 42, 9, 9);
    keypad(border, TRUE);
    keypad(text, TRUE);

    int shouldclose = 0; 
    int ch = 0;
    while (!shouldclose) {
        LoadLib(&s);
        mvprintw(0, 0, "NumChars: %d", ch);
        s.e(buffer, top);
        mvprintw(1, 0, "Essential: ");
        for (int i = 0; i < s.numresults; i++) {
            printw("%d ", s.results[i]);
        }
        mvprintw(2, 0, "Optional: %d", s.o(buffer, top));
        refresh();
        box(border, 0, 0);
        wrefresh(border);
         
        waddnstr(text, buffer, top);
        wrefresh(text);

        int c = wgetch(text);
        wclear(stdscr);
        wclear(text);
        switch (c) {
            case 27:
            {
                mvprintw(3, 0, "Case27");
                shouldclose = 1;
                break;
            }
            case KEY_BACKSPACE:
            {
                mvprintw(3, 0, "CaseBack");
                if (top) buffer[--top] = 0;
                break;
            }
            case ERR:
            {
                mvprintw(3, 0, "CaseErr");
                break;
            }
            default:
            {
                mvprintw(3, 0, "CaseDefault");
                buffer[top++] = c;
                ch = c;
                break;
            }
        }

    }



    UnloadLib(&s);
    delwin(text);
    endwin();


    return 0;
}

void LoadLib(SharedLib* s) {
    if (s->lib) dlclose(s->lib);
    s->lib = dlopen("./test.so", RTLD_NOW);
    if (!s->lib) {
        s->numresults = 0;
        s->results = 0;
        s->e = boolstub;
        s->o = varstub;
        return;
    }

    char* bname = *(char**)dlsym(s->lib, "bname");
    char* vname = *(char**)dlsym(s->lib, "vname");
    s->numresults = *(int*)dlsym(s->lib, "numresults");
    s->results = (int*)dlsym(s->lib, "results");

    s->e = dlsym(s->lib, bname);
    s->o = dlsym(s->lib, vname);

}

void UnloadLib(SharedLib* s) {
    if (s->lib) {
        dlclose(s->lib);
    }
}




