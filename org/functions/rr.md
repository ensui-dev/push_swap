# rr - Rotate Both Stacks Simultaneously

## Function Signature

```c
void rr(t_stack **stack_a, t_stack **stack_b, int print)
```

**Return type:** `void` - No return value (modifies both stacks in place)
**Parameter 1:** `t_stack **stack_a` - Double pointer to stack A
**Parameter 2:** `t_stack **stack_b` - Double pointer to stack B
**Parameter 3:** `int print` - If 1, print "rr\n"; if 0, silent operation

---

## Purpose & Use Case

`rr` is a **combined operation** that rotates both stack A and stack B simultaneously. It calls both `ra` and `rb` in one operation, **but counts as only 1 move** instead of 2. This is a critical optimization - whenever both stacks need forward rotation, using `rr` reduces your operation count!

### When You'll Use It

You'll call `rr` whenever you need to:
1. **Optimize move count** - Rotate both stacks in 1 move instead of 2
2. **Simultaneous positioning** - Both stacks need elements rotated up
3. **Cost reduction** - Save operations in large sorts
4. **Turk algorithm** - When target positions require both rotations

### Why This Matters

**rr is pure optimization - it saves moves:**
```
Without rr (2 operations):
ra(&a, 1);  // Output: ra
rb(&b, 1);  // Output: rb
Total: 2 operations

With rr (1 operation):
rr(&a, &b, 1);  // Output: rr
Total: 1 operation

Same result, fewer moves! ✅
```

### Real-World Analogy

**Think of synchronized gears:**
```
Before rr:
Stack A:        Stack B:
[5] top         [7] top
[8]             [3]
[2]             [9]

After rr:
Stack A:        Stack B:
[8] top         [3] top
[2]             [9]
[5] bottom      [7] bottom

Both rotated together, counted as 1 move!
```

---

## Deep Dive: How It Works

### The Combined Rotate Operation Visualized

**Before `rr`:**
```
Stack A:                Stack B:
[5] <- top              [7] <- top
[8]                     [3]
[2]                     [9]
[3] <- last             [1] <- last
```

**After `rr`:**
```
Stack A:                Stack B:
[8] <- top (was 2nd)    [3] <- top (was 2nd)
[2]                     [9]
[3]                     [1]
[5] <- last (was 1st)   [7] <- last (was 1st)
```

**What happened:**
1. Performed ra on stack A (first → last)
2. Performed rb on stack B (first → last)
3. Both operations done simultaneously
4. Printed "rr\n" once
5. **Counts as 1 move!**

### Implementation Structure

**rr is a wrapper that calls ra and rb:**
```
FUNCTION rr:
    1. Call ra(stack_a, 0)  ← Silent mode!
    2. Call rb(stack_b, 0)  ← Silent mode!
    3. Print "rr\n" (if print flag set)
```

**Key insight:** ra and rb are called with `print = 0` so they don't output. Only rr outputs!

---

## Step-by-Step Implementation

### Step 1: Call ra Silently

**Rotate stack A without printing:**
```c
ra(stack_a, 0);  // print = 0, no output
```

**What ra does:**
```
Before: A = [5, 8, 2, 3]
After:  A = [8, 2, 3, 5]

No output (silent mode)
```

### Step 2: Call rb Silently

**Rotate stack B without printing:**
```c
rb(stack_b, 0);  // print = 0, no output
```

**What rb does:**
```
Before: B = [7, 3, 9, 1]
After:  B = [3, 9, 1, 7]

No output (silent mode)
```

### Step 3: Print Combined Operation

**If print flag is set:**
```c
if (print)
    ft_printf("rr\n");
```

**Output:** "rr\n"

**Total moves:** 1 (not 2!)

---

## Complete Algorithm Pseudocode

```
FUNCTION rr(stack_a, stack_b, print):
    // Step 1: Rotate A silently
    ra(stack_a, 0)

    // Step 2: Rotate B silently
    rb(stack_b, 0)

    // Step 3: Print if requested
    IF print == 1:
        PRINT "rr\n"

    RETURN
END FUNCTION
```

### Detailed Pseudocode with Edge Cases

```
FUNCTION rr(stack_a, stack_b, print):
    // Note: ra and rb handle their own validation
    // If A has < 2 elements, ra does nothing
    // If B has < 2 elements, rb does nothing

    // Rotate A (silent)
    IF stack_a AND *stack_a AND (*stack_a)->next:
        ra(stack_a, 0)  // Only rotates if possible

    // Rotate B (silent)
    IF stack_b AND *stack_b AND (*stack_b)->next:
        rb(stack_b, 0)  // Only rotates if possible

    // Print operation
    IF print == 1:
        WRITE "rr\n"

    RETURN
END FUNCTION
```

---

## Visual Execution Trace

### Example: Rotate Both [5, 8, 2] and [7, 3, 9]

**Initial State:**
```
Stack A: [5] -> [8] -> [2] -> NULL
Stack B: [7] -> [3] -> [9] -> NULL

Call: rr(&stack_a, &stack_b, 1);
```

**Step 1: Execute ra(stack_a, 0)**
```
Stack A before: [5] -> [8] -> [2] -> NULL
Stack A after:  [8] -> [2] -> [5] -> NULL
Output: (none - silent)
```

**Step 2: Execute rb(stack_b, 0)**
```
Stack B before: [7] -> [3] -> [9] -> NULL
Stack B after:  [3] -> [9] -> [7] -> NULL
Output: (none - silent)
```

**Step 3: Print "rr\n"**
```
Output: "rr\n"
```

**Final State:**
```
Stack A: [8] -> [2] -> [5] -> NULL
Stack B: [3] -> [9] -> [7] -> NULL

Total operations: 1 ✅
```

---

## Edge Cases

### Case 1: Both Stacks Empty

```c
t_stack *a = NULL;
t_stack *b = NULL;

rr(&a, &b, 1);

// Result: nothing happens
// ra and rb both return immediately
// No output (nothing was actually rotated)
```

### Case 2: One Stack Empty

```c
// A has elements, B is empty
t_stack *a = create_stack(5, 8, 2);
t_stack *b = NULL;

rr(&a, &b, 1);

// Result:
// A: [8, 2, 5] (rotated)
// B: NULL (unchanged)
// Output: rr
// Still counts as 1 move!
```

### Case 3: One Stack Has Single Element

```c
// A has multiple, B has one
t_stack *a = create_stack(5, 8, 2);
t_stack *b = stack_new(42);

rr(&a, &b, 1);

// Result:
// A: [8, 2, 5] (rotated)
// B: [42] (unchanged - can't rotate 1 element)
// Output: rr
```

### Case 4: Both Have Single Element

```c
t_stack *a = stack_new(5);
t_stack *b = stack_new(7);

rr(&a, &b, 1);

// Result:
// A: [5] (unchanged)
// B: [7] (unchanged)
// Output: rr (technically nothing happened!)
```

### Case 5: Perfect Use Case - Both Need Rotation

```c
// Both stacks have multiple elements
t_stack *a = create_stack(5, 8, 2, 3);
t_stack *b = create_stack(7, 3, 9, 1);

rr(&a, &b, 1);

// Result:
// A: [8, 2, 3, 5] (rotated)
// B: [3, 9, 1, 7] (rotated)
// Output: rr
// This is the ideal case - saved 1 operation!
```

### Case 6: Multiple rr Operations

```c
// Starting state
A: [5, 8, 2, 3]
B: [7, 3, 9, 1]

// Execute rr twice
rr(&a, &b, 1);  // A: [8, 2, 3, 5], B: [3, 9, 1, 7]
rr(&a, &b, 1);  // A: [2, 3, 5, 8], B: [9, 1, 7, 3]

// Output:
// rr
// rr

// Total: 2 operations (would be 4 if using ra+rb)
```

---

## Time & Space Complexity

### Time Complexity: **O(n + m)** - Linear Time

**Operations performed:**
1. Call ra(stack_a, 0) - O(n) where n = size of A
2. Call rb(stack_b, 0) - O(m) where m = size of B
3. Print - O(1)

**Total: O(n + m)**

**Why O(n + m)?**
```
ra must traverse A to find last node: O(n)
rb must traverse B to find last node: O(m)
Combined: O(n + m)

However, both operations happen, so cost is additive!
```

**Performance note:**
```
Time cost: Same as ra + rb
Move count: 1 instead of 2 ← This is the benefit!
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
- No additional allocations
- ra uses O(1) space
- rb uses O(1) space
- No arrays, no recursion

**Total: O(1)** - Fixed memory usage

---

## Relationship with Other Operations

### Combines ra and rb

```c
// These are equivalent in result:
ra(&a, 1);
rb(&b, 1);
// = 2 operations

rr(&a, &b, 1);
// = 1 operation ← Better!
```

### Inverse of rrr (Reverse Rotate Both)

```c
// Starting state
A: [5, 8, 2, 3]
B: [7, 3, 9, 1]

rr(&a, &b, 1);   // A: [8, 2, 3, 5], B: [3, 9, 1, 7]
rrr(&a, &b, 1);  // A: [5, 8, 2, 3], B: [7, 3, 9, 1]

// Back to original! rr and rrr are inverses
```

### Decision Tree: When to Use rr

```
Need to rotate A?
    No  → Don't use ra/rr
    Yes → Need to rotate B?
        No  → Use ra
        Yes → Use rr ← Save 1 operation!
```

---

## 42 Norm Considerations

### Function Signature

```c
void	rr(t_stack **stack_a, t_stack **stack_b, int print)
{
    ra(stack_a, 0);
    rb(stack_b, 0);
    if (print)
        ft_printf("rr\n");
}
```

**Norm requirements:**
- ✅ Return type void
- ✅ Takes two double pointers
- ✅ Simple function (~5 lines)
- ✅ No variables needed
- ✅ Calls existing functions (code reuse)

### Subject Requirements

**Exact naming and output:**
```c
✅ CORRECT:
Function name: rr
Output: "rr\n"
Counts as: 1 operation

❌ WRONG:
Function name: rotate_both, rr_both, rab
Output: "RR\n", "rr", "ra\nrb\n"
```

---

## Common Mistakes

### ❌ Mistake 1: Calling ra and rb with print=1

```c
// WRONG - Would print "ra\n" and "rb\n" separately!
void rr(t_stack **stack_a, t_stack **stack_b, int print)
{
    ra(stack_a, 1);  // Prints "ra"
    rb(stack_b, 1);  // Prints "rb"
    // Never prints "rr"!
}

Result: Output is "ra\nrb\n" not "rr\n"
```

**✅ Correct:**
```c
void rr(t_stack **stack_a, t_stack **stack_b, int print)
{
    ra(stack_a, 0);  // Silent
    rb(stack_b, 0);  // Silent
    if (print)
        ft_printf("rr\n");  // Print once
}
```

### ❌ Mistake 2: Not Printing When Both Rotate

```c
// WRONG - Only prints if BOTH can rotate
void rr(t_stack **stack_a, t_stack **stack_b, int print)
{
    int a_rotated = 0;
    int b_rotated = 0;

    if (*stack_a && (*stack_a)->next)
    {
        ra(stack_a, 0);
        a_rotated = 1;
    }
    if (*stack_b && (*stack_b)->next)
    {
        rb(stack_b, 0);
        b_rotated = 1;
    }

    if (print && a_rotated && b_rotated)  // Wrong!
        ft_printf("rr\n");
}
```

**✅ Should always print rr even if only one rotates!**

### ❌ Mistake 3: Counting as 2 Operations

```c
// Wrong understanding
operation_count++;  // For ra
operation_count++;  // For rb

Correct understanding:
operation_count++;  // For rr (just once!)
```

### ❌ Mistake 4: Wrong Parameter Order

```c
// WRONG - Swapped A and B
rr(&stack_b, &stack_a, 1);
```

**✅ Always A first, B second:**
```c
rr(&stack_a, &stack_b, 1);
```

### ❌ Mistake 5: Not Using rr When Possible

```c
// SUBOPTIMAL - Using separate operations
if (need_rotate_a)
    ra(&stack_a, 1);
if (need_rotate_b)
    rb(&stack_b, 1);

// Total: 2 operations
```

**✅ Optimize:**
```c
// OPTIMAL - Combine when possible
if (need_rotate_a && need_rotate_b)
{
    rr(&stack_a, &stack_b, 1);  // 1 operation
}
else if (need_rotate_a)
    ra(&stack_a, 1);
else if (need_rotate_b)
    rb(&stack_b, 1);
```

---

## Testing Strategy

### Test 1: Both Stacks Have Multiple Elements

```c
// Setup
t_stack *a = create_stack(5, 8, 2);
t_stack *b = create_stack(7, 3, 9);

// Test
rr(&a, &b, 1);

// Verify
assert(a->value == 8);  // Was second
assert(b->value == 3);  // Was second
assert(stack_last(a)->value == 5);  // Was first
assert(stack_last(b)->value == 7);  // Was first
printf("✓ Both stacks rotated\n");
```

### Test 2: Only A Has Multiple Elements

```c
// Setup
t_stack *a = create_stack(5, 8, 2);
t_stack *b = stack_new(42);

// Test
rr(&a, &b, 1);

// Verify
assert(a->value == 8);  // Rotated
assert(b->value == 42); // Unchanged
printf("✓ Only A rotated\n");
```

### Test 3: Only B Has Multiple Elements

```c
// Setup
t_stack *a = stack_new(5);
t_stack *b = create_stack(7, 3, 9);

// Test
rr(&a, &b, 1);

// Verify
assert(a->value == 5);  // Unchanged
assert(b->value == 3);  // Rotated
printf("✓ Only B rotated\n");
```

### Test 4: Both Empty

```c
// Setup
t_stack *a = NULL;
t_stack *b = NULL;

// Test
rr(&a, &b, 1);

// Verify
assert(a == NULL);
assert(b == NULL);
printf("✓ Empty stacks handled\n");
```

### Test 5: Silent Mode

```c
// Setup
t_stack *a = create_stack(5, 8, 2);
t_stack *b = create_stack(7, 3, 9);

// Test
rr(&a, &b, 0);  // print = 0

// Verify
assert(a->value == 8);  // Rotated
assert(b->value == 3);  // Rotated
// Verify no output printed
printf("✓ Silent mode works\n");
```

### Test 6: Multiple rr Operations

```c
// Setup
t_stack *a = create_stack(1, 2, 3);
t_stack *b = create_stack(4, 5, 6);

// Test: 3 rotations (full cycle)
rr(&a, &b, 1);
rr(&a, &b, 1);
rr(&a, &b, 1);

// Verify: Back to original
assert(a->value == 1);
assert(b->value == 4);
printf("✓ Multiple rotations work\n");
```

---

## Integration with Push_swap

### Usage 1: Turk Algorithm - Optimal Positioning

```c
void execute_cheapest_move(t_stack **a, t_stack **b, t_stack *cheapest)
{
    int moves_a = cheapest->cost_a;
    int moves_b = cheapest->cost_b;

    // Optimize: Use rr for common rotations
    while (moves_a > 0 && moves_b > 0)
    {
        rr(a, b, 1);  // Both need forward rotation
        moves_a--;
        moves_b--;
    }

    // Do remaining individual rotations
    while (moves_a > 0)
    {
        ra(a, 1);
        moves_a--;
    }
    while (moves_b > 0)
    {
        rb(b, 1);
        moves_b--;
    }

    // Finally push
    pa(a, b, 1);
}
```

### Usage 2: Cost Calculation

```c
int calculate_total_cost(int cost_a, int cost_b)
{
    // If both positive, can use rr
    if (cost_a > 0 && cost_b > 0)
    {
        int rr_count = min(cost_a, cost_b);
        int remaining_a = cost_a - rr_count;
        int remaining_b = cost_b - rr_count;

        return rr_count + remaining_a + remaining_b;
    }

    // Otherwise, just sum the costs
    return abs(cost_a) + abs(cost_b);
}
```

### Usage 3: Simultaneous Positioning

```c
// Prepare both stacks for optimal operation
void align_stacks(t_stack **a, t_stack **b, int target_pos_a, int target_pos_b)
{
    // Rotate both together as much as possible
    while (target_pos_a > 0 && target_pos_b > 0)
    {
        rr(a, b, 1);
        target_pos_a--;
        target_pos_b--;
    }

    // Finish individual rotations
    while (target_pos_a > 0)
    {
        ra(a, 1);
        target_pos_a--;
    }
    while (target_pos_b > 0)
    {
        rb(b, 1);
        target_pos_b--;
    }
}
```

---

## Real-World Usage Example

### Sorting Large Stack - Minimizing Operations

```c
// Goal: Push element from B to A at optimal position
// Element at position 3 in B, target position 2 in A

// Without optimization (5 operations):
ra(a, 1);  // Position A
ra(a, 1);  // Position A
rb(b, 1);  // Position B
rb(b, 1);  // Position B
rb(b, 1);  // Position B
pa(a, b, 1);  // Push
// Total: 6 operations

// With rr optimization (4 operations):
rr(a, b, 1);  // Both forward
rr(a, b, 1);  // Both forward
rb(b, 1);     // Finish B
pa(a, b, 1);  // Push
// Total: 4 operations ← Saved 2 moves!
```

---

## Performance Notes

### When to Use rr

**Use rr when:**
1. Both stacks need forward rotation (ra + rb)
2. Optimizing operation count is critical
3. Both target positions are in upper half of stacks

**Don't use rr when:**
1. Only one stack needs rotation (use ra or rb)
2. One needs forward, other needs reverse (use ra + rrb)
3. Both need reverse rotation (use rrr instead)

### Decision Matrix

```
Stack A needs:    Stack B needs:    Use:
Forward           Forward           rr    ✅ Optimize!
Forward           Reverse           ra+rrb
Forward           Nothing           ra
Reverse           Reverse           rrr   ✅ Optimize!
Reverse           Forward           rra+rb
```

---

## Summary

**What rr Does:**
- Calls ra(stack_a, 0) silently
- Calls rb(stack_b, 0) silently
- Prints "rr\n" once
- Counts as 1 operation (not 2!)
- Pure optimization operation

**Key Points:**
- ✅ Saves 1 operation when both stacks need rotation
- ✅ Critical for optimal sorting algorithms
- ✅ Calls must be silent (print = 0)
- ✅ Only prints "rr\n" once
- ✅ Time: O(n + m) - same as separate operations
- ✅ Move count: 1 - better than separate operations!

**Remember:**
1. Always use rr when both stacks need forward rotation
2. Silent calls to ra and rb (print = 0)
3. Print "rr\n" once at the end
4. Counts as single operation for scoring
5. Optimize by using rr whenever possible
6. Inverse operation is rrr

---

## Location in Project

**File:** `srcs/operations_rotate.c`
**Header:** `includes/push_swap.h`
**Category:** Phase 4 - Stack Operations
**Type:** Combined Rotate Operation

---

## Related Functions

- [ra](ra.md) - Rotate stack A (called by rr)
- [rb](rb.md) - Rotate stack B (called by rr)
- [rrr](rrr.md) - Reverse rotate both (inverse operation)
- [ss](ss.md) - Swap both (similar combined operation)

---

*rr is your optimization tool - use it whenever both stacks need forward rotation to minimize your operation count!*
