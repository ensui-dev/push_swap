# find_min_index - Find Position of Minimum Value in Stack

## Function Signature

```c
int find_min_index(t_stack *stack)
```

**Return type:** `int` - The position/index of the minimum value in the stack (0-based)
**Parameter:** `t_stack *stack` - Pointer to the head of the stack to search

---

## Purpose & Use Case

`find_min_index` is a **position-finding function** that not only locates the minimum value but returns **where** it is in the stack. Unlike `find_min` which returns the value itself, this function returns the position (0, 1, 2, ...) of that minimum value.

### When You'll Use It

You'll call `find_min_index` whenever you need to:
1. **Final rotation** - Determine how many rotations needed to bring min to top
2. **Small sorting algorithms** - Decide whether to use ra or rra to position minimum
3. **Cost calculations** - Calculate the cost to move minimum to top
4. **Optimization decisions** - Choose shortest path (rotate vs reverse rotate)
5. **Algorithm logic** - Make decisions based on minimum's position

### Why Position Matters

**Knowing WHERE the minimum is located is crucial:**
```
Stack: [5, 8, 2, 9, 1]
       [0] [1] [2] [3] [4]  ← positions

find_min(stack) = 1       ← What is the minimum?
find_min_index(stack) = 4 ← Where is the minimum?

Decision based on position:
Position 4 of 5 (size 5):
- 4 rotations needed with ra
- 1 rotation needed with rra  ← BETTER! Use reverse rotate

This optimization saves operations!
```

### Real-World Analogy

**Finding the position of the shortest person in a line:**
```
Line: [5'8", 6'2", 5'3", 5'10", 6'0"]
Pos:  [  0     1     2      3      4  ]

find_min: "5'3"" is the shortest (the value)
find_min_index: Position 2 is where the shortest person stands

Now you know:
- Need to move 2 positions to reach them
- They're in the front half
- Quick to reach from the start
```

---

## Deep Dive: How It Works

### The Two-Phase Algorithm

**Phase 1: Find the minimum value**
- Use `find_min()` to get the actual minimum value

**Phase 2: Find where that value is located**
- Traverse stack again counting positions
- Stop when you find the node with the minimum value
- Return the current position counter

### Algorithm Visualization

**Stack Example:** [5, 8, 2, 9, 1, 7]

```
Phase 1: Find minimum value
Call find_min(stack)
Returns: 1

Phase 2: Find position of value 1
Position counter: pos = 0
Current node: [5]
5 == 1? No
pos++, move to next

Position counter: pos = 1
Current node: [8]
8 == 1? No
pos++, move to next

Position counter: pos = 2
Current node: [2]
2 == 1? No
pos++, move to next

Position counter: pos = 3
Current node: [9]
9 == 1? No
pos++, move to next

Position counter: pos = 4
Current node: [1]
1 == 1? YES! ✅ Found it!
Return: 4

Result: Minimum is at position 4 (5th element, 0-based)
```

### Visual Position Mapping

```
Stack Structure:
┌─────┐
│  5  │ ← pos 0 (top)
├─────┤
│  8  │ ← pos 1
├─────┤
│  2  │ ← pos 2
├─────┤
│  9  │ ← pos 3
├─────┤
│  1  │ ← pos 4 ✅ MINIMUM HERE
├─────┤
│  7  │ ← pos 5
└─────┘

find_min_index returns: 4
```

---

## Step-by-Step Implementation

### Step 1: Handle Empty Stack

**Validate input:**
```c
if (!stack)
    return (-1);  // or 0, depending on design
```

**Why return -1:**
```
-1 indicates "not found" or "invalid"
- Valid positions are 0, 1, 2, ...
- -1 is clearly an error value
- Caller can check: if (index < 0) handle_error()
```

### Step 2: Find the Minimum Value

**Call the helper function:**
```c
int min = find_min(stack);
```

**Why reuse find_min:**
```
Don't repeat yourself (DRY principle)
- find_min already finds the minimum value
- We just need to reuse that result
- Cleaner, more maintainable code
- Single source of truth for "what is minimum"

Result: min now holds the value we're searching for
```

### Step 3: Initialize Position Counter

**Set up tracking:**
```c
int pos = 0;
```

**Position counting:**
```
Start at 0 (top of stack)
Increment for each node we visit
When we find the minimum, pos is its position

Example:
pos=0: Check first node
pos=1: Check second node
pos=2: Check third node
...
```

### Step 4: Traverse Until Minimum Found

**Search loop:**
```c
while (stack)
{
    if (stack->value == min)
        return (pos);  // Found it! Return position
    pos++;
    stack = stack->next;
}
```

**Loop logic:**
```
1. Check if current node has the minimum value
2. If yes: Return current position immediately
3. If no: Increment position counter
4. Move to next node
5. Repeat until found

Early exit optimization:
- Stop as soon as we find the minimum
- No need to check remaining nodes
```

### Step 5: Handle Not Found Case

**Should never happen if stack is valid:**
```c
return (-1);  // Safety fallback
```

**Why this is needed:**
```
Defensive programming:
- In theory, if find_min found a value, we WILL find it
- But better to have a fallback return
- Prevents "control reaches end of non-void function" warning
- Returns error value if something unexpected happens
```

---

## Complete Algorithm Pseudocode

```
FUNCTION find_min_index(stack):
    // Step 1: Validate input
    IF stack is NULL:
        RETURN -1  // Error: empty stack

    // Step 2: Find minimum value
    min = find_min(stack)

    // Step 3: Initialize position counter
    pos = 0

    // Step 4: Traverse and find position
    WHILE stack is not NULL:
        IF stack.value == min:
            RETURN pos  // Found! Return current position
        pos = pos + 1
        stack = stack.next

    // Step 5: Fallback (should never reach)
    RETURN -1  // Error: not found
END FUNCTION
```

---

## Visual Execution Trace

### Example: Finding Min Index in [5, 8, 2, 9, 1, 7]

```
Initial State:
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> [7] -> NULL
Pos:   [0]    [1]    [2]    [3]    [4]    [5]

Call: index = find_min_index(stack)

Step 1: Validate
stack != NULL ✅ Continue

Step 2: Find minimum value
min = find_min(stack)
min = 1 ✅

Step 3: Initialize
pos = 0

Step 4: Search Loop

Iteration 1:
  Current: [5] at pos=0
  5 == 1? No
  pos++ → pos=1
  Move to next: [8]

Iteration 2:
  Current: [8] at pos=1
  8 == 1? No
  pos++ → pos=2
  Move to next: [2]

Iteration 3:
  Current: [2] at pos=2
  2 == 1? No
  pos++ → pos=3
  Move to next: [9]

Iteration 4:
  Current: [9] at pos=3
  9 == 1? No
  pos++ → pos=4
  Move to next: [1]

Iteration 5:
  Current: [1] at pos=4
  1 == 1? YES! ✅ FOUND IT!
  RETURN 4

Result: index = 4
(Minimum value 1 is at position 4)
```

---

## Edge Cases

### Case 1: Empty Stack

```c
t_stack *stack = NULL;

int index = find_min_index(stack);

// Result: -1 (error value)
// No crash ✅
```

### Case 2: Single Element

```c
// Stack: [42] -> NULL

int index = find_min_index(stack);

// Process:
// min = find_min(stack) = 42
// pos = 0
// Check pos 0: 42 == 42? Yes
// return 0

// Result: 0 ✅
// Only element is at position 0
```

### Case 3: Minimum is First (Top)

```c
// Stack: [1, 5, 8, 9, 12]
//        [0] [1] [2] [3] [4]

int index = find_min_index(stack);

// Process:
// min = 1
// pos = 0
// Check pos 0: 1 == 1? Yes!
// return 0

// Result: 0 ✅
// Minimum already on top!
```

### Case 4: Minimum is Last

```c
// Stack: [9, 8, 5, 3, 1]
//        [0] [1] [2] [3] [4]

int index = find_min_index(stack);

// Process:
// min = 1
// Check positions 0,1,2,3: No match
// Check position 4: 1 == 1? Yes!
// return 4

// Result: 4 ✅
// Minimum at the bottom
```

### Case 5: Multiple Minimums (Duplicates)

```c
// Stack: [5, 1, 8, 1, 3]
//        [0] [1] [2] [3] [4]

int index = find_min_index(stack);

// Process:
// min = 1
// Check pos 0: 5 == 1? No
// Check pos 1: 1 == 1? Yes!
// return 1

// Result: 1 ✅
// Returns FIRST occurrence of minimum
```

### Case 6: All Same Values

```c
// Stack: [5, 5, 5, 5, 5]
//        [0] [1] [2] [3] [4]

int index = find_min_index(stack);

// Process:
// min = 5
// pos = 0
// Check pos 0: 5 == 5? Yes!
// return 0

// Result: 0 ✅
// First element is the minimum (they're all equal)
```

### Case 7: Negative Numbers

```c
// Stack: [5, -3, 0, -10, 2]
//        [0] [1]  [2] [3]  [4]

int index = find_min_index(stack);

// Process:
// min = -10
// Check until pos 3: -10 == -10? Yes!
// return 3

// Result: 3 ✅
// Handles negatives correctly
```

---

## Time & Space Complexity

### Time Complexity: **O(n)** - Linear Time

**Two passes through data:**
```
Pass 1: find_min(stack)
- Traverses entire stack: O(n)

Pass 2: Find position
- Worst case: Traverse entire stack: O(n)
- Best case: Find at position 0: O(1)
- Average case: Find at middle: O(n/2) = O(n)

Total: O(n) + O(n) = O(2n) = O(n)
```

**Can we optimize to one pass?**
```
Yes! You could combine both operations:
- Track both minimum value AND position in one loop
- This would be O(n) with a smaller constant

But for clarity and code reuse, two passes is acceptable.
The complexity is still O(n).
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
Variables:
- int min (4 bytes)
- int pos (4 bytes)
- t_stack *stack (8 bytes on 64-bit)

Total: 16 bytes, regardless of stack size
No additional data structures
No recursion
No allocations

Space = O(1) ✅
```

---

## Relationship with Other Functions

### Uses find_min

```c
int find_min_index(t_stack *stack)
{
    int min = find_min(stack);  // ← Dependency on find_min!

    // Then finds position of that minimum
    // ...
}
```

### Used in final_rotate

```c
void final_rotate(t_stack **stack_a)
{
    int min_index = find_min_index(*stack_a);  // ← Uses find_min_index!
    int size = stack_size(*stack_a);

    // Decide shortest path to bring min to top
    if (min_index <= size / 2)
        // Use ra (rotate): closer to top
        while (min_index--)
            ra(stack_a, 1);
    else
        // Use rra (reverse rotate): closer to bottom
        while (min_index++ < size)
            rra(stack_a, 1);
}
```

### Used in sort_four and sort_five

```c
void sort_four(t_stack **stack_a, t_stack **stack_b)
{
    int min_index = find_min_index(*stack_a);  // ← Find where min is

    // Move minimum to top
    if (min_index == 1)
        sa(stack_a, 1);  // Min is second, swap
    else if (min_index == 2)
    {
        rra(stack_a, 1);  // Min is third
        rra(stack_a, 1);
    }
    else if (min_index == 3)
        rra(stack_a, 1);  // Min is fourth

    // Now push min to B
    pb(stack_a, stack_b, 1);

    // Sort remaining 3
    sort_three(stack_a);

    // Push min back
    pa(stack_a, stack_b, 1);
}
```

### Complements find_max_index

```c
int min_idx = find_min_index(stack);
int max_idx = find_max_index(stack);

// Use both to understand distribution
// Are min and max close together?
// This affects sorting strategy
```

---

## Integration with Push_swap

### Scenario: Final Rotation Optimization

```c
// After sorting, stack might look like:
A: [3, 4, 5, 1, 2]
    [0] [1] [2] [3] [4]  ← positions

// Need to rotate minimum to top
int min_idx = find_min_index(A);  // Returns 3
int size = stack_size(A);          // Returns 5

// Calculate costs:
// Using ra (rotate): 3 operations
// Using rra (reverse rotate): 5 - 3 = 2 operations

Decision:
if (min_idx <= size / 2)  // 3 <= 2.5? No
    use_ra();
else
    use_rra();  // ✅ Choose this: only 2 ops vs 3

// Execute:
rra(&A, 1);  // A: [2, 3, 4, 5, 1]
rra(&A, 1);  // A: [1, 2, 3, 4, 5] ✅ Sorted!

// Saved 1 operation by choosing optimal direction!
```

### Scenario: Small Sort Decision Making

```c
// Stack: [3, 1, 2]
//        [0] [1] [2]

int min_idx = find_min_index(stack);  // Returns 1

// Decision tree based on position:
if (min_idx == 0)
    // Min already on top, handle differently
else if (min_idx == 1)
    // Min is second, swap to top
    sa(&stack, 1);  // ✅ This case
else if (min_idx == 2)
    // Min is third, reverse rotate
    rra(&stack, 1);

// After swap: [1, 3, 2]
// Now continue with sort logic...
```

### Scenario: Cost-Benefit Analysis

```c
// Large stack scenario
int min_idx = find_min_index(stack_a);
int size = stack_size(stack_a);

// Calculate rotation costs
int rotate_cost = min_idx;                    // ra operations
int rev_rotate_cost = size - min_idx;         // rra operations

// Choose cheaper option
if (rotate_cost < rev_rotate_cost)
{
    // Use ra (rotate)
    while (rotate_cost--)
        ra(&stack_a, 1);
}
else
{
    // Use rra (reverse rotate)
    while (rev_rotate_cost--)
        rra(&stack_a, 1);
}
```

---

## 42 Norm Considerations

### Function Structure

```c
int	find_min_index(t_stack *stack)
{
	int	min;
	int	pos;

	if (!stack)
		return (-1);
	min = find_min(stack);
	pos = 0;
	while (stack)
	{
		if (stack->value == min)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}
```

**Norm compliance:**
- ✅ Under 25 lines
- ✅ Single responsibility: finds position of minimum
- ✅ Only 2 variables (min, pos)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Early return for efficiency

### Variable Naming

```c
✅ GOOD: min, pos, stack
❌ BAD: minimum_value, position_counter, current_stack_node
```

Keep names short but descriptive!

---

## Common Mistakes

### Mistake 1: Not Handling NULL

```c
// ❌ WRONG
int find_min_index(t_stack *stack)
{
    int min = find_min(stack);  // If stack NULL, find_min might crash
    // ... rest of code
}
```

**✅ Correct:**
```c
if (!stack)
    return (-1);  // Check first!
int min = find_min(stack);
```

### Mistake 2: Starting Position at 1 Instead of 0

```c
// ❌ WRONG
int pos = 1;  // Positions should be 0-based!
while (stack)
{
    if (stack->value == min)
        return (pos);
    pos++;
    // ...
}
// Returns 1 for first element (should be 0)
```

**✅ Correct:**
```c
int pos = 0;  // Start at 0 for 0-based indexing
```

### Mistake 3: Incrementing Position Before Checking

```c
// ❌ WRONG
int pos = 0;
while (stack)
{
    pos++;  // Increment first
    if (stack->value == min)
        return (pos);  // Returns wrong position (off by 1)
    // ...
}
```

**✅ Correct:**
```c
while (stack)
{
    if (stack->value == min)
        return (pos);  // Return BEFORE incrementing
    pos++;  // Increment AFTER check
    // ...
}
```

### Mistake 4: Not Advancing Pointer

```c
// ❌ WRONG - Infinite loop!
while (stack)
{
    if (stack->value == min)
        return (pos);
    pos++;
    // Forgot: stack = stack->next;
}
```

**✅ Correct:**
```c
while (stack)
{
    if (stack->value == min)
        return (pos);
    pos++;
    stack = stack->next;  // CRITICAL!
}
```

### Mistake 5: Using Wrong Comparison

```c
// ❌ WRONG
if (stack->value < min)  // Looking for values LESS than min?
    return (pos);        // This doesn't make sense
```

**✅ Correct:**
```c
if (stack->value == min)  // Looking for EQUAL to min
    return (pos);
```

---

## Testing Strategy

### Test 1: Basic Positions

```c
// Min at start
stack = [1, 5, 8, 12];
assert(find_min_index(stack) == 0);

// Min at end
stack = [12, 8, 5, 1];
assert(find_min_index(stack) == 3);

// Min in middle
stack = [8, 3, 12, 5];
assert(find_min_index(stack) == 1);
```

### Test 2: Edge Cases

```c
// Empty
assert(find_min_index(NULL) == -1);

// Single
stack = [42];
assert(find_min_index(stack) == 0);

// Two elements
stack = [5, 3];
assert(find_min_index(stack) == 1);
```

### Test 3: Duplicates

```c
// Multiple minimums
stack = [5, 1, 8, 1, 3];
assert(find_min_index(stack) == 1);  // First occurrence

// All same
stack = [7, 7, 7, 7];
assert(find_min_index(stack) == 0);  // First is min
```

### Test 4: Negative Numbers

```c
stack = [5, -3, 0, -10, 2];
assert(find_min_index(stack) == 3);  // -10 at position 3

stack = [-1, -2, -3, -4, -5];
assert(find_min_index(stack) == 4);  // -5 at end
```

### Test 5: Large Stacks

```c
// 100 elements, min at various positions
stack = create_stack_with_min_at(0);
assert(find_min_index(stack) == 0);

stack = create_stack_with_min_at(50);
assert(find_min_index(stack) == 50);

stack = create_stack_with_min_at(99);
assert(find_min_index(stack) == 99);
```

### Test 6: Integration with find_min

```c
stack = [5, 8, 2, 9, 1, 7];

int min_val = find_min(stack);        // Should be 1
int min_idx = find_min_index(stack);  // Should be 4

// Verify they match
t_stack *temp = stack;
for (int i = 0; i < min_idx; i++)
    temp = temp->next;

assert(temp->value == min_val);  // Value at index should match
```

---

## Summary

**What find_min_index Does:**
1. Finds the minimum value using find_min()
2. Traverses stack to find WHERE that minimum is located
3. Returns the position (0-based index) of the minimum
4. Critical for rotation optimization decisions

**Key Characteristics:**
- ✅ Two-phase algorithm (find value, then find position)
- ✅ O(n) time complexity (two passes)
- ✅ O(1) space complexity
- ✅ Returns first occurrence if duplicates exist
- ✅ Returns -1 for error cases

**Critical Uses:**
- Final rotation: choosing between ra and rra
- Small sorts: deciding which operations to use
- Cost calculations: determining optimal move count
- Optimization: avoiding unnecessary operations

**Remember:**
- Always validate for NULL stack
- Use 0-based positioning (start at 0)
- Return position, not value
- Check equality (==), not inequality
- Advance pointer in loop to avoid infinite loop

**Optimization Insight:**
```
Position in first half → Use ra (rotate)
Position in second half → Use rra (reverse rotate)

Decision point: position <= size / 2

This single function enables this critical optimization!
```

---

## Location in Project

**File:** `srcs/stack_find.c` or `srcs/position.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 1.3 (Advanced Stack Utilities)

---

## Related Functions

- [find_min](find_min.md) - Finds minimum value (used by this function)
- [find_max_index](find_max_index.md) - Finds position of maximum (parallel function)
- [find_max](find_max.md) - Finds maximum value
- [final_rotate](final_rotate.md) - Uses find_min_index for optimization
- [sort_four](sort_four.md) - Uses find_min_index for positioning
- [sort_five](sort_five.md) - Uses find_min_index for positioning
- [assign_position](assign_position.md) - Different position assignment (cost-based)

---

*Knowing WHERE the minimum is located is just as important as knowing WHAT the minimum is - this function enables intelligent rotation decisions!*
