# comp & comp flags
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror 
CFLAGS_GCOV = $(CFLAGS) -fprofile-arcs -ftest-coverage 

# for diff linking on MacOS and Linux
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    LDFLAGS := -lcheck -pthread -lcheck_pic -lrt -lm -lsubunit
    LDFLAGS_GCOV := $(LDFLAGS) -fprofile-arcs --coverage
    LIBLINK := -L. -l:s21_decimal.a
else ifeq ($(UNAME), Darwin)  # MacOS
    LDFLAGS := -lcheck
    LDFLAGS_GCOV := $(LDFLAGS) -fprofile-arcs --coverage
    LIBLINK := s21_decimal.a
else
    $(error Unsupported platform: $(UNAME))
endif

# source files/dirs
SRCDIR = .
LIB_OBJDIR = lib_obj
TEST_OBJDIR = tests_obj

SRC = $(wildcard $(SRCDIR)/s21_*.c)
LIB_OBJ = $(patsubst $(SRCDIR)/%.c, $(LIB_OBJDIR)/%.o, $(SRC))
LIB = s21_decimal.a

# for testing & gcov report
TEST_DIR = tests
TEST_SRC = $(wildcard $(TEST_DIR)/test_s21_*.c)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c, $(TEST_OBJDIR)/%.o, $(TEST_SRC))
TEST_EXEC = s21_decimal_test

# default target
all: $(LIB)

# creating directories for objects
$(LIB_OBJDIR):
	mkdir -p $(LIB_OBJDIR)

$(TEST_OBJDIR):
	mkdir -p $(TEST_OBJDIR)

# building static lib from obj files
$(LIB): $(LIB_OBJDIR) $(LIB_OBJ)
	ar rcs $@ $(LIB_OBJ)

# library object files
$(LIB_OBJDIR)/%.o: $(SRCDIR)/%.c | $(LIB_OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# test object files
$(TEST_OBJDIR)/%.o: $(TEST_DIR)/%.c | $(TEST_OBJDIR)
	$(CC) -std=c11 -Wall -Wextra -c $< -o $@

# build and run tests
test: $(LIB) $(TEST_OBJDIR) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(LIBLINK) -o $(TEST_EXEC) $(LDFLAGS)

# gcov_report target with rebuilding the library and tests with gcov flags
gcov_report: clean $(LIB_OBJDIR) $(TEST_OBJDIR)
	@$(MAKE) CFLAGS="$(CFLAGS_GCOV)" LDFLAGS="$(LDFLAGS_GCOV)" $(LIB)
	@$(MAKE) CFLAGS="$(CFLAGS_GCOV)" LDFLAGS="$(LDFLAGS_GCOV)" test
	./s21_string_test || true
	lcov -t "Report" -c -d ./ --output-file ./coverage.info
	genhtml ./coverage.info --output-directory ./report/

	@echo "\033[7;1;32m\t\t                      GCOV REPORT IS DONE                        \033[0m"


# clean target
clean:
	rm -rf *.o $(LIB_OBJDIR) $(TEST_OBJDIR) $(LIB) $(TEST_EXEC) *.gcda *.gcno ./report coverage.info

.PHONY: all clean test gcov_report
