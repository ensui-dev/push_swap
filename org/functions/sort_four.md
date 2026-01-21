# sort_four - Sort Exactly Four Elements

## Function Signature

```c
void sort_four(t_stack **stack_a, t_stack **stack_b)
```

**Return type:** `void` - Modifies stacks A and B in place
**Parameters:**
- `t_stack **stack_a` - Double pointer to the head of stack A
- `t_stack **stack_b` - Double pointer to the head of stack B (initially empty)

---

## Purpose & Use Case

`sort_four` is a **specialized sorting function** that sorts exactly 4 elements by reducing the problem to sorting 3 elements. The strategy: isolate the minimum element by pushing it to stack B, sort the remaining 3 in stack A using `sort_three`, then push the minimum back to the top.

### When You'll Use It

You'll call `sort_four` whenever:
1. **Stack has exactly 4 elements** - Detected by `stack_size(stack) == 4`
2. **Called by sort_small** - Router function delegates to sort_four
3. **Building block learning** - Demonstrates reduction strategy
4. **Optimal small sorting** - Uses proven efficient approach

### Why This Strategy Works

**Problem reduction approach:**
```
4 elements → Reduce to 3 elements
[4, 2, 1, 3]

Step 1: Find and isolate minimum (1)
Move 1 to B: [4, 2, 3] | [1]

Step 2: Sort remaining 3 using sort_three
After sort_three: [2, 3, 4] | [1]

Step 3: Push minimum back to top
After pa: [1, 2, 3, 4] | []

Result: SORTED! ✅

Maximum operations: ~5-6 operations
This is highly efficient!
```

### Real-World Analogy

**Organizing four books by height:**
```
Books: [Tall, Medium, Short, Very Tall]

Strategy:
1. Remove the shortest book (set aside)
2. Organize remaining 3 books
3. Place shortest book back at the front

Result: [Short, Medium, Tall, Very Tall]

Same concept for sorting 4 numbers!
```

---

## Deep Dive: How It Works

### The Three-Phase Algorithm

**Phase 1: Find and Move Minimum to B**
- Use `find_min_index` to locate the minimum
- Rotate to bring minimum to top (choose shortest path)
- Push minimum to stack B

**Phase 2: Sort Remaining Three**
- Stack A now has 3 elements
- Call `sort_three` to sort them optimally
- Stack A is now sorted (but missing the minimum)

**Phase 3: Restore Minimum**
- Push element from B back to A
- Minimum is now on top of sorted stack
- Final result: fully sorted 4 elements

### Algorithm Visualization

```
Initial: A: [4, 2, 1, 3]  B: []

Phase 1: Find minimum
min_index = find_min_index(A) = 2 (value 1 at position 2)

Phase 1: Bring min to top
Since min_index = 2 (closer to bottom)
Use rra twice:
rra: A: [3, 4, 2, 1]  B: []
rra: A: [1, 3, 4, 2]  B: []

Phase 1: Push min to B
pb: A: [3, 4, 2]  B: [1]

Phase 2: Sort remaining 3
sort_three(A)
Result: A: [2, 3, 4]  B: [1]

Phase 3: Push min back
pa: A: [1, 2, 3, 4]  B: []

SORTED! ✅
```

---

## Step-by-Step Implementation

### Step 1: Validate Input (DEFENSIVE)

```c
if (!stack_a || !stack_b || !*stack_a)
    return;
if (stack_size(*stack_a) < 4)
    return;
```

**Defensive checks:**
```
!stack_a: Double pointer for stack A is NULL → Cannot dereference (CRITICAL)
!stack_b: Double pointer for stack B is NULL → pb will crash (CRITICAL)
!*stack_a: Stack A is empty → Nothing to sort (CRITICAL)
size < 4: Not enough elements → Algorithm requires exactly 4 (MEDIUM)

These checks prevent SEGFAULT and ensure algorithm preconditions are met.
```

**Defensive Priority:** CRITICAL - Must validate before any operation

### Step 2: Find Minimum Index

```c
int min_index = find_min_index(*stack_a);
```

**Why find position?**
```
Need to know WHERE the minimum is located
So we can decide shortest path to bring it to top

Positions 0-1: Use ra (rotate forward)
Positions 2-3: Use rra (reverse rotate)

This optimization saves operations!
```

### Step 2: Bring Minimum to Top

**Decision based on position:**

```c
if (min_index == 1)
    sa(stack_a, 1);  // Min is second, swap to top
else if (min_index == 2)
{
    rra(stack_a, 1);  // Min is third, reverse rotate twice
    rra(stack_a, 1);
}
else if (min_index == 3)
    rra(stack_a, 1);  // Min is fourth, reverse rotate once
// If min_index == 0, already on top, do nothing
```

**Position-specific strategies:**
```
Position 0: Already on top → 0 operations
Position 1: sa → 1 operation
Position 2: rra, rra → 2 operations
Position 3: rra → 1 operation

Alternatives:
Position 1: Could use ra, ra, ra (3 ops) but sa (1 op) is better
Position 2: Could use ra, ra (2 ops) same as rra, rra (2 ops)
Position 3: Could use ra, ra, ra (3 ops) but rra (1 op) is better

Our implementation chooses optimal paths!
```

### Step 3: Push Minimum to B

```c
pb(stack_a, stack_b, 1);
```

**Result:**
```
Stack A: 3 elements (all larger than minimum)
Stack B: 1 element (the minimum)

Now A can be sorted independently!
```

### Step 4: Sort Remaining Three

```c
sort_three(stack_a);
```

**Delegation:**
```
Reuses sort_three function
Handles all 6 permutations optimally
Maximum 2 operations
Stack A is now sorted (without minimum)
```

### Step 5: Restore Minimum

```c
pa(stack_a, stack_b, 1);
```

**Final step:**
```
Pushes minimum from B back to top of A
Minimum is now at position 0
Rest of A is still sorted
Result: Fully sorted 4 elements!
```

---

## Complete Algorithm Pseudocode

### Basic Implementation
```
FUNCTION sort_four(stack_a, stack_b):
    // Step 1: Find minimum position
    min_index = find_min_index(stack_a)

    // Step 2: Bring minimum to top (choose shortest path)
    IF min_index == 1:
        sa(stack_a)         // Swap to top
    ELSE IF min_index == 2:
        rra(stack_a)        // Reverse rotate twice
        rra(stack_a)
    ELSE IF min_index == 3:
        rra(stack_a)        // Reverse rotate once
    // If min_index == 0, already on top

    // Step 3: Push minimum to B
    pb(stack_a, stack_b)

    // Step 4: Sort remaining 3 in A
    sort_three(stack_a)

    // Step 5: Push minimum back to A
    pa(stack_a, stack_b)

    // Done! Stack A is fully sorted
END FUNCTION
```

### Defensive Implementation (Full)
```
FUNCTION sort_four(stack_a, stack_b):
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
    IF stack_size(*stack_a) < 4:
        RETURN  // Algorithm requires exactly 4 elements

    // Step 5: Find minimum position
    min_index = find_min_index(*stack_a)  // find_min_index has own NULL check

    // Step 6: Bring minimum to top (choose shortest path)
    IF min_index == 1:
        sa(stack_a, 1)         // Swap to top
    ELSE IF min_index == 2:
        rra(stack_a, 1)        // Reverse rotate twice
        rra(stack_a, 1)
    ELSE IF min_index == 3:
        rra(stack_a, 1)        // Reverse rotate once
    // If min_index == 0, already on top

    // Step 7: Push minimum to B
    pb(stack_a, stack_b, 1)  // pb has own defensive checks

    // Step 8: Sort remaining 3 in A
    sort_three(stack_a)  // sort_three has own defensive checks

    // Step 9: Push minimum back to A
    pa(stack_a, stack_b, 1)  // pa has own defensive checks

    // Done! Stack A is fully sorted
END FUNCTION
```

---

## Visual Execution Trace

### Example: Sorting [4, 2, 1, 3]

```
Initial State:
A: [4, 2, 1, 3]  B: []
   [0][1][2][3]

Call: sort_four(&stack_a, &stack_b)

Step 1: Find minimum index
min_index = find_min_index(A)
Minimum value: 1
Position: 2 ✅

Step 2: Bring min to top
min_index == 2, so execute:
rra(&stack_a, 1)

After first rra:
A: [3, 4, 2, 1]  B: []

rra(&stack_a, 1)

After second rra:
A: [1, 3, 4, 2]  B: []
   ^
   Minimum now on top!

Step 3: Push to B
pb(&stack_a, &stack_b, 1)

After pb:
A: [3, 4, 2]  B: [1]

Step 4: Sort remaining 3
sort_three(&stack_a)
(Internally executes optimal solution)

After sort_three:
A: [2, 3, 4]  B: [1]
   ^  ^  ^
   Sorted!

Step 5: Push minimum back
pa(&stack_a, &stack_b, 1)

Final State:
A: [1, 2, 3, 4]  B: []
   ^  ^  ^  ^
   FULLY SORTED! ✅

Operations used:
- rra (2 times)
- pb (1 time)
- sort_three operations (varies)
- pa (1 time)

Total: ~5-6 operations depending on sort_three case
```

### Example 2: Sorting [3, 1, 4, 2]

```
Initial State:
A: [3, 1, 4, 2]  B: []
   [0][1][2][3]

Step 1: Find minimum
min_index = 1 (value 1 at position 1)

Step 2: Bring to top
sa(&stack_a, 1)  // Swap first two

After sa:
A: [1, 3, 4, 2]  B: []

Step 3: Push to B
pb(&stack_a, &stack_b, 1)

After pb:
A: [3, 4, 2]  B: [1]

Step 4: Sort remaining 3
sort_three(&stack_a)

After sort_three:
A: [2, 3, 4]  B: [1]

Step 5: Push back
pa(&stack_a, &stack_b, 1)

Final:
A: [1, 2, 3, 4]  B: [] ✅

Operations: sa, pb, sort_three ops, pa
Total: ~4-5 operations
```

---

## Defensive Checks

### Input Validation
| Check | Priority | Failure Mode | Consequence |
|-------|----------|--------------|-------------|
| `!stack_a` | **CRITICAL** | NULL double pointer for stack A | SEGFAULT when dereferencing `*stack_a` |
| `!stack_b` | **CRITICAL** | NULL double pointer for stack B | SEGFAULT when calling `pb()` |
| `!*stack_a` | **CRITICAL** | Empty stack | SEGFAULT when accessing elements |
| `stack_size(*stack_a) < 4` | **MEDIUM** | Insufficient elements | Invalid sorting logic |

### Why These Checks Matter

1. **NULL stack_a check (`!stack_a`) - CRITICAL:**
   - **Without:** Dereferencing `*stack_a` will crash immediately
   - **With:** Returns safely before attempting any operation
   - **Cost:** O(1) - single pointer comparison
   - **Benefit:** Prevents crash, essential for function safety

2. **NULL stack_b check (`!stack_b`) - CRITICAL:**
   - **Without:** `pb()` operation will crash when accessing stack B
   - **With:** Returns safely, prevents crash during push operation
   - **Cost:** O(1) - single pointer comparison
   - **Benefit:** sort_four REQUIRES stack B for its reduction strategy

3. **Empty stack check (`!*stack_a`) - CRITICAL:**
   - **Without:** `find_min_index()` will crash or return invalid index
   - **With:** Returns safely, treating empty stack as edge case
   - **Cost:** O(1) - single pointer comparison
   - **Benefit:** Prevents crash on empty input

4. **Size validation (`stack_size < 4`) - MEDIUM:**
   - **Without:** Algorithm assumes 4 elements, will malfunction with fewer
   - **With:** Returns early for invalid sizes
   - **Cost:** O(n) where n ≤ 4, so effectively O(1)
   - **Benefit:** Ensures algorithm preconditions are met

### Defensive Implementation Strategy

**Guard Order:**
```
1. CRITICAL: Check if stack_a pointer is NULL
2. CRITICAL: Check if stack_b pointer is NULL
3. CRITICAL: Check if dereferenced stack_a is NULL
4. MEDIUM: Validate stack has at least 4 elements
5. PROCEED: Execute sorting algorithm
```

**Return Behavior:**
- Returns `void` - no error codes
- Silent failure on invalid input (no sorting performed)
- Relies on defensive operations (pb, pa, sort_three) for additional safety

---

## Edge Cases

### Case 1: Already Sorted

```c
// A: [1, 2, 3, 4]  B: []

sort_four(&stack_a, &stack_b);

// min_index = 0 (already on top)
// No rotation needed
// pb: A: [2,3,4]  B: [1]
// sort_three: Already sorted, 0 ops
// pa: A: [1,2,3,4]  B: []

// Total: 2 operations (pb, pa)
```

### Case 2: Reverse Sorted

```c
// A: [4, 3, 2, 1]  B: []

sort_four(&stack_a, &stack_b);

// min_index = 3
// rra once: A: [1,4,3,2]
// pb: A: [4,3,2]  B: [1]
// sort_three: ~2 ops
// pa: A: [1,2,3,4]

// Total: ~5 operations
```

### Case 3: Minimum Already on Top

```c
// A: [1, 4, 3, 2]  B: []

sort_four(&stack_a, &stack_b);

// min_index = 0
// No rotation needed
// pb: A: [4,3,2]  B: [1]
// sort_three: sorts to [2,3,4]
// pa: A: [1,2,3,4]

// Efficient!
```

### Case 4: Negative Numbers

```c
// A: [5, -3, 0, -10]  B: []

sort_four(&stack_a, &stack_b);

// min = -10 at position 3
// Works same as positive numbers
// Result: [-10, -3, 0, 5] ✅
```

---

## Time & Space Complexity

### Time Complexity: **O(1)** - Constant Time

**Operations breakdown:**
```
find_min_index: O(4) = O(1) for 4 elements
Rotations to top: O(1) (max 2 rotations)
pb: O(1)
sort_three: O(1) (max 2 operations)
pa: O(1)

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
Best case: ~2-3 operations (if already nearly sorted)
Worst case: ~6-7 operations (reverse sorted)
Average case: ~5 operations

Highly efficient for 4 elements!
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
        sort_four(stack_a, stack_b);  // ← Delegates to sort_four
    else if (size == 5)
        sort_five(stack_a, stack_b);
}
```

### Uses find_min_index

```c
int min_index = find_min_index(*stack_a);  // Find where min is
```

### Uses sort_three

```c
sort_three(stack_a);  // Reuses optimal 3-element sort
```

### Uses Multiple Operations

```c
sa(stack_a, 1);   // Swap
ra(stack_a, 1);   // Rotate (alternative)
rra(stack_a, 1);  // Reverse rotate
pb(stack_a, stack_b, 1);  // Push to B
pa(stack_a, stack_b, 1);  // Push to A
```

---

## Integration with Push_swap

### Scenario: Direct 4-Element Sort

```c
// Input: ./push_swap 4 2 1 3
// A: [4, 2, 1, 3]  B: []

sort_four(&stack_a, &stack_b);

// Output: "rra\nrra\npb\n[sort_three ops]\npa"
// Result: A: [1, 2, 3, 4]  B: [] ✅
```

### Scenario: Comparison with Naive Approach

```c
// Naive approach (bubble sort):
// Multiple passes, swaps, many operations
// Could take 8-10+ operations

// sort_four approach:
// Intelligent reduction to sort_three
// Maximum 6-7 operations
// More efficient! ✅
```

---

## 42 Norm Considerations

### Function Structure (Basic)

```c
void	sort_four(t_stack **stack_a, t_stack **stack_b)
{
	int	min_index;

	min_index = find_min_index(*stack_a);
	if (min_index == 1)
		sa(stack_a, 1);
	else if (min_index == 2)
	{
		rra(stack_a, 1);
		rra(stack_a, 1);
	}
	else if (min_index == 3)
		rra(stack_a, 1);
	pb(stack_a, stack_b, 1);
	sort_three(stack_a);
	pa(stack_a, stack_b, 1);
}
```

### Function Structure (Defensive - Recommended)

```c
void	sort_four(t_stack **stack_a, t_stack **stack_b)
{
	int	min_index;

	if (!stack_a || !stack_b || !*stack_a)
		return ;
	if (stack_size(*stack_a) < 4)
		return ;
	min_index = find_min_index(*stack_a);
	if (min_index == 1)
		sa(stack_a, 1);
	else if (min_index == 2)
	{
		rra(stack_a, 1);
		rra(stack_a, 1);
	}
	else if (min_index == 3)
		rra(stack_a, 1);
	pb(stack_a, stack_b, 1);
	sort_three(stack_a);
	pa(stack_a, stack_b, 1);
}
```

**Norm compliance:**
- ✅ Under 25 lines (22 lines with defensive checks)
- ✅ Single responsibility: sorts 4 elements
- ✅ Only 1 variable (min_index)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Clear reduction strategy
- ✅ Defensive checks add only 4 lines

---

## Common Mistakes

### Mistake 1: Not Validating Input (CRITICAL)

```c
// ❌ WRONG - No defensive checks
void sort_four(t_stack **stack_a, t_stack **stack_b)
{
    int min_index = find_min_index(*stack_a);  // CRASH if stack_a is NULL!
    // ...
}
```

**✅ Correct:**
```c
if (!stack_a || !stack_b || !*stack_a)
    return;
if (stack_size(*stack_a) < 4)
    return;
// Now safe to proceed
```

**Severity:** CRITICAL - causes SEGFAULT on NULL input
**Defensive Priority:** Must be first checks before any dereference

### Mistake 2: Not Using Optimal Rotation (MEDIUM)

```c
// ❌ WRONG - Always using ra
if (min_index == 3)
{
    ra(stack_a, 1);  // 3 operations!
    ra(stack_a, 1);
    ra(stack_a, 1);
}
```

**✅ Correct:**
```c
if (min_index == 3)
    rra(stack_a, 1);  // 1 operation! Much better
```

**Severity:** MEDIUM - works but inefficient
**Impact:** Uses more operations than necessary

### Mistake 3: Forgetting to Push Back (HIGH)

```c
// ❌ WRONG
pb(stack_a, stack_b, 1);
sort_three(stack_a);
// Forgot: pa(stack_a, stack_b, 1);
// Minimum is stuck in B!
```

**✅ Correct:**
```c
pb(stack_a, stack_b, 1);
sort_three(stack_a);
pa(stack_a, stack_b, 1);  // CRITICAL! Restore minimum
```

**Severity:** HIGH - produces incorrect result
**Impact:** Minimum element left in stack B, sort incomplete

### Mistake 4: Not Handling All Positions (HIGH)

```c
// ❌ WRONG - Missing position 2
if (min_index == 1)
    sa(stack_a, 1);
else if (min_index == 3)
    rra(stack_a, 1);
// What if min_index == 2? Nothing happens!
```

**✅ Correct:**
```c
// Handle all positions: 0, 1, 2, 3
```

**Severity:** HIGH - some inputs fail to sort correctly
**Impact:** Minimum not moved to top for position 2

### Mistake 5: Sorting Before Isolating Min (HIGH)

```c
// ❌ WRONG - Strategy doesn't work
sort_three(stack_a);  // Sort 3 of the 4 elements?
// This doesn't make sense for 4 elements
```

**✅ Correct:**
```c
// Isolate minimum FIRST
pb(stack_a, stack_b, 1);
// THEN sort remaining 3
sort_three(stack_a);
```

**Severity:** HIGH - incorrect algorithm
**Impact:** sort_three expects exactly 3 elements

---

## Testing Strategy

### Test 1: All Position Cases

```c
// Min at position 0
sort_four([1,4,3,2]);
assert_sorted();

// Min at position 1
sort_four([4,1,3,2]);
assert_sorted();

// Min at position 2
sort_four([4,3,1,2]);
assert_sorted();

// Min at position 3
sort_four([4,3,2,1]);
assert_sorted();
```

### Test 2: Verify Correctness

```c
// Test multiple permutations
for each permutation of 4 elements:
    stack_a = create_permutation();
    stack_b = NULL;
    sort_four(&stack_a, &stack_b);
    assert(is_sorted(stack_a));
    assert(stack_b == NULL);  // B should be empty after
```

### Test 3: Operation Count

```c
// Verify efficiency
stack_a = [4,2,1,3];
int ops = count_operations(sort_four);
assert(ops <= 7);  // Should use at most 6-7 operations
```

### Test 4: Edge Cases

```c
// Already sorted
sort_four([1,2,3,4]);
assert(is_sorted());

// Reverse sorted
sort_four([4,3,2,1]);
assert(is_sorted());

// Negative numbers
sort_four([5,-3,0,-10]);
assert_result([-10,-3,0,5]);
```

---

## Defensive Programming Checklist

### Implementation Verification
- [ ] **NULL stack_a check** - `if (!stack_a) return;` is first line
- [ ] **NULL stack_b check** - `if (!stack_b) return;` is in validation
- [ ] **Empty stack check** - `if (!*stack_a) return;` handles empty case
- [ ] **Size validation** - `if (stack_size(*stack_a) < 4) return;`
- [ ] **find_min_index call** - Properly calls after validation
- [ ] **All positions handled** - Cases for 0, 1, 2, 3
- [ ] **pb executed** - Pushes minimum to B
- [ ] **sort_three called** - Sorts remaining 3
- [ ] **pa executed** - Restores minimum to A

### Testing Checklist
- [ ] **NULL stack_a** - `sort_four(NULL, &b)` doesn't crash
- [ ] **NULL stack_b** - `sort_four(&a, NULL)` doesn't crash
- [ ] **Empty stack** - `sort_four(&empty, &b)` doesn't crash
- [ ] **Size < 4** - `sort_four(&three_elements, &b)` returns safely
- [ ] **Min at pos 0** - `[1,4,3,2]` sorts correctly
- [ ] **Min at pos 1** - `[4,1,3,2]` sorts correctly
- [ ] **Min at pos 2** - `[4,3,1,2]` sorts correctly
- [ ] **Min at pos 3** - `[4,3,2,1]` sorts correctly
- [ ] **Stack B empty after** - B has no elements after sort

### Defensive Dependencies
- [ ] **find_min_index has defensive checks** - Verify handles NULL
- [ ] **sort_three has defensive checks** - Verify validates input
- [ ] **pb has defensive checks** - Verify handles NULL stacks
- [ ] **pa has defensive checks** - Verify handles empty source
- [ ] **Layered defense works** - Multiple validation layers prevent failures

---

## Summary

**What sort_four Does:**
1. Validates input pointers and size
2. Finds and isolates minimum element (push to B)
3. Sorts remaining 3 elements using sort_three
4. Restores minimum to top of sorted stack
5. Uses 5-6 operations on average

**Key Characteristics:**
- ✅ Reduction strategy (4 → 3 problem)
- ✅ Reuses sort_three for efficiency
- ✅ O(1) time and space
- ✅ Maximum ~6-7 operations
- ✅ Optimal path selection for rotations

**Defensive features:**
- ✅ NULL stack_a pointer validation (CRITICAL)
- ✅ NULL stack_b pointer validation (CRITICAL)
- ✅ Empty stack validation (CRITICAL)
- ✅ Size validation (MEDIUM)
- ✅ Layered defense with delegated functions
- ✅ Silent failure on invalid input

**Critical Uses:**
- Direct sorting of 4-element stacks
- Called by sort_small router
- Demonstrates problem reduction technique
- Building block for understanding sort_five

**Remember:**
- Always validate pointers first (CRITICAL)
- Find minimum position after validation
- Choose shortest rotation path
- Isolate minimum in stack B
- Sort remaining 3 with sort_three
- Push minimum back to complete sort

**Strategy Insight:**
```
4 elements is too complex for hardcoded solutions
(24 permutations would need 24 cases!)

Instead: Reduce to 3 elements
- 3 elements: 6 cases (manageable)
- Push/pop overhead: 2 operations
- Total: Still very efficient!

This reduction strategy is brilliant! ✅
```

---

## Location in Project

**File:** `srcs/sort_small_utils.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 6 (Small Sorting Algorithms)

---

## Related Functions

- [sort_small](sort_small.md) - Router that calls sort_four
- [sort_three](sort_three.md) - Used internally to sort 3 elements
- [sort_two](sort_two.md) - Simpler sort
- [sort_five](sort_five.md) - Similar strategy for 5 elements
- [find_min_index](find_min_index.md) - Finds minimum position
- [pb](pb.md), [pa](pa.md) - Push operations used
- [sa](sa.md), [ra](ra.md), [rra](rra.md) - Rotation operations

---

*sort_four teaches the reduction strategy - solving a complex problem by reducing it to a simpler one!*
