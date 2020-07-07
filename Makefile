_dummy := $(shell mkdir -p obj)

NAME =

CC = g++

ODIR = obj

INC_DIR = include

CXXFLAGS = -g -Wall -Werror -Wextra -I./$(INC_DIR)

SRC_DIR = src/

CLASS_DIR = $(SRC_DIR)Classes/

_CLASSES = 
_SRC = 

SRC = $(addprefix $(SRC_DIR), _SRC)
CLASSES = $(addprefix $(CLASS_DIR), _CLASSES)

OBJ = $(patsubst %, $(ODIR)/%, $(_SRC:.cpp=.o)) $(patsubst %, $(ODIR)/%, $(_CLASSES:.cpp=.o))

$(ODIR)/%.o: $(SRC_DIR)%.cpp $(INC_DIR)/*.h
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/%.o: $(CLASS_DIR)%.cpp $(INC_DIR)/*.h
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS)

clean:
	$(RM) -rf $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re

