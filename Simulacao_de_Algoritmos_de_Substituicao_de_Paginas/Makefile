PROJ_NAME=Simulacao_de_Algoritmos_de_Substituicao_de_Paginas

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
			 -Wshadow	\
			 -Wconversion \
			 -Wcast-align \
			 -Werror		\
          -std=c++17 \
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


valgrind:
	$(MAKE)
	valgrind --leak-check=full --track-origins=yes -s ./$(PROJ_NAME) 64 < vsim-gcc.txt

clean:
	rm -rf src/*.o $(PROJ_NAME) *~

remake:
	$(MAKE) clean
	$(MAKE)