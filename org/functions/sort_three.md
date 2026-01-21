# sort_three - Sort Exactly Three Elements

## Function Signature

```c
void sort_three(t_stack **stack_a)
```

**Return type:** `void` - Modifies stack A in place
**Parameter:** `t_stack **stack_a` - Double pointer to the head of stack A

---

## Purpose & Use Case

`sort_three` is a **specialized sorting function** that sorts exactly 3 elements using hardcoded optimal solutions. With 3 elements, there are exactly 6 possible permutations (3! = 6), and each can be solved with a maximum of 2 operations. This function implements all optimal solutions.

### When You'll Use It

You'll call `sort_three` whenever:
1. **Stack has exactly 3 elements** - Detected by `stack_size(stack) == 3`
2. **Called by sort_small** - Router function delegates to sort_three
3. **After sort_four/five** - After moving elements to B, 3 remain in A
4. **Core sorting strategy** - Fundamental building block of push_swap

### Why This Matters

**With 3 elements, there are exactly 6 possible arrangements:**
```
All permutations of [1, 2, 3]:

1. [1, 2, 3] ← Already sorted (0 operations)
2. [1, 3, 2] ← Need: sa, ra (2 operations)
3. [2, 1, 3] ← Need: sa (1 operation)
4. [2, 3, 1] ← Need: rra (1 operation)
5. [3, 1, 2] ← Need: ra (1 operation)
6. [3, 2, 1] ← Need: sa, rra (2 operations)

Maximum 2 operations for any case!
This is provably optimal ✅
```

### Real-World Analogy

**Three people lining up by height:**
```
Scenario 1: [Short, Medium, Tall] ← Already correct!
Scenario 2: [Short, Tall, Medium] ← Swap last two, rotate
Scenario 3: [Medium, Short, Tall] ← Swap first two
Scenario 4: [Medium, Tall, Short] ← Rotate back once
Scenario 5: [Tall, Short, Medium] ← Rotate forward once
Scenario 6: [Tall, Medium, Short] ← Swap first two, rotate back

Each scenario has a specific solution!
```

---

## Deep Dive: How It Works

### The Decision Tree Algorithm

**Strategy:**
- Identify which permutation we have
- Execute the specific optimal solution for that permutation
- Use minimum operations to sort

### All Six Cases Mapped

```
Case 1: [1, 2, 3] - ALREADY SORTED
min=1, mid=2, max=3
Action: Nothing (0 ops)

Case 2: [1, 3, 2] - Min on top, max in middle
min=1, mid=3, max=2
Action: sa, ra (2 ops)

Case 3: [2, 1, 3] - Min in middle, max on bottom
min=2, mid=1, max=3
Action: sa (1 op)

Case 4: [2, 3, 1] - Max in middle, min on bottom
min=2, mid=3, max=1
Action: rra (1 op)

Case 5: [3, 1, 2] - Max on top, min in middle
min=3, mid=1, max=2
Action: ra (1 op)

Case 6: [3, 2, 1] - REVERSE SORTED
min=3, mid=2, max=1
Action: sa, rra (2 ops)
```

### Implementation Strategy

**Common approach:**
```
Find maximum value using find_max()
Check position of maximum
Use if-else tree to determine which case
Execute appropriate operations
```

**Why find_max?**
```
The maximum element's position is a good discriminator:

max on top (pos 0): Cases 5 or 6
max in middle (pos 1): Cases 2 or 4
max on bottom (pos 2): Cases 1 or 3

Then use one more comparison to determine exact case.
```

---

## Step-by-Step Implementation

### Step 1: Validate Input (DEFENSIVE)

```c
if (!stack_a || !*stack_a)
    return;
if (stack_size(*stack_a) < 3)
    return;
```

**Defensive checks:**
```
!stack_a: Double pointer is NULL → Cannot dereference (CRITICAL)
!*stack_a: Stack is empty → Nothing to sort (CRITICAL)
size < 3: Not enough elements → Algorithm requires exactly 3 (MEDIUM)

These checks prevent SEGFAULT and ensure algorithm preconditions are met.
```

**Defensive Priority:** CRITICAL - Must validate before any dereference or operation

### Step 2: Find the Maximum Value

```c
int max = find_max(*stack_a);
```

**Why maximum?**
```
The maximum element's position helps identify the permutation.
Alternatively, could use minimum.
Both work, but max is conventional in many implementations.

Note: find_max has its own NULL check, but we validate first for clarity.
```

### Step 3: Identify Position and Execute

**Decision tree based on max position:**

```c
if ((*stack_a)->value == max)
{
    // Max is on top (pos 0): Cases 5 or 6
    ra(stack_a, 1);  // Rotate to move max down

    // Now check if more work needed
    if ((*stack_a)->value > (*stack_a)->next->value)
        sa(stack_a, 1);  // Swap if still out of order
}
else if ((*stack_a)->next->value == max)
{
    // Max is in middle (pos 1): Cases 2 or 4
    rra(stack_a, 1);  // Rotate back to move max to bottom

    // Now check if more work needed
    if ((*stack_a)->value > (*stack_a)->next->value)
        sa(stack_a, 1);  // Swap if still out of order
}
else
{
    // Max is on bottom (pos 2): Cases 1 or 3
    // Max already in correct position (bottom of sorted 3)

    if ((*stack_a)->value > (*stack_a)->next->value)
        sa(stack_a, 1);  // Just swap top two if needed
}
```

---

## Complete Algorithm Pseudocode

### Basic Implementation
```
FUNCTION sort_three(stack_a):
    // Validate size only
    IF stack has less than 3 elements:
        RETURN

    // Find maximum value
    max = find_max(stack_a)

    // Decision tree based on max position
    IF top_value == max:
        // Max on top: Cases 5, 6
        ra(stack_a)  // Move max down
        IF top > second:  // Still out of order?
            sa(stack_a)   // Swap

    ELSE IF second_value == max:
        // Max in middle: Cases 2, 4
        rra(stack_a)  // Move max to bottom
        IF top > second:  // Still out of order?
            sa(stack_a)   // Swap

    ELSE:
        // Max on bottom: Cases 1, 3
        IF top > second:  // Out of order?
            sa(stack_a)   // Just swap
        // Else already sorted

    // Done! Stack is now sorted
END FUNCTION
```

### Defensive Implementation (Full)
```
FUNCTION sort_three(stack_a):
    // DEFENSIVE STEP 1: Validate double pointer (CRITICAL)
    IF stack_a is NULL:
        RETURN  // Cannot dereference NULL pointer

    // DEFENSIVE STEP 2: Validate dereferenced stack (CRITICAL)
    IF *stack_a is NULL:
        RETURN  // Empty stack, nothing to sort

    // DEFENSIVE STEP 3: Validate size (MEDIUM)
    IF stack_size(*stack_a) < 3:
        RETURN  // Algorithm requires exactly 3 elements

    // Step 4: Find maximum value
    max = find_max(*stack_a)  // find_max has own NULL check (layered defense)

    // Step 5: Decision tree based on max position
    IF (*stack_a)->value == max:
        // Max on top: Cases 5, 6
        ra(stack_a, 1)  // Move max down (ra has own checks)
        IF (*stack_a)->value > (*stack_a)->next->value:
            sa(stack_a, 1)  // Swap if still out of order

    ELSE IF (*stack_a)->next->value == max:
        // Max in middle: Cases 2, 4
        rra(stack_a, 1)  // Move max to bottom (rra has own checks)
        IF (*stack_a)->value > (*stack_a)->next->value:
            sa(stack_a, 1)  // Swap if still out of order

    ELSE:
        // Max on bottom: Cases 1, 3
        IF (*stack_a)->value > (*stack_a)->next->value:
            sa(stack_a, 1)  // Just swap if out of order
        // Else already sorted (Case 1)

    // Done! Stack is now sorted
END FUNCTION
```

---

## Visual Execution Trace

### Example 1: Case 5 [3, 1, 2]

```
Initial State:
Stack A: [3] -> [1] -> [2] -> NULL
         max    min    mid

Call: sort_three(&stack_a)

Step 1: Find max
max = find_max(stack_a) = 3

Step 2: Check position
(*stack_a)->value == max?
3 == 3? YES! ✅ Max is on top

Step 3: Execute Case 5 solution
ra(&stack_a, 1)  // Rotate

After ra:
Stack A: [1] -> [2] -> [3] -> NULL
         min    mid    max

Step 4: Check if more work needed
(*stack_a)->value > (*stack_a)->next->value?
1 > 2? NO ✅ Already sorted!

Final State:
Stack A: [1] -> [2] -> [3] -> NULL ✅ SORTED!

Operations used: 1 (ra)
Output: "ra"
```

### Example 2: Case 6 [3, 2, 1]

```
Initial State:
Stack A: [3] -> [2] -> [1] -> NULL
         max    mid    min

Call: sort_three(&stack_a)

Step 1: Find max
max = 3

Step 2: Check position
3 == 3? YES! Max on top

Step 3: Rotate
ra(&stack_a, 1)

After ra:
Stack A: [2] -> [1] -> [3] -> NULL
         mid    min    max

Step 4: Check if swap needed
2 > 1? YES! ✅ Need to swap

Step 5: Swap
sa(&stack_a, 1)

After sa:
Stack A: [1] -> [2] -> [3] -> NULL

Final State: ✅ SORTED!

Operations used: 2 (ra, sa)
Output: "ra\nsa"
```

### Example 3: Case 3 [2, 1, 3]

```
Initial State:
Stack A: [2] -> [1] -> [3] -> NULL
         mid    min    max

Call: sort_three(&stack_a)

Step 1: Find max
max = 3

Step 2: Check position
2 == 3? NO
1 == 3? NO
Max is on bottom ✅

Step 3: Check if swap needed
2 > 1? YES! ✅

Step 4: Swap
sa(&stack_a, 1)

After sa:
Stack A: [1] -> [2] -> [3] -> NULL

Final State: ✅ SORTED!

Operations used: 1 (sa)
Output: "sa"
```

### Example 4: Case 1 [1, 2, 3] - Already Sorted

```
Initial State:
Stack A: [1] -> [2] -> [3] -> NULL

Call: sort_three(&stack_a)

Step 1: Find max
max = 3

Step 2: Check position
1 == 3? NO
2 == 3? NO
Max is on bottom ✅

Step 3: Check if swap needed
1 > 2? NO ✅ Already sorted!

Final State:
Stack A: [1] -> [2] -> [3] -> NULL ✅

Operations used: 0
Output: (nothing)
```

---

## All Six Cases Detailed

### Case 1: [1, 2, 3] - Already Sorted
```
Initial: [1, 2, 3]
Operations: None
Result: [1, 2, 3]
Ops count: 0
```

### Case 2: [1, 3, 2] - Min on top, max middle
```
Initial: [1, 3, 2]
Step 1: rra → [2, 1, 3]  (move max to bottom)
Step 2: sa → [1, 2, 3]   (swap top two)
Result: [1, 2, 3]
Ops count: 2
```

### Case 3: [2, 1, 3] - Max on bottom
```
Initial: [2, 1, 3]
Step 1: sa → [1, 2, 3]   (just swap)
Result: [1, 2, 3]
Ops count: 1
```

### Case 4: [2, 3, 1] - Max middle, min bottom
```
Initial: [2, 3, 1]
Step 1: rra → [1, 2, 3]  (rotate back once)
Result: [1, 2, 3]
Ops count: 1
```

### Case 5: [3, 1, 2] - Max on top
```
Initial: [3, 1, 2]
Step 1: ra → [1, 2, 3]   (rotate forward once)
Result: [1, 2, 3]
Ops count: 1
```

### Case 6: [3, 2, 1] - Reverse sorted
```
Initial: [3, 2, 1]
Step 1: ra → [2, 1, 3]   (move max down)
Step 2: sa → [1, 2, 3]   (swap top two)
Result: [1, 2, 3]
Ops count: 2
```

---

## Defensive Checks

### Input Validation
| Check | Priority | Failure Mode | Consequence |
|-------|----------|--------------|-------------|
| `!stack` | **CRITICAL** | NULL double pointer | SEGFAULT when dereferencing `stack` |
| `!*stack` | **CRITICAL** | NULL dereferenced pointer | SEGFAULT when accessing `(*stack)->value` |
| `stack_size(*stack) < 3` | **MEDIUM** | Insufficient elements | Invalid sorting logic, potential SEGFAULT |
| Depends on `sa`, `ra`, `rra` | **LOW** | Operation failures | Operations have their own defensive checks |

### Why These Checks Matter

1. **NULL stack pointer check (`!stack`) - CRITICAL:**
   - **Without:** Dereferencing `*stack` will cause immediate SEGFAULT
   - **With:** Returns safely without attempting to sort
   - **Cost:** O(1) - single pointer comparison
   - **Benefit:** Prevents catastrophic crash from NULL double pointer
   - **Defensive Priority:** Must be first check before any dereference

2. **NULL dereferenced stack check (`!*stack`) - CRITICAL:**
   - **Without:** Accessing `(*stack)->value` will crash on empty stack
   - **With:** Returns safely, treating empty stack as already sorted
   - **Cost:** O(1) - single pointer comparison
   - **Benefit:** Prevents crash when stack contains no nodes
   - **Defensive Priority:** Must be second check, after stack pointer validation

3. **Size validation check (should have exactly 3 elements) - MEDIUM:**
   - **Without:** Logic assumes 3 elements, may access NULL nodes if fewer
   - **With:** Returns early for stacks with < 3 elements
   - **Cost:** O(n) where n ≤ 3, so effectively O(1)
   - **Benefit:** Prevents invalid comparisons and potential SEGFAULT
   - **Defensive Priority:** Validates precondition before sorting logic
   - **Note:** Stacks with > 3 elements may also be invalid, but algorithm will only sort top 3

4. **Operation dependencies (`sa`, `ra`, `rra`) - LOW:**
   - **Strategy:** sort_three relies on these operations being defensive
   - **Each operation validates:**
     - NULL pointer checks
     - Minimum element requirements
   - **Layered defense:** sort_three's checks prevent invalid calls
   - **Trust but verify:** Operations perform their own validation

### Defensive Implementation Strategy

**Guard Order:**
```
1. CRITICAL: Check if stack pointer is NULL
2. CRITICAL: Check if dereferenced stack is NULL
3. MEDIUM: Validate stack has at least 3 elements
4. PROCEED: Execute sorting logic
```

**Return Behavior:**
- Returns `void` - no error codes
- Silent failure on invalid input (no sorting performed)
- Relies on defensive operations for additional safety

**Validation Cost:**
- NULL checks: O(1) - two comparisons
- Size check: O(3) = O(1) - constant for 3-element validation
- Total overhead: O(1) - negligible

---

## Edge Cases

### Case 1: Less Than 3 Elements

```c
// Stack: [1, 2]
sort_three(&stack_a);

// DEFENSIVE: Returns early via size check
// No sorting performed (not enough elements)
// STATUS: ✅ Safe - size validation catches this
```

### Case 2: Empty Stack (NULL Dereferenced)

```c
t_stack *stack_a = NULL;
sort_three(&stack_a);

// DEFENSIVE: Returns immediately via !*stack check
// No crash, silent no-op
// STATUS: ✅ Safe - CRITICAL check prevents SEGFAULT
```

### Case 3: NULL Stack Pointer

```c
sort_three(NULL);

// DEFENSIVE: Returns immediately via !stack check
// No crash, cannot dereference NULL pointer
// STATUS: ✅ Safe - CRITICAL check prevents SEGFAULT
```

### Case 4: Negative Numbers

```c
// Stack: [-1, -5, -3]
sort_three(&stack_a);

// Should sort to: [-5, -3, -1]
// Works the same as positive numbers
// STATUS: ✅ Works - comparisons work with negative values
```

### Case 5: Duplicates

```c
// Stack: [2, 2, 1]
sort_three(&stack_a);

// Should sort to: [1, 2, 2]
// Duplicates treated normally
// STATUS: ✅ Works - algorithm handles equal values correctly
```

### Case 6: More Than 3 Elements

```c
// Stack: [4, 3, 2, 1]
sort_three(&stack_a);

// BEHAVIOR: Sorts only top 3 elements
// Result: [2, 3, 4, 1] (first 3 sorted, last unchanged)
// STATUS: ⚠️ Potentially unexpected - caller should validate size
// NOTE: This is typically not called with > 3 elements
```

---

## Time & Space Complexity

### Time Complexity: **O(1)** - Constant Time

**Operations:**
```
Maximum 2 operations needed for any case:
- find_max: O(3) = O(1) for 3 elements
- 0 to 2 swap/rotate operations: O(1)

Total: O(1) ✅

No loops over varying data, fixed size!
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
Variables:
- int max (4 bytes)
- Temporary pointers for operations

No additional allocations
No recursion
Modifies in place

Space = O(1) ✅
```

### Performance Characteristics

```
Best case: 0 operations (already sorted)
Worst case: 2 operations (reverse sorted or cases 2, 6)
Average case: ~1 operation

This is provably optimal for 3 elements!
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
        sort_three(stack_a);  // ← Delegates to sort_three
    else if (size == 4)
        sort_four(stack_a, stack_b);
    // ...
}
```

### Called by sort_four and sort_five

```c
void sort_four(t_stack **stack_a, t_stack **stack_b)
{
    // Move smallest to B
    // ... operations ...

    // Sort remaining 3 in A
    sort_three(stack_a);  // ← Reuses sort_three!

    // Move element back from B
    pa(stack_a, stack_b, 1);
}
```

### Uses Multiple Operations

```c
void sort_three(t_stack **stack_a)
{
    // Uses:
    sa(stack_a, 1);   // Swap
    ra(stack_a, 1);   // Rotate
    rra(stack_a, 1);  // Reverse rotate

    // All operations are needed depending on case
}
```

### Uses find_max

```c
int max = find_max(*stack_a);  // Find maximum value

// Uses max to determine which case we're in
```

---

## Integration with Push_swap

### Scenario: Direct 3-Element Sort

```c
// Input: ./push_swap 2 1 3
// Stack A: [2, 1, 3]

sort_three(&stack_a);

// Identifies: Case 3
// Executes: sa
// Output: "sa"
// Result: [1, 2, 3] ✅
```

### Scenario: Part of Larger Sort

```c
// During sort_five:
// 1. Push 2 smallest to B
// 2. Sort remaining 3 in A using sort_three
// 3. Push back from B

void sort_five(t_stack **a, t_stack **b)
{
    // ... move elements ...

    sort_three(a);  // ← Sort the 3 remaining

    // ... move back ...
}
```

### Scenario: All Cases Example

```c
// Test all 6 permutations

sort_three([1,2,3]); // Output: (nothing)  0 ops
sort_three([1,3,2]); // Output: rra, sa    2 ops
sort_three([2,1,3]); // Output: sa         1 op
sort_three([2,3,1]); // Output: rra        1 op
sort_three([3,1,2]); // Output: ra         1 op
sort_three([3,2,1]); // Output: ra, sa     2 ops
```

---

## 42 Norm Considerations

### Function Structure (Basic)

```c
void	sort_three(t_stack **stack_a)
{
	int	max;

	if (stack_size(*stack_a) < 3)
		return ;
	max = find_max(*stack_a);
	if ((*stack_a)->value == max)
	{
		ra(stack_a, 1);
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a, 1);
	}
	else if ((*stack_a)->next->value == max)
	{
		rra(stack_a, 1);
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a, 1);
	}
	else if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a, 1);
}
```

### Function Structure (Defensive - Recommended)

```c
void	sort_three(t_stack **stack_a)
{
	int	max;

	if (!stack_a || !*stack_a)
		return ;
	if (stack_size(*stack_a) < 3)
		return ;
	max = find_max(*stack_a);
	if ((*stack_a)->value == max)
	{
		ra(stack_a, 1);
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a, 1);
	}
	else if ((*stack_a)->next->value == max)
	{
		rra(stack_a, 1);
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a, 1);
	}
	else if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a, 1);
}
```

**Norm compliance:**
- ✅ Under 25 lines (24 lines with defensive checks)
- ✅ Single responsibility: sorts 3 elements
- ✅ Only 1 variable (max)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Handles all cases optimally
- ✅ Defensive checks add only 2 lines

---

## Common Mistakes

### Mistake 1: Not Validating Input (CRITICAL)

```c
// ❌ WRONG - No defensive checks
void sort_three(t_stack **stack_a)
{
    int max = find_max(*stack_a);  // CRASH if stack_a is NULL!
    // ...
}
```

**✅ Correct:**
```c
if (!stack_a || !*stack_a)
    return;
if (stack_size(*stack_a) < 3)
    return;
// Now safe to proceed
```

**Severity:** CRITICAL - causes SEGFAULT on NULL input
**Defensive Priority:** Must be first checks before any dereference
**Impact:** Without validation, NULL or insufficient elements crash the program

### Mistake 2: Not Using Optimal Solutions (MEDIUM)

```c
// ❌ WRONG - Using bubble sort approach
void sort_three(t_stack **a)
{
    // Multiple passes, 3+ operations
    while (!is_sorted(*a))
    {
        if ((*a)->value > (*a)->next->value)
            sa(a, 1);
        ra(a, 1);
    }
}
// Uses more operations than optimal!
```

**✅ Correct:**
```c
// Hardcoded optimal solutions
// Maximum 2 operations
```

**Severity:** MEDIUM - works but inefficient
**Impact:** Uses more operations than necessary, worse performance

### Mistake 3: Wrong Rotation Direction (HIGH)

```c
// ❌ WRONG
if ((*stack_a)->value == max)
    rra(stack_a, 1);  // Should be ra!
```

**✅ Correct:**
```c
if ((*stack_a)->value == max)
    ra(stack_a, 1);  // Rotate forward to move max down
```

**Severity:** HIGH - produces incorrect sorting
**Impact:** Stack ends up in wrong order, sorting fails

### Mistake 4: Forgetting to Check After Rotation (HIGH)

```c
// ❌ WRONG
if ((*stack_a)->value == max)
    ra(stack_a, 1);
// Forgot to check if swap still needed!
```

**✅ Correct:**
```c
if ((*stack_a)->value == max)
{
    ra(stack_a, 1);
    if ((*stack_a)->value > (*stack_a)->next->value)
        sa(stack_a, 1);  // Additional check
}
```

**Severity:** HIGH - incomplete sorting
**Impact:** Some permutations remain unsorted after rotation

### Mistake 5: Using find_min Instead of find_max (LOW)

```c
// ❌ NOT WRONG but different logic
int min = find_min(*stack_a);
// Would need different if-else tree
```

**✅ Conventional:**
```c
int max = find_max(*stack_a);
// Standard approach, easier to reason about
```

**Severity:** LOW - works but requires different decision tree
**Impact:** More complex logic, harder to maintain

---

## Testing Strategy

### Test 1: All Six Cases

```c
// Case 1: [1,2,3]
assert_operations([1,2,3], 0);

// Case 2: [1,3,2]
assert_operations([1,3,2], 2);

// Case 3: [2,1,3]
assert_operations([2,1,3], 1);

// Case 4: [2,3,1]
assert_operations([2,3,1], 1);

// Case 5: [3,1,2]
assert_operations([3,1,2], 1);

// Case 6: [3,2,1]
assert_operations([3,2,1], 2);
```

### Test 2: Verify Correctness

```c
for (int i = 0; i < 6; i++)
{
    t_stack *stack = create_permutation(i);
    sort_three(&stack);
    assert(is_sorted(stack) == 1);
    free_stack(&stack);
}
```

### Test 3: Operation Count

```c
// Verify no case uses more than 2 operations
for each permutation:
    count = count_operations(sort_three(perm));
    assert(count <= 2);
```

### Test 4: Edge Cases

```c
// Less than 3 elements
sort_three([1,2]);  // Should handle gracefully

// Duplicates
sort_three([2,2,1]);  // Should sort to [1,2,2]

// Negative
sort_three([-1,-5,-3]);  // Should sort to [-5,-3,-1]
```

---

## Defensive Programming Checklist

### Implementation Verification
- [ ] **NULL double pointer check** - `if (!stack_a) return;` is first line
- [ ] **NULL stack check** - `if (!*stack_a) return;` is second check
- [ ] **Size validation** - Verify stack has at least 3 elements before sorting
- [ ] **find_max() call** - Properly calls find_max to determine permutation
- [ ] **Max position check** - Correctly identifies if max is top/middle/bottom
- [ ] **Rotation direction** - Uses `ra` (not `rra`) when max on top
- [ ] **Post-rotation check** - Checks if swap needed after rotation
- [ ] **All 6 cases handled** - Logic covers all possible permutations

### Testing Checklist
- [ ] **NULL double pointer** - `sort_three(NULL)` doesn't crash
- [ ] **Empty stack** - `sort_three(&empty_stack)` doesn't crash
- [ ] **Single element** - `sort_three(&stack_with_one)` doesn't crash
- [ ] **Two elements** - `sort_three(&stack_with_two)` doesn't crash or sort incorrectly
- [ ] **All 6 permutations** - Each of [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1] sorts correctly
- [ ] **Operation count** - No permutation uses more than 2 operations
- [ ] **Negative numbers** - Correctly sorts negative values
- [ ] **Duplicates** - Handles equal values without crashing

### Correctness Verification
- [ ] **Already sorted [1,2,3]** - 0 operations
- [ ] **Case 2 [1,3,2]** - Exactly 2 operations (rra, sa)
- [ ] **Case 3 [2,1,3]** - Exactly 1 operation (sa)
- [ ] **Case 4 [2,3,1]** - Exactly 1 operation (rra)
- [ ] **Case 5 [3,1,2]** - Exactly 1 operation (ra)
- [ ] **Case 6 [3,2,1]** - Exactly 2 operations (ra, sa)

### Defensive Dependencies
- [ ] **find_max has defensive checks** - Verify find_max handles NULL
- [ ] **Operations have defensive checks** - Verify sa, ra, rra handle NULL
- [ ] **stack_size defensive** - If using size check, verify stack_size handles NULL
- [ ] **Layered defense** - sort_three's checks prevent invalid calls to dependencies

---

## Summary

**What sort_three Does:**
1. Validates input (double pointer, dereferenced stack, size)
2. Identifies which of 6 permutations is present
3. Executes optimal hardcoded solution for that case
4. Uses maximum 2 operations
5. Employs sa, ra, and rra operations

**Key Characteristics:**
- ✅ Handles all 6 permutations optimally
- ✅ O(1) time and space
- ✅ Maximum 2 operations
- ✅ Provably optimal algorithm
- ✅ Building block for larger sorts

**Defensive features:**
- ✅ NULL double pointer validation (CRITICAL)
- ✅ Empty stack validation (CRITICAL)
- ✅ Size validation (MEDIUM)
- ✅ Defensive dependencies (LOW - trusts operations' own checks)
- ✅ Silent failure on invalid input
- ✅ No memory allocation (no malloc failure modes)

**Critical Uses:**
- Direct sorting of 3-element stacks
- Called by sort_four and sort_five
- Part of sort_small router
- Foundation of small sorting strategy

**Remember:**
- Always validate input first (NULL checks, size check)
- Use find_max to identify case
- Maximum is on top, middle, or bottom
- Each position has specific solution
- Never need more than 2 operations
- This is mathematically optimal

**Optimization:**
```
6 permutations, each optimally solved:
0 ops: 1 case  (already sorted)
1 op:  3 cases (simple fixes)
2 ops: 2 cases (complex fixes)

Average: 1 operation per sort!
This is the best possible algorithm! ✅
```

---

## Location in Project

**File:** `srcs/sort_small.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 2.2 (Small Sorting Algorithms)

---

## Related Functions

- [sort_small](sort_small.md) - Router that calls sort_three
- [sort_two](sort_two.md) - Simpler: sorts 2 elements
- [sort_four](sort_four.md) - Uses sort_three internally
- [sort_five](sort_five.md) - Uses sort_three internally
- [find_max](find_max.md) - Used to identify case
- [sa](sa.md), [ra](ra.md), [rra](rra.md) - Operations used

---

*Master sort_three and you understand optimal hardcoded sorting - the foundation of efficient small-stack algorithms!*
