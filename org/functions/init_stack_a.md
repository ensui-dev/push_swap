# init_stack_a - Initialize Stack A from Command Line Arguments

## Function Signature

```c
t_stack *init_stack_a(int argc, char **argv)
```

**Return type:** `t_stack *` - Pointer to head of initialized stack A (or NULL on error)
**Parameters:**
- `int argc` - Number of command line arguments
- `char **argv` - Array of command line argument strings

---

## Purpose & Use Case

`init_stack_a` is the **orchestrator function** that transforms raw command line input into a validated, ready-to-sort stack. This is the most complex initialization function in push_swap because it coordinates parsing, validation, conversion, and stack building into one cohesive process.

### When You'll Use It

You'll call `init_stack_a` once at program startup to:
1. **Parse arguments** into normalized format
2. **Validate each number** for correct format
3. **Convert strings to integers** with overflow checking
4. **Build the linked list** stack structure
5. **Check for duplicates** in the final stack
6. **Return ready-to-sort stack** or NULL on any error

### Why This Matters

**Complete initialization pipeline:**
```
Input: ./push_swap 5 3 1 4 2

init_stack_a does ALL of this:
┌─────────────────────────────────────┐
│ 1. Parse: "5 3 1 4 2" → ["5","3"...│
│ 2. Validate: "5" is valid? ✓       │
│ 3. Convert: "5" → 5 (int)          │
│ 4. Check range: 5 in INT range? ✓  │
│ 5. Create node: stack_new(5)       │
│ 6. Add to stack: stack_add_back()  │
│ 7. Repeat for all numbers...       │
│ 8. Check duplicates: has_dupes? ✗  │
└─────────────────────────────────────┘

Output: Stack A ready to sort!
[5] → [3] → [1] → [4] → [2] → NULL
```

---

## Deep Dive: How It Works

### The Complete Pipeline

```
Phase 1: PARSING
Input: argc, argv
↓
parse_arguments()
↓
Output: ["5", "3", "1", "4", "2", NULL]

Phase 2: VALIDATION & CONVERSION (for each string)
For "5":
  ├─ is_valid_number("5")? → YES ✓
  ├─ ft_atol("5") → 5L
  ├─ is_int_range(5L)? → YES ✓
  ├─ stack_new(5) → node
  └─ stack_add_back(&stack, node)

Phase 3: DUPLICATE CHECK
stack: [5] → [3] → [1] → [4] → [2] → NULL
↓
has_duplicates(stack)? → NO ✓
↓
Return stack (SUCCESS!)
```

### Step-by-Step Implementation

#### Step 1: Parse Arguments

```c
char **numbers = parse_arguments(argc, argv);
if (!numbers)
    return (NULL);
```

**What happens:**
- Calls parse_arguments to normalize input
- Gets array of number strings
- Returns NULL if no valid input

**Memory note:** If argc == 2, numbers is allocated and must be freed

#### Step 2: Initialize Stack

```c
t_stack *stack_a = NULL;
int i = 0;
```

**Starting state:**
- Empty stack (NULL pointer)
- Counter for array iteration

#### Step 3: Iterate Through Number Strings

```c
while (numbers[i])
{
    // Process each number string
    i++;
}
```

**Array structure:**
```
numbers = ["5", "3", "1", "4", "2", NULL]
           ↑                         ↑
           i=0                    terminator
```

#### Step 4: Validate Number Format

```c
if (!is_valid_number(numbers[i]))
{
    free_stack(&stack_a);
    if (argc == 2)
        free_split(numbers);
    return (NULL);
}
```

**What is_valid_number checks:**
- Optional sign (+/-)
- Only digits
- No leading zeros (except "0")
- Not empty string

**Error handling:**
- Free any nodes already created
- Free numbers array if allocated
- Return NULL

#### Step 5: Convert String to Long

```c
long value = ft_atol(numbers[i]);
```

**Why long?**
- int range: -2,147,483,648 to 2,147,483,647
- Need to detect: 2,147,483,648 (too big!)
- long can hold bigger values for overflow detection
- Check range in next step

#### Step 6: Check Integer Range

```c
if (!is_int_range(value))
{
    free_stack(&stack_a);
    if (argc == 2)
        free_split(numbers);
    return (NULL);
}
```

**Range check:**
```
INT_MIN = -2,147,483,648
INT_MAX =  2,147,483,647

Valid:   -2147483648 ≤ value ≤ 2147483647
Invalid: value < INT_MIN or value > INT_MAX
```

#### Step 7: Create Stack Node

```c
t_stack *node = stack_new((int)value);
if (!node)
{
    free_stack(&stack_a);
    if (argc == 2)
        free_split(numbers);
    return (NULL);
}
```

**What stack_new does:**
- Allocates memory for node
- Initializes all fields
- Returns NULL if malloc fails

**Cast to int:**
- We know value fits in int (checked in step 6)
- Safe to cast long to int

#### Step 8: Add Node to Stack

```c
stack_add_back(&stack_a, node);
```

**Stack building:**
```
First iteration (i=0):
stack_a = [5] → NULL

Second iteration (i=1):
stack_a = [5] → [3] → NULL

Third iteration (i=2):
stack_a = [5] → [3] → [1] → NULL

... and so on
```

#### Step 9: Check for Duplicates

```c
if (has_duplicates(stack_a))
{
    free_stack(&stack_a);
    if (argc == 2)
        free_split(numbers);
    return (NULL);
}
```

**Why check after building:**
- More efficient to check once at end
- Could check during building but slower
- Duplicates are rare in valid input

#### Step 10: Clean Up and Return

```c
if (argc == 2)
    free_split(numbers);

return (stack_a);
```

**Final cleanup:**
- Free numbers array if we allocated it
- Return pointer to fully initialized stack
- Caller now owns the stack

---

## Visual Execution Trace

### Example: Complete Initialization

```
Command: ./push_swap "5 3 1 4 2"

═══════════════════════════════════════
STEP 1: PARSE ARGUMENTS
═══════════════════════════════════════
parse_arguments(2, ["./push_swap", "5 3 1 4 2"])
↓
ft_split("5 3 1 4 2", ' ')
↓
numbers = ["5", "3", "1", "4", "2", NULL]
          ↑                         ↑
          allocated              terminator

═══════════════════════════════════════
STEP 2: INITIALIZE STACK
═══════════════════════════════════════
stack_a = NULL
i = 0

═══════════════════════════════════════
ITERATION 1: Process "5"
═══════════════════════════════════════
numbers[0] = "5"

Validate:
  is_valid_number("5")? → YES ✓
  No sign, all digits, valid format

Convert:
  ft_atol("5") → 5L

Range check:
  is_int_range(5L)? → YES ✓
  -2147483648 ≤ 5 ≤ 2147483647

Create node:
  stack_new(5)
  ↓
  node = [value:5, index:-1, next:NULL]

Add to stack:
  stack_add_back(&stack_a, node)
  ↓
  stack_a = [5] → NULL

i++ → i = 1

═══════════════════════════════════════
ITERATION 2: Process "3"
═══════════════════════════════════════
numbers[1] = "3"

Validate: ✓
Convert: 3L
Range check: ✓
Create node: [value:3, ...]
Add to stack:
  stack_a = [5] → [3] → NULL

i++ → i = 2

═══════════════════════════════════════
ITERATION 3: Process "1"
═══════════════════════════════════════
numbers[2] = "1"

Validate: ✓
Convert: 1L
Range check: ✓
Create node: [value:1, ...]
Add to stack:
  stack_a = [5] → [3] → [1] → NULL

i++ → i = 3

═══════════════════════════════════════
ITERATION 4: Process "4"
═══════════════════════════════════════
numbers[3] = "4"

Validate: ✓
Convert: 4L
Range check: ✓
Create node: [value:4, ...]
Add to stack:
  stack_a = [5] → [3] → [1] → [4] → NULL

i++ → i = 4

═══════════════════════════════════════
ITERATION 5: Process "2"
═══════════════════════════════════════
numbers[4] = "2"

Validate: ✓
Convert: 2L
Range check: ✓
Create node: [value:2, ...]
Add to stack:
  stack_a = [5] → [3] → [1] → [4] → [2] → NULL

i++ → i = 5

═══════════════════════════════════════
STEP 3: END OF ARRAY
═══════════════════════════════════════
numbers[5] = NULL
Loop exits

═══════════════════════════════════════
STEP 4: CHECK DUPLICATES
═══════════════════════════════════════
has_duplicates(stack_a)?
  Compare all pairs:
  5 vs 3,1,4,2 → all different ✓
  3 vs 1,4,2   → all different ✓
  1 vs 4,2     → all different ✓
  4 vs 2       → all different ✓

Result: NO DUPLICATES ✓

═══════════════════════════════════════
STEP 5: CLEANUP
═══════════════════════════════════════
argc == 2, so free numbers array:
  free_split(numbers)
  ↓
  free("5"), free("3"), free("1"), free("4"), free("2")
  free(array)

═══════════════════════════════════════
STEP 6: RETURN SUCCESS
═══════════════════════════════════════
return stack_a

Final stack:
[5] → [3] → [1] → [4] → [2] → NULL

Ready to sort! ✅
```

### Example: Error During Validation

```
Command: ./push_swap "5 3 abc 4 2"

═══════════════════════════════════════
STEP 1: PARSE
═══════════════════════════════════════
numbers = ["5", "3", "abc", "4", "2", NULL]

═══════════════════════════════════════
STEP 2: INITIALIZE
═══════════════════════════════════════
stack_a = NULL
i = 0

═══════════════════════════════════════
ITERATION 1: "5" ✓
═══════════════════════════════════════
stack_a = [5] → NULL
i = 1

═══════════════════════════════════════
ITERATION 2: "3" ✓
═══════════════════════════════════════
stack_a = [5] → [3] → NULL
i = 2

═══════════════════════════════════════
ITERATION 3: "abc" ✗ ERROR!
═══════════════════════════════════════
numbers[2] = "abc"

Validate:
  is_valid_number("abc")? → NO ✗
  Contains non-digit characters!

Error handling:
  free_stack(&stack_a)
    ↓ free([5]), free([3])
  free_split(numbers)
    ↓ free all strings and array
  return (NULL)

═══════════════════════════════════════
RESULT: NULL (Error)
═══════════════════════════════════════
Caller receives NULL
Should print "Error" and exit
```

---

## Complete Algorithm Pseudocode

```
FUNCTION init_stack_a(argc, argv):
    // Step 1: Parse arguments
    numbers = parse_arguments(argc, argv)
    IF numbers is NULL:
        RETURN NULL

    // Step 2: Initialize empty stack
    stack_a = NULL
    i = 0

    // Step 3: Process each number string
    WHILE numbers[i] is not NULL:
        // Validate format
        IF NOT is_valid_number(numbers[i]):
            free_stack(&stack_a)
            IF argc == 2:
                free_split(numbers)
            RETURN NULL

        // Convert to long
        value = ft_atol(numbers[i])

        // Check integer range
        IF NOT is_int_range(value):
            free_stack(&stack_a)
            IF argc == 2:
                free_split(numbers)
            RETURN NULL

        // Create node
        node = stack_new((int)value)
        IF node is NULL:
            free_stack(&stack_a)
            IF argc == 2:
                free_split(numbers)
            RETURN NULL

        // Add to stack
        stack_add_back(&stack_a, node)

        i = i + 1

    // Step 4: Check for duplicates
    IF has_duplicates(stack_a):
        free_stack(&stack_a)
        IF argc == 2:
            free_split(numbers)
        RETURN NULL

    // Step 5: Clean up temporary memory
    IF argc == 2:
        free_split(numbers)

    // Step 6: Return initialized stack
    RETURN stack_a
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: No Arguments

```c
// Command: ./push_swap
int argc = 1;
t_stack *stack = init_stack_a(argc, argv);
// parse_arguments returns NULL
// init_stack_a returns NULL
// Main should exit cleanly (no error per subject)
```

### Edge Case 2: Invalid Number Format

```c
// Command: ./push_swap 5 3a 1
// "3a" is not a valid number
// is_valid_number("3a") returns 0
// init_stack_a returns NULL after freeing
```

### Edge Case 3: Integer Overflow

```c
// Command: ./push_swap 2147483648
// This is INT_MAX + 1
// ft_atol("2147483648") → 2147483648L
// is_int_range(2147483648L) → 0 (too big!)
// init_stack_a returns NULL after freeing
```

### Edge Case 4: Integer Underflow

```c
// Command: ./push_swap -2147483649
// This is INT_MIN - 1
// ft_atol("-2147483649") → -2147483649L
// is_int_range(-2147483649L) → 0 (too small!)
// init_stack_a returns NULL after freeing
```

### Edge Case 5: Duplicate Values

```c
// Command: ./push_swap 5 3 1 3 2
// All numbers valid, all in range
// Stack built: [5] → [3] → [1] → [3] → [2] → NULL
// has_duplicates() finds two 3's
// init_stack_a returns NULL after freeing
```

### Edge Case 6: Single Number

```c
// Command: ./push_swap 42
// Valid input
// Stack: [42] → NULL
// No duplicates (only one number)
// Returns valid stack
// Main will detect already sorted and exit
```

### Edge Case 7: Malloc Failure

```c
// During stack_new() or ft_split()
// If malloc returns NULL
// Must free everything and return NULL
// Prevents memory leaks
```

---

## Time & Space Complexity

### Time Complexity: O(n²)

**Breakdown:**
```
n = number of integers

1. parse_arguments: O(n)
   - ft_split scans string once

2. For each number (n iterations):
   - is_valid_number: O(m) where m = string length
   - ft_atol: O(m)
   - is_int_range: O(1)
   - stack_new: O(1)
   - stack_add_back: O(n) worst case (find last node)

   Per iteration: O(m + n) ≈ O(n) if m is small
   Total: n × O(n) = O(n²)

3. has_duplicates: O(n²)
   - Nested loop comparing all pairs

Overall: O(n²) dominated by duplicate check and repeated add_back
```

**Optimization note:**
- Could optimize stack_add_back by keeping tail pointer
- Would make iteration O(n) instead of O(n²)
- Total would still be O(n²) due to has_duplicates

### Space Complexity: O(n)

**Memory allocation:**
```
1. numbers array (if argc==2):
   - Array of n pointers: O(n)
   - n string copies: O(n)
   - Temporary, freed before return

2. Stack nodes:
   - n nodes × sizeof(t_stack): O(n)
   - Permanent, returned to caller

3. No recursion: O(1) stack space

Total: O(n) - linear in number of integers
```

---

## Relationship with Other Functions

### Functions Called By init_stack_a

1. **parse_arguments()** - Normalizes command line input
2. **is_valid_number()** - Validates each number string format
3. **ft_atol()** - Converts string to long integer
4. **is_int_range()** - Checks if value fits in int
5. **stack_new()** - Creates new stack node
6. **stack_add_back()** - Adds node to end of stack
7. **has_duplicates()** - Checks for duplicate values
8. **free_stack()** - Frees stack on error
9. **free_split()** - Frees parsed array on error

### Functions That Use init_stack_a

1. **main()** - Primary caller, entry point of program

---

## Integration with Push_swap

### Complete main() Flow

```c
int main(int argc, char **argv)
{
    t_stack *stack_a;
    t_stack *stack_b;

    // Initialize stack A from arguments
    stack_a = init_stack_a(argc, argv);
    if (!stack_a)
    {
        // Error occurred during initialization
        // Subject: No output for no args, "Error" for invalid input
        if (argc >= 2)
            print_error();
        return (argc >= 2 ? 1 : 0);
    }

    // Check if already sorted
    if (is_sorted(stack_a))
    {
        free_stack(&stack_a);
        return (0);  // Already sorted, nothing to output
    }

    // Sort the stack
    stack_b = NULL;
    choose_sort(&stack_a, &stack_b);

    // Clean up
    free_stack(&stack_a);
    return (0);
}
```

---

## 42 Norm Considerations

### Norm Compliance

✅ **Function length:** ~35-40 lines (may need helper functions)
⚠️ **Complexity:** High cyclomatic complexity, consider splitting
✅ **Single responsibility:** Initializes stack (but does many sub-tasks)
✅ **Error handling:** Comprehensive cleanup on all errors
✅ **Memory management:** No leaks on any path

### Refactoring Suggestion

To meet norm, split into helper functions:

```c
// Main function
t_stack *init_stack_a(int argc, char **argv)
{
    char    **numbers;
    t_stack *stack_a;

    numbers = parse_arguments(argc, argv);
    if (!numbers)
        return (NULL);
    stack_a = build_stack(numbers, argc);
    if (argc == 2)
        free_split(numbers);
    return (stack_a);
}

// Helper function
static t_stack *build_stack(char **numbers, int argc)
{
    t_stack *stack;
    int     i;

    stack = NULL;
    i = 0;
    while (numbers[i])
    {
        if (!add_number_to_stack(&stack, numbers[i], argc, numbers))
            return (NULL);
        i++;
    }
    if (has_duplicates(stack))
    {
        free_stack(&stack);
        return (NULL);
    }
    return (stack);
}

// Helper function
static int add_number_to_stack(t_stack **stack, char *str,
                               int argc, char **numbers)
{
    long     value;
    t_stack  *node;

    if (!is_valid_number(str))
        return (cleanup_and_fail(stack, numbers, argc));
    value = ft_atol(str);
    if (!is_int_range(value))
        return (cleanup_and_fail(stack, numbers, argc));
    node = stack_new((int)value);
    if (!node)
        return (cleanup_and_fail(stack, numbers, argc));
    stack_add_back(stack, node);
    return (1);
}
```

---

## Common Mistakes to Avoid

### Mistake 1: Memory Leaks on Error

```c
❌ WRONG:
t_stack *init_stack_a(int argc, char **argv)
{
    char **numbers = parse_arguments(argc, argv);
    // ... build stack ...
    if (has_duplicates(stack_a))
        return (NULL);  // Leaked numbers and stack!
}

✓ CORRECT:
if (has_duplicates(stack_a))
{
    free_stack(&stack_a);
    if (argc == 2)
        free_split(numbers);
    return (NULL);
}
```

### Mistake 2: Forgetting to Check Malloc

```c
❌ WRONG:
t_stack *node = stack_new(value);
stack_add_back(&stack_a, node);  // What if node is NULL?

✓ CORRECT:
t_stack *node = stack_new(value);
if (!node)
{
    // Free everything and return NULL
}
stack_add_back(&stack_a, node);
```

### Mistake 3: Not Checking Range After Conversion

```c
❌ WRONG:
long value = ft_atol(numbers[i]);
t_stack *node = stack_new((int)value);  // Truncation!

✓ CORRECT:
long value = ft_atol(numbers[i]);
if (!is_int_range(value))
{
    // Handle error
}
t_stack *node = stack_new((int)value);  // Safe cast
```

### Mistake 4: Inconsistent Memory Management

```c
❌ WRONG:
// Always free numbers
free_split(numbers);
return (stack_a);

Problem: If argc > 2, numbers points to argv (not allocated!)

✓ CORRECT:
if (argc == 2)
    free_split(numbers);
return (stack_a);
```

### Mistake 5: Not Validating Before Converting

```c
❌ WRONG:
long value = ft_atol(numbers[i]);  // What if numbers[i] = "abc"?

✓ CORRECT:
if (!is_valid_number(numbers[i]))
    return (error_cleanup(...));
long value = ft_atol(numbers[i]);  // Now safe
```

---

## Testing Strategy

### Test Case 1: Valid Input

```bash
$ ./push_swap 5 3 1 4 2
# init_stack_a should succeed
# Returns stack: [5]→[3]→[1]→[4]→[2]→NULL
# All nodes allocated
# No memory leaks
```

### Test Case 2: Invalid Number Format

```bash
$ ./push_swap 5 3a 1
# init_stack_a should fail
# Returns NULL
# All memory freed
# Error printed
```

### Test Case 3: Integer Overflow

```bash
$ ./push_swap 2147483648
# init_stack_a should fail
# Returns NULL
# Error printed
```

### Test Case 4: Duplicates

```bash
$ ./push_swap 5 3 1 3 2
# init_stack_a should fail
# Returns NULL
# Stack freed before return
# Error printed
```

### Test Case 5: Memory Leak Check

```bash
$ valgrind ./push_swap 5 3 1 4 2
# Should show:
# All heap blocks freed
# No memory leaks
# Both success and error paths
```

### Test Case 6: Edge Values

```bash
$ ./push_swap -2147483648 0 2147483647
# INT_MIN, 0, INT_MAX
# Should succeed
# Returns valid stack
```

---

## Summary: What init_stack_a Does

1. **Parses** command line arguments into array of strings
2. **Validates** each string is a properly formatted number
3. **Converts** validated strings to long integers
4. **Checks** each value fits in int range (INT_MIN to INT_MAX)
5. **Creates** stack nodes for each valid integer
6. **Builds** linked list stack structure
7. **Verifies** no duplicate values exist
8. **Cleans up** temporary memory (numbers array)
9. **Returns** fully initialized stack or NULL on error

**Key insight:** This is the gatekeeper function. It ensures that only valid, duplicate-free, in-range integers make it into your stack. By the time this function returns, you have a guarantee that your data is clean and ready to sort.

---

## Location in Project

**File:** `srcs/stack_init.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 2.2 (Parsing & Validation - Stack Initialization)

**Function prototype:**
```c
t_stack *init_stack_a(int argc, char **argv);
```

---

## Related Functions

**Depends on:**
- `parse_arguments()` - Argument parsing
- `is_valid_number()` - Format validation
- `ft_atol()` - String to long conversion
- `is_int_range()` - Range checking
- `stack_new()` - Node creation
- `stack_add_back()` - Stack building
- `has_duplicates()` - Duplicate detection
- `free_stack()` - Cleanup
- `free_split()` - Cleanup

**Used by:**
- `main()` - Program entry point

---

*Remember: Thorough validation at initialization prevents bugs during sorting. Take the time to check everything now, and the rest of your program can trust its data!*
