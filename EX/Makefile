# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/14 10:51:10 by mju-ferr          #+#    #+#              #
#    Updated: 2026/01/14 10:51:47 by mju-ferr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#                                  COLORS                                      #
# ============================================================================ #

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# ============================================================================ #
#                                  NAMES                                       #
# ============================================================================ #

NAME = push_swap
BONUS_NAME = checker

# ============================================================================ #
#                                  PATHS                                       #
# ============================================================================ #

SRCS_DIR = srcs
BONUS_DIR = srcs_bonus
OBJS_DIR = objs
BONUS_OBJS_DIR = objs_bonus
INCLUDES_DIR = includes
LIBFT_DIR = libft

# ============================================================================ #
#                                  FILES                                       #
# ============================================================================ #

# Mandatory source files
SRCS = main.c \
       parser.c \
       error.c \
       stack_init.c \
       stack_utils.c \
       position.c \
       index.c \
       operations_swap.c \
       operations_push.c \
       operations_rotate.c \
       operations_reverse.c \
       sort_small.c \
       sort_large.c \
       cost.c \
       free.c

# Bonus source files (checker program)
BONUS_SRCS = checker_bonus.c \
             parser_bonus.c \
             error_bonus.c \
             stack_init_bonus.c \
             stack_utils_bonus.c \
             operations_swap_bonus.c \
             operations_push_bonus.c \
             operations_rotate_bonus.c \
             operations_reverse_bonus.c \
             free_bonus.c

# Object files
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(BONUS_OBJS_DIR)/, $(BONUS_SRCS:.c=.o))

# Dependency files (for automatic recompilation on header changes)
DEPS = $(OBJS:.o=.d)
BONUS_DEPS = $(BONUS_OBJS:.o=.d)

# ============================================================================ #
#                                  LIBRARIES                                   #
# ============================================================================ #

LIBFT = $(LIBFT_DIR)/libft.a

# ============================================================================ #
#                                  COMPILATION                                 #
# ============================================================================ #

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(INCLUDES_DIR) -I$(LIBFT_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft

# Dependency flags for automatic header tracking
DEPFLAGS = -MMD -MP

# ============================================================================ #
#                                  RULES                                       #
# ============================================================================ #

.PHONY: all clean fclean re bonus help

# Default target
all: $(NAME)

# Compile push_swap
# The $(NAME) rule depends on $(LIBFT) and $(OBJS)
# If any of these are newer than $(NAME), it will recompile
# If $(NAME) is up-to-date, it will NOT relink (prevents unnecessary relinking)
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(CYAN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

# Compile bonus checker
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS)
	@echo "$(CYAN)Linking $(BONUS_NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) -o $(BONUS_NAME)
	@echo "$(GREEN)✓ $(BONUS_NAME) compiled successfully!$(RESET)"

# Compile object files from source files (mandatory)
# This rule creates .o files in the objs/ directory
# The -MMD -MP flags generate .d dependency files automatically
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c $< -o $@

# Compile object files from source files (bonus)
$(BONUS_OBJS_DIR)/%.o: $(BONUS_DIR)/%.c | $(BONUS_OBJS_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c $< -o $@

# Create object directories if they don't exist
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(BONUS_OBJS_DIR):
	@mkdir -p $(BONUS_OBJS_DIR)

# Compile libft library
# The $(LIBFT) rule will only run if libft.a doesn't exist or if any
# libft source files are newer than libft.a
# This prevents unnecessary recompilation of libft
$(LIBFT):
	@echo "$(MAGENTA)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✓ libft compiled!$(RESET)"

# Clean object files and dependency files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@rm -rf $(OBJS_DIR) $(BONUS_OBJS_DIR)
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

# Clean everything (object files and executables)
fclean: clean
	@echo "$(RED)Cleaning executables...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(NAME) $(BONUS_NAME)
	@echo "$(GREEN)✓ All files cleaned!$(RESET)"

# Rebuild everything from scratch
re: fclean all

# Help message
help:
	@echo "$(CYAN)╔════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║           PUSH_SWAP MAKEFILE COMMANDS                  ║$(RESET)"
	@echo "$(CYAN)╚════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(GREEN)make$(RESET) or $(GREEN)make all$(RESET)"
	@echo "  └─ Compile the push_swap program"
	@echo ""
	@echo "$(GREEN)make bonus$(RESET)"
	@echo "  └─ Compile the checker program (bonus)"
	@echo ""
	@echo "$(GREEN)make clean$(RESET)"
	@echo "  └─ Remove object files (.o) and dependency files (.d)"
	@echo ""
	@echo "$(GREEN)make fclean$(RESET)"
	@echo "  └─ Remove object files and executables"
	@echo ""
	@echo "$(GREEN)make re$(RESET)"
	@echo "  └─ Rebuild everything from scratch (fclean + all)"
	@echo ""
	@echo "$(GREEN)make help$(RESET)"
	@echo "  └─ Display this help message"
	@echo ""
	@echo "$(YELLOW)Note: This Makefile prevents relinking!$(RESET)"
	@echo "  • If no files have changed, $(GREEN)make$(RESET) will do nothing"
	@echo "  • Only modified files will be recompiled"
	@echo ""

# ============================================================================ #
#                           DEPENDENCY MANAGEMENT                              #
# ============================================================================ #

# Include dependency files (automatically track header dependencies)
# The '-' prefix means make won't fail if .d files don't exist yet
-include $(DEPS)
-include $(BONUS_DEPS)

# ============================================================================ #
#                              ADDITIONAL INFO                                 #
# ============================================================================ #

# This Makefile is designed to prevent relinking:
#
# 1. Target Dependencies:
#    - $(NAME) depends on $(LIBFT) and $(OBJS)
#    - If these are up-to-date, make will not relink
#
# 2. Object File Dependencies:
#    - Each .o file depends on its corresponding .c file
#    - The -MMD -MP flags generate .d files that track header dependencies
#    - If a header changes, only affected .o files are recompiled
#
# 3. Libft Dependencies:
#    - $(LIBFT) target only runs if libft.a is missing or out-of-date
#    - Libft's own Makefile handles its internal dependencies
#
# 4. Testing No-Relink:
#    - Run 'make' twice in a row
#    - The second run should output: "make: Nothing to be done for 'all'."
#    - If any file is modified, only that file (and dependents) recompile
#
# 5. Timestamp Checking:
#    - Make compares timestamps of targets and prerequisites
#    - If target is newer than all prerequisites, it's up-to-date
#    - This is why touch, modification, or creation triggers recompilation
