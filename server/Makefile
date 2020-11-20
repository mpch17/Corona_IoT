CC=g++
LIB := ../lib
FLAGS = -I$(LIB) -pthread
LINK := server.cpp ../lib/communicate.c IO/frame.cpp IO/frame_io.cpp IO/frame_io_read.cpp IO/frame_io_write.cpp IO/node.cpp graph/graph.cpp graph/flow_graph.cpp google_location.cpp

server: $(foreach l, $(LINK), $(l)) ; \
    $(CC) -o server $(foreach l, $(LINK), $(l)) $(FLAGS)

clean: ; \
    rm server
