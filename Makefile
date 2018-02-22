YFLAGS  = -d

# TODO: remove parser/parse.h somehow?
parser_obj = parser/parse.o parser/parse.h parser/scan.o
mtg_src = $(wildcard src/mtg/*.c)
mtg_obj = $(mtg_src:%.c=%.o)
test_src = $(wildcard test/mtg/*.c)
test_obj = $(test_src:%.c=%.o)

app_obj = src/main.o src/syntax.o

name = magic-parser
test_name = test/test

objects = $(parser_obj) $(app_obj) $(mtg_obj)

$(name): $(parser_obj) $(app_obj) $(mtg_obj)
	cc -o $(name) $(objects) -lfl -L/usr/lib

# TODO: Improve this step?
parser/parse.h: parser/parse.c
	mv -f y.tab.h parser/parse.h

clean-interm:
	rm -f parser/parse.c parser/parse.h

clean: clean-interm
	rm -f $(name) $(objects) test/test test/main.o $(test_obj)

test: $(test_name)
	$(test_name)

test/test: $(name) test/main.o $(test_obj)
	cc -o test/test $(mtg_obj) test/main.o $(test_obj) -lcunit -L/usr/lib
