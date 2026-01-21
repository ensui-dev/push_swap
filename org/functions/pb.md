# pb - Push Top of Stack A to Stack B

## Function Signature

```c
void pb(t_stack **stack_a, t_stack **stack_b, int print)
```

**Return type:** `void` - No return value (modifies both stacks in place)
**Parameter 1:** `t_stack **stack_a` - Double pointer to stack A (source)
**Parameter 2:** `t_stack **stack_b` - Double pointer to stack B (destination)
**Parameter 3:** `int print` - If 1, print "pb\n"; if 0, silent operation

---

## Purpose & Use Case

`pb` (push B) is one of the **5 most important operations** in push_swap. It takes the top element from stack A and pushes it onto stack B. This is how you move elements between stacks - the foundation of all push_swap sorting strategies!

### When You'll Use It

You'll call `pb` whenever you need to:
1. **Move elements to B** - Core of most sorting algorithms
2. **Partition the stack** - Separate elements into groups
3. **Sort large stacks** - Turk algorithm, chunk sorting, etc.
4. **Temporarily store elements** - Use B as working space

### Why This Matters

**Push operations are the heart of push_swap:**
```
Without push operations:
- Only have swap and rotate
- Can't use stack B
- Limited sorting strategies

With push operations:
- Can partition data
- Use B as temporary storage
- Implement advanced algorithms
- Minimize operation count
```

---

## Deep Dive: How It Works

### The Push Operation Visualized

**Before `pb`:**
```
Stack A:                Stack B:
[3] <- top              [7] <- top
[5]                     [1]
[8]                     [9]
[2]
```

**After `pb`:**
```
Stack A:                Stack B:
[5] <- top              [3] <- top (moved from A!)
[8]                     [7]
[2]                     [1]
                        [9]
```

**What happened:**
1. Element `3` removed from top of A
2. Element `3` added to top of B
3. All other elements stay in place

### Linked List Perspective

**Before `pb`:**
```
stack_a -> [3] -> [5] -> [8] -> [2] -> NULL

stack_b -> [7] -> [1] -> [9] -> NULL
```

**After `pb`:**
```
stack_a -> [5] -> [8] -> [2] -> NULL

stack_b -> [3] -> [7] -> [1] -> [9] -> NULL
               ^
               └── Moved from A!
```

---

## Step-by-Step Implementation

### Step 1: Validate Stacks

**Check if operation is possible:**
```c
if (!stack_a || !stack_b || !*stack_a)
    return;
```

**Why these checks?**
- `!stack_a` - Validates source double pointer (defensive)
- `!stack_b` - Validates destination double pointer (defensive)
- `!*stack_a` - Source must have at least 1 element to push

**Note:** Unlike swap/rotate operations, push only needs **1 element** in the source stack (not 2), so we don't check `!(*stack_a)->next`.

### Step 2: Save Pointer to Element Being Moved

**Store reference to top of A:**
```c
t_stack *temp = *stack_a;
```

**Memory state:**
```
stack_a -> [3] -> [5] -> [8] -> NULL
           ↑
         temp (saved reference)

We need this pointer because we're about to change stack_a!
```

### Step 3: Remove Element from Stack A

**Update stack A head to skip first element:**
```c
*stack_a = (*stack_a)->next;
```

**Memory state:**
```
Before:
stack_a -> [3] -> [5] -> [8] -> NULL
           ↑
         temp

After:
stack_a -> [5] -> [8] -> NULL

temp    -> [3] -> [5] -> [8] -> NULL
                  ^ temp still points to old second element!
```

### Step 4: **CRITICAL** - Disconnect Moved Node

**Clear temp's next pointer to prevent shared memory:**
```c
temp->next = NULL;
```

**Why this is CRITICAL:**
```
Before:
temp    -> [3] -> [5] -> [8] -> NULL
                  ^ Still connected to stack A!

After:
temp    -> [3] -> NULL
           ^ Now isolated, safe to add to B

Without this step:
- temp shares nodes with stack A
- Both stacks point to same nodes
- Freeing causes DOUBLE FREE
- Memory corruption!
```

**This is a common source of bugs:**
- If you forget this line, both stacks will share nodes
- When you free one stack, the other has dangling pointers
- Results in double free errors or segfaults
- Always disconnect before adding to destination!

### Step 5: Add Element to Stack B

**Use stack_add_front to add temp to B:**
```c
stack_add_front(stack_b, temp);
```

**This function does:**
```c
temp->next = *stack_b;  // temp points to old top of B
*stack_b = temp;         // B now starts with temp
```

**Memory state:**
```
Before:
stack_b -> [7] -> [1] -> NULL
temp    -> [3] -> NULL  (disconnected from A!)

After:
stack_b -> [3] -> [7] -> [1] -> NULL
           ↑
         temp (same node, now in B!)
stack_a -> [5] -> [8] -> NULL (completely separate)
```

### Step 6: Print Operation

**Output "pb\n" if requested:**
```c
if (print)
    ft_printf("pb\n");
```

---

## Real-World Example: Complete Trace

Let's push from A: `[3, 5, 8]` to B: `[7, 1]`

### Initial State

```
Stack A: [3] -> [5] -> [8] -> NULL
Stack B: [7] -> [1] -> NULL

Call: pb(&stack_a, &stack_b, 1);
```

### Step 1: Validation

```c
if (!*stack_a)
    return;

*stack_a = [3] (not NULL) ✓
Continue...
```

### Step 2: Save Pointer

```c
t_stack *temp = *stack_a;

Memory:
stack_a -> [3] -> [5] -> [8] -> NULL
           ↑
         temp (0x1000, for example)
```

### Step 3: Remove from A

```c
*stack_a = (*stack_a)->next;

Before:
stack_a -> [3] -> [5] -> [8] -> NULL

After:
stack_a -> [5] -> [8] -> NULL

temp still points to [3] node:
temp -> [3] -> [5] (still has old next pointer)
```

### Step 4: Disconnect Node (CRITICAL!)

```c
temp->next = NULL;

Before:
temp -> [3] -> [5] (shares nodes with A!)

After:
temp -> [3] -> NULL (isolated)

Why critical:
- Prevents both stacks from sharing nodes
- Avoids double free when freeing stacks
- Essential for memory safety
```

### Step 5: Add to B

```c
stack_add_front(&stack_b, temp);

Inside stack_add_front:
    temp->next = *stack_b;   // temp->next = [7]
    *stack_b = temp;          // stack_b = temp

Result:
stack_b -> [3] -> [7] -> [1] -> NULL
           ↑
         temp
stack_a -> [5] -> [8] -> NULL (completely separate!)
```

### Step 6: Print

```c
if (print)
    ft_printf("pb\n");

Output: pb
```

### Final State

```
Stack A: [5] -> [8] -> NULL
Stack B: [3] -> [7] -> [1] -> NULL

Success! Element moved from A to B.
```

---

## Visual Examples

### Example 1: Simple Push

```
Initial:
Stack A: [5] -> [3] -> [1] -> NULL
Stack B: NULL

Operation: pb
Result:
Stack A: [3] -> [1] -> NULL
Stack B: [5] -> NULL

Output: pb
```

### Example 2: Multiple Pushes

```
Initial:
Stack A: [5] -> [3] -> [8] -> [1] -> NULL
Stack B: NULL

Operation: pb
Stack A: [3] -> [8] -> [1] -> NULL
Stack B: [5] -> NULL

Operation: pb
Stack A: [8] -> [1] -> NULL
Stack B: [3] -> [5] -> NULL

Operation: pb
Stack A: [1] -> NULL
Stack B: [8] -> [3] -> [5] -> NULL

Output:
pb
pb
pb
```

**Notice:** Each pb moves one element. B builds up in reverse order!

### Example 3: Push Until Empty

```
Initial:
Stack A: [1] -> [2] -> NULL
Stack B: NULL

Operation: pb
Stack A: [2] -> NULL
Stack B: [1] -> NULL

Operation: pb
Stack A: NULL
Stack B: [2] -> [1] -> NULL

Operation: pb (attempted)
Stack A: NULL (no change)
Stack B: [2] -> [1] -> NULL (no change)
Output: (nothing)

Can't push from empty stack!
```

### Example 4: Chunk Sorting

```
Goal: Push all elements less than median to B

Initial:
Stack A: [5] -> [2] -> [8] -> [1] -> [7] -> NULL
Median: 5

Algorithm:
- Check 5: 5 >= 5, don't push, rotate
- Check 2: 2 < 5, push!
- Check 8: 8 >= 5, don't push, rotate
- Check 1: 1 < 5, push!
- Check 7: 7 >= 5, done

Result:
Stack A: [5] -> [7] -> [8] -> NULL
Stack B: [1] -> [2] -> NULL
```

---

## Edge Cases

### Edge Case 1: Push from Empty Stack A

```c
t_stack *stack_a = NULL;
t_stack *stack_b = NULL;

pb(&stack_a, &stack_b, 1);

Result:
stack_a = NULL (unchanged)
stack_b = NULL (unchanged)
Output: (nothing)

Function returns immediately.
```

### Edge Case 2: Push to Empty Stack B

```c
t_stack *stack_a = stack_new(42);
t_stack *stack_b = NULL;

pb(&stack_a, &stack_b, 1);

Result:
stack_a = NULL
stack_b -> [42] -> NULL
Output: pb

Works perfectly! B was empty, now has one element.
```

### Edge Case 3: Push Last Element from A

```c
t_stack *stack_a = stack_new(42);
t_stack *stack_b = stack_new(10);

pb(&stack_a, &stack_b, 1);

Result:
stack_a = NULL (now empty)
stack_b -> [42] -> [10] -> NULL
Output: pb

A is now empty. Valid state!
```

### Edge Case 4: Silent Mode

```c
t_stack *stack_a = stack_new(5);
t_stack *stack_b = NULL;

pb(&stack_a, &stack_b, 0);  // print = 0

Result:
stack_a = NULL
stack_b -> [5] -> NULL
Output: (nothing)

Push happened, but no output printed.
```

### Edge Case 5: Single Element in A

```c
t_stack *stack_a = stack_new(42);
t_stack *stack_b = NULL;

pb(&stack_a, &stack_b, 1);

Before:
A: [42] -> NULL
B: NULL

After:
A: NULL
B: [42] -> NULL

Perfect! Last element moved successfully.
```

---

## Time & Space Complexity

### Time Complexity: O(1) - Constant Time

**Why O(1)?**
```
Operations performed:
1. Check if stack_a is NULL           → O(1)
2. Save pointer to top of A           → O(1)
3. Update head of A                   → O(1)
4. Call stack_add_front for B         → O(1)
   - Set temp->next                   → O(1)
   - Update head of B                 → O(1)
5. Print (optional)                   → O(1)

Total: 6 operations (constant)
No loops, no traversal, no size dependency!
```

**Performance:**
- Same speed for 3 elements or 500 elements
- Only touches the top of each stack
- One of the fundamental O(1) operations

### Space Complexity: O(1) - Constant Space

**Memory usage:**
```
Variables:
- temp pointer (8 bytes)

Total: 8 bytes (constant)
No new allocations, just pointer shuffling!
```

**Important:** No new nodes created! We're just moving existing nodes between stacks.

---

## Implementation Pseudocode

### Basic Implementation

```
FUNCTION pb(stack_a, stack_b, print):
    // Step 1: Validate stacks (consistent with other operations)
    IF stack_a is NULL OR stack_b is NULL OR *stack_a is NULL:
        RETURN  // Invalid pointers or nothing to push

    // Step 2: Save reference to element being moved
    temp = *stack_a

    // Step 3: Remove element from stack A
    *stack_a = (*stack_a)->next

    // Step 4: CRITICAL - Disconnect node from old stack
    temp->next = NULL  // Prevents shared memory between stacks!

    // Step 5: Add element to stack B
    stack_add_front(stack_b, temp)

    // Step 6: Print if requested
    IF print == 1:
        PRINT "pb\n"
END FUNCTION
```

### Detailed Implementation

```
FUNCTION pb(stack_a, stack_b, print):
    // Validate both stacks (consistent with sa, ra, etc.)
    // We need at least one element in A to push
    IF stack_a is NULL:
        RETURN  // Invalid source pointer
    IF stack_b is NULL:
        RETURN  // Invalid destination pointer
    IF *stack_a is NULL:
        RETURN  // Empty source stack

    // Save pointer to node being moved
    // This node will be removed from A and added to B
    node_to_move = *stack_a

    // Remove from stack A
    // Make head of A point to second element
    // If A had only one element, *stack_a becomes NULL
    *stack_a = (*stack_a)->next

    // Add to stack B
    // This makes node_to_move the new top of B
    // node_to_move->next will point to old top of B
    // Then B's head pointer will point to node_to_move
    stack_add_front(stack_b, node_to_move)

    // Print operation name for checker/visualizer
    IF print is TRUE:
        OUTPUT "pb\n"
END FUNCTION
```

### Inline Implementation (Without stack_add_front)

```
FUNCTION pb_inline(stack_a, stack_b, print):
    // Validate (consistent with sa, ra, etc.)
    IF stack_a is NULL OR stack_b is NULL OR *stack_a is NULL:
        RETURN

    // Save and remove from A
    temp = *stack_a
    *stack_a = (*stack_a)->next
    temp->next = NULL  // CRITICAL: disconnect!

    // Add to B (inline)
    temp->next = *stack_b
    *stack_b = temp

    // Print
    IF print:
        PRINT "pb\n"
END FUNCTION

Note: Even though we set temp->next twice, the first assignment
to NULL is conceptually important for clarity. In practice, the
second assignment overwrites it, but showing both makes the
logic explicit: disconnect from old stack, then connect to new.
```

---

## 42 Norm Considerations

### Norm Compliance

✅ **Function length:** 6-10 lines (under 25-line limit)
✅ **Single responsibility:** Only pushes from A to B
✅ **No global variables:** All state passed as parameters
✅ **Return type:** `void` (modifies in place)
✅ **Clear naming:** `pb` follows subject requirements
✅ **Uses helper functions:** `stack_add_front` for code reuse

### Subject Requirements

**Exact naming and output:**
```c
✅ CORRECT:
Function name: pb
Output: "pb\n"

❌ WRONG:
Function name: push_b, pushB, push_to_b
Output: "PB\n", "pb", "push_b\n"
```

**Must handle edge cases silently:**
```c
✅ CORRECT:
if (!*stack_a)
    return;  // No error message

❌ WRONG:
if (!*stack_a)
    write(2, "Error\n", 6);  // Don't print errors for normal cases
```

---

## Common Mistakes to Avoid

### Mistake 1: Forgetting to Save Pointer

```c
❌ WRONG:
void pb(t_stack **stack_a, t_stack **stack_b, int print)
{
    if (!*stack_a)
        return;

    *stack_a = (*stack_a)->next;  // Lost reference!
    stack_add_front(stack_b, ???);  // What do we add?
}

Must save: temp = *stack_a BEFORE modifying stack_a!
```

### Mistake 2: Not Checking for NULL

```c
❌ WRONG:
void pb(t_stack **stack_a, t_stack **stack_b, int print)
{
    t_stack *temp = *stack_a;  // Crashes if stack_a is NULL!
    *stack_a = (*stack_a)->next;
    stack_add_front(stack_b, temp);
}

Must check: if (!*stack_a) return;
```

### Mistake 3: Copying Node Instead of Moving

```c
❌ WRONG:
void pb(t_stack **stack_a, t_stack **stack_b, int print)
{
    t_stack *copy = stack_new((*stack_a)->value);
    stack_add_front(stack_b, copy);
    // Didn't remove from A! Now it's in both stacks!
}

Must remove from A: *stack_a = (*stack_a)->next;
```

### Mistake 3b: Not Disconnecting Node (THIS BUG!)

```c
❌ WRONG:
void pb(t_stack **stack_a, t_stack **stack_b, int print)
{
    if (!*stack_a)
        return;
    temp = *stack_a;
    *stack_a = (*stack_a)->next;
    // FORGOT: temp->next = NULL;
    stack_add_front(stack_b, temp);
}

Result: temp->next still points to old stack A nodes!
Both stacks share memory → Double free when freeing!
This is THE MOST COMMON BUG in push operations!

Correct: Always add temp->next = NULL; before stack_add_front!
```

### Mistake 4: Memory Leak (Freeing Instead of Moving)

```c
❌ WRONG:
void pb(t_stack **stack_a, t_stack **stack_b, int print)
{
    t_stack *temp = *stack_a;
    *stack_a = (*stack_a)->next;
    free(temp);  // NO! We need to move it, not delete it!
}

Must move, not free!
```

### Mistake 5: Wrong Order of Operations

```c
❌ WRONG:
void pb(t_stack **stack_a, t_stack **stack_b, int print)
{
    if (!*stack_a)
        return;

    stack_add_front(stack_b, *stack_a);  // Added to B
    *stack_a = (*stack_a)->next;         // Removed from A

    // Problem: stack_add_front modifies (*stack_a)->next!
    // Now *stack_a points to wrong place!
}

Correct order:
1. Save pointer
2. Remove from A
3. Add to B
```

---

## Testing Strategy

### Test Case 1: Push from Non-Empty to Empty

```c
// Setup
t_stack *stack_a = stack_new(42);
t_stack *stack_b = NULL;

// Test
pb(&stack_a, &stack_b, 1);

// Verify
assert(stack_a == NULL);
assert(stack_b != NULL);
assert(stack_b->value == 42);
assert(stack_b->next == NULL);
printf("✓ Push to empty stack B\n");
```

### Test Case 2: Push from A with Multiple Elements

```c
// Setup
t_stack *stack_a = NULL;
stack_add_back(&stack_a, stack_new(1));
stack_add_back(&stack_a, stack_new(2));
stack_add_back(&stack_a, stack_new(3));
// A: [1] -> [2] -> [3] -> NULL
t_stack *stack_b = NULL;

// Test
pb(&stack_a, &stack_b, 1);

// Verify
assert(stack_a->value == 2);      // A now starts with 2
assert(stack_b->value == 1);      // B has 1
assert(stack_size(stack_a) == 2);
assert(stack_size(stack_b) == 1);
printf("✓ Push from multi-element stack\n");
```

### Test Case 3: Multiple Pushes

```c
// Setup
t_stack *stack_a = NULL;
stack_add_back(&stack_a, stack_new(1));
stack_add_back(&stack_a, stack_new(2));
stack_add_back(&stack_a, stack_new(3));
t_stack *stack_b = NULL;

// Test: Push all from A to B
pb(&stack_a, &stack_b, 1);  // B: [1]
pb(&stack_a, &stack_b, 1);  // B: [2] -> [1]
pb(&stack_a, &stack_b, 1);  // B: [3] -> [2] -> [1]

// Verify
assert(stack_a == NULL);
assert(stack_b->value == 3);
assert(stack_b->next->value == 2);
assert(stack_b->next->next->value == 1);
printf("✓ Multiple pushes work\n");
```

### Test Case 4: Push from Empty Stack

```c
// Setup
t_stack *stack_a = NULL;
t_stack *stack_b = stack_new(10);

// Test
pb(&stack_a, &stack_b, 1);

// Verify
assert(stack_a == NULL);       // Still empty
assert(stack_b->value == 10);  // Unchanged
assert(stack_size(stack_b) == 1);
printf("✓ Empty source handled\n");
```

### Test Case 5: Push to Non-Empty B

```c
// Setup
t_stack *stack_a = stack_new(5);
t_stack *stack_b = NULL;
stack_add_back(&stack_b, stack_new(7));
stack_add_back(&stack_b, stack_new(9));
// A: [5], B: [7] -> [9]

// Test
pb(&stack_a, &stack_b, 1);

// Verify
assert(stack_a == NULL);
assert(stack_b->value == 5);       // New top of B
assert(stack_b->next->value == 7); // Old top now second
assert(stack_size(stack_b) == 3);
printf("✓ Push to non-empty stack B\n");
```

### Test Case 6: Node Integrity After Push

```c
// Setup
t_stack *stack_a = stack_new(42);
stack_a->index = 5;
stack_a->cost_a = 10;
t_stack *stack_b = NULL;

// Test
pb(&stack_a, &stack_b, 1);

// Verify all fields preserved
assert(stack_b->value == 42);
assert(stack_b->index == 5);
assert(stack_b->cost_a == 10);
printf("✓ All node fields preserved\n");
```

---

## Integration: How It's Used in push_swap

### Usage 1: Chunk Algorithm

```c
void push_chunks_to_b(t_stack **stack_a, t_stack **stack_b)
{
    int median = calculate_median(*stack_a);

    while (*stack_a)
    {
        if ((*stack_a)->index < median)
            pb(stack_a, stack_b, 1);  // Push small values to B
        else
            ra(stack_a, 1);           // Rotate large values
    }
}
```

### Usage 2: Sort Small (4 and 5 elements)

```c
void sort_four(t_stack **stack_a, t_stack **stack_b)
{
    // Find minimum
    int min_pos = find_position_of_min(*stack_a);

    // Rotate min to top
    while (find_min(*stack_a) != (*stack_a)->value)
        ra(stack_a, 1);

    // Push min to B
    pb(stack_a, stack_b, 1);

    // Sort remaining 3
    sort_three(stack_a);

    // Push min back
    pa(stack_a, stack_b, 1);
}
```

### Usage 3: Turk Algorithm

```c
void turk_algorithm(t_stack **stack_a, t_stack **stack_b)
{
    // Push all but 3 to B
    while (stack_size(*stack_a) > 3)
        pb(stack_a, stack_b, 1);

    // Sort remaining 3 in A
    sort_three(stack_a);

    // Push back from B, finding optimal positions
    while (*stack_b)
    {
        calculate_target_positions(*stack_a, *stack_b);
        execute_cheapest_move(stack_a, stack_b);
    }
}
```

### Usage 4: Testing

```c
void test_pb(void)
{
    t_stack *a = create_stack((int[]){5, 3, 1}, 3);
    t_stack *b = NULL;

    pb(&a, &b, 1);

    assert(b->value == 5);
    assert(a->value == 3);
    printf("pb test: PASS\n");

    free_stack(&a);
    free_stack(&b);
}
```

---

## Comparison with pa

### pb vs pa

```c
pb - Push from A to B (stack_a is source)
pa - Push from B to A (stack_b is source)
```

**Symmetry:**
```c
// pb implementation
void pb(t_stack **stack_a, t_stack **stack_b, int print)
{
    if (!*stack_a) return;
    temp = *stack_a;
    *stack_a = (*stack_a)->next;
    stack_add_front(stack_b, temp);
    if (print) ft_printf("pb\n");
}

// pa implementation (almost identical!)
void pa(t_stack **stack_a, t_stack **stack_b, int print)
{
    if (!*stack_b) return;
    temp = *stack_b;
    *stack_b = (*stack_b)->next;
    stack_add_front(stack_a, temp);
    if (print) ft_printf("pa\n");
}

Only differences:
1. Check stack_b instead of stack_a
2. Source and destination swapped
3. Print "pa" instead of "pb"
```

### Reversibility

```c
pb followed by pa = no change

Initial:
A: [5] -> [3] -> NULL
B: NULL

After pb:
A: [3] -> NULL
B: [5] -> NULL

After pa:
A: [5] -> [3] -> NULL
B: NULL

Back to original!
```

---

## Related Functions

### Same Category (Push Operations)

- **pa()** - Push from B to A (opposite of pb)

### Uses These Functions

- **stack_add_front()** - Adds node to destination stack

### Used By These Functions

- **sort_four()** - Pushes min to B
- **sort_five()** - Pushes two smallest to B
- **push_chunks_to_b()** - Pushes chunk to B
- **turk_algorithm()** - Pushes most elements to B

### Helper Functions

- **stack_size()** - Determine how many to push
- **find_min()** - Find which element to push
- **calculate_target()** - Determine push order

---

## Location in Project

**File:** `srcs/operations_push.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 2 (Operation Implementation)

**Function prototype:**
```c
void pb(t_stack **stack_a, t_stack **stack_b, int print);
```

**Typical implementation:**
```c
void pb(t_stack **stack_a, t_stack **stack_b, int print)
{
    t_stack *temp;

    if (!stack_a || !stack_b || !*stack_a)
        return;

    temp = *stack_a;
    *stack_a = (*stack_a)->next;
    temp->next = NULL;  // CRITICAL: disconnect from A!
    stack_add_front(stack_b, temp);

    if (print)
        ft_printf("pb\n");
}
```

---

## Summary: What pb Does

1. **Validates** both stack pointers and that A has elements to push
2. **Saves** pointer to top element of A
3. **Removes** element from A (updates head)
4. **CRITICAL: Disconnects** temp node (sets next to NULL)
5. **Adds** element to front of B
6. **Prints** "pb\n" if requested
7. **Time:** O(1) - constant time operation!

**CRITICAL NOTE:** Step 4 (setting temp->next = NULL) is essential to prevent both stacks from sharing nodes, which would cause double free errors!

**Key insight:** pb is how you move data between stacks. Master this operation, and you understand the core mechanism that enables all push_swap algorithms. Combined with pa, these operations let you arbitrarily rearrange elements between stacks!

---

*Remember: Push operations don't create or destroy nodes. They just move existing nodes between stacks. Memory efficiency at its finest!*
