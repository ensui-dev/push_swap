# 42 Norm Quick Reference Checklist

## Function Rules

### Length and Structure
- [ ] **Max 25 lines per function** (including opening/closing braces)
- [ ] **Max 5 functions per file**
- [ ] **Max 4 parameters per function**
- [ ] Each function must have a prototype in header file
- [ ] Blank line between functions (mandatory)

### Variables
- [ ] All variables declared at top of function (before any code)
- [ ] One variable per line (no `int a, b, c;`)
- [ ] No variable declarations after code starts
- [ ] Variables must be initialized if used immediately

Example - CORRECT:
```c
int	ft_function(int a, int b)
{
	int		result;
	char	*str;

	result = 0;
	str = NULL;
	// ... code here ...
	return (result);
}
```

Example - WRONG:
```c
int	ft_function(int a, int b)
{
	int result = 0;  // WRONG: initialization on same line with declaration
	result = a + b;
	char *str;       // WRONG: declaration after code
	return (result);
}
```

## Control Structures

### Loop Rules
- [ ] **NO for loops allowed** (use while loops instead)
- [ ] Space after keyword (if, while, return)
- [ ] No space before opening parenthesis of function call

Example - CORRECT:
```c
while (stack)
{
	// code
	stack = stack->next;
}

if (value > 0)
	return (1);
```

Example - WRONG:
```c
for (int i = 0; i < n; i++)  // WRONG: for loop not allowed
{
	// code
}

if(value > 0)  // WRONG: no space after if
	return(1); // WRONG: no space after return
```

## Indentation and Spacing

### Tabs and Spaces
- [ ] Use **TABS** for indentation (not spaces)
- [ ] Each level of nesting = 1 tab
- [ ] Space after commas in parameter lists
- [ ] Space around operators (=, +, -, *, /, ==, !=, etc.)
- [ ] No space before semicolons
- [ ] No trailing whitespace

Example - CORRECT:
```c
int	calculate(int a, int b, int c)
{
	int	result;

	result = a + b * c;
	if (result > 100)
		result = 100;
	return (result);
}
```

### Braces
- [ ] Opening brace on same line for control structures
- [ ] Opening brace on next line for functions
- [ ] Always use braces for if/while (even for single statement)

Example - CORRECT:
```c
int	ft_example(void)
{
	if (condition)
	{
		do_something();
	}
	return (0);
}
```

## Naming Conventions

### Variables and Functions
- [ ] Use **snake_case** (lowercase with underscores)
- [ ] No camelCase
- [ ] Descriptive names (not single letters except for loop counters)
- [ ] Global variables start with `g_` (but avoid globals!)

Example - CORRECT:
```c
int		stack_size;
char	*temp_str;
void	free_stack(t_stack **stack);
```

Example - WRONG:
```c
int stackSize;      // WRONG: camelCase
char *s;            // WRONG: non-descriptive
void freeStk();     // WRONG: abbreviated
```

### Structures and Types
- [ ] Structures prefixed with `s_`
- [ ] Typedefs prefixed with `t_`
- [ ] Use typedef for structs

Example - CORRECT:
```c
typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;
```

## Header Files

### Structure
- [ ] Include guards (ifndef/define/endif)
- [ ] Include system headers first
- [ ] Include local headers after
- [ ] All function prototypes
- [ ] All structure definitions
- [ ] All macros/defines

Example - CORRECT:
```c
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
}	t_stack;

void	sa(t_stack **stack_a, int print);
void	sb(t_stack **stack_b, int print);
int		stack_size(t_stack *stack);

#endif
```

## Comments

### Allowed Comments
- [ ] `/* multi-line comments */` allowed
- [ ] `// single-line comments` allowed
- [ ] Use comments to explain complex logic
- [ ] Don't over-comment obvious code

Example - CORRECT:
```c
/*
** Calculate the cost to move element to top of stack
** Returns negative value for reverse rotate, positive for rotate
*/
int	calculate_cost(t_stack *stack, int position)
{
	int	size;

	size = stack_size(stack);
	if (position <= size / 2)
		return (position);  // Rotate forward
	return (position - size);  // Reverse rotate (negative)
}
```

## Forbidden

### Absolutely Not Allowed
- [ ] **Global variables** (except in very specific cases with g_ prefix)
- [ ] **For loops** (use while instead)
- [ ] **Switch statements** (use if-else)
- [ ] **Ternary operators** `? :` (use if-else)
- [ ] **Goto statements**
- [ ] **Variable-length arrays (VLA)**
- [ ] **Functions with more than 4 parameters**
- [ ] **Functions longer than 25 lines**

### Memory Rules
- [ ] Every `malloc()` must have a corresponding `free()`
- [ ] No memory leaks allowed
- [ ] Check malloc return value (handle NULL)
- [ ] No double free
- [ ] No use after free

## Makefile

### Required Rules
- [ ] `NAME` - name of executable
- [ ] `all` - compile everything
- [ ] `clean` - remove .o files
- [ ] `fclean` - remove .o and executable
- [ ] `re` - recompile everything (fclean + all)
- [ ] `bonus` - compile bonus part (if applicable)

### Compilation
- [ ] Use `cc` compiler
- [ ] Flags: `-Wall -Wextra -Werror`
- [ ] Must not relink (compile only changed files)
- [ ] Properly handle dependencies

Example - CORRECT:
```makefile
NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c srcs/parser.c srcs/stack_ops.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

## Common Norm Violations to Avoid

### Top 10 Mistakes
1. **Function too long** - Split into smaller functions
2. **More than 4 parameters** - Use struct to group parameters
3. **For loops** - Replace with while loops
4. **Variables declared mid-function** - Move to top
5. **Missing spaces after keywords** - Add spaces: `if (x)` not `if(x)`
6. **Wrong indentation** - Use tabs, not spaces
7. **CamelCase names** - Use snake_case
8. **Missing blank line between functions** - Add blank line
9. **More than 5 functions per file** - Split file
10. **Global variables** - Avoid or use g_ prefix and document why needed

## Verification Commands

### Run These Before Submission
```bash
# Check norm compliance
norminette includes/
norminette srcs/
norminette srcs_bonus/  # if you have bonus

# Check for memory leaks
valgrind --leak-check=full --show-leak-kinds=all ./push_swap 4 2 1 3

# Check compilation
make re
make clean
make fclean
make all

# Check bonus
make bonus
make fclean
make bonus  # should not recompile unnecessarily
```

## Quick Fixes

### If Function is Too Long
Split into helper functions:
```c
// BEFORE - 30 lines (too long)
void	sort_stack(t_stack **a, t_stack **b)
{
	// ... 30 lines of code
}

// AFTER - split into helpers
void	sort_stack(t_stack **a, t_stack **b)
{
	push_to_b(a, b);
	sort_remaining(a);
	push_back_to_a(a, b);
}

static void	push_to_b(t_stack **a, t_stack **b)
{
	// ... implementation
}
```

### If Too Many Parameters
Use a structure:
```c
// BEFORE - 5 parameters (too many)
void	do_something(int a, int b, int c, int d, int e)

// AFTER - use struct
typedef struct s_params
{
	int	a;
	int	b;
	int	c;
	int	d;
	int	e;
}	t_params;

void	do_something(t_params *params)
```

### If For Loop Present
Convert to while:
```c
// BEFORE - for loop (not allowed)
for (int i = 0; i < n; i++)
{
	array[i] = 0;
}

// AFTER - while loop
int	i;

i = 0;
while (i < n)
{
	array[i] = 0;
	i++;
}
```

## Final Checklist Before Submission

- [ ] Run norminette on all files - 0 errors
- [ ] Run valgrind - 0 leaks
- [ ] Compile with all flags - 0 warnings
- [ ] Test Makefile rules (all, clean, fclean, re, bonus)
- [ ] Test with various inputs
- [ ] Test error cases
- [ ] Read through code one final time
- [ ] Ensure no global variables (unless absolutely necessary)
- [ ] Ensure no forbidden functions used
- [ ] Ensure all functions have prototypes
- [ ] Ensure all includes in header file

---

**Remember**: The norm is strict but exists to teach good coding habits. Following it makes your code cleaner and more maintainable!

**Tip**: Set up your editor to use tabs for indentation and show whitespace characters to avoid invisible errors.
