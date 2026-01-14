# Push_swap - Detailed TODO Checklist

**Algorithm Choice**: Hybrid Approach (Hardcoded small + Turk/Chunk medium + Optimized large)
**Data Structure**: Linked List
**Optimization**: Index Normalization

---

## Phase 0: Project Setup and Planning

### 0.1 Repository and Structure Setup
- [x] Create project directory structure
  - [x] Create `includes/` directory
  - [x] Create `srcs/` directory
  - [x] Create `srcs_bonus/` directory (for bonus)
  - [x] Create `libft/` directory (copy your libft)
  - [x] Create `Makefile` at root
  - [x] Create `README.md` at root

### 0.2 Makefile Creation
- [x] Write Makefile with required rules
  - [x] `NAME = push_swap` variable
  - [x] `all` rule (compiles push_swap)
  - [x] `clean` rule (removes .o files)
  - [x] `fclean` rule (removes .o and binary)
  - [x] `re` rule (fclean + all)
  - [x] `bonus` rule (compiles checker)
  - [x] Compile libft first using its Makefile
  - [x] Use flags: `-Wall -Wextra -Werror`
  - [x] Use `cc` compiler
  - [x] Prevent relinking (check if files changed)
  - [x] Test that `make` works without errors
  - [x] Test that `make clean` removes only .o files
  - [x] Test that `make fclean` removes everything
  - [x] Test that `make re` rebuilds properly
  - [x] Verify no relinking occurs on second `make`

### 0.3 Header File Setup
- [x] Create `includes/push_swap.h`
  - [x] Add include guards (`#ifndef PUSH_SWAP_H`)
  - [x] Include necessary system headers (`<unistd.h>`, `<stdlib.h>`)
  - [x] Include libft header (`"../libft/libft.h"`)
  - [x] Add structure definitions (forward declare)
  - [x] Add all function prototypes (will expand as you code)
  - [x] Add any necessary macros (INT_MAX, INT_MIN, TRUE, FALSE, ERROR)
  - [x] Close include guard (`#endif`)

---

## Phase 1: Core Data Structures

### 1.1 Stack Node Structure
- [x] Define `t_stack` structure in header
  ```c
  typedef struct s_stack
  {
      int value;              // Original value from input
      int index;              // Normalized index (0 to N-1)
      int pos;                // Current position in stack
      int target_pos;         // Target position for optimization
      int cost_a;             // Cost to move in stack A
      int cost_b;             // Cost to move in stack B
      struct s_stack *next;   // Pointer to next node
  }   t_stack;
  ```
- [x] Verify structure follows 42 Norm (no tabs, proper indentation)

### 1.2 Stack Utility Functions - Basic Operations
**File:** `srcs/stack_utils.c` (5 functions - 42 Norm max per file)

- [x] Create `srcs/stack_utils.c`
  - [x] Write `stack_new(int value)` function
    - [x] Allocate memory with `malloc(sizeof(t_stack))`
    - [x] Initialize all fields (value, index=-1, pos=0, costs=0)
    - [x] Set `next` to NULL
    - [x] Return new node
    - [x] Handle malloc failure (return NULL)

  - [x] Write `stack_size(t_stack *stack)` function
    - [x] Count nodes in linked list
    - [x] Return 0 if stack is NULL
    - [x] Use while loop (no for loops - 42 Norm)
    - [x] Return total count

  - [x] Write `stack_last(t_stack *stack)` function
    - [x] Traverse to last node
    - [x] Return NULL if stack is NULL
    - [x] Return pointer to last node

  - [x] Write `stack_add_back(t_stack **stack, t_stack *new)` function
    - [x] If stack is empty, set *stack = new
    - [x] Else find last node and link: `last->next = new`
    - [x] **Proper linking explained**: Must set `last->next = new` to connect nodes
    - [x] Without linking: node is orphaned → memory leak + traversal breaks

  - [x] Write `stack_add_front(t_stack **stack, t_stack *new)` function
    - [x] Set new->next to current *stack
    - [x] Set *stack to new
    - [x] **Push operations**: This O(1) pattern is core logic of pa/pb

### 1.3 Stack Utility Functions - Search Operations
**File:** `srcs/stack_find.c` (5 functions - new file for 42 Norm compliance)

- [x] Create `srcs/stack_find.c`
  - [x] Write `find_min(t_stack *stack)` function
    - [x] Return minimum value in stack
    - [x] Iterate through all nodes
    - [x] Track minimum value
    - [x] Return min value

  - [x] Write `find_max(t_stack *stack)` function
    - [x] Return maximum value in stack
    - [x] Similar to find_min

  - [x] Write `find_min_index(t_stack *stack)` function
    - [x] Return minimum index in stack
    - [x] Useful for index-based operations

  - [x] Write `find_max_index(t_stack *stack)` function
    - [x] Return maximum index in stack

  - [x] Write `is_sorted(t_stack *stack)` function
    - [x] Check if stack is sorted in ascending order
    - [x] Compare each node with next
    - [x] Return 1 (TRUE) if sorted, 0 (FALSE) otherwise
    - [x] Return 1 if stack is empty or has 1 element

### 1.4 Position Assignment
- [x] Create `srcs/position.c`
  - [x] Write `assign_position(t_stack *stack)` function
    - [x] Iterate through stack
    - [x] Assign current position to each node (0, 1, 2...)
    - [x] Store in `pos` field of each node
    - [x] Needed for cost calculation

---

## Phase 2: Input Parsing and Validation

### 2.1 Argument Parsing
- [x] Create `srcs/parser.c`
  - [x] Write `count_total_numbers(int argc, char **argv)` helper function (static)
    - [x] Iterate through all arguments (argv[1] to argv[argc-1])
    - [x] Split each argument by spaces using `ft_split()`
    - [x] Count total numbers across all split results
    - [x] Free temporary split arrays after counting
    - [x] Return total count or -1 on error
    - [x] Handles single strings, multiple args, and mixed formats

  - [ ] Write `join_all_arguments(int argc, char **argv, int total)` helper function (static)
    - [ ] Allocate result array for (total + 1) pointers
    - [ ] Iterate through all arguments
    - [ ] Split each argument by spaces
    - [ ] Transfer string pointers from split to result (ownership transfer)
    - [ ] Free only temp array structure (not strings - transferred)
    - [ ] NULL-terminate result array
    - [ ] Return combined array or NULL on error

  - [ ] Write `parse_arguments(int argc, char **argv)` main function
    - [ ] Handle case: no arguments (argc < 2, return NULL)
    - [ ] Call `count_total_numbers()` to get total count
    - [ ] Validate count > 0
    - [ ] Call `join_all_arguments()` to build result array
    - [ ] Return unified array of number strings (ALWAYS allocated)
    - [ ] **NEW:** Supports mixed formats like `./push_swap "2 4" 91 10`
    - [ ] **NEW:** Consistent memory management (always allocates)
    - [ ] Memory: Caller MUST free with free_split() - no argc checks needed

### 2.2 Number Validation
- [ ] Add to `srcs/parser.c`
  - [ ] Write `is_valid_number(char *str)` function
    - [ ] Check if string represents valid integer
    - [ ] Handle signs ('+', '-')
    - [ ] Check all characters are digits
    - [ ] Handle leading zeros
    - [ ] Return 1 if valid, 0 if invalid

  - [ ] Write `ft_atol(char *str)` function
    - [ ] Convert string to long (to check overflow)
    - [ ] Handle signs
    - [ ] Parse digit by digit
    - [ ] Return long value

  - [ ] Write `is_int_range(long num)` function
    - [ ] Check if num is within INT_MIN and INT_MAX
    - [ ] Return 1 if valid, 0 if overflow

### 2.3 Duplicate Detection
- [ ] Add to `srcs/parser.c`
  - [ ] Write `has_duplicates(t_stack *stack)` function
    - [ ] Compare each node with all other nodes
    - [ ] Check for duplicate values
    - [ ] Return 1 if duplicates found, 0 otherwise
    - [ ] Use nested while loops (no for loops - 42 Norm)

### 2.4 Stack Initialization
- [ ] Create `srcs/stack_init.c`
  - [ ] Write `init_stack_a(char **numbers)` function
    - [ ] **UPDATED SIGNATURE:** Now takes `char **numbers` (already parsed)
    - [ ] Main() calls parse_arguments and passes result to this function
    - [ ] Validate each number string:
      - [ ] Check if valid number format (is_valid_number)
      - [ ] Convert to long (ft_atol)
      - [ ] Check if within int range (is_int_range)
    - [ ] Create stack node for each valid number
    - [ ] Add node to stack A (stack_add_back)
    - [ ] Check for duplicates (has_duplicates)
    - [ ] Return stack A or NULL on error
    - [ ] **IMPORTANT:** Does NOT free numbers array (caller's responsibility)

---

## Phase 3: Error Handling and Memory Management

### 3.1 Error Handling
- [ ] Create `srcs/error.c`
  - [ ] Write `print_error()` function
    - [ ] Write "Error\n" to stderr (fd = 2)
    - [ ] Use `write(2, "Error\n", 6)`

  - [ ] Write `error_exit(t_stack **stack_a, t_stack **stack_b)` function
    - [ ] Call print_error()
    - [ ] Free stack A if allocated
    - [ ] Free stack B if allocated
    - [ ] Exit program with `exit(1)`

### 3.2 Memory Cleanup
- [ ] Create `srcs/free.c`
  - [ ] Write `free_stack(t_stack **stack)` function
    - [ ] Iterate through entire stack
    - [ ] Free each node
    - [ ] Set *stack to NULL after freeing all
    - [ ] Handle NULL pointer (do nothing)

  - [x] Write `free_split(char **split)` function
    - [x] Free each string in split array
    - [x] Free the array itself
    - [x] Needed if using ft_split for parsing

---

## Phase 4: Stack Operations Implementation

### 4.1 Swap Operations
- [ ] Create `srcs/operations_swap.c`
  - [ ] Write `sa(t_stack **stack_a, int print)` function
    - [ ] Swap first two elements of stack A
    - [ ] Handle edge cases (NULL, 1 element)
    - [ ] If print=1, write "sa\n" to stdout
    - [ ] Implementation:
      - [ ] Save first node (head)
      - [ ] Save second node (head->next)
      - [ ] Set head->next to second->next
      - [ ] Set second->next to head
      - [ ] Update stack head to second

  - [ ] Write `sb(t_stack **stack_b, int print)` function
    - [ ] Same as sa but for stack B
    - [ ] If print=1, write "sb\n" to stdout

  - [ ] Write `ss(t_stack **stack_a, t_stack **stack_b, int print)` function
    - [ ] Call sa with print=0
    - [ ] Call sb with print=0
    - [ ] If print=1, write "ss\n" to stdout

### 4.2 Push Operations
- [ ] Create `srcs/operations_push.c`
  - [ ] Write `pa(t_stack **stack_a, t_stack **stack_b, int print)` function
    - [ ] Take top element from B, push to A
    - [ ] Handle edge case (B is empty - do nothing)
    - [ ] If print=1, write "pa\n" to stdout
    - [ ] Implementation:
      - [ ] Save top of B
      - [ ] Remove top from B (update head)
      - [ ] Add saved node to top of A

  - [ ] Write `pb(t_stack **stack_a, t_stack **stack_b, int print)` function
    - [ ] Take top element from A, push to B
    - [ ] Handle edge case (A is empty - do nothing)
    - [ ] If print=1, write "pb\n" to stdout

### 4.3 Rotate Operations
- [ ] Create `srcs/operations_rotate.c`
  - [ ] Write `ra(t_stack **stack_a, int print)` function
    - [ ] Shift all elements up by 1 (first becomes last)
    - [ ] Handle edge cases (NULL, 1 element)
    - [ ] If print=1, write "ra\n" to stdout
    - [ ] Implementation:
      - [ ] Save first node
      - [ ] Update head to second node
      - [ ] Find last node
      - [ ] Attach saved first node to end
      - [ ] Set its next to NULL

  - [ ] Write `rb(t_stack **stack_b, int print)` function
    - [ ] Same as ra but for stack B
    - [ ] If print=1, write "rb\n" to stdout

  - [ ] Write `rr(t_stack **stack_a, t_stack **stack_b, int print)` function
    - [ ] Call ra with print=0
    - [ ] Call rb with print=0
    - [ ] If print=1, write "rr\n" to stdout

### 4.4 Reverse Rotate Operations
- [ ] Create `srcs/operations_reverse_rotate.c`
  - [ ] Write `rra(t_stack **stack_a, int print)` function
    - [ ] Shift all elements down by 1 (last becomes first)
    - [ ] Handle edge cases (NULL, 1 element)
    - [ ] If print=1, write "rra\n" to stdout
    - [ ] Implementation:
      - [ ] Find last node
      - [ ] Find second-to-last node
      - [ ] Detach last node (set second-to-last next to NULL)
      - [ ] Attach last node to beginning
      - [ ] Update head to last node

  - [ ] Write `rrb(t_stack **stack_b, int print)` function
    - [ ] Same as rra but for stack B
    - [ ] If print=1, write "rrb\n" to stdout

  - [ ] Write `rrr(t_stack **stack_a, t_stack **stack_b, int print)` function
    - [ ] Call rra with print=0
    - [ ] Call rrb with print=0
    - [ ] If print=1, write "rrr\n" to stdout

### 4.5 Operation Testing
- [ ] Test each operation individually
  - [ ] Create test stack with known values
  - [ ] Execute operation
  - [ ] Verify stack state manually
  - [ ] Test edge cases for each operation

---

## Phase 5: Index Normalization (Optimization)

### 5.1 Index Mapping Implementation
- [ ] Create `srcs/index.c`
  - [ ] Write `assign_index(t_stack *stack_a)` function
    - [ ] Create array to store values
    - [ ] Copy all values from stack to array
    - [ ] Sort array in ascending order (use simple sorting)
    - [ ] Assign indices: smallest value gets index 0, next gets 1, etc.
    - [ ] Iterate through stack and assign corresponding index to each node
    - [ ] Free temporary array
    - [ ] Purpose: normalize values to 0...N-1 range

  - [ ] Write `get_index_position(int value, int *sorted_arr, int size)` function
    - [ ] Binary search or linear search to find value in sorted array
    - [ ] Return index position

  - [ ] Write `copy_values_to_array(t_stack *stack, int **arr)` function
    - [ ] Allocate array of size stack_size
    - [ ] Copy each value from stack to array
    - [ ] Return array

### 5.2 Array Sorting Helper
- [ ] Add to `srcs/index.c`
  - [ ] Write `sort_int_array(int *arr, int size)` function
    - [ ] Use simple sorting (bubble sort is fine for this purpose)
    - [ ] Sort array in ascending order
    - [ ] This is not the stack sorting - just helper for index assignment

---

## Phase 6: Small Number Sorting (Hardcoded Solutions)

### 6.1 Two Numbers
- [ ] Create `srcs/sort_small.c`
  - [ ] Write `sort_two(t_stack **stack_a)` function
    - [ ] If first > second, execute sa
    - [ ] Else already sorted, do nothing
    - [ ] Total operations: 0-1

### 6.2 Three Numbers (Optimal)
- [ ] Add to `srcs/sort_small.c`
  - [ ] Write `sort_three(t_stack **stack_a)` function
    - [ ] Identify positions of min, max, and middle values
    - [ ] Use optimal case analysis:
      - [ ] Case 1: [3,2,1] → sa + rra (or ra + sa)
      - [ ] Case 2: [2,3,1] → rra
      - [ ] Case 3: [3,1,2] → ra
      - [ ] Case 4: [1,3,2] → sa + ra (or rra + sa)
      - [ ] Case 5: [2,1,3] → sa
      - [ ] Case 6: [1,2,3] → nothing (sorted)
    - [ ] Maximum 2 operations for any configuration

### 6.3 Four Numbers
- [ ] Add to `srcs/sort_small.c`
  - [ ] Write `sort_four(t_stack **stack_a, t_stack **stack_b)` function
    - [ ] Find smallest element
    - [ ] Rotate/reverse rotate to bring it to top (choose cheaper direction)
    - [ ] Push smallest to B (pb)
    - [ ] Sort remaining 3 with sort_three
    - [ ] Push smallest back to A (pa)
    - [ ] Maximum operations: ~8-10

### 6.4 Five Numbers
- [ ] Add to `srcs/sort_small.c`
  - [ ] Write `sort_five(t_stack **stack_a, t_stack **stack_b)` function
    - [ ] Find smallest element, push to B
    - [ ] Find second smallest, push to B
    - [ ] Sort remaining 3 with sort_three
    - [ ] Push back both elements from B to A (pa, pa)
    - [ ] Maximum operations: ~12

### 6.5 Small Sort Router
- [ ] Add to `srcs/sort_small.c`
  - [ ] Write `sort_small(t_stack **stack_a, t_stack **stack_b)` function
    - [ ] Get stack size
    - [ ] If size == 2, call sort_two
    - [ ] If size == 3, call sort_three
    - [ ] If size == 4, call sort_four
    - [ ] If size == 5, call sort_five
    - [ ] Return after sorting

---

## Phase 7: Large Number Sorting - Turk/Chunk Algorithm

### 7.1 Chunk/Partition Strategy
- [ ] Create `srcs/sort_large.c`
  - [ ] Write `push_chunks_to_b(t_stack **stack_a, t_stack **stack_b, int size)` function
    - [ ] Determine chunk size based on total size
      - [ ] For 100 elements: ~20 chunks (5 per chunk)
      - [ ] For 500 elements: ~35 chunks (~14 per chunk)
    - [ ] Calculate number of chunks
    - [ ] Push elements to B in chunks based on index:
      - [ ] For each chunk range:
        - [ ] Find elements in stack A within current chunk index range
        - [ ] Rotate/reverse rotate to bring element to top (cheaper option)
        - [ ] Push to B (pb)
        - [ ] Rotate B intelligently to keep larger elements on top
    - [ ] Continue until all elements (except ~3 smallest) are in B

### 7.2 Cost Calculation
- [ ] Create `srcs/cost.c`
  - [ ] Write `calculate_cost(t_stack *stack_a, t_stack *stack_b)` function
    - [ ] Assign positions to both stacks
    - [ ] For each element in B:
      - [ ] Find target position in A (where it should be inserted)
      - [ ] Calculate cost to bring element to top of B
      - [ ] Calculate cost to rotate A to target position
      - [ ] Store both costs in node

  - [ ] Write `find_target_position(t_stack *stack_a, int index_b)` function
    - [ ] Find position in A where element from B should be inserted
    - [ ] Find smallest element in A that is larger than index_b
    - [ ] If none found, target is position of smallest element
    - [ ] Return target position

  - [ ] Write `calculate_move_cost(t_stack *stack, int target_pos)` function
    - [ ] Calculate cost to move element to top
    - [ ] Compare rotate cost vs reverse rotate cost
    - [ ] Return cheaper cost (and direction)

### 7.3 Cheapest Element Selection
- [ ] Add to `srcs/cost.c`
  - [ ] Write `find_cheapest(t_stack *stack_b)` function
    - [ ] Calculate total cost for each element (cost_a + cost_b)
    - [ ] Find element with minimum total cost
    - [ ] Return pointer to cheapest element

  - [ ] Write `execute_cheapest_move(t_stack **a, t_stack **b, t_stack *cheapest)` function
    - [ ] Get costs from cheapest element
    - [ ] Execute optimal moves:
      - [ ] If both costs positive (both rotate): use rr
      - [ ] If both costs negative (both reverse rotate): use rrr
      - [ ] If mixed: execute independently
    - [ ] Bring element to top of B
    - [ ] Rotate A to target position
    - [ ] Execute pa to push to A

### 7.4 Main Large Sort Function
- [ ] Add to `srcs/sort_large.c`
  - [ ] Write `sort_large(t_stack **stack_a, t_stack **stack_b)` function
    - [ ] Push chunks to B using push_chunks_to_b
    - [ ] While B is not empty:
      - [ ] Calculate costs for all elements in B
      - [ ] Find cheapest element
      - [ ] Execute cheapest move
      - [ ] Push element from B to A at target position
    - [ ] Final rotation to ensure smallest element is on top

  - [ ] Write `final_rotate(t_stack **stack_a)` function
    - [ ] Find position of minimum element
    - [ ] Rotate or reverse rotate to bring it to top
    - [ ] Choose cheaper direction

---

## Phase 8: Main Program and Algorithm Selection

### 8.1 Main Function
- [ ] Create `srcs/main.c`
  - [ ] Write `main(int argc, char **argv)` function
    - [ ] Declare stack_a, stack_b pointers, and numbers array
    - [ ] Initialize stack_b to NULL
    - [ ] **Step 1:** Call parse_arguments(argc, argv) to get numbers array
    - [ ] If parse fails (NULL returned): return 0 (no error - just no args)
    - [ ] **Step 2:** Call init_stack_a(numbers) to create and validate stack A
    - [ ] If init fails (NULL returned):
      - [ ] Free numbers with free_split() - ALWAYS allocated
      - [ ] Call print_error()
      - [ ] Return 1
    - [ ] Check if stack is already sorted
      - [ ] If sorted: free stack A, free numbers, exit (no operations)
    - [ ] Assign indices to stack A (assign_index)
    - [ ] Route to appropriate sorting algorithm (choose_sort)
    - [ ] Free both stacks
    - [ ] **Step 3:** Free numbers array with free_split() - ALWAYS required
    - [ ] Return 0
    - [ ] **IMPORTANT:** Always free numbers - no argc checks needed

### 8.2 Algorithm Router
- [ ] Add to `srcs/main.c`
  - [ ] Write `choose_sort(t_stack **stack_a, t_stack **stack_b)` function
    - [ ] Get size of stack A
    - [ ] If size <= 5: call sort_small
    - [ ] Else: call sort_large
    - [ ] This implements the hybrid approach

---

## Phase 9: Testing and Optimization

### 9.1 Basic Functionality Testing
- [ ] Test with manual inputs
  - [ ] Test: `./push_swap 2 1 3` (should output: sa)
  - [ ] Test: `./push_swap 1 2 3` (should output: nothing, already sorted)
  - [ ] Test: `./push_swap 3 2 1` (test 3 numbers)
  - [ ] Test: `./push_swap 4 3 2 1` (test 4 numbers)
  - [ ] Test: `./push_swap 5 4 3 2 1` (test 5 numbers)

### 9.2 Error Testing
- [ ] Test error handling
  - [ ] Test: `./push_swap` (no args - should show nothing)
  - [ ] Test: `./push_swap ""` (empty string - should show Error)
  - [ ] Test: `./push_swap 1 2 2` (duplicates - should show Error)
  - [ ] Test: `./push_swap 1 a 3` (non-integer - should show Error)
  - [ ] Test: `./push_swap 2147483648` (overflow - should show Error)
  - [ ] Test: `./push_swap -2147483649` (underflow - should show Error)

### 9.2b Mixed Format Testing (NEW!)
- [ ] Test mixed argument formats
  - [ ] Test: `./push_swap "2 4 3" 91 10` (mixed: string + numbers)
  - [ ] Test: `./push_swap 2 4 "3 91" 10` (mixed: numbers + string + number)
  - [ ] Test: `./push_swap "1 2" "3 4" "5"` (multiple strings)
  - [ ] Test: `./push_swap "5   3    1"` (extra spaces in string)
  - [ ] Test: `./push_swap "  5 3 1  "` (leading/trailing spaces)
  - [ ] Verify all mixed formats work correctly
  - [ ] Verify memory is properly freed (valgrind)

### 9.3 Valgrind Memory Testing
- [ ] Run valgrind on all test cases
  - [ ] `valgrind --leak-check=full ./push_swap 4 2 1 3`
  - [ ] Verify: "All heap blocks were freed"
  - [ ] Verify: "no leaks are possible"
  - [ ] Test with error cases too
  - [ ] Fix any memory leaks found

### 9.4 Benchmark Testing - 100 Numbers
- [ ] Generate random 100 numbers and test
  - [ ] Create script to generate random numbers
    ```bash
    ARG=$(seq 1 100 | shuf | tr '\n' ' ')
    ./push_swap $ARG | wc -l
    ```
  - [ ] Run test 10 times, calculate average
  - [ ] Target: < 700 operations (for 100%)
  - [ ] Acceptable: < 1100 operations (for 80%)
  - [ ] Record results

### 9.5 Benchmark Testing - 500 Numbers
- [ ] Generate random 500 numbers and test
  - [ ] Create script:
    ```bash
    ARG=$(seq 1 500 | shuf | tr '\n' ' ')
    ./push_swap $ARG | wc -l
    ```
  - [ ] Run test 10 times, calculate average
  - [ ] Target: < 5500 operations (for 100%)
  - [ ] Acceptable: < 8500 operations (for 80%)
  - [ ] Record results

### 9.6 Checker Validation (Use provided checker)
- [ ] Download checker_OS from intranet
  - [ ] Place in project directory
  - [ ] Make executable: `chmod +x checker_OS`
- [ ] Test with checker:
  ```bash
  ARG="4 67 3 87 23"
  ./push_swap $ARG | ./checker_OS $ARG
  ```
  - [ ] Should output: OK
  - [ ] Test with various inputs
  - [ ] Verify all outputs are OK
  - [ ] If KO, debug sorting algorithm

### 9.7 Optimization Round 1
- [ ] If benchmarks not met, optimize:
  - [ ] Review chunk sizes - adjust based on results
  - [ ] Optimize cost calculation - reduce unnecessary calculations
  - [ ] Implement look-ahead - check next few moves
  - [ ] Use double operations (rr, rrr, ss) more effectively
  - [ ] Profile code to find bottlenecks

### 9.8 Optimization Round 2
- [ ] Advanced optimizations:
  - [ ] Implement pre-sorting optimization in B
  - [ ] Keep B partially sorted during push phase
  - [ ] Reduce unnecessary rotations
  - [ ] Batch similar operations
  - [ ] Fine-tune chunk algorithm parameters

### 9.9 Edge Case Testing
- [ ] Test special cases:
  - [ ] Already sorted: `./push_swap 1 2 3 4 5`
  - [ ] Reverse sorted: `./push_swap 5 4 3 2 1`
  - [ ] Single element: `./push_swap 42`
  - [ ] Two elements sorted: `./push_swap 1 2`
  - [ ] Two elements unsorted: `./push_swap 2 1`
  - [ ] Negative numbers: `./push_swap -5 -2 -10 0 3`
  - [ ] Large numbers: `./push_swap 2147483647 -2147483648`
  - [ ] Mixed: `./push_swap -100 50 -200 150 0`

---

## Phase 10: 42 Norm Compliance Check

### 10.1 Norm Validation
- [ ] Run norminette on all files
  - [ ] `norminette includes/`
  - [ ] `norminette srcs/`
  - [ ] Fix all norm errors
  - [ ] Common issues to check:
    - [ ] Function length (max 25 lines)
    - [ ] Functions per file (max 5)
    - [ ] Parameters per function (max 4)
    - [ ] No for loops (use while)
    - [ ] No variable declarations in function body after code
    - [ ] Proper indentation (tabs, not spaces)
    - [ ] Blank line between functions
    - [ ] Space after keywords (if, while, return)

### 10.2 Function Splitting
- [ ] If functions too long (>25 lines):
  - [ ] Split into smaller helper functions
  - [ ] Each helper should do one thing
  - [ ] Add helper prototypes to header
  - [ ] Re-run norminette to verify

### 10.3 Code Review
- [ ] Review code for readability
  - [ ] Add comments where logic is complex
  - [ ] Ensure variable names are clear
  - [ ] Check for unnecessary code
  - [ ] Verify proper error handling everywhere

---

## Phase 11: Bonus Part - Checker Program

**NOTE: Only proceed if mandatory part achieves 100% on all benchmarks**

### 11.1 Bonus Header
- [ ] Create `includes/push_swap_bonus.h`
  - [ ] Copy necessary structures from main header
  - [ ] Add checker-specific prototypes
  - [ ] Include guards

### 11.2 Checker Main
- [ ] Create `srcs_bonus/checker_bonus.c`
  - [ ] Write `main(int argc, char **argv)` function
    - [ ] Parse arguments (same as push_swap)
    - [ ] Initialize stack A
    - [ ] Initialize stack B (empty)
    - [ ] Read instructions from stdin
    - [ ] Execute each instruction
    - [ ] Check if sorted at end
    - [ ] Output "OK\n" or "KO\n"

### 11.3 Instruction Reading
- [ ] Add to `srcs_bonus/checker_bonus.c`
  - [ ] Write `read_instructions()` function
    - [ ] Use get_next_line or read() to read stdin
    - [ ] Read line by line
    - [ ] Parse each instruction
    - [ ] Return list of instructions or execute directly

### 11.4 Instruction Parsing
- [ ] Create `srcs_bonus/parse_instructions_bonus.c`
  - [ ] Write `parse_instruction(char *line)` function
    - [ ] Compare line with valid instructions
    - [ ] Return instruction ID or error code
    - [ ] Valid instructions: sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr

  - [ ] Write `execute_instruction(char *line, t_stack **a, t_stack **b)` function
    - [ ] Parse instruction
    - [ ] Call appropriate operation function (with print=0)
    - [ ] Return 0 on success, -1 on error

### 11.5 Checker Operations
- [ ] Create `srcs_bonus/operations_bonus.c`
  - [ ] Copy all operation functions from mandatory
  - [ ] Ensure print parameter is respected
  - [ ] All operations should NOT print when called from checker

### 11.6 Final Check
- [ ] Add to `srcs_bonus/checker_bonus.c`
  - [ ] Write `check_sorted(t_stack *stack_a, t_stack *stack_b)` function
    - [ ] Check if stack A is sorted
    - [ ] Check if stack B is empty
    - [ ] Return 1 if both conditions true, 0 otherwise

  - [ ] In main, after executing all instructions:
    - [ ] Call check_sorted
    - [ ] If true: write "OK\n" to stdout
    - [ ] If false: write "KO\n" to stdout

### 11.7 Bonus Error Handling
- [ ] Handle errors in checker:
  - [ ] Invalid instruction: write "Error\n" to stderr
  - [ ] Invalid arguments: write "Error\n" to stderr
  - [ ] Free memory and exit on error

### 11.8 Bonus Makefile Rule
- [ ] Update Makefile
  - [ ] Add `bonus` rule
  - [ ] Compile bonus files separately
  - [ ] Create `checker` binary
  - [ ] Link with libft
  - [ ] Test that `make bonus` works

### 11.9 Bonus Testing
- [ ] Test checker with push_swap output:
  ```bash
  ARG="3 2 1 0"
  ./push_swap $ARG | ./checker $ARG
  ```
  - [ ] Should output: OK
- [ ] Test with incorrect instructions:
  ```bash
  echo -e "sa\npa\nrra" | ./checker 3 2 1
  ```
  - [ ] Should output: KO (if not sorted)
- [ ] Test with invalid instruction:
  ```bash
  echo "sa\ninvalid\npa" | ./checker 3 2 1
  ```
  - [ ] Should output: Error
- [ ] Run norminette on bonus files

---

## Phase 12: Documentation and Submission

### 12.1 README.md Creation
- [ ] Write comprehensive README.md
  - [ ] First line (italicized): "This project has been created as part of the 42 curriculum by <your_login>."
  - [ ] **Description** section:
    - [ ] Explain push_swap concept
    - [ ] Explain goal (sort with minimum operations)
    - [ ] Explain stacks and operations
  - [ ] **Instructions** section:
    - [ ] Compilation: `make`
    - [ ] Usage: `./push_swap <numbers>`
    - [ ] Bonus compilation: `make bonus`
    - [ ] Bonus usage: `./push_swap <nums> | ./checker <nums>`
    - [ ] Clean: `make clean`, `make fclean`, `make re`
  - [ ] **Algorithm** section:
    - [ ] Explain hybrid approach
    - [ ] Explain small number hardcoded sorts
    - [ ] Explain Turk/Chunk algorithm for large numbers
    - [ ] Mention index normalization
  - [ ] **Performance** section:
    - [ ] Show benchmark results (3, 5, 100, 500 numbers)
    - [ ] Show operation counts achieved
  - [ ] **Resources** section:
    - [ ] List sorting algorithm references
    - [ ] List tutorials/articles used
    - [ ] **AI Usage Disclosure**:
      - [ ] Specify which AI tools were used (if any)
      - [ ] Specify which tasks (e.g., "algorithm research", "debugging", "optimization ideas")
      - [ ] Specify which parts of project (e.g., "cost calculation function", "testing scripts")

### 12.2 Code Commenting
- [ ] Add comments to complex functions
  - [ ] Explain algorithm logic
  - [ ] Document parameters
  - [ ] Document return values
  - [ ] Keep comments concise and meaningful

### 12.3 Final Testing Before Submission
- [ ] Run full test suite one more time
  - [ ] All error cases
  - [ ] Small number sorts (2, 3, 4, 5)
  - [ ] Medium number sorts (10, 50, 100)
  - [ ] Large number sorts (500)
  - [ ] Valgrind all tests
  - [ ] Norminette all files
  - [ ] Check Makefile rules

### 12.4 Git Submission
- [ ] Verify git repository
  - [ ] Ensure all files are added
  - [ ] Ensure no object files (.o) committed
  - [ ] Ensure no binaries committed (unless allowed)
  - [ ] Ensure .gitignore is proper (ignore .o, binaries, .DS_Store, etc.)
- [ ] Commit final version
  - [ ] `git add .`
  - [ ] `git commit -m "Final push_swap submission"`
  - [ ] `git push`
- [ ] Verify on intranet that files are visible

### 12.5 Peer Evaluation Preparation
- [ ] Prepare for defense:
  - [ ] Review entire codebase
  - [ ] Understand every function you wrote
  - [ ] Be ready to explain algorithm choices
  - [ ] Be ready to explain complexity
  - [ ] Prepare test cases to demonstrate
  - [ ] Test on fresh clone of repo
  - [ ] Ensure compilation works on school computers

---

## Phase 13: Optimization Tips (If Needed)

### 13.1 Chunk Size Tuning
- [ ] Experiment with chunk sizes:
  - [ ] For 100: try 5-6 chunks (16-20 elements each)
  - [ ] For 500: try 11-15 chunks (33-45 elements each)
  - [ ] Test each configuration
  - [ ] Record operation counts
  - [ ] Choose best performing

### 13.2 Cost Calculation Optimization
- [ ] Optimize cost calculation:
  - [ ] Pre-calculate positions once per iteration
  - [ ] Cache frequently accessed values
  - [ ] Skip unnecessary recalculations
  - [ ] Use bit operations where applicable

### 13.3 Pre-rotation Strategy
- [ ] Implement smart pre-rotation:
  - [ ] When pushing to B, keep it partially sorted
  - [ ] Rotate B to optimal position before each push
  - [ ] Reduces operations when pushing back to A

### 13.4 Operation Batching
- [ ] Batch similar operations:
  - [ ] Group consecutive rotations
  - [ ] Use rr/rrr instead of ra+rb/rra+rrb
  - [ ] Look ahead 2-3 operations
  - [ ] Combine where possible

---

## Completion Checklist

### Mandatory Requirements
- [ ] Program compiles with no errors
- [ ] Program compiles with no warnings
- [ ] Makefile has all required rules
- [ ] Makefile doesn't relink
- [ ] No norm errors in any file
- [ ] No memory leaks (verified with valgrind)
- [ ] No crashes (segfault, bus error, double free)
- [ ] Error handling works correctly
- [ ] Sorts 3 numbers in ≤3 operations
- [ ] Sorts 5 numbers in ≤12 operations
- [ ] Sorts 100 numbers in <700 operations (average)
- [ ] Sorts 500 numbers in <5500 operations (average)
- [ ] Works with checker_OS provided by 42

### Bonus Requirements (Optional)
- [ ] Mandatory part is 100% complete
- [ ] Checker program compiles with `make bonus`
- [ ] Checker correctly validates sorting sequences
- [ ] Checker handles errors properly
- [ ] Checker has no memory leaks
- [ ] Checker has no norm errors

### Documentation
- [ ] README.md is complete and comprehensive
- [ ] AI usage is documented (if applicable)
- [ ] Code is well-commented
- [ ] PROJECT_ANALYSIS.md exists (for your reference)

### Final Verification
- [ ] Test on fresh clone of repository
- [ ] Test on school computer (if possible)
- [ ] All files submitted to git repository
- [ ] Ready for peer evaluation

---

## Notes and Tips

### General Tips
1. **Start small**: Implement and test each operation individually
2. **Test frequently**: Don't write too much code before testing
3. **Valgrind early**: Catch memory issues as you code
4. **Norm check often**: Don't accumulate norm errors
5. **Read the subject**: Multiple times, carefully

### Algorithm Tips
1. **Understand complexity**: Know why your algorithm works
2. **Visualize**: Draw stacks on paper to understand operations
3. **Optimize iteratively**: Get it working first, then optimize
4. **Test edge cases**: Empty, single element, already sorted
5. **Compare approaches**: Try different chunk sizes

### Common Mistakes to Avoid
1. **Not freeing memory**: Every malloc needs a free
2. **Integer overflow**: Use long for parsing
3. **Ignoring edge cases**: NULL pointers, empty stacks
4. **Global variables**: Not allowed in 42 Norm
5. **For loops**: Use while loops instead
6. **Function too long**: Split if >25 lines
7. **Not testing enough**: Test all benchmarks thoroughly

### Resources
- Sorting algorithms: Wikipedia, GeeksforGeeks
- Visualizers: Use push_swap visualizers online
- Peer discussions: Learn from others (but code yourself)
- 42 Discord/Slack: Ask questions if stuck

---

**Good luck with your push_swap project!**
**Remember: Understanding is more important than just passing. Take your time to learn!**
