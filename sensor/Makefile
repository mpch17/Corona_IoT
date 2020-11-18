CC=gcc
LIB := ../lib
FLAGS = -I$(LIB)
LINK := node.c camera_sim.c ../lib/communicate.c

node: $(foreach l, $(LINK), $(l)) ; \
    $(CC) -o node $(foreach l, $(LINK), $(l)) $(FLAGS)

clean: ; \
    rm node
