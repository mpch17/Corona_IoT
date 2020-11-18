CC=gcc
FLAGS = 
LINK := node.c camera_sim.c

node: $(foreach l, $(LINK), $(l)) ; \
    $(CC) -o node $(foreach l, $(LINK), $(l)) $(FLAGS)

clean: ; \
    rm node
