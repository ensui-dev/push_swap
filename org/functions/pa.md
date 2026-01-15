# pa - Push Top of Stack B to Stack A

## Function Signature

```c
void pa(t_stack **stack_a, t_stack **stack_b, int print)
```

**Return type:** `void` - No return value (modifies both stacks in place)
**Parameter 1:** `t_stack **stack_a` - Double pointer to stack A (destination)
**Parameter 2:** `t_stack **stack_b` - Double pointer to stack B (source)
**Parameter 3:** `int print` - If 1, print "pa\n"; if 0, silent operation

---

## Purpose & Use Case

`pa` (push A) is the **inverse operation of pb**. It takes the top element from stack B and pushes it onto stack A. This is how you return elements from temporary storage back to the main stack - essential for completing any sorting algorithm!

### When You'll Use It

You'll call `pa` whenever you need to:
1. **Return elements to A** - Bring sorted elements back from B
2. **Final assembly** - Build the final sorted stack in A
3. **Complete sorting** - All elements must end in A when done
4. **Retrieve stored elements** - Get back elements temporarily held in B

### Why This Matters

**pa completes the sorting cycle:**
```
Start:  All elements in A (unsorted)
Middle: Elements distributed between A and B (processing)
End:    All elements back in A (sorted)

Without pa:
- Elements stuck in B forever
- Cannot complete sorting
- Project fails ❌

With pa:
- Can retrieve elements from B
- Build final sorted stack
- Complete the algorithm ✅
```

---

## Deep Dive: How It Works

### The Push A Operation Visualized

**Before `pa`:**
```
Stack A:                Stack B:
[5] <- top              [3] <- top
[8]                     [7]
[2]                     [1]
```

**After `pa`:**
```
Stack A:                Stack B:
[3] <- top (from B!)    [7] <- top
[5]                     [1]
[8]
[2]
```

**What happened:**
1. Element `3` removed from top of B
2. Element `3` added to top of A
3. All other elements stay in place

### Linked List Perspective

**Before `pa`:**
```
stack_a -> [5] -> [8] -> [2] -> NULL

stack_b -> [3] -> [7] -> [1] -> NULL
```

**After `pa`:**
```
stack_a -> [3] -> [5] -> [8] -> [2] -> NULL
               ^
               └── Moved from B!

stack_b -> [7] -> [1] -> NULL
```

---

## Step-by-Step Implementation

### Step 1: Validate Source Stack

**Check if stack B has elements to push:**
```c
if (!*stack_b)
    return;  // Empty stack B, nothing to push
```

**Why this check?**
- Can't push from empty stack
- Attempting to access NULL->next would crash
- Graceful handling of edge case

**Difference from pb:**
- `pb` checks `*stack_a` (source is A)
- `pa` checks `*stack_b` (source is B)
- Everything else is the same logic!

### Step 2: Save Pointer to Element Being Moved

**Store reference to top of B:**
```c
t_stack *temp = *stack_b;
```

**Memory state:**
```
stack_b -> [3] -> [7] -> [1] -> NULL
           ↑
         temp (saved reference)

We need this pointer because we're about to change stack_b!
```

### Step 3: Remove Element from Stack B

**Update stack B head to skip first element:**
```c
*stack_b = (*stack_b)->next;
```

**Memory state:**
```
Before:
stack_b -> [3] -> [7] -> [1] -> NULL
           ↑
         temp

After:
stack_b -> [7] -> [1] -> NULL

temp    -> [3] -> [7] -> [1] -> NULL
                  ^ temp still points to old second element!
```

### Step 4: Add Element to Stack A

**Use stack_add_front to add temp to A:**
```c
stack_add_front(stack_a, temp);
```

**This function does:**
```c
temp->next = *stack_a;  // temp points to old top of A
*stack_a = temp;         // A now starts with temp
```

**Memory state:**
```
Before:
stack_a -> [5] -> [8] -> NULL
temp    -> [3] -> ???

After:
stack_a -> [3] -> [5] -> [8] -> NULL
           ↑
         temp (same node, now in A!)
```

### Step 5: Print Operation

**Output "pa\n" if requested:**
```c
if (print)
    ft_printf("pa\n");
```

---

## Real-World Example: Complete Trace

Let's push from B: `[3, 7, 1]` to A: `[5, 8]`

### Initial State

```
Stack A: [5] -> [8] -> NULL
Stack B: [3] -> [7] -> [1] -> NULL

Call: pa(&stack_a, &stack_b, 1);
```

### Step 1: Validation

```c
if (!*stack_b)
    return;

*stack_b = [3] (not NULL) ✓
Continue...
```

### Step 2: Save Pointer

```c
t_stack *temp = *stack_b;

Memory:
stack_b -> [3] -> [7] -> [1] -> NULL
           ↑
         temp (0x2000, for example)
```

### Step 3: Remove from B

```c
*stack_b = (*stack_b)->next;

Before:
stack_b -> [3] -> [7] -> [1] -> NULL

After:
stack_b -> [7] -> [1] -> NULL

temp still points to [3] node:
temp -> [3] -> [7] (still has old next pointer)
```

### Step 4: Add to A

```c
stack_add_front(&stack_a, temp);

Inside stack_add_front:
    temp->next = *stack_a;   // temp->next = [5]
    *stack_a = temp;          // stack_a = temp

Result:
stack_a -> [3] -> [5] -> [8] -> NULL
           ↑
         temp
```

### Step 5: Print

```c
if (print)
    ft_printf("pa\n");

Output: pa
```

### Final State

```
Stack A: [3] -> [5] -> [8] -> NULL
Stack B: [7] -> [1] -> NULL

Success! Element moved from B to A.
```

---

## Visual Examples

### Example 1: Basic Return from B

```
Initial:
Stack A: [5] -> [8] -> NULL
Stack B: [3] -> [1] -> NULL

Operation: pa
Result:
Stack A: [3] -> [5] -> [8] -> NULL
Stack B: [1] -> NULL

Output: pa
```

### Example 2: Complete Sort Sequence

```
Initial:
Stack A: [2] -> [1] -> [3] -> NULL
Stack B: NULL

Step 1: pb (move 2 to B)
Stack A: [1] -> [3] -> NULL
Stack B: [2] -> NULL

Step 2: sa (swap 1 and 3)
Stack A: [3] -> [1] -> NULL
Stack B: [2] -> NULL

Step 3: pa (bring 2 back)
Stack A: [2] -> [3] -> [1] -> NULL
Stack B: NULL

(More operations to finish...)
```

### Example 3: Emptying Stack B

```
Initial:
Stack A: [5] -> NULL
Stack B: [3] -> [2] -> [1] -> NULL

Operation: pa
Stack A: [3] -> [5] -> NULL
Stack B: [2] -> [1] -> NULL

Operation: pa
Stack A: [2] -> [3] -> [5] -> NULL
Stack B: [1] -> NULL

Operation: pa
Stack A: [1] -> [2] -> [3] -> [5] -> NULL
Stack B: NULL

All elements returned to A!
```

### Example 4: Reversing with Push Operations

```
Initial:
Stack A: [1] -> [2] -> [3] -> NULL
Stack B: NULL

Push all to B:
pb, pb, pb

Result:
Stack A: NULL
Stack B: [3] -> [2] -> [1] -> NULL

Push all back to A:
pa, pa, pa

Result:
Stack A: [1] -> [2] -> [3] -> NULL
Stack B: NULL

Back to original! (2 reversals = identity)
```

---

## Edge Cases

### Edge Case 1: Push from Empty Stack B

```c
t_stack *stack_a = stack_new(5);
t_stack *stack_b = NULL;

pa(&stack_a, &stack_b, 1);

Result:
stack_a -> [5] -> NULL (unchanged)
stack_b = NULL (unchanged)
Output: (nothing)

Function returns immediately.
```

### Edge Case 2: Push to Empty Stack A

```c
t_stack *stack_a = NULL;
t_stack *stack_b = stack_new(42);

pa(&stack_a, &stack_b, 1);

Result:
stack_a -> [42] -> NULL
stack_b = NULL
Output: pa

Works perfectly! A was empty, now has one element.
```

### Edge Case 3: Push Last Element from B

```c
t_stack *stack_a = stack_new(10);
t_stack *stack_b = stack_new(42);

pa(&stack_a, &stack_b, 1);

Result:
stack_a -> [42] -> [10] -> NULL
stack_b = NULL (now empty)
Output: pa

B is now empty. Valid state!
```

### Edge Case 4: Silent Mode

```c
t_stack *stack_a = NULL;
t_stack *stack_b = stack_new(5);

pa(&stack_a, &stack_b, 0);  // print = 0

Result:
stack_a -> [5] -> NULL
stack_b = NULL
Output: (nothing)

Push happened, but no output printed.
```

### Edge Case 5: After pb/pa Sequence

```c
t_stack *stack_a = stack_new(42);
t_stack *stack_b = NULL;

// Push to B
pb(&stack_a, &stack_b, 1);
// A: NULL, B: [42]

// Push back to A
pa(&stack_a, &stack_b, 1);
// A: [42], B: NULL

Result: Back to original state!
```

---

## Time & Space Complexity

### Time Complexity: O(1) - Constant Time

**Why O(1)?**
```
Operations performed:
1. Check if stack_b is NULL           → O(1)
2. Save pointer to top of B           → O(1)
3. Update head of B                   → O(1)
4. Call stack_add_front for A         → O(1)
   - Set temp->next                   → O(1)
   - Update head of A                 → O(1)
5. Print (optional)                   → O(1)

Total: 6 operations (constant)
No loops, no traversal, no size dependency!
```

**Performance:**
- Identical to pb performance
- Same speed regardless of stack size
- Only touches the top of each stack

### Space Complexity: O(1) - Constant Space

**Memory usage:**
```
Variables:
- temp pointer (8 bytes)

Total: 8 bytes (constant)
No new allocations, just pointer shuffling!
```

---

## Implementation Pseudocode

### Basic Implementation

```
FUNCTION pa(stack_a, stack_b, print):
    // Step 1: Check if source stack is empty
    IF *stack_b is NULL:
        RETURN  // Nothing to push

    // Step 2: Save reference to element being moved
    temp = *stack_b

    // Step 3: Remove element from stack B
    *stack_b = (*stack_b)->next

    // Step 4: Add element to stack A
    stack_add_front(stack_a, temp)

    // Step 5: Print if requested
    IF print == 1:
        PRINT "pa\n"
END FUNCTION
```

### Side-by-Side: pa vs pb

```
FUNCTION pa(stack_a, stack_b, print):     FUNCTION pb(stack_a, stack_b, print):
    IF *stack_b is NULL:                      IF *stack_a is NULL:
        RETURN                                    RETURN

    temp = *stack_b                           temp = *stack_a
    *stack_b = (*stack_b)->next               *stack_a = (*stack_a)->next
    stack_add_front(stack_a, temp)            stack_add_front(stack_b, temp)

    IF print:                                 IF print:
        PRINT "pa\n"                              PRINT "pb\n"
END FUNCTION                              END FUNCTION

Differences:
1. Source check: stack_b vs stack_a
2. Remove from: B vs A
3. Add to: A vs B
4. Output: "pa" vs "pb"
```

### Inline Implementation

```
FUNCTION pa_inline(stack_a, stack_b, print):
    // Validate
    IF *stack_b is NULL:
        RETURN

    // Save and remove from B
    temp = *stack_b
    *stack_b = (*stack_b)->next

    // Add to A (inline, without stack_add_front)
    temp->next = *stack_a
    *stack_a = temp

    // Print
    IF print:
        PRINT "pa\n"
END FUNCTION
```

---

## 42 Norm Considerations

### Norm Compliance

✅ **Function length:** 6-10 lines (under 25-line limit)
✅ **Single responsibility:** Only pushes from B to A
✅ **No global variables:** All state passed as parameters
✅ **Return type:** `void` (modifies in place)
✅ **Clear naming:** `pa` follows subject requirements
✅ **Code reuse:** Uses `stack_add_front` helper

### Subject Requirements

**Exact naming and output:**
```c
✅ CORRECT:
Function name: pa
Output: "pa\n"

❌ WRONG:
Function name: push_a, pushA, push_to_a
Output: "PA\n", "pa", "push_a\n"
```

**Must be symmetric with pb:**
```c
pa and pb must be implemented consistently:
- Same structure
- Same error handling
- Same print behavior
```

---

## Common Mistakes to Avoid

### Mistake 1: Checking Wrong Stack

```c
❌ WRONG:
void pa(t_stack **stack_a, t_stack **stack_b, int print)
{
    if (!*stack_a)  // WRONG! Should check stack_b!
        return;
    // ...
}

Correct: if (!*stack_b) return;
```

### Mistake 2: Adding to Wrong Stack

```c
❌ WRONG:
void pa(t_stack **stack_a, t_stack **stack_b, int print)
{
    if (!*stack_b)
        return;
    temp = *stack_b;
    *stack_b = (*stack_b)->next;
    stack_add_front(stack_b, temp);  // Added back to B! No movement!
}

Correct: stack_add_front(stack_a, temp);
```

### Mistake 3: Not Removing from Source

```c
❌ WRONG:
void pa(t_stack **stack_a, t_stack **stack_b, int print)
{
    if (!*stack_b)
        return;
    temp = *stack_b;
    // Forgot to remove from B!
    stack_add_front(stack_a, temp);
}

Result: temp is now in both stacks! Disaster!
Correct: *stack_b = (*stack_b)->next;
```

### Mistake 4: Confusing pa and pb Logic

```c
❌ WRONG:
void pa(t_stack **stack_a, t_stack **stack_b, int print)
{
    // Copy-pasted pb code without changing logic!
    if (!*stack_a)  // Wrong source
        return;
    temp = *stack_a;
    *stack_a = (*stack_a)->next;
    stack_add_front(stack_b, temp);  // Wrong destination
    if (print)
        ft_printf("pa\n");  // Right output, wrong operation!
}

Result: Does pb operation but prints "pa"!
```

### Mistake 5: Memory Leak

```c
❌ WRONG:
void pa(t_stack **stack_a, t_stack **stack_b, int print)
{
    if (!*stack_b)
        return;

    t_stack *temp = stack_new((*stack_b)->value);
    *stack_b = (*stack_b)->next;  // Lost reference! Memory leak!
    stack_add_front(stack_a, temp);
}

Must move the actual node, not create a copy!
```

---

## Testing Strategy

### Test Case 1: Push from B to Empty A

```c
// Setup
t_stack *stack_a = NULL;
t_stack *stack_b = stack_new(42);

// Test
pa(&stack_a, &stack_b, 1);

// Verify
assert(stack_a != NULL);
assert(stack_a->value == 42);
assert(stack_a->next == NULL);
assert(stack_b == NULL);
printf("✓ Push to empty stack A\n");
```

### Test Case 2: Push from B with Multiple Elements

```c
// Setup
t_stack *stack_a = stack_new(5);
t_stack *stack_b = NULL;
stack_add_back(&stack_b, stack_new(1));
stack_add_back(&stack_b, stack_new(2));
stack_add_back(&stack_b, stack_new(3));
// B: [1] -> [2] -> [3] -> NULL

// Test
pa(&stack_a, &stack_b, 1);

// Verify
assert(stack_a->value == 1);      // A now starts with 1
assert(stack_a->next->value == 5); // Old top now second
assert(stack_b->value == 2);      // B now starts with 2
assert(stack_size(stack_a) == 2);
assert(stack_size(stack_b) == 2);
printf("✓ Push to non-empty stack A\n");
```

### Test Case 3: Empty Stack B

```c
// Setup
t_stack *stack_a = stack_new(5);
t_stack *stack_b = NULL;

// Test
pa(&stack_a, &stack_b, 1);

// Verify
assert(stack_a->value == 5);
assert(stack_size(stack_a) == 1);
assert(stack_b == NULL);
printf("✓ Empty source handled\n");
```

### Test Case 4: pb then pa (Round Trip)

```c
// Setup
t_stack *stack_a = stack_new(42);
stack_a->index = 5;
stack_a->cost_a = 10;
t_stack *stack_b = NULL;

// Test: Push to B then back to A
pb(&stack_a, &stack_b, 1);
pa(&stack_a, &stack_b, 1);

// Verify: Back to original state
assert(stack_a != NULL);
assert(stack_a->value == 42);
assert(stack_a->index == 5);
assert(stack_a->cost_a == 10);
assert(stack_a->next == NULL);
assert(stack_b == NULL);
printf("✓ Round trip preserves state\n");
```

### Test Case 5: Empty All of B into A

```c
// Setup
t_stack *stack_a = NULL;
t_stack *stack_b = NULL;
stack_add_back(&stack_b, stack_new(1));
stack_add_back(&stack_b, stack_new(2));
stack_add_back(&stack_b, stack_new(3));

// Test: Push all from B to A
int count = 0;
while (stack_b)
{
    pa(&stack_a, &stack_b, 1);
    count++;
}

// Verify
assert(count == 3);
assert(stack_b == NULL);
assert(stack_size(stack_a) == 3);
assert(stack_a->value == 3);  // Last pushed is first
printf("✓ Emptied B into A\n");
```

### Test Case 6: Alternating Operations

```c
// Setup
t_stack *stack_a = NULL;
stack_add_back(&stack_a, stack_new(1));
stack_add_back(&stack_a, stack_new(2));
t_stack *stack_b = NULL;

// Test: pb, pb, pa
pb(&stack_a, &stack_b, 1);  // A:[2], B:[1]
pb(&stack_a, &stack_b, 1);  // A:[], B:[2,1]
pa(&stack_a, &stack_b, 1);  // A:[2], B:[1]

// Verify
assert(stack_a->value == 2);
assert(stack_a->next == NULL);
assert(stack_b->value == 1);
assert(stack_b->next == NULL);
printf("✓ Alternating operations work\n");
```

---

## Integration: How It's Used in push_swap

### Usage 1: Completing Sort

```c
void sort_large(t_stack **stack_a, t_stack **stack_b)
{
    // Push most elements to B
    push_chunks_to_b(stack_a, stack_b);

    // Sort remaining in A
    sort_three(stack_a);

    // Push everything back from B to A in optimal order
    while (*stack_b)
    {
        calculate_target_position(*stack_a, *stack_b);
        execute_move(stack_a, stack_b);
        pa(stack_a, stack_b, 1);  // KEY: Bring element back!
    }

    // Final rotation to put min at top
    final_rotate(stack_a);
}
```

### Usage 2: Sort Small (4 elements)

```c
void sort_four(t_stack **stack_a, t_stack **stack_b)
{
    // Find and push minimum to B
    int min_pos = find_position_of_min(*stack_a);
    while (find_min(*stack_a) != (*stack_a)->value)
        ra(stack_a, 1);
    pb(stack_a, stack_b, 1);

    // Sort remaining 3
    sort_three(stack_a);

    // Bring minimum back to top of A
    pa(stack_a, stack_b, 1);  // KEY: Return the min!
}
```

### Usage 3: Sort Five Elements

```c
void sort_five(t_stack **stack_a, t_stack **stack_b)
{
    // Push two smallest to B
    push_min_to_b(stack_a, stack_b);  // Uses pb
    push_min_to_b(stack_a, stack_b);  // Uses pb

    // Sort remaining 3
    sort_three(stack_a);

    // Bring both back in order
    pa(stack_a, stack_b, 1);  // Second smallest
    pa(stack_a, stack_b, 1);  // Smallest

    // Both are now at top of A in wrong order
    sa(stack_a, 1);  // Swap to fix
}
```

### Usage 4: Turk Algorithm Final Assembly

```c
void turk_push_back(t_stack **stack_a, t_stack **stack_b)
{
    while (*stack_b)
    {
        // Find cheapest move
        assign_target_positions(*stack_a, *stack_b);
        calculate_costs(*stack_a, *stack_b);
        t_stack *cheapest = find_cheapest(*stack_b);

        // Execute rotations
        execute_rotations(stack_a, stack_b, cheapest);

        // Push element to its target position
        pa(stack_a, stack_b, 1);  // KEY: Final push!
    }
}
```

---

## Comparison with pb

### Symmetry

```c
pb(stack_a, stack_b, 1);  // A to B
pa(stack_a, stack_b, 1);  // B to A
```

**They are inverses of each other:**
```c
Initial state:
A: [5, 3, 1]
B: []

After pb:
A: [3, 1]
B: [5]

After pa:
A: [5, 3, 1]
B: []

Back to original!
```

### Usage Pattern

```c
// Typical pattern: Push to B, process, push back to A

// Phase 1: Push to B
while (should_push_to_b(*stack_a))
    pb(stack_a, stack_b, 1);

// Phase 2: Sort what remains in A
sort_remaining(stack_a);

// Phase 3: Push back from B to A
while (*stack_b)
    pa(stack_a, stack_b, 1);
```

---

## Related Functions

### Same Category (Push Operations)

- **pb()** - Push from A to B (opposite of pa)

### Uses These Functions

- **stack_add_front()** - Adds node to destination stack

### Used By These Functions

- **sort_four()** - Pushes min back from B
- **sort_five()** - Pushes two mins back from B
- **turk_algorithm()** - Pushes all elements back from B
- **sort_large()** - Final assembly phase

### Helper Functions

- **calculate_target_position()** - Determine where to push
- **execute_rotations()** - Prepare stacks for push
- **final_rotate()** - Adjust A after all pushes

---

## Location in Project

**File:** `srcs/operations_push.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 2 (Operation Implementation)

**Function prototype:**
```c
void pa(t_stack **stack_a, t_stack **stack_b, int print);
```

**Typical implementation:**
```c
void pa(t_stack **stack_a, t_stack **stack_b, int print)
{
    t_stack *temp;

    if (!*stack_b)
        return;

    temp = *stack_b;
    *stack_b = (*stack_b)->next;
    stack_add_front(stack_a, temp);

    if (print)
        ft_printf("pa\n");
}
```

---

## Summary: What pa Does

1. **Validates** stack B has elements to push
2. **Saves** pointer to top element of B
3. **Removes** element from B (updates head)
4. **Adds** element to front of A
5. **Prints** "pa\n" if requested
6. **Time:** O(1) - constant time operation!

**Key insight:** pa is the "return" operation. Every element pushed to B with pb must eventually come back to A with pa. Understanding this cycle is crucial for designing efficient sorting algorithms. Your goal is to use the minimum number of operations to cycle elements through B and return them to A in sorted order!

---

*Remember: pa brings elements home. Every sorting algorithm in push_swap ends with a series of pa operations to reassemble the final sorted stack!*
