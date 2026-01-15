# init_stack_a - Initialize Stack A from Command Line Arguments

## Function Signature

```c
t_stack *init_stack_a(int argc, char **argv)
```

**Return type:** `t_stack *` - Pointer to head of initialized stack A (or NULL on error)
**Parameters:**
- `int argc` - Number of command line arguments
- `char **argv` - Array of command line argument strings

**Static Helpers:** Uses `append_node()` and `build_stack()` for 42 Norm compliance
- See [append_node.md](append_node.md) for node creation helper
- See [build_stack.md](build_stack.md) for stack building helper

---

## Purpose & Use Case

`init_stack_a` is the **orchestrator function** that transforms raw command line input into a validated, ready-to-sort stack. This is the most complex initialization function in push_swap because it coordinates parsing, validation, conversion, and stack building into one cohesive process.

**42 Norm Note:** This function is split into three smaller functions (`init_stack_a`, `build_stack`, `append_node`) to stay under the 25-line limit while maintaining code readability.

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

### The Complete Pipeline (Refactored)

```
┌─────────────────────────────────────────────────────────────┐
│                    init_stack_a(argc, argv)                 │
│                    (Main Entry Point)                        │
├─────────────────────────────────────────────────────────────┤
│                                                              │
│  Phase 1: PARSING                                            │
│  Input: argc, argv                                           │
│  ↓                                                           │
│  parse_arguments()                                           │
│  ↓                                                           │
│  Output: numbers = ["5", "3", "1", "4", "2", NULL]          │
│                                                              │
│  Phase 2: BUILD STACK (delegated to helper)                  │
│  ↓                                                           │
│  ┌─────────────────────────────────────────────────────────┐│
│  │              build_stack(numbers)                        ││
│  │              (Static Helper)                             ││
│  ├─────────────────────────────────────────────────────────┤│
│  │  For each number in array:                               ││
│  │  ↓                                                       ││
│  │  ┌─────────────────────────────────────────────────────┐││
│  │  │           append_node(&stack, str)                  │││
│  │  │           (Static Helper)                           │││
│  │  ├─────────────────────────────────────────────────────┤││
│  │  │  1. is_valid_number("5")? → YES ✓                   │││
│  │  │  2. ft_atol("5") → 5L                               │││
│  │  │  3. is_int_range(5L)? → YES ✓                       │││
│  │  │  4. stack_new(5) → node                             │││
│  │  │  5. stack_add_back(&stack, node)                    │││
│  │  │  6. Return node (success)                           │││
│  │  └─────────────────────────────────────────────────────┘││
│  │  ↓                                                       ││
│  │  has_duplicates(stack)? → NO ✓                          ││
│  │  ↓                                                       ││
│  │  Return stack                                            ││
│  └─────────────────────────────────────────────────────────┘│
│                                                              │
│  Phase 3: CLEANUP & RETURN                                   │
│  if (argc == 2) free_split(numbers)                          │
│  ↓                                                           │
│  Return stack (SUCCESS!)                                     │
└─────────────────────────────────────────────────────────────┘

Final stack: [5] → [3] → [1] → [4] → [2] → NULL
```

### Function Hierarchy

```
init_stack_a()          ~15 lines (PUBLIC)
    │
    ├── parse_arguments()
    │
    └── build_stack()   ~18 lines (STATIC)
            │
            └── append_node()  ~12 lines (STATIC)
                    │
                    ├── is_valid_number()
                    ├── ft_atol()
                    ├── is_int_range()
                    ├── stack_new()
                    └── stack_add_back()
```

### Step-by-Step Implementation (Refactored)

**Note:** This function is split into three parts for 42 Norm compliance:
- `init_stack_a` - Main entry point (~15 lines)
- `build_stack` - Static helper that builds the stack (~18 lines)
- `append_node` - Static helper that adds one node (~12 lines)

#### Step 1: Parse Arguments (init_stack_a)

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

#### Step 2: Build Stack (init_stack_a)

```c
stack_a = build_stack(numbers);
if (!stack_a)
{
    if (argc == 2)
        free_split(numbers);
    return (NULL);
}
```

**What happens:**
- Delegates all stack construction to build_stack helper
- build_stack handles validation, creation, and duplicate check
- On failure, clean up numbers array if needed

#### Step 3: Clean Up and Return (init_stack_a)

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

### Helper Function: build_stack

#### Step 1: Initialize Empty Stack

```c
t_stack *stack = NULL;
int i = 0;
```

**Starting state:**
- Empty stack (NULL pointer)
- Counter for array iteration

#### Step 2: Iterate and Add Each Number

```c
while (numbers[i])
{
    if (!append_node(&stack, numbers[i]))
    {
        free_stack(&stack);
        return (NULL);
    }
    i++;
}
```

**What happens:**
- For each number string, call append_node
- append_node handles validation, conversion, and creation
- On any failure, free partial stack and return NULL

#### Step 3: Check for Duplicates

```c
if (has_duplicates(stack))
{
    free_stack(&stack);
    return (NULL);
}
return (stack);
```

**Why check after building:**
- More efficient to check once at end
- Could check during building but slower
- Duplicates are rare in valid input

---

### Helper Function: append_node

#### Step 1: Validate Number Format

```c
if (!is_valid_number(str))
    return (NULL);
```

**What is_valid_number checks:**
- Optional sign (+/-)
- Only digits
- No leading zeros (except "0")
- Not empty string

#### Step 2: Convert and Check Range

```c
value = ft_atol(str);
if (!is_int_range(value))
    return (NULL);
```

**Why long?**
- int range: -2,147,483,648 to 2,147,483,647
- Need to detect overflow before casting
- long can hold bigger values for detection

#### Step 3: Create and Add Node

```c
node = stack_new((int)value);
if (!node)
    return (NULL);
stack_add_back(stack, node);
return (node);
```

**What happens:**
- Create node with validated value
- Add to end of stack
- Return node pointer to signal success

---

## Visual Execution Trace (Refactored)

### Example: Complete Initialization

```
Command: ./push_swap "5 3 1 4 2"

╔═══════════════════════════════════════════════════════════════╗
║                    init_stack_a(2, argv)                       ║
╚═══════════════════════════════════════════════════════════════╝

═══════════════════════════════════════
STEP 1: PARSE ARGUMENTS (init_stack_a)
═══════════════════════════════════════
parse_arguments(2, ["./push_swap", "5 3 1 4 2"])
↓
ft_split("5 3 1 4 2", ' ')
↓
numbers = ["5", "3", "1", "4", "2", NULL]
          ↑                         ↑
          allocated              terminator

═══════════════════════════════════════
STEP 2: BUILD STACK (init_stack_a calls build_stack)
═══════════════════════════════════════

  ╔═════════════════════════════════════════════════════════╗
  ║              build_stack(numbers)                        ║
  ╚═════════════════════════════════════════════════════════╝

  Initialize: stack = NULL, i = 0

  ┌─────────────────────────────────────────────────────────┐
  │ ITERATION 1: append_node(&stack, "5")                   │
  ├─────────────────────────────────────────────────────────┤
  │ is_valid_number("5")? → YES ✓                           │
  │ ft_atol("5") → 5L                                       │
  │ is_int_range(5L)? → YES ✓                               │
  │ stack_new(5) → node [value:5, index:-1, next:NULL]      │
  │ stack_add_back(&stack, node)                            │
  │ Return: node (success)                                  │
  │                                                         │
  │ stack = [5] → NULL                                      │
  └─────────────────────────────────────────────────────────┘
  i = 1

  ┌─────────────────────────────────────────────────────────┐
  │ ITERATION 2: append_node(&stack, "3")                   │
  ├─────────────────────────────────────────────────────────┤
  │ Validate ✓ → Convert 3L ✓ → Range ✓ → Create → Add      │
  │ stack = [5] → [3] → NULL                                │
  └─────────────────────────────────────────────────────────┘
  i = 2

  ┌─────────────────────────────────────────────────────────┐
  │ ITERATION 3: append_node(&stack, "1")                   │
  ├─────────────────────────────────────────────────────────┤
  │ Validate ✓ → Convert 1L ✓ → Range ✓ → Create → Add      │
  │ stack = [5] → [3] → [1] → NULL                          │
  └─────────────────────────────────────────────────────────┘
  i = 3

  ┌─────────────────────────────────────────────────────────┐
  │ ITERATION 4: append_node(&stack, "4")                   │
  ├─────────────────────────────────────────────────────────┤
  │ Validate ✓ → Convert 4L ✓ → Range ✓ → Create → Add      │
  │ stack = [5] → [3] → [1] → [4] → NULL                    │
  └─────────────────────────────────────────────────────────┘
  i = 4

  ┌─────────────────────────────────────────────────────────┐
  │ ITERATION 5: append_node(&stack, "2")                   │
  ├─────────────────────────────────────────────────────────┤
  │ Validate ✓ → Convert 2L ✓ → Range ✓ → Create → Add      │
  │ stack = [5] → [3] → [1] → [4] → [2] → NULL              │
  └─────────────────────────────────────────────────────────┘
  i = 5

  Loop exit: numbers[5] = NULL

  ┌─────────────────────────────────────────────────────────┐
  │ DUPLICATE CHECK: has_duplicates(stack)                  │
  ├─────────────────────────────────────────────────────────┤
  │ 5 vs 3,1,4,2 → all different ✓                          │
  │ 3 vs 1,4,2   → all different ✓                          │
  │ 1 vs 4,2     → all different ✓                          │
  │ 4 vs 2       → all different ✓                          │
  │ Result: NO DUPLICATES ✓                                 │
  └─────────────────────────────────────────────────────────┘

  Return: stack = [5] → [3] → [1] → [4] → [2] → NULL

═══════════════════════════════════════
STEP 3: CLEANUP & RETURN (init_stack_a)
═══════════════════════════════════════
argc == 2, so free numbers array:
  free_split(numbers)
  ↓
  free("5"), free("3"), free("1"), free("4"), free("2")
  free(array)

return stack_a

╔═══════════════════════════════════════════════════════════════╗
║ Final stack: [5] → [3] → [1] → [4] → [2] → NULL               ║
║ Ready to sort! ✅                                              ║
╚═══════════════════════════════════════════════════════════════╝
```

### Example: Error During Validation

```
Command: ./push_swap "5 3 abc 4 2"

╔═══════════════════════════════════════════════════════════════╗
║                    init_stack_a(2, argv)                       ║
╚═══════════════════════════════════════════════════════════════╝

═══════════════════════════════════════
STEP 1: PARSE (init_stack_a)
═══════════════════════════════════════
numbers = ["5", "3", "abc", "4", "2", NULL]

═══════════════════════════════════════
STEP 2: BUILD STACK (init_stack_a calls build_stack)
═══════════════════════════════════════

  ╔═════════════════════════════════════════════════════════╗
  ║              build_stack(numbers)                        ║
  ╚═════════════════════════════════════════════════════════╝

  ┌─────────────────────────────────────────────────────────┐
  │ ITERATION 1: append_node(&stack, "5") → SUCCESS         │
  │ stack = [5] → NULL                                      │
  └─────────────────────────────────────────────────────────┘

  ┌─────────────────────────────────────────────────────────┐
  │ ITERATION 2: append_node(&stack, "3") → SUCCESS         │
  │ stack = [5] → [3] → NULL                                │
  └─────────────────────────────────────────────────────────┘

  ┌─────────────────────────────────────────────────────────┐
  │ ITERATION 3: append_node(&stack, "abc") → FAIL!         │
  ├─────────────────────────────────────────────────────────┤
  │ is_valid_number("abc")? → NO ✗                          │
  │ Contains non-digit characters!                          │
  │ Return: NULL                                            │
  └─────────────────────────────────────────────────────────┘

  ┌─────────────────────────────────────────────────────────┐
  │ ERROR HANDLING in build_stack:                          │
  ├─────────────────────────────────────────────────────────┤
  │ append_node returned NULL                               │
  │ free_stack(&stack) → free [5], free [3]                 │
  │ Return: NULL                                            │
  └─────────────────────────────────────────────────────────┘

═══════════════════════════════════════
STEP 3: ERROR HANDLING (init_stack_a)
═══════════════════════════════════════
build_stack returned NULL

argc == 2, so free numbers array:
  free_split(numbers)
  ↓
  free all strings and array

return (NULL)

╔═══════════════════════════════════════════════════════════════╗
║ RESULT: NULL (Error)                                           ║
║ Caller receives NULL → should print "Error" and exit          ║
╚═══════════════════════════════════════════════════════════════╝
```

---

## Complete Algorithm Pseudocode (Refactored)

**Note:** Split into three functions for 42 Norm compliance.

### Main Function: init_stack_a

```
FUNCTION init_stack_a(argc, argv):
    // Step 1: Parse arguments
    numbers = parse_arguments(argc, argv)
    IF numbers is NULL:
        RETURN NULL

    // Step 2: Build stack using helper
    stack_a = build_stack(numbers)
    IF stack_a is NULL:
        IF argc == 2:
            free_split(numbers)
        RETURN NULL

    // Step 3: Clean up and return
    IF argc == 2:
        free_split(numbers)
    RETURN stack_a
END FUNCTION
```

### Static Helper: build_stack

```
FUNCTION build_stack(numbers):
    // Step 1: Initialize empty stack
    stack = NULL
    i = 0

    // Step 2: Process each number string
    WHILE numbers[i] is not NULL:
        // Validate, convert, create, and add node
        IF append_node(&stack, numbers[i]) is NULL:
            free_stack(&stack)
            RETURN NULL
        i = i + 1

    // Step 3: Check for duplicates
    IF has_duplicates(stack):
        free_stack(&stack)
        RETURN NULL

    // Step 4: Return completed stack
    RETURN stack
END FUNCTION
```

### Static Helper: append_node

```
FUNCTION append_node(stack, str):
    // Step 1: Validate format
    IF NOT is_valid_number(str):
        RETURN NULL

    // Step 2: Convert to long
    value = ft_atol(str)

    // Step 3: Check integer range
    IF NOT is_int_range(value):
        RETURN NULL

    // Step 4: Create node
    node = stack_new((int)value)
    IF node is NULL:
        RETURN NULL

    // Step 5: Add to stack and return
    stack_add_back(stack, node)
    RETURN node
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

| Requirement | Status | Notes |
|-------------|--------|-------|
| Function length | Split into helpers | Each function under 25 lines |
| Static helpers | build_stack, append_node | Encapsulate sub-tasks |
| Single responsibility | Each function has one job | Clean separation |
| Error handling | Comprehensive | Cleanup on all error paths |
| Memory management | No leaks | All paths properly cleaned up |
| Max parameters | Varies | All within limits |

### Required Refactoring: Split into Helper Functions

To meet 42 Norm requirements, `init_stack_a` MUST be split into smaller functions:

**File Structure in `stack_init.c`:**
```
1. static t_stack *append_node(t_stack **stack, char *str)
   - Validates, converts, creates, and adds one node
   - Returns node on success, NULL on failure

2. static t_stack *build_stack(char **numbers)
   - Iterates through numbers array
   - Calls append_node for each number
   - Returns completed stack or NULL on error

3. t_stack *init_stack_a(int argc, char **argv)
   - Main entry point (PUBLIC)
   - Calls parse_arguments and build_stack
   - Handles memory cleanup
```

### Static Helper 1: append_node

**Purpose:** Validate, convert, create, and add a single node to the stack.

```c
static t_stack *append_node(t_stack **stack, char *str)
{
    long    value;
    t_stack *node;

    if (!is_valid_number(str))
        return (NULL);
    value = ft_atol(str);
    if (!is_int_range(value))
        return (NULL);
    node = stack_new((int)value);
    if (!node)
        return (NULL);
    stack_add_back(stack, node);
    return (node);
}
```

**Line count:** ~12 lines

See [append_node.md](append_node.md) for complete documentation.

### Static Helper 2: build_stack

**Purpose:** Build complete stack from numbers array, validate no duplicates.

```c
static t_stack *build_stack(char **numbers)
{
    t_stack *stack;
    int     i;

    stack = NULL;
    i = 0;
    while (numbers[i])
    {
        if (!append_node(&stack, numbers[i]))
        {
            free_stack(&stack);
            return (NULL);
        }
        i++;
    }
    if (has_duplicates(stack))
    {
        free_stack(&stack);
        return (NULL);
    }
    return (stack);
}
```

**Line count:** ~18 lines

See [build_stack.md](build_stack.md) for complete documentation.

### Main Function: init_stack_a (Refactored)

**Purpose:** Entry point - orchestrate parsing and stack building.

```c
t_stack *init_stack_a(int argc, char **argv)
{
    char    **numbers;
    t_stack *stack_a;

    numbers = parse_arguments(argc, argv);
    if (!numbers)
        return (NULL);
    stack_a = build_stack(numbers);
    if (!stack_a)
    {
        if (argc == 2)
            free_split(numbers);
        return (NULL);
    }
    if (argc == 2)
        free_split(numbers);
    return (stack_a);
}
```

**Line count:** ~15 lines

### Line Count Summary

| Function | Lines | Norm Limit | Status |
|----------|-------|------------|--------|
| append_node | ~12 | 25 | PASS |
| build_stack | ~18 | 25 | PASS |
| init_stack_a | ~15 | 25 | PASS |

**Total functions in stack_init.c:** 3 (under 5 function limit per file)

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
