# free_split - Free NULL-Terminated String Array

## Function Signature

```c
void free_split(char **split)
```

**Return type:** `void` - No return value
**Parameter:** `char **split` - NULL-terminated array of strings to free

---

## Purpose & Use Case

`free_split` is a **memory cleanup function** specifically designed to free string arrays created by `ft_split`. It properly deallocates both the individual strings and the array itself, preventing memory leaks when parsing single-string arguments.

### When You'll Use It

You'll call `free_split` to:
1. **Clean up after ft_split** - Free arrays from `./push_swap "5 3 1"`
2. **Error path cleanup** - Free on validation failures
3. **Normal cleanup** - Free after successful parsing
4. **Prevent memory leaks** - Essential for valgrind compliance

### Why This Matters

**ft_split memory structure:**
```
ft_split("5 3 1", ' ') allocates:

Array of pointers:
split = [ptr0, ptr1, ptr2, NULL]  ← malloc'd array
         ↓     ↓     ↓
String copies:
        "5"  "3"  "1"              ← 3 malloc'd strings

Total allocations: 4
- 1 array
- 3 strings

Must free all 4 blocks!
```

---

## Deep Dive: How It Works

### The Two-Level Freeing Process

```
Step 1: Free each string
split[0] = "5"   → free(split[0])
split[1] = "3"   → free(split[1])
split[2] = "1"   → free(split[2])
split[3] = NULL  → stop (NULL terminator)

Step 2: Free array itself
split = [...]    → free(split)
```

### Step-by-Step Process

#### Step 1: Check for NULL

```c
if (!split)
    return;
```

**Safety:** Nothing to free if NULL

#### Step 2: Free Each String

```c
int i = 0;
while (split[i])
{
    free(split[i]);
    i++;
}
```

**Loop through strings:**
- Free split[0]
- Free split[1]
- ...
- Stop at NULL

#### Step 3: Free Array

```c
free(split);
```

**Free the container** after contents

---

## Visual Execution Trace

### Example: Free Array from ft_split

```
Input: split from ft_split("5 3 1", ' ')

Memory layout:
split → [&"5", &"3", &"1", NULL]
         ↓     ↓     ↓
        "5"   "3"   "1"

═══════════════════════════════════════
STEP 1: Check NULL
═══════════════════════════════════════
split is not NULL ✓

═══════════════════════════════════════
STEP 2: Free Strings
═══════════════════════════════════════
i = 0:
  split[0] = "5"
  free("5")
  Memory block for "5" freed

i = 1:
  split[1] = "3"
  free("3")
  Memory block for "3" freed

i = 2:
  split[2] = "1"
  free("1")
  Memory block for "1" freed

i = 3:
  split[3] = NULL
  Loop exits

State: All strings freed

═══════════════════════════════════════
STEP 3: Free Array
═══════════════════════════════════════
free(split)
Array itself freed

═══════════════════════════════════════
COMPLETE
═══════════════════════════════════════
All 4 allocations freed:
- 3 string blocks ✓
- 1 array block ✓
No memory leaks ✓
```

---

## Complete Algorithm Pseudocode

```
FUNCTION free_split(split):
    // Step 1: Safety check
    IF split is NULL:
        RETURN

    // Step 2: Free each string
    i = 0
    WHILE split[i] is not NULL:
        free(split[i])
        i = i + 1

    // Step 3: Free array
    free(split)
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: NULL Array

```c
char **split = NULL;
free_split(split);
// Safe - returns immediately
```

### Edge Case 2: Empty Array

```c
// split = [NULL]
free_split(split);
// Skips string loop, frees array
```

### Edge Case 3: Single String

```c
// split = ["42", NULL]
free_split(split);
// Frees "42", then array
```

---

## Time & Space Complexity

### Time Complexity: O(n)

```
n = number of strings

Operations:
- Free each string: O(n)
- Free array: O(1)
Total: O(n)
```

### Space Complexity: O(1)

```
Only frees memory, doesn't allocate
O(1) constant space
```

---

## Common Mistakes

### Mistake 1: Wrong Order

```c
❌ WRONG:
free(split);  // Free array first
for (int i = 0; split[i]; i++)
    free(split[i]);  // Use after free!

✓ CORRECT:
for (int i = 0; split[i]; i++)
    free(split[i]);  // Free strings first
free(split);  // Then array
```

### Mistake 2: Not Checking NULL

```c
❌ WRONG:
for (int i = 0; split[i]; i++)  // CRASH if split is NULL
    free(split[i]);

✓ CORRECT:
if (!split)
    return;
```

---

## Integration with Push_swap

### Usage with Single String Input

```c
t_stack *init_stack_a(int argc, char **argv)
{
    char **numbers = parse_arguments(argc, argv);
    t_stack *stack_a = NULL;

    // Build stack...

    // Cleanup (if argc == 2, numbers was allocated)
    if (argc == 2)
        free_split(numbers);

    return (stack_a);
}
```

---

## 42 Norm Considerations

### Implementation

```c
void    free_split(char **split)
{
    int i;

    if (!split)
        return ;
    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}
```

**Norm compliant:** ~10 lines ✓

---

## Summary

1. **Checks** for NULL pointer
2. **Iterates** through string array
3. **Frees** each string
4. **Frees** array itself

**Key insight:** ft_split creates multi-level allocations. This function correctly frees both levels.

---

## Location in Project

**File:** `srcs/free.c`
**Header:** `includes/push_swap.h`

**Function prototype:**
```c
void free_split(char **split);
```

---

*Remember: Match your frees to your mallocs. ft_split does multiple mallocs, so free_split does multiple frees!*
