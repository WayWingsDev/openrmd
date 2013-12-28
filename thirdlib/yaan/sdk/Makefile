
#################################################################
#TARGET
TARGET_DYN_LIB = libynnet.so
TARGET_STA_LIB = libynnet.a

#################################################################
#tool chain
CC = g++
AR = ar

#################################################################
#compile parameters
CFLAGS += -Wall -O

#################################################################
#OBJ LIST
SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=%.o)

#################################################################
#generate dynamic/static library
.PHONY: clean all
all: $(TARGET_DYN_LIB) $(TARGET_STA_LIB)

$(TARGET_DYN_LIB): $(OBJ)
	$(CC) -fPIC -shared -o $@ $^ -lpthread

$(TARGET_STA_LIB): $(OBJ)
	$(AR) rcs $@ $^

$(OBJ): %.o : %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@rm -f $(TARGET_DYN_LIB)
	@rm -f $(TARGET_STA_LIB)
	@rm -f $(OBJ)

install:
#	install $(TARGET_DYN_LIB) ../../../../nfs
