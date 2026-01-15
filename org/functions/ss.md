# ss - Swap Top Two Elements of Both Stacks Simultaneously

## Function Signature

```c
void ss(t_stack **stack_a, t_stack **stack_b, int print)
```

**Return type:** `void` - No return value (modifies both stacks in place)
**Parameter 1:** `t_stack **stack_a` - Double pointer to stack A
**Parameter 2:** `t_stack **stack_b` - Double pointer to stack B
**Parameter 3:** `int print` - If 1, print "ss\n"; if 0, silent operation

---

## Purpose & Use Case

`ss` (swap both) executes **sa and sb simultaneously**, swapping the top two elements of BOTH stacks in a single operation. This is an optimization that counts as **only 1 move** instead of 2, making it crucial for achieving optimal sorting performance.

### When You'll Use It

You'll call `ss` whenever:
1. **Both stacks need swapping** - Top 2 elements of A AND B are in wrong order
2. **Optimization matters** - Reducing move count is critical
3. **Parallel operations** - Both stacks require the same adjustment
4. **Efficient sorting** - Cutting moves in half compared to separate swaps

### Why This Matters

**ss provides significant move reduction:**
```
Without ss (separate operations):
sa    // Move 1
sb    // Move 2
Total: 2 moves

With ss (combined operation):
ss    // Move 1 (does both!)
Total: 1 move

Result: 50% move reduction! ✅
```

**In push_swap scoring:**
- Fewer moves = better grade
- ss counts as 1 move, not 2
- Can make difference between pass/fail on tight benchmarks

---

## Deep Dive: How It Works

### The SS Operation Visualized

**Before `ss`:**
```
Stack A:                Stack B:
[5] <- top              [9] <- top
[2] <- second           [4] <- second
[8]                     [1]
[3]                     [6]
```

**After `ss`:**
```
Stack A:                Stack B:
[2] <- top (swapped!)   [4] <- top (swapped!)
[5] <- second           [9] <- second
[8]                     [1]
[3]                     [6]
```

**What happened:**
1. Top two of A swapped: [5,2] → [2,5]
2. Top two of B swapped: [9,4] → [4,9]
3. **Both happened in ONE operation**
4. All other elements unchanged

### Execution Flow

**ss internally calls sa and sb:**
```
ss(&stack_a, &stack_b, 1):
    1. Call sa(&stack_a, 0)  // Silent mode (no print)
    2. Call sb(&stack_b, 0)  // Silent mode (no print)
    3. If print == 1:
           write "ss\n"      // Print once for both swaps
```

### Why Silent Mode in sa/sb?

**Important:** When ss calls sa and sb, it passes `print = 0`:
```c
sa(&stack_a, 0);  // 0 = don't print "sa"
sb(&stack_b, 0);  // 0 = don't print "sb"

if (print)
    ft_printf("ss\n");  // Print "ss" once
```

**Result:**
```
// Output is "ss" not "sa\nsb\n"
ss

// This counts as 1 move, not 2!
```

---

## Step-by-Step Implementation

### Step 1: Execute SA (Silently)

**Swap top 2 of stack A without printing:**
```c
sa(&stack_a, 0);  // 0 = silent mode
```

**What this does:**
- If A has 2+ elements: swaps them
- If A has <2 elements: does nothing
- No output to stdout

### Step 2: Execute SB (Silently)

**Swap top 2 of stack B without printing:**
```c
sb(&stack_b, 0);  // 0 = silent mode
```

**What this does:**
- If B has 2+ elements: swaps them
- If B has <2 elements: does nothing
- No output to stdout

### Step 3: Print Operation (Optional)

**If print flag is set, output "ss":**
```c
if (print)
    ft_printf("ss\n");
```

**Why this matters:**
- Tells the tester this was 1 combined operation
- Not 2 separate operations
- Counts as single move in scoring

---

## Complete Algorithm Pseudocode

```
FUNCTION ss(stack_a, stack_b, print):
    // Step 1: Swap A silently
    CALL sa(stack_a, 0)  // 0 = don't print

    // Step 2: Swap B silently
    CALL sb(stack_b, 0)  // 0 = don't print

    // Step 3: Print combined operation
    IF print == 1:
        PRINT "ss\n"

    RETURN
END FUNCTION
```

**Simplicity key:**
- Reuses sa and sb logic
- No duplicate pointer manipulation
- Clean, maintainable code

---

## Visual Execution Trace

### Example: Swap [5, 2, 8] and [9, 4, 1]

**Initial State:**
```
A: [5] -> [2] -> [8] -> NULL
B: [9] -> [4] -> [1] -> NULL
```

**After Step 1 (sa silently):**
```
A: [2] -> [5] -> [8] -> NULL  ✅ Swapped!
B: [9] -> [4] -> [1] -> NULL  (unchanged yet)
No output yet
```

**After Step 2 (sb silently):**
```
A: [2] -> [5] -> [8] -> NULL  (stays swapped)
B: [4] -> [9] -> [1] -> NULL  ✅ Swapped!
No output yet
```

**After Step 3 (print):**
```
A: [2] -> [5] -> [8] -> NULL
B: [4] -> [9] -> [1] -> NULL
Output: "ss\n"  ✅
```

---

## Edge Cases

### Case 1: Both Stacks Empty
```c
t_stack *a = NULL;
t_stack *b = NULL;

ss(&a, &b, 1);

// Result:
// - sa does nothing (NULL stack)
// - sb does nothing (NULL stack)
// - Nothing printed (optional: could still print "ss")
// - No crashes
```

### Case 2: A Has 2+, B Empty
```c
// Before
A: [5] -> [2] -> NULL
B: NULL

// Execute
ss(&a, &b, 1);

// After
A: [2] -> [5] -> NULL  ✅ A swapped
B: NULL                    B unchanged

// Output: "ss\n"
// Still valid - ss executed even though only A swapped
```

### Case 3: A Empty, B Has 2+
```c
// Before
A: NULL
B: [9] -> [4] -> [1] -> NULL

// Execute
ss(&a, &b, 1);

// After
A: NULL                    A unchanged
B: [4] -> [9] -> [1] -> NULL  ✅ B swapped

// Output: "ss\n"
// Valid - B was swapped
```

### Case 4: Both Have Exactly 2 Elements
```c
// Before
A: [5] -> [2] -> NULL
B: [9] -> [4] -> NULL

// Execute
ss(&a, &b, 1);

// After
A: [2] -> [5] -> NULL  ✅
B: [4] -> [9] -> NULL  ✅

// Perfect case - both fully swapped
```

### Case 5: Both Have 1 Element
```c
// Before
A: [5] -> NULL
B: [9] -> NULL

// Execute
ss(&a, &b, 1);

// After
A: [5] -> NULL  (no change)
B: [9] -> NULL  (no change)

// Valid but pointless - neither stack can swap
```

### Case 6: Large Stacks
```c
// Before
A: [1] -> [2] -> [3] -> [4] -> [5] -> NULL
B: [10] -> [20] -> [30] -> [40] -> NULL

// Execute
ss(&a, &b, 1);

// After
A: [2] -> [1] -> [3] -> [4] -> [5] -> NULL  ✅
B: [20] -> [10] -> [30] -> [40] -> NULL     ✅

// Only top 2 of each swapped, rest unchanged
```

---

## Time & Space Complexity

### Time Complexity: **O(1)** - Constant Time

**Operations performed:**
1. Call sa - O(1)
2. Call sb - O(1)
3. Optional print - O(1)

**Total: O(1)** - Always the same time regardless of stack sizes!

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
- No additional allocations
- sa and sb each use O(1) space
- No recursion
- No temporary structures

**Total: O(1)** - Fixed memory footprint

---

## Move Count Economics

### Scenario 1: Need to swap both stacks

**Option A: Separate operations**
```c
sa(&stack_a, 1);  // Output: "sa\n"  - Move 1
sb(&stack_b, 1);  // Output: "sb\n"  - Move 2
// Total: 2 moves
```

**Option B: Combined operation**
```c
ss(&stack_a, &stack_b, 1);  // Output: "ss\n"  - Move 1
// Total: 1 move  ✅ BETTER!
```

**Savings:** 50% move reduction

### Scenario 2: Only one stack needs swapping

**If only A needs swap:**
```c
sa(&stack_a, 1);  // 1 move - correct choice
// DON'T use ss - wastes the operation on B
```

**If only B needs swap:**
```c
sb(&stack_b, 1);  // 1 move - correct choice
// DON'T use ss unnecessarily
```

### When to Choose ss

**Use ss when:**
- Both A and B need their top 2 swapped
- Every move counts (optimization phase)
- Both swaps contribute to sorting goal

**Don't use ss when:**
- Only one stack needs swapping
- Either stack has <2 elements
- The swaps don't contribute to sorting

---

## 42 Norm Considerations

### Function Signature
```c
void	ss(t_stack **stack_a, t_stack **stack_b, int print)
{
    sa(stack_a, 0);
    sb(stack_b, 0);
    if (print)
        ft_printf("ss\n");
}
```

**Norm compliance:**
- ✅ No variables needed (under 5 variable limit)
- ✅ Only 5 lines (well under 25 line limit)
- ✅ Single responsibility (coordinate sa and sb)
- ✅ Tab between return type and name
- ✅ Proper formatting

### No Complexity
**ss is beautifully simple:**
- Delegates to existing functions
- No pointer manipulation
- No validation needed (sa/sb handle it)
- Clean and maintainable

---

## Common Mistakes

### ❌ Mistake 1: Duplicating sa/sb Logic
```c
// WRONG - Reimplementing swap logic
void ss(t_stack **stack_a, t_stack **stack_b, int print)
{
    // Manually swapping A...
    if (*stack_a && (*stack_a)->next) {
        // ... pointer manipulation ...
    }
    // Manually swapping B...
    if (*stack_b && (*stack_b)->next) {
        // ... pointer manipulation ...
    }
}
// Code duplication! Hard to maintain!
```

**✅ Correct approach:**
```c
void ss(t_stack **stack_a, t_stack **stack_b, int print)
{
    sa(stack_a, 0);  // Reuse existing logic
    sb(stack_b, 0);
    if (print)
        ft_printf("ss\n");
}
```

### ❌ Mistake 2: Printing sa and sb
```c
// WRONG - Prints both operations separately
void ss(t_stack **stack_a, t_stack **stack_b, int print)
{
    sa(stack_a, 1);  // Prints "sa"
    sb(stack_b, 1);  // Prints "sb"
}
// Output: "sa\nsb\n" - counts as 2 moves! ❌
```

**✅ Correct:**
```c
void ss(t_stack **stack_a, t_stack **stack_b, int print)
{
    sa(stack_a, 0);  // Silent
    sb(stack_b, 0);  // Silent
    if (print)
        ft_printf("ss\n");  // Print once
}
// Output: "ss\n" - counts as 1 move! ✅
```

### ❌ Mistake 3: Always Printing
```c
// WRONG - Ignores print flag
void ss(t_stack **stack_a, t_stack **stack_b, int print)
{
    sa(stack_a, 0);
    sb(stack_b, 0);
    ft_printf("ss\n");  // Always prints!
}
```

**✅ Correct:**
```c
if (print)
    ft_printf("ss\n");  // Only print if requested
```

### ❌ Mistake 4: Wrong Order
```c
// WRONG - Printing before operations
void ss(t_stack **stack_a, t_stack **stack_b, int print)
{
    if (print)
        ft_printf("ss\n");
    sa(stack_a, 0);  // Operations after print
    sb(stack_b, 0);
}
// Operations happen AFTER we announce them!
```

**✅ Correct:**
```c
sa(stack_a, 0);  // Operations first
sb(stack_b, 0);
if (print)
    ft_printf("ss\n");  // Then announce
```

### ❌ Mistake 5: Single Pointer Parameters
```c
// WRONG - Can't modify stack heads
void ss(t_stack *stack_a, t_stack *stack_b, int print)
{
    // Can't pass these to sa/sb which need double pointers!
}
```

**✅ Use double pointers:**
```c
void ss(t_stack **stack_a, t_stack **stack_b, int print)
```

---

## Testing Strategy

### Test 1: Both Stacks Normal
```c
// Setup
t_stack *a = create_stack(5, 2, 8);     // A: [5, 2, 8]
t_stack *b = create_stack(9, 4, 1);     // B: [9, 4, 1]

// Execute
ss(&a, &b, 1);

// Verify A
assert(a->value == 2);                  // Was 5
assert(a->next->value == 5);            // Was 2
assert(a->next->next->value == 8);      // Unchanged

// Verify B
assert(b->value == 4);                  // Was 9
assert(b->next->value == 9);            // Was 4
assert(b->next->next->value == 1);      // Unchanged
```

### Test 2: Only A Has 2+ Elements
```c
t_stack *a = create_stack(5, 2, 8);
t_stack *b = stack_new(9);              // Only 1 element

ss(&a, &b, 1);

// A should swap
assert(a->value == 2);
// B should be unchanged
assert(b->value == 9);
assert(b->next == NULL);
```

### Test 3: Only B Has 2+ Elements
```c
t_stack *a = stack_new(5);
t_stack *b = create_stack(9, 4, 1);

ss(&a, &b, 1);

// A unchanged
assert(a->value == 5);
// B should swap
assert(b->value == 4);
assert(b->next->value == 9);
```

### Test 4: Both Empty
```c
t_stack *a = NULL;
t_stack *b = NULL;

ss(&a, &b, 1);

assert(a == NULL);
assert(b == NULL);
// Should not crash
```

### Test 5: Print Flag
```c
// Test silent mode
ss(&a, &b, 0);  // Should not print

// Test print mode
ss(&a, &b, 1);  // Should print "ss\n"
```

### Test 6: Idempotent (Double ss)
```c
// Setup
t_stack *a = create_stack(5, 2);
t_stack *b = create_stack(9, 4);

// Save original
int a_first = a->value;
int a_second = a->next->value;
int b_first = b->value;
int b_second = b->next->value;

// Execute twice
ss(&a, &b, 1);
ss(&a, &b, 1);

// Should return to original
assert(a->value == a_first);
assert(a->next->value == a_second);
assert(b->value == b_first);
assert(b->next->value == b_second);
```

---

## Integration with Push_swap

### Optimization in Sorting
```c
// Check if both stacks need swapping
bool a_needs_swap = needs_swap(stack_a);
bool b_needs_swap = needs_swap(stack_b);

if (a_needs_swap && b_needs_swap)
{
    ss(&stack_a, &stack_b, 1);  // 1 move instead of 2!
}
else if (a_needs_swap)
    sa(&stack_a, 1);
else if (b_needs_swap)
    sb(&stack_b, 1);
```

### In Checker Program
```c
// Parsing instructions
if (strcmp(instruction, "ss") == 0)
    ss(&stack_a, &stack_b, 0);  // Silent mode for checker
```

### Move Counter
```c
int move_count = 0;

ss(&stack_a, &stack_b, 1);
move_count++;  // Increment by 1, not 2!
```

---

## Real-World Usage Example

### Sorting scenario where ss is optimal

```c
// State
A: [4, 2, 1, 3]
B: [6, 5]

// Both need swapping!
// A: 4 and 2 should swap
// B: 6 and 5 should swap

// Suboptimal approach (2 moves):
sa(&a, 1);  // Move 1
sb(&b, 1);  // Move 2

// Optimal approach (1 move):
ss(&a, &b, 1);  // Move 1

// Result (same for both):
A: [2, 4, 1, 3]
B: [5, 6]

// But ss saved 1 move!
```

---

## Performance Notes

### ss vs sa+sb

**Algorithmic equivalence:**
```
ss(&a, &b, 1) ≡ sa(&a, 1) + sb(&b, 1)
```
**Result:** Same final state

**Move count difference:**
```
ss:     1 move
sa+sb:  2 moves
```
**Result:** ss is 50% better!

### When ss Makes the Difference

In tight benchmarks:
- 100 numbers: ss might save 5-10 moves
- 500 numbers: ss might save 20-50 moves
- These savings can change your grade!

### Detection Pattern
```c
// Pseudo-code for ss optimization
for each state in sorting:
    if top_2_of_A_need_swap AND top_2_of_B_need_swap:
        use ss
        saved_moves++
```

---

## Summary

**What ss Does:**
- Executes sa and sb in one operation
- Counts as 1 move instead of 2
- Critical for move count optimization
- Simple implementation leveraging existing functions

**Key Points:**
- ✅ Use when BOTH stacks need top-2 swap
- ✅ Always call sa/sb with print=0
- ✅ Print "ss\n" once if requested
- ✅ 50% move reduction when applicable
- ✅ Must validate both stacks independently

**Remember:**
1. ss = sa + sb but counts as 1 move
2. Both operations happen even if one fails
3. Order: operations first, then print
4. Don't use ss when only one stack needs swapping
5. This optimization can make or break your grade!

---

## Location in Project

**File:** `srcs/operations_swap.c`
**Header:** `includes/push_swap.h`
**Category:** Phase 4 - Stack Operations
**Type:** Combined Swap Operation

---

## Related Functions

- [sa](sa.md) - Swap top 2 of stack A (called by ss)
- [sb](sb.md) - Swap top 2 of stack B (called by ss)
- [rr](rr.md) - Combined rotate (similar concept)
- [rrr](rrr.md) - Combined reverse rotate (similar concept)

---

*ss is your secret weapon for optimal move counts - use it wisely!*
