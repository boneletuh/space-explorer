CC := gcc
CFLAGS := -Wall -Wextra -pedantic -O1
LINK_PARAMS := -I./raylib/include/ -L./raylib/lib/ -lm -lc -lgcc -l:libraylib.a

main=src/main
physics=src/physics
utils=src/utils
render=src/render
save_and_load=src/save_and_load

out_name := space_explorer

all: compile

compile: ${main}.o ${physics}.o ${utils}.o ${render}.o ${save_and_load}.o
	${CC} ${CFLAGS} ${main}.o ${physics}.o ${utils}.o ${render}.o ${save_and_load}.o -o ${out_name} ${LINK_PARAMS}

%.o: %.c
	${CC} ${CFLAGS} $< -c -o $@ ${LINK_PARAMS}

clean:
	rm ${main}.o ${physics}.o ${utils}.o ${render}.o ${save_and_load}.o