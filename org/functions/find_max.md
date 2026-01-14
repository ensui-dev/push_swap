# find_max - Find Maximum Value in Stack

## Function Signature

```c
int find_max(t_stack *stack)
```

**Return type:** `int` - The maximum value found in the stack
**Parameter:** `t_stack *stack` - Pointer to the head of the stack to search

---

## Purpose & Use Case

`find_max` is a **search function** that traverses the entire stack to find and return the **largest value** present. This is the complementary function to `find_min`, providing essential utility for sorting strategies, range calculations, and algorithm decision-making.

### When You'll Use It

You'll call `find_max` whenever you need to:
1. **Range calculations** - Determine the spread of values (max - min) for chunk sizing
2. **Index normalization** - Find the highest value when assigning normalized indices
3. **Algorithm selection** - Choose sorting strategy based on value distribution
4. **Target position calculations** - Determine where to place elements in Turk algorithm
5. **Validation and debugging** - Verify correctness of operations

### Why This Matters

**The maximum value is crucial for:**
```
Understanding your data range:
min = 5, max = 500
range = 495  ← Large range might need different strategy

min = 1, max = 5
range = 4    ← Small range, simple sorting works

Chunk calculations:
chunks = (max - min) / number_of_chunks
This determines how you partition the data for optimization
```

### Real-World Analogy

**Finding the tallest person in a line:**
```
Line of people with heights:
[5'8", 6'2", 5'3", 5'10", 6'0"]

Walk through entire line, checking each person:
Current tallest: 5'8"
Check 6'2": Yes! New tallest
Check 5'3": No, 6'2" still tallest
Check 5'10": No, 6'2" still tallest
Check 6'0": No, 6'2" still tallest

Result: 6'2" is the maximum
```

---

## Deep Dive: How It Works

### The Linear Search Algorithm

**Concept:**
- Start with first value as "current maximum"
- Visit every node in the stack
- If you find a larger value, update the maximum
- Return the largest value found after checking all nodes

### Algorithm Visualization

**Stack Example:** [5, 8, 2, 9, 1, 7]

```
Step 1: Initialize
max = 5 (first value)
current = stack (pointing to 5)

Step 2: Check 5
max = 5
current value = 5
5 > 5? No
max stays 5

Step 3: Move to 8
current = current->next (now at 8)
current value = 8
8 > 5? Yes! ← Found larger
max = 8

Step 4: Move to 2
current = current->next (now at 2)
current value = 2
2 > 8? No
max stays 8

Step 5: Move to 9
current = current->next (now at 9)
current value = 9
9 > 8? Yes! ← Found even larger
max = 9

Step 6: Move to 1
current = current->next (now at 1)
current value = 1
1 > 9? No
max stays 9

Step 7: Move to 7
current = current->next (now at 7)
current value = 7
7 > 9? No
max stays 9

Step 8: End of stack
current = current->next = NULL
Traversal complete

Result: return 9
```

### Memory State During Search

```
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> [7] -> NULL

Iteration 1:
  current -> [5]
  max = 5

Iteration 2:
  current -> [8]
  max = 8  (updated!)

Iteration 3:
  current -> [2]
  max = 8  (no change)

Iteration 4:
  current -> [9]
  max = 9  (updated!)

Iteration 5:
  current -> [1]
  max = 9  (no change)

Iteration 6:
  current -> [7]
  max = 9  (no change)

Final: return 9
```

---

## Step-by-Step Implementation

### Step 1: Handle Empty Stack

**Validate input:**
```c
if (!stack)
    return (0);  // or INT_MIN, depending on implementation
```

**Why this matters:**
- NULL pointer would cause segmentation fault
- Need a sensible default for empty stack
- Some implementations return INT_MIN to indicate "no max found"
- Others return 0 (though 0 could be a valid maximum)

**Design decision:**
```
Option 1: Return 0
- Simple
- But 0 might be a valid maximum
- Can't distinguish "empty" from "max is 0"

Option 2: Return INT_MIN
- Clearly invalid as a real maximum
- Caller can check if result == INT_MIN
- Better for error detection ✅

Option 3: Return first value or special sentinel
- Depends on your design
```

### Step 2: Initialize Maximum to First Value

**Set starting point:**
```c
int max = stack->value;
```

**Why start with first value:**
```
Stack: [42, 5, 8, 52]

Start max = 42
- Valid starting point
- Guaranteed to exist (we checked !stack)
- Will be replaced if larger value found
- If it's actually the maximum, it stays

Alternative (WRONG):
Start max = 0 or max = INT_MAX
- What if all values are negative?
- What if maximum is actually -5 but we start at 0?
- Doesn't work correctly ❌
```

### Step 3: Traverse the Stack

**Move to next node:**
```c
stack = stack->next;
```

**Why move before checking:**
```
We already captured the first value as max.
No need to compare max with itself.
Start checking from second node onward.

Stack: [5] -> [8] -> [2] -> NULL
       ^
       Already saved as max=5

Move to: [8] -> [2] -> NULL
         ^
         Start checking here
```

### Step 4: Compare Each Value

**Loop through remaining nodes:**
```c
while (stack)
{
    if (stack->value > max)
        max = stack->value;
    stack = stack->next;
}
```

**Comparison logic:**
```
For each node:
1. Is current value > current max?
2. YES: Update max to current value
3. NO: Keep existing max
4. Move to next node
5. Repeat until NULL
```

**Why > and not ≥:**
```
If stack->value == max:
- No need to update (already equal)
- > is sufficient
- Slightly more efficient (fewer assignments)

Example:
max = 9
Current value = 9
9 > 9? No, skip update ✅
9 ≥ 9? Yes, but update to same value (unnecessary)
```

### Step 5: Return the Maximum

**Final step:**
```c
return (max);
```

**At this point:**
- We've checked every single node
- `max` holds the largest value found
- Safe to return to caller

---

## Complete Algorithm Pseudocode

```
FUNCTION find_max(stack):
    // Step 1: Validate input
    IF stack is NULL:
        RETURN INT_MIN  // or 0, based on design

    // Step 2: Initialize max to first value
    max = stack.value

    // Step 3: Move to second node
    stack = stack.next

    // Step 4: Traverse and compare
    WHILE stack is not NULL:
        IF stack.value > max:
            max = stack.value
        stack = stack.next

    // Step 5: Return result
    RETURN max
END FUNCTION
```

---

## Visual Execution Trace

### Example: Finding Max in [5, 8, 2, 9, 1, 7]

```
Initial State:
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> [7] -> NULL

Call: max_val = find_max(stack)

Step 1: Validate
stack != NULL ✅ Continue

Step 2: Initialize
max = 5 (first node's value)

Step 3: Move to next
stack now points to [8]

Step 4: Loop Iteration 1
Current node: [8]
Compare: 8 > 5? Yes! ✅
max = 8 (updated)
Move to next: [2]

Step 4: Loop Iteration 2
Current node: [2]
Compare: 2 > 8? No
max = 8 (unchanged)
Move to next: [9]

Step 4: Loop Iteration 3
Current node: [9]
Compare: 9 > 8? Yes! ✅
max = 9 (updated)
Move to next: [1]

Step 4: Loop Iteration 4
Current node: [1]
Compare: 1 > 9? No
max = 9 (unchanged)
Move to next: [7]

Step 4: Loop Iteration 5
Current node: [7]
Compare: 7 > 9? No
max = 9 (unchanged)
Move to next: NULL

Step 4: Loop exits (stack is NULL)

Step 5: Return
return 9

Result: max_val = 9 ✅
```

---

## Edge Cases

### Case 1: Empty Stack

```c
t_stack *stack = NULL;

int max = find_max(stack);

// Result: 0 or INT_MIN (depends on implementation)
// No crash ✅
```

### Case 2: Single Element

```c
// Stack: [42] -> NULL

int max = find_max(stack);

// Process:
// max = 42
// stack = stack->next = NULL
// Loop never executes
// return 42

// Result: 42 ✅
```

### Case 3: All Same Values

```c
// Stack: [5, 5, 5, 5, 5]

int max = find_max(stack);

// Process:
// max = 5
// Check 5: 5 > 5? No
// Check 5: 5 > 5? No
// Check 5: 5 > 5? No
// Check 5: 5 > 5? No
// return 5

// Result: 5 ✅
```

### Case 4: Maximum is First

```c
// Stack: [99, 5, 8, 9, 12]

int max = find_max(stack);

// Process:
// max = 99
// Check 5: 5 > 99? No
// Check 8: 8 > 99? No
// Check 9: 9 > 99? No
// Check 12: 12 > 99? No
// return 99

// Result: 99 ✅
// Still had to check all nodes!
```

### Case 5: Maximum is Last

```c
// Stack: [1, 3, 5, 8, 99]

int max = find_max(stack);

// Process:
// max = 1
// Check 3: 3 > 1? Yes → max = 3
// Check 5: 5 > 3? Yes → max = 5
// Check 8: 8 > 5? Yes → max = 8
// Check 99: 99 > 8? Yes → max = 99
// return 99

// Result: 99 ✅
// Max updated at every step (worst case for updates)
```

### Case 6: Negative Numbers

```c
// Stack: [-5, -3, -8, -10, -2]

int max = find_max(stack);

// Process:
// max = -5
// Check -3: -3 > -5? Yes → max = -3
// Check -8: -8 > -3? No
// Check -10: -10 > -3? No
// Check -2: -2 > -3? Yes → max = -2
// return -2

// Result: -2 ✅
// Handles negatives correctly
```

### Case 7: INT_MAX Present

```c
// Stack: [0, 5, INT_MAX, 10]

int max = find_max(stack);

// Result: INT_MAX (2147483647)
// Correctly handles maximum possible int
```

### Case 8: Mixed Positive and Negative

```c
// Stack: [-100, 50, -20, 75, -5]

int max = find_max(stack);

// Process:
// max = -100
// Check 50: 50 > -100? Yes → max = 50
// Check -20: -20 > 50? No
// Check 75: 75 > 50? Yes → max = 75
// Check -5: -5 > 75? No
// return 75

// Result: 75 ✅
```

---

## Time & Space Complexity

### Time Complexity: **O(n)** - Linear Time

**Operations:**
- Must visit every single node exactly once
- Cannot optimize or skip nodes
- No way to know where maximum is without checking all

**Formula:**
```
n = number of nodes
Operations = n comparisons + n pointer moves
Total = 2n = O(n)
```

**Why can't we do better?**
```
❌ Can't use binary search - stack isn't sorted
❌ Can't use hashing - we need the maximum value, not existence check
❌ Can't stop early - max could be the last element
✅ Must check every element - O(n) is optimal for this problem
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
Variables:
- int max (4 bytes)
- t_stack *stack (8 bytes on 64-bit)

Total: 12 bytes, regardless of stack size
No additional data structures
No recursion (no stack frames)
No allocations

Space = O(1) ✅
```

### Performance Characteristics

```
Best case: O(n)    - Max is first, but still check all
Average case: O(n) - Must check all elements
Worst case: O(n)   - Must check all elements

No difference in time complexity for different cases!
Always O(n) because we always traverse entire stack.
```

---

## Relationship with Other Functions

### Works With find_min

```c
int min = find_min(stack);
int max = find_max(stack);
int range = max - min;

// Useful for:
// - Determining value distribution
// - Chunk size calculations
// - Algorithm selection

// Example:
// Stack: [5, 15, 8, 20, 12]
// min = 5, max = 20
// range = 15
// This tells us the spread of values
```

### Used in Index Normalization

```c
void assign_index(t_stack *stack_a)
{
    int max = find_max(stack_a);  // ← Uses find_max!

    // Use max to determine index assignments
    // Assign indices 0 to (max) based on relative values
    // ...
}
```

### Critical for Chunk Calculations

```c
void push_chunks_to_b(t_stack **a, t_stack **b, int size)
{
    int min = find_min(*a);
    int max = find_max(*a);  // ← Find the maximum
    int range = max - min;
    int chunk_size = range / 5;  // Divide into 5 chunks

    // Use chunk_size to partition data
    // ...
}
```

### Used in find_max_index

```c
int find_max_index(t_stack *stack)
{
    int max_value = find_max(stack);  // ← Uses find_max!

    // Then finds position of max_value
    // ...
}
```

---

## Integration with Push_swap

### Scenario: Chunk-Based Sorting

```c
// Stack A: [42, 15, 73, 8, 56, 91, 23, 67]

int min = find_min(stack_a);  // Returns 8
int max = find_max(stack_a);  // Returns 91
int range = max - min;         // 91 - 8 = 83

// Divide into 3 chunks
int chunk_size = range / 3;    // 83 / 3 = 27

// Define chunk boundaries:
// Chunk 1: 8 to 35 (8 + 27)
// Chunk 2: 36 to 63 (35 + 28)
// Chunk 3: 64 to 91 (63 + 28)

// Push elements to B based on chunks
// This optimizes the sorting process
```

### Scenario: Algorithm Selection

```c
int size = stack_size(stack_a);
int max = find_max(stack_a);
int min = find_min(stack_a);

if (size <= 3)
    sort_three(&stack_a);
else if (size <= 5)
    sort_five(&stack_a, &stack_b);
else
{
    // Use range to determine strategy
    int range = max - min;
    if (range < 100)
        use_simple_strategy();
    else
        use_chunk_strategy();
}
```

### Scenario: Target Position Calculation

```c
int find_target_position(t_stack *stack_a, int index_b)
{
    int max_index = find_max_index(stack_a);  // Uses find_max internally

    // If index_b is larger than all in A
    // Target position is where max_index is
    // ...
}
```

---

## 42 Norm Considerations

### Function Structure

```c
int	find_max(t_stack *stack)
{
	int	max;

	if (!stack)
		return (INT_MIN);  // or 0
	max = stack->value;
	stack = stack->next;
	while (stack)
	{
		if (stack->value > max)
			max = stack->value;
		stack = stack->next;
	}
	return (max);
}
```

**Norm compliance:**
- ✅ Under 25 lines
- ✅ Single return point at end
- ✅ Only 1 variable (max)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Function does one thing: finds maximum

### Variable Naming

```c
✅ GOOD: max, stack
❌ BAD: maximum_value, current_stack_pointer
```

Keep names short but clear!

---

## Common Mistakes

### Mistake 1: Not Handling NULL

```c
// ❌ WRONG
int find_max(t_stack *stack)
{
    int max = stack->value;  // SEGFAULT if stack is NULL!
}
```

**✅ Correct:**
```c
if (!stack)
    return (INT_MIN);
int max = stack->value;  // Safe now
```

### Mistake 2: Starting Max at 0

```c
// ❌ WRONG
int max = 0;
while (stack)
{
    if (stack->value > max)
        max = stack->value;
    stack = stack->next;
}
// If all values are negative, returns 0 incorrectly!
// Stack: [-5, -3, -8]
// Would return 0 instead of -3
```

**✅ Correct:**
```c
int max = stack->value;  // Start with actual first value
stack = stack->next;      // Then check rest
```

### Mistake 3: Using ≥ Instead of >

```c
// ❌ WRONG (but works, just inefficient)
if (stack->value >= max)
    max = stack->value;
// Unnecessary assignment when equal
```

**✅ Better:**
```c
if (stack->value > max)
    max = stack->value;
// Only update when strictly larger
```

### Mistake 4: Not Advancing Pointer

```c
// ❌ WRONG - Infinite loop!
while (stack)
{
    if (stack->value > max)
        max = stack->value;
    // Forgot: stack = stack->next;
}
```

**✅ Correct:**
```c
while (stack)
{
    if (stack->value > max)
        max = stack->value;
    stack = stack->next;  // CRITICAL!
}
```

### Mistake 5: Confusing with find_min

```c
// ❌ WRONG - Using < instead of >
if (stack->value < max)  // This finds min, not max!
    max = stack->value;
```

**✅ Correct:**
```c
if (stack->value > max)  // Find maximum
    max = stack->value;
```

---

## Testing Strategy

### Test 1: Normal Cases

```c
// Test ascending
stack = [1, 2, 3, 4, 5];
assert(find_max(stack) == 5);

// Test descending
stack = [5, 4, 3, 2, 1];
assert(find_max(stack) == 5);

// Test random
stack = [3, 1, 4, 1, 5, 9, 2, 6];
assert(find_max(stack) == 9);
```

### Test 2: Edge Cases

```c
// Empty
assert(find_max(NULL) == INT_MIN);  // or 0

// Single
stack = [42];
assert(find_max(stack) == 42);

// Two elements
stack = [5, 3];
assert(find_max(stack) == 5);

// All same
stack = [7, 7, 7, 7];
assert(find_max(stack) == 7);
```

### Test 3: Negative Numbers

```c
stack = [5, -3, 0, -10, 2];
assert(find_max(stack) == 5);

stack = [-1, -2, -3, -4, -5];
assert(find_max(stack) == -1);

stack = [INT_MIN, 0, INT_MAX];
assert(find_max(stack) == INT_MAX);
```

### Test 4: Position Variations

```c
// Max at start
stack = [99, 5, 8, 12];
assert(find_max(stack) == 99);

// Max at end
stack = [12, 8, 5, 99];
assert(find_max(stack) == 99);

// Max in middle
stack = [8, 99, 12, 5];
assert(find_max(stack) == 99);
```

### Test 5: Large Stack

```c
// 100 elements, max is 999
stack = create_random_stack(100);
assert(find_max(stack) == 999);
```

### Test 6: Complementary with find_min

```c
stack = [5, 8, 2, 9, 1, 7];
int min = find_min(stack);  // Should be 1
int max = find_max(stack);  // Should be 9
int range = max - min;      // Should be 8
assert(range == 8);
assert(min < max);  // Sanity check
```

---

## Summary

**What find_max Does:**
1. Traverses entire stack once (O(n))
2. Keeps track of largest value seen
3. Returns the maximum value found
4. Used extensively in range calculations and algorithm decisions

**Key Characteristics:**
- ✅ Simple linear search
- ✅ Always O(n) time
- ✅ O(1) space
- ✅ Must check every element
- ✅ Cannot be optimized further for unsorted stack

**Critical Uses:**
- Range calculation (max - min) for chunk sizing
- Index normalization and value distribution analysis
- Algorithm selection based on data spread
- Target position calculations in sorting
- Validation and debugging

**Remember:**
- Always validate for NULL stack
- Start max with first actual value
- Use > not ≥ for comparison
- Must traverse entire stack
- No shortcuts possible for unsorted data

**Comparison with find_min:**
```
find_min: Uses < to find smallest
find_max: Uses > to find largest

Both are O(n) time, O(1) space
Both must traverse entire stack
Both are fundamental utility functions
Together they define the data range
```

---

## Location in Project

**File:** `srcs/stack_find.c` or `srcs/stack_utils.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 1.3 (Advanced Stack Utilities)

---

## Related Functions

- [find_min](find_min.md) - Find minimum value (complementary operation)
- [find_max_index](find_max_index.md) - Find position of maximum
- [find_min_index](find_min_index.md) - Find position of minimum
- [assign_index](assign_index.md) - Uses max for index normalization
- [push_chunks_to_b](push_chunks_to_b.md) - Uses max for chunk calculations
- [is_sorted](is_sorted.md) - Validation function

---

*Finding the maximum is essential for understanding your data range - master this alongside find_min for complete stack analysis!*
