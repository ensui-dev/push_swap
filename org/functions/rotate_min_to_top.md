# rotate_min_to_top - Static Helper for sort_five

## Function Signature

```c
static void rotate_min_to_top(t_stack **stack_a, int size)
```

**Return type:** `void` - Modifies stack A in place
**Parameters:**
- `t_stack **stack_a` - Double pointer to the head of stack A
- `int size` - Current size of the stack (5 or 4)

**Scope:** `static` - File-local, only visible within sort_small.c

---

## Purpose & Use Case

`rotate_min_to_top` is a **static helper function** that finds the minimum element in stack A and rotates it to the top position using the shortest path. It's designed specifically to support `sort_five` by handling the rotation logic for both phases (5-element and 4-element).

### When You'll Use It

You'll call `rotate_min_to_top` whenever:
1. **sort_five Phase 1** - Rotate minimum to top of 5-element stack
2. **sort_five Phase 2** - Rotate second-minimum to top of 4-element stack
3. **Reusable rotation** - Same logic, different stack sizes

### Why This Helper Exists

**42 Norm compliance:**
```
sort_five with full rotation logic: ~30 lines
sort_five with helper:              ~14 lines ✅

Helper function:                    ~18 lines ✅

Both under 25 lines! Norm compliant!
```

### Why Static?

**`static` keyword benefits:**
```
1. File-local scope - Only visible in sort_small.c
2. No namespace pollution - Won't conflict with other files
3. Compiler optimization - Can inline the function
4. Encapsulation - Implementation detail, not public API
5. No header declaration needed - Keeps push_swap.h clean
```

---

## Deep Dive: How It Works

### Rotation Strategy by Position

**For 5-element stack (size == 5):**
```
Position 0: Already on top     → 0 operations
Position 1: sa                 → 1 operation
Position 2: ra, ra             → 2 operations (forward faster)
Position 3: rra, rra           → 2 operations (backward faster)
Position 4: rra                → 1 operation

Optimal path chosen for each position!
```

**For 4-element stack (size == 4):**
```
Position 0: Already on top     → 0 operations
Position 1: sa                 → 1 operation
Position 2: rra, rra           → 2 operations (backward faster)
Position 3: rra                → 1 operation

Different optimal paths due to smaller size!
```

### Decision Logic

```
The key insight: optimal rotation direction depends on both
position AND stack size.

For position 2:
- 5 elements: ra, ra (2 forward) is same as rra, rra, rra (3 backward)
              → Use ra, ra (fewer operations)
- 4 elements: rra, rra (2 backward) is same as ra, ra (2 forward)
              → Both equal, but rra, rra matches pattern

For position 3:
- 5 elements: rra, rra (2 backward) beats ra, ra, ra (3 forward)
- 4 elements: rra (1 backward) beats ra, ra, ra (3 forward)
```

---

## Step-by-Step Implementation

### Step 1: Find Minimum Index

```c
int min_idx = find_min_index(*stack_a);
```

**Purpose:**
```
Locate the minimum element's position (0-indexed)
Position determines which rotation strategy to use
find_min_index traverses stack and returns position
```

### Step 2: Handle Position 1 (Both Sizes)

```c
if (min_idx == 1)
    sa(stack_a, 1);
```

**Logic:**
```
Minimum is second element
Simple swap brings it to top
Works for both 5 and 4 element stacks
Single operation - optimal
```

### Step 3: Handle Position 2 (Size-Dependent)

```c
else if (min_idx == 2 && size == 5)
{
    ra(stack_a, 1);
    ra(stack_a, 1);
}
else if (min_idx == 2 && size == 4)
{
    rra(stack_a, 1);
    rra(stack_a, 1);
}
```

**Logic:**
```
For 5 elements: 2 forward rotations optimal
For 4 elements: 2 backward rotations optimal

The combined condition handles this:
(min_idx == 3 && size == 5) || (min_idx == 2 && size == 4)
```

### Step 4: Handle Position 3/4 (Size-Dependent)

```c
else if ((min_idx == 3 && size == 5) || (min_idx == 2 && size == 4))
{
    rra(stack_a, 1);
    rra(stack_a, 1);
}
else if ((min_idx == 4 && size == 5) || (min_idx == 3 && size == 4))
    rra(stack_a, 1);
```

**Logic:**
```
Position 3 (5-element) and Position 2 (4-element): 2 backward rotations
Position 4 (5-element) and Position 3 (4-element): 1 backward rotation

Combined conditions reduce code duplication
```

---

## Complete Algorithm Pseudocode

### Basic Implementation
```
FUNCTION rotate_min_to_top(stack_a, size):
    // Step 1: Find minimum position
    min_idx = find_min_index(stack_a)

    // Step 2: Rotate based on position and size
    IF min_idx == 1:
        sa(stack_a)  // Swap brings second to top

    ELSE IF min_idx == 2 AND size == 5:
        ra(stack_a)  // 2 forward rotations
        ra(stack_a)

    ELSE IF (min_idx == 3 AND size == 5) OR (min_idx == 2 AND size == 4):
        rra(stack_a)  // 2 backward rotations
        rra(stack_a)

    ELSE IF (min_idx == 4 AND size == 5) OR (min_idx == 3 AND size == 4):
        rra(stack_a)  // 1 backward rotation

    // Position 0: Already on top, no action needed
END FUNCTION
```

### Defensive Implementation (Full)
```
FUNCTION rotate_min_to_top(stack_a, size):
    // Note: Defensive checks are in sort_five (caller)
    // This helper trusts that stack_a is valid
    // Layered defense: find_min_index has own NULL check

    // Step 1: Find minimum position
    min_idx = find_min_index(*stack_a)  // Has defensive checks

    // Step 2: Rotate based on position and size
    IF min_idx == 1:
        sa(stack_a, 1)  // sa has defensive checks

    ELSE IF min_idx == 2 AND size == 5:
        ra(stack_a, 1)  // ra has defensive checks
        ra(stack_a, 1)

    ELSE IF (min_idx == 3 AND size == 5) OR (min_idx == 2 AND size == 4):
        rra(stack_a, 1)  // rra has defensive checks
        rra(stack_a, 1)

    ELSE IF (min_idx == 4 AND size == 5) OR (min_idx == 3 AND size == 4):
        rra(stack_a, 1)

    // Position 0: Already on top, no action needed
END FUNCTION
```

---

## Visual Execution Trace

### Example 1: 5-Element Stack, Min at Position 2

```
Initial State:
A: [5, 3, 1, 4, 2]
    0  1  2  3  4
         ^
         min at position 2

Call: rotate_min_to_top(&stack_a, 5)

Step 1: Find minimum
min_idx = find_min_index(A) = 2

Step 2: Check conditions
min_idx == 1? NO
min_idx == 2 AND size == 5? YES!

Step 3: Execute ra, ra
ra(&stack_a, 1)
After: A: [3, 1, 4, 2, 5]

ra(&stack_a, 1)
After: A: [1, 4, 2, 5, 3]
        ^
        Minimum now on top! ✅

Operations used: 2 (ra, ra)
```

### Example 2: 4-Element Stack, Min at Position 3

```
Initial State:
A: [4, 3, 5, 2]
    0  1  2  3
            ^
            min at position 3

Call: rotate_min_to_top(&stack_a, 4)

Step 1: Find minimum
min_idx = find_min_index(A) = 3

Step 2: Check conditions
min_idx == 1? NO
min_idx == 2 AND size == 5? NO (size is 4)
(min_idx == 3 AND size == 5) OR (min_idx == 2 AND size == 4)? NO
(min_idx == 4 AND size == 5) OR (min_idx == 3 AND size == 4)? YES!

Step 3: Execute rra
rra(&stack_a, 1)
After: A: [2, 4, 3, 5]
        ^
        Minimum now on top! ✅

Operations used: 1 (rra)
```

### Example 3: Min Already on Top

```
Initial State:
A: [1, 5, 3, 4, 2]
    ^
    min at position 0

Call: rotate_min_to_top(&stack_a, 5)

Step 1: Find minimum
min_idx = find_min_index(A) = 0

Step 2: Check conditions
min_idx == 1? NO
min_idx == 2 AND size == 5? NO
All other conditions? NO

Step 3: No action taken
min_idx == 0 means already on top

Operations used: 0 ✅
```

---

## Defensive Checks

### Input Validation Strategy

| Check | Location | Priority | Rationale |
|-------|----------|----------|-----------|
| `!stack_a` | sort_five (caller) | CRITICAL | Caller validates before calling helper |
| `!*stack_a` | sort_five (caller) | CRITICAL | Caller ensures stack exists |
| size validation | sort_five (caller) | MEDIUM | Caller ensures correct size |
| find_min_index NULL | find_min_index | LOW | Layered defense |
| Operation NULL checks | sa/ra/rra | LOW | Operations self-protect |

### Why No Defensive Checks in Helper?

**Deliberate design decision:**
```
1. Caller (sort_five) already validates all inputs
2. Adding redundant checks wastes lines (Norm constraint)
3. Static function = controlled calling context
4. Layered defense from called functions (find_min_index, operations)
5. Trust the caller - it's in the same file!

This is NOT removing safety, just organizing where checks occur.
```

### Layered Defense Diagram

```
sort_five validates → rotate_min_to_top trusts → find_min_index validates
         ↓                      ↓                         ↓
     [CRITICAL]            [TRUSTED]                   [BACKUP]
         ↓                      ↓                         ↓
    Stops NULL           Proceeds safely            Extra safety
```

---

## Edge Cases

### Case 1: Minimum at Position 0

```c
// A: [1, 5, 3, 4, 2]  (min already first)

rotate_min_to_top(&stack_a, 5);

// No conditions match
// Function returns immediately
// No operations performed ✅
```

### Case 2: Minimum at Last Position (5-element)

```c
// A: [5, 3, 4, 2, 1]  (min at position 4)

rotate_min_to_top(&stack_a, 5);

// min_idx == 4 AND size == 5 matches
// Single rra brings min to top
// Result: [1, 5, 3, 4, 2] ✅
```

### Case 3: Minimum at Last Position (4-element)

```c
// A: [4, 3, 5, 2]  (min at position 3)

rotate_min_to_top(&stack_a, 4);

// (min_idx == 3 AND size == 4) matches
// Single rra brings min to top
// Result: [2, 4, 3, 5] ✅
```

---

## Time & Space Complexity

### Time Complexity: **O(n)** where n ≤ 5

**Operations:**
```
find_min_index: O(n) to traverse stack
Rotations: O(1) per rotation, max 2 rotations

Total: O(n) but n ≤ 5, so effectively O(1)
```

### Space Complexity: **O(1)**

**Memory used:**
```
Variable: int min_idx (4 bytes)
No additional allocations
No recursion

Space = O(1) ✅
```

---

## Relationship with Other Functions

### Called by sort_five

```c
void sort_five(t_stack **stack_a, t_stack **stack_b)
{
    // ... validation ...
    rotate_min_to_top(stack_a, 5);  // ← First call (5 elements)
    pb(stack_a, stack_b, 1);
    rotate_min_to_top(stack_a, 4);  // ← Second call (4 elements)
    pb(stack_a, stack_b, 1);
    // ...
}
```

### Uses find_min_index

```c
int min_idx = find_min_index(*stack_a);  // Finds position
```

### Uses Multiple Operations

```c
sa(stack_a, 1);   // Swap
ra(stack_a, 1);   // Rotate forward
rra(stack_a, 1);  // Rotate backward
```

---

## 42 Norm Considerations

### Function Structure

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

**Norm compliance:**
- ✅ Under 25 lines (18 lines)
- ✅ `static` keyword for file-local scope
- ✅ Single responsibility: rotate minimum to top
- ✅ Only 1 variable (min_idx)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Combined conditions reduce code duplication

---

## Common Mistakes

### Mistake 1: Forgetting `static` Keyword (MEDIUM)

```c
// ❌ WRONG - Missing static
void rotate_min_to_top(t_stack **stack_a, int size)
```

**✅ Correct:**
```c
static void rotate_min_to_top(t_stack **stack_a, int size)
```

**Severity:** MEDIUM - compiles but pollutes namespace
**Impact:** Function visible to other files, may cause linking conflicts

### Mistake 2: Wrong Rotation Direction (HIGH)

```c
// ❌ WRONG - Using ra instead of rra for position 3
else if (min_idx == 3 && size == 5)
{
    ra(stack_a, 1);  // 3 operations needed!
    ra(stack_a, 1);
    ra(stack_a, 1);
}
```

**✅ Correct:**
```c
else if (min_idx == 3 && size == 5)
{
    rra(stack_a, 1);  // Only 2 operations!
    rra(stack_a, 1);
}
```

**Severity:** HIGH - inefficient, more operations than necessary
**Impact:** Sort works but uses suboptimal operation count

### Mistake 3: Not Handling Size Difference (HIGH)

```c
// ❌ WRONG - Same logic for all sizes
else if (min_idx == 2)
{
    ra(stack_a, 1);  // Wrong for 4-element stack!
    ra(stack_a, 1);
}
```

**✅ Correct:**
```c
else if (min_idx == 2 && size == 5)
{
    ra(stack_a, 1);
    ra(stack_a, 1);
}
else if (min_idx == 2 && size == 4)
{
    rra(stack_a, 1);  // Different for 4 elements
    rra(stack_a, 1);
}
```

**Severity:** HIGH - wrong rotation path for 4-element stack
**Impact:** Minimum not moved to top correctly

### Mistake 4: Adding Redundant Defensive Checks (LOW)

```c
// ❌ UNNECESSARY - Caller already validates
static void rotate_min_to_top(t_stack **stack_a, int size)
{
    if (!stack_a || !*stack_a)  // Wastes lines!
        return;
    // ...
}
```

**✅ Better:**
```c
static void rotate_min_to_top(t_stack **stack_a, int size)
{
    // Trust caller (sort_five) validated inputs
    int min_idx = find_min_index(*stack_a);
    // ...
}
```

**Severity:** LOW - works but wastes precious Norm lines
**Impact:** May push function over 25 lines

---

## Defensive Programming Checklist

### Implementation Verification
- [ ] **static keyword** - Function declared as `static`
- [ ] **find_min_index call** - Correctly finds minimum position
- [ ] **Position 0 handled** - No action when min already on top
- [ ] **Position 1 handled** - sa for both sizes
- [ ] **Position 2 (5-elem)** - ra, ra
- [ ] **Position 2 (4-elem)** - rra, rra
- [ ] **Position 3 (5-elem)** - rra, rra
- [ ] **Position 3 (4-elem)** - rra
- [ ] **Position 4 (5-elem)** - rra
- [ ] **Combined conditions** - Size-dependent logic correct

### Testing Checklist
- [ ] **5-elem, pos 0** - No operations
- [ ] **5-elem, pos 1** - 1 operation (sa)
- [ ] **5-elem, pos 2** - 2 operations (ra, ra)
- [ ] **5-elem, pos 3** - 2 operations (rra, rra)
- [ ] **5-elem, pos 4** - 1 operation (rra)
- [ ] **4-elem, pos 0** - No operations
- [ ] **4-elem, pos 1** - 1 operation (sa)
- [ ] **4-elem, pos 2** - 2 operations (rra, rra)
- [ ] **4-elem, pos 3** - 1 operation (rra)

### Caller Verification
- [ ] **sort_five validates pointers** - Before calling helper
- [ ] **sort_five validates size** - Ensures >= 5 elements
- [ ] **Correct size passed** - 5 for first call, 4 for second

---

## Summary

**What rotate_min_to_top Does:**
1. Finds the minimum element's position in stack A
2. Calculates the optimal rotation path based on position and size
3. Executes minimum number of operations to bring min to top
4. Handles both 5-element and 4-element stacks

**Key Characteristics:**
- ✅ Static helper function (file-local)
- ✅ Reusable for different stack sizes
- ✅ Optimal rotation path selection
- ✅ Under 25 lines (Norm compliant)
- ✅ Single responsibility

**Defensive features:**
- ✅ Trusts caller (sort_five) for input validation
- ✅ Layered defense via find_min_index
- ✅ Operations have their own defensive checks
- ✅ No redundant validation (saves lines)

**Critical Uses:**
- Called twice by sort_five
- Enables sort_five to stay under 25 lines
- Encapsulates rotation logic complexity

**Remember:**
- Must be `static` (file-local scope)
- Must be placed BEFORE sort_five in file
- Size parameter determines rotation strategy
- Position 0 = no action needed
- Trust caller's validation

---

## Location in Project

**File:** `srcs/sort_small_utils.c`
**Scope:** `static` (not in header)
**Position:** Before sort_five function
**Phase in TODO:** Phase 6 (Small Sorting Algorithms)

---

## Related Functions

- [sort_five](sort_five.md) - Caller, the only function that uses this helper
- [find_min_index](find_min_index.md) - Used to locate minimum position
- [sa](sa.md) - Swap operation for position 1
- [ra](ra.md) - Forward rotation
- [rra](rra.md) - Backward rotation

---

*rotate_min_to_top is a focused helper - it does one thing well and enables sort_five to stay Norm compliant!*
