PROJ_NAME=exercicio1

# .c files
C_SOURCE=$(wildcard *.cpp)

# .h files
H_SOURCE=$(wildcard *.h)

# Object files
OBJ=$(C_SOURCE:.c=.o)

# Compiler
CC=g++

# Flags for compiler
CC_FLAGS= -Wall      \
          -Wextra    \
          -pthread   \
          -std=c++17 \
#          -pedantic	

#
# Compilation and linking
#
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CC_FLAGS)

%.o: %.cpp %.h
	$(CC) -o $@ $< $(CC_FLAGS)

main.o: main.cpp $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	rm -rf *.o $(PROJ_NAME) *~