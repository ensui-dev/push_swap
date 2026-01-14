# main - Entry Point for Push_swap Program

## Function Signature

```c
int main(int argc, char **argv)
```

**Return type:** `int` - Exit status (0 success, 1 error)
**Parameters:**
- `int argc` - Argument count
- `char **argv` - Argument vector (array of strings)

---

## Purpose & Use Case

`main` is the **program entry point** that orchestrates the entire push_swap execution flow: validation, initialization, optimization checks, sorting, and cleanup. It's the conductor that calls all other functions in the correct order.

### When It Runs

`main` executes when:
1. **Program starts** - ./push_swap 5 3 1 4 2
2. **Arguments provided** - Validates and processes
3. **Sorting needed** - Chooses and executes algorithm
4. **Program exits** - Returns status code

### Why This Matters

**Complete program flow:**
```
./push_swap 5 3 1 4 2

main() orchestrates:
├─ Validate arguments
├─ Initialize stack A
├─ Check if already sorted (optimization)
├─ Choose sorting algorithm
├─ Execute sort
├─ Clean up memory
└─ Exit with status code
```

---

## Deep Dive: How It Works

### The Seven-Phase Execution

```
Phase 1: Argument validation
Phase 2: Stack initialization
Phase 3: Early exit optimization
Phase 4: Algorithm selection
Phase 5: Sort execution
Phase 6: Memory cleanup
Phase 7: Exit
```

### Step-by-Step Process

#### Step 1: Check Argument Count

```c
if (argc < 2)
    return (0);  // No error for no arguments
```

**Edge case handling:**
- `./push_swap` → exit silently (0)
- No error message per subject

#### Step 2: Initialize Stack A

```c
t_stack *stack_a = init_stack_a(argc, argv);
if (!stack_a)
{
    print_error();
    return (1);
}
```

**Initialization includes:**
- Parse arguments
- Validate format
- Check range
- Check duplicates
- Build linked list

#### Step 3: Check if Already Sorted

```c
if (is_sorted(stack_a))
{
    free_stack(&stack_a);
    return (0);  // No output for sorted input
}
```

**Optimization:** Skip sorting if already sorted

#### Step 4: Initialize Stack B

```c
t_stack *stack_b = NULL;
```

**Stack B starts empty**

#### Step 5: Choose and Execute Sort

```c
choose_sort(&stack_a, &stack_b);
```

**Routing:**
- Small stacks (≤5): Optimized algorithms
- Large stacks (>5): Turk algorithm or chunks

#### Step 6: Clean Up

```c
free_stack(&stack_a);
free_stack(&stack_b);
```

**Memory management:** Free all allocations

#### Step 7: Return Success

```c
return (0);
```

---

## Visual Execution Trace

### Example: Valid Input

```
Command: ./push_swap 5 3 1

═══════════════════════════════════════
PHASE 1: Argument Validation
═══════════════════════════════════════
argc = 4 (> 1) ✓

═══════════════════════════════════════
PHASE 2: Initialize Stack A
═══════════════════════════════════════
init_stack_a(4, argv)
↓
Parse: ["5", "3", "1"]
Validate: all valid ✓
Build: [5] → [3] → [1] → NULL
Return: stack_a

═══════════════════════════════════════
PHASE 3: Check if Sorted
═══════════════════════════════════════
is_sorted(stack_a)?
5 > 3 → NO ✗
Not sorted, continue...

═══════════════════════════════════════
PHASE 4: Initialize Stack B
═══════════════════════════════════════
stack_b = NULL

═══════════════════════════════════════
PHASE 5: Sort
═══════════════════════════════════════
choose_sort(&stack_a, &stack_b)
↓
Size = 3
Call sort_three()
↓
Output operations:
ra
sa

Result:
stack_a = [1] → [3] → [5] → NULL
stack_b = NULL

═══════════════════════════════════════
PHASE 6: Cleanup
═══════════════════════════════════════
free_stack(&stack_a)
free_stack(&stack_b)

═══════════════════════════════════════
PHASE 7: Exit
═══════════════════════════════════════
return 0 ✓
```

### Example: Error Case

```
Command: ./push_swap 5 3 abc

═══════════════════════════════════════
PHASE 1: Argument Validation
═══════════════════════════════════════
argc = 4 ✓

═══════════════════════════════════════
PHASE 2: Initialize Stack A
═══════════════════════════════════════
init_stack_a(4, argv)
↓
Parse: ["5", "3", "abc"]
Validate "abc": FAIL ✗
↓
Return NULL

═══════════════════════════════════════
ERROR HANDLING
═══════════════════════════════════════
stack_a == NULL
print_error()
↓
Output: "Error\n"

═══════════════════════════════════════
EXIT
═══════════════════════════════════════
return 1 ✗
```

---

## Complete Algorithm Pseudocode

```
FUNCTION main(argc, argv):
    // Phase 1: Validate arguments
    IF argc < 2:
        RETURN 0  // Silent exit

    // Phase 2: Initialize stack
    stack_a = init_stack_a(argc, argv)
    IF stack_a is NULL:
        print_error()
        RETURN 1

    // Phase 3: Optimization check
    IF is_sorted(stack_a):
        free_stack(&stack_a)
        RETURN 0

    // Phase 4: Initialize helper stack
    stack_b = NULL

    // Phase 5: Sort
    choose_sort(&stack_a, &stack_b)

    // Phase 6: Cleanup
    free_stack(&stack_a)
    free_stack(&stack_b)

    // Phase 7: Success
    RETURN 0
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: No Arguments

```bash
$ ./push_swap
$ echo $?
0
```

**No error message** per subject

### Edge Case 2: Already Sorted

```bash
$ ./push_swap 1 2 3 4 5
$ echo $?
0
```

**No output** - optimization

### Edge Case 3: Invalid Input

```bash
$ ./push_swap 5 3 abc
Error
$ echo $?
1
```

**Error message and exit code 1**

---

## Time & Space Complexity

### Time Complexity: Depends on sort

```
Initialization: O(n²) (duplicate check)
Sorting: 
  - Small (≤5): O(1)
  - Large: O(n²) or O(n log n)
Cleanup: O(n)

Total: Dominated by sorting algorithm
```

### Space Complexity: O(n)

```
Stack A: O(n)
Stack B: O(n) worst case
Total: O(n)
```

---

## 42 Norm Considerations

### Implementation Example

```c
int main(int argc, char **argv)
{
    t_stack *stack_a;
    t_stack *stack_b;

    if (argc < 2)
        return (0);
    stack_a = init_stack_a(argc, argv);
    if (!stack_a)
    {
        print_error();
        return (1);
    }
    if (is_sorted(stack_a))
    {
        free_stack(&stack_a);
        return (0);
    }
    stack_b = NULL;
    choose_sort(&stack_a, &stack_b);
    free_stack(&stack_a);
    free_stack(&stack_b);
    return (0);
}
```

**Norm compliant:** ~25 lines ✓

---

## Common Mistakes

### Mistake 1: Not Freeing Memory

```c
❌ WRONG:
int main(int argc, char **argv)
{
    t_stack *stack_a = init_stack_a(argc, argv);
    choose_sort(&stack_a, &stack_b);
    return (0);  // Memory leak!
}

✓ CORRECT:
free_stack(&stack_a);
free_stack(&stack_b);
return (0);
```

### Mistake 2: Wrong Error Handling

```c
❌ WRONG:
if (argc < 2)
{
    print_error();  // Don't print for no args!
    return (1);
}

✓ CORRECT:
if (argc < 2)
    return (0);  // Silent exit
```

---

## Summary

1. **Validates** argument count
2. **Initializes** stack from arguments
3. **Optimizes** with early sorted check
4. **Selects** appropriate sorting algorithm
5. **Executes** sort with operations output
6. **Cleans** up all allocated memory
7. **Returns** appropriate exit code

**Key insight:** main is the orchestrator. It doesn't do the work itself, but calls the right functions in the right order.

---

## Location in Project

**File:** `srcs/main.c`
**Header:** `includes/push_swap.h`

---

*Remember: A good main function is simple and clean. It delegates work to specialized functions and focuses on overall flow!*
