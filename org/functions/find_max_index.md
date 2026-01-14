# find_max_index - Find Position of Maximum Value in Stack

## Function Signature

```c
int find_max_index(t_stack *stack)
```

**Return type:** `int` - The position/index of the maximum value in the stack (0-based)
**Parameter:** `t_stack *stack` - Pointer to the head of the stack to search

---

## Purpose & Use Case

`find_max_index` is a **position-finding function** that locates the maximum value and returns **where** it is in the stack. This is the complementary function to `find_min_index`, providing essential positioning information for the Turk algorithm and target position calculations.

### When You'll Use It

You'll call `find_max_index` whenever you need to:
1. **Target position calculations** - Determine where to place elements from stack B to stack A
2. **Turk algorithm** - Find optimal insertion points for maximum efficiency
3. **Cost optimization** - Calculate rotation costs to position maximum
4. **Algorithm decisions** - Choose strategies based on maximum's location
5. **Index-based sorting** - Position elements relative to the maximum

### Why Position Matters

**Knowing WHERE the maximum is located is essential for the Turk algorithm:**
```
Stack A: [5, 8, 2, 9, 1]
         [0] [1] [2] [3] [4]  ← positions

find_max(stack_a) = 9         ← What is the maximum?
find_max_index(stack_a) = 3   ← Where is the maximum?

In Turk algorithm:
- When pushing from B to A
- If value in B is larger than max in A
- Target position = position of current max
- This is where the new max should go

Knowing max position saves operations!
```

### Real-World Analogy

**Finding the position of the tallest person in a line:**
```
Line: [5'8", 6'2", 5'3", 5'10", 6'0"]
Pos:  [  0     1     2      3      4  ]

find_max: "6'2"" is the tallest (the value)
find_max_index: Position 1 is where the tallest person stands

Now you know:
- Need to move 1 position to reach them
- They're near the front
- Very accessible from the start
- Anyone taller than 6'2" should go near this position
```

---

## Deep Dive: How It Works

### The Two-Phase Algorithm

**Phase 1: Find the maximum value**
- Use `find_max()` to get the actual maximum value

**Phase 2: Find where that value is located**
- Traverse stack again counting positions
- Stop when you find the node with the maximum value
- Return the current position counter

### Algorithm Visualization

**Stack Example:** [5, 8, 2, 9, 1, 7]

```
Phase 1: Find maximum value
Call find_max(stack)
Returns: 9

Phase 2: Find position of value 9
Position counter: pos = 0
Current node: [5]
5 == 9? No
pos++, move to next

Position counter: pos = 1
Current node: [8]
8 == 9? No
pos++, move to next

Position counter: pos = 2
Current node: [2]
2 == 9? No
pos++, move to next

Position counter: pos = 3
Current node: [9]
9 == 9? YES! ✅ Found it!
Return: 3

Result: Maximum is at position 3 (4th element, 0-based)
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
│  9  │ ← pos 3 ✅ MAXIMUM HERE
├─────┤
│  1  │ ← pos 4
├─────┤
│  7  │ ← pos 5
└─────┘

find_max_index returns: 3
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

### Step 2: Find the Maximum Value

**Call the helper function:**
```c
int max = find_max(stack);
```

**Why reuse find_max:**
```
Don't repeat yourself (DRY principle)
- find_max already finds the maximum value
- We just need to reuse that result
- Cleaner, more maintainable code
- Single source of truth for "what is maximum"

Result: max now holds the value we're searching for
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
When we find the maximum, pos is its position

Example:
pos=0: Check first node
pos=1: Check second node
pos=2: Check third node
...
```

### Step 4: Traverse Until Maximum Found

**Search loop:**
```c
while (stack)
{
    if (stack->value == max)
        return (pos);  // Found it! Return position
    pos++;
    stack = stack->next;
}
```

**Loop logic:**
```
1. Check if current node has the maximum value
2. If yes: Return current position immediately
3. If no: Increment position counter
4. Move to next node
5. Repeat until found

Early exit optimization:
- Stop as soon as we find the maximum
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
- In theory, if find_max found a value, we WILL find it
- But better to have a fallback return
- Prevents "control reaches end of non-void function" warning
- Returns error value if something unexpected happens
```

---

## Complete Algorithm Pseudocode

```
FUNCTION find_max_index(stack):
    // Step 1: Validate input
    IF stack is NULL:
        RETURN -1  // Error: empty stack

    // Step 2: Find maximum value
    max = find_max(stack)

    // Step 3: Initialize position counter
    pos = 0

    // Step 4: Traverse and find position
    WHILE stack is not NULL:
        IF stack.value == max:
            RETURN pos  // Found! Return current position
        pos = pos + 1
        stack = stack.next

    // Step 5: Fallback (should never reach)
    RETURN -1  // Error: not found
END FUNCTION
```

---

## Visual Execution Trace

### Example: Finding Max Index in [5, 8, 2, 9, 1, 7]

```
Initial State:
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> [7] -> NULL
Pos:   [0]    [1]    [2]    [3]    [4]    [5]

Call: index = find_max_index(stack)

Step 1: Validate
stack != NULL ✅ Continue

Step 2: Find maximum value
max = find_max(stack)
max = 9 ✅

Step 3: Initialize
pos = 0

Step 4: Search Loop

Iteration 1:
  Current: [5] at pos=0
  5 == 9? No
  pos++ → pos=1
  Move to next: [8]

Iteration 2:
  Current: [8] at pos=1
  8 == 9? No
  pos++ → pos=2
  Move to next: [2]

Iteration 3:
  Current: [2] at pos=2
  2 == 9? No
  pos++ → pos=3
  Move to next: [9]

Iteration 4:
  Current: [9] at pos=3
  9 == 9? YES! ✅ FOUND IT!
  RETURN 3

Result: index = 3
(Maximum value 9 is at position 3)
```

---

## Edge Cases

### Case 1: Empty Stack

```c
t_stack *stack = NULL;

int index = find_max_index(stack);

// Result: -1 (error value)
// No crash ✅
```

### Case 2: Single Element

```c
// Stack: [42] -> NULL

int index = find_max_index(stack);

// Process:
// max = find_max(stack) = 42
// pos = 0
// Check pos 0: 42 == 42? Yes
// return 0

// Result: 0 ✅
// Only element is at position 0
```

### Case 3: Maximum is First (Top)

```c
// Stack: [99, 5, 8, 9, 12]
//        [0]  [1] [2] [3] [4]

int index = find_max_index(stack);

// Process:
// max = 99
// pos = 0
// Check pos 0: 99 == 99? Yes!
// return 0

// Result: 0 ✅
// Maximum already on top!
```

### Case 4: Maximum is Last

```c
// Stack: [1, 3, 5, 8, 99]
//        [0] [1] [2] [3] [4]

int index = find_max_index(stack);

// Process:
// max = 99
// Check positions 0,1,2,3: No match
// Check position 4: 99 == 99? Yes!
// return 4

// Result: 4 ✅
// Maximum at the bottom
```

### Case 5: Multiple Maximums (Duplicates)

```c
// Stack: [5, 9, 8, 9, 3]
//        [0] [1] [2] [3] [4]

int index = find_max_index(stack);

// Process:
// max = 9
// Check pos 0: 5 == 9? No
// Check pos 1: 9 == 9? Yes!
// return 1

// Result: 1 ✅
// Returns FIRST occurrence of maximum
```

### Case 6: All Same Values

```c
// Stack: [5, 5, 5, 5, 5]
//        [0] [1] [2] [3] [4]

int index = find_max_index(stack);

// Process:
// max = 5
// pos = 0
// Check pos 0: 5 == 5? Yes!
// return 0

// Result: 0 ✅
// First element is the maximum (they're all equal)
```

### Case 7: Negative Numbers

```c
// Stack: [-5, -3, -8, -1, -10]
//        [0]  [1]  [2]  [3]  [4]

int index = find_max_index(stack);

// Process:
// max = -1
// Check until pos 3: -1 == -1? Yes!
// return 3

// Result: 3 ✅
// Handles negatives correctly (-1 is largest)
```

---

## Time & Space Complexity

### Time Complexity: **O(n)** - Linear Time

**Two passes through data:**
```
Pass 1: find_max(stack)
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
- Track both maximum value AND position in one loop
- This would be O(n) with a smaller constant

But for clarity and code reuse, two passes is acceptable.
The complexity is still O(n).
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
Variables:
- int max (4 bytes)
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

### Uses find_max

```c
int find_max_index(t_stack *stack)
{
    int max = find_max(stack);  // ← Dependency on find_max!

    // Then finds position of that maximum
    // ...
}
```

### Used in find_target_position

```c
int find_target_position(t_stack *stack_a, int index_b)
{
    int max_index = find_max_index(stack_a);  // ← Uses find_max_index!

    // If index_b is larger than all indices in stack_a
    // The target position is where the maximum is
    // Because new maximum should go there

    // ...
}
```

### Critical for Turk Algorithm

```c
void calculate_target_positions(t_stack *stack_a, t_stack *stack_b)
{
    t_stack *b = stack_b;

    while (b)
    {
        // For each element in B, find where it should go in A
        int target = find_target_position(stack_a, b->index);

        // find_target_position uses find_max_index internally
        // to handle cases where B element is larger than all in A

        b->target_pos = target;
        b = b->next;
    }
}
```

### Complements find_min_index

```c
int min_idx = find_min_index(stack);
int max_idx = find_max_index(stack);

// Use both to understand distribution
if (max_idx - min_idx < 2)
    // Min and max are close together
    // Already nearly sorted or very small range
else
    // Spread out distribution
    // Need more complex sorting
```

---

## Integration with Push_swap

### Scenario: Target Position for Larger Elements

```c
// Stack A: [3, 7, 5, 9, 2]  (indices: [1, 3, 2, 4, 0])
//          [0] [1] [2] [3] [4]

// Stack B: [10]  (index: 5)  ← Larger than all in A!

int find_target_position(t_stack *a, int index_b)
{
    // index_b = 5 (from element 10 in B)

    // Find max in A
    int max_idx_a = find_max_index(a);  // Returns 3 (where 9 is)

    // Check if index_b is larger than all in A
    int max_val_a = find_max(a);  // Returns 9

    // Since 10 > 9 (index 5 > index 4)
    // The new element should become the new max
    // Target position = current max position

    return (max_idx_a);  // Return 3
}

// Result: Push 10 to position 3 (where current max is)
```

### Scenario: Rotation Cost Calculation

```c
// Calculate cost to bring max to top
int max_idx = find_max_index(stack);
int size = stack_size(stack);

// Calculate both rotation directions
int rotate_cost = max_idx;              // ra operations
int rev_rotate_cost = size - max_idx;   // rra operations

// Choose optimal direction
if (rotate_cost < rev_rotate_cost)
{
    printf("Use ra: %d operations\n", rotate_cost);
    cost = rotate_cost;
}
else
{
    printf("Use rra: %d operations\n", rev_rotate_cost);
    cost = -rev_rotate_cost;  // Negative indicates reverse
}
```

### Scenario: Finding Insertion Point

```c
// When pushing from B to A in Turk algorithm
t_stack *b_node = stack_b;

while (b_node)
{
    // For element in B with index 3
    int index_b = b_node->index;  // e.g., 3

    // Find where it should go in A
    // If it's larger than max in A:
    int max_idx_a = find_max_index(stack_a);
    int max_index_a = stack_a->index;  // Need to get max index value

    if (index_b > max_index_a)
    {
        // This element is new maximum
        // Should go where current max is
        target_pos = max_idx_a;
    }
    else
    {
        // Find closest larger element in A
        target_pos = find_closest_larger(stack_a, index_b);
    }

    b_node->target_pos = target_pos;
    b_node = b_node->next;
}
```

---

## 42 Norm Considerations

### Function Structure

```c
int	find_max_index(t_stack *stack)
{
	int	max;
	int	pos;

	if (!stack)
		return (-1);
	max = find_max(stack);
	pos = 0;
	while (stack)
	{
		if (stack->value == max)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}
```

**Norm compliance:**
- ✅ Under 25 lines
- ✅ Single responsibility: finds position of maximum
- ✅ Only 2 variables (max, pos)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Early return for efficiency

### Variable Naming

```c
✅ GOOD: max, pos, stack
❌ BAD: maximum_value, position_counter, current_node
```

Keep names short but clear!

---

## Common Mistakes

### Mistake 1: Not Handling NULL

```c
// ❌ WRONG
int find_max_index(t_stack *stack)
{
    int max = find_max(stack);  // If stack NULL, find_max might crash
    // ... rest of code
}
```

**✅ Correct:**
```c
if (!stack)
    return (-1);  // Check first!
int max = find_max(stack);
```

### Mistake 2: Starting Position at 1 Instead of 0

```c
// ❌ WRONG
int pos = 1;  // Positions should be 0-based!
while (stack)
{
    if (stack->value == max)
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

### Mistake 3: Confusing with find_min_index

```c
// ❌ WRONG
int find_max_index(t_stack *stack)
{
    int min = find_min(stack);  // Should be find_max!
    // ...
}
```

**✅ Correct:**
```c
int max = find_max(stack);  // Find MAXIMUM
```

### Mistake 4: Not Advancing Pointer

```c
// ❌ WRONG - Infinite loop!
while (stack)
{
    if (stack->value == max)
        return (pos);
    pos++;
    // Forgot: stack = stack->next;
}
```

**✅ Correct:**
```c
while (stack)
{
    if (stack->value == max)
        return (pos);
    pos++;
    stack = stack->next;  // CRITICAL!
}
```

### Mistake 5: Using Wrong Comparison

```c
// ❌ WRONG
if (stack->value > max)  // Looking for values GREATER than max?
    return (pos);        // This doesn't make sense
```

**✅ Correct:**
```c
if (stack->value == max)  // Looking for EQUAL to max
    return (pos);
```

---

## Testing Strategy

### Test 1: Basic Positions

```c
// Max at start
stack = [99, 5, 8, 12];
assert(find_max_index(stack) == 0);

// Max at end
stack = [1, 5, 8, 99];
assert(find_max_index(stack) == 3);

// Max in middle
stack = [8, 99, 12, 5];
assert(find_max_index(stack) == 1);
```

### Test 2: Edge Cases

```c
// Empty
assert(find_max_index(NULL) == -1);

// Single
stack = [42];
assert(find_max_index(stack) == 0);

// Two elements
stack = [5, 8];
assert(find_max_index(stack) == 1);
```

### Test 3: Duplicates

```c
// Multiple maximums
stack = [5, 9, 8, 9, 3];
assert(find_max_index(stack) == 1);  // First occurrence

// All same
stack = [7, 7, 7, 7];
assert(find_max_index(stack) == 0);  // First is max
```

### Test 4: Negative Numbers

```c
stack = [-5, -3, -8, -1, -10];
assert(find_max_index(stack) == 3);  // -1 at position 3

stack = [-1, -2, -3, -4, -5];
assert(find_max_index(stack) == 0);  // -1 at start
```

### Test 5: Large Stacks

```c
// 100 elements, max at various positions
stack = create_stack_with_max_at(0);
assert(find_max_index(stack) == 0);

stack = create_stack_with_max_at(50);
assert(find_max_index(stack) == 50);

stack = create_stack_with_max_at(99);
assert(find_max_index(stack) == 99);
```

### Test 6: Integration with find_max

```c
stack = [5, 8, 2, 9, 1, 7];

int max_val = find_max(stack);        // Should be 9
int max_idx = find_max_index(stack);  // Should be 3

// Verify they match
t_stack *temp = stack;
for (int i = 0; i < max_idx; i++)
    temp = temp->next;

assert(temp->value == max_val);  // Value at index should match
```

### Test 7: Complementary with find_min_index

```c
stack = [5, 8, 2, 9, 1, 7];

int min_idx = find_min_index(stack);  // Should be 4 (value 1)
int max_idx = find_max_index(stack);  // Should be 3 (value 9)

assert(min_idx != max_idx);  // Different positions
assert(min_idx >= 0 && max_idx >= 0);  // Both valid
```

---

## Summary

**What find_max_index Does:**
1. Finds the maximum value using find_max()
2. Traverses stack to find WHERE that maximum is located
3. Returns the position (0-based index) of the maximum
4. Critical for Turk algorithm target position calculations

**Key Characteristics:**
- ✅ Two-phase algorithm (find value, then find position)
- ✅ O(n) time complexity (two passes)
- ✅ O(1) space complexity
- ✅ Returns first occurrence if duplicates exist
- ✅ Returns -1 for error cases

**Critical Uses:**
- Target position calculation in Turk algorithm
- Determining where to insert elements larger than all in stack
- Cost calculation for rotating maximum to specific position
- Algorithm decisions based on maximum's location

**Remember:**
- Always validate for NULL stack
- Use 0-based positioning (start at 0)
- Return position, not value
- Check equality (==), not inequality
- Advance pointer in loop to avoid infinite loop

**Turk Algorithm Insight:**
```
When element in B is larger than all in A:
→ Its target position = position of current max in A
→ find_max_index provides this critical information
→ Enables efficient insertion of new maximum elements

This function is the key to handling "larger than max" cases!
```

---

## Location in Project

**File:** `srcs/stack_find.c` or `srcs/position.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 1.3 (Advanced Stack Utilities)

---

## Related Functions

- [find_max](find_max.md) - Finds maximum value (used by this function)
- [find_min_index](find_min_index.md) - Finds position of minimum (parallel function)
- [find_min](find_min.md) - Finds minimum value
- [find_target_position](find_target_position.md) - Uses find_max_index for target calculation
- [calculate_cost](calculate_cost.md) - Uses positions for cost calculation
- [assign_position](assign_position.md) - Different position assignment (sequential)

---

*Knowing WHERE the maximum is located enables the Turk algorithm to efficiently handle elements that are larger than all existing elements in the target stack!*
