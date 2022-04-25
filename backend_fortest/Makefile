SOURCES=BaseHandler.cpp WorldSimulatorHandler.cpp AmazonHandler.cpp FrontEndHandler.cpp\
 UPSData.cpp Buffer.cpp ServerSocket.cpp ClientSocket.cpp Common.cpp SeqnumCreator.cpp\
 Truck.cpp UPSServer.cpp

LIBS=libprotocol.a -lpthread -lpqxx -lpq `pkg-config --cflags --libs protobuf`
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
INC_PRO=./protocolcodes
INC_CPTL=./cptl
CPPFLAGS=-I$(INC_PRO) -I$(INC_CPTL) -Wall -Werror -pedantic -std=c++2a

all: UPSServer
UPSServer: $(OBJS)
	g++ $(CPPFLAGS) -o UPSServer $(OBJS) $(LIBS)
%.o: %.cpp
	g++ $(CPPFLAGS) -c $<

clean:
	rm -f UPSServer *.o