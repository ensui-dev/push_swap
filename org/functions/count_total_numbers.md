# count_total_numbers - Count Total Numbers Across All Arguments (Static Helper)

## Function Signature

```c
static int count_total_numbers(int argc, char **argv)
```

**IMPORTANT:** This is a **STATIC helper function** - not declared in header file!

**Return type:** `int` - Total count of numbers found, or -1 on error
**Parameters:**
- `int argc` - Number of command line arguments
- `char **argv` - Array of command line argument strings

**Visibility:** File-scope only (static) - internal to `parser.c`

---

## Purpose & Use Case

`count_total_numbers` is a **static helper function** that performs the **first pass** through command line arguments to determine how many individual numbers exist across all arguments. This count is essential for allocating the correct array size in `parse_arguments`.

### When You'll Use It

This function is called internally by `parse_arguments` to:
1. **Determine array size** - Count total numbers before allocation
2. **First pass analysis** - Scan all arguments without building result
3. **Memory efficiency** - Allocate exactly the right amount of memory
4. **Avoid reallocation** - Single allocation instead of growing array

### Why This Matters

**The Two-Pass Strategy:**
```
Without counting first (inefficient):
- Allocate small array
- Process arguments
- Reallocate when array full
- Copy old data to new array
- Repeat as needed
→ Multiple allocations, copies, performance hit

With counting first (efficient):
- Count all numbers (first pass)
- Allocate exact size needed
- Process arguments (second pass)
- Fill array directly
→ Single allocation, no copying, optimal
```

**Example scenarios:**
```
Input: ./push_swap "5 3" 1 "4 2"

First pass (count_total_numbers):
argv[1] = "5 3"  → split → ["5", "3"] → count = 2
argv[2] = "1"    → split → ["1"]       → count = 1
argv[3] = "4 2"  → split → ["4", "2"]  → count = 2
Total = 5 numbers

Now we know: allocate array of size 6 (5 + NULL terminator)

Second pass (join_all_arguments):
Fill the pre-allocated array with actual strings
```

---

## Deep Dive: How It Works

### The Core Algorithm

**Purpose in Two-Pass Strategy:**
```
count_total_numbers() = Pass 1: Measurement
    ↓
    Determine exact size needed
    ↓
    Allocate result array
    ↓
join_all_arguments() = Pass 2: Population
```

### Why Static?

**Static function benefits:**
1. **Encapsulation** - Implementation detail hidden from users
2. **No header pollution** - Doesn't appear in push_swap.h
3. **File-scope only** - Can't be called from other files
4. **42 Norm compliance** - Breaks down complex function into helpers
5. **Clear intent** - Internal helper, not public API

### Step-by-Step Process

#### Step 1: Initialize Counter

```c
int i = 1;      // Start at first argument (skip program name)
int count = 0;  // Total number counter
```

**Why start at i = 1?**
- `argv[0]` is program name ("./push_swap")
- Actual arguments start at `argv[1]`
- We only count user-provided numbers

#### Step 2: Iterate Through Each Argument

```c
while (i < argc)
{
    // Process argv[i]
    i++;
}
```

**Loop structure:**
```
argc = 4
argv = ["./push_swap", "5 3", "1", "4 2"]
        ↑ skip this    ↑ i=1  ↑ i=2 ↑ i=3

Loop iterations:
i = 1: Process "5 3"
i = 2: Process "1"
i = 3: Process "4 2"
i = 4: Exit loop (i >= argc)
```

#### Step 3: Split Each Argument

```c
temp = ft_split(argv[i], ' ');
if (!temp)
    return (-1);  // Allocation failure
```

**Why split every argument?**
- Each argument might contain multiple numbers
- "5 3" needs to be split into ["5", "3"]
- Even "1" gets split into ["1"] (single element array)
- Uniform processing for all formats

**Example splits:**
```
"5 3"     → ft_split → ["5", "3", NULL]
"1"       → ft_split → ["1", NULL]
"4 2 6"   → ft_split → ["4", "2", "6", NULL]
"42"      → ft_split → ["42", NULL]
```

#### Step 4: Count Elements in Split Result

```c
int j = 0;
while (temp[j])
{
    count++;
    j++;
}
```

**Counting mechanism:**
```
temp = ["5", "3", NULL]

j = 0: temp[0] = "5"  → count = 1, j = 1
j = 1: temp[1] = "3"  → count = 2, j = 2
j = 2: temp[2] = NULL → exit loop

Elements counted: 2
```

**NULL-terminated array property:**
- ft_split returns NULL-terminated array
- Loop until we hit NULL pointer
- Number of iterations = number of strings

#### Step 5: Free Temporary Split

```c
free_split(temp);
```

**Critical memory management:**
- ft_split allocates memory for array + strings
- We only needed to count, not keep the data
- Must free both array and strings
- Use `free_split()` which frees everything
- Prevents memory leaks in first pass

**Why free immediately?**
```
Without freeing:
Process argv[1] → temp1 allocated (leaked)
Process argv[2] → temp2 allocated (leaked)
Process argv[3] → temp3 allocated (leaked)
→ Memory leaks accumulate!

With freeing:
Process argv[1] → temp1 allocated → count → free
Process argv[2] → temp2 allocated → count → free
Process argv[3] → temp3 allocated → count → free
→ No leaks, clean first pass
```

#### Step 6: Return Total Count

```c
return (count);
```

**Return value meanings:**
- Positive number: Total count of numbers found
- 0: No numbers found (valid but unusual)
- -1: Error occurred (malloc failure in ft_split)

---

## Visual Execution Trace

### Example 1: Mixed Format Arguments

```
Command: ./push_swap "2 4 3" 91 10

BEFORE count_total_numbers:
argc = 4
argv = ["./push_swap", "2 4 3", "91", "10"]
        ↑ argv[0]      ↑ argv[1] ↑argv[2] ↑argv[3]

Initialize:
i = 1
count = 0

--- Iteration 1: i = 1 ---
Current argument: argv[1] = "2 4 3"

Split:
temp = ft_split("2 4 3", ' ')
temp = ["2", "4", "3", NULL]
       ↑     ↑    ↑    ↑
      [0]   [1]  [2]  [3]

Count elements:
j = 0: temp[0] = "2"  → count = 1
j = 1: temp[1] = "4"  → count = 2
j = 2: temp[2] = "3"  → count = 3
j = 3: temp[3] = NULL → exit inner loop

Free:
free_split(temp)  // Free ["2", "4", "3", NULL]

Update:
i = 2

--- Iteration 2: i = 2 ---
Current argument: argv[2] = "91"

Split:
temp = ft_split("91", ' ')
temp = ["91", NULL]
       ↑     ↑
      [0]   [1]

Count elements:
j = 0: temp[0] = "91" → count = 4
j = 1: temp[1] = NULL → exit inner loop

Free:
free_split(temp)  // Free ["91", NULL]

Update:
i = 3

--- Iteration 3: i = 3 ---
Current argument: argv[3] = "10"

Split:
temp = ft_split("10", ' ')
temp = ["10", NULL]
       ↑     ↑
      [0]   [1]

Count elements:
j = 0: temp[0] = "10" → count = 5
j = 1: temp[1] = NULL → exit inner loop

Free:
free_split(temp)  // Free ["10", NULL]

Update:
i = 4

--- Loop Exit: i = 4 (i >= argc) ---

AFTER count_total_numbers:
Return: count = 5

Result: Found 5 total numbers across 3 arguments
```

### Example 2: Single String with Multiple Numbers

```
Command: ./push_swap "5 3 1 4 2"

BEFORE count_total_numbers:
argc = 2
argv = ["./push_swap", "5 3 1 4 2"]
        ↑ argv[0]      ↑ argv[1]

Initialize:
i = 1
count = 0

--- Iteration 1: i = 1 ---
Current argument: argv[1] = "5 3 1 4 2"

Split:
temp = ft_split("5 3 1 4 2", ' ')
temp = ["5", "3", "1", "4", "2", NULL]

Count elements:
j = 0: temp[0] = "5" → count = 1
j = 1: temp[1] = "3" → count = 2
j = 2: temp[2] = "1" → count = 3
j = 3: temp[3] = "4" → count = 4
j = 4: temp[4] = "2" → count = 5
j = 5: temp[5] = NULL → exit loop

Free:
free_split(temp)

Update:
i = 2

--- Loop Exit: i = 2 (i >= argc) ---

AFTER count_total_numbers:
Return: count = 5
```

### Example 3: All Single Arguments

```
Command: ./push_swap 5 3 1

BEFORE count_total_numbers:
argc = 4
argv = ["./push_swap", "5", "3", "1"]

Initialize:
i = 1
count = 0

--- Iteration 1: i = 1 ---
argv[1] = "5"
temp = ft_split("5", ' ') = ["5", NULL]
Count: 1 element → count = 1
free_split(temp)
i = 2

--- Iteration 2: i = 2 ---
argv[2] = "3"
temp = ft_split("3", ' ') = ["3", NULL]
Count: 1 element → count = 2
free_split(temp)
i = 3

--- Iteration 3: i = 3 ---
argv[3] = "1"
temp = ft_split("1", ' ') = ["1", NULL]
Count: 1 element → count = 3
free_split(temp)
i = 4

--- Loop Exit ---

AFTER count_total_numbers:
Return: count = 3
```

### Example 4: Error Case - ft_split Failure

```
Command: ./push_swap "5 3 1"
Scenario: malloc fails inside ft_split

--- Iteration 1: i = 1 ---
argv[1] = "5 3 1"
temp = ft_split("5 3 1", ' ')
→ malloc fails inside ft_split
→ ft_split returns NULL

Check:
if (!temp)
    return (-1);  ✓ Error detected

AFTER count_total_numbers:
Return: -1 (error)

Caller (parse_arguments) will detect -1 and return NULL
```

---

## Complete Algorithm Pseudocode

### High-Level Overview

```
FUNCTION count_total_numbers(argc, argv):
    // Initialize counters
    i = 1       // Start at first real argument
    count = 0   // Total numbers found

    // Process each argument
    WHILE i < argc:
        // Split current argument by spaces
        temp = ft_split(argv[i], ' ')

        // Check for allocation failure
        IF temp is NULL:
            RETURN -1

        // Count elements in split result
        j = 0
        WHILE temp[j] is not NULL:
            count = count + 1
            j = j + 1

        // Free temporary split (we only needed count)
        free_split(temp)

        // Move to next argument
        i = i + 1

    // Return total count
    RETURN count
END FUNCTION
```

### Detailed Implementation

```
FUNCTION count_total_numbers(argc, argv):
    DECLARE i AS integer
    DECLARE count AS integer
    DECLARE temp AS pointer to string array
    DECLARE j AS integer

    // Step 1: Initialize loop variables
    i = 1           // Skip program name (argv[0])
    count = 0       // Start with zero numbers

    // Step 2: Iterate through all command line arguments
    WHILE i < argc:
        // Step 3: Split current argument on space delimiter
        temp = ft_split(argv[i], ' ')

        // Step 4: Handle ft_split failure
        IF temp equals NULL:
            // Malloc failed inside ft_split
            RETURN -1

        // Step 5: Count number of strings in temp array
        j = 0
        WHILE temp[j] is not NULL:
            // Each non-NULL element is one number string
            count = count + 1
            j = j + 1
        // END WHILE (inner counting loop)

        // Step 6: Free temporary split result
        // We only needed the count, not the actual strings
        free_split(temp)

        // Step 7: Advance to next argument
        i = i + 1
    // END WHILE (outer argument loop)

    // Step 8: Return total count of numbers found
    RETURN count
END FUNCTION
```

### Compact Version

```
FUNCTION count_total_numbers(argc, argv):
    i = 1
    count = 0

    WHILE i < argc:
        temp = ft_split(argv[i], ' ')
        IF NOT temp:
            RETURN -1

        j = 0
        WHILE temp[j]:
            count++
            j++

        free_split(temp)
        i++

    RETURN count
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: Single Argument with One Number

```c
// Command: ./push_swap "42"
int argc = 2;
char **argv = {"./push_swap", "42"};
int result = count_total_numbers(argc, argv);
// result = 1
```

**Handling:** ft_split returns ["42", NULL], count = 1

### Edge Case 2: Empty String

```c
// Command: ./push_swap ""
int argc = 2;
char **argv = {"./push_swap", ""};
int result = count_total_numbers(argc, argv);
// ft_split("", ' ') behavior depends on implementation
// Usually returns NULL or empty array
// result = 0 or -1
```

**Handling:** Depends on ft_split implementation. Check in parse_arguments.

### Edge Case 3: Multiple Spaces Between Numbers

```c
// Command: ./push_swap "5   3    1"
int argc = 2;
char **argv = {"./push_swap", "5   3    1"};
int result = count_total_numbers(argc, argv);
// ft_split handles consecutive delimiters correctly
// result = 3
```

**Handling:** ft_split automatically handles multiple consecutive spaces.

### Edge Case 4: Only Whitespace

```c
// Command: ./push_swap "   "
int argc = 2;
char **argv = {"./push_swap", "   "};
int result = count_total_numbers(argc, argv);
// ft_split returns empty array or NULL
// result = 0 or -1
```

**Handling:** Should be caught and handled in parse_arguments.

### Edge Case 5: ft_split Allocation Failure

```c
// Malloc fails inside ft_split
int result = count_total_numbers(argc, argv);
// ft_split returns NULL
// result = -1 (error code)
```

**Handling:** Return -1 immediately. Caller checks for negative return.

### Edge Case 6: Very Large Number of Arguments

```c
// Command: ./push_swap 1 2 3 4 5 ... 1000
int argc = 1001;
int result = count_total_numbers(argc, argv);
// result = 1000
// Each argument contributes 1 to count
```

**Handling:** Works correctly, count accumulates properly.

### Edge Case 7: Mixed Empty and Valid Arguments

```c
// Command: ./push_swap "5 3" "" "1"
// Note: Shell typically filters out empty args
// But if it didn't...
int result = count_total_numbers(3, argv);
// argv[1] = "5 3" → count += 2
// argv[2] = ""    → count += 0
// argv[3] = "1"   → count += 1
// result = 3
```

---

## Time & Space Complexity

### Time Complexity: O(n × m)

```
n = argc - 1 (number of arguments to process)
m = average length of each argument string

Operations:
- Outer loop: O(n) iterations (once per argument)
- For each iteration:
  - ft_split: O(m) - scan string, count spaces, allocate, copy
  - Count loop: O(k) where k = numbers in this argument
  - free_split: O(k) - free each string + array
- Total per iteration: O(m + k)

Overall: O(n × (m + k))
Since k ≤ m (can't have more numbers than chars):
Total: O(n × m)
```

**Example analysis:**
```
Input: ./push_swap "2 4 3" 91 10
n = 3 arguments
m = average length ≈ 5 characters

Argument 1: "2 4 3" (5 chars)
- ft_split: O(5)
- Count: 3 elements, O(3)
- free_split: O(3)
- Total: O(5)

Argument 2: "91" (2 chars)
- ft_split: O(2)
- Count: 1 element, O(1)
- free_split: O(1)
- Total: O(2)

Argument 3: "10" (2 chars)
- ft_split: O(2)
- Count: 1 element, O(1)
- free_split: O(1)
- Total: O(2)

Total time: O(5 + 2 + 2) = O(9) = O(n × m)
```

### Space Complexity: O(k)

```
k = maximum number of numbers in any single argument

Memory used:
- i, count, j: O(1) local variables
- temp: O(k) - temporary array from ft_split
  - Array of k+1 pointers: O(k)
  - k strings with total m chars: O(m)
  - Total: O(k + m)
- Freed after each iteration
- Peak memory: Size of largest temp array

Total: O(k) where k = max numbers in one argument
```

**Why not O(total_count)?**
```
We don't keep all splits simultaneously!

Process argv[1] → temp1 allocated → count → FREE
Process argv[2] → temp2 allocated → count → FREE
Process argv[3] → temp3 allocated → count → FREE

At any moment, only ONE temp array exists.
Peak memory = size of largest temp array
```

---

## Relationship with Other Functions

### Functions Called By count_total_numbers

1. **ft_split()**
   - Called for each argument
   - Splits string on space delimiter
   - Returns NULL-terminated array
   - Returns NULL on allocation failure

2. **free_split()**
   - Called after counting each split
   - Frees both array and strings
   - Prevents memory leaks

### Functions That Call count_total_numbers

1. **parse_arguments()** (parent function)
   - Calls this first to get total count
   - Uses returned count to allocate result array
   - Checks for negative return (error)

### Relationship with join_all_arguments

**Two-pass strategy partners:**
```
count_total_numbers()          join_all_arguments()
        ↓                              ↓
    First pass                     Second pass
        ↓                              ↓
  Count numbers                  Fill array
        ↓                              ↓
Return total count         Return filled array
        ↓                              ↓
        └───────→ Both used by parse_arguments ←────────┘
```

**Why separate functions?**
- Each under 25 lines (42 Norm)
- Single responsibility principle
- Clear, testable logic
- Easier to debug and maintain

---

## Integration with Push_swap

### Usage in parse_arguments()

```c
char **parse_arguments(int argc, char **argv)
{
    int total;

    // Validate argument count
    if (argc < 2)
        return (NULL);

    // STEP 1: Count total numbers (this function!)
    total = count_total_numbers(argc, argv);

    // Check for error or zero numbers
    if (total <= 0)
        return (NULL);

    // STEP 2: Use count to allocate and fill array
    return (join_all_arguments(argc, argv, total));
}
```

**Flow diagram:**
```
main()
  ↓
  calls parse_arguments(argc, argv)
    ↓
    ├─→ Step 1: count_total_numbers(argc, argv)
    │     Returns: total = 5
    │
    ├─→ Step 2: Allocate array of size (total + 1)
    │     result = malloc(sizeof(char*) * 6)
    │
    └─→ Step 3: join_all_arguments(argc, argv, total)
          Fills the array with actual strings
          Returns: ["2", "4", "3", "91", "10", NULL]
```

### Memory Management Flow

```c
// PASS 1: count_total_numbers
// Purpose: Measurement only, no data retention

Allocate temp → Count elements → Free temp
Allocate temp → Count elements → Free temp
Allocate temp → Count elements → Free temp
        ↓
Return: total count

// PASS 2: join_all_arguments
// Purpose: Data collection and retention

Allocate result array (size = total + 1)
Allocate temp → Copy strings → Free temp array (keep strings!)
Allocate temp → Copy strings → Free temp array (keep strings!)
Allocate temp → Copy strings → Free temp array (keep strings!)
        ↓
Return: filled result array
```

---

## 42 Norm Considerations

### Norm Compliance Checklist

✅ **Function length:** ~20 lines (under 25-line limit)
✅ **Static function:** File-scope, not in header
✅ **Single responsibility:** Only counts numbers
✅ **No global variables:** All data in parameters/locals
✅ **Clear variable names:** i, count, temp, j are descriptive
✅ **Proper error handling:** Returns -1 on malloc failure
✅ **Memory management:** All allocations properly freed
✅ **Max 4 parameters:** Only 2 parameters (argc, argv)

### Why Static is Important

**42 Norm requirements:**
- Main functions should be under 25 lines
- Helper functions should be static (file-scope)
- No unnecessary exposure in header files

**Without static helpers:**
```c
// Would need everything in parse_arguments
// Function would exceed 25 lines
// 42 Norm violation!
```

**With static helpers:**
```c
// parse_arguments: ~10 lines ✓
// count_total_numbers: ~20 lines ✓
// join_all_arguments: ~23 lines ✓
// All under limit, norm compliant!
```

### Implementation Structure

```c
// File: srcs/parser.c

// Static helper 1 - NOT in header
static int count_total_numbers(int argc, char **argv)
{
    int     i;
    int     count;
    char    **temp;
    int     j;

    i = 1;
    count = 0;
    while (i < argc)
    {
        temp = ft_split(argv[i], ' ');
        if (!temp)
            return (-1);
        j = 0;
        while (temp[j])
        {
            count++;
            j++;
        }
        free_split(temp);
        i++;
    }
    return (count);
}

// Static helper 2 - NOT in header
static char **join_all_arguments(int argc, char **argv, int total)
{
    // ... implementation ...
}

// Public function - declared in header
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

---

## Common Mistakes to Avoid

### Mistake 1: Not Freeing Temporary Splits

```c
❌ WRONG:
while (i < argc)
{
    temp = ft_split(argv[i], ' ');
    // Count elements...
    // Missing: free_split(temp)
    i++;
}

Problem: Memory leak! Each temp allocation is leaked
Solution: Always free_split after counting
```

### Mistake 2: Forgetting to Check ft_split Return

```c
❌ WRONG:
temp = ft_split(argv[i], ' ');
j = 0;
while (temp[j])  // CRASH if temp is NULL!
{
    count++;
    j++;
}

Problem: If malloc fails, temp is NULL, dereferencing crashes
Solution: Check if (!temp) return (-1);
```

### Mistake 3: Starting Loop at i = 0

```c
❌ WRONG:
i = 0;
while (i < argc)
{
    temp = ft_split(argv[i], ' ');
    // ...
}

Problem: Tries to split argv[0] ("./push_swap")
Solution: Start at i = 1 (first real argument)
```

### Mistake 4: Not Returning Error on ft_split Failure

```c
❌ WRONG:
temp = ft_split(argv[i], ' ');
if (!temp)
    continue;  // Skip and continue

Problem: Silent failure, might allocate wrong size
Solution: Return -1 immediately on error
```

### Mistake 5: Using free Instead of free_split

```c
❌ WRONG:
temp = ft_split(argv[i], ' ');
// ... count ...
free(temp);  // Only frees array, not strings!

Problem: Memory leak! Strings inside array not freed
Solution: Use free_split(temp) which frees everything
```

### Mistake 6: Incorrect Loop Termination

```c
❌ WRONG:
while (i <= argc)  // Off-by-one error!
{
    temp = ft_split(argv[i], ' ');
    // ...
}

Problem: Accesses argv[argc] which is NULL or invalid
Solution: Use i < argc (strictly less than)
```

### Mistake 7: Not Handling Empty Splits

```c
❌ WRONG:
// Assuming ft_split always returns at least one element
temp = ft_split(argv[i], ' ');
count++;  // Wrong! Might be empty array

Problem: Counts incorrectly if ft_split returns empty array
Solution: Count actual elements with while (temp[j]) loop
```

---

## Testing Strategy

### Test Case 1: Single String Multiple Numbers

```c
char *argv[] = {"./push_swap", "5 3 1 4 2"};
int result = count_total_numbers(2, argv);
assert(result == 5);
```

### Test Case 2: Multiple Single Arguments

```c
char *argv[] = {"./push_swap", "5", "3", "1"};
int result = count_total_numbers(4, argv);
assert(result == 3);
```

### Test Case 3: Mixed Format

```c
char *argv[] = {"./push_swap", "2 4 3", "91", "10"};
int result = count_total_numbers(4, argv);
assert(result == 5);
```

### Test Case 4: Extra Spaces

```c
char *argv[] = {"./push_swap", "5   3    1"};
int result = count_total_numbers(2, argv);
assert(result == 3);  // ft_split handles multiple spaces
```

### Test Case 5: Single Number

```c
char *argv[] = {"./push_swap", "42"};
int result = count_total_numbers(2, argv);
assert(result == 1);
```

### Test Case 6: Large Number of Arguments

```c
char *argv[] = {"./push_swap", "1", "2", "3", ..., "100"};
int result = count_total_numbers(101, argv);
assert(result == 100);
```

### Test Case 7: Empty String (ft_split behavior)

```c
char *argv[] = {"./push_swap", ""};
int result = count_total_numbers(2, argv);
// Depends on ft_split implementation
// Either 0 or -1 is acceptable
assert(result <= 0);
```

### Test Case 8: Complex Mixed Format

```c
char *argv[] = {"./push_swap", "1 2", "3", "4 5 6", "7", "8 9"};
int result = count_total_numbers(6, argv);
assert(result == 9);
// Breakdown:
// "1 2"     → 2 numbers
// "3"       → 1 number
// "4 5 6"   → 3 numbers
// "7"       → 1 number
// "8 9"     → 2 numbers
// Total: 9
```

---

## Summary: What count_total_numbers Does

1. **First pass** through all command line arguments
2. **Splits** each argument by spaces using ft_split
3. **Counts** elements in each split result
4. **Frees** temporary splits immediately (no data retention)
5. **Accumulates** total count across all arguments
6. **Returns** total count for array allocation
7. **Error handling** returns -1 on malloc failure

**Key insights:**
- Static helper function (file-scope only)
- Part of two-pass strategy for efficient parsing
- Measurement pass - determines array size needed
- Temporary allocations freed immediately
- Enables single allocation in second pass
- Essential for 42 Norm compliance (keeps functions small)

**Purpose in bigger picture:**
```
parse_arguments flow:
1. count_total_numbers()  ← You are here
   └→ Return: total = 5

2. malloc(sizeof(char*) * (total + 1))
   └→ Allocate: array[6]

3. join_all_arguments()
   └→ Fill array with actual strings

4. Return filled array to caller
```

---

## Location in Project

**File:** `srcs/parser.c`
**Header:** NOT in header file (static function)
**Phase in TODO:** Phase 2.1 (Parsing & Validation - Helper Function)

**Implementation location:**
```c
// File: srcs/parser.c

// Static helper - internal to this file only
static int count_total_numbers(int argc, char **argv)
{
    // Implementation here
}

// NOT declared in push_swap.h
// Only visible within parser.c
```

---

## Related Functions

**Calls:**
- `ft_split()` - Splits each argument by spaces
- `free_split()` - Frees temporary split results

**Called by:**
- `parse_arguments()` - Uses returned count for allocation

**Works with:**
- `join_all_arguments()` - Complementary second pass function
- Together they implement the two-pass parsing strategy

**Related concepts:**
- Static functions in C
- Two-pass algorithms
- Memory-efficient parsing
- 42 Norm function length limits

---

*Remember: Counting first enables precise allocation. This two-pass approach is more efficient than repeatedly reallocating and copying as you discover new numbers. Measure twice, allocate once!*
