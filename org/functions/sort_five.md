# sort_five - Sort Exactly Five Elements

## Function Signature

```c
void sort_five(t_stack **stack_a, t_stack **stack_b)
```

**Return type:** `void` - Modifies stacks A and B in place
**Parameters:**
- `t_stack **stack_a` - Double pointer to the head of stack A
- `t_stack **stack_b` - Double pointer to the head of stack B (initially empty)

---

## Purpose & Use Case

`sort_five` is a **specialized sorting function** that sorts exactly 5 elements by reducing the problem to sorting 3 elements. The strategy: isolate the two smallest elements by pushing them to stack B, sort the remaining 3 in stack A using `sort_three`, then push the small elements back in order.

### When You'll Use It

You'll call `sort_five` whenever:
1. **Stack has exactly 5 elements** - Detected by `stack_size(stack) == 5`
2. **Called by sort_small** - Router function delegates to sort_five
3. **Maximum small sort** - Largest size for hardcoded optimization
4. **Efficiency demonstration** - Shows reduction strategy at scale

### Why This Strategy Works

**Double reduction approach:**
```
5 elements → Reduce to 3 elements
[5, 2, 1, 4, 3]

Step 1: Find and isolate TWO smallest (1, 2)
Move 1 and 2 to B: [5, 4, 3] | [2, 1]

Step 2: Sort remaining 3 using sort_three
After sort_three: [3, 4, 5] | [2, 1]

Step 3: Push both back (in order)
After pa, pa: [1, 2, 3, 4, 5] | []

Result: SORTED! ✅

Maximum operations: ~8-12 operations
Still very efficient for 5 elements!
```

### Real-World Analogy

**Organizing five books by height:**
```
Books: [Very Tall, Medium-Small, Shortest, Tall, Medium]

Strategy:
1. Remove the TWO shortest books (set aside in order)
2. Organize remaining 3 books
3. Place the two shortest books back at the front (in order)

Result: [Shortest, Medium-Small, Medium, Tall, Very Tall]

Same concept for sorting 5 numbers!
```

---

## Deep Dive: How It Works

### The Four-Phase Algorithm

**Phase 1: Push Minimum to B**
- Find minimum using `find_min_index`
- Rotate to bring minimum to top
- Push minimum to stack B

**Phase 2: Push Second Minimum to B**
- Find new minimum in stack A (which is the second smallest overall)
- Rotate to bring it to top
- Push to stack B (now B has two smallest elements)

**Phase 3: Sort Remaining Three**
- Stack A now has 3 largest elements
- Call `sort_three` to sort them optimally
- Stack A is now sorted (but missing two smallest)

**Phase 4: Restore Both Small Elements**
- Push from B to A twice
- Since we pushed min first, then second-min, they're in reverse order in B
- First pa brings second-min to A
- Second pa brings min to A
- Final result: fully sorted 5 elements

### Algorithm Visualization

```
Initial: A: [5, 2, 1, 4, 3]  B: []

Phase 1: Find and move minimum (1)
min_index = 2 (value 1 at position 2)
Rotate to top: rra, rra
A: [1, 5, 2, 4, 3]  B: []
Push to B: pb
A: [5, 2, 4, 3]  B: [1]

Phase 2: Find and move second minimum (2)
min_index = 1 (value 2 at position 1)
Rotate to top: sa (or ra once)
A: [2, 5, 4, 3]  B: [1]
Push to B: pb
A: [5, 4, 3]  B: [2, 1]
                   ^  ^
                   second-min, min

Phase 3: Sort remaining 3
sort_three(A)
A: [3, 4, 5]  B: [2, 1]

Phase 4: Push both back
pa: A: [2, 3, 4, 5]  B: [1]
pa: A: [1, 2, 3, 4, 5]  B: []

SORTED! ✅
```

---

## Step-by-Step Implementation

### Step 1: Validate Input (DEFENSIVE)

```c
if (!stack_a || !stack_b || !*stack_a)
    return;
if (stack_size(*stack_a) < 5)
    return;
```

**Defensive checks:**
```
!stack_a: Double pointer for stack A is NULL → Cannot dereference (CRITICAL)
!stack_b: Double pointer for stack B is NULL → pb will crash (CRITICAL)
!*stack_a: Stack A is empty → Nothing to sort (CRITICAL)
size < 5: Not enough elements → Algorithm requires exactly 5 (MEDIUM)

These checks prevent SEGFAULT and ensure algorithm preconditions are met.
```

**Defensive Priority:** CRITICAL - Must validate before any operation

### Step 2: Find and Push First Minimum

```c
int min_index = find_min_index(*stack_a);

// Bring to top using shortest path
if (min_index == 1)
    sa(stack_a, 1);
else if (min_index == 2)
{
    ra(stack_a, 1);
    ra(stack_a, 1);
}
else if (min_index == 3)
{
    rra(stack_a, 1);
    rra(stack_a, 1);
}
else if (min_index == 4)
    rra(stack_a, 1);

// Push to B
pb(stack_a, stack_b, 1);
```

**Position strategies:**
```
Position 0: Already on top → 0 operations
Position 1: sa → 1 operation
Position 2: ra, ra → 2 operations
Position 3: rra, rra → 2 operations
Position 4: rra → 1 operation

Choose shortest path for each position!
```

### Step 2: Find and Push Second Minimum

```c
// Now find minimum in remaining 4 elements (which is overall second-min)
min_index = find_min_index(*stack_a);

// Bring to top (same logic, but for 4 elements)
if (min_index == 1)
    sa(stack_a, 1);
else if (min_index == 2)
{
    rra(stack_a, 1);
    rra(stack_a, 1);
}
else if (min_index == 3)
    rra(stack_a, 1);

// Push to B
pb(stack_a, stack_b, 1);
```

**Result after Step 2:**
```
Stack A: 3 elements (all larger than both in B)
Stack B: 2 elements (the two smallest, second-min on top)

Now ready for sort_three!
```

### Step 3: Sort Remaining Three

```c
sort_three(stack_a);
```

**Delegation:**
```
Reuses sort_three function
Handles all permutations optimally
Maximum 2 operations
Stack A is now sorted (missing two smallest)
```

### Step 4: Push Both Back

```c
pa(stack_a, stack_b, 1);  // Push second-min
pa(stack_a, stack_b, 1);  // Push min
```

**Order matters:**
```
B before pa: [2, 1] (second-min on top)
             ^
After first pa: A: [2, ...], B: [1]
After second pa: A: [1, 2, ...]

This automatically places them in correct order!
```

---

## Complete Algorithm Pseudocode

### Basic Implementation (With Helper Function)
```
// Static helper function - rotates minimum to top
FUNCTION rotate_min_to_top(stack_a, size):
    min_idx = find_min_index(stack_a)

    IF min_idx == 1:
        sa(stack_a)
    ELSE IF min_idx == 2 AND size == 5:
        ra(stack_a)
        ra(stack_a)
    ELSE IF (min_idx == 3 AND size == 5) OR (min_idx == 2 AND size == 4):
        rra(stack_a)
        rra(stack_a)
    ELSE IF (min_idx == 4 AND size == 5) OR (min_idx == 3 AND size == 4):
        rra(stack_a)
    // Position 0: Already on top, no action needed
END FUNCTION

// Main sort_five function
FUNCTION sort_five(stack_a, stack_b):
    // Phase 1: Rotate first minimum to top and push to B
    rotate_min_to_top(stack_a, 5)
    pb(stack_a, stack_b)

    // Phase 2: Rotate second minimum to top and push to B
    rotate_min_to_top(stack_a, 4)
    pb(stack_a, stack_b)

    // Phase 3: Sort remaining 3 elements
    sort_three(stack_a)

    // Phase 4: Push both back to A
    pa(stack_a, stack_b)  // Push second-min
    pa(stack_a, stack_b)  // Push min

    // Done! Stack A is fully sorted
END FUNCTION
```

### Defensive Implementation (With Helper Function)
```
// Static helper function - trusts caller validation (layered defense)
FUNCTION rotate_min_to_top(stack_a, size):
    // No defensive checks here - sort_five validates before calling
    // find_min_index has its own NULL check (backup layer)

    min_idx = find_min_index(*stack_a)

    IF min_idx == 1:
        sa(stack_a, 1)  // sa has own defensive checks
    ELSE IF min_idx == 2 AND size == 5:
        ra(stack_a, 1)  // ra has own defensive checks
        ra(stack_a, 1)
    ELSE IF (min_idx == 3 AND size == 5) OR (min_idx == 2 AND size == 4):
        rra(stack_a, 1)  // rra has own defensive checks
        rra(stack_a, 1)
    ELSE IF (min_idx == 4 AND size == 5) OR (min_idx == 3 AND size == 4):
        rra(stack_a, 1)
    // Position 0: Already on top, no action needed
END FUNCTION

// Main sort_five function with full defensive checks
FUNCTION sort_five(stack_a, stack_b):
    // DEFENSIVE STEP 1: Validate stack A pointer (CRITICAL)
    IF stack_a is NULL:
        RETURN  // Cannot dereference NULL pointer

    // DEFENSIVE STEP 2: Validate stack B pointer (CRITICAL)
    IF stack_b is NULL:
        RETURN  // pb operation needs valid stack B

    // DEFENSIVE STEP 3: Validate dereferenced stack (CRITICAL)
    IF *stack_a is NULL:
        RETURN  // Empty stack, nothing to sort

    // DEFENSIVE STEP 4: Validate size (MEDIUM)
    IF stack_size(*stack_a) < 5:
        RETURN  // Algorithm requires exactly 5 elements

    // Phase 1: Rotate first minimum to top and push to B
    rotate_min_to_top(stack_a, 5)  // Helper trusts our validation
    pb(stack_a, stack_b, 1)        // pb has own defensive checks

    // Phase 2: Rotate second minimum to top and push to B
    rotate_min_to_top(stack_a, 4)  // Now 4 elements in A
    pb(stack_a, stack_b, 1)

    // Phase 3: Sort remaining 3 elements
    sort_three(stack_a)  // sort_three has own defensive checks

    // Phase 4: Push both back to A
    pa(stack_a, stack_b, 1)  // Push second-min (pa has own checks)
    pa(stack_a, stack_b, 1)  // Push min

    // Done! Stack A is fully sorted
END FUNCTION
```

---

## Visual Execution Trace

### Example: Sorting [5, 2, 1, 4, 3]

```
Initial State:
A: [5, 2, 1, 4, 3]  B: []
   [0][1][2][3][4]

Call: sort_five(&stack_a, &stack_b)

=== PHASE 1: First Minimum ===

Step 1: Find minimum
min_index = find_min_index(A) = 2 (value 1)

Step 2: Bring to top (position 2)
ra(&stack_a, 1)
After: A: [2, 1, 4, 3, 5]  B: []

ra(&stack_a, 1)
After: A: [1, 4, 3, 5, 2]  B: []
       ^
       Minimum on top!

Step 3: Push to B
pb(&stack_a, &stack_b, 1)
After: A: [4, 3, 5, 2]  B: [1]

=== PHASE 2: Second Minimum ===

Step 4: Find second minimum
min_index = find_min_index(A) = 3 (value 2)

Step 5: Bring to top (position 3 of 4 elements)
rra(&stack_a, 1)
After: A: [2, 4, 3, 5]  B: [1]
       ^
       Second-min on top!

Step 6: Push to B
pb(&stack_a, &stack_b, 1)
After: A: [4, 3, 5]  B: [2, 1]
                        ^  ^
                        2nd min

=== PHASE 3: Sort Remaining Three ===

Step 7: Sort 3 elements
sort_three(&stack_a)
(Internally executes optimal operations)
After: A: [3, 4, 5]  B: [2, 1]
          ^  ^  ^
          Sorted!

=== PHASE 4: Restore Both ===

Step 8: Push second-min back
pa(&stack_a, &stack_b, 1)
After: A: [2, 3, 4, 5]  B: [1]

Step 9: Push min back
pa(&stack_a, &stack_b, 1)
After: A: [1, 2, 3, 4, 5]  B: []
          ^  ^  ^  ^  ^
          FULLY SORTED! ✅

Total operations:
- ra (2) + pb (1) = 3 ops for first min
- rra (1) + pb (1) = 2 ops for second min
- sort_three (~1-2 ops)
- pa (2)
Total: ~9-10 operations
```

---

## Defensive Checks

### Input Validation
| Check | Priority | Failure Mode | Consequence |
|-------|----------|--------------|-------------|
| `!stack_a` | **CRITICAL** | NULL double pointer for stack A | SEGFAULT when dereferencing `*stack_a` |
| `!stack_b` | **CRITICAL** | NULL double pointer for stack B | SEGFAULT when calling `pb()` |
| `!*stack_a` | **CRITICAL** | Empty stack | SEGFAULT when accessing elements |
| `stack_size(*stack_a) < 5` | **MEDIUM** | Insufficient elements | Invalid sorting logic |

### Why These Checks Matter

1. **NULL stack_a check (`!stack_a`) - CRITICAL:**
   - **Without:** Dereferencing `*stack_a` will crash immediately
   - **With:** Returns safely before attempting any operation
   - **Cost:** O(1) - single pointer comparison
   - **Benefit:** Prevents crash, essential for function safety

2. **NULL stack_b check (`!stack_b`) - CRITICAL:**
   - **Without:** `pb()` operations (called twice) will crash
   - **With:** Returns safely, prevents crash during push operations
   - **Cost:** O(1) - single pointer comparison
   - **Benefit:** sort_five REQUIRES stack B for its double reduction strategy

3. **Empty stack check (`!*stack_a`) - CRITICAL:**
   - **Without:** `find_min_index()` will crash or return invalid index
   - **With:** Returns safely, treating empty stack as edge case
   - **Cost:** O(1) - single pointer comparison
   - **Benefit:** Prevents crash on empty input

4. **Size validation (`stack_size < 5`) - MEDIUM:**
   - **Without:** Algorithm assumes 5 elements, will malfunction with fewer
   - **With:** Returns early for invalid sizes
   - **Cost:** O(n) where n ≤ 5, so effectively O(1)
   - **Benefit:** Ensures algorithm preconditions are met

### Defensive Implementation Strategy

**Guard Order:**
```
1. CRITICAL: Check if stack_a pointer is NULL
2. CRITICAL: Check if stack_b pointer is NULL
3. CRITICAL: Check if dereferenced stack_a is NULL
4. MEDIUM: Validate stack has at least 5 elements
5. PROCEED: Execute four-phase sorting algorithm
```

**Return Behavior:**
- Returns `void` - no error codes
- Silent failure on invalid input (no sorting performed)
- Relies on defensive operations (pb, pa, sort_three) for additional safety

---

## Edge Cases

### Case 1: Already Sorted

```c
// A: [1, 2, 3, 4, 5]  B: []

sort_five(&stack_a, &stack_b);

// Min at position 0: No rotation
// Second-min at position 0: No rotation
// sort_three: Already sorted, 0 ops
// Total: 4 operations (2 pb + 2 pa)
```

### Case 2: Reverse Sorted

```c
// A: [5, 4, 3, 2, 1]  B: []

sort_five(&stack_a, &stack_b);

// Min at position 4: rra (1 op)
// Second-min at position 3: rra (1 op)
// sort_three: ~2 ops
// Total: ~6-7 operations + 2 pb + 2 pa = ~10-11 ops
```

### Case 3: Two Smallest Adjacent

```c
// A: [5, 1, 2, 4, 3]  B: []

sort_five(&stack_a, &stack_b);

// Efficient if they're close together
// Fewer rotations needed
```

### Case 4: Negative Numbers

```c
// A: [5, -3, 0, -10, 2]  B: []

sort_five(&stack_a, &stack_b);

// Min = -10, second-min = -3
// Works same as positive numbers
// Result: [-10, -3, 0, 2, 5] ✅
```

---

## Time & Space Complexity

### Time Complexity: **O(1)** - Constant Time

**Operations breakdown:**
```
find_min_index: O(5) = O(1) for 5 elements (twice)
Rotations: O(1) (max 4 total)
pb: O(1) (twice)
sort_three: O(1) (max 2 operations)
pa: O(1) (twice)

Total: O(1) ✅

Fixed size means constant time!
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
Variable: int min_index (4 bytes)
Uses existing stack B temporarily
No additional allocations
No recursion overhead

Space = O(1) ✅
```

### Performance Characteristics

```
Best case: ~5-6 operations (if nearly sorted)
Worst case: ~11-12 operations (reverse sorted)
Average case: ~8-9 operations

Highly efficient for 5 elements!
Better than any comparison-based sort for this size!
```

---

## Relationship with Other Functions

### Called by sort_small

```c
void sort_small(t_stack **stack_a, t_stack **stack_b)
{
    int size = stack_size(*stack_a);

    if (size == 2)
        sort_two(stack_a);
    else if (size == 3)
        sort_three(stack_a);
    else if (size == 4)
        sort_four(stack_a, stack_b);
    else if (size == 5)
        sort_five(stack_a, stack_b);  // ← Maximum small sort
}
```

### Uses find_min_index

```c
int min_index = find_min_index(*stack_a);  // Called twice
```

### Uses sort_three

```c
sort_three(stack_a);  // Core of the algorithm
```

### Uses Multiple Operations

```c
sa(stack_a, 1);   // Swap
ra(stack_a, 1);   // Rotate forward
rra(stack_a, 1);  // Rotate reverse
pb(stack_a, stack_b, 1);  // Push to B
pa(stack_a, stack_b, 1);  // Push to A
```

---

## Integration with Push_swap

### Scenario: Direct 5-Element Sort

```c
// Input: ./push_swap 5 2 1 4 3
// A: [5, 2, 1, 4, 3]  B: []

sort_five(&stack_a, &stack_b);

// Output: sequence of operations
// Result: A: [1, 2, 3, 4, 5]  B: [] ✅
```

### Scenario: Maximum Efficiency

```c
// For 5 or fewer elements, small sorts are optimal
// No need for complex algorithms like Turk

if (size <= 5)
    sort_small(&stack_a, &stack_b);  // Uses sort_five
else
    sort_large(&stack_a, &stack_b);  // Uses Turk algorithm
```

---

## 42 Norm Considerations

### The Problem: Function Length

The full defensive implementation of sort_five with all rotation logic **exceeds 25 lines**. We need to extract the rotation logic into a static helper function.

**Line count analysis:**
```
Defensive checks:     4 lines
First minimum logic: 12 lines (find + rotations + pb)
Second minimum logic: 10 lines (find + rotations + pb)
Final operations:     4 lines (sort_three + 2x pa)
Total:              ~30 lines ❌ EXCEEDS NORM
```

### Solution: Static Helper Function

Extract the "rotate minimum to top" logic into a reusable static helper function.

**Benefits:**
- sort_five stays under 25 lines
- Helper is reusable for both 5-element and 4-element phases
- Cleaner separation of concerns
- Each function has single responsibility

---

### Helper Function: rotate_min_to_top (static)

```c
static void	rotate_min_to_top(t_stack **stack_a, int size)
{
	int	min_idx;

	min_idx = find_min_index(*stack_a);
	if (min_idx == 1)
		sa(stack_a, 1);
	else if (min_idx == 2 && size == 5)
	{
		ra(stack_a, 1);
		ra(stack_a, 1);
	}
	else if ((min_idx == 3 && size == 5) || (min_idx == 2 && size == 4))
	{
		rra(stack_a, 1);
		rra(stack_a, 1);
	}
	else if ((min_idx == 4 && size == 5) || (min_idx == 3 && size == 4))
		rra(stack_a, 1);
}
```

**Line count: 18 lines ✅ UNDER 25**

**Norm compliance:**
- ✅ Under 25 lines (18 lines)
- ✅ `static` keyword for file-local scope
- ✅ Single responsibility: rotate minimum to top
- ✅ Only 1 variable (min_idx)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Handles both 5-element and 4-element cases via size parameter

---

### Main Function: sort_five (Defensive - Recommended)

```c
void	sort_five(t_stack **stack_a, t_stack **stack_b)
{
	if (!stack_a || !stack_b || !*stack_a)
		return ;
	if (stack_size(*stack_a) < 5)
		return ;
	rotate_min_to_top(stack_a, 5);
	pb(stack_a, stack_b, 1);
	rotate_min_to_top(stack_a, 4);
	pb(stack_a, stack_b, 1);
	sort_three(stack_a);
	pa(stack_a, stack_b, 1);
	pa(stack_a, stack_b, 1);
}
```

**Line count: 14 lines ✅ UNDER 25**

**Norm compliance:**
- ✅ Under 25 lines (14 lines)
- ✅ Single responsibility: orchestrates 5-element sort
- ✅ No variables needed (helper handles min_index)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Defensive checks included
- ✅ Clean, readable logic

---

### Complete File Structure

```c
/* ************************************************************************** */
/*                                                                            */
/*   sort_small.c                                                             */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// ... sort_two, sort_three, sort_four functions ...

static void	rotate_min_to_top(t_stack **stack_a, int size)
{
	int	min_idx;

	min_idx = find_min_index(*stack_a);
	if (min_idx == 1)
		sa(stack_a, 1);
	else if (min_idx == 2 && size == 5)
	{
		ra(stack_a, 1);
		ra(stack_a, 1);
	}
	else if ((min_idx == 3 && size == 5) || (min_idx == 2 && size == 4))
	{
		rra(stack_a, 1);
		rra(stack_a, 1);
	}
	else if ((min_idx == 4 && size == 5) || (min_idx == 3 && size == 4))
		rra(stack_a, 1);
}

void	sort_five(t_stack **stack_a, t_stack **stack_b)
{
	if (!stack_a || !stack_b || !*stack_a)
		return ;
	if (stack_size(*stack_a) < 5)
		return ;
	rotate_min_to_top(stack_a, 5);
	pb(stack_a, stack_b, 1);
	rotate_min_to_top(stack_a, 4);
	pb(stack_a, stack_b, 1);
	sort_three(stack_a);
	pa(stack_a, stack_b, 1);
	pa(stack_a, stack_b, 1);
}
```

---

### Function Placement Note

**IMPORTANT:** The `static` helper function MUST be placed **BEFORE** `sort_five` in the file, as C requires functions to be declared before use (unless you add a prototype).

**Recommended file order:**
1. sort_two
2. sort_three
3. sort_four
4. rotate_min_to_top (static helper)
5. sort_five
6. sort_small (router)

---

## Common Mistakes

### Mistake 1: Not Validating Input (CRITICAL)

```c
// ❌ WRONG - No defensive checks
void sort_five(t_stack **stack_a, t_stack **stack_b)
{
    int min_index = find_min_index(*stack_a);  // CRASH if stack_a is NULL!
    // ...
}
```

**✅ Correct:**
```c
if (!stack_a || !stack_b || !*stack_a)
    return;
if (stack_size(*stack_a) < 5)
    return;
// Now safe to proceed
```

**Severity:** CRITICAL - causes SEGFAULT on NULL input
**Defensive Priority:** Must be first checks before any dereference

### Mistake 2: Wrong Push Order (HIGH)

```c
// ❌ WRONG
pb(second_min);  // Push second-min first
pb(min);         // Push min second
// B: [1, 2]

pa();  // Gets 1
pa();  // Gets 2
// A: [2, 1, ...] ← WRONG ORDER!
```

**✅ Correct:**
```c
pb(min);         // Push min first
pb(second_min);  // Push second-min second
// B: [2, 1]

pa();  // Gets 2
pa();  // Gets 1
// A: [1, 2, ...] ✅
```

**Severity:** HIGH - produces incorrect result
**Impact:** Elements restored in wrong order, sort fails

### Mistake 3: Not Handling Position 2 Differently (HIGH)

```c
// ❌ WRONG - Using ra for position 2 and 3
if (min_index == 2)
    ra(stack_a, 1);  // Only 1 rotation
// Element won't reach top!
```

**✅ Correct:**
```c
if (min_index == 2)
{
    ra(stack_a, 1);
    ra(stack_a, 1);  // Need 2 rotations
}
```

**Severity:** HIGH - minimum not moved to top
**Impact:** Wrong element pushed to B, sort fails

### Mistake 4: Forgetting Second Minimum (HIGH)

```c
// ❌ WRONG - Only pushing one element
pb(stack_a, stack_b, 1);  // Push min
sort_three(stack_a);      // Sort 4 elements?
// sort_three only works for 3 elements!
```

**✅ Correct:**
```c
pb(stack_a, stack_b, 1);  // Push min
pb(stack_a, stack_b, 1);  // Push second-min
sort_three(stack_a);      // Now sort 3 elements ✅
```

**Severity:** HIGH - sort_three expects exactly 3 elements
**Impact:** Undefined behavior, incorrect sort

### Mistake 5: Not Pushing Back Both Elements (HIGH)

```c
// ❌ WRONG
pa(stack_a, stack_b, 1);  // Push one back
// Forgot second pa!
// One element stuck in B!
```

**✅ Correct:**
```c
pa(stack_a, stack_b, 1);  // Push second-min
pa(stack_a, stack_b, 1);  // Push min
// Both restored ✅
```

**Severity:** HIGH - incomplete sort
**Impact:** One element left in stack B, stack A only has 4 elements

---

## Testing Strategy

### Test 1: All Minimum Positions

```c
// Test with min at each position 0-4
for (int pos = 0; pos < 5; pos++)
{
    stack = create_stack_with_min_at(pos);
    sort_five(&stack, &b);
    assert(is_sorted(stack));
}
```

### Test 2: Verify Correctness

```c
// Test random permutations
for (int i = 0; i < 100; i++)
{
    stack_a = create_random_5_stack();
    stack_b = NULL;
    sort_five(&stack_a, &stack_b);
    assert(is_sorted(stack_a));
    assert(stack_b == NULL);  // B empty after
}
```

### Test 3: Operation Count

```c
// Verify efficiency
stack_a = [5,4,3,2,1];
int ops = count_operations(sort_five);
assert(ops <= 12);  // Should use at most 12 operations
```

### Test 4: Edge Cases

```c
// Already sorted
sort_five([1,2,3,4,5]);
assert(operation_count <= 5);

// Reverse sorted
sort_five([5,4,3,2,1]);
assert(is_sorted());

// Negative numbers
sort_five([5,-3,0,-10,2]);
assert_result([-10,-3,0,2,5]);
```

---

## Defensive Programming Checklist

### Implementation Verification
- [ ] **NULL stack_a check** - `if (!stack_a) return;` is first line
- [ ] **NULL stack_b check** - `if (!stack_b) return;` is in validation
- [ ] **Empty stack check** - `if (!*stack_a) return;` handles empty case
- [ ] **Size validation** - `if (stack_size(*stack_a) < 5) return;`
- [ ] **First find_min_index call** - For 5-element stack
- [ ] **All 5 positions handled** - Cases for 0, 1, 2, 3, 4
- [ ] **First pb executed** - Pushes minimum to B
- [ ] **Second find_min_index call** - For 4-element stack
- [ ] **All 4 positions handled** - Cases for 0, 1, 2, 3
- [ ] **Second pb executed** - Pushes second-min to B
- [ ] **sort_three called** - Sorts remaining 3
- [ ] **Two pa executed** - Restores both elements to A

### Testing Checklist
- [ ] **NULL stack_a** - `sort_five(NULL, &b)` doesn't crash
- [ ] **NULL stack_b** - `sort_five(&a, NULL)` doesn't crash
- [ ] **Empty stack** - `sort_five(&empty, &b)` doesn't crash
- [ ] **Size < 5** - `sort_five(&four_elements, &b)` returns safely
- [ ] **Min at each position 0-4** - All cases sort correctly
- [ ] **Second-min at each position** - All combinations work
- [ ] **Stack B empty after** - B has no elements after sort
- [ ] **Negative numbers** - `[-10,-3,0,2,5]` sorts correctly
- [ ] **Already sorted** - Uses minimal operations

### Defensive Dependencies
- [ ] **find_min_index has defensive checks** - Verify handles NULL
- [ ] **sort_three has defensive checks** - Verify validates input
- [ ] **pb has defensive checks** - Verify handles NULL stacks
- [ ] **pa has defensive checks** - Verify handles empty source
- [ ] **Layered defense works** - Multiple validation layers prevent failures

---

## Summary

**What sort_five Does:**
1. Validates input pointers and size
2. Finds and pushes minimum to B
3. Finds and pushes second minimum to B
4. Sorts remaining 3 elements using sort_three
5. Pushes both small elements back in order
6. Uses 8-12 operations on average

**Key Characteristics:**
- ✅ Double reduction strategy (5 → 3 problem)
- ✅ Reuses sort_three for efficiency
- ✅ O(1) time and space
- ✅ Maximum ~12 operations
- ✅ Push order ensures correct restoration

**Defensive features:**
- ✅ NULL stack_a pointer validation (CRITICAL)
- ✅ NULL stack_b pointer validation (CRITICAL)
- ✅ Empty stack validation (CRITICAL)
- ✅ Size validation (MEDIUM)
- ✅ Layered defense with delegated functions
- ✅ Silent failure on invalid input

**Critical Uses:**
- Largest size for small sort algorithms
- Called by sort_small router
- Demonstrates advanced reduction technique
- Upper bound for hardcoded optimization

**Remember:**
- Always validate pointers first (CRITICAL)
- Push minimum FIRST, second-min SECOND
- Find minimum twice (for 5, then for 4 elements)
- Choose shortest rotation paths
- Sort 3 remaining with sort_three
- Push back twice to complete sort

**Strategy Insight:**
```
5 elements: 120 permutations (5!)
Hardcoding all cases would be impractical

Reduction strategy:
- Remove 2 smallest → 3 remain
- Sort 3 optimally (6 cases)
- Restore 2 smallest
- Much simpler! ✅

This is the practical limit for reduction strategies.
Beyond 5, need algorithmic sorting (Turk, quicksort, etc.)
```

---

## Location in Project

**File:** `srcs/sort_small_utils.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 6 (Small Sorting Algorithms)

---

## Related Functions

- [sort_small](sort_small.md) - Router that calls sort_five
- [sort_three](sort_three.md) - Used internally to sort 3 elements
- [sort_four](sort_four.md) - Similar strategy for 4 elements
- [find_min_index](find_min_index.md) - Finds minimum position (called twice)
- [pb](pb.md), [pa](pa.md) - Push operations (4 total)
- [sa](sa.md), [ra](ra.md), [rra](rra.md) - Rotation operations

---

*sort_five is the pinnacle of small sorting - beyond this point, algorithmic sorting becomes necessary!*
