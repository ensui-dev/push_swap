# rrr - Reverse Rotate Both Stacks Simultaneously

## Function Signature

```c
void rrr(t_stack **stack_a, t_stack **stack_b, int print)
```

**Return type:** `void` - No return value (modifies both stacks in place)
**Parameter 1:** `t_stack **stack_a` - Double pointer to stack A
**Parameter 2:** `t_stack **stack_b` - Double pointer to stack B
**Parameter 3:** `int print` - If 1, print "rrr\n"; if 0, silent operation

---

## Purpose & Use Case

`rrr` is a **combined operation** that reverse rotates both stack A and stack B simultaneously. It calls both `rra` and `rrb` in one operation, **but counts as only 1 move** instead of 2. This is a critical optimization - whenever both stacks need reverse rotation (moving last element to first), using `rrr` reduces your operation count!

### When You'll Use It

You'll call `rrr` whenever you need to:
1. **Optimize move count** - Reverse rotate both stacks in 1 move instead of 2
2. **Simultaneous backward positioning** - Both stacks need last elements moved to top
3. **Cost reduction** - Save operations in large sorts
4. **Turk algorithm** - When target positions require both reverse rotations

### Why This Matters

**rrr is pure optimization - it saves moves:**
```
Without rrr (2 operations):
rra(&a, 1);  // Output: rra
rrb(&b, 1);  // Output: rrb
Total: 2 operations

With rrr (1 operation):
rrr(&a, &b, 1);  // Output: rrr
Total: 1 operation

Same result, fewer moves! ✅
```

### Real-World Analogy

**Think of synchronized escalators going down:**
```
Before rrr:
Stack A:        Stack B:
[5] top         [7] top
[8]             [3]
[2]             [9]
[3] bottom      [1] bottom

After rrr:
Stack A:        Stack B:
[3] top         [1] top
[5]             [7]
[8]             [3]
[2] bottom      [9] bottom

Both reverse rotated together, counted as 1 move!
```

---

## Deep Dive: How It Works

### The Combined Reverse Rotate Operation Visualized

**Before `rrr`:**
```
Stack A:                Stack B:
[5] <- top              [7] <- top
[8]                     [3]
[2]                     [9]
[3] <- last             [1] <- last
```

**After `rrr`:**
```
Stack A:                Stack B:
[3] <- top (was last)   [1] <- top (was last)
[5]                     [7]
[8]                     [3]
[2] <- last             [9] <- last
```

**What happened:**
1. Performed rra on stack A (last → first)
2. Performed rrb on stack B (last → first)
3. Both operations done simultaneously
4. Printed "rrr\n" once
5. **Counts as 1 move!**

### Implementation Structure

**rrr is a wrapper that calls rra and rrb:**
```
FUNCTION rrr:
    1. Call rra(stack_a, 0)  ← Silent mode!
    2. Call rrb(stack_b, 0)  ← Silent mode!
    3. Print "rrr\n" (if print flag set)
```

**Key insight:** rra and rrb are called with `print = 0` so they don't output. Only rrr outputs!

---

## Step-by-Step Implementation

### Step 1: Call rra Silently

**Reverse rotate stack A without printing:**
```c
rra(stack_a, 0);  // print = 0, no output
```

**What rra does:**
```
Before: A = [5, 8, 2, 3]
After:  A = [3, 5, 8, 2]

No output (silent mode)
```

### Step 2: Call rrb Silently

**Reverse rotate stack B without printing:**
```c
rrb(stack_b, 0);  // print = 0, no output
```

**What rrb does:**
```
Before: B = [7, 3, 9, 1]
After:  B = [1, 7, 3, 9]

No output (silent mode)
```

### Step 3: Print Combined Operation

**If print flag is set:**
```c
if (print)
    ft_printf("rrr\n");
```

**Output:** "rrr\n"

**Total moves:** 1 (not 2!)

---

## Complete Algorithm Pseudocode

```
FUNCTION rrr(stack_a, stack_b, print):
    // Step 1: Reverse rotate A silently
    rra(stack_a, 0)

    // Step 2: Reverse rotate B silently
    rrb(stack_b, 0)

    // Step 3: Print if requested
    IF print == 1:
        PRINT "rrr\n"

    RETURN
END FUNCTION
```

### Detailed Pseudocode with Edge Cases

```
FUNCTION rrr(stack_a, stack_b, print):
    // Note: rra and rrb handle their own validation
    // If A has < 2 elements, rra does nothing
    // If B has < 2 elements, rrb does nothing

    // Reverse rotate A (silent)
    IF stack_a AND *stack_a AND (*stack_a)->next:
        rra(stack_a, 0)  // Only rotates if possible

    // Reverse rotate B (silent)
    IF stack_b AND *stack_b AND (*stack_b)->next:
        rrb(stack_b, 0)  // Only rotates if possible

    // Print operation
    IF print == 1:
        WRITE "rrr\n"

    RETURN
END FUNCTION
```

---

## Visual Execution Trace

### Example: Reverse Rotate Both [5, 8, 2, 3] and [7, 3, 9, 1]

**Initial State:**
```
Stack A: [5] -> [8] -> [2] -> [3] -> NULL
Stack B: [7] -> [3] -> [9] -> [1] -> NULL

Call: rrr(&stack_a, &stack_b, 1);
```

**Step 1: Execute rra(stack_a, 0)**
```
Stack A before: [5] -> [8] -> [2] -> [3] -> NULL
Stack A after:  [3] -> [5] -> [8] -> [2] -> NULL
Output: (none - silent)
```

**Step 2: Execute rrb(stack_b, 0)**
```
Stack B before: [7] -> [3] -> [9] -> [1] -> NULL
Stack B after:  [1] -> [7] -> [3] -> [9] -> NULL
Output: (none - silent)
```

**Step 3: Print "rrr\n"**
```
Output: "rrr\n"
```

**Final State:**
```
Stack A: [3] -> [5] -> [8] -> [2] -> NULL
Stack B: [1] -> [7] -> [3] -> [9] -> NULL

Total operations: 1 ✅
```

---

## Edge Cases

### Case 1: Both Stacks Empty

```c
t_stack *a = NULL;
t_stack *b = NULL;

rrr(&a, &b, 1);

// Result: nothing happens
// rra and rrb both return immediately
// No output (nothing was actually rotated)
```

### Case 2: One Stack Empty

```c
// A has elements, B is empty
t_stack *a = create_stack(5, 8, 2, 3);
t_stack *b = NULL;

rrr(&a, &b, 1);

// Result:
// A: [3, 5, 8, 2] (reverse rotated)
// B: NULL (unchanged)
// Output: rrr
// Still counts as 1 move!
```

### Case 3: One Stack Has Single Element

```c
// A has multiple, B has one
t_stack *a = create_stack(5, 8, 2, 3);
t_stack *b = stack_new(42);

rrr(&a, &b, 1);

// Result:
// A: [3, 5, 8, 2] (reverse rotated)
// B: [42] (unchanged - can't rotate 1 element)
// Output: rrr
```

### Case 4: Both Have Single Element

```c
t_stack *a = stack_new(5);
t_stack *b = stack_new(7);

rrr(&a, &b, 1);

// Result:
// A: [5] (unchanged)
// B: [7] (unchanged)
// Output: rrr (technically nothing happened!)
```

### Case 5: Perfect Use Case - Both Need Reverse Rotation

```c
// Both stacks have multiple elements
t_stack *a = create_stack(5, 8, 2, 3);
t_stack *b = create_stack(7, 3, 9, 1);

rrr(&a, &b, 1);

// Result:
// A: [3, 5, 8, 2] (reverse rotated)
// B: [1, 7, 3, 9] (reverse rotated)
// Output: rrr
// This is the ideal case - saved 1 operation!
```

### Case 6: Multiple rrr Operations

```c
// Starting state
A: [5, 8, 2, 3]
B: [7, 3, 9, 1]

// Execute rrr twice
rrr(&a, &b, 1);  // A: [3, 5, 8, 2], B: [1, 7, 3, 9]
rrr(&a, &b, 1);  // A: [2, 3, 5, 8], B: [9, 1, 7, 3]

// Output:
// rrr
// rrr

// Total: 2 operations (would be 4 if using rra+rrb)
```

---

## Time & Space Complexity

### Time Complexity: **O(n + m)** - Linear Time

**Operations performed:**
1. Call rra(stack_a, 0) - O(n) where n = size of A
2. Call rrb(stack_b, 0) - O(m) where m = size of B
3. Print - O(1)

**Total: O(n + m)**

**Why O(n + m)?**
```
rra must traverse A to find last and second-to-last: O(n)
rrb must traverse B to find last and second-to-last: O(m)
Combined: O(n + m)

Both operations happen, so cost is additive!
```

**Performance note:**
```
Time cost: Same as rra + rrb
Move count: 1 instead of 2 ← This is the benefit!
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
- No additional allocations
- rra uses O(1) space
- rrb uses O(1) space
- No arrays, no recursion

**Total: O(1)** - Fixed memory usage

---

## Relationship with Other Operations

### Combines rra and rrb

```c
// These are equivalent in result:
rra(&a, 1);
rrb(&b, 1);
// = 2 operations

rrr(&a, &b, 1);
// = 1 operation ← Better!
```

### Inverse of rr (Rotate Both)

```c
// Starting state
A: [5, 8, 2, 3]
B: [7, 3, 9, 1]

rr(&a, &b, 1);   // A: [8, 2, 3, 5], B: [3, 9, 1, 7]
rrr(&a, &b, 1);  // A: [5, 8, 2, 3], B: [7, 3, 9, 1]

// Back to original! rr and rrr are inverses
```

### Decision Tree: When to Use rrr

```
Need to reverse rotate A?
    No  → Don't use rra/rrr
    Yes → Need to reverse rotate B?
        No  → Use rra
        Yes → Use rrr ← Save 1 operation!
```

---

## 42 Norm Considerations

### Function Signature

```c
void	rrr(t_stack **stack_a, t_stack **stack_b, int print)
{
    rra(stack_a, 0);
    rrb(stack_b, 0);
    if (print)
        ft_printf("rrr\n");
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
Function name: rrr
Output: "rrr\n"
Counts as: 1 operation

❌ WRONG:
Function name: reverse_rotate_both, rrr_both, rrab
Output: "RRR\n", "rrr", "rra\nrrb\n"
```

---

## Common Mistakes

### ❌ Mistake 1: Calling rra and rrb with print=1

```c
// WRONG - Would print "rra\n" and "rrb\n" separately!
void rrr(t_stack **stack_a, t_stack **stack_b, int print)
{
    rra(stack_a, 1);  // Prints "rra"
    rrb(stack_b, 1);  // Prints "rrb"
    // Never prints "rrr"!
}

Result: Output is "rra\nrrb\n" not "rrr\n"
```

**✅ Correct:**
```c
void rrr(t_stack **stack_a, t_stack **stack_b, int print)
{
    rra(stack_a, 0);  // Silent
    rrb(stack_b, 0);  // Silent
    if (print)
        ft_printf("rrr\n");  // Print once
}
```

### ❌ Mistake 2: Not Printing When Both Reverse Rotate

```c
// WRONG - Only prints if BOTH can reverse rotate
void rrr(t_stack **stack_a, t_stack **stack_b, int print)
{
    int a_rotated = 0;
    int b_rotated = 0;

    if (*stack_a && (*stack_a)->next)
    {
        rra(stack_a, 0);
        a_rotated = 1;
    }
    if (*stack_b && (*stack_b)->next)
    {
        rrb(stack_b, 0);
        b_rotated = 1;
    }

    if (print && a_rotated && b_rotated)  // Wrong!
        ft_printf("rrr\n");
}
```

**✅ Should always print rrr even if only one rotates!**

### ❌ Mistake 3: Counting as 2 Operations

```c
// Wrong understanding
operation_count++;  // For rra
operation_count++;  // For rrb

Correct understanding:
operation_count++;  // For rrr (just once!)
```

### ❌ Mistake 4: Wrong Parameter Order

```c
// WRONG - Swapped A and B
rrr(&stack_b, &stack_a, 1);
```

**✅ Always A first, B second:**
```c
rrr(&stack_a, &stack_b, 1);
```

### ❌ Mistake 5: Not Using rrr When Possible

```c
// SUBOPTIMAL - Using separate operations
if (need_reverse_rotate_a)
    rra(&stack_a, 1);
if (need_reverse_rotate_b)
    rrb(&stack_b, 1);

// Total: 2 operations
```

**✅ Optimize:**
```c
// OPTIMAL - Combine when possible
if (need_reverse_rotate_a && need_reverse_rotate_b)
{
    rrr(&stack_a, &stack_b, 1);  // 1 operation
}
else if (need_reverse_rotate_a)
    rra(&stack_a, 1);
else if (need_reverse_rotate_b)
    rrb(&stack_b, 1);
```

### ❌ Mistake 6: Confusing rr and rrr

```c
// WRONG - Using rr instead of rrr
// These do opposite things!

rr(&a, &b, 1);   // First → Last
rrr(&a, &b, 1);  // Last → First

// Don't confuse them!
```

---

## Testing Strategy

### Test 1: Both Stacks Have Multiple Elements

```c
// Setup
t_stack *a = create_stack(5, 8, 2, 3);
t_stack *b = create_stack(7, 3, 9, 1);

// Test
rrr(&a, &b, 1);

// Verify
assert(a->value == 3);  // Was last
assert(b->value == 1);  // Was last
assert(stack_last(a)->value == 2);  // Was second-to-last
assert(stack_last(b)->value == 9);  // Was second-to-last
printf("✓ Both stacks reverse rotated\n");
```

### Test 2: Only A Has Multiple Elements

```c
// Setup
t_stack *a = create_stack(5, 8, 2, 3);
t_stack *b = stack_new(42);

// Test
rrr(&a, &b, 1);

// Verify
assert(a->value == 3);   // Reverse rotated
assert(b->value == 42);  // Unchanged
printf("✓ Only A reverse rotated\n");
```

### Test 3: Only B Has Multiple Elements

```c
// Setup
t_stack *a = stack_new(5);
t_stack *b = create_stack(7, 3, 9, 1);

// Test
rrr(&a, &b, 1);

// Verify
assert(a->value == 5);  // Unchanged
assert(b->value == 1);  // Reverse rotated
printf("✓ Only B reverse rotated\n");
```

### Test 4: Both Empty

```c
// Setup
t_stack *a = NULL;
t_stack *b = NULL;

// Test
rrr(&a, &b, 1);

// Verify
assert(a == NULL);
assert(b == NULL);
printf("✓ Empty stacks handled\n");
```

### Test 5: Silent Mode

```c
// Setup
t_stack *a = create_stack(5, 8, 2, 3);
t_stack *b = create_stack(7, 3, 9, 1);

// Test
rrr(&a, &b, 0);  // print = 0

// Verify
assert(a->value == 3);  // Reverse rotated
assert(b->value == 1);  // Reverse rotated
// Verify no output printed
printf("✓ Silent mode works\n");
```

### Test 6: Inverse of rr

```c
// Setup
t_stack *a = create_stack(5, 8, 2, 3);
t_stack *b = create_stack(7, 3, 9, 1);

// Test: rr then rrr
rr(&a, &b, 1);   // Forward rotate both
rrr(&a, &b, 1);  // Reverse rotate both

// Verify: Back to original
assert(a->value == 5);
assert(b->value == 7);
printf("✓ rr and rrr are inverses\n");
```

---

## Integration with Push_swap

### Usage 1: Turk Algorithm - Optimal Positioning

```c
void execute_cheapest_move(t_stack **a, t_stack **b, t_stack *cheapest)
{
    int moves_a = cheapest->cost_a;
    int moves_b = cheapest->cost_b;

    // Optimize: Use rrr for common reverse rotations
    while (moves_a < 0 && moves_b < 0)
    {
        rrr(a, b, 1);  // Both need reverse rotation
        moves_a++;
        moves_b++;
    }

    // Do remaining individual reverse rotations
    while (moves_a < 0)
    {
        rra(a, 1);
        moves_a++;
    }
    while (moves_b < 0)
    {
        rrb(b, 1);
        moves_b++;
    }

    // Finally push
    pa(a, b, 1);
}
```

### Usage 2: Cost Calculation

```c
int calculate_total_cost(int cost_a, int cost_b)
{
    // If both negative (both need reverse rotation), can use rrr
    if (cost_a < 0 && cost_b < 0)
    {
        int rrr_count = min(abs(cost_a), abs(cost_b));
        int remaining_a = abs(cost_a) - rrr_count;
        int remaining_b = abs(cost_b) - rrr_count;

        return rrr_count + remaining_a + remaining_b;
    }

    // Otherwise, just sum the absolute costs
    return abs(cost_a) + abs(cost_b);
}
```

### Usage 3: Simultaneous Backward Positioning

```c
// Prepare both stacks for optimal operation
void align_stacks_reverse(t_stack **a, t_stack **b, int pos_a, int pos_b)
{
    int size_a = stack_size(*a);
    int size_b = stack_size(*b);

    // Calculate reverse rotation needs
    int rra_count = size_a - pos_a;
    int rrb_count = size_b - pos_b;

    // Reverse rotate both together as much as possible
    while (rra_count > 0 && rrb_count > 0)
    {
        rrr(a, b, 1);
        rra_count--;
        rrb_count--;
    }

    // Finish individual reverse rotations
    while (rra_count > 0)
    {
        rra(a, 1);
        rra_count--;
    }
    while (rrb_count > 0)
    {
        rrb(b, 1);
        rrb_count--;
    }
}
```

### Usage 4: Mixed Rotation Optimization

```c
void execute_rotations(t_stack **a, t_stack **b, int cost_a, int cost_b)
{
    // Both positive: use rr
    if (cost_a > 0 && cost_b > 0)
    {
        while (cost_a > 0 && cost_b > 0)
        {
            rr(a, b, 1);
            cost_a--;
            cost_b--;
        }
    }
    // Both negative: use rrr
    else if (cost_a < 0 && cost_b < 0)
    {
        while (cost_a < 0 && cost_b < 0)
        {
            rrr(a, b, 1);  // Optimal!
            cost_a++;
            cost_b++;
        }
    }

    // Finish individual rotations
    while (cost_a > 0)
        ra(a, 1), cost_a--;
    while (cost_a < 0)
        rra(a, 1), cost_a++;
    while (cost_b > 0)
        rb(b, 1), cost_b--;
    while (cost_b < 0)
        rrb(b, 1), cost_b++;
}
```

---

## Real-World Usage Example

### Sorting Large Stack - Minimizing Operations

```c
// Goal: Push element from B to A at optimal position
// Element at position 7 in B (size 10), target position 8 in A (size 10)

// Without optimization (7 operations):
rra(a, 1);  // Position A (from bottom)
rra(a, 1);
rrb(b, 1);  // Position B (from bottom)
rrb(b, 1);
rrb(b, 1);
pa(a, b, 1);  // Push
// Total: 6 operations

// With rrr optimization (4 operations):
rrr(a, b, 1);  // Both reverse
rrr(a, b, 1);  // Both reverse
rrb(b, 1);     // Finish B
pa(a, b, 1);   // Push
// Total: 4 operations ← Saved 2 moves!
```

---

## Performance Notes

### When to Use rrr

**Use rrr when:**
1. Both stacks need reverse rotation (rra + rrb)
2. Optimizing operation count is critical
3. Both target positions are in lower half of stacks

**Don't use rrr when:**
1. Only one stack needs reverse rotation (use rra or rrb)
2. One needs forward, other needs reverse (use ra + rrb or rra + rb)
3. Both need forward rotation (use rr instead)

### Decision Matrix

```
Stack A needs:    Stack B needs:    Use:
Forward           Forward           rr    ✅ Optimize!
Forward           Reverse           ra+rrb
Forward           Nothing           ra
Reverse           Reverse           rrr   ✅ Optimize!
Reverse           Forward           rra+rb
Reverse           Nothing           rra
```

---

## Summary

**What rrr Does:**
- Calls rra(stack_a, 0) silently
- Calls rrb(stack_b, 0) silently
- Prints "rrr\n" once
- Counts as 1 operation (not 2!)
- Pure optimization operation

**Key Points:**
- ✅ Saves 1 operation when both stacks need reverse rotation
- ✅ Critical for optimal sorting algorithms
- ✅ Calls must be silent (print = 0)
- ✅ Only prints "rrr\n" once
- ✅ Inverse operation of rr
- ✅ Time: O(n + m) - same as separate operations
- ✅ Move count: 1 - better than separate operations!

**Remember:**
1. Always use rrr when both stacks need reverse rotation
2. Silent calls to rra and rrb (print = 0)
3. Print "rrr\n" once at the end
4. Counts as single operation for scoring
5. Optimize by using rrr whenever possible
6. Inverse operation is rr
7. Better for elements in lower half of both stacks

---

## Location in Project

**File:** `srcs/operations_reverse_rotate.c`
**Header:** `includes/push_swap.h`
**Category:** Phase 4 - Stack Operations
**Type:** Combined Reverse Rotate Operation

---

## Related Functions

- [rra](rra.md) - Reverse rotate stack A (called by rrr)
- [rrb](rrb.md) - Reverse rotate stack B (called by rrr)
- [rr](rr.md) - Rotate both (inverse operation)
- [ss](ss.md) - Swap both (similar combined operation)

---

*rrr is your reverse optimization tool - use it whenever both stacks need reverse rotation to minimize your operation count!*
