# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/20 19:00:00 by mju-ferr          #+#    #+#              #
#    Updated: 2026/01/20 19:00:00 by mju-ferr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors for output
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I../includes -I../libft

# Directories
SRC_DIR = ../srcs
LIBFT_DIR = ../libft
OBJ_DIR = obj

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files to compile with tests
STACK_UTILS_SRC = $(SRC_DIR)/stack_utils.c $(SRC_DIR)/free.c
STACK_FIND_SRC = $(SRC_DIR)/stack_find.c $(SRC_DIR)/stack_utils.c $(SRC_DIR)/free.c
VALIDATE_SRC = $(SRC_DIR)/validate.c $(SRC_DIR)/stack_utils.c $(SRC_DIR)/free.c
OPERATIONS_SWAP_SRC = $(SRC_DIR)/operations_swap.c $(SRC_DIR)/stack_utils.c $(SRC_DIR)/free.c
OPERATIONS_PUSH_SRC = $(SRC_DIR)/operations_push.c $(SRC_DIR)/stack_utils.c $(SRC_DIR)/free.c
OPERATIONS_ROTATE_SRC = $(SRC_DIR)/operations_rotate.c $(SRC_DIR)/stack_utils.c $(SRC_DIR)/free.c
OPERATIONS_REVERSE_SRC = $(SRC_DIR)/operations_reverse.c $(SRC_DIR)/operations_rotate.c $(SRC_DIR)/stack_utils.c $(SRC_DIR)/free.c

# Test executables
TEST_STACK_UTILS = stack_utils_test
TEST_STACK_FIND = stack_find_test
TEST_VALIDATE = validate_test
TEST_OPS_SWAP = operations_swap_test
TEST_OPS_PUSH = operations_push_test
TEST_OPS_ROTATE = operations_rotate_test
TEST_OPS_REVERSE = operations_reverse_test

ALL_TESTS = $(TEST_STACK_UTILS) $(TEST_STACK_FIND) $(TEST_VALIDATE) \
			$(TEST_OPS_SWAP) $(TEST_OPS_PUSH) $(TEST_OPS_ROTATE) \
			$(TEST_OPS_REVERSE)

# Default target
all: $(LIBFT) $(ALL_TESTS)
	@echo "$(GREEN)All test executables built successfully!$(NC)"
	@echo "$(YELLOW)Run 'make test' to execute all tests$(NC)"

# Build libft
$(LIBFT):
	@echo "$(BLUE)Building libft...$(NC)"
	@make -C $(LIBFT_DIR)

# Test executables
$(TEST_STACK_UTILS): stack_utils_test.c $(STACK_UTILS_SRC) $(LIBFT)
	@echo "$(BLUE)Compiling $@...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) $< $(STACK_UTILS_SRC) $(LIBFT) -o $@

$(TEST_STACK_FIND): stack_find_test.c $(STACK_FIND_SRC) $(LIBFT)
	@echo "$(BLUE)Compiling $@...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) $< $(STACK_FIND_SRC) $(LIBFT) -o $@

$(TEST_VALIDATE): validate_test.c $(VALIDATE_SRC) $(LIBFT)
	@echo "$(BLUE)Compiling $@...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) $< $(VALIDATE_SRC) $(LIBFT) -o $@

$(TEST_OPS_SWAP): operations_swap_test.c $(OPERATIONS_SWAP_SRC) $(LIBFT)
	@echo "$(BLUE)Compiling $@...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) $< $(OPERATIONS_SWAP_SRC) $(LIBFT) -o $@

$(TEST_OPS_PUSH): operations_push_test.c $(OPERATIONS_PUSH_SRC) $(LIBFT)
	@echo "$(BLUE)Compiling $@...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) $< $(OPERATIONS_PUSH_SRC) $(LIBFT) -o $@

$(TEST_OPS_ROTATE): operations_rotate_test.c $(OPERATIONS_ROTATE_SRC) $(LIBFT)
	@echo "$(BLUE)Compiling $@...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) $< $(OPERATIONS_ROTATE_SRC) $(LIBFT) -o $@

$(TEST_OPS_REVERSE): operations_reverse_test.c $(OPERATIONS_REVERSE_SRC) $(LIBFT)
	@echo "$(BLUE)Compiling $@...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) $< $(OPERATIONS_REVERSE_SRC) $(LIBFT) -o $@

# Run all tests
test: all
	@echo "\n$(GREEN)========================================$(NC)"
	@echo "$(GREEN)       RUNNING ALL UNIT TESTS$(NC)"
	@echo "$(GREEN)========================================$(NC)\n"
	@failed=0; \
	for test in $(ALL_TESTS); do \
		echo "$(YELLOW)Running $$test...$(NC)"; \
		./$$test; \
		if [ $$? -ne 0 ]; then \
			failed=$$((failed + 1)); \
		fi; \
		echo ""; \
	done; \
	echo "$(GREEN)========================================$(NC)"; \
	if [ $$failed -eq 0 ]; then \
		echo "$(GREEN)✓ All test suites passed!$(NC)"; \
	else \
		echo "$(RED)✗ $$failed test suite(s) failed$(NC)"; \
	fi; \
	echo "$(GREEN)========================================$(NC)\n"

# Run individual tests
test_stack_utils: $(TEST_STACK_UTILS)
	@echo "$(YELLOW)Running stack_utils tests...$(NC)"
	@./$(TEST_STACK_UTILS)

test_stack_find: $(TEST_STACK_FIND)
	@echo "$(YELLOW)Running stack_find tests...$(NC)"
	@./$(TEST_STACK_FIND)

test_validate: $(TEST_VALIDATE)
	@echo "$(YELLOW)Running validate tests...$(NC)"
	@./$(TEST_VALIDATE)

test_swap: $(TEST_OPS_SWAP)
	@echo "$(YELLOW)Running operations_swap tests...$(NC)"
	@./$(TEST_OPS_SWAP)

test_push: $(TEST_OPS_PUSH)
	@echo "$(YELLOW)Running operations_push tests...$(NC)"
	@./$(TEST_OPS_PUSH)

test_rotate: $(TEST_OPS_ROTATE)
	@echo "$(YELLOW)Running operations_rotate tests...$(NC)"
	@./$(TEST_OPS_ROTATE)

test_reverse: $(TEST_OPS_REVERSE)
	@echo "$(YELLOW)Running operations_reverse tests...$(NC)"
	@./$(TEST_OPS_REVERSE)

# Valgrind checks
valgrind: all
	@echo "$(YELLOW)Running valgrind on all tests...$(NC)"
	@for test in $(ALL_TESTS); do \
		echo "\n$(BLUE)Checking $$test with valgrind...$(NC)"; \
		valgrind --leak-check=full --show-leak-kinds=all \
			--track-origins=yes --error-exitcode=1 ./$$test; \
	done

# Clean
clean:
	@echo "$(RED)Cleaning test executables...$(NC)"
	@rm -f $(ALL_TESTS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Full clean...$(NC)"
	@make -C $(LIBFT_DIR) fclean

re: fclean all

# Help
help:
	@echo "$(GREEN)Available targets:$(NC)"
	@echo "  $(YELLOW)make$(NC) or $(YELLOW)make all$(NC)     - Build all test executables"
	@echo "  $(YELLOW)make test$(NC)             - Run all tests"
	@echo "  $(YELLOW)make test_stack_utils$(NC) - Run stack_utils tests only"
	@echo "  $(YELLOW)make test_stack_find$(NC)  - Run stack_find tests only"
	@echo "  $(YELLOW)make test_validate$(NC)    - Run validate tests only"
	@echo "  $(YELLOW)make test_swap$(NC)        - Run operations_swap tests only"
	@echo "  $(YELLOW)make test_push$(NC)        - Run operations_push tests only"
	@echo "  $(YELLOW)make test_rotate$(NC)      - Run operations_rotate tests only"
	@echo "  $(YELLOW)make test_reverse$(NC)     - Run operations_reverse tests only"
	@echo "  $(YELLOW)make valgrind$(NC)         - Run all tests with valgrind"
	@echo "  $(YELLOW)make clean$(NC)            - Remove test executables"
	@echo "  $(YELLOW)make fclean$(NC)           - Remove all build files"
	@echo "  $(YELLOW)make re$(NC)               - Rebuild everything"

.PHONY: all test clean fclean re help valgrind \
		test_stack_utils test_stack_find test_validate \
		test_swap test_push test_rotate test_reverse
