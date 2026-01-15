# sb - Swap Top Two Elements of Stack B

## Function Signature

```c
void sb(t_stack **stack_b, int print)
```

**Return type:** `void` - No return value (modifies stack B in place)
**Parameter 1:** `t_stack **stack_b` - Double pointer to stack B
**Parameter 2:** `int print` - If 1, print "sb\n"; if 0, silent operation

---

## Purpose & Use Case

`sb` (swap B) is the **mirror operation of sa**, operating on stack B instead of stack A. It swaps the first two elements at the top of stack B. This operation is crucial when you need to adjust the order of elements in the temporary holding stack.

### When You'll Use It

You'll call `sb` whenever you need to:
1. **Reorder elements in B** - Adjust positions before pushing back to A
2. **Optimize moves** - Sometimes swapping in B is cheaper than in A
3. **Small sorts** - Essential for sort_four and sort_five algorithms
4. **Preparation moves** - Set up B for efficient pa operations

### Why This Matters

**sb enables stack B manipulation:**
```
Without sb:
- Can't reorder elements in B
- Limited sorting strategies
- More moves required ❌

With sb:
- Full control over B order
- More optimization opportunities
- Efficient combined operations (ss) ✅
```

---

## Deep Dive: How It Works

### The Swap B Operation Visualized

**Before `sb`:**
```
Stack A:                Stack B:
[5]                     [7] <- top
[8]                     [3] <- second
[2]                     [1]
```

**After `sb`:**
```
Stack A:                Stack B:
[5]                     [3] <- top (was second)
[8]                     [7] <- second (was top)
[2]                     [1]
```

**What happened:**
1. The top element (7) and second element (3) swap positions
2. Stack A remains completely unchanged
3. All other elements in B stay in place

### Linked List Perspective

**Before `sb`:**
```
stack_b -> [7] -> [3] -> [1] -> NULL
           top    2nd
```

**After `sb`:**
```
stack_b -> [3] -> [7] -> [1] -> NULL
           top    2nd
```

### Memory State Transition

**Before:**
```
Node 1 (7):  next = Node 2
Node 2 (3):  next = Node 3
Node 3 (1):  next = NULL

*stack_b = Node 1
```

**After:**
```
Node 1 (7):  next = Node 3  (changed!)
Node 2 (3):  next = Node 1  (changed!)
Node 3 (1):  next = NULL

*stack_b = Node 2  (changed!)
```

---

## Step-by-Step Implementation

### Step 1: Validate Stack Has At Least 2 Elements

**Check stack B size:**
```c
// If NULL or only 1 element, do nothing
if (!stack_b || !*stack_b || !(*stack_b)->next)
    return;
```

**Why this check matters:**
- Cannot swap if stack is NULL (empty)
- Cannot swap if only 1 element exists
- Prevents segmentation faults

### Step 2: Store References to First and Second Nodes

**Save pointers to the nodes we're swapping:**
```c
first = *stack_b;           // Top element
second = (*stack_b)->next;  // Second element
```

**Memory state:**
```
first  -> [7] -> [3] -> [1] -> NULL
second -> [3] -> [1] -> NULL
*stack_b = first
```

### Step 3: Rewire Pointer Connections

**Perform the swap in proper order:**

**3a. Point first node's next to second's next:**
```c
first->next = second->next;
```
**After this:**
```
first  -> [7] -> [1] -> NULL  (skips over second!)
second -> [3] -> [1] -> NULL
```

**3b. Point second node's next to first:**
```c
second->next = first;
```
**After this:**
```
first  -> [7] -> [1] -> NULL
second -> [3] -> [7] -> [1] -> NULL  (now second points to first)
```

**3c. Update stack head to point to second:**
```c
*stack_b = second;
```
**Final result:**
```
*stack_b -> [3] -> [7] -> [1] -> NULL
```

### Step 4: Print Operation (Optional)

**If print flag is set:**
```c
if (print)
    ft_printf("sb\n");
```

**When to print:**
- print = 1: Normal execution (output moves)
- print = 0: Part of combined operation (ss handles printing)

---

## Complete Algorithm Pseudocode

```
FUNCTION sb(stack_b, print):
    // Step 1: Validate
    IF stack_b is NULL:
        RETURN
    IF *stack_b is NULL:
        RETURN
    IF (*stack_b)->next is NULL:
        RETURN

    // Step 2: Store references
    first = *stack_b
    second = (*stack_b)->next

    // Step 3: Rewire pointers (CRITICAL ORDER!)
    first->next = second->next    // First jumps over second
    second->next = first           // Second now points to first
    *stack_b = second             // Head now points to second

    // Step 4: Print if requested
    IF print == 1:
        PRINT "sb\n"

    RETURN
END FUNCTION
```

---

## Visual Execution Trace

### Example: Swap [7, 3, 1]

**Initial State:**
```
stack_b -> [7] -> [3] -> [1] -> NULL
```

**After Step 1 (Validation):**
```
✅ Stack exists
✅ Has at least 2 elements
Continue to swap
```

**After Step 2 (Store References):**
```
first  = pointer to node with value 7
second = pointer to node with value 3
*stack_b still points to [7]
```

**After Step 3a (first->next = second->next):**
```
first  -> [7] -----> [1] -> NULL  (bypasses 3)
              \
               X [3]  (temporarily disconnected from first's path)
```

**After Step 3b (second->next = first):**
```
first  -> [7] -> [1] -> NULL
second -> [3] -> [7] -> [1] -> NULL  (3 now leads to 7)
```

**After Step 3c (*stack_b = second):**
```
*stack_b -> [3] -> [7] -> [1] -> NULL  ✅ SWAP COMPLETE
```

**After Step 4 (Print):**
```
Output: "sb\n"
```

---

## Edge Cases

### Case 1: Empty Stack B
```c
// Input
t_stack *stack_b = NULL;

// Action
sb(&stack_b, 1);

// Result
// Nothing happens - function returns immediately
// No error, no crash
```

### Case 2: Stack B Has Only 1 Element
```c
// Before
stack_b -> [42] -> NULL

// Action
sb(&stack_b, 1);

// After
stack_b -> [42] -> NULL  (unchanged)
// No swap occurs - need 2 elements minimum
```

### Case 3: Stack B Has Exactly 2 Elements
```c
// Before
stack_b -> [9] -> [4] -> NULL

// Action
sb(&stack_b, 1);

// After
stack_b -> [4] -> [9] -> NULL  ✅
// Perfect swap
```

### Case 4: Stack B Has Many Elements
```c
// Before
stack_b -> [100] -> [50] -> [25] -> [12] -> [6] -> NULL

// Action
sb(&stack_b, 1);

// After
stack_b -> [50] -> [100] -> [25] -> [12] -> [6] -> NULL
// Only top two swapped, rest unchanged
```

### Case 5: Silent Mode (print = 0)
```c
// Used in combined operations (ss)
sb(&stack_b, 0);
// No output to stdout
// Used when ss will print "ss\n" instead
```

---

## Time & Space Complexity

### Time Complexity: **O(1)** - Constant Time

**Operations performed:**
1. Check NULL conditions - O(1)
2. Store 2 pointers - O(1)
3. Rewire 3 pointers - O(1)
4. Optional print - O(1)

**Total: O(1)** - Always exactly the same number of operations regardless of stack size!

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
- 2 temporary pointers (first, second)
- No allocations
- No recursion
- No arrays

**Total: O(1)** - Fixed memory footprint

---

## Relationship with Other Operations

### Complementary to sa
```c
sa(&stack_a, 1);  // Swap top 2 in A
sb(&stack_b, 1);  // Swap top 2 in B
// Mirror operations on different stacks
```

### Combined in ss
```c
// Instead of:
sa(&stack_a, 0);
sb(&stack_b, 0);
ft_printf("ss\n");

// The ss function does both swaps + prints "ss" once
ss(&stack_a, &stack_b, 1);
```

### Used with Push Operations
```c
// Common pattern: swap then push
sb(&stack_b, 1);  // Reorder B
pa(&stack_a, &stack_b, 1);  // Push from B to A
```

---

## 42 Norm Considerations

### Function Signature
```c
void	sb(t_stack **stack_b, int print)
{
    // Implementation
}
```

**Norm requirements:**
- ✅ Return type void (side effects on stack)
- ✅ Double pointer for modifying the head
- ✅ int flag for print control
- ✅ Tab between return type and function name
- ✅ No more than 25 lines

### Variable Declarations
```c
t_stack	*first;
t_stack	*second;
```

**Norm requirements:**
- ✅ Tab alignment between type and name
- ✅ All variables declared at top
- ✅ Maximum 5 variables per function
- ✅ Descriptive names

### Pointer Dereferencing
```c
// Correct
first = *stack_b;
second = (*stack_b)->next;

// Also correct
first = *stack_b;
second = first->next;
```

---

## Common Mistakes

### ❌ Mistake 1: Wrong Pointer Order
```c
// WRONG - Order matters!
*stack_b = second;           // Changes head first
first->next = second->next;  // Now first is inaccessible!
second->next = first;
// Result: Lost reference to first, memory leak!
```

**✅ Correct order:**
```c
first->next = second->next;  // Rewire first
second->next = first;        // Rewire second
*stack_b = second;          // Update head last
```

### ❌ Mistake 2: Forgetting Validation
```c
// WRONG - No validation
void sb(t_stack **stack_b, int print)
{
    *stack_b = (*stack_b)->next;  // SEGFAULT if NULL!
}
```

**✅ Always validate:**
```c
if (!stack_b || !*stack_b || !(*stack_b)->next)
    return;
```

### ❌ Mistake 3: Single Pointer Parameter
```c
// WRONG - Can't modify the head pointer
void sb(t_stack *stack_b, int print)
{
    // Can modify nodes but can't change what stack_b points to!
}
```

**✅ Use double pointer:**
```c
void sb(t_stack **stack_b, int print)
{
    // Can modify both nodes AND the head pointer
}
```

### ❌ Mistake 4: Using sa Logic on stack_b
```c
// WRONG - Copying sa code without changing variable names
void sb(t_stack **stack_b, int print)
{
    sa(&stack_b, print);  // Calling wrong function!
}
```

**✅ Implement sb independently:**
```c
void sb(t_stack **stack_b, int print)
{
    // Own implementation for stack_b
}
```

### ❌ Mistake 5: Printing in Silent Mode
```c
// WRONG - Always prints
void sb(t_stack **stack_b, int print)
{
    // ... swap logic ...
    ft_printf("sb\n");  // Ignores print flag!
}
```

**✅ Check print flag:**
```c
if (print)
    ft_printf("sb\n");
```

---

## Testing Strategy

### Test 1: Empty Stack
```c
t_stack *stack_b = NULL;

sb(&stack_b, 1);

assert(stack_b == NULL);  // Should remain NULL
// Should not crash
```

### Test 2: Single Element
```c
t_stack *stack_b = stack_new(42);

sb(&stack_b, 1);

assert(stack_b->value == 42);
assert(stack_b->next == NULL);
// No change - needs 2 elements
```

### Test 3: Two Elements
```c
// Setup: B = [10, 20]
t_stack *stack_b = stack_new(20);
stack_add_front(&stack_b, stack_new(10));

// Execute
sb(&stack_b, 1);

// Verify
assert(stack_b->value == 20);          // Was second, now first
assert(stack_b->next->value == 10);    // Was first, now second
assert(stack_b->next->next == NULL);
```

### Test 4: Multiple Elements
```c
// Setup: B = [1, 2, 3, 4, 5]
t_stack *stack_b = stack_new(5);
stack_add_front(&stack_b, stack_new(4));
stack_add_front(&stack_b, stack_new(3));
stack_add_front(&stack_b, stack_new(2));
stack_add_front(&stack_b, stack_new(1));

// Execute
sb(&stack_b, 1);

// Verify
assert(stack_b->value == 2);               // Swapped
assert(stack_b->next->value == 1);         // Swapped
assert(stack_b->next->next->value == 3);   // Unchanged
assert(stack_b->next->next->next->value == 4);
assert(stack_b->next->next->next->next->value == 5);
```

### Test 5: Print Flag
```c
// Test silent mode
sb(&stack_b, 0);  // Should not print

// Test print mode
sb(&stack_b, 1);  // Should print "sb\n"
```

### Test 6: Double Swap Returns to Original
```c
// Setup: B = [7, 3, 1]
// Save original state
int first_val = stack_b->value;
int second_val = stack_b->next->value;

// Execute twice
sb(&stack_b, 1);
sb(&stack_b, 1);

// Verify back to original
assert(stack_b->value == first_val);
assert(stack_b->next->value == second_val);
```

---

## Integration with Push_swap

### In sort_four
```c
void sort_four(t_stack **stack_a, t_stack **stack_b)
{
    // ... push elements to B ...

    // If B needs reordering before pushing back
    if ((*stack_b)->value < (*stack_b)->next->value)
        sb(stack_b, 1);  // Swap to get larger on top

    // ... push back to A ...
}
```

### In sort_five
```c
void sort_five(t_stack **stack_a, t_stack **stack_b)
{
    // Push 2 smallest to B
    // ...

    // Ensure correct order in B
    if ((*stack_b)->value < (*stack_b)->next->value)
        sb(stack_b, 1);  // Swap so larger is on top

    // Push back in correct order
    pa(stack_a, stack_b, 1);
    pa(stack_a, stack_b, 1);
}
```

### In Large Sort Optimization
```c
// Sometimes cheaper to swap in B than rotate in A
if (calculate_cost_with_sb(stack_b) < calculate_cost_without_sb(stack_b))
{
    sb(stack_b, 1);  // Optimize before pushing to A
}
```

### Combined with ss
```c
// When both A and B need swapping
if (needs_swap_a && needs_swap_b)
    ss(stack_a, stack_b, 1);  // More efficient than sa + sb
else if (needs_swap_b)
    sb(stack_b, 1);
```

---

## Real-World Usage Example

### Sorting [3, 1, 4, 2, 5]

```c
// Initial
A: [3, 1, 4, 2, 5]
B: []

pb(a, b);  // Push 3 to B
A: [1, 4, 2, 5]
B: [3]

pb(a, b);  // Push 1 to B
A: [4, 2, 5]
B: [1, 3]

sb(b, 1);  // Swap B to get correct order!
A: [4, 2, 5]
B: [3, 1]  // Now larger is on top

// Continue sorting...
pa(a, b);  // Push 3 back
A: [3, 4, 2, 5]
B: [1]

// The sb operation was crucial for correct ordering!
```

---

## Performance Notes

### When to Use sb

**Use sb when:**
1. Stack B has exactly 2 elements in wrong order
2. Combined ss operation is beneficial (both A and B need swap)
3. Swapping in B reduces total moves compared to rotating in A
4. Setting up for optimal pa sequence

**Avoid sb when:**
1. Stack B has 0 or 1 elements (does nothing)
2. Top 2 elements are already in desired order
3. Other operations would be more efficient

### Cost Analysis
```
sb = 1 move
vs
rb + rb = 2 moves (to get same element to top)

sb is more efficient for reordering top 2 elements!
```

---

## Summary

**What sb Does:**
- Swaps the first two elements of stack B
- O(1) time complexity
- Modifies only the top 2 nodes
- Can operate silently (print = 0) or with output (print = 1)

**Key Points:**
- ✅ Exact mirror of sa but for stack B
- ✅ Critical for small sorts (sort_four, sort_five)
- ✅ Enables ss combined operation
- ✅ Must have at least 2 elements to swap
- ✅ Pointer rewiring order is crucial

**Remember:**
1. Always validate stack has 2+ elements
2. Rewire in correct order: first→next, second→next, head
3. Only print if flag is set
4. sb + sb returns to original state

---

## Location in Project

**File:** `srcs/operations_swap.c`
**Header:** `includes/push_swap.h`
**Category:** Phase 4 - Stack Operations
**Type:** Swap Operation

---

## Related Functions

- [sa](sa.md) - Swap top 2 of stack A (mirror function)
- [ss](ss.md) - Swap both A and B simultaneously
- [pa](pa.md) - Push from B to A (often used after sb)
- [pb](pb.md) - Push from A to B (often used before sb)
- [stack_size](stack_size.md) - Count elements (validation)

---

*sb is small but mighty - master this operation for complete control over stack B!*
