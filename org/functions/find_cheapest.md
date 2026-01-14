# find_cheapest - Find Element in B with Minimum Total Cost

## Function Signature

```c
t_stack *find_cheapest(t_stack *stack_b)
```

**Return type:** `t_stack *` - Pointer to cheapest node
**Parameter:** `t_stack *stack_b` - Pointer to stack B

---

## Purpose & Use Case

`find_cheapest` searches through stack B to find the element with the minimum total move cost (|cost_a| + |cost_b|). This is the optimal element to move next in the Turk algorithm.

### Algorithm

```
For each element in B:
  Calculate total_cost = |cost_a| + |cost_b|
  Track element with minimum total_cost
Return pointer to cheapest element
```

### Example

```
Stack B:
[0] cost_a=3, cost_b=1  → total = 4
[1] cost_a=-2, cost_b=0 → total = 2 ✅ CHEAPEST
[2] cost_a=1, cost_b=5  → total = 6

Return pointer to B[1]
```

---

## Implementation

```c
t_stack	*find_cheapest(t_stack *stack_b)
{
	t_stack	*cheapest;
	int		min_cost;
	int		total_cost;

	if (!stack_b)
		return (NULL);
	min_cost = INT_MAX;
	cheapest = stack_b;
	while (stack_b)
	{
		total_cost = abs(stack_b->cost_a) + abs(stack_b->cost_b);
		if (total_cost < min_cost)
		{
			min_cost = total_cost;
			cheapest = stack_b;
		}
		stack_b = stack_b->next;
	}
	return (cheapest);
}
```

---

## Time & Space Complexity

- **Time:** O(n) - Single pass through stack B
- **Space:** O(1) - Few variables

---

## Common Patterns

### Tie-Breaking
```
If multiple elements have same cost:
- Return first found (simplest)
- Or prioritize by position
- Or by other heuristic
```

---

## Location in Project

**File:** `srcs/cost.c`
**Phase:** Phase 7 (Large Sorting Algorithm)

---

## Related Functions

- [calculate_cost](calculate_cost.md) - Must be called first
- [execute_cheapest_move](execute_cheapest_move.md) - Uses result

---

*Finding the cheapest move is the heart of optimization - this is why Turk algorithm is efficient!*
