# execute_cheapest_move - Execute Optimal Move Sequence for Cheapest Element

## Function Signature

```c
void execute_cheapest_move(t_stack **a, t_stack **b, t_stack *cheapest)
```

**Return type:** `void` - Modifies both stacks
**Parameters:**
- `t_stack **a` - Pointer to stack A
- `t_stack **b` - Pointer to stack B
- `t_stack *cheapest` - Pointer to cheapest element in B

---

## Purpose & Use Case

`execute_cheapest_move` performs the optimal sequence of rotations and push operations to move the cheapest element from B to its target position in A. It optimizes by using simultaneous rotations (rr/rrr) when both stacks rotate in the same direction.

### Move Optimization

```
Without optimization:
cost_a = 3, cost_b = 2 (both positive)
Operations: ra ra ra + rb rb + pa = 6 operations

With optimization (use rr):
Operations: rr rr + ra + pa = 4 operations ✅

Savings: 2 operations per move!
```

### Algorithm Steps

```
1. Analyze cost signs (same direction?)
2. If both positive: Use rr while both need rotation
3. If both negative: Use rrr while both need rotation
4. If different signs: Rotate each separately
5. Push from B to A
```

---

## Implementation

```c
void	execute_cheapest_move(t_stack **a, t_stack **b, t_stack *cheapest)
{
	int	cost_a;
	int	cost_b;

	cost_a = cheapest->cost_a;
	cost_b = cheapest->cost_b;
	while (cost_a > 0 && cost_b > 0)
	{
		rr(a, b, 1);
		cost_a--;
		cost_b--;
	}
	while (cost_a < 0 && cost_b < 0)
	{
		rrr(a, b, 1);
		cost_a++;
		cost_b++;
	}
	while (cost_a > 0)
	{
		ra(a, 1);
		cost_a--;
	}
	while (cost_a < 0)
	{
		rra(a, 1);
		cost_a++;
	}
	while (cost_b > 0)
	{
		rb(b, 1);
		cost_b--;
	}
	while (cost_b < 0)
	{
		rrb(b, 1);
		cost_b++;
	}
	pa(a, b, 1);
}
```

---

## Visual Example

```
Initial:
A: [100, 75, 50, 25]
B: [60, 40, 90]
Cheapest: B[1] (40) with cost_a=2, cost_b=1

Step 1: Both positive, use rr
rr → A: [75, 50, 25, 100], B: [90, 60, 40]
cost_a=1, cost_b=0

Step 2: Finish A rotation
ra → A: [50, 25, 100, 75]
cost_a=0

Step 3: Push to A
pa → A: [90, 50, 25, 100, 75], B: [60, 40]

Result: 90 inserted optimally!
```

---

## Time & Space Complexity

- **Time:** O(n) - Worst case full rotations
- **Space:** O(1) - No allocations

---

## Location in Project

**File:** `srcs/execute_move.c`
**Phase:** Phase 7 (Large Sorting Algorithm)

---

## Related Functions

- [find_cheapest](find_cheapest.md) - Provides cheapest element
- [calculate_cost](calculate_cost.md) - Computes costs
- [rr](rr.md), [rrr](rrr.md) - Simultaneous rotations
- [pa](pa.md) - Final push operation

---

*Smart execution with rr/rrr optimization makes Turk algorithm highly efficient!*
