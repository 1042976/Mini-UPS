CC=g++
OUTPUT_FILE=libprotocol.a
OBJ_DIR=.
OUTPUT_DIR=../
CPPFLAGS=-Wall -Werror -pedantic -std=c++2a
$(OUTPUT_FILE): $(patsubst %.cc,$(OBJ_DIR)/%.o,$(wildcard *.cc))
	ar -r -o $(OUTPUT_DIR)/$@ $^
$(OBJ_DIR)/%.o: %.cc
	$(CC) -c $(CPPFLAGS) -o $@  $<
clean:
	rm -f *.a *.o *.gch