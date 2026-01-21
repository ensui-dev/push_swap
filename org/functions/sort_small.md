# sort_small - Router Function for Small Stacks (2-5 Elements)

## Function Signature

```c
void sort_small(t_stack **stack_a, t_stack **stack_b)
```

**Return type:** `void` - Modifies stacks in place
**Parameters:**
- `t_stack **stack_a` - Double pointer to the head of stack A
- `t_stack **stack_b` - Double pointer to the head of stack B (initially empty)

---

## Purpose & Use Case

`sort_small` is a **router function** (also called a dispatcher or orchestrator) that determines the size of the stack and delegates to the appropriate specialized sorting function. It acts as the control center for sorting 2-5 element stacks, ensuring each size uses its optimal algorithm.

### When You'll Use It

You'll call `sort_small` whenever:
1. **Stack has 2-5 elements** - Detected in main sorting logic
2. **Entry point for small sorts** - Single function to handle all small cases
3. **Abstraction layer** - Caller doesn't need to know which specific sort to use
4. **Clean architecture** - Separates size detection from sorting logic

### Why This Design Matters

**Single entry point simplifies the main logic:**
```
Without sort_small (messy):
if (size == 2)
    sort_two(&stack_a);
else if (size == 3)
    sort_three(&stack_a);
else if (size == 4)
    sort_four(&stack_a, &stack_b);
else if (size == 5)
    sort_five(&stack_a, &stack_b);
else
    sort_large(&stack_a, &stack_b);

With sort_small (clean):
if (size <= 5)
    sort_small(&stack_a, &stack_b);  ← Single call!
else
    sort_large(&stack_a, &stack_b);

Much cleaner! ✅
```

### Real-World Analogy

**Restaurant host seating customers:**
```
Host: "How many in your party?"

Party of 2: → Seat at small table (sort_two)
Party of 3: → Seat at medium table (sort_three)
Party of 4: → Seat at large table (sort_four)
Party of 5: → Seat at extra-large table (sort_five)
Party of 6+: → Use different seating area (sort_large)

The host is the "router" - they don't seat anyone themselves,
they just direct parties to the appropriate seating.

sort_small is the host!
```

---

## Deep Dive: How It Works

### The Delegation Pattern

**Concept:**
- Check the size of the stack
- Based on size, call the appropriate specialized sorting function
- Each specialized function is optimized for its exact size
- Router function contains no sorting logic itself

### Decision Flow

```
sort_small() called
       |
       v
   size = ?
       |
    ┌──┴──┐
    |     |
 size<=5  size>5
    |     |
    v     v
dispatch  return
to func   (error)
    |
    ├─── size==2 → sort_two()
    ├─── size==3 → sort_three()
    ├─── size==4 → sort_four()
    └─── size==5 → sort_five()
```

### Routing Table

```
Size | Function    | Operations | Needs Stack B?
-----|-------------|------------|---------------
  2  | sort_two    | 0-1        | No
  3  | sort_three  | 0-2        | No
  4  | sort_four   | ~5-6       | Yes
  5  | sort_five   | ~8-12      | Yes
 6+  | sort_large  | O(n log n) | Yes

sort_small handles sizes 2-5 only!
```

---

## Step-by-Step Implementation

### Step 1: Validate Input (DEFENSIVE)

```c
if (!stack_a || !*stack_a)
    return;
```

**Defensive checks:**
```
!stack_a: Double pointer is NULL → Can't proceed (CRITICAL)
!*stack_a: Stack is empty → Nothing to sort (valid case, return early)

These checks prevent SEGFAULT when calling stack_size or delegated functions.
```

**Defensive Priority:** CRITICAL - Must validate before any dereference

### Step 2: Get Stack Size

```c
int size = stack_size(*stack_a);
```

**Why calculate size?**
```
Need to know how many elements to determine which function to call
stack_size() traverses the stack and counts nodes
O(n) operation, but n is at most 5, so O(1) in practice

Note: stack_size has its own NULL check, but we validate first for clarity
```

### Step 3: Route Based on Size

```c
if (size == 2)
    sort_two(stack_a);
else if (size == 3)
    sort_three(stack_a);
else if (size == 4)
    sort_four(stack_a, stack_b);
else if (size == 5)
    sort_five(stack_a, stack_b);
```

**Decision logic:**
```
Match size to appropriate function
size 2-3: Only need stack_a (no push operations)
size 4-5: Need both stacks (use push operations)
size 0-1: No case matches, returns early (already sorted)
size >5: No case matches, wrong function called (caller error)
```

**Defensive note:** Each delegated function has its own defensive checks

### Step 4: Function Returns

```c
// No explicit return needed (void function)
// Once the delegated function completes, sort_small is done
```

**After delegation:**
```
The specialized function has sorted the stack
sort_small returns control to caller
Stack A is now fully sorted
Stack B is empty (if it was used)

Edge cases (size 0, 1, or >5):
No matching case, function returns immediately
```

---

## Defensive Checks

### Input Validation
| Check | Priority | Failure Mode | Consequence |
|-------|----------|--------------|-------------|
| `!stack_a` | **CRITICAL** | NULL double pointer for stack A | SEGFAULT when dereferencing `*stack_a` |
| `!stack_b` | **MEDIUM** | NULL double pointer for stack B | SEGFAULT if size 4-5 (uses stack B) |
| `!*stack_a` | **MEDIUM** | Empty stack | stack_size returns 0, safe early return |
| stack_size failure | **LOW** | stack_size has own checks | Delegated to stack_size function |

### Why These Checks Matter

1. **NULL stack_a check (`!stack_a`) - CRITICAL:**
   - **Without:** Dereferencing `*stack_a` in stack_size call crashes immediately
   - **With:** Returns safely before attempting size calculation
   - **Cost:** O(1) - single pointer comparison
   - **Benefit:** Prevents crash, essential for router function safety

2. **NULL stack_b check (`!stack_b`) - MEDIUM:**
   - **Without:** sort_four/sort_five will crash when using stack B
   - **With:** Can validate early or delegate to size-specific functions
   - **Cost:** O(1) - single pointer comparison
   - **Benefit:** Prevents crash for 4-5 element sorts

3. **Empty stack handling (`!*stack_a`) - MEDIUM:**
   - **Without:** stack_size handles it, returns 0, no case matches
   - **With:** Explicit early return, clearer intent
   - **Cost:** O(1) - single pointer comparison
   - **Benefit:** Explicit edge case handling, clearer code

### Defensive Implementation Strategy

**Layered Defense:**
- sort_small validates pointers
- stack_size has its own NULL check
- Each sort_two/three/four/five has defensive checks
- Defense-in-depth: multiple layers prevent failures

**Return Behavior:**
- Silent return on invalid input
- Delegates to specialized functions for actual sorting
- Trusts delegated functions' defensive implementations

---

## Complete Algorithm Pseudocode

### Basic Implementation
```
FUNCTION sort_small(stack_a, stack_b):
    // Step 1: Determine size
    size = stack_size(stack_a)

    // Step 2: Route to appropriate function
    IF size == 2:
        sort_two(stack_a)
    ELSE IF size == 3:
        sort_three(stack_a)
    ELSE IF size == 4:
        sort_four(stack_a, stack_b)
    ELSE IF size == 5:
        sort_five(stack_a, stack_b)
    ELSE:
        // Size is 0, 1, or >5
        RETURN  // Nothing to do or wrong function called

    // Done! Stack is sorted
END FUNCTION
```

### Defensive Implementation (Full)
```
FUNCTION sort_small(stack_a, stack_b):
    // DEFENSIVE STEP 1: Validate stack pointers (CRITICAL)
    IF stack_a is NULL:
        RETURN  // Cannot proceed without valid stack A pointer

    // DEFENSIVE STEP 2: Validate stack B pointer (MEDIUM)
    IF stack_b is NULL:
        RETURN  // sort_four/five need stack B

    // DEFENSIVE STEP 3: Check for empty stack (MEDIUM)
    IF *stack_a is NULL:
        RETURN  // Empty stack, nothing to sort

    // Step 4: Determine size
    size = stack_size(*stack_a)  // stack_size has its own NULL check

    // Step 5: Route to appropriate function
    IF size == 2:
        sort_two(stack_a)  // Has own defensive checks
    ELSE IF size == 3:
        sort_three(stack_a)  // Has own defensive checks
    ELSE IF size == 4:
        sort_four(stack_a, stack_b)  // Has own defensive checks
    ELSE IF size == 5:
        sort_five(stack_a, stack_b)  // Has own defensive checks
    ELSE:
        // Size is 0, 1, or >5
        RETURN  // Edge cases: 0/1 already sorted, >5 is caller error

    // Done! Stack is sorted
END FUNCTION
```

---

## Visual Execution Trace

### Example 1: Routing 2 Elements

```
Initial State:
A: [2, 1]  B: []

Call: sort_small(&stack_a, &stack_b)

Step 1: Get size
size = stack_size(A) = 2 ✅

Step 2: Route decision
size == 2? YES! ✅

Step 3: Delegate to sort_two
Call: sort_two(&stack_a)

sort_two executes:
- Compares 2 > 1
- Swaps with sa
- Returns

Result:
A: [1, 2]  B: []

sort_small returns
```

### Example 2: Routing 5 Elements

```
Initial State:
A: [5, 2, 1, 4, 3]  B: []

Call: sort_small(&stack_a, &stack_b)

Step 1: Get size
size = stack_size(A) = 5 ✅

Step 2: Route decision
size == 2? NO
size == 3? NO
size == 4? NO
size == 5? YES! ✅

Step 3: Delegate to sort_five
Call: sort_five(&stack_a, &stack_b)

sort_five executes:
- Pushes 2 minimums to B
- Sorts 3 remaining
- Pushes back
- Returns

Result:
A: [1, 2, 3, 4, 5]  B: []

sort_small returns
```

### Example 3: Already Sorted Stack

```
Initial State:
A: [1, 2, 3]  B: []

Call: sort_small(&stack_a, &stack_b)

Step 1: Get size
size = 3

Step 2: Route
size == 3? YES

Step 3: Delegate
sort_three(&stack_a)

sort_three executes:
- Checks if sorted
- Already sorted, does nothing
- Returns

Result:
A: [1, 2, 3]  B: []
Operations: 0 ✅
```

---

## Edge Cases

### Case 1: Empty Stack

```c
// A: []  B: []

sort_small(&stack_a, &stack_b);

// size = 0
// None of the conditions match
// Function returns immediately
// Safe! ✅
```

### Case 2: Single Element

```c
// A: [42]  B: []

sort_small(&stack_a, &stack_b);

// size = 1
// None of the conditions match
// Already "sorted" by definition
// Returns immediately ✅
```

### Case 3: Size > 5

```c
// A: [6, 5, 4, 3, 2, 1]  B: []

sort_small(&stack_a, &stack_b);

// size = 6
// None of the conditions match
// This should NOT be called for >5 elements
// Caller should use sort_large instead
```

### Case 4: All Functions Handle Their Sizes

```c
// Each size 2-5 is handled optimally
for (int size = 2; size <= 5; size++)
{
    stack = create_random_stack(size);
    sort_small(&stack, &b);
    assert(is_sorted(stack));  // All pass ✅
}
```

---

## Time & Space Complexity

### Time Complexity: **O(1)** - Constant Time

**Operations:**
```
stack_size: O(n) where n ≤ 5, so O(1) in practice
Routing logic: O(1) (simple if-else)
Delegated functions:
- sort_two: O(1)
- sort_three: O(1)
- sort_four: O(1)
- sort_five: O(1)

Total: O(1) ✅

All delegated functions are constant time for fixed sizes!
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
Variable: int size (4 bytes)
No additional allocations
Delegates to functions that use O(1) space

Space = O(1) ✅
```

---

## Relationship with Other Functions

### Called by Main or Sorting Logic

```c
int main(int argc, char **argv)
{
    t_stack *stack_a = init_stack_a(argc, argv);
    t_stack *stack_b = NULL;

    if (is_sorted(stack_a))
        return (0);  // Already sorted

    int size = stack_size(stack_a);

    if (size <= 5)
        sort_small(&stack_a, &stack_b);  // ← Calls sort_small
    else
        sort_large(&stack_a, &stack_b);

    free_stack(&stack_a);
    return (0);
}
```

### Delegates to Specialized Functions

```c
void sort_small(t_stack **a, t_stack **b)
{
    int size = stack_size(*a);

    if (size == 2)
        sort_two(a);          // ← Delegates
    else if (size == 3)
        sort_three(a);        // ← Delegates
    else if (size == 4)
        sort_four(a, b);      // ← Delegates
    else if (size == 5)
        sort_five(a, b);      // ← Delegates
}
```

### Complements sort_large

```c
// Binary decision:
if (size <= 5)
    sort_small(&a, &b);  // Small optimization
else
    sort_large(&a, &b);  // Algorithmic sorting (Turk)
```

---

## Integration with Push_swap

### Scenario: Main Sorting Decision

```c
// User input: ./push_swap 3 1 2
// Stack A: [3, 1, 2]

int size = stack_size(stack_a);  // 3

if (size <= 5)
    sort_small(&stack_a, &stack_b);  // ← Takes this path

// sort_small routes to sort_three
// sort_three sorts [3,1,2] → [1,2,3]
// Output: "sa\nrra" (or similar)
// Result: Sorted! ✅
```

### Scenario: Decision Boundary

```c
// 5 elements: Use sort_small (last small sort)
A: [5, 4, 3, 2, 1]
size = 5 → sort_small → sort_five ✅

// 6 elements: Use sort_large (first large sort)
A: [6, 5, 4, 3, 2, 1]
size = 6 → sort_large → Turk algorithm ✅

// sort_small handles UP TO and INCLUDING 5
// Beyond 5, different approach needed
```

### Scenario: Complete Program Flow

```c
1. Parse input → stack_a
2. Check if sorted → exit if yes
3. Get size
4. IF size <= 5:
     sort_small(&stack_a, &stack_b)  ← Router
   ELSE:
     sort_large(&stack_a, &stack_b)
5. Final rotate (if needed)
6. Free memory
7. Exit
```

---

## 42 Norm Considerations

### Function Structure

```c
void	sort_small(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	size = stack_size(*stack_a);
	if (size == 2)
		sort_two(stack_a);
	else if (size == 3)
		sort_three(stack_a);
	else if (size == 4)
		sort_four(stack_a, stack_b);
	else if (size == 5)
		sort_five(stack_a, stack_b);
}
```

**Norm compliance:**
- ✅ Under 25 lines (only ~12 lines)
- ✅ Single responsibility: routes to appropriate sort
- ✅ Only 1 variable (size)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Clean, readable logic

---

## Common Mistakes

### Mistake 1: Not Validating Pointers (CRITICAL)

```c
// ❌ WRONG - No defensive checks
void sort_small(t_stack **a, t_stack **b)
{
    int size = stack_size(*a);  // CRASH if a is NULL!
    // ...
}
```

**✅ Correct:**
```c
if (!a || !b || !*a)
    return;
int size = stack_size(*a);  // Now safe
```

**Severity:** CRITICAL - causes SEGFAULT on NULL input
**Defensive Priority:** Must be first checks in router function

### Mistake 2: Not Checking Size (HIGH)

```c
// ❌ WRONG - Assuming size without checking
void sort_small(t_stack **a, t_stack **b)
{
    sort_three(a);  // What if size != 3?
}
```

**✅ Correct:**
```c
int size = stack_size(*a);
if (size == 3)
    sort_three(a);  // Only call when appropriate
```

**Severity:** HIGH - calls wrong sorting function, produces incorrect results

### Mistake 3: Handling Wrong Sizes (MEDIUM)

```c
// ❌ WRONG - Trying to sort 6+ elements
if (size == 6)
    sort_six(a, b);  // sort_small shouldn't handle 6+!
```

**✅ Correct:**
```c
// sort_small only handles 2-5
// Caller should use sort_large for 6+
if (size <= 5)
    sort_small(a, b);
else
    sort_large(a, b);
```

**Severity:** MEDIUM - wrong algorithm for input size, inefficient

### Mistake 4: Forgetting Stack B Parameter (HIGH)

```c
// ❌ WRONG - sort_four and sort_five need stack B!
void sort_small(t_stack **a)  // Missing **b parameter
{
    if (size == 4)
        sort_four(a, ???);  // Where's stack_b?
}
```

**✅ Correct:**
```c
void sort_small(t_stack **a, t_stack **b)
{
    if (size == 4)
        sort_four(a, b);  // Both parameters ✅
}
```

**Severity:** HIGH - won't compile or crashes, sort_four/five need stack B

### Mistake 5: Doing Sorting Logic Itself (MEDIUM)

```c
// ❌ WRONG - Router should not contain sorting logic!
void sort_small(t_stack **a, t_stack **b)
{
    int size = stack_size(*a);
    if (size == 2)
    {
        if ((*a)->value > (*a)->next->value)
            sa(a, 1);  // This is sort_two's job!
    }
}
```

**✅ Correct:**
```c
void sort_small(t_stack **a, t_stack **b)
{
    int size = stack_size(*a);
    if (size == 2)
        sort_two(a);  // Delegate, don't implement! ✅
}
```

**Severity:** MEDIUM - violates separation of concerns, harder to maintain

---

## Testing Strategy

### Test 1: All Sizes 2-5

```c
// Test each size routes correctly
for (int size = 2; size <= 5; size++)
{
    stack_a = create_random_stack(size);
    stack_b = NULL;
    sort_small(&stack_a, &stack_b);
    assert(is_sorted(stack_a));
    assert(stack_b == NULL);  // B empty after sort
    free_stack(&stack_a);
}
```

### Test 2: Edge Cases

```c
// Empty stack
stack_a = NULL;
sort_small(&stack_a, &stack_b);  // Should not crash

// Single element
stack_a = create_stack([42]);
sort_small(&stack_a, &stack_b);  // Should not crash

// Already sorted
stack_a = create_stack([1,2,3,4,5]);
ops = count_operations(sort_small);
// Should be minimal (just pb, pa operations)
```

### Test 3: Correctness for All Permutations

```c
// Test all permutations of size 3
int perms[6][3] = {
    {1,2,3}, {1,3,2}, {2,1,3},
    {2,3,1}, {3,1,2}, {3,2,1}
};

for (int i = 0; i < 6; i++)
{
    stack_a = create_stack(perms[i]);
    stack_b = NULL;
    sort_small(&stack_a, &stack_b);
    assert(is_sorted(stack_a));
}
```

### Test 4: Verify Delegation

```c
// Mock the delegated functions to verify they're called

// Test size 2 calls sort_two
stack_a = create_stack([2,1]);
sort_small(&stack_a, &stack_b);
assert(sort_two_was_called);  // Verify routing

// Test size 5 calls sort_five
stack_a = create_stack([5,4,3,2,1]);
sort_small(&stack_a, &stack_b);
assert(sort_five_was_called);  // Verify routing
```

---

## Defensive Programming Checklist

### Implementation Verification
- [ ] **NULL stack_a check** - `if (!stack_a) return;` is first line
- [ ] **NULL stack_b check** - `if (!stack_b) return;` is second check
- [ ] **Empty stack check** - `if (!*stack_a) return;` handles empty case
- [ ] **stack_size call** - Properly calls stack_size after validation
- [ ] **Size routing logic** - Correctly routes to size 2, 3, 4, 5
- [ ] **Edge case handling** - Size 0, 1, and >5 don't crash
- [ ] **Delegation only** - No sorting logic, only routing

### Testing Checklist
- [ ] **NULL double pointer** - `sort_small(NULL, &b)` doesn't crash
- [ ] **NULL stack_b** - `sort_small(&a, NULL)` doesn't crash
- [ ] **Empty stack** - `sort_small(&empty, &b)` doesn't crash
- [ ] **Single element** - `sort_small(&one_element, &b)` returns safely
- [ ] **Size 2** - Routes to sort_two correctly
- [ ] **Size 3** - Routes to sort_three correctly
- [ ] **Size 4** - Routes to sort_four correctly
- [ ] **Size 5** - Routes to sort_five correctly
- [ ] **Size > 5** - Returns without crash (caller error scenario)

### Delegation Verification
- [ ] **sort_two has defensive checks** - Verify sort_two validates input
- [ ] **sort_three has defensive checks** - Verify sort_three validates input
- [ ] **sort_four has defensive checks** - Verify sort_four validates input
- [ ] **sort_five has defensive checks** - Verify sort_five validates input
- [ ] **stack_size defensive** - Verify stack_size handles NULL
- [ ] **Layered defense works** - Multiple validation layers prevent failures

---

## Summary

**What sort_small Does:**
1. Validates input pointers (double pointers for both stacks)
2. Determines the size of stack A
3. Routes to the appropriate specialized sorting function
4. Acts as a clean abstraction layer
5. Handles sizes 2-5 only

**Key Characteristics:**
- ✅ Pure router function (no sorting logic)
- ✅ Single entry point for small sorts
- ✅ O(1) time and space
- ✅ Clean separation of concerns
- ✅ Delegates to optimal implementations

**Defensive features:**
- ✅ NULL stack_a pointer validation (CRITICAL)
- ✅ NULL stack_b pointer validation (MEDIUM)
- ✅ Empty stack handling (MEDIUM)
- ✅ Layered defense with delegated functions (LOW)
- ✅ Silent failure on invalid input
- ✅ Edge case handling (size 0, 1, >5)

**Critical Uses:**
- Main entry point for sorting 2-5 elements
- Abstraction layer in main sorting logic
- Simplifies caller code
- Ensures optimal algorithm for each size

**Remember:**
- Always validate pointers first (CRITICAL)
- Check size before routing
- Route based on size (2, 3, 4, 5)
- Delegate, don't implement sorting
- Handle edge cases (0, 1 elements)
- Only for sizes 2-5 (not 6+)

**Design Pattern:**
```
This is the "Strategy Pattern":
- Runtime decision based on data (size)
- Each strategy is a separate function
- Router selects appropriate strategy
- Clean, maintainable, extensible ✅

If we ever need sort_six, just add:
else if (size == 6)
    sort_six(a, b);

Easy to extend!
```

**Efficiency:**
```
Size 2: 0-1 operations
Size 3: 0-2 operations
Size 4: ~5-6 operations
Size 5: ~8-12 operations

All use optimal hardcoded solutions!
No generic algorithm can beat these! ✅
```

---

## Location in Project

**File:** `srcs/sort_small.c` (router function only)
**Helper Functions File:** `srcs/sort_small_utils.c` (sort_two, sort_three, sort_four, sort_five, rotate_min_to_top)
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 6 (Small Sorting Algorithms)

### File Structure
```
srcs/
├── sort_small.c           # Router function only (~15 lines)
│   └── sort_small()       # Routes to appropriate sort function
│
└── sort_small_utils.c     # All helper sorting functions
    ├── sort_two()         # 2-element sort
    ├── sort_three()       # 3-element sort
    ├── sort_four()        # 4-element sort
    ├── rotate_min_to_top() # Static helper for sort_five
    └── sort_five()        # 5-element sort
```

**Why this structure:**
- 42 Norm: Maximum 5 functions per file
- sort_small.c: 1 function (router)
- sort_small_utils.c: 5 functions (sort_two, sort_three, sort_four, rotate_min_to_top, sort_five)
- Clean separation: routing logic vs. sorting implementations

---

## Related Functions

- **Delegates to:**
  - [sort_two](sort_two.md) - Handles 2 elements
  - [sort_three](sort_three.md) - Handles 3 elements
  - [sort_four](sort_four.md) - Handles 4 elements
  - [sort_five](sort_five.md) - Handles 5 elements

- **Complements:**
  - [sort_large](sort_large.md) - Handles 6+ elements

- **Uses:**
  - [stack_size](stack_size.md) - Determines which function to call

- **Called by:**
  - Main program logic
  - Primary sorting coordinator

---

*sort_small is the control center - it doesn't do the work itself, but it ensures the right specialist handles each job!*
