_dummy := $(shell mkdir -p obj/testobj)

NAME =

TEST_NAME = 

CC = g++

ODIR = obj

TEST_ODIR = obj/testobj

INC_DIR = include

TEST_INC_DIR = $(INC_DIR)/test

GMOCK_INC_DIR = $(TEST_INC_DIR)/gmock

GTEST_INC_DIR = $(TEST_INC_DIR)/gtest

LIB_DIR = lib

CXXFLAGS = -g -Wall -Werror -Wextra -I./$(INC_DIR)

TEST_FLAGS = -L$(LIB_DIR) -lgtest_main -lgmock_main \
			 -I$(GTEST_INC_DIR) -I$(GMOCK_INC_DIR)

SRC_DIR = src/

TEST_DIR = $(SRC_DIR)tests/

CLASS_DIR = $(SRC_DIR)Classes/

_CLASSES = 
_SRC = 
_TESTS = 

SRC = $(addprefix $(SRC_DIR), $(_SRC))
CLASSES = $(addprefix $(CLASS_DIR), $(_CLASSES))
TESTS = $(addprefix $(TEST_DIR), $(_TESTS))

OBJ = $(patsubst %, $(ODIR)/%, $(_SRC:.cpp=.o)) $(patsubst %, $(ODIR)/%, $(_CLASSES:.cpp=.o))

TEST_OBJ = $(OBJ) $(patsubst %, $(ODIR)/%, $(_TESTS:.cpp=.o))

$(ODIR)/%.o: $(SRC_DIR)%.cpp $(INC_DIR)/*.h
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/%.o: $(CLASS_DIR)%.cpp $(INC_DIR)/*.h
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(TEST_ODIR)/%.o: $(TEST_DIR)%.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS) $(TEST_FLAGS)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS)

$(TEST_NAME): $(TEST_OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS) $(TEST_FLAGS)

all: $(NAME)

test: $(TEST_NAME)

clean:
	$(RM) -rf $(ODIR)

fclean: clean
	$(RM) $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all fclean clean re

