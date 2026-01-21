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

  - [x] Write `join_all_arguments(int argc, char **argv, int total)` helper function (static)
    - [x] Allocate result array for (total + 1) pointers
    - [x] Iterate through all arguments
    - [x] Split each argument by spaces
    - [x] Transfer string pointers from split to result (ownership transfer)
    - [x] Free only temp array structure (not strings - transferred)
    - [x] NULL-terminate result array
    - [x] Return combined array or NULL on error

  - [x] Write `parse_arguments(int argc, char **argv)` main function
    - [x] Handle case: no arguments (argc < 2, return NULL)
    - [x] Call `count_total_numbers()` to get total count
    - [x] Validate count > 0
    - [x] Call `join_all_arguments()` to build result array
    - [x] Return unified array of number strings (ALWAYS allocated)
    - [x] **NEW:** Supports mixed formats like `./push_swap "2 4" 91 10`
    - [x] **NEW:** Consistent memory management (always allocates)
    - [x] Memory: Caller MUST free with free_split() - no argc checks needed

### 2.2 Number Validation
**File:** `srcs/validate.c` (4 functions - separate file for 42 Norm compliance)

**NOTE:** These functions are in a separate file because parser.c already has 3 functions
(parse_arguments + 2 static helpers), and 42 Norm limits files to 5 functions max.

- [x] Create `srcs/validate.c`
  - [x] Write `is_valid_number(char *str)` function
    - [x] Check if string represents valid integer
    - [x] Handle signs ('+', '-')
    - [x] Check all characters are digits
    - [x] Handle leading zeros
    - [x] Return 1 if valid, 0 if invalid

  - [x] Write `ft_atol(char *str)` function
    - [x] Convert string to long (to check overflow)
    - [x] Handle signs
    - [x] Parse digit by digit
    - [x] Return long value

  - [x] Write `is_int_range(long num)` function
    - [x] Check if num is within INT_MIN and INT_MAX
    - [x] Return 1 if valid, 0 if overflow

### 2.3 Duplicate Detection
- [x] Add to `srcs/validate.c`
  - [x] Write `has_duplicates(t_stack *stack)` function
    - [x] Compare each node with all other nodes
    - [x] Check for duplicate values
    - [x] Return 1 if duplicates found, 0 otherwise
    - [x] Use nested while loops (no for loops - 42 Norm)

### 2.4 Stack Initialization
- [x] Create `srcs/stack_init.c` (3 functions for 42 Norm compliance)

  - [x] Write `append_node(t_stack **stack, char *str)` **static helper** (~12 lines)
    - [x] Validate single number string format (is_valid_number)
    - [x] Convert string to long (ft_atol)
    - [x] Check if value is within int range (is_int_range)
    - [x] Create stack node (stack_new) with cast to int
    - [x] Add node to stack (stack_add_back)
    - [x] Return node pointer on success, NULL on any failure
    - [x] **NOTE:** Stack remains unchanged if validation fails

  - [x] Write `build_stack(char **numbers)` **static helper** (~18 lines)
    - [x] Initialize empty stack (NULL)
    - [x] Iterate through numbers array (while numbers[i])
    - [x] Call append_node for each number string
    - [x] On append_node failure: free_stack and return NULL
    - [x] After loop: check for duplicates (has_duplicates)
    - [x] If duplicates found: free_stack and return NULL
    - [x] Return completed stack on success

  - [x] Write `init_stack_a(int argc, char **argv)` **main function** (~15 lines)
    - [x] Call parse_arguments(argc, argv) to get numbers array
    - [x] If parse fails (NULL): return NULL
    - [x] Call build_stack(numbers) to construct stack
    - [x] If build fails (NULL):
      - [x] Free numbers array if argc == 2 (allocated by ft_split)
      - [x] Return NULL
    - [x] On success: free numbers array if argc == 2
    - [x] Return completed stack_a
    - [x] **IMPORTANT:** Memory ownership - numbers is freed here, not by caller

---

## Phase 3: Error Handling and Memory Management

### 3.1 Error Handling
- [x] Create `srcs/error.c`
  - [x] Write `print_error()` function
    - [x] Write "Error\n" to stderr (fd = 2)
    - [x] Use `write(2, "Error\n", 6)`

  - [x] Write `error_exit(t_stack **stack_a, t_stack **stack_b)` function
    - [x] Call print_error()
    - [x] Free stack A if allocated
    - [x] Free stack B if allocated
    - [x] Exit program with `exit(1)`

### 3.2 Memory Cleanup
- [x] Create `srcs/free.c`
  - [x] Write `free_stack(t_stack **stack)` function
    - [x] Iterate through entire stack
    - [x] Free each node
    - [x] Set *stack to NULL after freeing all
    - [x] Handle NULL pointer (do nothing)

  - [x] Write `free_split(char **split)` function
    - [x] Free each string in split array
    - [x] Free the array itself
    - [x] Needed if using ft_split for parsing

---

## Phase 4: Stack Operations Implementation

### 4.1 Swap Operations
- [x] Create `srcs/operations_swap.c`
  - [x] Write `sa(t_stack **stack_a, int print)` function
    - [x] Swap first two elements of stack A
    - [x] Handle edge cases (NULL double pointer, empty stack, 1 element)
    - [x] If print=1, write "sa\n" to stdout
    - [x] Implementation:
      - [x] Validate: `if (!stack_a || !*stack_a || !(*stack_a)->next) return;`
      - [x] Save first node (head)
      - [x] Save second node (head->next)
      - [x] Set first->next to second->next (skip second)
      - [x] Set second->next to first (link second to first)
      - [x] Update stack head to second (complete swap)

  - [x] Write `sb(t_stack **stack_b, int print)` function
    - [x] Same as sa but for stack B
    - [x] Handle edge cases (NULL double pointer, empty stack, 1 element)
    - [x] If print=1, write "sb\n" to stdout

  - [x] Write `ss(t_stack **stack_a, t_stack **stack_b, int print)` function
    - [x] Call sa with print=0
    - [x] Call sb with print=0
    - [x] If print=1, write "ss\n" to stdout

### 4.2 Push Operations
- [x] Create `srcs/operations_push.c`
  - [x] Write `pa(t_stack **stack_a, t_stack **stack_b, int print)` function
    - [x] Take top element from B, push to A
    - [x] Handle edge case (B is empty - do nothing)
    - [x] If print=1, write "pa\n" to stdout
    - [x] Implementation:
      - [x] Save top of B
      - [x] Remove top from B (update head)
      - [x] Add saved node to top of A

  - [x] Write `pb(t_stack **stack_a, t_stack **stack_b, int print)` function
    - [x] Take top element from A, push to B
    - [x] Handle edge case (A is empty - do nothing)
    - [x] If print=1, write "pb\n" to stdout

### 4.3 Rotate Operations
- [x] Create `srcs/operations_rotate.c`
  - [x] Write `ra(t_stack **stack_a, int print)` function
    - [x] Shift all elements up by 1 (first becomes last)
    - [x] Handle edge cases (NULL, 1 element)
    - [x] If print=1, write "ra\n" to stdout
    - [x] Implementation:
      - [x] Save first node
      - [x] Update head to second node
      - [x] Find last node
      - [x] Attach saved first node to end
      - [x] Set its next to NULL

  - [x] Write `rb(t_stack **stack_b, int print)` function
    - [x] Same as ra but for stack B
    - [x] If print=1, write "rb\n" to stdout

  - [x] Write `rr(t_stack **stack_a, t_stack **stack_b, int print)` function
    - [x] Call ra with print=0
    - [x] Call rb with print=0
    - [x] If print=1, write "rr\n" to stdout

### 4.4 Reverse Rotate Operations
- [x] Create `srcs/operations_reverse.c`
  - [x] Write `rra(t_stack **stack_a, int print)` function
    - [x] Shift all elements down by 1 (last becomes first)
    - [x] Handle edge cases (NULL, 1 element)
    - [x] If print=1, write "rra\n" to stdout
    - [x] Implementation:
      - [x] Find last node
      - [x] Find second-to-last node
      - [x] Detach last node (set second-to-last next to NULL)
      - [x] Attach last node to beginning
      - [x] Update head to last node

  - [x] Write `rrb(t_stack **stack_b, int print)` function
    - [x] Same as rra but for stack B
    - [x] If print=1, write "rrb\n" to stdout

  - [x] Write `rrr(t_stack **stack_a, t_stack **stack_b, int print)` function
    - [x] Call rra with print=0
    - [x] Call rrb with print=0
    - [x] If print=1, write "rrr\n" to stdout

### 4.5 Operation Testing
- [x] Test each operation individually
  - [x] Create test stack with known values
  - [x] Execute operation
  - [x] Verify stack state manually
  - [x] Test edge cases for each operation

---

## Phase 5: Index Normalization (Optimization)

### 5.1 Index Mapping Implementation
- [x] Create `srcs/index.c`
  - [x] Write `assign_index(t_stack *stack_a)` function
    - [x] Create array to store values
    - [x] Copy all values from stack to array
    - [x] Sort array in ascending order (use simple sorting)
    - [x] Assign indices: smallest value gets index 0, next gets 1, etc.
    - [x] Iterate through stack and assign corresponding index to each node
    - [x] Free temporary array
    - [x] Purpose: normalize values to 0...N-1 range

  - [x] Write `get_index_position(int value, int *sorted_arr, int size)` function
    - [x] Binary search or linear search to find value in sorted array
    - [x] Return index position

  - [x] Write `copy_values_to_array(t_stack *stack, int **arr)` function
    - [x] Allocate array of size stack_size
    - [x] Copy each value from stack to array
    - [x] Return array

### 5.2 Array Sorting Helper
- [x] Add to `srcs/index.c`
  - [x] Write `sort_int_array(int *arr, int size)` function
    - [x] Use simple sorting (bubble sort is fine for this purpose)
    - [x] Sort array in ascending order
    - [x] This is not the stack sorting - just helper for index assignment

---

## Phase 6: Small Number Sorting (Hardcoded Solutions) ✅ COMPLETE

### File Structure
```
srcs/
├── sort_small.c           # Router function only (~15 lines)
│   └── sort_small()       # Routes to appropriate sort function
│
└── sort_small_utils.c     # All helper sorting functions
    ├── sort_two()         # 2-element sort
    ├── sort_three()       # 3-element sort
    ├── sort_four()        # 4-element sort
    ├── rotate_min_to_top() # Static helper for sort_five
    └── sort_five()        # 5-element sort
```

### 6.1 Two Numbers ✅
- [x] Create `srcs/sort_small_utils.c`
  - [x] Write `sort_two(t_stack **stack_a)` function
    - [x] **DEFENSIVE:** Validate `!stack_a || !*stack_a` (CRITICAL)
    - [x] **DEFENSIVE:** Validate `stack_size(*stack_a) < 2` (MEDIUM)
    - [x] If first > second, execute sa
    - [x] Else already sorted, do nothing
    - [x] Total operations: 0-1

### 6.2 Three Numbers (Optimal) ✅
- [x] Add to `srcs/sort_small_utils.c`
  - [x] Write `sort_three(t_stack **stack_a)` function
    - [x] **DEFENSIVE:** Validate `!stack_a || !*stack_a` (CRITICAL)
    - [x] **DEFENSIVE:** Validate `stack_size(*stack_a) < 3` (MEDIUM)
    - [x] Find maximum value using find_max
    - [x] Use decision tree based on max position:
      - [x] Max on top: ra, then sa if needed
      - [x] Max in middle: rra, then sa if needed
      - [x] Max on bottom: sa if out of order
    - [x] Maximum 2 operations for any configuration
    - [x] Under 25 lines (24 lines with defensive checks)

### 6.3 Four Numbers ✅
- [x] Add to `srcs/sort_small_utils.c`
  - [x] Write `sort_four(t_stack **stack_a, t_stack **stack_b)` function
    - [x] **DEFENSIVE:** Validate `!stack_a || !stack_b || !*stack_a` (CRITICAL)
    - [x] **DEFENSIVE:** Validate `stack_size(*stack_a) < 4` (MEDIUM)
    - [x] Find minimum using find_min_index
    - [x] Rotate/reverse rotate to bring it to top (choose cheaper direction)
    - [x] Push smallest to B (pb)
    - [x] Sort remaining 3 with sort_three
    - [x] Push smallest back to A (pa)
    - [x] Maximum operations: ~6-7

### 6.4 Five Numbers ✅
- [x] Add to `srcs/sort_small_utils.c`
  - [x] Write `rotate_min_to_top(t_stack **stack_a, int size)` **static helper** (~18 lines)
    - [x] Find minimum using find_min_index
    - [x] Handle position 1: sa
    - [x] Handle position 2 (5-elem): ra, ra
    - [x] Handle position 2 (4-elem) / position 3 (5-elem): rra, rra
    - [x] Handle position 3 (4-elem) / position 4 (5-elem): rra
    - [x] **NOTE:** No defensive checks - trusts caller (sort_five) validation
    - [x] **42 Norm:** 18 lines, under 25 lines ✅
  - [x] Write `sort_five(t_stack **stack_a, t_stack **stack_b)` function
    - [x] **DEFENSIVE:** Validate `!stack_a || !stack_b || !*stack_a` (CRITICAL)
    - [x] **DEFENSIVE:** Validate `stack_size(*stack_a) < 5` (MEDIUM)
    - [x] Call rotate_min_to_top(stack_a, 5) + pb
    - [x] Call rotate_min_to_top(stack_a, 4) + pb
    - [x] Sort remaining 3 with sort_three
    - [x] Push back both elements from B to A (pa, pa)
    - [x] Maximum operations: ~11-12
    - [x] **42 Norm:** 14 lines, under 25 lines ✅

### 6.5 Small Sort Router ✅
- [x] Create `srcs/sort_small.c` (router function only)
  - [x] Write `sort_small(t_stack **stack_a, t_stack **stack_b)` function
    - [x] **DEFENSIVE:** Validate `!stack_a || !stack_b || !*stack_a` (CRITICAL)
    - [x] Get stack size
    - [x] If size == 2, call sort_two
    - [x] If size == 3, call sort_three
    - [x] If size == 4, call sort_four
    - [x] If size == 5, call sort_five
    - [x] Edge cases (0, 1, >5): returns safely
    - [x] **LAYERED DEFENSE:** Each delegated function has own checks

### 6.6 Documentation Updates ✅
- [x] Updated all sort_small.c function documentation with:
  - [x] Defensive programming approach (CRITICAL/HIGH/MEDIUM severity)
  - [x] Basic and Defensive pseudocode versions
  - [x] Defensive Programming Checklists
  - [x] 42 Norm compliant function structures
- [x] Created rotate_min_to_top.md helper function documentation (~28 KB)

---

## Phase 7: Large Number Sorting - Turk/Chunk Algorithm ✅ COMPLETE

### 7.1 Chunk/Partition Strategy ✅
- [x] Create `srcs/sort_large.c`
  - [x] Write `push_chunks_to_b(t_stack **stack_a, t_stack **stack_b, int size)` function
    - [x] Determine chunk size based on total size
      - [x] For 100 elements: ~20 chunks (5 per chunk)
      - [x] For 500 elements: ~35 chunks (~14 per chunk)
    - [x] Calculate number of chunks
    - [x] Push elements to B in chunks based on index:
      - [x] For each chunk range:
        - [x] Find elements in stack A within current chunk index range
        - [x] Rotate/reverse rotate to bring element to top (cheaper option)
        - [x] Push to B (pb)
        - [x] Rotate B intelligently to keep larger elements on top
    - [x] Continue until all elements (except ~3 smallest) are in B

### 7.2 Cost Calculation ✅
- [x] Create `srcs/cost.c`
  - [x] Write `calculate_cost(t_stack *stack_a, t_stack *stack_b)` function
    - [x] Assign positions to both stacks
    - [x] For each element in B:
      - [x] Find target position in A (where it should be inserted)
      - [x] Calculate cost to bring element to top of B
      - [x] Calculate cost to rotate A to target position
      - [x] Store both costs in node

  - [x] Write `find_target_position(t_stack *stack_a, int index_b)` function
    - [x] Find position in A where element from B should be inserted
    - [x] Find smallest element in A that is larger than index_b
    - [x] If none found, target is position of smallest element
    - [x] Return target position

  - [x] Write `calculate_move_cost(t_stack *stack, int target_pos)` function
    - [x] Calculate cost to move element to top
    - [x] Compare rotate cost vs reverse rotate cost
    - [x] Return cheaper cost (and direction)

### 7.3 Cheapest Element Selection ✅
- [x] Add to `srcs/cost.c`
  - [x] Write `find_cheapest(t_stack *stack_b)` function
    - [x] Calculate total cost for each element (cost_a + cost_b)
    - [x] Find element with minimum total cost
    - [x] Return pointer to cheapest element

  - [x] Write `execute_cheapest_move(t_stack **a, t_stack **b, t_stack *cheapest)` function
    - [x] Get costs from cheapest element
    - [x] Execute optimal moves:
      - [x] If both costs positive (both rotate): use rr
      - [x] If both costs negative (both reverse rotate): use rrr
      - [x] If mixed: execute independently
    - [x] Bring element to top of B
    - [x] Rotate A to target position
    - [x] Execute pa to push to A

### 7.4 Main Large Sort Function ✅
- [x] Add to `srcs/sort_large.c`
  - [x] Write `sort_large(t_stack **stack_a, t_stack **stack_b)` function
    - [x] Push chunks to B using push_chunks_to_b
    - [x] While B is not empty:
      - [x] Calculate costs for all elements in B
      - [x] Find cheapest element
      - [x] Execute cheapest move
      - [x] Push element from B to A at target position
    - [x] Final rotation to ensure smallest element is on top

  - [x] Write `final_rotate(t_stack **stack_a)` function
    - [x] Find position of minimum element
    - [x] Rotate or reverse rotate to bring it to top
    - [x] Choose cheaper direction

---

## Phase 8: Main Program and Algorithm Selection ✅ COMPLETE

### 8.1 Main Function ✅
- [x] Create `srcs/main.c`
  - [x] Write `main(int argc, char **argv)` function
    - [x] Declare stack_a, stack_b pointers, and numbers array
    - [x] Initialize stack_b to NULL
    - [x] **Step 1:** Call parse_arguments(argc, argv) to get numbers array
    - [x] If parse fails (NULL returned): return 0 (no error - just no args)
    - [x] **Step 2:** Call init_stack_a(numbers) to create and validate stack A
    - [x] If init fails (NULL returned):
      - [x] Free numbers with free_split() - ALWAYS allocated
      - [x] Call print_error()
      - [x] Return 1
    - [x] Check if stack is already sorted
      - [x] If sorted: free stack A, free numbers, exit (no operations)
    - [x] Assign indices to stack A (assign_index)
    - [x] Route to appropriate sorting algorithm (choose_sort)
    - [x] Free both stacks
    - [x] **Step 3:** Free numbers array with free_split() - ALWAYS required
    - [x] Return 0
    - [x] **IMPORTANT:** Always free numbers - no argc checks needed

### 8.2 Algorithm Router ✅
- [x] Add to `srcs/main.c`
  - [x] Write `choose_sort(t_stack **stack_a, t_stack **stack_b)` function
    - [x] Get size of stack A
    - [x] If size <= 5: call sort_small
    - [x] Else: call sort_large
    - [x] This implements the hybrid approach

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
