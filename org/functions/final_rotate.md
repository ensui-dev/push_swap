# final_rotate - Rotate Stack A Until Minimum at Top

## Function Signature

```c
void final_rotate(t_stack **a)
```

**Return type:** `void` - Modifies stack A
**Parameter:** `t_stack **a` - Pointer to stack A

---

## Purpose & Use Case

`final_rotate` is the **final step** of the sorting algorithm. After all elements are back in stack A (potentially out of order), this function rotates the stack until the element with the smallest index (index 0) is at the top, completing the sort.

### Why Final Rotation is Needed

```
After Turk algorithm phase 2:
Stack A: [idx 3, idx 4, idx 0, idx 1, idx 2]
         Not sorted! idx 0 should be at top

After final_rotate:
Stack A: [idx 0, idx 1, idx 2, idx 3, idx 4]
         ✅ Fully sorted!

The elements are in correct relative order,
just need to rotate to start with minimum.
```

### Real-World Analogy

```
Circular conveyor belt with sorted boxes:
[Box 3][Box 4][Box 0][Box 1][Box 2]

Find Box 0, rotate belt until Box 0 at pickup point:
[Box 0][Box 1][Box 2][Box 3][Box 4] ✅

final_rotate does this for the stack!
```

---

## Algorithm

```
1. Find position of element with index 0 (minimum)
2. Determine optimal rotation direction:
   - If pos < size/2: Use ra (forward)
   - If pos >= size/2: Use rra (reverse)
3. Rotate until minimum at top
```

---

## Implementation

```c
void	final_rotate(t_stack **a)
{
	int	min_pos;
	int	size;

	// Find position of minimum index (index 0)
	min_pos = find_min_index_position(*a);
	size = stack_size(*a);

	// Choose rotation direction
	if (min_pos < size / 2)
	{
		// Forward rotation is cheaper
		while (min_pos > 0)
		{
			ra(a, 1);
			min_pos--;
		}
	}
	else
	{
		// Reverse rotation is cheaper
		while (min_pos < size)
		{
			rra(a, 1);
			min_pos++;
		}
	}
}
```

### Helper Function

```c
int	find_min_index_position(t_stack *stack)
{
	int		min_idx;
	int		min_pos;
	t_stack	*current;

	if (!stack)
		return (0);
	min_idx = stack->index;
	min_pos = 0;
	current = stack;
	while (current)
	{
		if (current->index < min_idx)
		{
			min_idx = current->index;
			min_pos = current->pos;
		}
		current = current->next;
	}
	return (min_pos);
}
```

---

## Visual Example

```
Stack A after phase 2:
Values:  [75, 100, 25, 50]
Indices: [2,  3,   0,  1]
Positions: [0, 1, 2, 3]
Size: 4

Step 1: Find minimum index
Minimum index: 0 (value 25)
Position of index 0: 2

Step 2: Choose rotation direction
pos = 2, size = 4
2 < 4/2? No (2 >= 2)
Use reverse rotation (rra)

Step 3: Calculate rotations needed
Reverse: size - pos = 4 - 2 = 2 rotations

Step 4: Execute
rra: [50, 75, 100, 25]
rra: [25, 50, 75, 100] ✅

Final:
Values:  [25, 50, 75, 100]
Indices: [0,  1,  2,  3]
✅ Fully sorted!
```

---

## Time & Space Complexity

### Time Complexity: **O(n)** - Linear

```
Find minimum position: O(n)
Rotate to top: O(n) worst case

Total: O(n)

Best case: O(1) if already at top
Worst case: O(n) if at bottom
Average: O(n/2) = O(n)
```

### Space Complexity: **O(1)** - Constant

```
Few local variables
No allocations
In-place rotations
```

---

## Edge Cases

### Case 1: Already at Top

```c
// Stack: [idx 0, idx 1, idx 2, idx 3]
// min_pos = 0
// No rotations needed ✅
```

### Case 2: At Bottom

```c
// Stack: [idx 1, idx 2, idx 3, idx 0]
// min_pos = 3, size = 4
// Reverse rotation: 1 rra
// More efficient than 3 ra ✅
```

### Case 3: Exactly at Middle

```c
// Stack size: 10, min_pos = 5
// 5 < 10/2? No (5 >= 5)
// Use reverse: 5 rra operations
// (Same as 5 ra, but convention uses reverse)
```

### Case 4: Single Element

```c
// Stack: [idx 0]
// Already sorted, no rotation ✅
```

### Case 5: Two Elements

```c
// Stack: [idx 1, idx 0]
// min_pos = 1
// 1 < 2/2? No (1 >= 1)
// Use rra: 1 operation ✅
```

---

## Optimization

### Direction Selection

```
Always choose cheaper rotation:

Position 2 in stack of 10:
- Forward: 2 ra operations
- Reverse: 8 rra operations
- Choose forward ✅

Position 8 in stack of 10:
- Forward: 8 ra operations
- Reverse: 2 rra operations
- Choose reverse ✅

This optimization saves up to n/2 operations!
```

---

## Integration with Push_swap

### Complete Sort Flow

```c
void push_swap(t_stack **a, t_stack **b)
{
	// Validate and parse
	if (is_sorted(*a))
		return;

	// Choose algorithm
	int size = stack_size(*a);
	if (size == 2)
		sort_two(a);
	else if (size == 3)
		sort_three(a);
	else if (size <= 5)
		sort_small(a, b);
	else
	{
		// Large sort
		assign_index(*a);
		sort_large(a, b);  // Includes final_rotate
	}

	// Stack now sorted!
}
```

### In sort_large

```c
void sort_large(t_stack **a, t_stack **b)
{
	push_chunks_to_b(a, b, 5);

	while (*b)
	{
		calculate_cost(*a, *b);
		execute_cheapest_move(a, b, find_cheapest(*b));
	}

	final_rotate(a);  // ← Last step! Complete the sort
}
```

---

## 42 Norm Considerations

```c
void	final_rotate(t_stack **a)
{
	int	min_pos;
	int	size;

	min_pos = find_min_index_position(*a);
	size = stack_size(*a);
	if (min_pos < size / 2)
	{
		while (min_pos-- > 0)
			ra(a, 1);
	}
	else
	{
		while (min_pos++ < size)
			rra(a, 1);
	}
}
```

---

## Common Mistakes

### Mistake 1: Using Value Instead of Index

```c
// ❌ WRONG
int min_val = find_min(*a);  // Finding minimum value
// Should find minimum INDEX!
```

**✅ Correct:**
```c
int min_pos = find_min_index_position(*a);  // Find index 0
```

### Mistake 2: Not Optimizing Direction

```c
// ❌ WRONG - Always uses forward rotation
while (min_pos > 0)
{
	ra(a, 1);
	min_pos--;
}
// Could be very expensive if min at bottom!
```

**✅ Correct:**
```c
// Choose based on position
if (min_pos < size / 2)
	use_forward_rotation();
else
	use_reverse_rotation();
```

### Mistake 3: Forgetting Final Rotate

```c
// ❌ WRONG
void sort_large(t_stack **a, t_stack **b)
{
	push_chunks_to_b(a, b, 5);
	while (*b)
		execute_cheapest_move(a, b, find_cheapest(*b));
	// Forgot: final_rotate(a);
}
// Stack not fully sorted!
```

---

## Testing Strategy

### Test 1: Various Positions

```c
// Min at position 0 (already sorted)
stack = create_stack_with_indices([0, 1, 2, 3]);
final_rotate(&stack);
assert(stack->index == 0);  // No change

// Min at position 2
stack = create_stack_with_indices([2, 3, 0, 1]);
final_rotate(&stack);
assert(stack->index == 0);  // Rotated to top

// Min at position 3 (last)
stack = create_stack_with_indices([1, 2, 3, 0]);
final_rotate(&stack);
assert(stack->index == 0);  // Reverse rotated
```

### Test 2: Direction Optimization

```c
// Verify correct direction chosen
stack = create_large_stack_with_min_at(80, 100);
int ops_before = operation_count;
final_rotate(&stack);
int ops_used = operation_count - ops_before;
// Should use reverse (20 ops), not forward (80 ops)
assert(ops_used == 20);
```

### Test 3: Final Result

```c
// Verify fully sorted after final_rotate
stack = create_random_indexed_stack(100);
// ... do Turk algorithm phases 1-2 ...
final_rotate(&stack);

// Check sorted
for (int i = 0; i < 99; i++)
	assert(get_index_at(stack, i) == i);
```

---

## Summary

**What final_rotate Does:**
1. Finds position of element with index 0 (minimum)
2. Chooses optimal rotation direction
3. Rotates until minimum at top
4. Completes the sorting process

**Key Characteristics:**
- ✅ O(n) time, O(1) space
- ✅ Optimizes rotation direction
- ✅ Final step of sort_large
- ✅ Guarantees sorted result

**Remember:**
- Find minimum INDEX, not value
- Choose cheaper rotation direction
- Essential last step
- Without it, sort is incomplete
- Simple but critical function

---

## Location in Project

**File:** `srcs/final_rotate.c` or `srcs/sort_large.c`
**Header:** `includes/push_swap.h`
**Phase:** Phase 7 (Large Sorting Algorithm)

---

## Related Functions

- [sort_large](sort_large.md) - Calls this as final step
- [find_min_index](find_min_index.md) - Finds minimum index
- [ra](ra.md) - Forward rotation
- [rra](rra.md) - Reverse rotation
- [is_sorted](is_sorted.md) - Verify result

---

*The final touch that completes the masterpiece - without final_rotate, the sorted stack would start at the wrong position!*
