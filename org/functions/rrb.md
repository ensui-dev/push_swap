# rrb - Reverse Rotate Stack B Down (Last Becomes First)

## Function Signature

```c
void rrb(t_stack **stack_b, int print)
```

**Return type:** `void` - No return value (modifies stack B in place)
**Parameter 1:** `t_stack **stack_b` - Double pointer to stack B
**Parameter 2:** `int print` - If 1, print "rrb\n"; if 0, silent operation

---

## Purpose & Use Case

`rrb` (reverse rotate B) is the **mirror operation of rra**, but operates on stack B instead of stack A. It shifts all elements of stack B **down by one position**. The last element becomes the first, and every other element moves down one spot. This is the **inverse operation of rb** and is essential for efficient navigation of the auxiliary stack.

### When You'll Use It

You'll call `rrb` whenever you need to:
1. **Move last element of B to top** - Bring bottom element up
2. **Access lower elements of B** - Faster than rb when element is near bottom
3. **Undo rb** - Reverse the effect of rb
4. **Optimize cost in B** - When target is in lower half of stack B

### Why This Matters

**rrb enables efficient B-stack management:**
```
Without rrb:
- Only have rb (must rotate entire stack)
- Accessing lower half of B is expensive ❌
- Suboptimal operation count

With rrb:
- Can navigate B forward or backward
- Accessing lower half of B is cheap ✅
- Minimized operation count
```

### Real-World Analogy

**Think of a conveyor belt moving backwards:**
```
Before rrb:
Top → [Blue]
      [Red]
      [Green]
Bottom → [Yellow] ← Take this one!

After rrb:
Top → [Yellow] ← Yellow came from bottom
      [Blue]
      [Red]
Bottom → [Green]
```

**Same as rra, just for stack B!**

---

## Deep Dive: How It Works

### The Reverse Rotate B Operation Visualized

**Before `rrb`:**
```
Stack B:
[7] <- top (first)
[3]
[9]
[1] <- last
```

**After `rrb`:**
```
Stack B:
[1] <- top (was last, now first)
[7]
[3]
[9] <- last (was second-to-last)
```

**What happened:**
1. Element `1` removed from bottom
2. Element `1` added to top
3. All others shift down
4. Net effect: entire stack rotated down

### Difference from rb

```
rb (rotate up):
[7, 3, 9, 1] → [3, 9, 1, 7]
First becomes last

rrb (rotate down):
[7, 3, 9, 1] → [1, 7, 3, 9]
Last becomes first
```

**They are inverse operations!**

### Linked List Perspective

**Before `rrb`:**
```
stack_b -> [7] -> [3] -> [9] -> [1] -> NULL
           ^                    ^
         first                 last
```

**After `rrb`:**
```
stack_b -> [1] -> [7] -> [3] -> [9] -> NULL
           ^                    ^
      new first               new last
      (was last)         (was second-to-last)
```

### Memory State Transition

**Before:**
```
Node 7:  next = Node 3
Node 3:  next = Node 9
Node 9:  next = Node 1
Node 1:  next = NULL

*stack_b = Node 7
```

**After:**
```
Node 7:  next = Node 3    (unchanged)
Node 3:  next = Node 9    (unchanged)
Node 9:  next = NULL      (changed - now last!)
Node 1:  next = Node 7    (changed - now points to old first!)

*stack_b = Node 1  (changed - new head!)
```

---

## Step-by-Step Implementation

### Step 1: Validate Stack Has 2+ Elements

**Check if rotation is possible:**
```c
if (!stack_b || !*stack_b || !(*stack_b)->next)
    return;
```

**Why this check matters:**
- NULL stack: nothing to rotate
- 1 element: rotating doesn't change anything
- 2+ elements: rotation has meaningful effect

### Step 2: Store References to Key Nodes

**Save pointers to nodes we'll manipulate:**
```c
first = *stack_b;               // Current top
last = stack_last(*stack_b);    // Current last (will become first)
second_to_last = stack_second_to_last(*stack_b);  // Will become new last
```

**Memory state:**
```
first -> [7] -> [3] -> [9] -> [1] -> NULL
                       ^      ^
              second_to_last  last

*stack_b = first
```

**Note:** We need TWO helper functions:
- `stack_last()` to find last node
- `stack_second_to_last()` to find second-to-last node

### Step 3: Detach Last Node

**Set second-to-last's next to NULL:**
```c
second_to_last->next = NULL;
```

**After this:**
```
*stack_b -> [7] -> [3] -> [9] -> NULL  (shortened)
last -> [1] -> NULL  (isolated)
```

### Step 4: Attach Last to Front

**Make last point to current first:**
```c
last->next = first;
```

**After this:**
```
last -> [1] -> [7] -> [3] -> [9] -> NULL
```

### Step 5: Update Stack Head

**Make stack point to last (new first):**
```c
*stack_b = last;
```

**Final result:**
```
*stack_b -> [1] -> [7] -> [3] -> [9] -> NULL
```

### Step 6: Print Operation (Optional)

**If print flag is set:**
```c
if (print)
    ft_printf("rrb\n");
```

---

## Complete Algorithm Pseudocode

```
FUNCTION rrb(stack_b, print):
    // Step 1: Validate
    IF stack_b is NULL:
        RETURN
    IF *stack_b is NULL:
        RETURN
    IF (*stack_b)->next is NULL:
        RETURN  // Only 1 element, nothing to rotate

    // Step 2: Store references
    first = *stack_b
    last = stack_last(*stack_b)
    second_to_last = stack_second_to_last(*stack_b)

    // Step 3: Detach last node
    second_to_last->next = NULL

    // Step 4: Attach last to front
    last->next = first

    // Step 5: Update head to last
    *stack_b = last

    // Step 6: Print if requested
    IF print == 1:
        PRINT "rrb\n"

    RETURN
END FUNCTION
```

### Alternative Implementation (Single Traversal)

```
FUNCTION rrb_optimized(stack_b, print):
    // Validate
    IF !stack_b OR !*stack_b OR !(*stack_b)->next:
        RETURN

    // Traverse to find last and second-to-last in one pass
    current = *stack_b
    WHILE current->next->next != NULL:
        current = current->next
    // Now current is second-to-last

    last = current->next
    current->next = NULL        // Detach
    last->next = *stack_b       // Attach to front
    *stack_b = last             // Update head

    IF print:
        PRINT "rrb\n"
END FUNCTION
```

---

## Visual Execution Trace

### Example: Reverse Rotate [7, 3, 9, 1]

**Initial State:**
```
*stack_b -> [7] -> [3] -> [9] -> [1] -> NULL
```

**After Step 1 (Validation):**
```
✅ Stack exists
✅ Has more than 1 element
Continue to reverse rotate
```

**After Step 2 (Store References):**
```
first = pointer to [7]
last  = pointer to [1]
second_to_last = pointer to [9]

first -> [7] -> [3] -> [9] -> [1] -> NULL
                       ^      ^
              second_to_last  last
```

**After Step 3 (Detach last):**
```
*stack_b -> [7] -> [3] -> [9] -> NULL
last -> [1] -> NULL  (isolated)
```

**After Step 4 (Attach to front):**
```
last -> [1] -> [7] -> [3] -> [9] -> NULL
```

**After Step 5 (Update head):**
```
*stack_b -> [1] -> [7] -> [3] -> [9] -> NULL
```

**After Step 6 (Print):**
```
Output: "rrb\n"
Final: [1, 7, 3, 9]  ✅ Reverse rotation complete!
```

---

## Edge Cases

### Case 1: Empty Stack

```c
t_stack *stack_b = NULL;

rrb(&stack_b, 1);

// Result: nothing happens, no crash
assert(stack_b == NULL);
```

### Case 2: Single Element

```c
// Before
stack_b -> [42] -> NULL

// Execute
rrb(&stack_b, 1);

// After
stack_b -> [42] -> NULL  (unchanged)

// Reverse rotation of 1 element has no effect
```

### Case 3: Two Elements

```c
// Before
stack_b -> [7] -> [3] -> NULL

// Execute
rrb(&stack_b, 1);

// After
stack_b -> [3] -> [7] -> NULL

// Effectively swaps them!
// Same result as rb or sb for 2 elements
```

### Case 4: Three Elements

```c
// Before
stack_b -> [7] -> [3] -> [9] -> NULL

// Execute
rrb(&stack_b, 1);

// After
stack_b -> [9] -> [7] -> [3] -> NULL

// Last element moved to top
```

### Case 5: Many Elements

```c
// Before
stack_b -> [1] -> [2] -> [3] -> [4] -> [5] -> NULL

// Execute
rrb(&stack_b, 1);

// After
stack_b -> [5] -> [1] -> [2] -> [3] -> [4] -> NULL

// Last moved to first, all others shifted down
```

### Case 6: Inverse of rb

```c
// Starting state
stack = [7, 3, 9, 1]

rb(&stack, 1);   // [3, 9, 1, 7]
rrb(&stack, 1);  // [7, 3, 9, 1]  ← Back to original!

// rb and rrb cancel each other out
```

---

## Time & Space Complexity

### Time Complexity: **O(n)** - Linear Time

**Operations performed:**
1. Validation - O(1)
2. Store first - O(1)
3. **Find last - O(n)** ← Bottleneck 1
4. **Find second-to-last - O(n)** ← Bottleneck 2
5. Detach last - O(1)
6. Attach to front - O(1)
7. Update head - O(1)
8. Print - O(1)

**Total: O(n)** where n = number of elements in stack B

**Why O(n)?**
```
Must traverse to find last node:
[first] -> [?] -> [?] -> ... -> [second-to-last] -> [last] -> NULL
    1       2      3             n-1                  n

Need to visit up to n nodes!
```

**Optimization note:**
```
Can find both last and second-to-last in one pass!
Still O(n), but only one traversal instead of two.
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
- 3 pointers (first, last, second_to_last)
- No allocations
- No recursion
- No arrays

**Total: O(1)** - Fixed memory usage

### Performance Comparison

```
Operation    Time        When to use
sb:          O(1)        2 elements need swap
rb:          O(n)        Element in upper half of B
rrb:         O(n)        Element in lower half of B ← Often better!
```

---

## Relationship with Other Operations

### Mirror of rra (Reverse Rotate A)

```c
// Starting state
A: [5, 8, 2, 3]
B: [7, 3, 9, 1]

rra(&a, 1);  // A: [3, 5, 8, 2]
rrb(&b, 1);  // B: [1, 7, 3, 9]

// Same operation, different stacks
```

### Inverse of rb (Rotate B)

```c
// Starting state
B: [7, 3, 9, 1]

rb(&b, 1);   // [3, 9, 1, 7]
rrb(&b, 1);  // [7, 3, 9, 1]  ← Back to start!

// They undo each other!
```

### Used to Access Lower Half Elements in B

```c
// To bring element near bottom of B to top
B: [7, 3, 9, 1, 5]  (5 is at position 4, last)

// Option 1: Use rb (4 operations)
rb(&b, 1);  // [3, 9, 1, 5, 7]
rb(&b, 1);  // [9, 1, 5, 7, 3]
rb(&b, 1);  // [1, 5, 7, 3, 9]
rb(&b, 1);  // [5, 7, 3, 9, 1]  ← 4 moves

// Option 2: Use rrb (1 operation!)
rrb(&b, 1);  // [5, 7, 3, 9, 1]  ← Only 1 move! ✅

// rrb is much better for lower half!
```

### Combined with rrr (Reverse Rotate Both)

```c
// If both stacks need reverse rotation
rrr(&a, &b, 1);  // Reverse rotates both, counts as 1 move

// Instead of:
rra(&a, 1);  // Move 1
rrb(&b, 1);  // Move 2
```

---

## 42 Norm Considerations

### Function Signature

```c
void	rrb(t_stack **stack_b, int print)
{
    t_stack	*first;
    t_stack	*last;
    t_stack	*second_to_last;

    // ... implementation ...
}
```

**Norm requirements:**
- ✅ Return type void
- ✅ Double pointer for head modification
- ✅ Tab between type and name
- ✅ Only 3 variables (under 5 limit)
- ✅ Should fit in ~20 lines (under 25 limit)

### Helper Function Dependencies

```c
// Must use helper functions
last = stack_last(*stack_b);
second_to_last = stack_second_to_last(*stack_b);

// Can't inline - would violate norms
```

**Required helpers:**
```c
t_stack *stack_last(t_stack *stack)
{
    while (stack && stack->next)
        stack = stack->next;
    return (stack);
}

t_stack *stack_second_to_last(t_stack *stack)
{
    if (!stack || !stack->next)
        return (NULL);
    while (stack->next->next)
        stack = stack->next;
    return (stack);
}
```

---

## Common Mistakes

### ❌ Mistake 1: Not Detaching Second-to-Last

```c
// WRONG
last->next = *stack_b;  // Attach to front first
*stack_b = last;

// Result: Circular list!
// [1] -> [7] -> [3] -> [9] -> [1] -> ...
// Infinite loop!
```

**✅ Correct:**
```c
second_to_last->next = NULL;  // CRITICAL: break the link first!
last->next = *stack_b;
*stack_b = last;
```

### ❌ Mistake 2: Confusing rrb with rra

```c
// WRONG - Operating on stack A instead of B
void rrb(t_stack **stack_b, int print)
{
    if (!stack_a || !*stack_a)  // Wrong stack!
        return;
    // ...
}
```

**✅ Must check stack_b:**
```c
if (!stack_b || !*stack_b || !(*stack_b)->next)
    return;
```

### ❌ Mistake 3: Wrong Order of Operations

```c
// WRONG
*stack_b = last;              // Change head first
last->next = *stack_b;        // Now points to itself!

// Result: Circular reference to self
```

**✅ Correct order:**
```c
second_to_last->next = NULL;  // 1. Detach
last->next = *stack_b;        // 2. Attach to front
*stack_b = last;              // 3. Update head
```

### ❌ Mistake 4: Not Finding Second-to-Last

```c
// WRONG - Just finding last
last = stack_last(*stack_b);
last->next = *stack_b;   // Who detaches last from chain?

// Result: Chain still connected, creating cycle
```

**✅ Must find second-to-last:**
```c
second_to_last = stack_second_to_last(*stack_b);
second_to_last->next = NULL;  // This detaches last!
```

### ❌ Mistake 5: Confusing rb and rrb Logic

```c
// WRONG - Using rb logic for rrb
first->next = NULL;  // This is rb logic!
last->next = first;

// Result: Wrong operation, breaks the list
```

**✅ rrb moves last to first:**
```c
second_to_last->next = NULL;  // Detach last
last->next = first;            // Last points to first
*stack_b = last;               // Last becomes new head
```

### ❌ Mistake 6: Single Pointer Parameter

```c
// WRONG
void rrb(t_stack *stack_b, int print)
{
    // Can't change what stack_b points to!
}
```

**✅ Use double pointer:**
```c
void rrb(t_stack **stack_b, int print)
{
    *stack_b = last;  // Can modify the head
}
```

---

## Testing Strategy

### Test 1: Empty Stack

```c
t_stack *b = NULL;

rrb(&b, 1);

assert(b == NULL);  // Unchanged
// No crash
```

### Test 2: Single Element

```c
t_stack *b = stack_new(42);

rrb(&b, 1);

assert(b->value == 42);
assert(b->next == NULL);
// Unchanged
```

### Test 3: Two Elements

```c
// Setup: B = [7, 3]
t_stack *b = stack_new(3);
stack_add_front(&b, stack_new(7));

// Execute
rrb(&b, 1);

// Verify
assert(b->value == 3);          // Was last
assert(b->next->value == 7);    // Was first
assert(b->next->next == NULL);
```

### Test 4: Three Elements

```c
// Setup: B = [7, 3, 9]
t_stack *b = create_stack(7, 3, 9);

// Execute
rrb(&b, 1);

// Verify
assert(b->value == 9);          // Was last
assert(b->next->value == 7);    // Was first
assert(b->next->next->value == 3);
assert(b->next->next->next == NULL);
```

### Test 5: Inverse of rb

```c
// Setup: B = [7, 3, 9, 1]
t_stack *b = create_stack(7, 3, 9, 1);
int original_top = b->value;

// Execute: rb then rrb
rb(&b, 1);   // [3, 9, 1, 7]
rrb(&b, 1);  // [7, 3, 9, 1]

// Verify: Back to original
assert(b->value == original_top);
```

### Test 6: Large Stack

```c
// Setup: B = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
t_stack *b = create_large_stack(10);

// Execute
rrb(&b, 1);

// Verify
assert(b->value == 10);              // Last is now first
assert(b->next->value == 1);         // First is now second
```

---

## Integration with Push_swap

### Bringing Lower Element of B to Top

```c
// Find target element's position in B
int target_pos = find_position(stack_b, target_value);
int size = stack_size(stack_b);

// Optimize: Use rrb if in lower half
if (target_pos > size / 2)
{
    int rrb_count = size - target_pos;
    for (int i = 0; i < rrb_count; i++)
        rrb(&stack_b, 1);
}
else
{
    for (int i = 0; i < target_pos; i++)
        rb(&stack_b, 1);
}
```

### In Turk Algorithm - Optimal B Positioning

```c
void execute_reverse_moves_b(t_stack **stack_b, int moves_b)
{
    // Negative moves_b indicates rrb should be used
    if (moves_b < 0)
    {
        moves_b = -moves_b;  // Make positive
        while (moves_b > 0)
        {
            rrb(stack_b, 1);
            moves_b--;
        }
    }
}
```

### Cost Calculation with rrb

```c
// Calculate cheapest way to bring element to top of B
int calculate_rotate_cost_b(t_stack *stack_b, int position)
{
    int size = stack_size(stack_b);

    // Cost using rb (forward)
    int cost_rb = position;

    // Cost using rrb (backward)
    int cost_rrb = size - position;

    // Return cheaper option
    return (cost_rb < cost_rrb) ? cost_rb : -cost_rrb;
    // Negative indicates rrb should be used
}
```

### Optimizing with rrr

```c
// If both stacks need reverse rotation
if (cost_a < 0 && cost_b < 0)
{
    // Do combined reverse rotations first
    while (cost_a < 0 && cost_b < 0)
    {
        rrr(&stack_a, &stack_b, 1);  // Uses rra and rrb
        cost_a++;
        cost_b++;
    }

    // Do remaining individual reverse rotations
    while (cost_b < 0)
    {
        rrb(&stack_b, 1);
        cost_b++;
    }
}
```

---

## Real-World Usage Example

### Sorting with B - Finding Element Efficiently

```c
// Goal: Push element from B to A, but element is at bottom of B

// Initial
A: [5, 8, 2]
B: [7, 3, 9, 1]  (want to push 1)

Position of 1 in B: index 3 (last)
Size of B: 4

// Strategy decision:
// rb cost: 3 operations
// rrb cost: 1 operation ← Better!

// Using rrb:
rrb(b, 1);  // B: [1, 7, 3, 9]  ← 1 is now on top!

// Now push to A
pa(a, b, 1);  // A: [1, 5, 8, 2], B: [7, 3, 9]

// Only 2 moves total instead of 4! ✅
```

---

## Performance Notes

### When to Use rrb

**Use rrb when:**
1. Element is in lower half of stack B (position > size/2)
2. Need to undo rb operation
3. Want to move last element of B to top
4. Combined rrr operation is beneficial

**Avoid rrb when:**
1. Element is in upper half of B (use rb instead)
2. Only 2 elements (use sb - it's O(1))
3. Stack B is small and position is at top

### Cost Decision

```c
// Automatic decision making for stack B
int size = stack_size(stack_b);
int target_pos = find_position(stack_b, target);

if (target_pos <= size / 2)
    use rb  // Element closer to top
else
    use rrb  // Element closer to bottom ← Often better!
```

### Examples

```
Stack B size: 10
Target at position 2:
- rb: 2 moves
- rrb: 8 moves
→ Use rb!

Target at position 8:
- rb: 8 moves
- rrb: 2 moves
→ Use rrb! ✅

Target at position 5:
- rb: 5 moves
- rrb: 5 moves
→ Either works, prefer rb (slightly simpler)
```

---

## Summary

**What rrb Does:**
- Reverse rotates stack B downward
- Last element moves to first position
- All others shift down by one
- O(n) time complexity (must find last and second-to-last)
- Inverse operation of rb

**Key Points:**
- ✅ Mirror of rra, operates on stack B
- ✅ Critical for efficient B-stack navigation
- ✅ Better than rb for lower half elements
- ✅ Inverse of rb (they cancel each other)
- ✅ Must detach second-to-last's next to NULL
- ✅ Order of operations is crucial

**Remember:**
1. Always validate stack has 2+ elements
2. Find both last and second-to-last nodes
3. Detach last by setting second-to-last->next = NULL
4. Attach last to front: last->next = first
5. Update head: *stack_b = last
6. Use rrb when element is in lower half of B
7. Combine with rrr when both stacks need reverse rotation

---

## Location in Project

**File:** `srcs/operations_reverse_rotate.c`
**Header:** `includes/push_swap.h`
**Category:** Phase 4 - Stack Operations
**Type:** Reverse Rotate Operation

---

## Related Functions

- [rb](rb.md) - Rotate stack B (inverse operation)
- [rra](rra.md) - Reverse rotate stack A (mirror function)
- [rrr](rrr.md) - Reverse rotate both A and B simultaneously
- [stack_last](stack_last.md) - Find last node (required helper)
- [stack_second_to_last](stack_utils.md) - Find second-to-last (required helper)
- [stack_size](stack_size.md) - Count elements (for cost calculation)

---

*rrb is your backward navigation tool for stack B - use it to efficiently access the lower half of your auxiliary stack!*
