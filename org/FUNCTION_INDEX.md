# Push_swap Function Documentation Index

## Status Legend
- ✅ Complete - Detailed documentation exists
- 🚧 In Progress - Being created
- ⏳ Pending - Not yet documented

---

## Phase 1: Stack Utility Functions

### Basic Operations (Phase 1.2)
- ✅ [stack_new](functions/stack_new.md) - Create new stack node
- ✅ [stack_size](functions/stack_size.md) - Count nodes in stack
- ✅ [stack_last](functions/stack_last.md) - Find last node
- ✅ [stack_add_back](functions/stack_add_back.md) - Add node to end
- ⏳ stack_add_front - Add node to beginning

### Advanced Operations (Phase 1.3)
- ⏳ find_min - Find minimum value in stack
- ⏳ find_max - Find maximum value in stack
- ⏳ find_min_index - Find minimum index in stack
- ⏳ find_max_index - Find maximum index in stack
- ⏳ is_sorted - Check if stack is sorted

### Position Management (Phase 1.4)
- ⏳ assign_position - Assign current position to each node

---

## Phase 2: Parsing and Validation

### Argument Parsing (Phase 2.1)
- ⏳ parse_arguments - Parse command line arguments
- ⏳ init_stack_a - Initialize stack A from arguments

### Number Validation (Phase 2.2)
- ⏳ is_valid_number - Validate number string format
- ⏳ ft_atol - Convert string to long (overflow check)
- ⏳ is_int_range - Check if within INT_MIN/INT_MAX

### Duplicate Detection (Phase 2.3)
- ⏳ has_duplicates - Check for duplicate values

---

## Phase 3: Error Handling and Memory

### Error Handling (Phase 3.1)
- ⏳ print_error - Print "Error\n" to stderr
- ⏳ error_exit - Print error, free memory, exit

### Memory Cleanup (Phase 3.2)
- ⏳ free_stack - Free entire stack
- ⏳ free_split - Free split array

---

## Phase 4: Stack Operations (11 operations)

### Swap Operations (Phase 4.1)
- ⏳ sa - Swap first two elements of stack A
- ⏳ sb - Swap first two elements of stack B
- ⏳ ss - Execute sa and sb simultaneously

### Push Operations (Phase 4.2)
- ⏳ pa - Push top of B to A
- ⏳ pb - Push top of A to B

### Rotate Operations (Phase 4.3)
- ⏳ ra - Rotate stack A up (first becomes last)
- ⏳ rb - Rotate stack B up
- ⏳ rr - Execute ra and rb simultaneously

### Reverse Rotate Operations (Phase 4.4)
- ⏳ rra - Reverse rotate stack A (last becomes first)
- ⏳ rrb - Reverse rotate stack B
- ⏳ rrr - Execute rra and rrb simultaneously

---

## Phase 5: Index Normalization

### Index Assignment (Phase 5.1)
- ⏳ assign_index - Normalize values to 0...N-1 indices
- ⏳ get_index_position - Find index of value in sorted array
- ⏳ copy_values_to_array - Copy stack values to array

### Array Sorting (Phase 5.2)
- ⏳ sort_int_array - Sort integer array (helper for indexing)

---

## Phase 6: Small Number Sorting

### Hardcoded Solutions (Phase 6.1-6.4)
- ⏳ sort_two - Sort 2 elements (optimal)
- ⏳ sort_three - Sort 3 elements (optimal)
- ⏳ sort_four - Sort 4 elements
- ⏳ sort_five - Sort 5 elements

### Router (Phase 6.5)
- ⏳ sort_small - Route to appropriate small sort function

---

## Phase 7: Large Number Sorting

### Chunk Strategy (Phase 7.1)
- ⏳ push_chunks_to_b - Push elements to B in chunks

### Cost Calculation (Phase 7.2)
- ⏳ calculate_cost - Calculate move costs for all elements
- ⏳ find_target_position - Find where element should go in A
- ⏳ calculate_move_cost - Calculate cost to move to top

### Cheapest Selection (Phase 7.3)
- ⏳ find_cheapest - Find element with minimum total cost
- ⏳ execute_cheapest_move - Execute optimal move sequence

### Main Algorithm (Phase 7.4)
- ⏳ sort_large - Main sorting algorithm for large numbers
- ⏳ final_rotate - Rotate smallest to top at end

---

## Phase 8: Main Program

### Main Function (Phase 8.1)
- ⏳ main - Entry point, orchestrates everything

### Algorithm Router (Phase 8.2)
- ⏳ choose_sort - Select small vs large sort algorithm

---

## Phase 11: Bonus - Checker

### Checker Main (Phase 11.2)
- ⏳ main (checker) - Checker program entry point

### Instruction Reading (Phase 11.3)
- ⏳ read_instructions - Read operations from stdin

### Instruction Parsing (Phase 11.4)
- ⏳ parse_instruction - Parse instruction string
- ⏳ execute_instruction - Execute parsed instruction

### Final Validation (Phase 11.6)
- ⏳ check_sorted - Verify stack A is sorted and B is empty

---

## Total Functions

- **Documented:** 4
- **Pending:** ~60+
- **Priority:** Stack operations, parsing, sorting algorithms

---

## Usage

To read detailed documentation for a function:
1. Find the function in this index
2. Click the markdown link (if ✅ complete)
3. Read the comprehensive breakdown

Each function documentation includes:
- Function signature
- Purpose and use cases
- Step-by-step breakdown
- Visual examples
- Edge cases
- Pseudocode
- Common mistakes
- Testing strategy
- 42 Norm considerations

---

## Next Priority Functions to Document

1. **stack_add_front** - Needed for push operations
2. **is_sorted** - Needed early for optimization
3. **sa, sb, pa, pb** - Core operations
4. **parse_arguments** - Entry point
5. **sort_three** - Most commonly referenced

---

*This index will be updated as more functions are documented.*
