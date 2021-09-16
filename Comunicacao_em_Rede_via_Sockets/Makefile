PROJ_NAME=Comunicacao_em_Rede_via_Sockets

# .c files
C_SOURCE=$(filter-out src/Servidor.cpp src/Cliente.cpp, $(wildcard src/*.cpp))

# .h files
H_SOURCE=$(filter-out Servidor.h Cliente.h, $(wildcard src/*.h))

# Object files
OBJ=$(C_SOURCE:.cpp=.o)
# OBJ = socket.o 

# Compiler
CC=g++

# Flags for compiler
CC_FLAGS= -Wall      \
          -Wextra    \
			 -Wshadow	\
			 -Wconversion \
			 -Wcast-align \
          -std=c++17 \
			 -g			\
			 -pthread   \
			#  -Werror		\

#
# Compilation and linking
#
# all: $(PROJ_NAME)
executables= servidor cliente

all: $(executables)

# $(PROJ_NAME): $(OBJ)
# 	$(CC) -o $@ $^ $(CC_FLAGS)
# $(CC) -o src/servidor.o -c src/Servidor.cpp $(CC_FLAGS)
# $(CC) -o src/cliente.o -c src/Cliente.cpp $(CC_FLAGS)
servidor: $(OBJ) src/Servidor.o
	$(CC) -o $@ $^ $(CC_FLAGS)

cliente: $(OBJ) src/Cliente.o
	$(CC) -o $@ $^ $(CC_FLAGS)

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CC_FLAGS)

src/Servidor.o: src/Servidor.cpp
	$(CC) -o src/Servidor.o -c src/Servidor.cpp $(CC_FLAGS)

src/Cliente.o: src/Cliente.cpp
	$(CC) -o src/Cliente.o -c src/Cliente.cpp $(CC_FLAGS)

# teste:
# 	$(OBJ)

valgrind:
	$(MAKE)
	valgrind --leak-check=full --track-origins=yes -s ./$(PROJ_NAME) 64 < vsim-gcc.txt

clean:
	rm -rf $(executables) src/*.o *~

remake:
	$(MAKE) clean
	$(MAKE)
