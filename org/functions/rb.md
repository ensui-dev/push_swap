# rb - Rotate Stack B Up (First Becomes Last)

## Function Signature

```c
void rb(t_stack **stack_b, int print)
```

**Return type:** `void` - No return value (modifies stack B in place)
**Parameter 1:** `t_stack **stack_b` - Double pointer to stack B
**Parameter 2:** `int print` - If 1, print "rb\n"; if 0, silent operation

---

## Purpose & Use Case

`rb` (rotate B) is the **mirror operation of ra**, but operates on stack B instead of stack A. It shifts all elements of stack B **up by one position**. The first element becomes the last, and every other element moves up one spot. Think of it like a **circular rotation upward** - just like ra, but for the auxiliary stack.

### When You'll Use It

You'll call `rb` whenever you need to:
1. **Navigate stack B** - Move element to bottom or bring element to top
2. **Position elements in B** - Prepare B for optimal push back to A
3. **Cycle through B** - Access elements deeper in stack B
4. **Combined operations** - Part of rr (rotate both stacks)

### Why This Matters

**rb enables sophisticated B-stack management:**
```
Without rb:
- Can only access top of B
- Limited positioning in B
- Suboptimal sorting strategies ❌

With rb:
- Full navigation of stack B
- Can position any element at top
- Advanced sorting algorithms possible ✅
```

### Real-World Analogy

**Think of a revolving door:**
```
Before rb:
Top → [Blue] ← Current top of B
      [Red]
      [Green]
Bottom

After rb:
Top → [Red] ← Red moved up, Blue went to bottom
      [Green]
Bottom → [Blue]
```

**Identical to ra, just for stack B!**

---

## Deep Dive: How It Works

### The Rotate B Operation Visualized

**Before `rb`:**
```
Stack B:
[7] <- top (first)
[3]
[9]
[1] <- last
```

**After `rb`:**
```
Stack B:
[3] <- top (was second, now first)
[9]
[1]
[7] <- last (was first, now last)
```

**What happened:**
1. Element `7` removed from top
2. Element `3` becomes new top
3. Element `7` added to bottom
4. Net effect: entire stack rotated up

### Linked List Perspective

**Before `rb`:**
```
stack_b -> [7] -> [3] -> [9] -> [1] -> NULL
           ^                    ^
         first                 last
```

**After `rb`:**
```
stack_b -> [3] -> [9] -> [1] -> [7] -> NULL
           ^                    ^
         new first             new last (was first)
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
Node 7:  next = NULL      (changed - now last!)
Node 3:  next = Node 9    (unchanged)
Node 9:  next = Node 1    (unchanged)
Node 1:  next = Node 7    (changed - now points to ex-first!)

*stack_b = Node 3  (changed - new head!)
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
first = *stack_b;          // Current top (will become last)
last = stack_last(*stack_b); // Current last
```

**Memory state:**
```
first -> [7] -> [3] -> [9] -> [1] -> NULL
last  -> [1] -> NULL

*stack_b = first
```

**Note:** We need `stack_last()` helper function to find the last node!

### Step 3: Update Stack Head to Second Element

**Make the second element the new top:**
```c
*stack_b = first->next;
```

**After this:**
```
first -> [7] -> [3] -> [9] -> [1] -> NULL  (disconnected from head)
*stack_b -> [3] -> [9] -> [1] -> NULL  (new head!)
```

### Step 4: Detach First Node

**Set first node's next to NULL:**
```c
first->next = NULL;
```

**After this:**
```
first -> [7] -> NULL  (isolated node)
*stack_b -> [3] -> [9] -> [1] -> NULL
```

### Step 5: Attach First to End

**Connect old last to old first:**
```c
last->next = first;
```

**Final result:**
```
*stack_b -> [3] -> [9] -> [1] -> [7] -> NULL
                              ^---------^
                            last    new last
```

### Step 6: Print Operation (Optional)

**If print flag is set:**
```c
if (print)
    write(1, "rb\n", 3);
```

---

## Complete Algorithm Pseudocode

```
FUNCTION rb(stack_b, print):
    // Step 1: Validate
    IF stack_b is NULL:
        RETURN
    IF *stack_b is NULL:
        RETURN
    IF (*stack_b)->next is NULL:
        RETURN  // Only 1 element, nothing to rotate

    // Step 2: Store references
    first = *stack_b
    last = stack_last(*stack_b)  // Helper function

    // Step 3: Update head to second element
    *stack_b = first->next

    // Step 4: Detach first node
    first->next = NULL

    // Step 5: Attach first to end
    last->next = first

    // Step 6: Print if requested
    IF print == 1:
        PRINT "rb\n"

    RETURN
END FUNCTION
```

---

## Visual Execution Trace

### Example: Rotate [7, 3, 9, 1]

**Initial State:**
```
*stack_b -> [7] -> [3] -> [9] -> [1] -> NULL
```

**After Step 1 (Validation):**
```
✅ Stack exists
✅ Has more than 1 element
Continue to rotate
```

**After Step 2 (Store References):**
```
first = pointer to [7]
last  = pointer to [1]

first -> [7] -> [3] -> [9] -> [1] -> NULL
last  -> [1] -> NULL
```

**After Step 3 (*stack_b = first->next):**
```
first -> [7] -> [3] -> [9] -> [1] -> NULL
*stack_b -> [3] -> [9] -> [1] -> NULL  (new head!)
```

**After Step 4 (first->next = NULL):**
```
first -> [7] -> NULL  (isolated)
*stack_b -> [3] -> [9] -> [1] -> NULL
```

**After Step 5 (last->next = first):**
```
*stack_b -> [3] -> [9] -> [1] -> [7] -> NULL
                              └-------┘
                         Last connected to first!
```

**After Step 6 (Print):**
```
Output: "rb\n"
Final: [3, 9, 1, 7]  ✅ Rotation complete!
```

---

## Edge Cases

### Case 1: Empty Stack

```c
t_stack *stack_b = NULL;

rb(&stack_b, 1);

// Result: nothing happens, no crash
assert(stack_b == NULL);
```

### Case 2: Single Element

```c
// Before
stack_b -> [42] -> NULL

// Execute
rb(&stack_b, 1);

// After
stack_b -> [42] -> NULL  (unchanged)

// Rotation of 1 element has no effect
```

### Case 3: Two Elements

```c
// Before
stack_b -> [7] -> [3] -> NULL

// Execute
rb(&stack_b, 1);

// After
stack_b -> [3] -> [7] -> NULL

// Effectively swaps them!
// Note: sb would be more direct for this case
```

### Case 4: Three Elements

```c
// Before
stack_b -> [7] -> [3] -> [9] -> NULL

// Execute
rb(&stack_b, 1);

// After
stack_b -> [3] -> [9] -> [7] -> NULL

// Classic rotation
```

### Case 5: Many Elements

```c
// Before
stack_b -> [1] -> [2] -> [3] -> [4] -> [5] -> NULL

// Execute
rb(&stack_b, 1);

// After
stack_b -> [2] -> [3] -> [4] -> [5] -> [1] -> NULL

// First moved to last, all others shifted up
```

### Case 6: Multiple Rotations Return to Original

```c
// With N elements, N rotations return to start
stack = [7, 3, 9]

rb(&stack, 1);  // [3, 9, 7]
rb(&stack, 1);  // [9, 7, 3]
rb(&stack, 1);  // [7, 3, 9]  ← Back to original!

// 3 elements × 1 rotation each = full cycle
```

---

## Time & Space Complexity

### Time Complexity: **O(n)** - Linear Time

**Operations performed:**
1. Validation - O(1)
2. Store first - O(1)
3. **Find last - O(n)** ← This is the bottleneck!
4. Update head - O(1)
5. Rewire pointers - O(1)
6. Print - O(1)

**Total: O(n)** where n = number of elements in stack B

**Why O(n)?**
```
To find the last node, we must traverse:
[first] -> [?] -> [?] -> ... -> [last] -> NULL
    1       2      3             n

Must visit all n nodes to find last!
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
- 2 pointers (first, last)
- No allocations
- No recursion
- No arrays

**Total: O(1)** - Fixed memory usage

### Performance Note

**rb is slower than sb/pb:**
```
sb:  O(1) - only touches first 2 nodes
pb:  O(1) - only touches tops
rb:  O(n) - must traverse to find last

For large stacks, rb can be expensive!
```

---

## Relationship with Other Operations

### Mirror of ra (Rotate A)

```c
// Starting state
A: [5, 8, 2, 3]
B: [7, 3, 9, 1]

ra(&a, 1);   // A: [8, 2, 3, 5]
rb(&b, 1);   // B: [3, 9, 1, 7]

// Same operation, different stacks
```

### Inverse of rrb (Reverse Rotate B)

```c
// Starting state
B: [7, 3, 9, 1]

rb(&b, 1);   // [3, 9, 1, 7]
rrb(&b, 1);  // [7, 3, 9, 1]  ← Back to start!

// rb and rrb are inverse operations
```

### Used to Access Deep Elements in B

```c
// To bring 3rd element of B to top:
B: [7, 3, 9, 1]

rb(&b, 1);  // [3, 9, 1, 7]
rb(&b, 1);  // [9, 1, 7, 3]  ← Now 9 is on top!

// 2 rotations brought 3rd element to top
```

### Combined with rr (Rotate Both)

```c
// If both stacks need rotation
rr(&a, &b, 1);  // Rotates both, counts as 1 move

// Instead of:
ra(&a, 1);  // Move 1
rb(&b, 1);  // Move 2
```

---

## 42 Norm Considerations

### Function Signature

```c
void	rb(t_stack **stack_b, int print)
{
    t_stack	*first;
    t_stack	*last;

    // ... implementation ...
}
```

**Norm requirements:**
- ✅ Return type void
- ✅ Double pointer for head modification
- ✅ Tab between type and name
- ✅ Only 2 variables (under 5 limit)
- ✅ Should fit in ~15 lines (under 25 limit)

### Helper Function Dependency

```c
// Must use stack_last helper
last = stack_last(*stack_b);

// Can't inline the traversal - would violate norms
```

**Required helper:**
```c
t_stack *stack_last(t_stack *stack)
{
    while (stack && stack->next)
        stack = stack->next;
    return (stack);
}
```

---

## Common Mistakes

### ❌ Mistake 1: Forgetting to Set first->next to NULL

```c
// WRONG
*stack_b = first->next;
last->next = first;  // first still points to next!

// Result: Circular linked list!
// [3] -> [9] -> [1] -> [7] -> [3] -> [9] -> ...
// Infinite loop disaster!
```

**✅ Correct:**
```c
*stack_b = first->next;
first->next = NULL;  // CRITICAL: break the link!
last->next = first;
```

### ❌ Mistake 2: Wrong Order of Operations

```c
// WRONG
first->next = NULL;  // First!
*stack_b = first->next;  // Now first->next is NULL!

// Result: stack_b becomes NULL, lost entire stack!
```

**✅ Correct order:**
```c
*stack_b = first->next;  // Save reference first!
first->next = NULL;      // Then detach
```

### ❌ Mistake 3: Confusing rb with ra

```c
// WRONG - Operating on stack A instead of B
void rb(t_stack **stack_b, int print)
{
    if (!stack_a || !*stack_a || !(*stack_a)->next)  // Wrong stack!
        return;
    // ...
}
```

**✅ Must check stack_b:**
```c
if (!stack_b || !*stack_b || !(*stack_b)->next)
    return;
```

### ❌ Mistake 4: Skipping Validation

```c
// WRONG
void rb(t_stack **stack_b, int print)
{
    first = *stack_b;
    last = stack_last(*stack_b);  // SEGFAULT if NULL!
}
```

**✅ Always validate:**
```c
if (!stack_b || !*stack_b || !(*stack_b)->next)
    return;
```

### ❌ Mistake 5: Single Pointer Parameter

```c
// WRONG
void rb(t_stack *stack_b, int print)
{
    // Can't change what stack_b points to!
}
```

**✅ Use double pointer:**
```c
void rb(t_stack **stack_b, int print)
{
    *stack_b = first->next;  // Can modify the head
}
```

---

## Testing Strategy

### Test 1: Empty Stack

```c
t_stack *b = NULL;

rb(&b, 1);

assert(b == NULL);  // Unchanged
// No crash
```

### Test 2: Single Element

```c
t_stack *b = stack_new(42);

rb(&b, 1);

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
rb(&b, 1);

// Verify
assert(b->value == 3);          // Was second
assert(b->next->value == 7);    // Was first
assert(b->next->next == NULL);
```

### Test 4: Three Elements

```c
// Setup: B = [7, 3, 9]
t_stack *b = create_stack(7, 3, 9);

// Execute
rb(&b, 1);

// Verify
assert(b->value == 3);
assert(b->next->value == 9);
assert(b->next->next->value == 7);  // First is now last
assert(b->next->next->next == NULL);
```

### Test 5: Full Cycle

```c
// Setup: B = [1, 2, 3]
t_stack *b = create_stack(1, 2, 3);
int original_top = b->value;

// Execute 3 rotations (size of stack)
rb(&b, 1);
rb(&b, 1);
rb(&b, 1);

// Verify back to original
assert(b->value == original_top);
```

### Test 6: Large Stack

```c
// Setup: B = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
t_stack *b = create_large_stack(10);

// Execute
rb(&b, 1);

// Verify
assert(b->value == 2);               // Second is now first
assert(stack_last(b)->value == 1);   // First is now last
```

---

## Integration with Push_swap

### Bringing Element to Top of B

```c
// Find target element's position in B
int target_pos = find_position(stack_b, target_value);

// Rotate B until target is on top
for (int i = 0; i < target_pos; i++)
    rb(&stack_b, 1);

// Now target is at top, can push to A
pa(&stack_a, &stack_b, 1);
```

### In Turk Algorithm - Positioning B

```c
void execute_move_b(t_stack **stack_b, int moves_b)
{
    // Rotate B to position element
    if (moves_b > 0)
    {
        while (moves_b > 0)
        {
            rb(stack_b, 1);
            moves_b--;
        }
    }
}
```

### In Cost Calculation

```c
// Calculate cost to bring element to top of B
int cost_rotate_b_to_top(t_stack *stack_b, int target_pos)
{
    int size = stack_size(stack_b);

    // Can rotate up or reverse rotate down
    int cost_rb = target_pos;              // rb operations
    int cost_rrb = size - target_pos;      // rrb operations

    return (cost_rb < cost_rrb) ? cost_rb : cost_rrb;
}
```

### Optimizing with rr

```c
// If both stacks need forward rotation
if (cost_a > 0 && cost_b > 0)
{
    // Do combined rotations first
    while (cost_a > 0 && cost_b > 0)
    {
        rr(&stack_a, &stack_b, 1);  // Uses ra and rb
        cost_a--;
        cost_b--;
    }

    // Do remaining individual rotations
    while (cost_b > 0)
    {
        rb(&stack_b, 1);
        cost_b--;
    }
}
```

---

## Real-World Usage Example

### Sorting with B as Auxiliary Stack

```c
// Goal: Push elements to B, then bring them back in order

// Initial
A: [5, 8, 2, 3, 1]
B: []

// Push some to B
pb(a, b, 1);  // A: [8, 2, 3, 1], B: [5]
pb(a, b, 1);  // A: [2, 3, 1], B: [8, 5]
pb(a, b, 1);  // A: [3, 1], B: [2, 8, 5]

// Now B: [2, 8, 5]
// Want to get 5 to top for optimal push back

rb(b, 1);  // B: [8, 5, 2]
rb(b, 1);  // B: [5, 2, 8]  ← 5 is now on top!

// Now can push 5 back to A optimally
pa(a, b, 1);  // A: [5, 3, 1], B: [2, 8]
```

---

## Performance Notes

### When to Use rb

**Use rb when:**
1. Need to access element in upper half of stack B
2. Combined rr operation is beneficial
3. Target element is closer to top than bottom

**Avoid rb when:**
1. Element is in lower half (use rrb instead - fewer operations)
2. Only 2 elements (use sb - it's O(1))
3. Stack B is very large and element is deep

### Cost Optimization

```c
// Decision: rb vs rrb
int size = stack_size(stack_b);
int target_pos = find_position(stack_b, target);

if (target_pos <= size / 2)
    use rb  // Closer to top
else
    use rrb  // Closer to bottom (reverse rotate)
```

### Examples

```
Stack B size: 10
Target at position 3:
- rb: 3 moves
- rrb: 7 moves
→ Use rb!

Target at position 8:
- rb: 8 moves
- rrb: 2 moves
→ Use rrb!
```

---

## Summary

**What rb Does:**
- Rotates stack B upward
- First element moves to last position
- All others shift up by one
- O(n) time complexity (must find last node)

**Key Points:**
- ✅ Mirror of ra, operates on stack B
- ✅ Critical for navigating stack B
- ✅ Inverse of rrb
- ✅ Must set first->next to NULL to avoid cycles
- ✅ Order of operations is crucial
- ✅ More expensive than swap/push (O(n) vs O(1))

**Remember:**
1. Always validate stack has 2+ elements
2. Use stack_last() to find last node
3. Rewire in correct order: head, detach, attach
4. Consider rrb if element is in lower half
5. N rotations on N-element stack returns to start
6. Combine with rr when both stacks need rotation

---

## Location in Project

**File:** `srcs/operations_rotate.c`
**Header:** `includes/push_swap.h`
**Category:** Phase 4 - Stack Operations
**Type:** Rotate Operation

---

## Related Functions

- [ra](ra.md) - Rotate stack A (mirror function)
- [rr](rr.md) - Rotate both A and B simultaneously
- [rrb](rrb.md) - Reverse rotate B (inverse operation)
- [stack_last](stack_last.md) - Find last node (required helper)
- [stack_size](stack_size.md) - Count elements (for cost calculation)

---

*rb is your key to stack B navigation - use it wisely to optimize your sorting algorithm!*
