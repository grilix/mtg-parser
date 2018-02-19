YFLAGS  = -d

# TODO: remove parser/parse.h somehow?
parser_objs = parser/parse.o parser/parse.h parser/scan.o
objects = $(parser_objs) \
		src/card.o src/rules.o src/objective.o src/effect.o \
		src/ability.o src/cost.o \
		src/syntax.o \
		src/main.o

name = magic-parser

$(name): $(objects)
	cc -o $(name) $(objects) -lfl -L/usr/lib

# TODO: Improve this step?
parser/parse.h: parser/parse.c
	mv -f y.tab.h parser/parse.h

clean-interm:
	rm -f parser/parse.c parser/parse.h

clean: clean-interm
	rm -f $(name) $(objects)
