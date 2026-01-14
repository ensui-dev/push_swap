*This project has been created as part of the 42 curriculum by mju-ferr.*

# Push_swap

## Description

**Push_swap** is a sorting algorithm project that challenges you to sort data in a stack using a limited set of instructions, with the goal of achieving the lowest possible number of operations.

The project provides two stacks (A and B) and 11 specific operations to manipulate them. Stack A starts with a random set of unique integers (positive and/or negative), while Stack B begins empty. The objective is to sort Stack A in ascending order with the smallest number on top.

This project is an exercise in algorithm complexity, optimization, and understanding different sorting strategies. You must choose and implement the most appropriate algorithms for different dataset sizes to meet strict performance benchmarks.

### Key Concepts:
- **Two stacks**: Stack A (initially filled with numbers) and Stack B (initially empty)
- **11 operations**: swap, push, rotate, and reverse rotate operations
- **Goal**: Sort Stack A in ascending order with minimum operations
- **Challenge**: Different algorithms perform better depending on the number of elements

---

## Instructions

### Compilation

To compile the mandatory part:
```bash
make
```

This will:
1. Compile your libft library (from the `libft/` directory)
2. Compile all source files
3. Create the `push_swap` executable

Other Makefile rules:
```bash
make clean     # Remove object files
make fclean    # Remove object files and executables
make re        # Rebuild everything from scratch
make bonus     # Compile the bonus checker program (if implemented)
```

### Usage

#### Basic Usage
```bash
./push_swap <numbers>
```

The program accepts integers as arguments (space-separated):
```bash
./push_swap 3 2 1 0
```

Or as a single quoted string:
```bash
./push_swap "3 2 1 0"
```

#### Output
The program outputs a series of operations to stdout, one per line:
```bash
$ ./push_swap 2 1 3
sa
```

If the stack is already sorted or no arguments are provided, no output is displayed.

#### Error Handling
In case of error, the program displays "Error" followed by a newline on stderr and exits:
```bash
$ ./push_swap 1 2 a
Error
$ ./push_swap 1 2 2
Error
```

Errors include:
- Non-integer arguments
- Integer overflow (values outside INT_MIN to INT_MAX range)
- Duplicate values

### Verification

You can verify the sorting using the provided checker (if implemented as bonus):
```bash
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker $ARG
```

The checker will output:
- `OK` if the operations correctly sort the stack
- `KO` if the stack is not sorted or Stack B is not empty
- `Error` if invalid operations or arguments

---

## Algorithm

This implementation uses a **hybrid approach** that selects the optimal algorithm based on the number of elements to sort:

### Small Numbers (2-5 elements)
**Hardcoded optimal solutions**

For very small sets, the most efficient approach is to use pre-determined optimal sequences:
- **2 numbers**: Maximum 1 operation (`sa` if needed)
- **3 numbers**: Maximum 2 operations (case analysis)
- **4 numbers**: ~8-10 operations (isolate minimum, sort 3, push back)
- **5 numbers**: ~12 operations (isolate 2 minimums, sort 3, push back)

These hardcoded solutions guarantee the absolute minimum number of operations.

### Medium to Large Numbers (6-500 elements)
**Turk/Chunk Algorithm with Cost Optimization**

For larger sets, the implementation uses a chunk-based algorithm with intelligent cost calculation:

1. **Index Normalization**
   - Map all values to normalized indices (0 to N-1)
   - Simplifies comparisons and algorithm logic
   - Maintains sorting relationships

2. **Chunking Strategy**
   - Divide the range into chunks based on size:
     - 100 elements: ~5 chunks (20 elements per chunk)
     - 500 elements: ~12-15 chunks (33-40 elements per chunk)
   - Push elements to Stack B in chunk order
   - Keep larger elements toward the top of Stack B

3. **Cost Calculation**
   - For each element in Stack B, calculate:
     - Cost to bring element to top of B
     - Cost to rotate Stack A to target position
     - Total cost = cost_a + cost_b
   - Consider both rotation directions (ra vs rra)
   - Use combined operations (rr, rrr) when both stacks rotate in same direction

4. **Greedy Selection**
   - Choose element with minimum total cost
   - Execute optimal sequence of operations
   - Push element from B to A at target position
   - Repeat until B is empty

5. **Final Rotation**
   - Rotate Stack A to position minimum at top
   - Stack is now sorted

### Optimization Techniques
- **Dual operations**: Use `rr` and `rrr` when both stacks need rotation
- **Direction selection**: Choose cheaper rotation direction (rotate vs reverse rotate)
- **Look-ahead**: Maintain partial ordering in Stack B during push phase
- **Cost minimization**: Always select the cheapest move at each step

---

## Performance

The algorithm meets the following benchmark requirements:

### Target Benchmarks (100% grade + bonus eligibility)
| Elements | Operations | Status |
|----------|-----------|--------|
| 3        | ≤ 3       | ✓ Met  |
| 5        | ≤ 12      | ✓ Met  |
| 100      | < 700     | ✓ Met  |
| 500      | ≤ 5500    | ✓ Met  |

### Minimum Benchmarks (80% grade)
Alternative acceptable combinations:
- 100 numbers: < 1100 ops AND 500 numbers: < 8500 ops
- 100 numbers: < 700 ops AND 500 numbers: < 11500 ops
- 100 numbers: < 1300 ops AND 500 numbers: < 5500 ops

### Testing Performance

To test with random numbers:
```bash
# Test 100 numbers
ARG=$(seq 1 100 | shuf | tr '\n' ' ')
./push_swap $ARG | wc -l

# Test 500 numbers
ARG=$(seq 1 500 | shuf | tr '\n' ' ')
./push_swap $ARG | wc -l
```

To verify correctness:
```bash
ARG=$(seq 1 100 | shuf | tr '\n' ' ')
./push_swap $ARG | ./checker_OS $ARG
# Should output: OK
```

---

## Project Structure

```
push_swap/
├── Makefile                    # Build configuration
├── README.md                   # This file
├── en.subject.pdf              # Project subject
├── includes/
│   ├── push_swap.h            # Main header file
│   └── push_swap_bonus.h      # Bonus header (if implemented)
├── srcs/
│   ├── main.c                 # Entry point and algorithm router
│   ├── parser.c               # Argument parsing and validation
│   ├── error.c                # Error handling
│   ├── stack_init.c           # Stack initialization
│   ├── stack_utils.c          # Stack utility functions
│   ├── position.c             # Position assignment
│   ├── index.c                # Index normalization
│   ├── operations_swap.c      # sa, sb, ss operations
│   ├── operations_push.c      # pa, pb operations
│   ├── operations_rotate.c    # ra, rb, rr operations
│   ├── operations_reverse.c   # rra, rrb, rrr operations
│   ├── sort_small.c           # Hardcoded sorts for ≤5 elements
│   ├── sort_large.c           # Chunk algorithm for large sets
│   ├── cost.c                 # Cost calculation and optimization
│   └── free.c                 # Memory cleanup
├── srcs_bonus/
│   ├── checker_bonus.c        # Bonus: operation validator
│   └── ...                    # Other bonus files
├── libft/
│   ├── Makefile               # Libft build configuration
│   ├── libft.h                # Libft header
│   └── *.c                    # Libft source files
└── org/
    ├── GETTING_STARTED.md     # Development guide
    ├── PROJECT_ANALYSIS.md    # Detailed requirements
    ├── TODO.md                # Implementation checklist
    └── LIBFT_VERIFICATION_REPORT.md
```

---

## Available Operations

The program can output the following operations:

### Swap Operations
- **sa**: Swap the first 2 elements at the top of Stack A
- **sb**: Swap the first 2 elements at the top of Stack B
- **ss**: Execute `sa` and `sb` simultaneously

### Push Operations
- **pa**: Take the top element from B and put it on top of A
- **pb**: Take the top element from A and put it on top of B

### Rotate Operations (shift up)
- **ra**: Shift all elements of Stack A up by 1 (first becomes last)
- **rb**: Shift all elements of Stack B up by 1 (first becomes last)
- **rr**: Execute `ra` and `rb` simultaneously

### Reverse Rotate Operations (shift down)
- **rra**: Shift all elements of Stack A down by 1 (last becomes first)
- **rrb**: Shift all elements of Stack B down by 1 (last becomes first)
- **rrr**: Execute `rra` and `rrb` simultaneously

---

## Technical Implementation

### Data Structure
The project uses a **linked list** implementation for the stacks:

```c
typedef struct s_stack
{
    int             value;       // Original value from input
    int             index;       // Normalized index (0 to N-1)
    int             pos;         // Current position in stack
    int             target_pos;  // Target position for optimization
    int             cost_a;      // Cost to move in Stack A
    int             cost_b;      // Cost to move in Stack B
    struct s_stack  *next;       // Pointer to next node
}   t_stack;
```

### Key Features
- **Dynamic memory allocation**: Efficient use of memory
- **O(1) push/pop operations**: Optimal for stack operations
- **Position tracking**: Enables cost calculation
- **Cost caching**: Stores movement costs for optimization

### Memory Management
- All heap-allocated memory is properly freed
- No memory leaks (verified with valgrind)
- Proper error handling with cleanup on failures
- Safe handling of malloc failures

### Compliance
- **42 Norm**: Fully compliant with the 42 coding standard
- **No global variables**: All state passed through function parameters
- **Function limits**: Maximum 25 lines per function, 4 parameters
- **Compilation flags**: `-Wall -Wextra -Werror`

---

## Resources

### Classic References

#### Sorting Algorithms
- [Wikipedia: Sorting Algorithm](https://en.wikipedia.org/wiki/Sorting_algorithm) - General overview of sorting algorithms and their complexities
- [GeeksforGeeks: Sorting Algorithms](https://www.geeksforgeeks.org/sorting-algorithms/) - Detailed explanations with examples
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/) - Algorithm complexity reference

#### Data Structures
- [Wikipedia: Stack (abstract data type)](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)) - Understanding stack operations
- [Linked List Tutorial](https://www.learn-c.org/en/Linked_lists) - Implementation in C

#### Algorithm Design
- [Khan Academy: Algorithms](https://www.khanacademy.org/computing/computer-science/algorithms) - Algorithm fundamentals
- [Visualgo](https://visualgo.net/en/sorting) - Algorithm visualization tool

### Project-Specific Resources
- [Push_swap Visualizer](https://github.com/o-reo/push_swap_visualizer) - Visual debugging tool
- [Push_swap Tester](https://github.com/lmalki-h/push_swap_tester) - Automated testing script
- 42 Intranet Project Page - Official requirements and checker program

### Development Tools
- **valgrind**: Memory leak detection (`valgrind --leak-check=full ./push_swap`)
- **norminette**: 42 Norm checker
- **gdb**: GNU debugger for C programs

---

## AI Usage Disclosure

### AI Tools Used
This project utilized AI assistance (Claude Code and ChatGPT) during development to enhance productivity and learning.

### Tasks Assisted by AI

#### Algorithm Research and Understanding
- Researching different sorting algorithms suitable for stack operations
- Understanding chunk-based sorting strategies
- Analyzing algorithm complexity and optimization techniques
- Comparing different approaches (Radix sort, Quick sort adapted, Chunk sort)

#### Code Structure and Planning
- Organizing project structure and file layout
- Creating implementation checklists and development roadmap
- Breaking down complex tasks into manageable steps
- Designing data structures for efficient operations

#### Debugging and Optimization
- Identifying potential edge cases and error scenarios
- Suggesting optimization strategies for benchmark improvement
- Reviewing cost calculation logic
- Analyzing memory management patterns

#### Documentation
- Generating comprehensive documentation structure
- Creating detailed README sections
- Writing clear explanations of algorithm approaches
- Organizing technical documentation

### Parts of Project Affected

#### Testing Strategy
- **Test cases**: AI suggested comprehensive test scenarios and edge cases
- **Benchmark scripts**: Assisted in creating automated testing scripts
- **Validation approach**: Helped design the testing and verification workflow

#### Optimization
- **Cost calculation**: AI provided insights on efficient cost calculation methods
- **Chunk sizing**: Assisted in determining optimal chunk sizes for different input sizes
- **Operation batching**: Suggested strategies for combining operations (rr, rrr, ss)

### Important Note
While AI assisted in research, planning, and initial code structure, **all final code was reviewed, understood, modified, and tested by the developer**. The developer takes full responsibility for the implementation and can explain every part of the codebase during evaluation. AI was used as a learning and productivity tool, not as a replacement for understanding.

---

## Author

**mju-ferr**
- 42 Network Student
- Project: Push_swap
- Version: 1.0

---

## License

This project is part of the 42 School curriculum. Code is provided for educational purposes.

---

## Acknowledgments

- 42 Network for the project design and learning framework
- Peers and the 42 community for discussions and peer learning
- Online resources and documentation for algorithm understanding
- AI tools for development assistance and documentation
