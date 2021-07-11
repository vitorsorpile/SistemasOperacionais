PROJ_NAME=exercicio3

# .c files
C_SOURCE=$(wildcard src/*.cpp)

# .h files
H_SOURCE=$(wildcard src/*.h)

# Object files
OBJ=$(C_SOURCE:.cpp=.o)

# Compiler
CC=g++
# Flags for compiler
CC_FLAGS= -Wall      \
          -Wextra    \
          -std=c++17 \
			 -Werror		\
			 -pthread   \
			 -pedantic	\
			 -g			\
			
#
# Compilation and linking
#
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CC_FLAGS)

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CC_FLAGS)

main.o: main.cpp $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	rm -rf src/*.o $(PROJ_NAME) *~