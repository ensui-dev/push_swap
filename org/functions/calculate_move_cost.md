# calculate_move_cost - Calculate Rotation Cost for Position

## Function Signature

```c
int calculate_move_cost(int pos, int size)
```

**Return type:** `int` - Rotation cost (positive=forward, negative=reverse)
**Parameters:**
- `int pos` - Current position in stack
- `int size` - Total size of stack

---

## Purpose & Use Case

`calculate_move_cost` determines the optimal rotation direction and cost to bring an element at a given position to the top of the stack. Returns positive for forward rotation (ra/rb) or negative for reverse rotation (rra/rrb).

### Algorithm

```
If position < size/2:
  Forward rotation is cheaper
  Cost = position (positive)
  Example: pos=2, size=10 → cost=2 (2 ra operations)

If position >= size/2:
  Reverse rotation is cheaper
  Cost = -(size - position) (negative)
  Example: pos=8, size=10 → cost=-2 (2 rra operations)
```

### Example

```
Stack size: 10
Positions: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

Element at pos 2:
  Forward: 2 rotations
  Reverse: 8 rotations
  Choose forward → cost = 2

Element at pos 8:
  Forward: 8 rotations
  Reverse: 2 rotations
  Choose reverse → cost = -2
```

---

## Implementation

```c
int	calculate_move_cost(int pos, int size)
{
	if (pos < size / 2)
		return (pos);
	else
		return (-(size - pos));
}
```

---

## Time & Space Complexity

- **Time:** O(1) - Simple calculation
- **Space:** O(1) - No memory allocation

---

## Location in Project

**File:** `srcs/cost_utils.c`
**Phase:** Phase 7 (Large Sorting Algorithm)

---

## Related Functions

- [calculate_cost](calculate_cost.md) - Main caller
- [execute_cheapest_move](execute_cheapest_move.md) - Uses cost sign

---

*Simple but critical - choosing the right rotation direction saves operations!*
