# parse_arguments - Entry Point for Command Line Argument Parsing

## Function Signature

```c
char **parse_arguments(int argc, char **argv)
```

**Return type:** `char **` - NULL-terminated array of number strings (or NULL on error)
**Parameters:**
- `int argc` - Number of command line arguments
- `char **argv` - Array of command line argument strings

---

## Purpose & Use Case

`parse_arguments` is the **first line of defense** in your push_swap program. It's the entry point that handles all the different ways users might provide input to your program. This function is crucial because it normalizes different input formats into a consistent format that the rest of your program can work with.

### When You'll Use It

You'll call `parse_arguments` at the very beginning of your program to:
1. **Handle single string input** - `./push_swap "5 3 1 4 2"`
2. **Handle multiple arguments** - `./push_swap 5 3 1 4 2`
3. **Handle mixed format** - `./push_swap "5 3" 1 4 2` or `./push_swap 5 "3 1" 4 2`
4. **Detect format and process accordingly** - Split any arguments containing spaces
5. **Return normalized format** - Always return array of individual number strings

### Why This Matters

**Input format flexibility:**
```
Case 1: Multiple arguments (all single numbers)
$ ./push_swap 5 3 1 4 2
→ argc = 6
→ argv = ["./push_swap", "5", "3", "1", "4", "2"]
→ Each arg is a single number, collect them all

Case 2: Single string (all numbers in one string)
$ ./push_swap "5 3 1 4 2"
→ argc = 2
→ argv = ["./push_swap", "5 3 1 4 2"]
→ Need to split! Use ft_split on argv[1]

Case 3: Mixed format (some strings with spaces, some without)
$ ./push_swap "5 3" 1 4 "2"
→ argc = 5
→ argv = ["./push_swap", "5 3", "1", "4", "2"]
→ Split argv[1] into ["5", "3"], keep "1", "4", "2"
→ Result: ["5", "3", "1", "4", "2"]

Case 4: Empty or invalid
$ ./push_swap ""
→ Return NULL (error)
```

---

## Implementation Note: Two Approaches

There are two common ways to implement `parse_arguments`:

### Approach 1: Simple (Basic 42 Subject)
- Check `if (argc == 2)` → split the string
- Else → return `&argv[1]`
- **Pros:** Simple, fewer lines, less memory allocation
- **Cons:** Doesn't support mixed formats, inconsistent memory management

### Approach 2: Unified (This Documentation) ✅
- Process ALL arguments uniformly
- Split each argument, combine results
- **Pros:** Maximum flexibility, consistent memory management, supports mixed formats
- **Cons:** Always allocates memory, slightly more complex

**This documentation describes Approach 2** because:
1. More robust and user-friendly
2. Consistent memory management (always allocate, always free)
3. Handles edge cases like `./push_swap "2 4" 91 10`
4. Still 42 Norm compliant with helper functions

**If you prefer Approach 1:**
- It's also valid for 42
- Simpler implementation
- But won't handle mixed argument formats
- You'll need to track whether to free based on argc

---

## Deep Dive: How It Works

### The Core Algorithm

**New Unified Approach:** Instead of treating `argc == 2` differently, this function processes ALL arguments uniformly, checking each one for spaces and splitting if needed.

```
Universal Input Processing:
Any format:  ./push_swap "5 3" 1 "4 2" 6
   → argc = 5
   → argv = ["./push_swap", "5 3", "1", "4 2", "6"]

Process each argument:
   → argv[1] = "5 3" → contains space → split into ["5", "3"]
   → argv[2] = "1" → no space → keep as ["1"]
   → argv[3] = "4 2" → contains space → split into ["4", "2"]
   → argv[4] = "6" → no space → keep as ["6"]

Combine results:
   → Final array: ["5", "3", "1", "4", "2", "6", NULL]
   → Newly allocated memory (must free later)
```

### Why This Approach?

**Advantages:**
1. **Maximum flexibility** - Handles any combination of formats
2. **Consistent behavior** - No special cases for argc == 2
3. **User-friendly** - Users can mix formats without errors
4. **42-compatible** - Still meets all project requirements

**Trade-off:**
- Must allocate memory even for simple cases (but provides consistency)
- Slightly more complex implementation (but more robust)

### Step-by-Step Process

#### Step 1: Validate Argument Count

```c
if (argc < 2)
    return (NULL);  // No arguments provided
```

**Why this check?**
- `argc = 1` means only program name, no numbers
- Can't sort zero numbers
- Return NULL to signal error

#### Step 2: Count Total Numbers (Helper Function)

**First pass through arguments:**
- Iterate through each `argv[i]` from index 1 to argc-1
- For each argument, split it by spaces using `ft_split`
- Count how many strings result from the split
- Add to total count
- Free the temporary split result
- Return total count

**Why count first?**
- Need to know final array size to allocate memory
- Prevents multiple reallocations (inefficient)
- Allows single allocation for result array

**Example:**
```
Input: ./push_swap "5 3" 1 "4 2"
argv[1] = "5 3"  → split → ["5", "3"] → count = 2
argv[2] = "1"    → split → ["1"]       → count = 1
argv[3] = "4 2"  → split → ["4", "2"]  → count = 2
Total count = 5 numbers
```

#### Step 3: Allocate Result Array

**Memory allocation:**
- Allocate array of `char *` pointers
- Size: total_count + 1 (for NULL terminator)
- Must check if malloc succeeds
- Return NULL if allocation fails

**Why +1?**
- C string arrays are NULL-terminated
- Functions that use this array need to know where it ends
- NULL terminator marks the end

#### Step 4: Process Each Argument

**Second pass through arguments:**

For each `argv[i]` from index 1 to argc-1:

1. **Split the argument** by spaces using `ft_split`
   - Even single numbers get "split" (returns array with one element)
   - Strings with spaces get split into multiple elements

2. **Copy each split result** to final array
   - Don't copy the pointers (that would require freeing temp array differently)
   - Take ownership of the strings from ft_split
   - Add to result array sequentially

3. **Free the temporary array structure** (not the strings inside)
   - ft_split allocates array + strings
   - We take ownership of strings
   - Free only the array structure itself

**Example walkthrough:**
```
Input: ./push_swap "5 3" 1 "4 2"

Process argv[1] = "5 3":
  ft_split("5 3", ' ') → temp = ["5", "3", NULL]
  Copy temp[0] → result[0] = "5"
  Copy temp[1] → result[1] = "3"
  Free temp array structure (keep strings)

Process argv[2] = "1":
  ft_split("1", ' ') → temp = ["1", NULL]
  Copy temp[0] → result[2] = "1"
  Free temp array structure

Process argv[3] = "4 2":
  ft_split("4 2", ' ') → temp = ["4", "2", NULL]
  Copy temp[0] → result[3] = "4"
  Copy temp[1] → result[4] = "2"
  Free temp array structure

Final: result = ["5", "3", "1", "4", "2", NULL]
```

#### Step 5: NULL-Terminate and Return

**Final touches:**
- Set last element to NULL
- Return pointer to result array
- Caller is responsible for freeing this array with `free_split`

**Memory ownership:**
- This function allocates memory
- Caller MUST free it after use
- Use `free_split` to free both array and strings

---

## Visual Execution Trace

### Example 1: Simple Multiple Arguments

```
Command: ./push_swap 5 3 1

BEFORE parse_arguments:
argc = 4
argv = ["./push_swap", "5", "3", "1"]
        ↑ argv[0]      ↑ argv[1]

Step 1: Check argc
argc = 4, which is >= 2 ✓

Step 2: Count total numbers
argv[1] = "5" → split → ["5"] → count = 1
argv[2] = "3" → split → ["3"] → count = 1
argv[3] = "1" → split → ["1"] → count = 1
Total = 3 numbers

Step 3: Allocate result array
malloc(sizeof(char *) * 4)  // 3 numbers + NULL
result = [?, ?, ?, ?]

Step 4: Process each argument
Process argv[1] = "5":
  temp = ["5", NULL]
  result[0] = "5"
  free(temp)

Process argv[2] = "3":
  temp = ["3", NULL]
  result[1] = "3"
  free(temp)

Process argv[3] = "1":
  temp = ["1", NULL]
  result[2] = "1"
  free(temp)

Step 5: NULL-terminate
result[3] = NULL

AFTER parse_arguments:
Returned: ["5", "3", "1", NULL]
          ↑
          Newly allocated array (must free)
```

### Example 2: Single String

```
Command: ./push_swap "5 3 1"

BEFORE parse_arguments:
argc = 2
argv = ["./push_swap", "5 3 1"]
        ↑ argv[0]      ↑ argv[1]

Step 1: Check argc
argc = 2 ✓

Step 2: Count total numbers
argv[1] = "5 3 1" → split → ["5", "3", "1"] → count = 3
Total = 3 numbers

Step 3: Allocate result array
malloc(sizeof(char *) * 4)  // 3 numbers + NULL
result = [?, ?, ?, ?]

Step 4: Process argument
Process argv[1] = "5 3 1":
  temp = ft_split("5 3 1", ' ')
  temp = ["5", "3", "1", NULL]

  Copy to result:
  result[0] = temp[0] = "5"
  result[1] = temp[1] = "3"
  result[2] = temp[2] = "1"

  free(temp)  // Free array structure only

Step 5: NULL-terminate
result[3] = NULL

AFTER parse_arguments:
Returned: ["5", "3", "1", NULL]
          ↑
          Newly allocated memory

Note: Memory allocated! Must free with free_split later
```

### Example 3: Mixed Format (NEW!)

```
Command: ./push_swap "2 4 3" 91 10

BEFORE parse_arguments:
argc = 4
argv = ["./push_swap", "2 4 3", "91", "10"]
        ↑ argv[0]      ↑ argv[1] ↑argv[2] ↑argv[3]

Step 1: Check argc
argc = 4, which is >= 2 ✓

Step 2: Count total numbers (FIRST PASS)
i = 1: argv[1] = "2 4 3"
  temp = ft_split("2 4 3", ' ')
  temp = ["2", "4", "3", NULL]
  Count = 3
  free_split(temp)

i = 2: argv[2] = "91"
  temp = ft_split("91", ' ')
  temp = ["91", NULL]
  Count = 1
  free_split(temp)

i = 3: argv[3] = "10"
  temp = ft_split("10", ' ')
  temp = ["10", NULL]
  Count = 1
  free_split(temp)

Total = 3 + 1 + 1 = 5 numbers

Step 3: Allocate result array
malloc(sizeof(char *) * 6)  // 5 numbers + NULL
result = [?, ?, ?, ?, ?, ?]

Step 4: Process each argument (SECOND PASS)
result_index = 0

Process argv[1] = "2 4 3":
  temp = ft_split("2 4 3", ' ')
  temp = ["2", "4", "3", NULL]

  j = 0: result[0] = temp[0] = "2", result_index = 1
  j = 1: result[1] = temp[1] = "4", result_index = 2
  j = 2: result[2] = temp[2] = "3", result_index = 3

  free(temp)  // Free array structure, keep strings

Process argv[2] = "91":
  temp = ft_split("91", ' ')
  temp = ["91", NULL]

  j = 0: result[3] = temp[0] = "91", result_index = 4

  free(temp)

Process argv[3] = "10":
  temp = ft_split("10", ' ')
  temp = ["10", NULL]

  j = 0: result[4] = temp[0] = "10", result_index = 5

  free(temp)

Step 5: NULL-terminate
result[5] = NULL

AFTER parse_arguments:
Returned: ["2", "4", "3", "91", "10", NULL]
          ↑
          Newly allocated array containing all numbers

Memory state:
result[0] → "2" (from argv[1] split)
result[1] → "4" (from argv[1] split)
result[2] → "3" (from argv[1] split)
result[3] → "91" (from argv[2] split)
result[4] → "10" (from argv[3] split)
result[5] → NULL

Note: ALWAYS allocated memory, regardless of format!
      Caller MUST free with free_split!
```

### Example 4: Empty String

```
Command: ./push_swap ""

BEFORE parse_arguments:
argc = 2
argv = ["./push_swap", ""]
        ↑ argv[0]      ↑ argv[1] (empty)

Step 1: Check argc
argc = 2 ✓

Step 2: Detect format
argc == 2, single string format

Step 3: Check for empty string
argv[1][0] = '\0' (empty string) ✗

Step 4: Return NULL
result = NULL (error)

AFTER parse_arguments:
Returned: NULL (signals error to caller)
```

### Example 5: No Arguments

```
Command: ./push_swap

BEFORE parse_arguments:
argc = 1
argv = ["./push_swap"]
        ↑ argv[0] only

Step 1: Check argc
argc = 1, which is < 2 ✗

Step 2: Return NULL immediately
result = NULL (error)

AFTER parse_arguments:
Returned: NULL (signals error to caller)
```

---

## Complete Algorithm Pseudocode

### High-Level Overview

```
FUNCTION parse_arguments(argc, argv):
    // Step 1: Validate we have arguments
    IF argc < 2:
        RETURN NULL  // No numbers provided

    // Step 2: Count total numbers across all arguments
    total = count_total_numbers(argc, argv)
    IF total <= 0:
        RETURN NULL  // No valid numbers found

    // Step 3: Allocate result array
    result = allocate_array(total + 1)  // +1 for NULL terminator
    IF result == NULL:
        RETURN NULL  // Allocation failed

    // Step 4: Process each argument and combine
    result = join_all_arguments(argc, argv, total)
    IF result == NULL:
        RETURN NULL  // Processing failed

    // Step 5: Return combined result
    RETURN result
END FUNCTION
```

### Detailed Implementation with Helper Functions

```
HELPER FUNCTION count_total_numbers(argc, argv):
    i = 1
    count = 0

    // Iterate through all arguments
    WHILE i < argc:
        // Split current argument by spaces
        temp = ft_split(argv[i], ' ')

        IF temp == NULL:
            RETURN -1  // Error

        // Count elements in split result
        j = 0
        WHILE temp[j] != NULL:
            count = count + 1
            j = j + 1

        // Free temporary split result
        free_split(temp)
        i = i + 1

    RETURN count
END HELPER FUNCTION

HELPER FUNCTION join_all_arguments(argc, argv, total):
    // Allocate result array
    result = malloc(sizeof(char *) * (total + 1))
    IF result == NULL:
        RETURN NULL

    i = 1           // Start at first argument after program name
    result_index = 0  // Track position in result array

    // Process each argument
    WHILE i < argc:
        // Split current argument by spaces
        temp = ft_split(argv[i], ' ')

        IF temp == NULL:
            free_split(result)  // Clean up on error
            RETURN NULL

        // Copy all strings from temp to result
        j = 0
        WHILE temp[j] != NULL:
            result[result_index] = temp[j]  // Transfer ownership
            result_index = result_index + 1
            j = j + 1

        // Free only the array structure, not the strings
        // (we transferred ownership to result)
        free(temp)

        i = i + 1

    // NULL-terminate the result array
    result[result_index] = NULL

    RETURN result
END HELPER FUNCTION

MAIN FUNCTION parse_arguments(argc, argv):
    // Step 1: Validate argument count
    IF argc < 2:
        RETURN NULL

    // Step 2: Count total numbers
    total = count_total_numbers(argc, argv)
    IF total <= 0:
        RETURN NULL

    // Step 3: Join all arguments into single array
    result = join_all_arguments(argc, argv, total)

    RETURN result
END FUNCTION
```

### Compact 42-Norm Compliant Version

```
FUNCTION parse_arguments(argc, argv):
    total = 0

    // Validate arguments exist
    IF argc < 2:
        RETURN NULL

    // Count and validate
    total = count_total_numbers(argc, argv)
    IF total <= 0:
        RETURN NULL

    // Build and return result
    RETURN join_all_arguments(argc, argv, total)
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: No Arguments

```c
// Command: ./push_swap
int argc = 1;
char **result = parse_arguments(argc, argv);
// result = NULL
```

**Handling:** Return NULL immediately. Main should detect and exit cleanly.

### Edge Case 2: Empty String

```c
// Command: ./push_swap ""
int argc = 2;
char **argv = {"./push_swap", ""};
char **result = parse_arguments(argc, argv);
// result = NULL
```

**Handling:** Detect empty string and return NULL.

### Edge Case 3: Only Whitespace

```c
// Command: ./push_swap "   "
int argc = 2;
char **argv = {"./push_swap", "   "};
char **result = parse_arguments(argc, argv);
// ft_split returns empty array or array with NULL
// Must handle appropriately
```

**Handling:** ft_split on spaces returns NULL or empty array. Check result.

### Edge Case 4: Mixed Format (SUPPORTED in this implementation)

```c
// Command: ./push_swap "5 3" 1 4 2
// argc = 5
// argv = ["./push_swap", "5 3", "1", "4", "2"]
// This is now supported!
```

**Handling:** Parse each argument individually, splitting any that contain spaces.

### Edge Case 5: Single Number (Valid)

```c
// Command: ./push_swap 42
int argc = 2;
char **argv = {"./push_swap", "42"};
char **result = parse_arguments(argc, argv);
// result = ft_split("42", ' ') = ["42", NULL]
```

**Handling:** Valid input. Single number is already sorted but legal.

### Edge Case 6: Malloc Failure in ft_split

```c
// ft_split allocates memory
// If allocation fails, ft_split returns NULL
char **result = parse_arguments(argc, argv);
if (!result)
{
    // Handle error - could be input error or malloc failure
    print_error();
    exit(1);
}
```

**Handling:** ft_split returns NULL on failure. Propagate error to caller.

### Edge Case 7: Extra Spaces

```c
// Command: ./push_swap "5   3    1"
// Multiple spaces between numbers
char **result = parse_arguments(2, argv);
// ft_split handles multiple delimiters correctly
// result = ["5", "3", "1", NULL]
```

**Handling:** ft_split automatically handles multiple consecutive spaces.

---

## Time & Space Complexity

### Time Complexity

**Case 1: Multiple arguments (argc > 2)**
```
Operations:
- Check argc: O(1)
- Return pointer: O(1)
Total: O(1) - constant time
```

**Case 2: Single string (argc == 2)**
```
Operations:
- Check argc: O(1)
- Check empty: O(1)
- ft_split: O(n) where n = length of string
  - Must scan entire string
  - Count spaces
  - Allocate memory
  - Copy substrings
Total: O(n) - linear in input string length
```

**Overall: O(n) where n is total input size**

### Space Complexity

**Case 1: Multiple arguments**
```
Memory used:
- No allocation (using existing argv)
- Return pointer only: O(1)
Total: O(1) - constant space
```

**Case 2: Single string**
```
Memory allocated:
- Array of pointers: O(m) where m = number of numbers
- String copies: O(n) where n = total string length
- Each number string is copied
Total: O(n + m) = O(n) - linear in input size
```

**Overall: O(n) in worst case (single string input)**

---

## Relationship with Other Functions

### Functions Called By parse_arguments

1. **ft_split()**
   - Splits string on delimiter
   - Allocates memory for array and strings
   - Returns NULL-terminated array

### Functions That Use parse_arguments

1. **init_stack_a()**
   - Calls parse_arguments first
   - Then validates and converts numbers
   - Builds the stack

2. **main()**
   - Might call parse_arguments directly
   - Or call init_stack_a which calls it

### Related Validation Functions

- **is_valid_number()** - Called later to validate each string
- **ft_atol()** - Called later to convert strings to numbers
- **has_duplicates()** - Called after stack creation

---

## Integration with Push_swap

### Usage in main()

```c
int main(int argc, char **argv)
{
    char    **numbers;
    t_stack *stack_a;
    t_stack *stack_b;

    // Step 1: Parse arguments
    numbers = parse_arguments(argc, argv);
    if (!numbers)
    {
        // No arguments or invalid format
        return (0);  // Or print_error() based on project requirements
    }

    // Step 2: Initialize stack from parsed numbers
    stack_a = init_stack_a(numbers);
    if (!stack_a)
    {
        // Validation failed
        free_split(numbers);  // ALWAYS free - always allocated
        print_error();
        return (1);
    }

    // Step 3: Check if already sorted
    if (is_sorted(stack_a))
    {
        free_stack(&stack_a);
        free_split(numbers);  // ALWAYS free - always allocated
        return (0);
    }

    // Step 4: Sort the stack
    stack_b = NULL;
    choose_sort(&stack_a, &stack_b);

    // Step 5: Clean up
    free_stack(&stack_a);
    free_split(numbers);  // ALWAYS free - always allocated
    return (0);
}
```

**Important change:** No need to check `if (argc == 2)` before freeing!
- Numbers is ALWAYS allocated regardless of format
- ALWAYS call `free_split(numbers)` after use
- Simpler, more consistent memory management

### Usage in init_stack_a()

```c
t_stack *init_stack_a(char **numbers)
{
    t_stack *stack_a;
    int     i;

    // No need to call parse_arguments - already done by caller
    // numbers array is guaranteed to be valid or NULL

    if (!numbers)
        return (NULL);

    // Build stack from number strings
    stack_a = NULL;
    i = 0;
    while (numbers[i])
    {
        // Validate and convert each number
        if (!is_valid_number(numbers[i]))
        {
            free_stack(&stack_a);
            return (NULL);
        }

        long value = ft_atol(numbers[i]);
        if (!is_int_range(value))
        {
            free_stack(&stack_a);
            return (NULL);
        }

        // Create and add node
        t_stack *node = stack_new((int)value);
        if (!node)
        {
            free_stack(&stack_a);
            return (NULL);
        }
        stack_add_back(&stack_a, node);
        i++;
    }

    // Check for duplicates
    if (has_duplicates(stack_a))
    {
        free_stack(&stack_a);
        return (NULL);
    }

    // Don't free numbers here - caller's responsibility
    return (stack_a);
}
```

**Important changes:**
- `init_stack_a` now takes `char **numbers` directly, not `argc, argv`
- Caller (main) handles parse_arguments and freeing
- No need to check `if (argc == 2)` - always allocated
- Cleaner separation of concerns
- init_stack_a focuses only on validation and stack building

---

## 42 Norm Considerations

### Norm Compliance Checklist

✅ **Function structure:** Main function + 2 static helper functions
✅ **Function length:** Each under 25-line limit
✅ **Single responsibility:** Each function does ONE thing
✅ **No global variables:** Everything is passed as parameters
✅ **Helper functions:** Static (file-scope only)
✅ **Proper return values:** NULL on error, valid pointer on success
✅ **No forbidden functions:** Only uses ft_split, malloc, free
✅ **Memory management:** All allocations properly freed on error

### Why Helper Functions?

**Problem:** Supporting mixed formats requires:
- Counting total numbers (first pass)
- Building result array (second pass)
- Main function would exceed 25 lines

**Solution:** Split into 3 functions:
1. `count_total_numbers` (static) - First pass
2. `join_all_arguments` (static) - Second pass
3. `parse_arguments` (main) - Orchestrates

**42 Norm compliance:**
- Each function under 25 lines ✓
- Static functions not visible outside file ✓
- Clear separation of concerns ✓
- Maximum 4 parameters per function ✓

### Function Breakdown

**Function 1: count_total_numbers (static)**
```c
Purpose: Count total numbers across all arguments
Lines: ~20 lines
Logic:
  - Iterate through argv
  - Split each argument
  - Count elements in split
  - Free temporary split
  - Return total count
Complexity: O(n*m) where n=argc, m=avg string length
```

**Function 2: join_all_arguments (static)**
```c
Purpose: Combine all split arguments into one array
Lines: ~23 lines
Logic:
  - Allocate result array
  - Iterate through argv
  - Split each argument
  - Transfer strings to result
  - Free temp array structure
  - NULL-terminate result
Complexity: O(n*m) where n=argc, m=avg string length
```

**Function 3: parse_arguments (main)**
```c
Purpose: Entry point, validates and orchestrates
Lines: ~10 lines
Logic:
  - Validate argc
  - Call count_total_numbers
  - Validate count
  - Call join_all_arguments
  - Return result
Complexity: O(n*m) - dominated by helper functions
```

### Memory Management Rules

**Critical 42 Norm requirement:** No memory leaks!

**Allocation points:**
1. `ft_split` - allocates array + strings
2. `malloc` for result array
3. String ownership transfer

**Free points:**
1. Free temp split arrays (keep strings)
2. On error, free partial result
3. Caller must free final result with `free_split`

**Error handling:**
- Every malloc checked for NULL
- Partial allocations freed before error return
- Consistent error return (NULL)

---

## Common Mistakes to Avoid

### Mistake 1: Double-Freeing Strings

```c
❌ WRONG:
temp = ft_split(argv[i], ' ');
// Copy strings to result
j = 0;
while (temp[j])
{
    result[k++] = temp[j];  // Transfer ownership
    j++;
}
free_split(temp);  // WRONG! This frees the strings too!

Problem: Strings now freed, but result array still points to them
Solution: Only free the array structure with free(temp), not free_split
```

### Mistake 2: Not Freeing Temp Arrays

```c
❌ WRONG:
while (i < argc)
{
    temp = ft_split(argv[i], ' ');
    // ... process temp ...
    // Missing: free(temp)
    i++;
}

Problem: Memory leak - temp array structure not freed
Solution: free(temp) after transferring strings
```

### Mistake 3: Allocating Wrong Size

```c
❌ WRONG:
result = malloc(sizeof(char *) * total);  // No space for NULL!

Problem: No space for NULL terminator
Solution: malloc(sizeof(char *) * (total + 1))
```

### Mistake 4: Not Checking ft_split Return

```c
❌ WRONG:
temp = ft_split(argv[i], ' ');
j = 0;
while (temp[j])  // Crash if temp is NULL!
    result[k++] = temp[j++];

Problem: If ft_split returns NULL, accessing temp[j] crashes
Solution: Check if temp is NULL before using
```

### Mistake 5: Forgetting to Free on Error

```c
❌ WRONG:
result = malloc(sizeof(char *) * (total + 1));
// ... some code ...
if (error_condition)
    return (NULL);  // Memory leak! result not freed

Problem: Allocated memory leaked on error path
Solution: Free result before returning NULL on error
```

### Mistake 6: Not Supporting Mixed Formats

```c
❌ WRONG (OLD APPROACH):
if (argc == 2)
    return (ft_split(argv[1], ' '));
else
    return (&argv[1]);  // Assumes all are single numbers!

Problem: Doesn't handle ./push_swap "2 4" 3 91
Solution: Process ALL arguments, splitting each as needed
```

### Mistake 7: Inconsistent Memory Management

```c
❌ WRONG (OLD APPROACH):
if (argc == 2)
    return (ft_split(...));  // Allocated
else
    return (&argv[1]);  // Not allocated

Problem: Caller doesn't know whether to free
Solution: ALWAYS allocate - consistent memory management
```

---

## Testing Strategy

### Test Case 1: No Arguments

```bash
$ ./push_swap
# parse_arguments(1, argv) should return NULL
# Program should exit cleanly (no error message per subject)
```

### Test Case 2: Empty String

```bash
$ ./push_swap ""
# parse_arguments(2, argv) should return NULL
# Program should print "Error" and exit
```

### Test Case 3: Single Number String

```bash
$ ./push_swap "42"
# parse_arguments returns ["42", NULL]
# Allocated memory, must free later
```

### Test Case 4: Multiple Numbers String

```bash
$ ./push_swap "5 3 1 4 2"
# parse_arguments returns ["5", "3", "1", "4", "2", NULL]
# Allocated memory, must free later
```

### Test Case 5: Multiple Arguments (All Single Numbers)

```bash
$ ./push_swap 5 3 1 4 2
# parse_arguments returns ["5", "3", "1", "4", "2", NULL]
# Allocated memory, must free later
```

### Test Case 6: Mixed Format (NEW!)

```bash
$ ./push_swap "2 4 3" 91 10
# parse_arguments returns ["2", "4", "3", "91", "10", NULL]
# Allocated memory, must free later

$ ./push_swap 2 4 "3 91" 10
# parse_arguments returns ["2", "4", "3", "91", "10", NULL]
# Allocated memory, must free later

$ ./push_swap "1 2" "3 4" "5"
# parse_arguments returns ["1", "2", "3", "4", "5", NULL]
# Allocated memory, must free later
```

### Test Case 7: Extra Spaces

```bash
$ ./push_swap "5   3    1"
# ft_split handles multiple spaces correctly
# Returns ["5", "3", "1", NULL]
```

### Test Case 8: Leading/Trailing Spaces

```bash
$ ./push_swap "  5 3 1  "
# ft_split should handle leading/trailing spaces
# Returns ["5", "3", "1", NULL]
```

### Test Case 9: Tabs (if supported)

```bash
$ ./push_swap "5	3  1"
# Note: Standard ft_split only splits on space delimiter
# Tabs won't be split unless you modify delimiter handling
```

### Test Case 10: Memory Leak Check

```c
void test_memory_leaks(void)
{
    char *argv1[] = {"./push_swap", "5 3 1"};
    char **result1 = parse_arguments(2, argv1);
    free_split(result1);  // Must ALWAYS free

    char *argv2[] = {"./push_swap", "2 4", "91", "10"};
    char **result2 = parse_arguments(4, argv2);
    free_split(result2);  // Must ALWAYS free

    // Run with valgrind: should show no leaks
    // valgrind --leak-check=full ./push_swap "5 3" 1
}
```

### Test Case 11: All Formats Together

```bash
# Test comprehensive mixed format
$ ./push_swap "1 2" 3 "4 5 6" 7 "8"
# Should return: ["1", "2", "3", "4", "5", "6", "7", "8", NULL]
```

---

## Summary: What parse_arguments Does

1. **Validates** that arguments were provided (argc >= 2)
2. **Processes** ALL arguments uniformly (no special cases)
3. **Splits** each argument by spaces using ft_split
4. **Combines** all split results into single array
5. **Normalizes** input into consistent format (array of number strings)
6. **Allocates** memory for result (ALWAYS - consistent behavior)
7. **Returns** NULL on error, valid array on success

**Key insight:** This function is the bridge between how users invoke your program and how your program processes data. It handles ALL input format variations (single string, multiple args, mixed) so the rest of your code can work with a consistent format.

**Critical difference from basic implementation:**
- **OLD:** Different code paths for argc==2 vs argc>2
- **NEW:** Unified approach - process all arguments the same way
- **Benefit:** Maximum flexibility, supports mixed formats
- **Trade-off:** Always allocates memory (but simplifies caller logic)

---

## Location in Project

**File:** `srcs/parser.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 2.1 (Parsing & Validation - Entry Point)

**Function prototypes in header:**
```c
// Main function (public - in header)
char **parse_arguments(int argc, char **argv);

// Helper functions (static - only in .c file, not in header)
static int count_total_numbers(int argc, char **argv);
static char **join_all_arguments(int argc, char **argv, int total);
```

**Implementation structure:**
```c
// File: srcs/parser.c

// Helper 1: Count numbers (static - not in header)
static int count_total_numbers(int argc, char **argv)
{
    // ... implementation (see pseudocode above)
}

// Helper 2: Join arguments (static - not in header)
static char **join_all_arguments(int argc, char **argv, int total)
{
    // ... implementation (see pseudocode above)
}

// Main function (public - declared in header)
char **parse_arguments(int argc, char **argv)
{
    int total;

    if (argc < 2)
        return (NULL);
    total = count_total_numbers(argc, argv);
    if (total <= 0)
        return (NULL);
    return (join_all_arguments(argc, argv, total));
}
```

**Note:** Only `parse_arguments` goes in the header file. The two helper functions are `static` and remain internal to `parser.c`.

---

## Related Functions

**Called by parse_arguments:**
- `ft_split()` - Splits string on delimiter

**Calls parse_arguments:**
- `init_stack_a()` - Uses parsed arguments to build stack
- `main()` - Entry point may call directly

**Related functions:**
- `free_split()` - Frees memory allocated by ft_split
- `is_valid_number()` - Validates each parsed string
- `ft_atol()` - Converts validated strings to numbers

---

*Remember: Good parsing makes everything else easier. Handle all input formats gracefully at the entry point, and the rest of your program can focus on solving the actual problem!*
