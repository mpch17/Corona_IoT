CC=g++
LIB := ../lib
FLAGS = -I$(LIB)
LINK := server.cpp ../lib/communicate.c IO/frame.cpp IO/frame_io.cpp IO/frame_io_read.cpp IO/frame_io_write.cpp graph/graph.cpp graph/flow_graph.cpp

server: $(foreach l, $(LINK), $(l)) ; \
    $(CC) -o server $(foreach l, $(LINK), $(l)) $(FLAGS)

clean: ; \
    rm server
