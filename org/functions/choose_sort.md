# choose_sort - Router Function for Sorting Algorithms

## Function Signature

```c
void choose_sort(t_stack **stack_a, t_stack **stack_b)
```

**Return type:** `void` - No return value
**Parameters:**
- `t_stack **stack_a` - Pointer to stack A pointer
- `t_stack **stack_b` - Pointer to stack B pointer

---

## Purpose & Use Case

`choose_sort` is a **routing function** that selects the appropriate sorting algorithm based on stack size. It's the decision point that optimizes your program by choosing specialized algorithms for small inputs and general algorithms for large inputs.

### When You'll Use It

You'll call `choose_sort` to:
1. **Determine stack size** - Count elements
2. **Route to optimal algorithm** - Small vs large
3. **Simplify main logic** - Single sort entry point
4. **Optimize performance** - Best algorithm for each case

### Why This Matters

**Algorithm selection strategy:**
```
Stack size ≤ 5:  Use sort_small (hardcoded optimal)
Stack size > 5:  Use sort_large (general algorithm)

Why this split?
- Small stacks: Few operations possible
  → Hardcoded optimal solutions
  → sort_two, sort_three, sort_four, sort_five
  
- Large stacks: Many combinations
  → General algorithm needed
  → Turk algorithm, chunk method, etc.
```

---

## Deep Dive: How It Works

### The Decision Tree

```
choose_sort()
    ↓
Get size = stack_size(stack_a)
    ↓
    ├─ if size ≤ 5 → sort_small(stack_a, stack_b)
    │                     ↓
    │                     ├─ if size == 2 → sort_two()
    │                     ├─ if size == 3 → sort_three()
    │                     ├─ if size == 4 → sort_four()
    │                     └─ if size == 5 → sort_five()
    │
    └─ if size > 5 → sort_large(stack_a, stack_b)
                          ↓
                          (Turk algorithm or chunks)
```

### Step-by-Step Process

#### Step 1: Get Stack Size

```c
int size = stack_size(*stack_a);
```

**Count elements** in stack A

#### Step 2: Decision Based on Size

```c
if (size <= 5)
    sort_small(stack_a, stack_b);
else
    sort_large(stack_a, stack_b);
```

**Simple binary decision:**
- Small: Specialized algorithms
- Large: General algorithm

---

## Visual Execution Trace

### Example 1: Small Stack (3 elements)

```
Stack: [5] → [3] → [1] → NULL

═══════════════════════════════════════
STEP 1: Get Size
═══════════════════════════════════════
stack_size(stack_a)
Count nodes: [5], [3], [1]
size = 3

═══════════════════════════════════════
STEP 2: Check Size
═══════════════════════════════════════
size = 3
3 ≤ 5? YES

═══════════════════════════════════════
STEP 3: Route to Small Sort
═══════════════════════════════════════
sort_small(stack_a, stack_b)
    ↓
    size = 3
    Call sort_three(stack_a)
    ↓
    Execute optimal operations
    Output: ra, sa

═══════════════════════════════════════
RESULT
═══════════════════════════════════════
Stack sorted with minimal operations ✓
```

### Example 2: Large Stack (100 elements)

```
Stack: 100 elements...

═══════════════════════════════════════
STEP 1: Get Size
═══════════════════════════════════════
stack_size(stack_a)
size = 100

═══════════════════════════════════════
STEP 2: Check Size
═══════════════════════════════════════
size = 100
100 ≤ 5? NO

═══════════════════════════════════════
STEP 3: Route to Large Sort
═══════════════════════════════════════
sort_large(stack_a, stack_b)
    ↓
    Execute Turk algorithm
    or chunk-based sorting
    ↓
    Output: many operations

═══════════════════════════════════════
RESULT
═══════════════════════════════════════
Stack sorted efficiently ✓
```

---

## Complete Algorithm Pseudocode

```
FUNCTION choose_sort(stack_a, stack_b):
    // Step 1: Determine size
    size = stack_size(*stack_a)

    // Step 2: Route based on size
    IF size <= 5:
        sort_small(stack_a, stack_b)
    ELSE:
        sort_large(stack_a, stack_b)
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: Size 2

```c
// Stack: [2] → [1] → NULL
choose_sort(&stack_a, &stack_b);
// Routes to sort_small → sort_two
// Output: sa (if needed)
```

### Edge Case 2: Size 5 (Boundary)

```c
// Stack: 5 elements
choose_sort(&stack_a, &stack_b);
// Routes to sort_small → sort_five
// Uses specialized algorithm
```

### Edge Case 3: Size 6 (Just Over Boundary)

```c
// Stack: 6 elements
choose_sort(&stack_a, &stack_b);
// Routes to sort_large
// Uses general algorithm
```

### Edge Case 4: Size 500

```c
// Stack: 500 elements
choose_sort(&stack_a, &stack_b);
// Routes to sort_large
// Must be efficient!
```

---

## Time & Space Complexity

### Time Complexity: O(1) for routing

```
Operations:
- stack_size(): O(n)
- if-else: O(1)
- function call: O(1)

Routing overhead: O(n) for size calculation
Actual sorting: Depends on algorithm called
```

### Space Complexity: O(1)

```
Only local variables
No allocation
O(1) constant space
```

---

## Why This Design?

### Separation of Concerns

```
main() → High-level flow
    ↓
choose_sort() → Algorithm selection
    ↓
sort_small()/sort_large() → Implementation
```

**Benefits:**
- main() doesn't need to know sorting details
- Easy to change size threshold
- Clear responsibility separation

### Optimization Point

```
Easy to adjust:
if (size <= 5)  // Could be 3, 4, 5, 6...
    sort_small();

Threshold tuning:
- Smaller: More hardcoded cases
- Larger: More general algorithm usage
```

---

## 42 Norm Considerations

### Implementation Example

```c
void    choose_sort(t_stack **stack_a, t_stack **stack_b)
{
    int size;

    size = stack_size(*stack_a);
    if (size <= 5)
        sort_small(stack_a, stack_b);
    else
        sort_large(stack_a, stack_b);
}
```

**Norm compliant:**
- ~8 lines ✓
- Single responsibility ✓
- Clear logic ✓

---

## Common Mistakes

### Mistake 1: Wrong Threshold

```c
❌ WRONG:
if (size < 5)  // Excludes size 5!
    sort_small();

✓ CORRECT:
if (size <= 5)  // Includes size 5
    sort_small();
```

### Mistake 2: Not Checking Size

```c
❌ WRONG:
void choose_sort(t_stack **stack_a, t_stack **stack_b)
{
    // Always use one algorithm
    sort_large(stack_a, stack_b);
}

Problem: Inefficient for small stacks

✓ CORRECT:
// Check size and route appropriately
```

---

## Integration with Push_swap

### Called from main

```c
int main(int argc, char **argv)
{
    t_stack *stack_a = init_stack_a(argc, argv);
    t_stack *stack_b = NULL;

    if (!is_sorted(stack_a))
    {
        choose_sort(&stack_a, &stack_b);  // Single call
    }

    free_stack(&stack_a);
    free_stack(&stack_b);
    return (0);
}
```

---

## Testing Strategy

### Test Size Boundaries

```bash
# Size 1 (already sorted, won't call choose_sort)
$ ./push_swap 42

# Size 2
$ ./push_swap 2 1
sa

# Size 5 (boundary)
$ ./push_swap 5 4 3 2 1
# Should use sort_five

# Size 6 (just over)
$ ./push_swap 6 5 4 3 2 1
# Should use sort_large

# Size 100
$ ./push_swap $(seq 1 100 | shuf)
# Should use sort_large
```

---

## Summary

1. **Calculates** stack size
2. **Decides** based on threshold (≤5)
3. **Routes** to appropriate function
4. **Optimizes** by using best algorithm

**Key insight:** This tiny router function is a design pattern that separates decision-making from implementation. It makes your code modular and easy to optimize.

---

## Location in Project

**File:** `srcs/main.c` or `srcs/sort.c`
**Header:** `includes/push_swap.h`

**Function prototype:**
```c
void choose_sort(t_stack **stack_a, t_stack **stack_b);
```

---

## Related Functions

**Calls:**
- `stack_size()` - Get element count
- `sort_small()` - For ≤5 elements
- `sort_large()` - For >5 elements

**Called by:**
- `main()` - Program orchestrator

---

*Remember: Sometimes the simplest functions have the biggest impact on architecture. This router makes your entire sorting system modular and maintainable!*
