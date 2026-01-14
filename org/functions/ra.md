# ra - Rotate Stack A Up (First Becomes Last)

## Function Signature

```c
void ra(t_stack **stack_a, int print)
```

**Return type:** `void` - No return value (modifies stack A in place)
**Parameter 1:** `t_stack **stack_a` - Double pointer to stack A
**Parameter 2:** `int print` - If 1, print "ra\n"; if 0, silent operation

---

## Purpose & Use Case

`ra` (rotate A) shifts all elements of stack A **up by one position**. The first element becomes the last, and every other element moves up one spot. Think of it like a **circular rotation upward** or moving the top card to the bottom of the deck.

### When You'll Use It

You'll call `ra` whenever you need to:
1. **Move element to bottom** - Push current top element to the end
2. **Bring element to top** - Rotate until desired element reaches top
3. **Cycle through stack** - Access elements deeper in the stack
4. **Positioning** - Prepare stack for optimal operations

### Why This Matters

**ra is essential for stack navigation:**
```
Without ra:
- Can only access top element
- Can't reposition elements
- Limited sorting strategies ❌

With ra:
- Can access any element (eventually)
- Full stack repositioning
- Complex sorting algorithms possible ✅
```

### Real-World Analogy

**Think of a stack of plates:**
```
Before ra:
Top → [Blue] ← You can only see/touch this one
      [Red]
      [Green]
Bottom

After ra:
Top → [Red] ← Red moved up, Blue went to bottom
      [Green]
Bottom → [Blue]
```

**Like a revolving door** - everything shifts up, top wraps to bottom!

---

## Deep Dive: How It Works

### The Rotate A Operation Visualized

**Before `ra`:**
```
Stack A:
[5] <- top (first)
[8]
[2]
[3] <- last
```

**After `ra`:**
```
Stack A:
[8] <- top (was second, now first)
[2]
[3]
[5] <- last (was first, now last)
```

**What happened:**
1. Element `5` removed from top
2. Element `8` becomes new top
3. Element `5` added to bottom
4. Net effect: entire stack rotated up

### Linked List Perspective

**Before `ra`:**
```
stack_a -> [5] -> [8] -> [2] -> [3] -> NULL
           ^                    ^
         first                 last
```

**After `ra`:**
```
stack_a -> [8] -> [2] -> [3] -> [5] -> NULL
           ^                    ^
         new first             new last (was first)
```

### Memory State Transition

**Before:**
```
Node 5:  next = Node 8
Node 8:  next = Node 2
Node 2:  next = Node 3
Node 3:  next = NULL

*stack_a = Node 5
```

**After:**
```
Node 5:  next = NULL      (changed - now last!)
Node 8:  next = Node 2    (unchanged)
Node 2:  next = Node 3    (unchanged)
Node 3:  next = Node 5    (changed - now points to ex-first!)

*stack_a = Node 8  (changed - new head!)
```

---

## Step-by-Step Implementation

### Step 1: Validate Stack Has 2+ Elements

**Check if rotation is possible:**
```c
if (!stack_a || !*stack_a || !(*stack_a)->next)
    return;
```

**Why this check matters:**
- NULL stack: nothing to rotate
- 1 element: rotating doesn't change anything
- 2+ elements: rotation has meaningful effect

### Step 2: Store References to Key Nodes

**Save pointers to nodes we'll manipulate:**
```c
first = *stack_a;          // Current top (will become last)
last = stack_last(*stack_a); // Current last
```

**Memory state:**
```
first -> [5] -> [8] -> [2] -> [3] -> NULL
last  -> [3] -> NULL

*stack_a = first
```

**Note:** We need `stack_last()` helper function to find the last node!

### Step 3: Update Stack Head to Second Element

**Make the second element the new top:**
```c
*stack_a = first->next;
```

**After this:**
```
first -> [5] -> [8] -> [2] -> [3] -> NULL  (disconnected from head)
*stack_a -> [8] -> [2] -> [3] -> NULL  (new head!)
```

### Step 4: Detach First Node

**Set first node's next to NULL:**
```c
first->next = NULL;
```

**After this:**
```
first -> [5] -> NULL  (isolated node)
*stack_a -> [8] -> [2] -> [3] -> NULL
```

### Step 5: Attach First to End

**Connect old last to old first:**
```c
last->next = first;
```

**Final result:**
```
*stack_a -> [8] -> [2] -> [3] -> [5] -> NULL
                              ^---------^
                            last    new last
```

### Step 6: Print Operation (Optional)

**If print flag is set:**
```c
if (print)
    write(1, "ra\n", 3);
```

---

## Complete Algorithm Pseudocode

```
FUNCTION ra(stack_a, print):
    // Step 1: Validate
    IF stack_a is NULL:
        RETURN
    IF *stack_a is NULL:
        RETURN
    IF (*stack_a)->next is NULL:
        RETURN  // Only 1 element, nothing to rotate

    // Step 2: Store references
    first = *stack_a
    last = stack_last(*stack_a)  // Helper function

    // Step 3: Update head to second element
    *stack_a = first->next

    // Step 4: Detach first node
    first->next = NULL

    // Step 5: Attach first to end
    last->next = first

    // Step 6: Print if requested
    IF print == 1:
        PRINT "ra\n"

    RETURN
END FUNCTION
```

---

## Visual Execution Trace

### Example: Rotate [5, 8, 2, 3]

**Initial State:**
```
*stack_a -> [5] -> [8] -> [2] -> [3] -> NULL
```

**After Step 1 (Validation):**
```
✅ Stack exists
✅ Has more than 1 element
Continue to rotate
```

**After Step 2 (Store References):**
```
first = pointer to [5]
last  = pointer to [3]

first -> [5] -> [8] -> [2] -> [3] -> NULL
last  -> [3] -> NULL
```

**After Step 3 (*stack_a = first->next):**
```
first -> [5] -> [8] -> [2] -> [3] -> NULL
*stack_a -> [8] -> [2] -> [3] -> NULL  (new head!)
```

**After Step 4 (first->next = NULL):**
```
first -> [5] -> NULL  (isolated)
*stack_a -> [8] -> [2] -> [3] -> NULL
```

**After Step 5 (last->next = first):**
```
*stack_a -> [8] -> [2] -> [3] -> [5] -> NULL
                              └-------┘
                         Last connected to first!
```

**After Step 6 (Print):**
```
Output: "ra\n"
Final: [8, 2, 3, 5]  ✅ Rotation complete!
```

---

## Edge Cases

### Case 1: Empty Stack
```c
t_stack *stack_a = NULL;

ra(&stack_a, 1);

// Result: nothing happens, no crash
assert(stack_a == NULL);
```

### Case 2: Single Element
```c
// Before
stack_a -> [42] -> NULL

// Execute
ra(&stack_a, 1);

// After
stack_a -> [42] -> NULL  (unchanged)

// Rotation of 1 element has no effect
```

### Case 3: Two Elements
```c
// Before
stack_a -> [5] -> [8] -> NULL

// Execute
ra(&stack_a, 1);

// After
stack_a -> [8] -> [5] -> NULL

// Effectively swaps them!
// Note: sa would be more direct for this case
```

### Case 4: Three Elements
```c
// Before
stack_a -> [5] -> [8] -> [2] -> NULL

// Execute
ra(&stack_a, 1);

// After
stack_a -> [8] -> [2] -> [5] -> NULL

// Classic rotation
```

### Case 5: Many Elements
```c
// Before
stack_a -> [1] -> [2] -> [3] -> [4] -> [5] -> NULL

// Execute
ra(&stack_a, 1);

// After
stack_a -> [2] -> [3] -> [4] -> [5] -> [1] -> NULL

// First moved to last, all others shifted up
```

### Case 6: Multiple Rotations Return to Original
```c
// With N elements, N rotations return to start
stack = [5, 8, 2]

ra(&stack, 1);  // [8, 2, 5]
ra(&stack, 1);  // [2, 5, 8]
ra(&stack, 1);  // [5, 8, 2]  ← Back to original!

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

**Total: O(n)** where n = number of elements

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

**ra is slower than sa/pa/pb:**
```
sa:  O(1) - only touches first 2 nodes
pa:  O(1) - only touches tops
ra:  O(n) - must traverse to find last

For large stacks, ra can be expensive!
```

---

## Relationship with Other Operations

### Inverse of rra (Reverse Rotate A)
```c
// Starting state
A: [5, 8, 2, 3]

ra(&a, 1);   // [8, 2, 3, 5]
rra(&a, 1);  // [5, 8, 2, 3]  ← Back to start!

// ra and rra are inverse operations
```

### Used to Access Deep Elements
```c
// To bring 3rd element to top:
A: [5, 8, 2, 3]

ra(&a, 1);  // [8, 2, 3, 5]
ra(&a, 1);  // [2, 3, 5, 8]  ← Now 2 is on top!

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
void	ra(t_stack **stack_a, int print)
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
last = stack_last(*stack_a);

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
*stack_a = first->next;
last->next = first;  // first still points to next!

// Result: Circular linked list!
// [8] -> [2] -> [3] -> [5] -> [8] -> [2] -> ...
// Infinite loop disaster!
```

**✅ Correct:**
```c
*stack_a = first->next;
first->next = NULL;  // CRITICAL: break the link!
last->next = first;
```

### ❌ Mistake 2: Wrong Order of Operations
```c
// WRONG
first->next = NULL;  // First!
*stack_a = first->next;  // Now first->next is NULL!

// Result: stack_a becomes NULL, lost entire stack!
```

**✅ Correct order:**
```c
*stack_a = first->next;  // Save reference first!
first->next = NULL;      // Then detach
```

### ❌ Mistake 3: Not Finding Last
```c
// WRONG - Assuming there's a direct 'last' pointer
last = stack_a->last;  // This field doesn't exist!
```

**✅ Must traverse:**
```c
last = stack_last(*stack_a);  // Use helper function
```

### ❌ Mistake 4: Skipping Validation
```c
// WRONG
void ra(t_stack **stack_a, int print)
{
    first = *stack_a;
    last = stack_last(*stack_a);  // SEGFAULT if NULL!
}
```

**✅ Always validate:**
```c
if (!stack_a || !*stack_a || !(*stack_a)->next)
    return;
```

### ❌ Mistake 5: Single Pointer Parameter
```c
// WRONG
void ra(t_stack *stack_a, int print)
{
    // Can't change what stack_a points to!
}
```

**✅ Use double pointer:**
```c
void ra(t_stack **stack_a, int print)
{
    *stack_a = first->next;  // Can modify the head
}
```

---

## Testing Strategy

### Test 1: Empty Stack
```c
t_stack *a = NULL;

ra(&a, 1);

assert(a == NULL);  // Unchanged
// No crash
```

### Test 2: Single Element
```c
t_stack *a = stack_new(42);

ra(&a, 1);

assert(a->value == 42);
assert(a->next == NULL);
// Unchanged
```

### Test 3: Two Elements
```c
// Setup: A = [5, 8]
t_stack *a = stack_new(8);
stack_add_front(&a, stack_new(5));

// Execute
ra(&a, 1);

// Verify
assert(a->value == 8);          // Was second
assert(a->next->value == 5);    // Was first
assert(a->next->next == NULL);
```

### Test 4: Three Elements
```c
// Setup: A = [5, 8, 2]
t_stack *a = create_stack(5, 8, 2);

// Execute
ra(&a, 1);

// Verify
assert(a->value == 8);
assert(a->next->value == 2);
assert(a->next->next->value == 5);  // First is now last
assert(a->next->next->next == NULL);
```

### Test 5: Full Cycle
```c
// Setup: A = [1, 2, 3]
t_stack *a = create_stack(1, 2, 3);
int original_top = a->value;

// Execute 3 rotations (size of stack)
ra(&a, 1);
ra(&a, 1);
ra(&a, 1);

// Verify back to original
assert(a->value == original_top);
```

### Test 6: Large Stack
```c
// Setup: A = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
t_stack *a = create_large_stack(10);

// Execute
ra(&a, 1);

// Verify
assert(a->value == 2);               // Second is now first
assert(stack_last(a)->value == 1);   // First is now last
```

---

## Integration with Push_swap

### Bringing Element to Top
```c
// Find target element's position
int target_pos = find_position(stack_a, target_value);

// Rotate until target is on top
for (int i = 0; i < target_pos; i++)
    ra(&stack_a, 1);

// Now target is at top, can operate on it
```

### In Final Rotate
```c
void final_rotate(t_stack **stack_a)
{
    // Rotate until smallest is on top
    int min_pos = find_min_index(*stack_a);

    while ((*stack_a)->index != min_pos)
        ra(stack_a, 1);  // Keep rotating
}
```

### In Sort Three
```c
void sort_three(t_stack **stack_a)
{
    int top = (*stack_a)->value;
    int mid = (*stack_a)->next->value;
    int bot = (*stack_a)->next->next->value;

    if (top > mid && top > bot)
        ra(stack_a, 1);  // Largest on top, rotate it down
    // ... other cases ...
}
```

### Cost Calculation
```c
// Calculate cost to bring element to top
int cost_rotate_to_top(t_stack *stack, int target_pos)
{
    int size = stack_size(stack);

    // Can rotate up or reverse rotate down
    int cost_ra = target_pos;              // ra operations
    int cost_rra = size - target_pos;      // rra operations

    return (cost_ra < cost_rra) ? cost_ra : cost_rra;
}
```

---

## Real-World Usage Example

### Sorting [5, 8, 2, 3, 1]

```c
// Goal: Bring minimum (1) to top using ra

// Initial
A: [5, 8, 2, 3, 1]
Position of 1: index 4

// Strategy: Rotate 4 times
ra(a, 1);  // [8, 2, 3, 1, 5]
ra(a, 1);  // [2, 3, 1, 5, 8]
ra(a, 1);  // [3, 1, 5, 8, 2]
ra(a, 1);  // [1, 5, 8, 2, 3]  ← 1 is now on top!

// Now can pb to move 1 to B, or continue sorting
```

---

## Performance Notes

### When to Use ra

**Use ra when:**
1. Need to access element in upper half of stack
2. Combined rr operation is beneficial
3. Target element is closer to top than bottom

**Avoid ra when:**
1. Element is in lower half (use rra instead - fewer operations)
2. Only 2 elements (use sa - it's O(1))
3. Stack is very large and element is deep

### Cost Optimization
```c
// Decision: ra vs rra
int size = stack_size(stack_a);
int target_pos = find_position(stack_a, target);

if (target_pos <= size / 2)
    use ra  // Closer to top
else
    use rra  // Closer to bottom (reverse rotate)
```

### Examples
```
Stack size: 10
Target at position 3:
- ra: 3 moves
- rra: 7 moves
→ Use ra!

Target at position 8:
- ra: 8 moves
- rra: 2 moves
→ Use rra!
```

---

## Summary

**What ra Does:**
- Rotates stack A upward
- First element moves to last position
- All others shift up by one
- O(n) time complexity (must find last node)

**Key Points:**
- ✅ Critical for accessing deep elements
- ✅ Inverse of rra
- ✅ Must set first->next to NULL to avoid cycles
- ✅ Order of operations is crucial
- ✅ More expensive than swap/push (O(n) vs O(1))

**Remember:**
1. Always validate stack has 2+ elements
2. Use stack_last() to find last node
3. Rewire in correct order: head, detach, attach
4. Consider rra if element is in lower half
5. N rotations on N-element stack returns to start

---

## Location in Project

**File:** `srcs/operations_rotate.c`
**Header:** `includes/push_swap.h`
**Category:** Phase 4 - Stack Operations
**Type:** Rotate Operation

---

## Related Functions

- [rb](rb.md) - Rotate stack B (mirror function)
- [rr](rr.md) - Rotate both A and B simultaneously
- [rra](rra.md) - Reverse rotate A (inverse operation)
- [stack_last](stack_last.md) - Find last node (required helper)
- [stack_size](stack_size.md) - Count elements (for cost calculation)

---

*ra is your key to stack navigation - master it to unlock complex sorting algorithms!*
