# Defensive Programming Guide - index.c Functions

## Overview

This guide documents the defensive programming approach for all functions related to `index.c`. These functions implement index normalization, which transforms arbitrary stack values into predictable 0-based indices for efficient sorting.

**Status:** ✅ Documentation Updated (Option 3: Full Defensive Implementation)

---

## Critical Defensive Principles

### 1. **Input Validation First**
Always validate inputs at function entry before any operations:
- Check for NULL pointers
- Check for invalid sizes (<= 0)
- Check for edge cases (empty, single element)

### 2. **Fail Gracefully**
Never crash on invalid input:
- Return early with safe values (-1, NULL, 0)
- Don't proceed with invalid data
- Document return values clearly

### 3. **Bounds Checking**
Prevent buffer overruns:
- Always use `i < size` (not `i <= size`)
- Use dual conditions in loops (`i < size && ptr`)
- Validate array access is within bounds

### 4. **Resource Management**
Handle memory correctly:
- Check malloc return values
- Free allocated memory on ALL paths
- No memory leaks on early returns

---

## Function-by-Function Defensive Checklist

### assign_index() - Main Function

**File:** `srcs/index.c`
**Priority:** 🔴 CRITICAL (entry point)

**Defensive Checks Required:**

```c
void assign_index(t_stack *stack)
{
    // ✅ Step 1: CRITICAL - Validate stack parameter
    if (!stack)
        return;  // Prevents crash on NULL input

    // ✅ Step 2: Get and validate size
    int size = stack_size(stack);
    if (size <= 1)
        return;  // Optimization: nothing to normalize

    // ✅ Step 3: Check malloc return
    int *values = malloc(sizeof(int) * size);
    if (!values)
        return;  // No memory leak yet

    // ✅ Step 4-6: Use defensive helper functions
    copy_values_to_array(stack, values, size);
    sort_int_array(values, size);

    // ✅ Step 7: Assign indices safely
    t_stack *current = stack;
    while (current)
    {
        current->index = get_index_position(values, size, current->value);
        current = current->next;
    }

    // ✅ Step 8: ALWAYS free
    free(values);
}
```

**Key Points:**
- **NULL check:** Prevents segfault on `stack_size(NULL)`
- **Size optimization:** Skip work for 0 or 1 element
- **Malloc check:** Handle allocation failure gracefully
- **Always free:** No memory leaks

**Severity if missing:** 🔴 HIGH - Crash on NULL input

---

### copy_values_to_array() - Helper Function

**File:** `srcs/index.c` or `srcs/index_utils.c`
**Priority:** 🔴 HIGH (called by assign_index)

**Defensive Checks Required:**

```c
void copy_values_to_array(t_stack *stack, int *arr, int size)
{
    // ✅ Step 1: CRITICAL - Validate all parameters
    if (!arr || !stack)
        return;  // Prevent NULL dereference

    // ✅ Optional but recommended
    if (size <= 0)
        return;

    // ✅ Step 2: Safe loop with dual conditions
    int i = 0;
    while (i < size && stack)  // Both checks essential!
    {
        arr[i] = stack->value;  // Safe: validated above
        stack = stack->next;
        i++;
    }
}
```

**Key Points:**
- **NULL array check:** Critical if malloc failed in caller
- **NULL stack check:** Prevents dereference
- **Dual loop condition:** Prevents both overflow and NULL access
- **Size check:** Optional but explicit is better

**Severity if missing:** 🔴 HIGH - Crash on NULL array

---

### get_index_position() - Search Function

**File:** `srcs/index.c` or `srcs/index_utils.c`
**Priority:** 🔴 HIGH (called for every node)

**Defensive Checks Required:**

```c
int get_index_position(int *arr, int size, int value)
{
    // ✅ Step 1: CRITICAL - Validate inputs
    if (!arr || size <= 0)
        return (-1);  // Cannot search invalid input

    // ✅ Step 2: Safe search with bounds check
    int i = 0;
    while (i < size)  // Bounds check prevents overflow
    {
        if (arr[i] == value)  // Safe: validated above
            return (i);
        i++;
    }

    // ✅ Step 3: Defensive return for "not found"
    return (-1);  // Should never happen, but handle it
}
```

**Key Points:**
- **NULL array check:** Prevents read from NULL
- **Size validation:** Prevents invalid loop bounds
- **Bounds check:** `i < size` (not `i <= size`)
- **Error return:** -1 distinguishes from valid indices

**Severity if missing:** 🔴 HIGH - Crash on NULL array

---

### sort_int_array() - Sort Function

**File:** `srcs/index_utils.c` or `srcs/sort_utils.c`
**Priority:** 🟡 MEDIUM (called once, but still important)

**Defensive Checks Required:**

```c
void sort_int_array(int *arr, int size)
{
    // ✅ Step 1: Validate inputs
    if (!arr || size <= 1)
        return;  // Nothing to sort

    // ✅ Step 2: Safe sorting logic
    // (Implementation details with proper bounds checking)
}
```

**Key Points:**
- **NULL array check:** Prevents crash
- **Size validation:** size <= 1 needs no sorting
- **Bounds checking:** Ensure i and j stay in valid range

**Severity if missing:** 🟡 MEDIUM - Less likely to crash, but still unsafe

---

## Common Mistakes and How to Avoid Them

### Mistake 1: Not Checking NULL Stack in assign_index

**Problem:**
```c
void assign_index(t_stack *stack)
{
    int size = stack_size(stack);  // CRASH if stack is NULL!
}
```

**Solution:**
```c
void assign_index(t_stack *stack)
{
    if (!stack)  // ← Add this!
        return;
    int size = stack_size(stack);  // Now safe
}
```

**Priority:** 🔴 CRITICAL

---

### Mistake 2: Not Checking Malloc Failure

**Problem:**
```c
int *values = malloc(sizeof(int) * size);
copy_values_to_array(stack, values, size);  // CRASH if malloc failed!
```

**Solution:**
```c
int *values = malloc(sizeof(int) * size);
if (!values)  // ← Add this!
    return;
copy_values_to_array(stack, values, size);  // Now safe
```

**Priority:** 🔴 HIGH

---

### Mistake 3: Not Checking NULL Array in copy_values_to_array

**Problem:**
```c
void copy_values_to_array(t_stack *stack, int *arr, int size)
{
    int i = 0;
    while (i < size && stack)
    {
        arr[i] = stack->value;  // CRASH if arr is NULL!
    }
}
```

**Solution:**
```c
void copy_values_to_array(t_stack *stack, int *arr, int size)
{
    if (!arr || !stack)  // ← Add this!
        return;
    int i = 0;
    while (i < size && stack)
    {
        arr[i] = stack->value;  // Now safe
    }
}
```

**Priority:** 🔴 HIGH

---

### Mistake 4: Not Checking NULL Array in get_index_position

**Problem:**
```c
int get_index_position(int *arr, int size, int value)
{
    int i = 0;
    while (i < size)
    {
        if (arr[i] == value)  // CRASH if arr is NULL!
            return (i);
    }
}
```

**Solution:**
```c
int get_index_position(int *arr, int size, int value)
{
    if (!arr || size <= 0)  // ← Add this!
        return (-1);
    int i = 0;
    while (i < size)
    {
        if (arr[i] == value)  // Now safe
            return (i);
    }
}
```

**Priority:** 🔴 HIGH

---

### Mistake 5: Off-by-One in Loop Bounds

**Problem:**
```c
while (i <= size)  // ← WRONG! Can access arr[size]
{
    if (arr[i] == value)
        return (i);
}
```

**Solution:**
```c
while (i < size)  // ← CORRECT! Stops at arr[size-1]
{
    if (arr[i] == value)
        return (i);
}
```

**Priority:** 🔴 HIGH - Buffer overflow

---

## Testing Defensive Checks

### Test NULL Inputs

```c
// Test assign_index with NULL
assign_index(NULL);  // Should return safely, not crash

// Test copy_values_to_array with NULL arr
t_stack *stack = create_test_stack();
copy_values_to_array(stack, NULL, 10);  // Should return safely

// Test get_index_position with NULL arr
int pos = get_index_position(NULL, 10, 42);  // Should return -1
```

### Test Edge Cases

```c
// Empty stack
t_stack *empty = NULL;
assign_index(empty);  // Should handle gracefully

// Single element
t_stack *single = stack_new(42);
assign_index(single);  // Should optimize (return early)

// Zero size
int arr[10];
copy_values_to_array(stack, arr, 0);  // Should return early
```

### Test Malloc Failure

```c
// Simulate malloc failure (use fault injection or wrapper)
// assign_index should return safely without crash
```

---

## Implementation Priority

When refactoring code to add defensive checks:

### Phase 1: Critical Checks (Do First) 🔴

1. **assign_index:** Add NULL stack check
2. **assign_index:** Add malloc failure check
3. **copy_values_to_array:** Add NULL arr check
4. **get_index_position:** Add NULL arr check

### Phase 2: Important Checks (Do Second) 🟡

5. **assign_index:** Add size <= 1 optimization
6. **copy_values_to_array:** Add NULL stack check
7. **get_index_position:** Add size <= 0 check
8. **sort_int_array:** Add NULL arr and size checks

### Phase 3: Polish (Do Last) 🟢

9. Add comprehensive comments explaining each check
10. Update documentation with examples
11. Create unit tests for all edge cases
12. Run valgrind to verify no leaks

---

## Benefits of Defensive Programming

### 1. **Robustness**
- Functions don't crash on unexpected input
- Graceful handling of edge cases
- Program continues running safely

### 2. **Debuggability**
- Easier to identify where problems occur
- Clear error returns help debugging
- Valgrind reports are cleaner

### 3. **Maintainability**
- Code intent is explicit
- New developers understand safety requirements
- Changes less likely to introduce bugs

### 4. **Professional Quality**
- Meets industry standards
- Ready for production use
- Handles real-world conditions

---

## Cost vs. Benefit Analysis

### Cost of Defensive Checks

- **Performance:** Negligible (1-3 comparisons per function)
- **Code size:** ~3-5 lines per function
- **Complexity:** Minimal (simple if statements)

### Benefit of Defensive Checks

- **Prevents crashes:** Saves hours of debugging
- **Prevents memory corruption:** Avoids data loss
- **Professional quality:** Industry best practice
- **Peace of mind:** Code works in all scenarios

**Conclusion:** The cost is trivial, the benefit is huge. Always use defensive programming!

---

## Quick Reference

### Defensive Pattern Template

```c
return_type function_name(parameters)
{
    // Step 1: ALWAYS validate inputs first
    if (!pointer_param)
        return (error_value);
    if (size_param <= 0)
        return (error_value);

    // Step 2: Check resource allocation
    type *resource = malloc(...);
    if (!resource)
        return (error_value);

    // Step 3: Use safe operations
    while (i < size && pointer)  // Dual conditions
    {
        // Safe operations here
    }

    // Step 4: ALWAYS cleanup
    free(resource);
    return (success_value);
}
```

---

## Documentation Status

| Function | Documentation Updated | Defensive Approach | Status |
|----------|----------------------|-------------------|---------|
| assign_index | ✅ Yes | Full defensive | Complete |
| copy_values_to_array | ✅ Yes | Full defensive | Complete |
| get_index_position | ✅ Yes | Full defensive | Complete |
| sort_int_array | ⚠️ Partial | Needs update | TODO |

---

## Next Steps for Manual Implementation

1. Read updated documentation for each function
2. Implement defensive checks following the pseudocode
3. Test with NULL inputs and edge cases
4. Run valgrind to verify no leaks
5. Update unit tests to cover defensive cases
6. Review code with defensive checklist

---

**Remember:** Defensive programming is not about being paranoid - it's about being professional. Handle errors gracefully, validate inputs, and your code will be robust and reliable.

---

*Last Updated: 2026-01-20*
*Documentation Version: 1.0 (Full Defensive Approach)*
