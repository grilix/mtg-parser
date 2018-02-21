YFLAGS  = -d

# TODO: remove parser/parse.h somehow?
parser_obj = parser/parse.o parser/parse.h parser/scan.o
mtg_src = $(wildcard src/mtg/*.c)
mtg_obj = $(mtg_src:%.c=%.o)

app_obj = src/main.o src/syntax.o

name = magic-parser

objects = $(parser_obj) $(app_obj) $(mtg_obj)

$(name): $(parser_obj) $(app_obj) $(mtg_obj)
	cc -o $(name) $(objects) -lfl -L/usr/lib

# TODO: Improve this step?
parser/parse.h: parser/parse.c
	mv -f y.tab.h parser/parse.h

clean-interm:
	rm -f parser/parse.c parser/parse.h

clean: clean-interm
	rm -f $(name) $(objects)
