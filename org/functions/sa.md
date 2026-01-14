# sa - Swap First Two Elements of Stack A

## Function Signature

```c
void sa(t_stack **stack_a, int print)
```

**Return type:** `void` - No return value (modifies stack in place)
**Parameter 1:** `t_stack **stack_a` - Double pointer to stack A
**Parameter 2:** `int print` - If 1, print "sa\n"; if 0, silent operation

---

## Purpose & Use Case

`sa` is one of the **11 fundamental operations** in push_swap. It swaps the first two elements at the top of stack A. This is a **core primitive operation** that forms the foundation of all push_swap sorting algorithms.

### When You'll Use It

You'll call `sa` whenever you need to:
1. **Fix small inversions** - Swap two adjacent elements that are out of order
2. **Sort small stacks** - Critical for sorting 2-3 elements
3. **Optimize positioning** - Adjust top elements before pushing
4. **Complex sorting** - Part of larger sorting sequences

### The 11 Core Operations

push_swap has exactly 11 operations, organized into 4 categories:

**Swap operations:**
- `sa` - swap first 2 elements of A
- `sb` - swap first 2 elements of B
- `ss` - `sa` and `sb` simultaneously

**Push operations:**
- `pa` - push top of B to A
- `pb` - push top of A to B

**Rotate operations:**
- `ra` - rotate A up (first becomes last)
- `rb` - rotate B up
- `rr` - `ra` and `rb` simultaneously

**Reverse rotate operations:**
- `rra` - rotate A down (last becomes first)
- `rrb` - rotate B down
- `rrr` - `rra` and `rrb` simultaneously

---

## Deep Dive: How It Works

### The Swap Operation Visualized

**Before swap:**
```
Stack A:
[5] <- top (first element)
[3] <- second element
[8]
[1]
[2] <- bottom

Linked list representation:
stack_a -> [5] -> [3] -> [8] -> [1] -> [2] -> NULL
```

**After `sa(stack_a, 1)`:**
```
Stack A:
[3] <- top (was second)
[5] <- second (was first)
[8]
[1]
[2] <- bottom

Linked list representation:
stack_a -> [3] -> [5] -> [8] -> [1] -> [2] -> NULL
```

**What changed:** Only the first two elements swapped positions!

---

## Step-by-Step Implementation

### Step 1: Check if Swap is Possible

**Condition:** Need at least 2 elements to swap.

```c
if (!*stack_a || !(*stack_a)->next)
    return;  // 0 or 1 element, cannot swap
```

**Cases where swap is impossible:**
```
Case 1: Empty stack
stack_a -> NULL
Cannot swap → return

Case 2: Single element
stack_a -> [5] -> NULL
Cannot swap → return

Case 3: Two or more elements
stack_a -> [5] -> [3] -> ...
Can swap → continue
```

### Step 2: Save Pointers

**Why?** We need to temporarily store pointers before rearranging.

```c
t_stack *first = *stack_a;
t_stack *second = (*stack_a)->next;
```

**Memory state:**
```
Original:
stack_a -> [5] -> [3] -> [8] -> NULL
           ↑      ↑
         first  second

After saving pointers:
stack_a still points to [5]
first points to [5]
second points to [3]
```

### Step 3: Perform the Swap

**Rewire the pointers:**
```c
first->next = second->next;  // First now points to third
*stack_a = second;            // Head now points to second
second->next = first;         // Second now points to first
```

**Detailed breakdown:**

**Operation 1:** `first->next = second->next`
```
Before:
[5] -> [3] -> [8] -> NULL
first  second

After:
[5] ----+
        |
[3] -> [8] -> NULL
second

Now first bypasses second and points to third element!
```

**Operation 2:** `*stack_a = second`
```
Before:
stack_a -> [5] ...

After:
stack_a -> [3] ...

Head pointer now points to second element!
```

**Operation 3:** `second->next = first`
```
Before:
stack_a -> [3] -> [8] ...
           [5] -> [8] ...

After:
stack_a -> [3] -> [5] -> [8] -> NULL

Complete! Elements are swapped!
```

### Step 4: Print Operation (Optional)

**Condition:** If `print == 1`, output the operation.

```c
if (print)
    write(1, "sa\n", 3);
```

**Why the print parameter?**
- `print = 1`: Normal operation, print "sa\n" for checker/evaluation
- `print = 0`: Silent mode, used in `ss` (simultaneous swap)

---

## Real-World Example: Complete Trace

Let's trace swapping in a stack: `[5, 3, 8, 1]`

### Initial State

```
Stack A:
stack_a -> [5] -> [3] -> [8] -> [1] -> NULL

Call: sa(&stack_a, 1);
```

### Step 1: Validation

```c
if (!*stack_a || !(*stack_a)->next)
    return;

*stack_a = [5] (not NULL) ✓
(*stack_a)->next = [3] (not NULL) ✓

Validation passed, continue.
```

### Step 2: Save Pointers

```c
t_stack *first = *stack_a;        // first points to [5]
t_stack *second = (*stack_a)->next; // second points to [3]

Memory state:
stack_a -> [5] -> [3] -> [8] -> [1] -> NULL
           ↑      ↑
         first  second
```

### Step 3: Rewire - Part 1

```c
first->next = second->next;

This makes [5]->next point to [8] instead of [3]

Memory state:
stack_a -> [5] ----+
                   |
           [3] -> [8] -> [1] -> NULL
           ↑
         second
```

### Step 4: Rewire - Part 2

```c
*stack_a = second;

This makes stack_a point to [3] instead of [5]

Memory state:
stack_a -> [3] -> [8] -> [1] -> NULL

           [5] -> [8] (also points to [8])
           ↑
         first
```

### Step 5: Rewire - Part 3

```c
second->next = first;

This makes [3]->next point to [5]

Final memory state:
stack_a -> [3] -> [5] -> [8] -> [1] -> NULL
```

### Step 6: Print

```c
if (print)
    write(1, "sa\n", 3);

Output: sa
```

### Final Result

```
Before:
Stack A: [5] -> [3] -> [8] -> [1] -> NULL

After:
Stack A: [3] -> [5] -> [8] -> [1] -> NULL

Success! First two elements swapped.
```

---

## Visual Examples

### Example 1: Basic Swap

```
Input:
./push_swap 5 3 1

Initial:
Stack A: [5] -> [3] -> [1] -> NULL

Operation: sa
Result:
Stack A: [3] -> [5] -> [1] -> NULL

Output: sa
```

### Example 2: Sorting Two Elements

```
Input:
./push_swap 2 1

Initial:
Stack A: [2] -> [1] -> NULL

Operation: sa
Result:
Stack A: [1] -> [2] -> NULL

Done! Stack is sorted.
Output: sa
```

### Example 3: Part of Larger Sort

```
Input:
./push_swap 3 2 1

Initial:
Stack A: [3] -> [2] -> [1] -> NULL

Step 1: sa
Stack A: [2] -> [3] -> [1] -> NULL

Step 2: rra
Stack A: [1] -> [2] -> [3] -> NULL

Done!
Output:
sa
rra
```

### Example 4: No-Op Cases

```
Case 1: Empty stack
Stack A: NULL
Operation: sa
Result: (nothing happens, no output)

Case 2: Single element
Stack A: [5] -> NULL
Operation: sa
Result: (nothing happens, no output)

Case 3: Already sorted pair
Stack A: [1] -> [2] -> [5] -> NULL
Operation: sa
Result: Stack A: [2] -> [1] -> [5] -> NULL
Note: Made it less sorted! sa doesn't check if swap is beneficial.
```

---

## Edge Cases

### Edge Case 1: Empty Stack

```c
t_stack *stack_a = NULL;
sa(&stack_a, 1);

Result: Function returns immediately
Output: (nothing)
```

### Edge Case 2: Single Element

```c
t_stack *stack_a = stack_new(42);
sa(&stack_a, 1);

Result: Function returns immediately
Stack: [42] -> NULL (unchanged)
Output: (nothing)
```

### Edge Case 3: Exactly Two Elements

```c
t_stack *stack_a = stack_new(5);
stack_add_back(&stack_a, stack_new(3));
// Stack: [5] -> [3] -> NULL

sa(&stack_a, 1);

Result: [3] -> [5] -> NULL
Output: sa
```

### Edge Case 4: Silent Mode (Used in ss)

```c
t_stack *stack_a = stack_new(5);
stack_add_back(&stack_a, stack_new(3));

sa(&stack_a, 0);  // print = 0

Result: [3] -> [5] -> NULL (swapped)
Output: (nothing printed)
```

**Use case:** When calling `ss` (swap both), we don't want "sa" and "sb" printed separately. We just want "ss".

```c
void ss(t_stack **stack_a, t_stack **stack_b, int print)
{
    sa(stack_a, 0);  // Silent
    sb(stack_b, 0);  // Silent
    if (print)
        write(1, "ss\n", 3);  // Print once
}
```

### Edge Case 5: Negative Numbers

```c
t_stack *stack_a = stack_new(-5);
stack_add_back(&stack_a, stack_new(-3));
// Stack: [-5] -> [-3] -> NULL

sa(&stack_a, 1);

Result: [-3] -> [-5] -> NULL
Output: sa

Works perfectly! sa doesn't care about values.
```

### Edge Case 6: INT_MIN and INT_MAX

```c
t_stack *stack_a = stack_new(INT_MAX);
stack_add_back(&stack_a, stack_new(INT_MIN));
// Stack: [2147483647] -> [-2147483648] -> NULL

sa(&stack_a, 1);

Result: [-2147483648] -> [2147483647] -> NULL
Output: sa

No overflow issues! Just pointer manipulation.
```

---

## Time & Space Complexity

### Time Complexity: O(1) - Constant Time

**Why O(1)?**
```
Operations performed:
1. Check if swap possible           → 1 check
2. Save first pointer               → 1 assignment
3. Save second pointer              → 1 assignment
4. Rewire first->next               → 1 assignment
5. Rewire *stack_a                  → 1 assignment
6. Rewire second->next              → 1 assignment
7. Print (optional)                 → 1 write

Total: 7 operations (constant)
No loops, no recursion, no stack size dependency!
```

**Performance:**
- Works the same on 3 elements or 500 elements
- Always exactly 3 pointer assignments
- One of the fastest operations in push_swap

### Space Complexity: O(1) - Constant Space

**Memory usage:**
```
Variables:
- first pointer (8 bytes)
- second pointer (8 bytes)

Total: 16 bytes (constant)
No arrays, no additional allocations!
```

---

## Implementation Pseudocode

### Basic Implementation

```
FUNCTION sa(stack_a, print):
    // Step 1: Validate
    IF stack_a is NULL OR stack_a->next is NULL:
        RETURN  // Cannot swap

    // Step 2: Save pointers
    first = *stack_a
    second = (*stack_a)->next

    // Step 3: Perform swap
    first->next = second->next   // First points to third
    *stack_a = second             // Head points to second
    second->next = first          // Second points to first

    // Step 4: Print if requested
    IF print == 1:
        PRINT "sa\n"
END FUNCTION
```

### Detailed Implementation with Comments

```
FUNCTION sa(stack_a, print):
    // Guard clause: need at least 2 elements to swap
    // Check if stack is empty OR only has one element
    IF *stack_a == NULL:
        RETURN  // Empty stack
    IF (*stack_a)->next == NULL:
        RETURN  // Only one element

    // Save references to first two nodes
    // These will be swapped
    first_node = *stack_a
    second_node = (*stack_a)->next

    // Rewire step 1: Make first node point past second node
    // This disconnects second from the chain temporarily
    first_node->next = second_node->next

    // Rewire step 2: Make head pointer point to second node
    // Second is now the new first element
    *stack_a = second_node

    // Rewire step 3: Make second node point to first node
    // This completes the swap - second now points to first
    second_node->next = first_node

    // Optional: Print operation for checker
    IF print is TRUE:
        OUTPUT "sa\n"
END FUNCTION
```

### Defensive Implementation

```
FUNCTION sa_safe(stack_a, print):
    // Extra safety checks
    IF stack_a is NULL:
        RETURN  // Invalid pointer

    IF *stack_a is NULL:
        RETURN  // Empty stack

    IF (*stack_a)->next is NULL:
        RETURN  // Single element

    // Proceed with swap
    first = *stack_a
    second = first->next

    // Validate second is not NULL (redundant but safe)
    IF second is NULL:
        RETURN

    // Perform swap
    first->next = second->next
    *stack_a = second
    second->next = first

    // Print
    IF print:
        WRITE "sa\n"
END FUNCTION
```

---

## 42 Norm Considerations

### Norm Compliance

✅ **Function length:** 8-12 lines (under 25-line limit)
✅ **Single responsibility:** Only swaps first two elements
✅ **No global variables:** Everything local or parameter
✅ **Return type:** `void` (modifies in place)
✅ **Clear naming:** `sa` follows subject requirements exactly
✅ **Parameter validation:** Checks for edge cases

### Subject Requirements

**Exact naming:**
- Must be named exactly `sa` (not swap_a, swapA, etc.)
- Must print exactly "sa\n" (not "SA\n" or "sa " with space)
- Must follow subject specifications precisely

**Output format:**
```c
✅ CORRECT:
write(1, "sa\n", 3);

❌ WRONG:
printf("sa\n");        // Not allowed (use write)
ft_putstr("sa\n");     // Okay if ft_putstr uses write
write(1, "sa", 2);     // Missing newline
write(1, "SA\n", 3);   // Wrong case
```

---

## Common Mistakes to Avoid

### Mistake 1: Wrong Order of Pointer Rewiring

```c
❌ WRONG:
void sa(t_stack **stack_a, int print)
{
    t_stack *first = *stack_a;
    t_stack *second = first->next;

    *stack_a = second;          // Changed head first!
    second->next = first;
    first->next = second->next; // Now second->next is first!
}

Result: Creates circular reference [second] -> [first] -> [second] -> ...
```

**Correct order:**
1. Fix first->next (make it skip second)
2. Update head pointer
3. Fix second->next (make it point to first)

### Mistake 2: Not Checking for NULL

```c
❌ WRONG:
void sa(t_stack **stack_a, int print)
{
    t_stack *first = *stack_a;       // Crashes if stack_a is NULL!
    t_stack *second = first->next;   // Crashes if first is NULL!
    // ...
}
```

### Mistake 3: Losing Reference to Rest of List

```c
❌ WRONG:
void sa(t_stack **stack_a, int print)
{
    t_stack *first = *stack_a;
    t_stack *second = first->next;

    second->next = first;    // This first!
    first->next = NULL;       // Lost reference to rest of list!
    *stack_a = second;
}

Result: Everything after second element is lost!
```

### Mistake 4: Using Single Pointer

```c
❌ WRONG:
void sa(t_stack *stack_a, int print)  // Single pointer!
{
    // Cannot modify caller's stack_a pointer
}

Must use: t_stack **stack_a
```

### Mistake 5: Swapping Values Instead of Nodes

```c
❌ WRONG (but works):
void sa(t_stack **stack_a, int print)
{
    if (!*stack_a || !(*stack_a)->next)
        return;

    int temp = (*stack_a)->value;
    (*stack_a)->value = (*stack_a)->next->value;
    (*stack_a)->next->value = temp;
}

Why wrong: Swaps values, not nodes
Problem: Doesn't swap index, pos, cost fields!
```

**Correct approach:** Swap nodes (pointers), not values.

---

## Testing Strategy

### Test Case 1: Two Elements

```c
// Setup
t_stack *stack_a = stack_new(2);
stack_add_back(&stack_a, stack_new(1));
// Stack: [2] -> [1] -> NULL

// Test
sa(&stack_a, 1);

// Verify
assert(stack_a->value == 1);
assert(stack_a->next->value == 2);
assert(stack_a->next->next == NULL);
printf("✓ Two elements swapped\n");
```

### Test Case 2: Three Elements

```c
// Setup
t_stack *stack_a = NULL;
stack_add_back(&stack_a, stack_new(5));
stack_add_back(&stack_a, stack_new(3));
stack_add_back(&stack_a, stack_new(1));
// Stack: [5] -> [3] -> [1] -> NULL

// Test
sa(&stack_a, 1);

// Verify
assert(stack_a->value == 3);           // First
assert(stack_a->next->value == 5);     // Second
assert(stack_a->next->next->value == 1); // Third (unchanged)
printf("✓ Three elements - first two swapped\n");
```

### Test Case 3: Empty Stack

```c
// Setup
t_stack *stack_a = NULL;

// Test
sa(&stack_a, 1);

// Verify
assert(stack_a == NULL);  // Still NULL
printf("✓ Empty stack handled\n");
```

### Test Case 4: Single Element

```c
// Setup
t_stack *stack_a = stack_new(42);

// Test
sa(&stack_a, 1);

// Verify
assert(stack_a->value == 42);
assert(stack_a->next == NULL);
printf("✓ Single element handled\n");
```

### Test Case 5: Silent Mode

```c
// Setup
t_stack *stack_a = stack_new(5);
stack_add_back(&stack_a, stack_new(3));

// Redirect stdout to capture output
// Test
sa(&stack_a, 0);  // Silent

// Verify
assert(stack_a->value == 3);  // Swapped
// Verify no output was printed
printf("✓ Silent mode works\n");
```

### Test Case 6: Multiple Swaps

```c
// Setup
t_stack *stack_a = stack_new(1);
stack_add_back(&stack_a, stack_new(2));

// Test: Swap twice
sa(&stack_a, 1);  // [2] -> [1]
sa(&stack_a, 1);  // [1] -> [2] (back to original)

// Verify
assert(stack_a->value == 1);
assert(stack_a->next->value == 2);
printf("✓ Multiple swaps work\n");
```

---

## Integration: How It's Used in push_swap

### Usage 1: Sorting Two Elements

```c
void sort_two(t_stack **stack_a)
{
    // Two elements - swap if first > second
    if ((*stack_a)->value > (*stack_a)->next->value)
        sa(stack_a, 1);
}
```

### Usage 2: Sorting Three Elements

```c
void sort_three(t_stack **stack_a)
{
    int first = (*stack_a)->value;
    int second = (*stack_a)->next->value;
    int third = (*stack_a)->next->next->value;

    // Case: 3 2 1 or 3 1 2
    if (first > second && first > third)
        ra(stack_a, 1);
    // Case: 2 3 1
    else if (second > first && second > third)
        rra(stack_a, 1);

    // Final check
    if ((*stack_a)->value > (*stack_a)->next->value)
        sa(stack_a, 1);
}
```

### Usage 3: Part of ss (Simultaneous Swap)

```c
void ss(t_stack **stack_a, t_stack **stack_b, int print)
{
    sa(stack_a, 0);  // Swap A silently
    sb(stack_b, 0);  // Swap B silently

    if (print)
        write(1, "ss\n", 3);  // Print once
}
```

### Usage 4: Optimization in Large Sorts

```c
void optimize_top_of_stack(t_stack **stack_a)
{
    // Before pushing, check if swapping helps
    if (*stack_a && (*stack_a)->next)
    {
        if (should_swap_before_push(*stack_a))
            sa(stack_a, 1);
    }
}
```

---

## Comparison with Other Operations

### sa vs sb vs ss

```c
sa - Swap A only
sb - Swap B only
ss - Swap both (equivalent to sa + sb but counts as 1 operation)
```

**Optimization opportunity:**
```c
❌ LESS EFFICIENT (2 operations):
sa(stack_a, 1);  // Output: sa
sb(stack_b, 1);  // Output: sb

✅ MORE EFFICIENT (1 operation):
ss(stack_a, stack_b, 1);  // Output: ss
```

### sa vs ra (Swap vs Rotate)

```c
sa - Changes order of first two elements
ra - Moves first element to end

Example:
Initial: [5] -> [3] -> [1] -> NULL

After sa:
[3] -> [5] -> [1] -> NULL

After ra:
[3] -> [1] -> [5] -> NULL

Different results! Choose based on goal.
```

---

## Related Functions

### Same Category (Swap Operations)

- **sb()** - Swap first two elements of stack B
- **ss()** - Swap both stacks simultaneously

### Other Categories

- **pa/pb()** - Push operations
- **ra/rb/rr()** - Rotate operations
- **rra/rrb/rrr()** - Reverse rotate operations

### Helper Functions

- **stack_add_front()** - Used by push operations
- **is_sorted()** - Check if swap is needed
- **stack_size()** - Determine which sort to use

---

## Location in Project

**File:** `srcs/operations_swap.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 2 (Operation Implementation)

**Function prototype:**
```c
void sa(t_stack **stack_a, int print);
```

**Typical implementation:**
```c
void sa(t_stack **stack_a, int print)
{
    t_stack *first;
    t_stack *second;

    if (!*stack_a || !(*stack_a)->next)
        return;

    first = *stack_a;
    second = (*stack_a)->next;

    first->next = second->next;
    *stack_a = second;
    second->next = first;

    if (print)
        write(1, "sa\n", 3);
}
```

---

## Summary: What sa Does

1. **Validates** stack has at least 2 elements
2. **Saves** pointers to first and second nodes
3. **Rewires** pointers to swap positions
4. **Prints** "sa\n" if requested
5. **Time:** O(1) - one of the fastest operations!

**Key insight:** sa is a building block. Combined with other operations, it forms the basis of all push_swap sorting algorithms. Master this, and you understand the fundamental mechanics of the project!

---

*Remember: sa doesn't care about values. It blindly swaps. You decide when to use it!*
