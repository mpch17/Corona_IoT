CC=g++
LIB := ../lib ../lib/json/include
CFLAGS = $(foreach L, $(LIB), -I$(L)) -pthread -std=c++11 #`pkg-config nlohmann_json --cflags`
LINK := server.cpp ../lib/communicate.c ../lib/flow_path.cpp IO/frame.cpp IO/frame_io.cpp IO/frame_io_read.cpp IO/frame_io_write.cpp IO/node.cpp graph/flow_graph.cpp

server: $(foreach l, $(LINK), $(l)) ; \
    $(CC) -o server $(foreach l, $(LINK), $(l)) $(CFLAGS)

clean: ; \
    rm server
