# rra - Reverse Rotate Stack A Down (Last Becomes First)

## Function Signature

```c
void rra(t_stack **stack_a, int print)
```

**Return type:** `void` - No return value (modifies stack A in place)
**Parameter 1:** `t_stack **stack_a` - Double pointer to stack A
**Parameter 2:** `int print` - If 1, print "rra\n"; if 0, silent operation

---

## Purpose & Use Case

`rra` (reverse rotate A) shifts all elements of stack A **down by one position**. The last element becomes the first, and every other element moves down one spot. Think of it like a **circular rotation downward** or bringing the bottom card to the top of the deck. This is the **inverse operation of ra** - what ra does, rra undoes!

### When You'll Use It

You'll call `rra` whenever you need to:
1. **Move last element to top** - Bring bottom element to the top
2. **Access lower elements** - Faster than ra when element is near bottom
3. **Undo ra** - Reverse the effect of ra
4. **Optimize cost** - When target is in lower half of stack

### Why This Matters

**rra is essential for efficient stack navigation:**
```
Without rra:
- Only have ra (must rotate entire stack)
- Accessing lower half is expensive ❌
- Suboptimal operation count

With rra:
- Can go forward or backward
- Accessing lower half is cheap ✅
- Minimized operation count
```

### Real-World Analogy

**Think of a deck of cards:**
```
Before rra:
Top → [Blue]
      [Red]
      [Green]
Bottom → [Yellow] ← Take this one!

After rra:
Top → [Yellow] ← Yellow came from bottom
      [Blue]
      [Red]
Bottom → [Green]
```

**Like a conveyor belt moving backwards!**

---

## Deep Dive: How It Works

### The Reverse Rotate A Operation Visualized

**Before `rra`:**
```
Stack A:
[5] <- top (first)
[8]
[2]
[3] <- last
```

**After `rra`:**
```
Stack A:
[3] <- top (was last, now first)
[5]
[8]
[2] <- last (was second-to-last)
```

**What happened:**
1. Element `3` removed from bottom
2. Element `3` added to top
3. All others shift down
4. Net effect: entire stack rotated down

### Difference from ra

```
ra (rotate up):
[5, 8, 2, 3] → [8, 2, 3, 5]
First becomes last

rra (rotate down):
[5, 8, 2, 3] → [3, 5, 8, 2]
Last becomes first
```

**They are inverse operations!**

### Linked List Perspective

**Before `rra`:**
```
stack_a -> [5] -> [8] -> [2] -> [3] -> NULL
           ^                    ^
         first                 last
```

**After `rra`:**
```
stack_a -> [3] -> [5] -> [8] -> [2] -> NULL
           ^                    ^
      new first               new last
      (was last)         (was second-to-last)
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
Node 5:  next = Node 8    (unchanged)
Node 8:  next = Node 2    (unchanged)
Node 2:  next = NULL      (changed - now last!)
Node 3:  next = Node 5    (changed - now points to old first!)

*stack_a = Node 3  (changed - new head!)
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
first = *stack_a;               // Current top
last = stack_last(*stack_a);    // Current last (will become first)
second_to_last = stack_second_to_last(*stack_a);  // Will become new last
```

**Memory state:**
```
first -> [5] -> [8] -> [2] -> [3] -> NULL
                       ^      ^
              second_to_last  last

*stack_a = first
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
*stack_a -> [5] -> [8] -> [2] -> NULL  (shortened)
last -> [3] -> NULL  (isolated)
```

### Step 4: Attach Last to Front

**Make last point to current first:**
```c
last->next = first;
```

**After this:**
```
last -> [3] -> [5] -> [8] -> [2] -> NULL
                       ^----------------^
                   old chain still intact
```

### Step 5: Update Stack Head

**Make stack point to last (new first):**
```c
*stack_a = last;
```

**Final result:**
```
*stack_a -> [3] -> [5] -> [8] -> [2] -> NULL
```

### Step 6: Print Operation (Optional)

**If print flag is set:**
```c
if (print)
    write(1, "rra\n", 4);
```

---

## Complete Algorithm Pseudocode

```
FUNCTION rra(stack_a, print):
    // Step 1: Validate
    IF stack_a is NULL:
        RETURN
    IF *stack_a is NULL:
        RETURN
    IF (*stack_a)->next is NULL:
        RETURN  // Only 1 element, nothing to rotate

    // Step 2: Store references
    first = *stack_a
    last = stack_last(*stack_a)
    second_to_last = stack_second_to_last(*stack_a)

    // Step 3: Detach last node
    second_to_last->next = NULL

    // Step 4: Attach last to front
    last->next = first

    // Step 5: Update head to last
    *stack_a = last

    // Step 6: Print if requested
    IF print == 1:
        PRINT "rra\n"

    RETURN
END FUNCTION
```

### Alternative Implementation (Single Traversal)

```
FUNCTION rra_optimized(stack_a, print):
    // Validate
    IF !stack_a OR !*stack_a OR !(*stack_a)->next:
        RETURN

    // Traverse to find last and second-to-last in one pass
    current = *stack_a
    WHILE current->next->next != NULL:
        current = current->next
    // Now current is second-to-last

    last = current->next
    current->next = NULL        // Detach
    last->next = *stack_a       // Attach to front
    *stack_a = last             // Update head

    IF print:
        PRINT "rra\n"
END FUNCTION
```

---

## Visual Execution Trace

### Example: Reverse Rotate [5, 8, 2, 3]

**Initial State:**
```
*stack_a -> [5] -> [8] -> [2] -> [3] -> NULL
```

**After Step 1 (Validation):**
```
✅ Stack exists
✅ Has more than 1 element
Continue to reverse rotate
```

**After Step 2 (Store References):**
```
first = pointer to [5]
last  = pointer to [3]
second_to_last = pointer to [2]

first -> [5] -> [8] -> [2] -> [3] -> NULL
                       ^      ^
              second_to_last  last
```

**After Step 3 (Detach last):**
```
*stack_a -> [5] -> [8] -> [2] -> NULL
last -> [3] -> NULL  (isolated)
```

**After Step 4 (Attach to front):**
```
last -> [3] -> [5] -> [8] -> [2] -> NULL
```

**After Step 5 (Update head):**
```
*stack_a -> [3] -> [5] -> [8] -> [2] -> NULL
```

**After Step 6 (Print):**
```
Output: "rra\n"
Final: [3, 5, 8, 2]  ✅ Reverse rotation complete!
```

---

## Edge Cases

### Case 1: Empty Stack

```c
t_stack *stack_a = NULL;

rra(&stack_a, 1);

// Result: nothing happens, no crash
assert(stack_a == NULL);
```

### Case 2: Single Element

```c
// Before
stack_a -> [42] -> NULL

// Execute
rra(&stack_a, 1);

// After
stack_a -> [42] -> NULL  (unchanged)

// Reverse rotation of 1 element has no effect
```

### Case 3: Two Elements

```c
// Before
stack_a -> [5] -> [8] -> NULL

// Execute
rra(&stack_a, 1);

// After
stack_a -> [8] -> [5] -> NULL

// Effectively swaps them!
// Same result as ra or sa for 2 elements
```

### Case 4: Three Elements

```c
// Before
stack_a -> [5] -> [8] -> [2] -> NULL

// Execute
rra(&stack_a, 1);

// After
stack_a -> [2] -> [5] -> [8] -> NULL

// Last element moved to top
```

### Case 5: Many Elements

```c
// Before
stack_a -> [1] -> [2] -> [3] -> [4] -> [5] -> NULL

// Execute
rra(&stack_a, 1);

// After
stack_a -> [5] -> [1] -> [2] -> [3] -> [4] -> NULL

// Last moved to first, all others shifted down
```

### Case 6: Inverse of ra

```c
// Starting state
stack = [5, 8, 2, 3]

ra(&stack, 1);   // [8, 2, 3, 5]
rra(&stack, 1);  // [5, 8, 2, 3]  ← Back to original!

// ra and rra cancel each other out
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

**Total: O(n)** where n = number of elements

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
sa:          O(1)        2 elements need swap
ra:          O(n)        Element in upper half
rra:         O(n)        Element in lower half ← Often better!
```

---

## Relationship with Other Operations

### Inverse of ra (Rotate A)

```c
// Starting state
A: [5, 8, 2, 3]

ra(&a, 1);   // [8, 2, 3, 5]
rra(&a, 1);  // [5, 8, 2, 3]  ← Back to start!

// They undo each other!
```

### Used to Access Lower Half Elements

```c
// To bring element near bottom to top
A: [5, 8, 2, 3, 1]  (1 is at position 4)

// Option 1: Use ra (4 operations)
ra(&a, 1);  // [8, 2, 3, 1, 5]
ra(&a, 1);  // [2, 3, 1, 5, 8]
ra(&a, 1);  // [3, 1, 5, 8, 2]
ra(&a, 1);  // [1, 5, 8, 2, 3]  ← 4 moves

// Option 2: Use rra (1 operation!)
rra(&a, 1);  // [1, 5, 8, 2, 3]  ← Only 1 move! ✅

// rra is much better for lower half!
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
void	rra(t_stack **stack_a, int print)
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
last = stack_last(*stack_a);
second_to_last = stack_second_to_last(*stack_a);

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

**Alternative:** Can optimize with single traversal function!

---

## Common Mistakes

### ❌ Mistake 1: Not Detaching Second-to-Last

```c
// WRONG
last->next = *stack_a;  // Attach to front first
*stack_a = last;

// Result: Circular list!
// [3] -> [5] -> [8] -> [2] -> [3] -> ...
// Infinite loop!
```

**✅ Correct:**
```c
second_to_last->next = NULL;  // CRITICAL: break the link first!
last->next = *stack_a;
*stack_a = last;
```

### ❌ Mistake 2: Wrong Order of Operations

```c
// WRONG
*stack_a = last;              // Change head first
last->next = *stack_a;        // Now points to itself!

// Result: Circular reference to self
```

**✅ Correct order:**
```c
second_to_last->next = NULL;  // 1. Detach
last->next = *stack_a;        // 2. Attach to front
*stack_a = last;              // 3. Update head
```

### ❌ Mistake 3: Not Finding Second-to-Last

```c
// WRONG - Just finding last
last = stack_last(*stack_a);
last->next = *stack_a;   // Who detaches last from chain?

// Result: Chain still connected, creating cycle
```

**✅ Must find second-to-last:**
```c
second_to_last = stack_second_to_last(*stack_a);
second_to_last->next = NULL;  // This detaches last!
```

### ❌ Mistake 4: Confusing ra and rra Logic

```c
// WRONG - Using ra logic for rra
first->next = NULL;  // This is ra logic!
last->next = first;

// Result: Wrong operation, breaks the list
```

**✅ rra moves last to first:**
```c
second_to_last->next = NULL;  // Detach last
last->next = first;            // Last points to first
*stack_a = last;               // Last becomes new head
```

### ❌ Mistake 5: Skipping Validation

```c
// WRONG
void rra(t_stack **stack_a, int print)
{
    last = stack_last(*stack_a);  // SEGFAULT if NULL!
}
```

**✅ Always validate:**
```c
if (!stack_a || !*stack_a || !(*stack_a)->next)
    return;
```

### ❌ Mistake 6: Single Pointer Parameter

```c
// WRONG
void rra(t_stack *stack_a, int print)
{
    // Can't change what stack_a points to!
}
```

**✅ Use double pointer:**
```c
void rra(t_stack **stack_a, int print)
{
    *stack_a = last;  // Can modify the head
}
```

---

## Testing Strategy

### Test 1: Empty Stack

```c
t_stack *a = NULL;

rra(&a, 1);

assert(a == NULL);  // Unchanged
// No crash
```

### Test 2: Single Element

```c
t_stack *a = stack_new(42);

rra(&a, 1);

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
rra(&a, 1);

// Verify
assert(a->value == 8);          // Was last
assert(a->next->value == 5);    // Was first
assert(a->next->next == NULL);
```

### Test 4: Three Elements

```c
// Setup: A = [5, 8, 2]
t_stack *a = create_stack(5, 8, 2);

// Execute
rra(&a, 1);

// Verify
assert(a->value == 2);          // Was last
assert(a->next->value == 5);    // Was first
assert(a->next->next->value == 8);
assert(a->next->next->next == NULL);
```

### Test 5: Inverse of ra

```c
// Setup: A = [5, 8, 2, 3]
t_stack *a = create_stack(5, 8, 2, 3);
int original_top = a->value;

// Execute: ra then rra
ra(&a, 1);   // [8, 2, 3, 5]
rra(&a, 1);  // [5, 8, 2, 3]

// Verify: Back to original
assert(a->value == original_top);
```

### Test 6: Large Stack

```c
// Setup: A = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
t_stack *a = create_large_stack(10);

// Execute
rra(&a, 1);

// Verify
assert(a->value == 10);              // Last is now first
assert(a->next->value == 1);         // First is now second
```

---

## Integration with Push_swap

### Bringing Lower Element to Top

```c
// Find target element's position
int target_pos = find_position(stack_a, target_value);
int size = stack_size(stack_a);

// Optimize: Use rra if in lower half
if (target_pos > size / 2)
{
    int rra_count = size - target_pos;
    for (int i = 0; i < rra_count; i++)
        rra(&stack_a, 1);
}
else
{
    for (int i = 0; i < target_pos; i++)
        ra(&stack_a, 1);
}
```

### In Final Rotate

```c
void final_rotate(t_stack **stack_a)
{
    int min_pos = find_min_position(*stack_a);
    int size = stack_size(*stack_a);

    // Choose optimal rotation direction
    if (min_pos <= size / 2)
    {
        // Upper half - use ra
        while (min_pos > 0)
        {
            ra(stack_a, 1);
            min_pos--;
        }
    }
    else
    {
        // Lower half - use rra
        while (min_pos < size)
        {
            rra(stack_a, 1);
            min_pos++;
        }
    }
}
```

### Cost Calculation with rra

```c
// Calculate cheapest way to bring element to top
int calculate_rotate_cost(t_stack *stack, int position)
{
    int size = stack_size(stack);

    // Cost using ra (forward)
    int cost_ra = position;

    // Cost using rra (backward)
    int cost_rra = size - position;

    // Return cheaper option
    return (cost_ra < cost_rra) ? cost_ra : -cost_rra;
    // Negative indicates rra should be used
}
```

---

## Real-World Usage Example

### Sorting [5, 8, 2, 3, 1] - Finding Minimum

```c
// Goal: Bring minimum (1) to top efficiently

// Initial
A: [5, 8, 2, 3, 1]
Position of 1: index 4 (last)
Size: 5

// Strategy decision:
// ra cost: 4 operations
// rra cost: 1 operation ← Better!

// Using rra:
rra(a, 1);  // [1, 5, 8, 2, 3]  ← 1 is now on top!

// Only 1 move instead of 4! ✅
```

---

## Performance Notes

### When to Use rra

**Use rra when:**
1. Element is in lower half of stack (position > size/2)
2. Need to undo ra operation
3. Want to move last element to top
4. Combined rrr operation is beneficial

**Avoid rra when:**
1. Element is in upper half (use ra instead)
2. Only 2 elements (use sa - it's O(1))
3. Stack is small and position is at top

### Cost Decision

```c
// Automatic decision making
int size = stack_size(stack_a);
int target_pos = find_position(stack_a, target);

if (target_pos <= size / 2)
    use ra  // Element closer to top
else
    use rra  // Element closer to bottom ← Often better!
```

### Examples

```
Stack size: 10
Target at position 2:
- ra: 2 moves
- rra: 8 moves
→ Use ra!

Target at position 8:
- ra: 8 moves
- rra: 2 moves
→ Use rra! ✅

Target at position 5:
- ra: 5 moves
- rra: 5 moves
→ Either works, prefer ra (slightly simpler)
```

---

## Summary

**What rra Does:**
- Reverse rotates stack A downward
- Last element moves to first position
- All others shift down by one
- O(n) time complexity (must find last and second-to-last)
- Inverse operation of ra

**Key Points:**
- ✅ Critical for efficient stack navigation
- ✅ Better than ra for lower half elements
- ✅ Inverse of ra (they cancel each other)
- ✅ Must detach second-to-last's next to NULL
- ✅ Order of operations is crucial
- ✅ More complex than ra (needs two node references)

**Remember:**
1. Always validate stack has 2+ elements
2. Find both last and second-to-last nodes
3. Detach last by setting second-to-last->next = NULL
4. Attach last to front: last->next = first
5. Update head: *stack_a = last
6. Use rra when element is in lower half
7. Combine with rrr when both stacks need reverse rotation

---

## Location in Project

**File:** `srcs/operations_reverse_rotate.c`
**Header:** `includes/push_swap.h`
**Category:** Phase 4 - Stack Operations
**Type:** Reverse Rotate Operation

---

## Related Functions

- [ra](ra.md) - Rotate stack A (inverse operation)
- [rrb](rrb.md) - Reverse rotate stack B (mirror function)
- [rrr](rrr.md) - Reverse rotate both A and B simultaneously
- [stack_last](stack_last.md) - Find last node (required helper)
- [stack_second_to_last](stack_utils.md) - Find second-to-last (required helper)
- [stack_size](stack_size.md) - Count elements (for cost calculation)

---

*rra is your backward navigation tool - use it to efficiently access the lower half of your stack!*
