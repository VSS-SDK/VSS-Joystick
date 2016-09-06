CCX = g++ -std=c++11 -w


INCLUDES = -Isrc 

LIBRARIES_PROTO = `pkg-config --cflags --libs protobuf`

LIBRARIES = $(LIBRARIES_PROTO) -lzmq -pthread -lm -lc -w



SRC := $(shell find -name '*.cpp')
FILE_NAMES_SRC = $(SRC:.cpp=.o)

PROTOS := $(shell find -name '*.cc')
FILE_NAMES_PROTOS = $(PROTOS:.cc=.o)

FILE_NAMES = $(FILE_NAMES_SRC) $(FILE_NAMES_PROTOS) 



EXEC = VSS-Joystick

.cpp.o:
	@$(CCX) $(INCLUDES) $(LIBRARIES) -Wall -Wformat -ffast-math -c -o $@ $< -w

.cc.o:
	@$(CCX) $(INCLUDES) $(LIBRARIES) -Wall -Wformat -ffast-math -c -o $@ $< -w

all: message_compiling $(EXEC)
	@echo Done ...
	
message_compiling:
	@echo Compiling VSS-Joystick ...

message_cleaning:
	@echo Cleaning VSS-Joystick ...

run:
	./$(EXEC)

$(EXEC): $(FILE_NAMES)
	@$(CCX) -o $(EXEC) $(FILE_NAMES) $(LIBRARIES) $(INCLUDES)

clean: message_cleaning
	@rm $(EXEC) $(FILE_NAMES)

proto:
	cd src/VSS-Interface/protos && make -f protos.make

help: 
	./$(EXEC) -h
#teste: 
#	$(SRC)

