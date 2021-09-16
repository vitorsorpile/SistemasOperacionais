PROJ_NAME=Comunicacao_em_Rede_via_Sockets

# .c files
C_SOURCE=$(filter-out src/main_loja.cpp src/main_cliente.cpp, $(wildcard src/*.cpp))

# .h files
H_SOURCE=$(wildcard src/*.h)

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
			 -Werror		\

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
servidor: $(OBJ) src/main_loja.o
	$(CC) -o $@ $^ $(CC_FLAGS)

cliente: $(OBJ) src/main_cliente.o
	$(CC) -o $@ $^ $(CC_FLAGS)

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CC_FLAGS)

src/main_loja.o: src/main_loja.cpp
	$(CC) -o src/main_loja.o -c src/main_loja.cpp $(CC_FLAGS)

src/main_cliente.o: src/main_cliente.cpp
	$(CC) -o src/main_cliente.o -c src/main_cliente.cpp $(CC_FLAGS)

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
