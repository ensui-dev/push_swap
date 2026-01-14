# sort_two - Sort Exactly Two Elements

## Function Signature

```c
void sort_two(t_stack **stack_a)
```

**Return type:** `void` - Modifies stack A in place
**Parameter:** `t_stack **stack_a` - Double pointer to the head of stack A

---

## Purpose & Use Case

`sort_two` is a **specialized sorting function** that sorts exactly 2 elements. It's the simplest possible sorting scenario and serves as a base case in the small sorting algorithms. With only 2 elements, there are exactly 2 possible arrangements, making the solution trivial.

### When You'll Use It

You'll call `sort_two` whenever:
1. **Stack has exactly 2 elements** - Detected by `stack_size(stack) == 2`
2. **Called by sort_small** - Router function delegates to sort_two
3. **After reducing larger sorts** - Sometimes sort_three/four/five reduce to 2 elements
4. **Base case optimization** - Simplest non-trivial sort

### Why This Matters

**With 2 elements, there are only 2 possible states:**
```
State 1: SORTED
[1, 2]  ← Already in order
Action: Do nothing! (0 operations)

State 2: UNSORTED
[2, 1]  ← Out of order
Action: Swap! (1 operation)

That's it! Only 2 possibilities!
```

### Real-World Analogy

**Two people in a line:**
```
Scenario 1: They're already in order by height
Shorter → Taller
Action: Nothing needed ✅

Scenario 2: They're in wrong order
Taller → Shorter
Action: Swap positions
Result: Shorter → Taller ✅

Same concept for sorting 2 numbers!
```

---

## Deep Dive: How It Works

### The Single-Comparison Algorithm

**Concept:**
- Check if first element > second element
- If yes: They're out of order, swap them (sa)
- If no: Already sorted, do nothing

### Decision Tree

```
Start: Stack with 2 elements

Check: Is first > second?
         |
    ┌────┴────┐
   YES       NO
    |         |
   SWAP   DO NOTHING
   (sa)   (already sorted)
    |         |
    └────┬────┘
         |
    SORTED! ✅
```

### Visual Examples

**Example 1: Already Sorted**
```
Input: [1, 2]

Check: 1 > 2?
Answer: No

Action: None
Output: [1, 2] ✅
Operations: 0
```

**Example 2: Needs Swap**
```
Input: [2, 1]

Check: 2 > 1?
Answer: Yes!

Action: sa (swap)
Output: [1, 2] ✅
Operations: 1
```

---

## Step-by-Step Implementation

### Step 1: Validate Input

**Safety check:**
```c
if (!stack_a || !*stack_a || !(*stack_a)->next)
    return;
```

**What we're checking:**
```
!stack_a: Double pointer is NULL → Can't proceed
!*stack_a: Stack is empty → Can't sort nothing
!(*stack_a)->next: Less than 2 elements → Can't sort 1 element

Any of these? Return immediately.
```

### Step 2: Compare First Two Elements

**The only check needed:**
```c
if ((*stack_a)->value > (*stack_a)->next->value)
```

**What this means:**
```
(*stack_a)->value: Value of first element (top)
(*stack_a)->next->value: Value of second element

If first > second:
→ Wrong order (descending)
→ Need to swap

If first < second:
→ Correct order (ascending)
→ Already sorted
```

### Step 3: Swap if Needed

**Perform swap:**
```c
sa(stack_a, 1);
```

**What sa does:**
```
Before: [2, 1]
        [0] [1]

After sa: [1, 2]
          [0] [1]

Swaps the top two elements.
The 1 parameter means "print the operation" (sa).
```

---

## Complete Algorithm Pseudocode

```
FUNCTION sort_two(stack_a):
    // Step 1: Validate
    IF stack_a is NULL OR *stack_a is NULL OR only 1 element:
        RETURN  // Can't sort, exit

    // Step 2: Compare
    IF first_element > second_element:
        // Step 3: Swap
        sa(stack_a, 1)  // Print "sa"

    // Done! Stack is now sorted
END FUNCTION
```

---

## Visual Execution Trace

### Example 1: Sorting [2, 1]

```
Initial State:
Stack A: [2] -> [1] -> NULL
         top

Call: sort_two(&stack_a)

Step 1: Validate
stack_a != NULL ✅
*stack_a != NULL ✅
(*stack_a)->next != NULL ✅
Continue

Step 2: Compare
(*stack_a)->value = 2
(*stack_a)->next->value = 1
2 > 1? YES! ✅ Need to swap

Step 3: Swap
Call: sa(&stack_a, 1)

sa operation:
Before: [2] -> [1] -> NULL
After:  [1] -> [2] -> NULL

Output printed: "sa"

Final State:
Stack A: [1] -> [2] -> NULL ✅ SORTED!

Operations used: 1 (sa)
```

### Example 2: Already Sorted [1, 2]

```
Initial State:
Stack A: [1] -> [2] -> NULL

Call: sort_two(&stack_a)

Step 1: Validate
All checks pass ✅

Step 2: Compare
(*stack_a)->value = 1
(*stack_a)->next->value = 2
1 > 2? NO ✅ Already sorted!

Step 3: Skip swap
Condition false, don't execute sa

Final State:
Stack A: [1] -> [2] -> NULL ✅ SORTED!

Operations used: 0 (already sorted)
```

---

## Edge Cases

### Case 1: NULL Pointer

```c
t_stack **stack_a = NULL;

sort_two(stack_a);

// Result: Function returns immediately
// No crash ✅
```

### Case 2: Empty Stack

```c
t_stack *stack_a = NULL;

sort_two(&stack_a);

// Result: Function returns immediately
// No operations performed ✅
```

### Case 3: Single Element

```c
// Stack: [42] -> NULL

sort_two(&stack_a);

// Result: Function returns immediately
// Can't sort 1 element ✅
```

### Case 4: Equal Elements

```c
// Stack: [5, 5] -> NULL

sort_two(&stack_a);

// Check: 5 > 5? No
// Result: No swap, stays [5, 5]
// Already "sorted" ✅
```

### Case 5: Negative Numbers

```c
// Stack: [-1, -5]

sort_two(&stack_a);

// Check: -1 > -5? Yes!
// Action: sa
// Result: [-5, -1] ✅ Sorted (ascending)
```

### Case 6: Mixed Positive/Negative

```c
// Stack: [3, -2]

sort_two(&stack_a);

// Check: 3 > -2? Yes!
// Action: sa
// Result: [-2, 3] ✅ Sorted
```

---

## Time & Space Complexity

### Time Complexity: **O(1)** - Constant Time

**Operations:**
```
1. Validation checks: O(1)
2. One comparison: O(1)
3. At most one swap: O(1)

Total: O(1) ✅

No loops, no recursion, fixed number of operations!
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
No additional variables
No allocations
No recursion
Only modifies existing stack in place

Space = O(1) ✅
```

### Performance Characteristics

```
Best case: 0 operations (already sorted)
Worst case: 1 operation (needs swap)
Average case: 0.5 operations (50% chance of needing swap)

Absolute minimum for sorting 2 elements!
```

---

## Relationship with Other Functions

### Called by sort_small

```c
void sort_small(t_stack **stack_a, t_stack **stack_b)
{
    int size = stack_size(*stack_a);

    if (size == 2)
        sort_two(stack_a);  // ← Delegates to sort_two
    else if (size == 3)
        sort_three(stack_a);
    // ... etc
}
```

### Uses sa Operation

```c
void sort_two(t_stack **stack_a)
{
    if (/* needs swap */)
        sa(stack_a, 1);  // ← Uses swap operation
}

// sa (swap a) - swaps top two elements
```

### Base Case for Larger Sorts

```c
void sort_three(t_stack **stack_a)
{
    // ... complex logic ...

    // Sometimes reduces to 2 elements
    if (stack_size(*stack_a) == 2)
        sort_two(stack_a);  // Handle remaining 2
}
```

---

## Integration with Push_swap

### Scenario: Direct Call

```c
int main(int argc, char **argv)
{
    t_stack *stack_a = init_stack_a(argc, argv);

    int size = stack_size(stack_a);

    if (size == 2)
        sort_two(&stack_a);  // ← Direct call for 2 elements

    free_stack(&stack_a);
    return (0);
}
```

### Scenario: Through sort_small Router

```c
// Input: ./push_swap 5 3
// Stack A: [5, 3]

sort_small(&stack_a, &stack_b);
// ↓
// Calls sort_two(&stack_a)
// ↓
// Executes: sa
// ↓
// Result: [3, 5] ✅
```

### Scenario: After Larger Sort Reduction

```c
// During sort_five:
// Push 2 elements to B
// Sort remaining 3 in A
// Push back from B
// Now A has 5 sorted elements

// But if something went wrong and only 2 remain:
if (stack_size(stack_a) == 2)
    sort_two(&stack_a);  // Safety fallback
```

---

## 42 Norm Considerations

### Function Structure

```c
void	sort_two(t_stack **stack_a)
{
	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a, 1);
}
```

**Norm compliance:**
- ✅ Under 25 lines (only 6 lines!)
- ✅ Single responsibility: sorts 2 elements
- ✅ No variables needed
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Clear, simple logic

### Alternative Implementation

```c
void	sort_two(t_stack **stack_a)
{
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a, 1);
}
```

**Note:** Some implementations skip validation checks if called only through sort_small which already validates. But explicit checks are safer!

---

## Common Mistakes

### Mistake 1: Not Validating Input

```c
// ❌ WRONG
void sort_two(t_stack **stack_a)
{
    if ((*stack_a)->value > (*stack_a)->next->value)  // CRASH if NULL!
        sa(stack_a, 1);
}
```

**✅ Correct:**
```c
if (!stack_a || !*stack_a || !(*stack_a)->next)
    return;
// Now safe to access
```

### Mistake 2: Wrong Comparison Direction

```c
// ❌ WRONG - Using <
if ((*stack_a)->value < (*stack_a)->next->value)
    sa(stack_a, 1);
// Swaps when already sorted! Opposite of what we want
```

**✅ Correct:**
```c
if ((*stack_a)->value > (*stack_a)->next->value)
    sa(stack_a, 1);
// Swaps when out of order
```

### Mistake 3: Always Swapping

```c
// ❌ WRONG
void sort_two(t_stack **stack_a)
{
    sa(stack_a, 1);  // Always swap, even if sorted!
}
// Wastes 1 operation when already sorted
```

**✅ Correct:**
```c
if (/* condition */)  // Only swap when needed
    sa(stack_a, 1);
```

### Mistake 4: Using Wrong Operation

```c
// ❌ WRONG
if ((*stack_a)->value > (*stack_a)->next->value)
    ra(stack_a, 1);  // Rotate doesn't sort 2 elements!
```

**✅ Correct:**
```c
if ((*stack_a)->value > (*stack_a)->next->value)
    sa(stack_a, 1);  // Swap is the right operation
```

### Mistake 5: Forgetting to Pass 1 to sa

```c
// ❌ WRONG
sa(stack_a);  // Missing the print parameter!
// Won't compile if sa expects 2 parameters
```

**✅ Correct:**
```c
sa(stack_a, 1);  // 1 = print the operation
```

---

## Testing Strategy

### Test 1: Basic Sorting

```c
// Test swap needed
stack_a = create_stack([2, 1]);
sort_two(&stack_a);
assert(stack_a->value == 1);
assert(stack_a->next->value == 2);

// Test already sorted
stack_a = create_stack([1, 2]);
sort_two(&stack_a);
assert(stack_a->value == 1);
assert(stack_a->next->value == 2);
```

### Test 2: Edge Cases

```c
// NULL pointer
sort_two(NULL);  // Should not crash

// Empty stack
stack_a = NULL;
sort_two(&stack_a);  // Should not crash

// Single element
stack_a = create_stack([42]);
sort_two(&stack_a);  // Should not crash
assert(stack_a->value == 42);
```

### Test 3: Special Values

```c
// Equal elements
stack_a = create_stack([5, 5]);
sort_two(&stack_a);
assert(stack_a->value == 5);
assert(stack_a->next->value == 5);

// Negative numbers
stack_a = create_stack([-1, -5]);
sort_two(&stack_a);
assert(stack_a->value == -5);
assert(stack_a->next->value == -1);

// Mixed
stack_a = create_stack([3, -2]);
sort_two(&stack_a);
assert(stack_a->value == -2);
assert(stack_a->next->value == 3);
```

### Test 4: Operation Count

```c
// Count operations printed
// Already sorted: should print nothing
stack_a = create_stack([1, 2]);
int ops_before = count_operations();
sort_two(&stack_a);
int ops_after = count_operations();
assert(ops_after - ops_before == 0);

// Needs swap: should print "sa"
stack_a = create_stack([2, 1]);
ops_before = count_operations();
sort_two(&stack_a);
ops_after = count_operations();
assert(ops_after - ops_before == 1);
```

### Test 5: Integration Test

```c
// Full program test
// Input: ./push_swap 5 3
// Expected output: "sa"

// Simulate
stack_a = init_stack_a(2, (char *[]){"5", "3"});
sort_two(&stack_a);

// Verify sorted
assert(is_sorted(stack_a) == 1);

// Verify operation was printed
// (check stdout contains "sa")
```

---

## Summary

**What sort_two Does:**
1. Validates input (2 elements exist)
2. Compares first and second element
3. Swaps if out of order (first > second)
4. Does nothing if already sorted

**Key Characteristics:**
- ✅ Simplest sort function
- ✅ O(1) time and space
- ✅ Maximum 1 operation needed
- ✅ Only uses sa (swap a)
- ✅ Base case for small sorts

**Critical Uses:**
- Direct sorting of 2-element stacks
- Called by sort_small router
- Base case in recursive sorting approaches
- Handles edge case in larger sorts

**Remember:**
- Always validate input
- Use > comparison (not <)
- Only swap when needed (not always)
- Use sa operation
- Pass 1 to print operation

**Optimization:**
```
Best algorithm for 2 elements!
No way to do better than:
- 0 operations if sorted
- 1 operation if unsorted

This is provably optimal ✅
```

---

## Location in Project

**File:** `srcs/sort_small.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 2.2 (Small Sorting Algorithms)

---

## Related Functions

- [sort_small](sort_small.md) - Router function that calls sort_two
- [sort_three](sort_three.md) - Sorts 3 elements (more complex)
- [sort_four](sort_four.md) - Sorts 4 elements
- [sort_five](sort_five.md) - Sorts 5 elements
- [sa](sa.md) - Swap operation used by sort_two
- [is_sorted](is_sorted.md) - Validation function

---

*The simplest sort - but still essential! Master sort_two and you understand the foundation of all small sorting algorithms!*
