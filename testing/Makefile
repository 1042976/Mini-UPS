SOURCES=AmazonServer.cpp Buffer.cpp ServerSocket.cpp ClientSocket.cpp Common.cpp SeqnumCreator.cpp
LIBS=libprotocol.a -lpthread -lpqxx -lpq `pkg-config --cflags --libs protobuf`
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
INC_PRO=./protocolcodes
INC_CPTL=./cptl
CPPFLAGS=-I$(INC_PRO) -I$(INC_CPTL) -Wall -Werror -pedantic -std=c++2a

all: AmazonServer
AmazonServer: $(OBJS)
	g++ $(CPPFLAGS) -o AmazonServer $(OBJS) $(LIBS)
%.o: %.cpp
	g++ $(CPPFLAGS) -c $<

clean:
	rm -f AmazonServer *.o