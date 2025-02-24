
SRC_DIRS := ./src
TST_DIRS := ./test

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
TSTS := $(shell find $(TST_DIRS) -name '*.c')

CFLAGS := -g

build/app : $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -lncurses -o build/app

build/test.so : $(TSTS)
	$(CC) $(TSTS) $(CFLAGS) -fPIC -shared -o build/test.so

test : build/app build/test.so
	cd build; \
	./app

