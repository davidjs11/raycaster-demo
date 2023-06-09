# macros
HOME	= 	.

SRC		=	$(HOME)/src
INCLUDE	=	$(HOME)/include
OBJ		=	$(HOME)/obj
BIN		=	$(HOME)/bin

FLAGS	=	-lSDL2 -lm


# binary 
$(BIN)/raycaster:\
	$(OBJ)/raycaster.o\
	$(OBJ)/graphUtils.o\
	$(OBJ)/sdlUtils.o\
	$(OBJ)/gameUtils.o
	@echo "creating binary..."
	@gcc -o  $(BIN)/raycaster\
			 $(OBJ)/raycaster.o\
			 $(OBJ)/graphUtils.o\
			 $(OBJ)/sdlUtils.o\
			 $(OBJ)/gameUtils.o\
			 $(FLAGS)


# objects
$(OBJ)/raycaster.o:\
	$(SRC)/raycaster.c\
	$(INCLUDE)/graphUtils.h\
	$(INCLUDE)/sdlUtils.h
	@echo "compiling raycaster..."
	@gcc -c -o $(OBJ)/raycaster.o\
			   $(SRC)/raycaster.c\
			 -I$(INCLUDE) $(FLAGS)

$(OBJ)/graphUtils.o:\
	$(SRC)/graphUtils.c\
	$(INCLUDE)/graphUtils.h
	@echo "compiling graphUtils..."
	@gcc -c -o $(OBJ)/graphUtils.o\
		  	   $(SRC)/graphUtils.c\
			 -I$(INCLUDE) $(FLAGS)

$(OBJ)/sdlUtils.o:\
	$(SRC)/sdlUtils.c\
	$(INCLUDE)/sdlUtils.h
	@echo "compiling sdlUtils..."
	@gcc -c -o $(OBJ)/sdlUtils.o\
		  	   $(SRC)/sdlUtils.c\
			 -I$(INCLUDE) $(FLAGS)

$(OBJ)/gameUtils.o:\
	$(SRC)/gameUtils.c\
	$(INCLUDE)/gameUtils.h
	@echo "compiling gameUtils..."
	@gcc -c -o $(OBJ)/gameUtils.o\
			   $(SRC)/gameUtils.c\
			 -I$(INCLUDE) $(FLAGS)


# cleaning
clean:
	@echo "cleaning..."
	@rm $(OBJ)/* $(BIN)/*
