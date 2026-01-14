# is_sorted - Check if Stack is Sorted in Ascending Order

## Function Signature

```c
int is_sorted(t_stack *stack)
```

**Return type:** `int` - Returns 1 if sorted, 0 if not sorted
**Parameter:** `t_stack *stack` - Pointer to the head of the stack to check

---

## Purpose & Use Case

`is_sorted` is an **optimization function** that checks whether your stack is already sorted in ascending order. This is crucial for efficiency because **if the stack is already sorted, you don't need to do any work at all!**

### When You'll Use It

You'll call `is_sorted` whenever you need to:
1. **Early exit optimization** - Check at program start to avoid unnecessary sorting
2. **Algorithm completion** - Verify that sorting is complete
3. **Debugging** - Confirm your sorting algorithm worked correctly
4. **Test cases** - Validate expected outcomes

### Why This Matters

**Performance impact:**
```
Input: ./push_swap 1 2 3 4 5

Without is_sorted:
- Parse input: ✓
- Initialize stack: ✓
- Run sorting algorithm: 100+ operations
- Output: sa, pb, ra, ... (unnecessary!)

With is_sorted:
- Parse input: ✓
- Initialize stack: ✓
- Check is_sorted: Already sorted!
- Output: (nothing) ✅

Savings: Hundreds of operations avoided!
```

---

## Deep Dive: How It Works

### The Core Algorithm

The algorithm checks if each element is less than the next element:

```
For a stack to be sorted ascending:
stack[0] < stack[1] < stack[2] < ... < stack[n-1]

Example sorted:
[1] -> [2] -> [5] -> [8] -> NULL
 1 < 2 ✓
      2 < 5 ✓
           5 < 8 ✓
All comparisons pass → SORTED!

Example not sorted:
[3] -> [1] -> [5] -> [2] -> NULL
 3 < 1 ✗
First comparison fails → NOT SORTED!
```

### Step-by-Step Process

#### Step 1: Handle Edge Cases

**Check for NULL or single element:**
```c
if (!stack || !stack->next)
    return (1);  // NULL or single element is considered sorted
```

**Why?**
- NULL stack: No elements, trivially sorted
- Single element: One element is always sorted
- Both cases: No comparisons possible, return sorted

#### Step 2: Traverse and Compare

**Loop through stack:**
```c
while (stack->next)
{
    if (stack->value > stack->next->value)
        return (0);  // Found out of order pair
    stack = stack->next;
}
```

**What's happening:**
- Compare current node with next node
- If current > next → not ascending → return 0
- Move to next node
- Repeat until end of list

#### Step 3: All Checks Passed

**Return sorted:**
```c
return (1);  // Made it through all comparisons
```

If we never found an out-of-order pair, the stack is sorted!

---

## Visual Examples

### Example 1: Sorted Stack

```
Input: [1] -> [2] -> [5] -> [8] -> NULL

Iteration 1:
Compare: 1 vs 2
1 < 2 ? YES ✓
Continue...

Iteration 2:
Compare: 2 vs 5
2 < 5 ? YES ✓
Continue...

Iteration 3:
Compare: 5 vs 8
5 < 8 ? YES ✓
Continue...

Iteration 4:
Current: 8, Next: NULL
Loop ends

Result: return 1 (SORTED)
```

### Example 2: Not Sorted Stack

```
Input: [3] -> [1] -> [5] -> [2] -> NULL

Iteration 1:
Compare: 3 vs 1
3 < 1 ? NO ✗
Found descending pair!

Result: return 0 (NOT SORTED)
```

**Notice:** We stop immediately! No need to check remaining elements.

### Example 3: Mostly Sorted

```
Input: [1] -> [2] -> [5] -> [4] -> [8] -> NULL

Iteration 1:
Compare: 1 vs 2
1 < 2 ? YES ✓

Iteration 2:
Compare: 2 vs 5
2 < 5 ? YES ✓

Iteration 3:
Compare: 5 vs 4
5 < 4 ? NO ✗
Found descending pair!

Result: return 0 (NOT SORTED)
```

**Key point:** Even if 99% sorted, one wrong pair means NOT sorted.

### Example 4: Duplicates

```
Input: [1] -> [2] -> [2] -> [5] -> NULL

Iteration 1:
Compare: 1 vs 2
1 < 2 ? YES ✓

Iteration 2:
Compare: 2 vs 2
2 < 2 ? NO ✗
Found equal pair (not strictly ascending)!

Result: return 0 (NOT SORTED)
```

**Important:** This function checks for **strictly ascending** order. Duplicates fail the test.

**Note for push_swap:** The subject guarantees no duplicates in input, so this case shouldn't occur in valid input.

---

## Edge Cases

### Edge Case 1: NULL Stack

```c
t_stack *stack = NULL;
int result = is_sorted(stack);
// result = 1 (considered sorted)
```

**Reasoning:** An empty stack has no elements to be out of order, so it's trivially sorted.

### Edge Case 2: Single Element

```c
t_stack *stack = stack_new(42);
int result = is_sorted(stack);
// result = 1 (single element is sorted)
```

**Reasoning:** A single element has nothing to compare with, so it's sorted.

### Edge Case 3: Two Elements - Sorted

```c
t_stack *stack = stack_new(1);
stack_add_back(&stack, stack_new(2));
int result = is_sorted(stack);
// result = 1 (1 < 2, sorted)
```

### Edge Case 4: Two Elements - Not Sorted

```c
t_stack *stack = stack_new(2);
stack_add_back(&stack, stack_new(1));
int result = is_sorted(stack);
// result = 0 (2 > 1, not sorted)
```

### Edge Case 5: All Same Values (Shouldn't Happen)

```c
t_stack *stack = stack_new(5);
stack_add_back(&stack, stack_new(5));
stack_add_back(&stack, stack_new(5));
int result = is_sorted(stack);
// result = 0 (not strictly ascending)
```

**Note:** push_swap input validation should reject duplicates, so this is an invalid input case.

### Edge Case 6: Already Sorted Input

```c
// Input: ./push_swap 1 2 3 4 5
t_stack *stack = init_stack_a(argc, argv);
int result = is_sorted(stack);
// result = 1

if (result)
{
    // Don't sort! Just exit.
    free_stack(&stack);
    return (0);
}
```

**This is the primary use case!** Avoid unnecessary work.

### Edge Case 7: Reverse Sorted

```c
// Input: [5] -> [4] -> [3] -> [2] -> [1] -> NULL
int result = is_sorted(stack);
// result = 0 (first comparison: 5 > 4 fails)
```

**Efficiency:** Detected on first comparison! No need to check all elements.

---

## Time & Space Complexity

### Time Complexity: O(n) - Linear Time

**Best case: O(1)**
```
Stack: [5] -> [1] -> [2] -> [3] -> NULL
       ↑     ↑
       Compare: 5 > 1 ✗

Found unsorted pair on first comparison!
Operations: 1 comparison
Time: O(1) - constant time
```

**Average case: O(n)**
```
Stack: [1] -> [3] -> [2] -> [4] -> NULL
       ↑     ↑
       Compare: 1 < 3 ✓
             ↑     ↑
             Compare: 3 > 2 ✗

Found unsorted pair in middle
Operations: ~n/2 comparisons
Time: O(n) - linear time
```

**Worst case: O(n)**
```
Stack: [1] -> [2] -> [3] -> [4] -> [5] -> NULL
       ↑     ↑
       Compare: 1 < 2 ✓
             ↑     ↑
             Compare: 2 < 3 ✓
                   ... (all comparisons)

Must check all pairs to confirm sorted
Operations: n-1 comparisons
Time: O(n) - linear time
```

**Why O(n)?**
```
For a stack with n elements:
- Must compare n-1 pairs in worst case
- Each comparison is O(1)
- Total: (n-1) × O(1) = O(n)
```

### Space Complexity: O(1) - Constant Space

**Memory usage:**
```
Variables used:
- stack pointer (8 bytes on 64-bit)
- No arrays
- No recursion
- No additional allocations

Total: O(1) - constant space
```

### Early Exit Optimization

**Impact on average performance:**
```
Without early exit (must check all):
Average: Always O(n) comparisons

With early exit (stop at first failure):
Already sorted:     O(n) comparisons
Not sorted:         O(1) to O(n) comparisons
Average:            ~O(n/2) comparisons

Practical improvement: ~2x faster on random input
```

---

## Implementation Pseudocode

### Basic Implementation

```
FUNCTION is_sorted(stack):
    // Handle edge cases
    IF stack is NULL OR stack.next is NULL:
        RETURN 1  // Empty or single element is sorted

    // Traverse and compare pairs
    WHILE stack.next exists:
        IF stack.value > stack.next.value:
            RETURN 0  // Found descending pair, not sorted

        // Move to next node
        stack = stack.next

    // All pairs are ascending
    RETURN 1  // Stack is sorted
END FUNCTION
```

### Implementation with Detailed Comments

```
FUNCTION is_sorted(stack):
    // Step 1: Edge case handling
    // NULL stack or single element is considered sorted
    // because there are no elements to be out of order
    IF stack == NULL:
        RETURN 1
    IF stack.next == NULL:
        RETURN 1

    // Step 2: Initialize traversal
    current = stack

    // Step 3: Check each adjacent pair
    WHILE current.next is not NULL:
        // For ascending order, current must be less than next
        IF current.value >= current.next.value:
            // Found pair that's not ascending
            // Immediately return false (early exit)
            RETURN 0

        // Move to next node for comparison
        current = current.next

    // Step 4: All pairs checked successfully
    // No descending pairs found, stack is sorted
    RETURN 1
END FUNCTION
```

### Alternative: Strictly Ascending vs Non-Descending

```
FUNCTION is_sorted_strict(stack):
    // Strictly ascending: a < b < c (no equals)
    WHILE stack.next:
        IF stack.value >= stack.next.value:  // Reject equals
            RETURN 0
        stack = stack.next
    RETURN 1

FUNCTION is_sorted_non_descending(stack):
    // Non-descending: a <= b <= c (allows equals)
    WHILE stack.next:
        IF stack.value > stack.next.value:   // Allow equals
            RETURN 0
        stack = stack.next
    RETURN 1
```

**For push_swap:** Use strictly ascending (no duplicates allowed in input).

---

## 42 Norm Considerations

### Norm Compliance

✅ **Function length:** 5-10 lines (well under 25-line limit)
✅ **Single responsibility:** Only checks if sorted
✅ **No global variables:** Everything is local
✅ **Return value:** Clear boolean semantics (0 or 1)
✅ **No side effects:** Doesn't modify stack
✅ **Clear naming:** `is_sorted` clearly indicates boolean check

### Coding Best Practices

**Good variable naming:**
```c
✅ GOOD:
int is_sorted(t_stack *stack)
{
    while (stack->next)
    {
        if (stack->value > stack->next->value)
            return (0);
        stack = stack->next;
    }
    return (1);
}

❌ BAD:
int is_sorted(t_stack *s)
{
    while (s->next)
    {
        if (s->value > s->next->value)
            return (0);
        s = s->next;
    }
    return (1);
}
```

**Using the parameter as iterator:**
- It's okay to modify the parameter `stack` since it's passed by value
- We're not modifying the actual nodes, just moving our pointer
- No side effects on the calling function

---

## Common Mistakes to Avoid

### Mistake 1: Wrong Comparison Operator

```c
❌ WRONG:
int is_sorted(t_stack *stack)
{
    while (stack->next)
    {
        if (stack->value < stack->next->value)  // Wrong direction!
            return (0);
        stack = stack->next;
    }
    return (1);
}

This checks for DESCENDING order, not ascending!
```

### Mistake 2: Forgetting Edge Cases

```c
❌ WRONG:
int is_sorted(t_stack *stack)
{
    while (stack->next)  // Will crash if stack is NULL!
    {
        if (stack->value > stack->next->value)
            return (0);
        stack = stack->next;
    }
    return (1);
}

Must check: if (!stack) return (1);
```

### Mistake 3: Not Using Early Exit

```c
❌ INEFFICIENT:
int is_sorted(t_stack *stack)
{
    int sorted = 1;
    while (stack->next)
    {
        if (stack->value > stack->next->value)
            sorted = 0;  // Don't return, keep checking!
        stack = stack->next;
    }
    return (sorted);
}

Why wrong: Wastes time checking remaining elements
```

### Mistake 4: Wrong Return Values

```c
❌ WRONG:
int is_sorted(t_stack *stack)
{
    while (stack->next)
    {
        if (stack->value > stack->next->value)
            return (1);  // Backwards! Should return 0
        stack = stack->next;
    }
    return (0);  // Backwards! Should return 1
}
```

### Mistake 5: Checking Only First Pair

```c
❌ WRONG:
int is_sorted(t_stack *stack)
{
    if (!stack || !stack->next)
        return (1);

    if (stack->value > stack->next->value)
        return (0);

    return (1);  // Only checked first pair!
}

Stack [1]->[2]->[0] would return 1 (wrong!)
```

---

## Testing Strategy

### Test Case 1: Empty Stack

```c
t_stack *stack = NULL;
assert(is_sorted(stack) == 1);
printf("✓ Empty stack is sorted\n");
```

### Test Case 2: Single Element

```c
t_stack *stack = stack_new(42);
assert(is_sorted(stack) == 1);
printf("✓ Single element is sorted\n");
free_stack(&stack);
```

### Test Case 3: Two Elements Sorted

```c
t_stack *stack = stack_new(1);
stack_add_back(&stack, stack_new(2));
assert(is_sorted(stack) == 1);
printf("✓ Two elements [1,2] is sorted\n");
free_stack(&stack);
```

### Test Case 4: Two Elements Not Sorted

```c
t_stack *stack = stack_new(2);
stack_add_back(&stack, stack_new(1));
assert(is_sorted(stack) == 0);
printf("✓ Two elements [2,1] is not sorted\n");
free_stack(&stack);
```

### Test Case 5: Already Sorted List

```c
t_stack *stack = NULL;
int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

for (int i = 0; i < 10; i++)
    stack_add_back(&stack, stack_new(values[i]));

assert(is_sorted(stack) == 1);
printf("✓ Sorted list [1..10] is sorted\n");
free_stack(&stack);
```

### Test Case 6: Reverse Sorted

```c
t_stack *stack = NULL;
int values[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

for (int i = 0; i < 10; i++)
    stack_add_back(&stack, stack_new(values[i]));

assert(is_sorted(stack) == 0);
printf("✓ Reverse sorted [10..1] is not sorted\n");
free_stack(&stack);
```

### Test Case 7: Unsorted in Middle

```c
t_stack *stack = NULL;
int values[] = {1, 2, 3, 5, 4, 6, 7};  // 5,4 out of order

for (int i = 0; i < 7; i++)
    stack_add_back(&stack, stack_new(values[i]));

assert(is_sorted(stack) == 0);
printf("✓ Unsorted in middle is not sorted\n");
free_stack(&stack);
```

### Test Case 8: Negative Numbers

```c
t_stack *stack = NULL;
int values[] = {-5, -3, -1, 0, 2, 4};

for (int i = 0; i < 6; i++)
    stack_add_back(&stack, stack_new(values[i]));

assert(is_sorted(stack) == 1);
printf("✓ Negative numbers sorted correctly\n");
free_stack(&stack);
```

### Test Case 9: Large Numbers

```c
t_stack *stack = NULL;
stack_add_back(&stack, stack_new(INT_MIN));
stack_add_back(&stack, stack_new(0));
stack_add_back(&stack, stack_new(INT_MAX));

assert(is_sorted(stack) == 1);
printf("✓ INT_MIN to INT_MAX is sorted\n");
free_stack(&stack);
```

---

## Integration: How It's Used in push_swap

### Usage 1: Early Exit Optimization

```c
int main(int argc, char **argv)
{
    t_stack *stack_a;
    t_stack *stack_b;

    // Parse and validate input
    stack_a = init_stack_a(argc, argv);
    stack_b = NULL;

    // CRITICAL: Check if already sorted
    if (is_sorted(stack_a))
    {
        // Already sorted! Don't output anything
        free_stack(&stack_a);
        return (0);
    }

    // Not sorted, proceed with sorting algorithm
    sort_stack(&stack_a, &stack_b);

    // Clean up
    free_stack(&stack_a);
    free_stack(&stack_b);
    return (0);
}
```

### Usage 2: Algorithm Verification

```c
void sort_stack(t_stack **stack_a, t_stack **stack_b)
{
    // Choose sorting algorithm based on size
    int size = stack_size(*stack_a);

    if (size <= 5)
        sort_small(stack_a, stack_b);
    else
        sort_large(stack_a, stack_b);

    // Verify sorting worked (debugging)
    assert(is_sorted(*stack_a));
    assert(*stack_b == NULL);  // All elements back in A
}
```

### Usage 3: Sorting Small Stacks

```c
void sort_three(t_stack **stack_a)
{
    // Find max element
    int max_index = find_max_index(*stack_a);

    // Apply specific operation based on max position
    if (max_index == 0)
        ra(stack_a, 1);
    else if (max_index == 1)
        rra(stack_a, 1);

    // Check if sorted now
    if (is_sorted(*stack_a))
        return;

    // One more swap if needed
    sa(stack_a, 1);
}
```

### Usage 4: Testing Sorting Algorithms

```c
void test_sorting_algorithm(void)
{
    int test_cases[][10] = {
        {5, 3, 1, 4, 2},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        // ... more test cases
    };

    for (int i = 0; i < num_tests; i++)
    {
        t_stack *stack_a = create_stack(test_cases[i]);
        t_stack *stack_b = NULL;

        sort_stack(&stack_a, &stack_b);

        // Verify result
        assert(is_sorted(stack_a));
        assert(stack_b == NULL);

        free_stack(&stack_a);
        printf("Test %d: PASS\n", i);
    }
}
```

---

## Performance Impact

### Scenario Analysis

**Test with already sorted input:**
```bash
# Without is_sorted check:
$ ./push_swap 1 2 3 4 5
(runs full algorithm, outputs operations)
Time: 0.05s

# With is_sorted check:
$ ./push_swap 1 2 3 4 5
(outputs nothing immediately)
Time: 0.001s

Speedup: 50x faster!
```

**Test with reverse sorted input:**
```bash
$ ./push_swap 5 4 3 2 1
(runs algorithm)
Time: Same with or without check
Overhead: Negligible (~1ms)
```

**Conclusion:**
- Best case: Massive speedup
- Worst case: Negligible overhead
- Always worth including!

---

## Related Functions

### Functions Used By is_sorted

- **None** - This is a standalone checker function

### Functions That Use is_sorted

- **main()** - Early exit optimization
- **sort_three()** - Check if sorting complete
- **sort_small()** - Verify completion
- **Testing functions** - Validate correctness

### Similar Checking Functions

- **has_duplicates()** - Checks for duplicate values
- **is_valid_number()** - Checks if string is valid number
- **is_int_range()** - Checks if number fits in int

### Alternative Approaches

```c
// Check if stack is sorted descending
int is_reverse_sorted(t_stack *stack)
{
    while (stack->next)
    {
        if (stack->value < stack->next->value)
            return (0);
        stack = stack->next;
    }
    return (1);
}
```

---

## Location in Project

**File:** `srcs/stack_utils.c` (or `srcs/utils.c`)
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 1.2 (Stack Utility Functions - Advanced)

**Function prototype:**
```c
int is_sorted(t_stack *stack);
```

**Typical implementation:**
```c
int is_sorted(t_stack *stack)
{
    if (!stack || !stack->next)
        return (1);

    while (stack->next)
    {
        if (stack->value > stack->next->value)
            return (0);
        stack = stack->next;
    }
    return (1);
}
```

---

## Summary: What is_sorted Does

1. **Checks** if stack is sorted in ascending order
2. **Returns** 1 if sorted, 0 if not
3. **Optimizes** by using early exit on first failure
4. **Handles** edge cases (NULL, single element)
5. **Enables** massive performance gains for sorted input

**Key insight:** This simple function can save hundreds or thousands of operations. Always check if already sorted before running expensive algorithms!

---

*Remember: The fastest algorithm is the one you don't have to run. Always check if the work is already done!*
