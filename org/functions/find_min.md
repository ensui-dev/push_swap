# find_min - Find Minimum Value in Stack

## Function Signature

```c
int find_min(t_stack *stack)
```

**Return type:** `int` - The minimum value found in the stack
**Parameter:** `t_stack *stack` - Pointer to the head of the stack to search

---

## Purpose & Use Case

`find_min` is a **search function** that traverses the entire stack to find and return the **smallest value** present. This is a fundamental utility function used extensively throughout the push_swap project for decision-making, positioning, and sorting strategies.

### When You'll Use It

You'll call `find_min` whenever you need to:
1. **Final positioning** - Rotate the minimum value to the top at the end of sorting
2. **Small sorting algorithms** - Identify the smallest element in sort_three, sort_four, sort_five
3. **Cost calculations** - Determine optimal moves based on minimum values
4. **Algorithm decisions** - Choose strategies based on where the min is located
5. **Validation** - Verify sorting correctness

### Why This Matters

**The minimum value is special in push_swap:**
```
Sorted stack ALWAYS starts with the minimum:
✅ Correct:  [1, 2, 3, 4, 5]  ← min on top
❌ Wrong:    [2, 3, 4, 5, 1]  ← not sorted

Therefore:
- Finding min is constant requirement
- Final step always rotates min to top
- Small sorts heavily rely on min position
```

### Real-World Analogy

**Finding the shortest person in a line:**
```
Line of people with heights:
[5'8", 6'2", 5'3", 5'10", 6'0"]

Walk through entire line, checking each person:
Current shortest: 5'8"
Check 6'2": No, 5'8" still shortest
Check 5'3": Yes! New shortest
Check 5'10": No, 5'3" still shortest
Check 6'0": No, 5'3" still shortest

Result: 5'3" is the minimum
```

---

## Deep Dive: How It Works

### The Linear Search Algorithm

**Concept:**
- Start with first value as "current minimum"
- Visit every node in the stack
- If you find a smaller value, update the minimum
- Return the smallest value found after checking all nodes

### Algorithm Visualization

**Stack Example:** [5, 8, 2, 9, 1, 7]

```
Step 1: Initialize
min = 5 (first value)
current = stack (pointing to 5)

Step 2: Check 5
min = 5
current value = 5
5 < 5? No
min stays 5

Step 3: Move to 8
current = current->next (now at 8)
current value = 8
8 < 5? No
min stays 5

Step 4: Move to 2
current = current->next (now at 2)
current value = 2
2 < 5? Yes! ← Found smaller
min = 2

Step 5: Move to 9
current = current->next (now at 9)
current value = 9
9 < 2? No
min stays 2

Step 6: Move to 1
current = current->next (now at 1)
current value = 1
1 < 2? Yes! ← Found even smaller
min = 1

Step 7: Move to 7
current = current->next (now at 7)
current value = 7
7 < 1? No
min stays 1

Step 8: End of stack
current = current->next = NULL
Traversal complete

Result: return 1
```

### Memory State During Search

```
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> [7] -> NULL

Iteration 1:
  current -> [5]
  min = 5

Iteration 2:
  current -> [8]
  min = 5  (no change)

Iteration 3:
  current -> [2]
  min = 2  (updated!)

Iteration 4:
  current -> [9]
  min = 2  (no change)

Iteration 5:
  current -> [1]
  min = 1  (updated!)

Iteration 6:
  current -> [7]
  min = 1  (no change)

Final: return 1
```

---

## Step-by-Step Implementation

### Step 1: Handle Empty Stack

**Validate input:**
```c
if (!stack)
    return (0);  // or INT_MAX, depending on implementation
```

**Why this matters:**
- NULL pointer would cause segmentation fault
- Need a sensible default for empty stack
- Some implementations return INT_MAX to indicate "no min found"
- Others return 0 (though 0 could be a valid minimum)

**Design decision:**
```
Option 1: Return 0
- Simple
- But 0 might be a valid minimum
- Can't distinguish "empty" from "min is 0"

Option 2: Return INT_MAX
- Clearly invalid as a real minimum
- Caller can check if result == INT_MAX
- Better for error detection ✅

Option 3: Return first value or special sentinel
- Depends on your design
```

### Step 2: Initialize Minimum to First Value

**Set starting point:**
```c
int min = stack->value;
```

**Why start with first value:**
```
Stack: [42, 5, 8, 2]

Start min = 42
- Valid starting point
- Guaranteed to exist (we checked !stack)
- Will be replaced if smaller value found
- If it's actually the minimum, it stays

Alternative (WRONG):
Start min = 0 or min = INT_MIN
- What if all values are negative?
- What if minimum is actually 5 but we start at 0?
- Doesn't work correctly ❌
```

### Step 3: Traverse the Stack

**Move to next node:**
```c
stack = stack->next;
```

**Why move before checking:**
```
We already captured the first value as min.
No need to compare min with itself.
Start checking from second node onward.

Stack: [5] -> [8] -> [2] -> NULL
       ^
       Already saved as min=5

Move to: [8] -> [2] -> NULL
         ^
         Start checking here
```

### Step 4: Compare Each Value

**Loop through remaining nodes:**
```c
while (stack)
{
    if (stack->value < min)
        min = stack->value;
    stack = stack->next;
}
```

**Comparison logic:**
```
For each node:
1. Is current value < current min?
2. YES: Update min to current value
3. NO: Keep existing min
4. Move to next node
5. Repeat until NULL
```

**Why < and not ≤:**
```
If stack->value == min:
- No need to update (already equal)
- < is sufficient
- Slightly more efficient (fewer assignments)

Example:
min = 5
Current value = 5
5 < 5? No, skip update ✅
5 ≤ 5? Yes, but update to same value (unnecessary)
```

### Step 5: Return the Minimum

**Final step:**
```c
return (min);
```

**At this point:**
- We've checked every single node
- `min` holds the smallest value found
- Safe to return to caller

---

## Complete Algorithm Pseudocode

```
FUNCTION find_min(stack):
    // Step 1: Validate input
    IF stack is NULL:
        RETURN INT_MAX  // or 0, based on design

    // Step 2: Initialize min to first value
    min = stack.value

    // Step 3: Move to second node
    stack = stack.next

    // Step 4: Traverse and compare
    WHILE stack is not NULL:
        IF stack.value < min:
            min = stack.value
        stack = stack.next

    // Step 5: Return result
    RETURN min
END FUNCTION
```

---

## Visual Execution Trace

### Example: Finding Min in [5, 8, 2, 9, 1, 7]

```
Initial State:
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> [7] -> NULL

Call: min_val = find_min(stack)

Step 1: Validate
stack != NULL ✅ Continue

Step 2: Initialize
min = 5 (first node's value)

Step 3: Move to next
stack now points to [8]

Step 4: Loop Iteration 1
Current node: [8]
Compare: 8 < 5? No
min = 5 (unchanged)
Move to next: [2]

Step 4: Loop Iteration 2
Current node: [2]
Compare: 2 < 5? Yes! ✅
min = 2 (updated)
Move to next: [9]

Step 4: Loop Iteration 3
Current node: [9]
Compare: 9 < 2? No
min = 2 (unchanged)
Move to next: [1]

Step 4: Loop Iteration 4
Current node: [1]
Compare: 1 < 2? Yes! ✅
min = 1 (updated)
Move to next: [7]

Step 4: Loop Iteration 5
Current node: [7]
Compare: 7 < 1? No
min = 1 (unchanged)
Move to next: NULL

Step 4: Loop exits (stack is NULL)

Step 5: Return
return 1

Result: min_val = 1 ✅
```

---

## Edge Cases

### Case 1: Empty Stack

```c
t_stack *stack = NULL;

int min = find_min(stack);

// Result: 0 or INT_MAX (depends on implementation)
// No crash ✅
```

### Case 2: Single Element

```c
// Stack: [42] -> NULL

int min = find_min(stack);

// Process:
// min = 42
// stack = stack->next = NULL
// Loop never executes
// return 42

// Result: 42 ✅
```

### Case 3: All Same Values

```c
// Stack: [5, 5, 5, 5, 5]

int min = find_min(stack);

// Process:
// min = 5
// Check 5: 5 < 5? No
// Check 5: 5 < 5? No
// Check 5: 5 < 5? No
// Check 5: 5 < 5? No
// return 5

// Result: 5 ✅
```

### Case 4: Minimum is First

```c
// Stack: [1, 5, 8, 9, 12]

int min = find_min(stack);

// Process:
// min = 1
// Check 5: 5 < 1? No
// Check 8: 8 < 1? No
// Check 9: 9 < 1? No
// Check 12: 12 < 1? No
// return 1

// Result: 1 ✅
// Still had to check all nodes!
```

### Case 5: Minimum is Last

```c
// Stack: [9, 8, 5, 3, 1]

int min = find_min(stack);

// Process:
// min = 9
// Check 8: 8 < 9? Yes → min = 8
// Check 5: 5 < 8? Yes → min = 5
// Check 3: 3 < 5? Yes → min = 3
// Check 1: 1 < 3? Yes → min = 1
// return 1

// Result: 1 ✅
// Min updated at every step (worst case for updates)
```

### Case 6: Negative Numbers

```c
// Stack: [5, -3, 8, -10, 2]

int min = find_min(stack);

// Process:
// min = 5
// Check -3: -3 < 5? Yes → min = -3
// Check 8: 8 < -3? No
// Check -10: -10 < -3? Yes → min = -10
// Check 2: 2 < -10? No
// return -10

// Result: -10 ✅
// Handles negatives correctly
```

### Case 7: INT_MIN Present

```c
// Stack: [0, -5, INT_MIN, 10]

int min = find_min(stack);

// Result: INT_MIN (-2147483648)
// Correctly handles minimum possible int
```

### Case 8: Large Stack

```c
// Stack with 500 elements: [387, 42, 956, ..., 1, ...]

int min = find_min(stack);

// Must check all 500 elements
// O(n) time complexity
// Eventually finds 1
```

---

## Time & Space Complexity

### Time Complexity: **O(n)** - Linear Time

**Operations:**
- Must visit every single node exactly once
- Cannot optimize or skip nodes
- No way to know where minimum is without checking all

**Formula:**
```
n = number of nodes
Operations = n comparisons + n pointer moves
Total = 2n = O(n)
```

**Why can't we do better?**
```
❌ Can't use binary search - stack isn't sorted
❌ Can't use hashing - we need the minimum value, not existence check
❌ Can't stop early - min could be the last element
✅ Must check every element - O(n) is optimal for this problem
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
Variables:
- int min (4 bytes)
- t_stack *stack (8 bytes on 64-bit)

Total: 12 bytes, regardless of stack size
No additional data structures
No recursion (no stack frames)
No allocations

Space = O(1) ✅
```

### Performance Characteristics

```
Best case: O(n)    - Min is first, but still check all
Average case: O(n) - Must check all elements
Worst case: O(n)   - Must check all elements

No difference in time complexity for different cases!
Always O(n) because we always traverse entire stack.
```

---

## Relationship with Other Functions

### Works With find_max

```c
int min = find_min(stack);
int max = find_max(stack);
int range = max - min;

// Useful for:
// - Determining value distribution
// - Chunk size calculations
// - Algorithm selection
```

### Used in find_min_index

```c
int find_min_index(t_stack *stack)
{
    int min_value = find_min(stack);  // ← Uses find_min!

    // Then finds position of min_value
    // ...
}
```

### Critical for final_rotate

```c
void final_rotate(t_stack **stack_a)
{
    int min = find_min(*stack_a);  // ← Find the minimum

    // Rotate until min is on top
    while ((*stack_a)->value != min)
        ra(stack_a, 1);
}
```

### Used in Small Sorts

```c
void sort_three(t_stack **stack)
{
    int min = find_min(*stack);  // ← Identify minimum

    // Use min to determine which operations to perform
    if ((*stack)->value == min)
        // Min already on top...
    else if ((*stack)->next->value == min)
        // Min is in middle...
    // ...
}
```

---

## Integration with Push_swap

### Scenario: Final Positioning

```c
// After all sorting, stack A might look like:
A: [3, 4, 5, 1, 2]
// Sorted? No - min (1) not on top

int min = find_min(A);  // Returns 1

// Find position of 1
int pos = 0;
t_stack *tmp = A;
while (tmp->value != min)
{
    pos++;
    tmp = tmp->next;
}
// pos = 3 (1 is at index 3)

// Rotate to bring 1 to top
while (pos--)
    ra(&A, 1);

// Result: [1, 2, 3, 4, 5] ✅ Fully sorted!
```

### Scenario: Sort Three Decision

```c
// Stack: [3, 1, 2]
int min = find_min(stack);  // Returns 1

// Decision logic:
if (stack->value == min)
    // 1 is on top, handle differently
else if (stack->next->value == min)
    // 1 is in middle, swap first
    sa(&stack, 1);
else
    // 1 is at bottom, rotate first
    rra(&stack, 1);
```

### Scenario: Chunk Calculation

```c
int min = find_min(stack_a);
int max = find_max(stack_a);
int range = max - min;
int chunk_size = range / 5;  // Divide into 5 chunks

// Use chunks for Turk algorithm partitioning
```

---

## 42 Norm Considerations

### Function Structure

```c
int	find_min(t_stack *stack)
{
	int	min;

	if (!stack)
		return (INT_MAX);  // or 0
	min = stack->value;
	stack = stack->next;
	while (stack)
	{
		if (stack->value < min)
			min = stack->value;
		stack = stack->next;
	}
	return (min);
}
```

**Norm compliance:**
- ✅ Under 25 lines
- ✅ Single return point at end
- ✅ Only 1 variable (min)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Function does one thing: finds minimum

### Variable Naming

```c
✅ GOOD: min, stack
❌ BAD: minimum_value, current_stack_pointer
```

Keep names short but clear!

---

## Common Mistakes

### ❌ Mistake 1: Not Handling NULL

```c
// WRONG
int find_min(t_stack *stack)
{
    int min = stack->value;  // SEGFAULT if stack is NULL!
}
```

**✅ Correct:**
```c
if (!stack)
    return (INT_MAX);
int min = stack->value;  // Safe now
```

### ❌ Mistake 2: Starting Min at 0

```c
// WRONG
int min = 0;
while (stack)
{
    if (stack->value < min)
        min = stack->value;
    stack = stack->next;
}
// If all values are positive, returns 0 incorrectly!
```

**✅ Correct:**
```c
int min = stack->value;  // Start with actual first value
stack = stack->next;      // Then check rest
```

### ❌ Mistake 3: Using ≤ Instead of <

```c
// WRONG (but works, just inefficient)
if (stack->value <= min)
    min = stack->value;
// Unnecessary assignment when equal
```

**✅ Better:**
```c
if (stack->value < min)
    min = stack->value;
// Only update when strictly smaller
```

### ❌ Mistake 4: Not Advancing Pointer

```c
// WRONG - Infinite loop!
while (stack)
{
    if (stack->value < min)
        min = stack->value;
    // Forgot: stack = stack->next;
}
```

**✅ Correct:**
```c
while (stack)
{
    if (stack->value < min)
        min = stack->value;
    stack = stack->next;  // CRITICAL!
}
```

### ❌ Mistake 5: Checking Wrong Field

```c
// WRONG
if (stack->index < min)  // Comparing index, not value!
```

**✅ Correct:**
```c
if (stack->value < min)  // Compare value field
```

---

## Testing Strategy

### Test 1: Normal Cases

```c
// Test ascending
stack = [1, 2, 3, 4, 5];
assert(find_min(stack) == 1);

// Test descending
stack = [5, 4, 3, 2, 1];
assert(find_min(stack) == 1);

// Test random
stack = [3, 1, 4, 1, 5, 9, 2, 6];
assert(find_min(stack) == 1);
```

### Test 2: Edge Cases

```c
// Empty
assert(find_min(NULL) == INT_MAX);  // or 0

// Single
stack = [42];
assert(find_min(stack) == 42);

// Two elements
stack = [5, 3];
assert(find_min(stack) == 3);

// All same
stack = [7, 7, 7, 7];
assert(find_min(stack) == 7);
```

### Test 3: Negative Numbers

```c
stack = [5, -3, 0, -10, 2];
assert(find_min(stack) == -10);

stack = [-1, -2, -3, -4, -5];
assert(find_min(stack) == -5);

stack = [INT_MIN, 0, INT_MAX];
assert(find_min(stack) == INT_MIN);
```

### Test 4: Position Variations

```c
// Min at start
stack = [1, 5, 8, 12];
assert(find_min(stack) == 1);

// Min at end
stack = [12, 8, 5, 1];
assert(find_min(stack) == 1);

// Min in middle
stack = [8, 3, 12, 5];
assert(find_min(stack) == 3);
```

### Test 5: Large Stack

```c
// 100 elements, min is 1
stack = create_random_stack(100);
assert(find_min(stack) == 1);
```

---

## Summary

**What find_min Does:**
1. Traverses entire stack once (O(n))
2. Keeps track of smallest value seen
3. Returns the minimum value found
4. Used extensively in sorting algorithms

**Key Characteristics:**
- ✅ Simple linear search
- ✅ Always O(n) time
- ✅ O(1) space
- ✅ Must check every element
- ✅ Cannot be optimized further for unsorted stack

**Critical Uses:**
- Final rotation to position minimum on top
- Small sorting algorithm decision-making
- Chunk and range calculations
- Validation and debugging

**Remember:**
- Always validate for NULL stack
- Start min with first actual value
- Use < not ≤ for comparison
- Must traverse entire stack
- No shortcuts possible for unsorted data

---

## Location in Project

**File:** `srcs/stack_utils.c` or `srcs/find_utils.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 1.3 (Advanced Stack Utilities)

---

## Related Functions

- [find_max](find_max.md) - Find maximum value (opposite operation)
- [find_min_index](find_min_index.md) - Find position of minimum
- [find_max_index](find_max_index.md) - Find position of maximum
- [final_rotate](final_rotate.md) - Uses find_min to position stack
- [sort_three](sort_three.md) - Uses find_min for decision logic
- [is_sorted](is_sorted.md) - Validation function

---

*Finding the minimum is fundamental - master this and you understand the core of push_swap positioning!*
