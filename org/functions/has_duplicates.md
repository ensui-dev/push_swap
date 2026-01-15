# has_duplicates - Check for Duplicate Values in Stack

## Function Signature

```c
int has_duplicates(t_stack *stack)
```

**Return type:** `int` - Returns 1 if duplicates found, 0 if no duplicates
**Parameter:** `t_stack *stack` - Pointer to head of stack to check

---

## Purpose & Use Case

`has_duplicates` is a **uniqueness validation function** that ensures all values in the stack are unique. The push_swap subject explicitly forbids duplicate values, making this check mandatory for input validation.

### When You'll Use It

You'll call `has_duplicates` to:
1. **Final validation** - Check after building entire stack
2. **Enforce uniqueness** - Reject inputs with duplicate values
3. **Prevent invalid sorts** - Sorting duplicates is undefined in project
4. **Pass tests** - Project tester specifically checks duplicate handling

### Why This Matters

**The duplicate problem:**
```
Valid input:
[5] → [3] → [1] → [4] → [2] → NULL
All values unique ✓

Invalid input:
[5] → [3] → [1] → [3] → [2] → NULL
                    ↑    ↑
               Duplicate 3's ✗

Project requirement:
If duplicates exist, print "Error\n" and exit
```

---

## Deep Dive: How It Works

### The Nested Loop Comparison

```
Strategy: Compare every element with every other element

For stack: [5] → [3] → [1] → [4]

Compare 5 with: 3, 1, 4
Compare 3 with: 1, 4
Compare 1 with: 4
Compare 4 with: (nothing left)

If any comparison finds equal values → duplicates exist
```

### Step-by-Step Process

#### Step 1: Handle Edge Cases

```c
if (!stack || !stack->next)
    return (0);  // Empty or single element - no duplicates possible
```

**Why no duplicates?**
- Empty stack: No elements to duplicate
- Single element: One value can't duplicate itself
- Both cases: Return 0 (no duplicates)

#### Step 2: Outer Loop - Select Element to Compare

```c
t_stack *current = stack;
while (current)
{
    // Compare current with all elements after it
    current = current->next;
}
```

**Outer loop traversal:**
```
Iteration 1: current = [5]
Iteration 2: current = [3]
Iteration 3: current = [1]
Iteration 4: current = [4]
Iteration 5: current = NULL → exit
```

#### Step 3: Inner Loop - Compare with Remaining Elements

```c
t_stack *compare = current->next;
while (compare)
{
    if (current->value == compare->value)
        return (1);  // Found duplicate!
    compare = compare->next;
}
```

**Inner loop for each outer:**
```
current = [5]:
  compare with [3], [1], [4]

current = [3]:
  compare with [1], [4]

current = [1]:
  compare with [4]

current = [4]:
  compare with (nothing)
```

#### Step 4: No Duplicates Found

```c
return (0);  // All comparisons completed, no matches
```

---

## Visual Execution Trace

### Example 1: No Duplicates

```
Stack: [5] → [3] → [1] → [4] → NULL

═══════════════════════════════════════
OUTER ITERATION 1: current = [5]
═══════════════════════════════════════
Compare 5 with remaining elements:

Inner iteration 1:
  5 == 3? NO ✓
  Move to next

Inner iteration 2:
  5 == 1? NO ✓
  Move to next

Inner iteration 3:
  5 == 4? NO ✓
  Move to next

Inner iteration 4:
  compare = NULL, inner loop exits

No duplicates found for 5

═══════════════════════════════════════
OUTER ITERATION 2: current = [3]
═══════════════════════════════════════
Compare 3 with remaining elements:

Inner iteration 1:
  3 == 1? NO ✓
  Move to next

Inner iteration 2:
  3 == 4? NO ✓
  Move to next

Inner iteration 3:
  compare = NULL, inner loop exits

No duplicates found for 3

═══════════════════════════════════════
OUTER ITERATION 3: current = [1]
═══════════════════════════════════════
Compare 1 with remaining elements:

Inner iteration 1:
  1 == 4? NO ✓
  Move to next

Inner iteration 2:
  compare = NULL, inner loop exits

No duplicates found for 1

═══════════════════════════════════════
OUTER ITERATION 4: current = [4]
═══════════════════════════════════════
No elements after 4
Skip inner loop

═══════════════════════════════════════
OUTER ITERATION 5: current = NULL
═══════════════════════════════════════
Outer loop exits

═══════════════════════════════════════
RESULT
═══════════════════════════════════════
No duplicates found!
return 0 ✓
```

### Example 2: Duplicates Found

```
Stack: [5] → [3] → [1] → [3] → [2] → NULL
                    ↑         ↑
                   Duplicate 3's

═══════════════════════════════════════
OUTER ITERATION 1: current = [5]
═══════════════════════════════════════
Compare 5 with: 3, 1, 3, 2
All different from 5 ✓

═══════════════════════════════════════
OUTER ITERATION 2: current = [3]
═══════════════════════════════════════
Compare 3 with remaining elements:

Inner iteration 1:
  3 == 1? NO ✓
  Move to next

Inner iteration 2:
  3 == 3? YES! ✗
  DUPLICATE FOUND!

═══════════════════════════════════════
IMMEDIATE RETURN
═══════════════════════════════════════
return 1 (DUPLICATES EXIST) ✗
```

### Example 3: Multiple Duplicates

```
Stack: [5] → [3] → [5] → [3] → NULL
        ↑         ↑
       First pair

═══════════════════════════════════════
OUTER ITERATION 1: current = [5]
═══════════════════════════════════════
Compare 5 with remaining elements:

Inner iteration 1:
  5 == 3? NO ✓

Inner iteration 2:
  5 == 5? YES! ✗
  DUPLICATE FOUND!

═══════════════════════════════════════
IMMEDIATE RETURN
═══════════════════════════════════════
return 1 ✗

Note: Found first duplicate (5's)
Didn't need to check second duplicate (3's)
Early exit optimization!
```

---

## Complete Algorithm Pseudocode

```
FUNCTION has_duplicates(stack):
    // Step 1: Handle edge cases
    IF stack is NULL OR stack.next is NULL:
        RETURN 0  // No duplicates possible

    // Step 2: Nested loop comparison
    current = stack
    WHILE current is not NULL:
        // Inner loop: compare with all elements after current
        compare = current.next
        WHILE compare is not NULL:
            // Check if values match
            IF current.value == compare.value:
                RETURN 1  // Duplicate found!

            compare = compare.next

        current = current.next

    // Step 3: No duplicates found
    RETURN 0
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: Empty Stack

```c
t_stack *stack = NULL;
int result = has_duplicates(stack);
// result = 0 (no duplicates - no elements!)
```

### Edge Case 2: Single Element

```c
t_stack *stack = stack_new(42);
int result = has_duplicates(stack);
// result = 0 (one element can't duplicate itself)
```

### Edge Case 3: Two Different Elements

```c
// Stack: [5] → [3] → NULL
int result = has_duplicates(stack);
// result = 0 (5 != 3)
```

### Edge Case 4: Two Identical Elements

```c
// Stack: [5] → [5] → NULL
int result = has_duplicates(stack);
// result = 1 (duplicates found!)
```

### Edge Case 5: Duplicates at Start

```c
// Stack: [3] → [3] → [1] → [4] → NULL
// First comparison finds duplicate
int result = has_duplicates(stack);
// result = 1 (found immediately)
```

### Edge Case 6: Duplicates at End

```c
// Stack: [5] → [3] → [1] → [4] → [4] → NULL
// Last comparison finds duplicate
int result = has_duplicates(stack);
// result = 1 (found at end)
```

### Edge Case 7: Multiple Pairs of Duplicates

```c
// Stack: [5] → [5] → [3] → [3] → [1] → [1] → NULL
// Multiple duplicate pairs
int result = has_duplicates(stack);
// result = 1 (stops at first pair found)
```

### Edge Case 8: All Same Values

```c
// Stack: [5] → [5] → [5] → [5] → NULL
int result = has_duplicates(stack);
// result = 1 (first comparison finds duplicate)
```

---

## Time & Space Complexity

### Time Complexity: O(n²)

```
n = number of elements in stack

Worst case (no duplicates):
- Outer loop: n iterations
- Inner loop: decreasing iterations
  - Iteration 1: n-1 comparisons
  - Iteration 2: n-2 comparisons
  - ...
  - Iteration n: 0 comparisons

Total comparisons: (n-1) + (n-2) + ... + 1 + 0
                 = n(n-1)/2
                 = (n² - n)/2
                 = O(n²)

Best case (duplicates at start):
- Outer loop: 1 iteration
- Inner loop: 1 comparison
- Total: O(1)

Average case: O(n²)
```

**Example with 5 elements:**
```
Comparisons needed:
current=0: compare with 1,2,3,4 → 4 comparisons
current=1: compare with 2,3,4   → 3 comparisons
current=2: compare with 3,4     → 2 comparisons
current=3: compare with 4       → 1 comparison
current=4: none                 → 0 comparisons

Total: 4 + 3 + 2 + 1 = 10 comparisons = 5×4/2
```

### Space Complexity: O(1)

```
Variables used:
- current pointer: 8 bytes
- compare pointer: 8 bytes
- No arrays
- No recursion
- No allocations

Total: O(1) - constant space
```

### Alternative: Sorting Approach

```
Alternative algorithm (not implemented):
1. Copy values to array
2. Sort array: O(n log n)
3. Check adjacent elements: O(n)
Total: O(n log n) time, O(n) space

Trade-off:
- Faster for large inputs
- More memory usage
- More complex implementation

For push_swap:
- Inputs typically small (< 500)
- O(n²) is acceptable
- Simpler implementation preferred
```

---

## Relationship with Other Functions

### Functions Called By has_duplicates

- **None** - Pure comparison function

### Functions That Use has_duplicates

- **init_stack_a()** - Final validation after building stack

---

## Integration with Push_swap

### Usage in init_stack_a()

```c
t_stack *init_stack_a(int argc, char **argv)
{
    char    **numbers;
    t_stack *stack_a;
    int     i;

    // Parse and validate format
    numbers = parse_arguments(argc, argv);
    if (!numbers)
        return (NULL);

    // Build stack from validated strings
    stack_a = NULL;
    i = 0;
    while (numbers[i])
    {
        // Format validation
        if (!is_valid_number(numbers[i]))
            return (error_cleanup());

        // Range validation
        long value = ft_atol(numbers[i]);
        if (!is_int_range(value))
            return (error_cleanup());

        // Create and add node
        t_stack *node = stack_new((int)value);
        if (!node)
            return (error_cleanup());
        stack_add_back(&stack_a, node);
        i++;
    }

    // FINAL CHECK: Duplicate validation
    if (has_duplicates(stack_a))
    {
        free_stack(&stack_a);
        if (argc == 2)
            free_split(numbers);
        return (NULL);
    }

    // Clean up and return
    if (argc == 2)
        free_split(numbers);
    return (stack_a);
}
```

---

## 42 Norm Considerations

### Norm Compliance

✅ **Function length:** 15-20 lines (under 25-line limit)
✅ **Single responsibility:** Only checks for duplicates
✅ **Nested loops:** Acceptable for comparison algorithm
✅ **Clear variable names:** current, compare
✅ **Early return:** Optimizes performance

### Implementation Example

```c
int has_duplicates(t_stack *stack)
{
    t_stack *current;
    t_stack *compare;

    if (!stack || !stack->next)
        return (0);
    current = stack;
    while (current)
    {
        compare = current->next;
        while (compare)
        {
            if (current->value == compare->value)
                return (1);
            compare = compare->next;
        }
        current = current->next;
    }
    return (0);
}
```

---

## Common Mistakes to Avoid

### Mistake 1: Not Handling Edge Cases

```c
❌ WRONG:
int has_duplicates(t_stack *stack)
{
    t_stack *current = stack;
    // What if stack is NULL? CRASH!
    while (current)
    {
        // ...
    }
}

✓ CORRECT:
if (!stack || !stack->next)
    return (0);
```

### Mistake 2: Comparing Element with Itself

```c
❌ WRONG:
t_stack *current = stack;
t_stack *compare = stack;  // Starts at same position!
while (compare)
{
    if (current->value == compare->value)
        return (1);  // Always true on first check!
}

✓ CORRECT:
t_stack *compare = current->next;  // Start with next element
```

### Mistake 3: Not Checking All Pairs

```c
❌ WRONG:
// Only checking adjacent elements
if (current->value == current->next->value)
    return (1);

Problem: Misses non-adjacent duplicates
[5] → [3] → [5] wouldn't be detected

✓ CORRECT:
// Check current with ALL remaining elements
```

### Mistake 4: Wrong Return Values

```c
❌ WRONG:
if (current->value == compare->value)
    return (0);  // Should return 1!
// ...
return (1);  // Should return 0!

✓ CORRECT:
if (duplicates_found)
    return (1);  // True, has duplicates
return (0);  // False, no duplicates
```

### Mistake 5: Inefficient Re-checking

```c
❌ WRONG:
// Comparing in both directions
[5] vs [3]  ← checked
[3] vs [5]  ← unnecessary (already checked)

✓ CORRECT:
// Only compare with elements after current
// Avoids redundant checks
```

---

## Testing Strategy

### Test Case 1: No Duplicates

```c
// Stack: [5] → [3] → [1] → [4] → [2] → NULL
assert(has_duplicates(stack) == 0);
printf("✓ No duplicates detected correctly\n");
```

### Test Case 2: Duplicate at Start

```c
// Stack: [5] → [5] → [3] → [1] → NULL
assert(has_duplicates(stack) == 1);
printf("✓ Immediate duplicate detected\n");
```

### Test Case 3: Duplicate at End

```c
// Stack: [5] → [3] → [1] → [1] → NULL
assert(has_duplicates(stack) == 1);
printf("✓ Duplicate at end detected\n");
```

### Test Case 4: Duplicate in Middle

```c
// Stack: [5] → [3] → [1] → [3] → [2] → NULL
assert(has_duplicates(stack) == 1);
printf("✓ Middle duplicate detected\n");
```

### Test Case 5: Edge Cases

```c
t_stack *empty = NULL;
assert(has_duplicates(empty) == 0);
printf("✓ Empty stack handled\n");

t_stack *single = stack_new(42);
assert(has_duplicates(single) == 0);
printf("✓ Single element handled\n");
free(single);
```

### Test Case 6: All Same

```c
// Stack: [5] → [5] → [5] → [5] → NULL
assert(has_duplicates(stack) == 1);
printf("✓ All same values detected\n");
```

### Test Case 7: Negative Numbers

```c
// Stack: [-5] → [-3] → [-5] → [1] → NULL
assert(has_duplicates(stack) == 1);
printf("✓ Negative duplicates detected\n");
```

---

## Summary: What has_duplicates Does

1. **Handles** edge cases (NULL, single element)
2. **Iterates** through each element (outer loop)
3. **Compares** with all subsequent elements (inner loop)
4. **Returns** 1 immediately when duplicate found (early exit)
5. **Returns** 0 if no duplicates after all comparisons

**Key insight:** This is a brute-force O(n²) algorithm, but it's simple, correct, and sufficient for push_swap's input sizes. The nested loop structure ensures every possible pair is checked exactly once.

---

## Location in Project

**File:** `srcs/validate.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 2.3 (Parsing & Validation - Duplicate Detection)

**Note:** This function is in `validate.c` (not `parser.c`) to comply with 42 Norm's
5 functions per file limit. Parser.c contains parse_arguments + 2 static helpers.

**Function prototype:**
```c
int has_duplicates(t_stack *stack);
```

---

## Related Functions

**Called by:**
- `init_stack_a()` - Final validation check

**Related validation:**
- `is_valid_number()` - Format validation
- `is_int_range()` - Range validation
- `is_sorted()` - Order checking

---

*Remember: Thorough validation prevents mysterious bugs. Check for duplicates after building your stack, and you'll never have to debug sorting behavior with duplicate values!*
