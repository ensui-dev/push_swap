# find_target_position - Find Target Position in Stack A for Element from B

## Function Signature

```c
int find_target_position(t_stack *stack_a, int index_b)
```

**Return type:** `int` - Target position in stack A
**Parameters:**
- `t_stack *stack_a` - Pointer to stack A
- `int index_b` - Index of element from B to place in A

---

## Purpose & Use Case

`find_target_position` determines where an element from stack B should be inserted into stack A to maintain sorted order. It finds the position of the closest larger index, or wraps around to find the minimum if the B element's index is larger than all in A.

### When You'll Use It

1. **Cost calculation** - Find target before calculating rotation costs
2. **Optimal insertion** - Determine where element belongs
3. **Maintain order** - Keep A progressively sorted
4. **Turk algorithm** - Core positioning logic

### Algorithm

```
For element with index_b from B:
1. Search A for smallest index greater than index_b
2. If found, return its position
3. If not found (index_b is largest), return position of minimum index

Example:
A indices: [5, 8, 2, 10]
A positions: [0, 1, 2, 3]

Find target for index_b = 6:
- 8 > 6 ✅ (closest larger)
- Target position = 1

Find target for index_b = 11 (larger than all):
- No index > 11 in A
- Return position of min index (2)
- Target position = 2
```

---

## Implementation

```c
int	find_target_position(t_stack *stack_a, int index_b)
{
	int		target_pos;
	int		target_idx;
	int		best_pos;
	t_stack	*a;

	target_idx = INT_MAX;
	best_pos = 0;
	target_pos = -1;
	a = stack_a;
	while (a)
	{
		if (a->index > index_b && a->index < target_idx)
		{
			target_idx = a->index;
			target_pos = a->pos;
		}
		if (a->index < stack_a->index)
			best_pos = a->pos;
		a = a->next;
	}
	if (target_pos == -1)
		return (best_pos);
	return (target_pos);
}
```

---

## Time & Space Complexity

- **Time:** O(n) - Single pass through stack A
- **Space:** O(1) - Constant variables

---

## Location in Project

**File:** `srcs/cost_utils.c`
**Phase:** Phase 7 (Large Sorting Algorithm)

---

## Related Functions

- [calculate_cost](calculate_cost.md) - Main caller
- [find_min_index](find_min_index.md) - Used for wrap-around
- [assign_position](assign_position.md) - Positions must be current

---

*Finding the right insertion point is key to maintaining order during Turk algorithm!*
