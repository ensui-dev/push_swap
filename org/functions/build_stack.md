# build_stack - Build Complete Stack from Numbers Array (Static Helper)

## Function Signature

```c
static t_stack *build_stack(char **numbers)
```

**IMPORTANT:** This is a **STATIC helper function** - not declared in header file!

**Return type:** `t_stack *` - Pointer to head of built stack, or NULL on error
**Parameters:**
- `char **numbers` - NULL-terminated array of number strings to process

**Visibility:** File-scope only (static) - internal to `stack_init.c`

---

## Purpose & Use Case

`build_stack` is a **static helper function** that constructs a complete stack from a parsed array of number strings. It iterates through all numbers, validates and adds each one, then performs a final duplicate check.

### When You'll Use It

This function is called internally by `init_stack_a` to:
1. **Iterate** through all number strings in the array
2. **Call** append_node for each number (validation + creation)
3. **Handle** errors from any invalid number
4. **Check** for duplicate values after building
5. **Return** the completed stack or NULL on error

### Why This Matters

**The Problem (Without Helper):**
```c
// In init_stack_a - too much code in one function!
t_stack *init_stack_a(int argc, char **argv)
{
    // ... parse arguments ...

    // Build stack (many lines)
    i = 0;
    while (numbers[i])
    {
        if (!is_valid_number(numbers[i]))
            // ... cleanup and return ...
        value = ft_atol(numbers[i]);
        if (!is_int_range(value))
            // ... cleanup and return ...
        node = stack_new((int)value);
        if (!node)
            // ... cleanup and return ...
        stack_add_back(&stack, node);
        i++;
    }
    if (has_duplicates(stack))
        // ... cleanup and return ...

    // ... final cleanup ...
}
// Function exceeds 25 lines!
// 42 Norm VIOLATION!
```

**The Solution (With Helper):**
```c
// Clean separation of concerns
t_stack *init_stack_a(int argc, char **argv)
{
    numbers = parse_arguments(argc, argv);
    if (!numbers)
        return (NULL);
    stack_a = build_stack(numbers);  // <-- All building logic here
    // ... cleanup ...
    return (stack_a);
}
// Function stays under 25 lines
// 42 Norm COMPLIANT!
```

---

## Deep Dive: How It Works

### The Core Logic

```
build_stack(numbers):
    1. Initialize empty stack
    2. For each number in array:
       a. Call append_node (validates + creates + adds)
       b. If append_node fails, free stack and return NULL
    3. Check for duplicates
    4. Return completed stack (or NULL if duplicates found)
```

### Why Separate from init_stack_a?

**Separation of concerns:**
- `init_stack_a`: Handles parsing, memory ownership (argc==2 check)
- `build_stack`: Handles stack construction and validation
- `append_node`: Handles single number processing

**Benefits:**
- Each function under 25 lines
- Clear responsibility boundaries
- Easier testing and debugging

### Step-by-Step Process

#### Step 1: Initialize Empty Stack

```c
t_stack *stack;
int     i;

stack = NULL;
i = 0;
```

**Starting state:**
- Empty stack pointer
- Index counter for array iteration

#### Step 2: Iterate Through Numbers Array

```c
while (numbers[i])
{
    // Process each number
    i++;
}
```

**Array structure:**
```
numbers = ["5", "3", "1", "4", "2", NULL]
           ↑                         ↑
           i=0                    terminator
```

#### Step 3: Process Each Number with append_node

```c
if (!append_node(&stack, numbers[i]))
{
    free_stack(&stack);
    return (NULL);
}
```

**What append_node does:**
- Validates number format
- Converts to long
- Checks integer range
- Creates node
- Adds to stack
- Returns node (or NULL on failure)

**Error handling:**
- If append_node returns NULL, something failed
- Free any nodes already created
- Return NULL to signal error

#### Step 4: Check for Duplicates

```c
if (has_duplicates(stack))
{
    free_stack(&stack);
    return (NULL);
}
```

**Why check after building:**
- More efficient than checking during each addition
- Duplicate check is O(n^2) regardless
- Keeps append_node simple and focused

#### Step 5: Return Completed Stack

```c
return (stack);
```

**Success state:**
- All numbers validated and added
- No duplicates found
- Stack ready for sorting

---

## Visual Execution Trace

### Example 1: Successful Build

```
Input: build_stack(["5", "3", "1", NULL])

Initialize:
stack = NULL
i = 0

--- Iteration 1: i = 0 ---
numbers[0] = "5"
append_node(&stack, "5")
    -> validates "5" -> OK
    -> converts to 5L
    -> range check -> OK
    -> creates node [5]
    -> adds to stack
    -> returns node
Result: stack = [5] -> NULL
i = 1

--- Iteration 2: i = 1 ---
numbers[1] = "3"
append_node(&stack, "3")
    -> validates "3" -> OK
    -> converts to 3L
    -> range check -> OK
    -> creates node [3]
    -> adds to stack
    -> returns node
Result: stack = [5] -> [3] -> NULL
i = 2

--- Iteration 3: i = 2 ---
numbers[2] = "1"
append_node(&stack, "1")
    -> validates "1" -> OK
    -> converts to 1L
    -> range check -> OK
    -> creates node [1]
    -> adds to stack
    -> returns node
Result: stack = [5] -> [3] -> [1] -> NULL
i = 3

--- Loop Exit: i = 3 ---
numbers[3] = NULL
Exit while loop

--- Duplicate Check ---
has_duplicates(stack)?
    5 vs 3,1 -> all different
    3 vs 1   -> all different
Result: NO DUPLICATES

--- Return ---
return stack = [5] -> [3] -> [1] -> NULL
SUCCESS!
```

### Example 2: Invalid Number in Middle

```
Input: build_stack(["5", "abc", "1", NULL])

Initialize:
stack = NULL
i = 0

--- Iteration 1: i = 0 ---
numbers[0] = "5"
append_node(&stack, "5") -> returns node
stack = [5] -> NULL
i = 1

--- Iteration 2: i = 1 ---
numbers[1] = "abc"
append_node(&stack, "abc")
    -> validates "abc" -> FAIL!
    -> returns NULL

Error handling:
free_stack(&stack)
    -> frees [5]
return (NULL)

RESULT: NULL (error)
```

### Example 3: Duplicates Found

```
Input: build_stack(["5", "3", "5", NULL])

Initialize:
stack = NULL
i = 0

--- Iteration 1 ---
append_node(&stack, "5") -> OK
stack = [5] -> NULL

--- Iteration 2 ---
append_node(&stack, "3") -> OK
stack = [5] -> [3] -> NULL

--- Iteration 3 ---
append_node(&stack, "5") -> OK
stack = [5] -> [3] -> [5] -> NULL

--- Duplicate Check ---
has_duplicates(stack)?
    5 vs 3,5 -> DUPLICATE FOUND! (5 == 5)
Result: DUPLICATES EXIST

Error handling:
free_stack(&stack)
    -> frees [5], [3], [5]
return (NULL)

RESULT: NULL (duplicates)
```

### Example 4: Integer Overflow

```
Input: build_stack(["5", "9999999999", NULL])

--- Iteration 1 ---
append_node(&stack, "5") -> OK
stack = [5] -> NULL

--- Iteration 2 ---
append_node(&stack, "9999999999")
    -> validates "9999999999" -> OK (all digits)
    -> converts to 9999999999L
    -> range check -> FAIL! (> INT_MAX)
    -> returns NULL

Error handling:
free_stack(&stack)
    -> frees [5]
return (NULL)

RESULT: NULL (overflow)
```

---

## Complete Algorithm Pseudocode

### High-Level Overview

```
FUNCTION build_stack(numbers):
    // Initialize
    stack = NULL
    i = 0

    // Build stack from all numbers
    WHILE numbers[i] is not NULL:
        IF NOT append_node(&stack, numbers[i]):
            free_stack(&stack)
            RETURN NULL
        i = i + 1

    // Verify no duplicates
    IF has_duplicates(stack):
        free_stack(&stack)
        RETURN NULL

    // Return completed stack
    RETURN stack
END FUNCTION
```

### Detailed Implementation

```
FUNCTION build_stack(numbers):
    DECLARE stack AS pointer to t_stack
    DECLARE i AS integer

    // Step 1: Initialize empty stack
    stack = NULL
    i = 0

    // Step 2: Iterate through all number strings
    WHILE numbers[i] is not NULL:
        // Step 3: Validate, create, and add node
        // append_node handles:
        // - Format validation
        // - String to long conversion
        // - Integer range check
        // - Node creation
        // - Stack addition
        IF append_node(&stack, numbers[i]) returns NULL:
            // Validation or creation failed
            // Clean up any nodes already created
            free_stack(&stack)
            RETURN NULL

        // Move to next number
        i = i + 1
    // END WHILE

    // Step 4: Check for duplicate values
    IF has_duplicates(stack) returns true:
        // Duplicates found - invalid input
        free_stack(&stack)
        RETURN NULL

    // Step 5: Return successfully built stack
    RETURN stack
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: Empty Numbers Array

```c
char **numbers = /* just NULL terminator */;
t_stack *result = build_stack(numbers);
// Loop doesn't execute (numbers[0] is NULL)
// has_duplicates(NULL) should handle empty stack
// result = NULL or empty stack (depends on has_duplicates)
```

**Handling:** Empty array leads to empty stack.

### Edge Case 2: Single Number

```c
char **numbers = {"42", NULL};
t_stack *result = build_stack(numbers);
// One iteration, one node
// No duplicates possible with one element
// result = valid stack [42] -> NULL
```

**Handling:** Single element always succeeds (no duplicate possible).

### Edge Case 3: First Number Invalid

```c
char **numbers = {"abc", "1", "2", NULL};
t_stack *result = build_stack(numbers);
// First append_node fails
// stack is still NULL (no nodes to free)
// result = NULL
```

**Handling:** Early failure, minimal cleanup needed.

### Edge Case 4: Last Number Invalid

```c
char **numbers = {"1", "2", "abc", NULL};
t_stack *result = build_stack(numbers);
// First two succeed, third fails
// Stack has [1] -> [2] -> NULL
// free_stack frees both nodes
// result = NULL
```

**Handling:** Partial stack properly cleaned up.

### Edge Case 5: All Same Numbers (Duplicates)

```c
char **numbers = {"5", "5", "5", NULL};
t_stack *result = build_stack(numbers);
// All append_node calls succeed
// Stack: [5] -> [5] -> [5] -> NULL
// has_duplicates finds duplicates
// Stack freed
// result = NULL
```

**Handling:** Duplicate check catches at the end.

---

## Time & Space Complexity

### Time Complexity: O(n^2)

```
n = number of elements in numbers array

Operations:
1. Building loop: O(n) iterations
   - Each append_node: O(m + k) where m = string length, k = current stack size
   - stack_add_back traverses to end: O(k)
   - Total for loop: O(n * n) = O(n^2)

2. Duplicate check: O(n^2)
   - Nested comparison of all pairs

Overall: O(n^2) dominated by stack_add_back and has_duplicates
```

**Optimization note:**
- Could keep tail pointer to make add_back O(1)
- Would reduce build phase to O(n)
- Still O(n^2) due to duplicate check

### Space Complexity: O(n)

```
Memory used:
- stack pointer: O(1)
- i counter: O(1)
- n stack nodes: O(n)

Total: O(n) for the stack itself
```

---

## Relationship with Other Functions

### Functions Called By build_stack

1. **append_node()** - Validates and adds each number
2. **free_stack()** - Cleans up on error
3. **has_duplicates()** - Final validation

### Functions That Call build_stack

1. **init_stack_a()** - Main entry point

---

## Integration with Push_swap

### Usage in init_stack_a()

```c
t_stack *init_stack_a(int argc, char **argv)
{
    char    **numbers;
    t_stack *stack_a;

    numbers = parse_arguments(argc, argv);
    if (!numbers)
        return (NULL);
    stack_a = build_stack(numbers);  // <-- Used here
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

**Flow diagram:**
```
init_stack_a(argc, argv)
    |
    +-- parse_arguments() -> numbers array
    |
    +-- build_stack(numbers)  <- You are here
    |       |
    |       +-- for each number:
    |       |       append_node() -> validates + creates + adds
    |       |
    |       +-- has_duplicates() -> final check
    |       |
    |       +-- return stack or NULL
    |
    +-- cleanup numbers if needed
    |
    +-- return stack_a
```

---

## 42 Norm Considerations

### Norm Compliance Checklist

| Requirement | Status | Notes |
|-------------|--------|-------|
| Function length | ~18 lines | Under 25-line limit |
| Static function | File-scope | Not in header |
| Single responsibility | Build stack | Delegates validation |
| Parameters | 1 | Minimal interface |
| Return type | t_stack* | Clear success/failure |

### Why Static is Important

**42 Norm requirements:**
- Main functions should be under 25 lines
- Helper functions should be static (file-scope)
- No unnecessary exposure in header files

**Function hierarchy:**
```
Public:  init_stack_a()     ~15 lines
Static:  build_stack()      ~18 lines
Static:  append_node()      ~12 lines
```

### Implementation Structure

```c
// File: srcs/stack_init.c

// Static helper 1 - NOT in header
static t_stack *append_node(t_stack **stack, char *str)
{
    // Single number processing
}

// Static helper 2 - NOT in header
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

// Public function - declared in header
t_stack *init_stack_a(int argc, char **argv)
{
    // Orchestrates parsing and building
}
```

---

## Common Mistakes to Avoid

### Mistake 1: Not Freeing Stack on Error

```c
// WRONG:
if (!append_node(&stack, numbers[i]))
    return (NULL);  // Leaked previously added nodes!

// CORRECT:
if (!append_node(&stack, numbers[i]))
{
    free_stack(&stack);
    return (NULL);
}
```

### Mistake 2: Checking Duplicates Before Complete Build

```c
// WRONG:
while (numbers[i])
{
    if (!append_node(&stack, numbers[i]))
        // ...
    if (has_duplicates(stack))  // Checking every iteration!
        // ...
    i++;
}

Problem: O(n^3) complexity, inefficient
Solution: Check once after all numbers added
```

### Mistake 3: Not Handling Empty Array

```c
// WRONG:
stack = NULL;
i = 0;
while (numbers[i])  // What if numbers[0] is NULL?
{
    // ...
}
return (stack);  // Returns NULL - is this correct behavior?

Note: Empty array is usually handled by caller (init_stack_a)
Make sure this case is tested
```

### Mistake 4: Double Free

```c
// WRONG:
if (!append_node(&stack, numbers[i]))
{
    free_stack(&stack);
    return (NULL);
}
// ... later ...
if (has_duplicates(stack))
{
    free_stack(&stack);
    return (NULL);  // What if we already freed above?
}

Note: This specific example won't double-free because
we return immediately after first free.
But be careful with more complex error paths.
```

### Mistake 5: Forgetting NULL Terminator Check

```c
// WRONG:
for (i = 0; i < some_count; i++)
{
    append_node(&stack, numbers[i]);
}

Problem: If some_count is wrong, may access beyond array
Solution: Use while (numbers[i]) to rely on NULL terminator
```

---

## Testing Strategy

### Test Case 1: Valid Numbers

```c
char *numbers[] = {"5", "3", "1", NULL};
t_stack *result = build_stack(numbers);
assert(result != NULL);
assert(result->value == 5);
assert(result->next->value == 3);
assert(result->next->next->value == 1);
free_stack(&result);
```

### Test Case 2: Invalid Number

```c
char *numbers[] = {"5", "abc", "1", NULL};
t_stack *result = build_stack(numbers);
assert(result == NULL);
// Valgrind: no leaks
```

### Test Case 3: Duplicates

```c
char *numbers[] = {"5", "3", "5", NULL};
t_stack *result = build_stack(numbers);
assert(result == NULL);
// Valgrind: no leaks
```

### Test Case 4: Single Number

```c
char *numbers[] = {"42", NULL};
t_stack *result = build_stack(numbers);
assert(result != NULL);
assert(result->value == 42);
assert(result->next == NULL);
free_stack(&result);
```

### Test Case 5: Large Numbers (Boundary)

```c
char *numbers[] = {"-2147483648", "0", "2147483647", NULL};
t_stack *result = build_stack(numbers);
assert(result != NULL);
// INT_MIN, 0, INT_MAX all valid
free_stack(&result);
```

### Test Case 6: Overflow

```c
char *numbers[] = {"1", "9999999999", NULL};
t_stack *result = build_stack(numbers);
assert(result == NULL);
// First node freed on error
// Valgrind: no leaks
```

---

## Summary: What build_stack Does

1. **Initializes** empty stack
2. **Iterates** through all number strings
3. **Delegates** to append_node for each number
4. **Handles** errors by freeing partial stack
5. **Validates** no duplicate values exist
6. **Returns** completed stack or NULL on error

**Key insights:**
- Static helper function (file-scope only)
- Created to meet 42 Norm requirements
- Encapsulates complete stack construction
- Clean separation from parsing logic
- All cleanup handled internally

**Purpose in bigger picture:**
```
init_stack_a flow:
1. parse_arguments() -> get numbers array

2. build_stack()  <- You are here
   |
   +-- Initialize stack = NULL
   |
   +-- for each number:
   |   |   append_node() -> validate + create + add
   |   |
   |   +-- on failure: free_stack, return NULL
   |
   +-- has_duplicates() -> final validation
   |
   +-- return completed stack (or NULL)

3. Cleanup numbers array if needed

4. Return stack to caller
```

---

## Location in Project

**File:** `srcs/stack_init.c`
**Header:** NOT in header file (static function)
**Phase in TODO:** Phase 2.4 (Parsing & Validation - Stack Initialization Helper)

**Implementation location:**
```c
// File: srcs/stack_init.c

// Static helper 1
static t_stack *append_node(t_stack **stack, char *str)
{
    // ...
}

// Static helper 2 - internal to this file only
static t_stack *build_stack(char **numbers)
{
    // Implementation here
}

// NOT declared in push_swap.h
// Only visible within stack_init.c
```

---

## Related Functions

**Calls:**
- `append_node()` - Validates and adds each number
- `free_stack()` - Cleanup on error
- `has_duplicates()` - Duplicate detection

**Called by:**
- `init_stack_a()` - Main entry point

**Works with:**
- `append_node()` - Per-number processing
- `init_stack_a()` - Orchestration
- `parse_arguments()` - Provides input array

**Related concepts:**
- Static functions in C
- Builder pattern
- Error propagation
- 42 Norm compliance strategies

---

*Remember: This function is the workhorse of stack initialization. It handles the iteration and error management, while delegating the per-number work to append_node. Clean separation makes the code readable and maintainable.*
