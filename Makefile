
# Makefile for f2022, ecs36b
# https://macappstore.org/libjson-rpc-cpp/
# https://github.com/cinemast/libjson-rpc-cpp

CC = g++ -std=c++14
CFLAGS = -g

# LDFLAGS = 	-L/Users/sfwu/vcpkg/installed/arm64-osx/lib -ljsoncpp -L/opt/homebrew/lib/ -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

LDFLAGS = 	-ljsoncpp -L/opt/homebrew/lib/ -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

INC	=	ecs36b_Common.h
INC_CL	=	JvTime.h Person.h Thing.h
OBJ	=	JvTime.o Person.o Thing.o

# rules.
all: 	grandmaHomeServer forestServer homeServer # hw5server # hw5client

#
#
# <target> : [... tab...] <dependency>
# [... tab ....] <action>

hw5client.h:		ecs36b_hw5.json
	jsonrpcstub ecs36b_hw5.json --cpp-server=hw5Server --cpp-client=hw5Client

hw5server.h:		ecs36b_hw5.json
	jsonrpcstub ecs36b_hw5.json --cpp-server=hw5Server --cpp-client=hw5Client

hw5client.o:		hw5client.cpp hw5client.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) hw5client.cpp

hw5server.o:		hw5server.cpp hw5server.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) hw5server.cpp

homeServer.o:		homeServer.cpp hw5server.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) homeServer.cpp

forestServer.o:		forestServer.cpp hw5server.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) forestServer.cpp

grandmaHomeServer.o:		grandmaHomeServer.cpp hw5server.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) grandmaHomeServer.cpp

ecs36b_JSON.o:		ecs36b_JSON.cpp $(INC)
	$(CC) -c $(CFLAGS) ecs36b_JSON.cpp

JvTime.o:	JvTime.cpp JvTime.h $(INC)
	$(CC) -c $(CFLAGS) JvTime.cpp

Person.o:	Person.cpp Person.h $(INC)
	$(CC) -c $(CFLAGS) Person.cpp

Thing.o:	Thing.cpp Thing.h $(INC)
	$(CC) -c $(CFLAGS) Thing.cpp

hw5server:	hw5server.o ecs36b_JSON.o $(OBJ)
	$(CC) -o hw5server hw5server.o ecs36b_JSON.o $(OBJ) $(LDFLAGS)

homeServer:	homeServer.o ecs36b_JSON.o $(OBJ)
	$(CC) -o homeServer homeServer.o ecs36b_JSON.o $(OBJ) $(LDFLAGS)

forestServer:	forestServer.o ecs36b_JSON.o $(OBJ)
	$(CC) -o forestServer forestServer.o ecs36b_JSON.o $(OBJ) $(LDFLAGS)

grandmaHomeServer:	grandmaHomeServer.o ecs36b_JSON.o $(OBJ)
	$(CC) -o grandmaHomeServer grandmaHomeServer.o ecs36b_JSON.o $(OBJ) $(LDFLAGS)

hw5client:	hw5client.o ecs36b_JSON.o $(OBJ)
	$(CC) -o hw5client hw5client.o ecs36b_JSON.o $(OBJ) $(LDFLAGS)

clean:
	rm -f *.o *~ core hw5client.h hw5server.h hw5client hw5server homeServer forestServer grandmaHomeServer


