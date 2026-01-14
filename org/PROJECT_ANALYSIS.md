# Push_swap Project - Detailed Analysis

## Project Overview
**Goal**: Sort data in a stack using a limited set of instructions with the lowest possible number of actions.

**Program Name**: push_swap
**Language**: C
**Compliance**: 42 Norm (MANDATORY)

---

## Core Concepts

### 1. Data Structures
- **Two Stacks**: Stack A and Stack B
- **Stack A**: Contains random unique integers (negative/positive) at start
- **Stack B**: Empty at start
- **Goal**: Sort Stack A in ascending order (smallest on top)

### 2. Available Operations

#### Swap Operations
- `sa`: Swap first 2 elements of stack A (no-op if ≤1 element)
- `sb`: Swap first 2 elements of stack B (no-op if ≤1 element)
- `ss`: Execute sa and sb simultaneously

#### Push Operations
- `pa`: Take top element from B, put on top of A (no-op if B empty)
- `pb`: Take top element from A, put on top of B (no-op if A empty)

#### Rotate Operations (shift up)
- `ra`: Shift all elements of A up by 1 (first → last)
- `rb`: Shift all elements of B up by 1 (first → last)
- `rr`: Execute ra and rb simultaneously

#### Reverse Rotate Operations (shift down)
- `rra`: Shift all elements of A down by 1 (last → first)
- `rrb`: Shift all elements of B down by 1 (last → first)
- `rrr`: Execute rra and rrb simultaneously

---

## Requirements

### Mandatory Part

#### Input Validation
- Accept integers as command-line arguments
- First argument = top of stack
- Handle errors:
  - Non-integer arguments
  - Integer overflow (outside INT_MIN to INT_MAX)
  - Duplicate values
  - Display "Error\n" to stderr on error

#### Output
- Print sequence of operations separated by '\n'
- No output if already sorted or no arguments
- Must be shortest/optimal sequence

#### Performance Benchmarks (CRITICAL)

**For 100% + Bonus Eligibility:**
- 3 numbers: ≤ 3 operations
- 5 numbers: ≤ 12 operations
- 100 numbers: < 700 operations
- 500 numbers: ≤ 5500 operations

**For 80% (Minimum Pass):**
Various combinations like:
- 100 numbers: < 1100 ops AND 500 numbers: < 8500 ops
- 100 numbers: < 700 ops AND 500 numbers: < 11500 ops
- 100 numbers: < 1300 ops AND 500 numbers: < 5500 ops

### Bonus Part (Optional)
**Program Name**: checker
**Purpose**: Verify if a sequence of operations sorts the stack

- Read operations from stdin
- Execute operations on provided stack
- Output "OK\n" if sorted correctly, "KO\n" otherwise
- Handle same errors as push_swap

**NOTE**: Bonus only evaluated if ALL mandatory benchmarks achieve maximum score

---

## Technical Constraints (42 Norm)

### Code Standards
- Functions ≤ 25 lines
- Maximum 4 parameters per function
- Maximum 5 functions per file
- No global variables
- No for loops (use while)
- No variable declarations in middle of function
- One variable declaration per line
- Blank line between functions
- Functions must have prototypes

### Memory Management
- No memory leaks (all malloc must be freed)
- No segfaults, bus errors, double frees
- Proper error handling

### Compilation
- Makefile required with: `NAME`, `all`, `clean`, `fclean`, `re`
- Flags: `-Wall -Wextra -Werror`
- No relinking
- Bonus rule: `bonus` (compiles bonus files with `_bonus.{c/h}` suffix)

### Allowed Functions
- `read`, `write`, `malloc`, `free`, `exit`
- `ft_printf` or equivalent (self-coded)
- libft is authorized

---

## Algorithm Complexity Analysis

### Small Sets (2-5 numbers)
- Hardcoded/optimized solutions
- Manual case handling
- O(1) instructions

### Medium Sets (6-100 numbers)
- Need efficient algorithm
- Target: < 700 operations for 100 numbers
- Algorithms: Quick Sort adapted, Chunk/Bucket Sort, Radix Sort

### Large Sets (100-500 numbers)
- Must scale efficiently
- Target: ≤ 5500 operations for 500 numbers
- Best: Radix Sort, Optimized Chunk Sort

---

## Key Implementation Considerations

### 1. Stack Representation
- Linked list (dynamic, efficient push/pop)
- Array (contiguous memory, but fixed size)

### 2. Index/Value Mapping
- Normalize values to indices (0 to N-1)
- Simplifies algorithmic logic
- Maintains sorting order

### 3. Optimization Strategies
- Use dual operations (ss, rr, rrr) when possible
- Calculate rotation cost (forward vs reverse)
- Look-ahead optimization
- Minimize moves between stacks

### 4. Testing Strategy
- Test small sets (2, 3, 5 numbers)
- Test medium sets (10, 50, 100 numbers)
- Test large sets (500 numbers)
- Edge cases: sorted, reverse sorted, random
- Validate with checker program

---

## Common Pitfalls to Avoid

1. **Integer Overflow**: Use `atol()` or equivalent, validate range
2. **Memory Leaks**: Free all allocated memory on error/exit
3. **Off-by-one Errors**: Careful with stack indices
4. **Norm Violations**: Function length, parameter count, formatting
5. **Edge Cases**: Empty input, single element, already sorted
6. **Inefficient Algorithm**: Won't pass benchmarks
7. **Global Variables**: Not allowed in 42 Norm

---

## README.md Requirements

Must include:
1. Italicized first line: "This project has been created as part of the 42 curriculum by <login>."
2. **Description**: Project goal and overview
3. **Instructions**: Compilation, installation, execution
4. **Resources**: Documentation, articles, AI usage disclosure

---

## Project Structure Suggestion

```
push_swap/
├── Makefile
├── README.md
├── PROJECT_ANALYSIS.md
├── includes/
│   ├── push_swap.h
│   └── push_swap_bonus.h
├── srcs/
│   ├── main.c
│   ├── parser.c
│   ├── error.c
│   ├── stack_init.c
│   ├── stack_operations_push.c
│   ├── stack_operations_swap.c
│   ├── stack_operations_rotate.c
│   ├── stack_operations_reverse_rotate.c
│   ├── sort_small.c
│   ├── sort_large.c
│   ├── algorithm.c
│   ├── utils.c
│   └── free.c
├── srcs_bonus/
│   ├── checker_bonus.c
│   ├── parser_bonus.c
│   ├── operations_bonus.c
│   └── utils_bonus.c
└── libft/
    └── (your libft files)
```

---

## Evaluation Criteria

1. **Norm Compliance**: Must be 100% norm-compliant
2. **Compilation**: No warnings, proper Makefile
3. **Functionality**: Correct sorting
4. **Performance**: Meet benchmark requirements
5. **Error Handling**: Proper error messages
6. **Memory**: No leaks, no crashes
7. **Code Quality**: Clean, readable, modular
8. **Bonus**: Only if mandatory is perfect

---

## Next Steps

1. Choose sorting algorithm (see algorithm comparison)
2. Implement stack data structure
3. Implement all stack operations
4. Implement parser and validation
5. Implement sorting algorithm
6. Optimize for benchmarks
7. Test thoroughly
8. Implement bonus (if mandatory perfect)
