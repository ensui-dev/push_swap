# error_exit - Print Error, Free Memory, and Exit Program

## Function Signature

```c
void error_exit(t_stack **stack_a, t_stack **stack_b)
```

**Return type:** `void` - Never returns (calls exit)
**Parameters:**
- `t_stack **stack_a` - Pointer to stack A pointer (to free)
- `t_stack **stack_b` - Pointer to stack B pointer (to free)

---

## Purpose & Use Case

`error_exit` is a **centralized error handler** that combines three critical operations: printing the error message, freeing all allocated memory, and exiting the program with an error code. This ensures clean error handling without memory leaks.

### When You'll Use It

You'll call `error_exit` when:
1. **Fatal error during sorting** - Can't continue execution
2. **Centralized cleanup needed** - Both stacks must be freed
3. **Simplify error paths** - One call does everything
4. **Guarantee no memory leaks** - Even on errors

### Why This Matters

**The memory leak problem:**
```
Without error_exit:
Error detected
→ Print "Error"
→ Forget to free stack_a ← Memory leak!
→ Exit
→ Valgrind fails ✗

With error_exit:
Error detected
→ error_exit(&stack_a, &stack_b)
  → Print "Error"
  → Free stack_a ✓
  → Free stack_b ✓
  → Exit with code 1
→ Valgrind clean ✓
```

---

## Deep Dive: How It Works

### The Three-Step Process

```
Step 1: Print error message
  write(2, "Error\n", 6)

Step 2: Free all allocated memory
  if (stack_a && *stack_a) free_stack(stack_a)
  if (stack_b && *stack_b) free_stack(stack_b)

Step 3: Exit with error code
  exit(1)
```

### Step-by-Step Implementation

#### Step 1: Print Error

```c
print_error();
// Or inline: write(2, "Error\n", 6);
```

#### Step 2: Free Stack A

```c
if (stack_a && *stack_a)
    free_stack(stack_a);
```

**Why double check?**
- `stack_a` - Check pointer isn't NULL
- `*stack_a` - Check stack itself isn't NULL
- Safe even if never allocated

#### Step 3: Free Stack B

```c
if (stack_b && *stack_b)
    free_stack(stack_b);
```

**Same safety checks** for stack B

#### Step 4: Exit Program

```c
exit(1);
```

**Exit code 1** - indicates error occurred

---

## Complete Algorithm Pseudocode

```
FUNCTION error_exit(stack_a, stack_b):
    // Step 1: Print error message
    print_error()

    // Step 2: Free stack A if it exists
    IF stack_a is not NULL AND *stack_a is not NULL:
        free_stack(stack_a)

    // Step 3: Free stack B if it exists
    IF stack_b is not NULL AND *stack_b is not NULL:
        free_stack(stack_b)

    // Step 4: Exit with error code
    exit(1)
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: Both Stacks NULL

```c
t_stack *a = NULL;
t_stack *b = NULL;
error_exit(&a, &b);
// Prints error, no freeing needed, exits
```

### Edge Case 2: Only Stack A Exists

```c
t_stack *a = /* initialized */;
t_stack *b = NULL;
error_exit(&a, &b);
// Frees A, skips B, exits
```

### Edge Case 3: Both Stacks Exist

```c
t_stack *a = /* initialized */;
t_stack *b = /* initialized */;
error_exit(&a, &b);
// Frees both, exits
```

### Edge Case 4: NULL Pointers Passed

```c
error_exit(NULL, NULL);
// Safe - checks prevent dereferencing
// Prints error and exits
```

---

## Time & Space Complexity

### Time Complexity: O(n)

```
n = total elements in both stacks

Operations:
- print_error(): O(1)
- free_stack(A): O(n_a) where n_a = size of stack A
- free_stack(B): O(n_b) where n_b = size of stack B
- exit(1): O(1)

Total: O(1) + O(n_a) + O(n_b) + O(1) = O(n_a + n_b) = O(n)
```

### Space Complexity: O(1)

```
No additional allocation
Only frees existing memory
O(1) constant space
```

---

## Integration with Push_swap

### Usage During Parsing

```c
t_stack *init_stack_a(int argc, char **argv)
{
    char    **numbers;
    t_stack *stack_a;

    numbers = parse_arguments(argc, argv);
    if (!numbers)
    {
        error_exit(NULL, NULL);  // Early error
        // Never returns
    }

    // Continue parsing...
}
```

### Usage During Sorting

```c
void sort_large(t_stack **stack_a, t_stack **stack_b)
{
    // Sorting operations...

    // If something goes catastrophically wrong:
    if (critical_error_detected)
        error_exit(stack_a, stack_b);

    // Continue sorting...
}
```

---

## 42 Norm Considerations

### Implementation Example

```c
void    error_exit(t_stack **stack_a, t_stack **stack_b)
{
    print_error();
    if (stack_a && *stack_a)
        free_stack(stack_a);
    if (stack_b && *stack_b)
        free_stack(stack_b);
    exit(1);
}
```

**Norm compliant:**
- Under 25 lines ✓
- Clear responsibility ✓
- No globals ✓

---

## Common Mistakes to Avoid

### Mistake 1: Not Checking Pointers

```c
❌ WRONG:
void error_exit(t_stack **stack_a, t_stack **stack_b)
{
    print_error();
    free_stack(stack_a);  // CRASH if NULL!
    free_stack(stack_b);
    exit(1);
}

✓ CORRECT:
if (stack_a && *stack_a)
    free_stack(stack_a);
```

### Mistake 2: Wrong Exit Code

```c
❌ WRONG:
exit(0);  // Success code!

✓ CORRECT:
exit(1);  // Error code
```

### Mistake 3: Forgetting to Free

```c
❌ WRONG:
void error_exit(t_stack **stack_a, t_stack **stack_b)
{
    print_error();
    exit(1);  // Leaked memory!
}

✓ CORRECT:
// Free both stacks before exit
```

---

## Summary

1. **Prints** error message
2. **Frees** stack A if exists
3. **Frees** stack B if exists
4. **Exits** with code 1

---

## Location in Project

**File:** `srcs/error.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 3.2

---

*Remember: Clean error handling prevents memory leaks even when things go wrong!*
