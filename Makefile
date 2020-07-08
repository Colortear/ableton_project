_dummy := $(shell mkdir -p obj/testobj)

NAME = warped_record

TEST_NAME = warped_record_tests

CC = gcc

ODIR = obj

TEST_ODIR = obj/testobj

INC_DIR = include

TEST_INC_DIR = $(INC_DIR)/test

GMOCK_INC_DIR = $(TEST_INC_DIR)/gmock

GTEST_INC_DIR = $(TEST_INC_DIR)/gtest

LIB_DIR = lib

CXXFLAGS = -g -lstdc++ -std=c++17 -Wall -Werror -Wextra

INC_FLAGS = -I./$(INC_DIR)

TEST_LIB_FLAGS = -L$(LIB_DIR) -lgtest -lgtest_main -lgmock -lgmock_main -lpthread

#TEST_INC_FLAGS = -I$(GTEST_INC_DIR) -I$(GMOCK_INC_DIR)
TEST_INC_FLAGS = -I$(TEST_INC_DIR)

SRC_DIR = src/

TEST_DIR = $(SRC_DIR)tests/

CLASS_DIR = $(SRC_DIR)Classes/

_CLASSES = 
_SRC = main.cpp
_TESTS = quick_test.cpp

SRC = $(addprefix $(SRC_DIR), $(_SRC))
CLASSES = $(addprefix $(CLASS_DIR), $(_CLASSES))
TESTS = $(addprefix $(TEST_DIR), $(_TESTS))

OBJ = $(patsubst %, $(ODIR)/%, $(_SRC:.cpp=.o)) $(patsubst %, $(ODIR)/%, $(_CLASSES:.cpp=.o))

TEST_OBJ = $(filter-out obj/main.o, $(OBJ)) $(patsubst %, $(TEST_ODIR)/%, $(_TESTS:.cpp=.o))

$(ODIR)/%.o: $(SRC_DIR)%.cpp
	$(CC) -c -o $@ $< $(INC_FLAGS) $(CXXFLAGS)

$(ODIR)/%.o: $(CLASS_DIR)%.cpp
	$(CC) -c -o $@ $< $(INC_DIR) $(CXXFLAGS)

$(TEST_ODIR)/%.o: $(TEST_DIR)%.cpp
	$(CC) -c -o $@ $(TEST_INC_FLAGS) $< $(CXXFLAGS)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS)

$(TEST_NAME): $(TEST_OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS) $(TEST_LIB_FLAGS)

all: $(NAME)

test: $(TEST_NAME)

install_deps: install_deps_script

install_deps_script:
	chmod +x scripts/install_deps.sh
	./scripts/install_deps.sh

clean:
	$(RM) -r $(ODIR)

fclean: clean
	$(RM) $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all fclean clean re test

