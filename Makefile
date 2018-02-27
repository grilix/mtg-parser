YACC = bison -y
YFLAGS  = -d
LEX = flex

parser_obj = parser/parse.o parser/scan.o

mtg_src = $(wildcard src/mtg/*.c)
mtg_obj = $(mtg_src:%.c=%.o)

test_mtg_src = $(wildcard test/mtg/*.c)
test_src = $(wildcard test/*.c)
test_obj = $(test_src:%.c=%.o) $(test_mtg_src:%.c=%.o)
app_obj = src/input.o src/common.o

name = magic-parser
test_name = test/test

objects = $(parser_obj) $(app_obj) $(mtg_obj)

$(name): $(objects) src/main.o
	cc -o $(name) $(objects) src/main.o -lfl -L/usr/lib

$(app_obj): parser/scan.c

parser/parse.o: parser/scan.c parser/parse.y
	bison --defines=parser/parse.h --output=parser/parse.c parser/parse.y
	cc -c -o parser/parse.o parser/parse.c

clean-interm:
	rm -f parser/parse.[ch] parser/scan.[ch]

clean: clean-interm
	rm -f $(name) $(objects) src/main.o test/test $(test_obj)

test: $(test_name)
	$(test_name)

test/test: $(name) test/main.o $(test_obj)
	cc -o test/test $(objects) $(test_obj) -lcunit -L/usr/lib
