# calculate_cost - Calculate Move Costs for All Elements in Stack B

## Function Signature

```c
void calculate_cost(t_stack *stack_a, t_stack *stack_b)
```

**Return type:** `void` - Modifies cost fields in stack B nodes
**Parameters:**
- `t_stack *stack_a` - Pointer to stack A
- `t_stack *stack_b` - Pointer to stack B

---

## Purpose & Use Case

`calculate_cost` is the **optimization engine** of the Turk algorithm. It assigns position indices, finds target positions in A for each element in B, and calculates the total rotation costs (cost_a and cost_b) needed to move each element from B to A. This enables finding the cheapest move.

### When You'll Use It

You'll call `calculate_cost` when you need to:
1. **Turk algorithm phase 2** - Before each push from B to A
2. **Cost analysis** - Determine optimal move sequence
3. **Find cheapest element** - Prepare data for find_cheapest
4. **Update after moves** - Recalculate after stack changes
5. **Optimize sorting** - Core of cost-based optimization

### Why Cost Calculation Matters

**Find the cheapest move to reduce operations:**
```
Stack B elements need to return to A:
Element 1: 5 rotations in A, 2 in B → Total: 7
Element 2: 3 rotations in A, 8 in B → Total: 11
Element 3: 1 rotation in A, 1 in B → Total: 2 ✅ CHEAPEST!

Without cost calculation: Random order, ~9 average operations
With cost calculation: Always pick cheapest, ~2-4 average operations

Massive optimization! This is why Turk algorithm is efficient.
```

### Real-World Analogy

**Calculating delivery costs to find best route:**
```
Delivery truck has 10 packages in cargo bay (B).
Each package needs delivery to specific address on main route (A).

For each package, calculate:
1. Where does it go on main route? (target position in A)
2. How many stops to get truck there? (rotations in A)
3. How deep is package in cargo? (rotations in B)
4. Total cost = stops + cargo depth

Pick package with lowest total cost!
Deliver it, then recalculate for remaining packages.

calculate_cost does this for stack elements!
```

---

## Deep Dive: How It Works

### The Three-Step Process

**Concept:**
1. **Assign positions**: Update current positions in both stacks
2. **Find targets**: For each element in B, find where it should go in A
3. **Calculate costs**: Compute rotation costs for both stacks

### Algorithm Visualization

**Example Stacks:**
```
Stack A: [100, 75, 50, 25]
Indices: [3,   2,  1,  0]
Positions: [0, 1, 2, 3]

Stack B: [60, 40, 90]
Indices: [?]
Positions: [0, 1, 2]

Step 1: Assign positions
✅ Positions updated in both stacks

Step 2: Find targets for each B element

Element at B[0] (value=60, index unknown, just for example):
  Where does 60 fit in A?
  A: [100, 75, 50, 25]
  60 fits between 75 and 50
  Target position in A: 2

Element at B[1] (value=40):
  Where does 40 fit in A?
  A: [100, 75, 50, 25]
  40 fits between 50 and 25
  Target position in A: 3

Element at B[2] (value=90):
  Where does 90 fit in A?
  A: [100, 75, 50, 25]
  90 fits between 100 and 75
  Target position in A: 1

Step 3: Calculate costs

Element B[0]:
  Current position in B: 0
  Target position in A: 2

  Cost B: Position 0 → 0 rotations (already at top)
  Cost A: Position 2 → 2 rotations OR size-2 reverse rotations
         Choose minimum: min(2, 4-2) = 2 forward rotations

  cost_b = 0
  cost_a = 2
  Total: 2

Element B[1]:
  Current position: 1
  Target position: 3

  Cost B: 1 rotation forward OR 3-1=2 reverse
         Choose: 1 forward (smaller)
  Cost A: 3 rotations forward OR 4-3=1 reverse
         Choose: -1 (negative = reverse)

  cost_b = 1
  cost_a = -1
  Total: |1| + |-1| = 2

Element B[2]:
  Current position: 2
  Target position: 1

  Cost B: 2 forward OR 3-2=1 reverse
         Choose: -1 (negative = reverse)
  Cost A: 1 forward OR 4-1=3 reverse
         Choose: 1 forward

  cost_b = -1
  cost_a = 1
  Total: |-1| + |1| = 2

All have equal total cost of 2!
Pick first one (or implement tie-breaker)
```

---

## Step-by-Step Implementation

### Step 1: Assign Positions

**Update position fields:**
```c
assign_position(stack_a);
assign_position(stack_b);
```

**Why necessary:**
```
Positions change after every operation
Must update before calculating costs
Position = distance from top (0, 1, 2, ...)
```

### Step 2: Iterate Through Stack B

**Process each element:**
```c
t_stack *b = stack_b;
while (b)
{
    // Calculate costs for this element
    b = b->next;
}
```

### Step 3: Find Target Position in A

**For current B element:**
```c
int target_pos = find_target_position(stack_a, b->index);
```

**What this returns:**
```
Position in A where element should be inserted
Based on index ordering (sorted final position)
```

### Step 4: Calculate Rotation Costs

**For Stack B (to top):**
```c
int size_b = stack_size(stack_b);
b->cost_b = calculate_move_cost(b->pos, size_b);
```

**For Stack A (to target):**
```c
int size_a = stack_size(stack_a);
b->cost_a = calculate_move_cost(target_pos, size_a);
```

**Cost calculation logic:**
```
If position < size/2:
  Use forward rotation (ra/rb)
  Cost = position (positive)

If position >= size/2:
  Use reverse rotation (rra/rrb)
  Cost = -(size - position) (negative)

Negative cost = reverse rotation
Positive cost = forward rotation
```

---

## Complete Algorithm Pseudocode

```
FUNCTION calculate_cost(stack_a, stack_b):
    // Step 1: Update positions
    assign_position(stack_a)
    assign_position(stack_b)

    // Get sizes
    size_a = stack_size(stack_a)
    size_b = stack_size(stack_b)

    // Step 2: Process each element in B
    current = stack_b
    WHILE current is not NULL:
        // Step 3: Find where this element belongs in A
        target_pos = find_target_position(stack_a, current.index)

        // Step 4: Calculate rotation cost for B
        // (cost to bring current element to top of B)
        IF current.pos < size_b / 2:
            current.cost_b = current.pos  // Forward rotation
        ELSE:
            current.cost_b = -(size_b - current.pos)  // Reverse rotation

        // Step 5: Calculate rotation cost for A
        // (cost to rotate A to target position)
        IF target_pos < size_a / 2:
            current.cost_a = target_pos  // Forward rotation
        ELSE:
            current.cost_a = -(size_a - target_pos)  // Reverse rotation

        // Move to next element
        current = current.next

    // Done! All costs calculated
END FUNCTION
```

---

## Visual Execution Trace

### Example: Calculate Costs

```
Initial State:
Stack A: [100, 75, 50, 25]
Positions: [0, 1, 2, 3]
Size A: 4

Stack B: [60, 40, 90]
Positions: [0, 1, 2]
Size B: 3

Call: calculate_cost(stack_a, stack_b)

Step 1: Assign positions
✅ Positions already shown above

Step 2-5: Process B[0] (value=60, assume index=2)

Find target in A:
  target_pos = find_target_position(A, index=2)
  A indices: [3, 2, 1, 0]
  Index 2 should go between indices 3 and 1
  Target position: 2

Calculate cost_b:
  Current pos in B: 0
  Size B: 3
  0 < 3/2? Yes (0 < 1.5)
  cost_b = 0 (already at top)

Calculate cost_a:
  Target pos in A: 2
  Size A: 4
  2 < 4/2? No (2 >= 2)
  cost_a = -(4 - 2) = -2 (reverse rotation)

B[0] costs: cost_a=-2, cost_b=0
Total: |−2| + |0| = 2

Step 2-5: Process B[1] (value=40, index=1)

Find target: position 3
Calculate cost_b:
  pos=1, size=3
  1 < 1.5? Yes
  cost_b = 1

Calculate cost_a:
  pos=3, size=4
  3 < 2? No
  cost_a = -(4-3) = -1

B[1] costs: cost_a=-1, cost_b=1
Total: |−1| + |1| = 2

Step 2-5: Process B[2] (value=90, index=3)

Find target: position 1
Calculate cost_b:
  pos=2, size=3
  2 < 1.5? No
  cost_b = -(3-2) = -1

Calculate cost_a:
  pos=1, size=4
  1 < 2? Yes
  cost_a = 1

B[2] costs: cost_a=1, cost_b=-1
Total: |1| + |−1| = 2

Final State:
Stack B with costs:
[0] cost_a=-2, cost_b=0, total=2
[1] cost_a=-1, cost_b=1, total=2
[2] cost_a=1, cost_b=-1, total=2

Ready for find_cheapest()!
```

---

## Edge Cases

### Case 1: Empty Stack B

```c
calculate_cost(stack_a, NULL);
// Loop never executes
// No crash ✅
```

### Case 2: Single Element in B

```c
// B: [60]
// Position: 0
// cost_b always 0 (already at top)
// cost_a depends on target in A
```

### Case 3: Element Already at Top

```c
// B element at position 0
// cost_b = 0 (no rotation needed)
// Only cost_a matters
```

### Case 4: Element at Bottom

```c
// B element at last position
// Compare forward vs reverse
// Usually reverse is cheaper
```

### Case 5: Symmetric Position

```c
// Element exactly at middle
// Forward and reverse cost equal
// Convention: use forward (positive)
```

---

## Time & Space Complexity

### Time Complexity: **O(n × m)** where n=|A|, m=|B|

**Analysis:**
```
assign_position(A): O(n)
assign_position(B): O(m)

For each element in B (m iterations):
  find_target_position(): O(n) - searches through A
  calculate costs: O(1)

Total: O(n) + O(m) + O(m × n) = O(n × m)

Typical case: Both stacks similar size
O(n × m) ≈ O(n²)
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
Local variables only
No allocations
Modifies existing node fields
Space = O(1) ✅
```

---

## Relationship with Other Functions

### Called by sort_large

```c
void sort_large(t_stack **a, t_stack **b)
{
    push_chunks_to_b(a, b, 5);

    while (*b)
    {
        calculate_cost(*a, *b);  // ← Recalculate each iteration
        execute_cheapest_move(a, b);
    }

    final_rotate(a);
}
```

### Uses Helper Functions

```c
void calculate_cost(t_stack *a, t_stack *b)
{
    assign_position(a);  // ← Update positions
    assign_position(b);

    while (b)
    {
        int target = find_target_position(a, b->index);  // ← Find target
        b->cost_b = calculate_move_cost(b->pos, size_b);  // ← Calculate
        b->cost_a = calculate_move_cost(target, size_a);
        b = b->next;
    }
}
```

---

## 42 Norm Considerations

```c
void	calculate_cost(t_stack *stack_a, t_stack *stack_b)
{
	int	size_a;
	int	size_b;

	assign_position(stack_a);
	assign_position(stack_b);
	size_a = stack_size(stack_a);
	size_b = stack_size(stack_b);
	while (stack_b)
	{
		stack_b->cost_b = calculate_move_cost(stack_b->pos, size_b);
		stack_b->cost_a = calculate_move_cost(
			find_target_position(stack_a, stack_b->index), size_a);
		stack_b = stack_b->next;
	}
}
```

---

## Common Mistakes

### Mistake 1: Not Updating Positions First

```c
// ❌ WRONG - Using outdated positions!
void calculate_cost(t_stack *a, t_stack *b)
{
    // Forgot: assign_position(a);
    // Forgot: assign_position(b);

    while (b)
    {
        // Using wrong b->pos values!
    }
}
```

### Mistake 2: Using Absolute Values in Cost Fields

```c
// ❌ WRONG - Lost direction information!
b->cost_a = abs(cost);  // Can't tell if forward or reverse!
```

**✅ Correct:**
```c
// Keep sign: positive=forward, negative=reverse
b->cost_a = cost;  // Could be -3 (reverse) or +3 (forward)
```

### Mistake 3: Forgetting to Update After Moves

```c
// ❌ WRONG
calculate_cost(a, b);  // Calculate once
while (b)
{
    execute_cheapest_move(a, b);
    // Forgot to recalculate! Costs now wrong!
}
```

**✅ Correct:**
```c
while (b)
{
    calculate_cost(a, b);  // Recalculate each iteration
    execute_cheapest_move(a, b);
}
```

---

## Summary

**What calculate_cost Does:**
1. Updates positions in both stacks
2. For each element in B, finds target position in A
3. Calculates rotation costs for both stacks
4. Stores costs in node fields for later optimization

**Key Characteristics:**
- ✅ O(n × m) time complexity
- ✅ Enables optimal move selection
- ✅ Core of Turk algorithm optimization
- ✅ Must be called before each move

**Remember:**
- Always update positions first
- Negative cost = reverse rotation
- Positive cost = forward rotation
- Recalculate after every move
- Foundation of cost-based sorting

---

## Location in Project

**File:** `srcs/cost.c` or `srcs/turk_algorithm.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 7 (Large Sorting Algorithm)

---

## Related Functions

- [assign_position](assign_position.md) - Updates positions first
- [find_target_position](find_target_position.md) - Finds where to insert
- [calculate_move_cost](calculate_move_cost.md) - Calculates individual costs
- [find_cheapest](find_cheapest.md) - Uses calculated costs
- [execute_cheapest_move](execute_cheapest_move.md) - Executes optimal move

---

*Cost calculation is the brain of Turk algorithm - without it, we're sorting randomly!*
