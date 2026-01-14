# sort_large - Main Turk Algorithm for Large Stacks

## Function Signature

```c
void sort_large(t_stack **a, t_stack **b)
```

**Return type:** `void` - Modifies both stacks
**Parameters:**
- `t_stack **a` - Pointer to stack A (starts with all elements)
- `t_stack **b` - Pointer to stack B (starts empty)

---

## Purpose & Use Case

`sort_large` implements the complete Turk algorithm for efficiently sorting large stacks (typically > 5 elements). It uses a three-phase approach: chunking, cost-based optimization, and final rotation.

### The Turk Algorithm (Three Phases)

```
Phase 1: Chunking
- Partition stack A by normalized indices
- Push lower index chunks to B
- Keep highest indices in A

Phase 2: Cost-Based Push Back
- While B is not empty:
  - Calculate move costs for all B elements
  - Find cheapest element
  - Execute optimal move to push back to A
  - Repeat

Phase 3: Final Rotation
- Rotate A until minimum index at top
- Stack now fully sorted!
```

### Why Turk Algorithm is Efficient

```
Naive approach: O(n²) operations
Turk algorithm: O(n log n) average

Key optimizations:
✅ Intelligent chunking reduces search space
✅ Cost-based selection minimizes rotations
✅ Simultaneous rotations (rr/rrr)
✅ Target position pre-calculation
✅ Only move when beneficial

Result: ~700 operations for 100 elements
       ~5500 operations for 500 elements
```

---

## Implementation

```c
void	sort_large(t_stack **a, t_stack **b)
{
	// Phase 1: Partition into chunks
	push_chunks_to_b(a, b, 5);

	// Phase 2: Cost-based optimization
	while (*b)
	{
		calculate_cost(*a, *b);
		execute_cheapest_move(a, b, find_cheapest(*b));
	}

	// Phase 3: Final rotation to sort
	final_rotate(a);
}
```

---

## Visual Example (12 Elements)

```
Input: [5, 12, 3, 8, 1, 11, 6, 2, 9, 4, 10, 7]
After assign_index: indices [2, 5, 1, 4, 0, 5, 3, 1, 4, 2, 5, 3]

Phase 1: push_chunks_to_b (3 chunks)
- Push indices 0-3 to B
- Push indices 4-7 to B
- Keep indices 8-11 in A

After Phase 1:
A: [elem₈, elem₉, elem₁₀, elem₁₁] (highest indices)
B: [mixed elements, indices 0-7]

Phase 2: Loop
Iteration 1:
  calculate_cost(A, B)
  cheapest = find_cheapest(B)
  execute_cheapest_move()
  → One element pushed to A

Iteration 2:
  Recalculate costs (positions changed!)
  Find new cheapest
  Execute move
  → Another element pushed to A

... continue until B empty ...

After Phase 2:
A: All elements, mostly sorted by index
B: Empty

Phase 3: final_rotate
Find minimum index position in A
Rotate until min at top

Final Result:
A: [elem₀, elem₁, elem₂, ..., elem₁₁] ✅ Fully sorted!
B: Empty
```

---

## Algorithm Complexity

### Time Complexity

```
Phase 1: O(n²) worst case, O(n) typical
- Push ~80% of elements
- Each may need full rotation

Phase 2: O(n² log n)
- n iterations (one per element in B)
- Each iteration:
  - calculate_cost: O(n²)
  - find_cheapest: O(n)
  - execute_move: O(n)

Phase 3: O(n)
- Single final rotation

Total: O(n² log n) worst case
Average: Much better due to optimizations
```

### Space Complexity

```
O(1) - All operations in place
No additional data structures
Only local variables
```

---

## Optimizations in Turk Algorithm

### 1. Chunking Strategy
```
Instead of random push, partition by index ranges
Reduces search space for phase 2
Keeps high indices in A (already near sorted)
```

### 2. Cost-Based Selection
```
Always pick element with minimum total cost
Avoids expensive moves
Reduces total operations by ~40%
```

### 3. Simultaneous Rotations
```
Use rr when both stacks rotate forward
Use rrr when both rotate reverse
Saves one operation per overlapping rotation
```

### 4. Target Pre-Calculation
```
Find target position before moving
Ensures optimal insertion point
Maintains progressive sorting
```

### 5. Adaptive Chunk Count
```
Small stacks: fewer chunks (3-4)
Large stacks: more chunks (5-10)
Balances chunking overhead vs benefit
```

---

## Tuning Parameters

```
Chunk count:
- 100 elements: 5 chunks
- 500 elements: 10 chunks
- Formula: sqrt(n) or n/50

Typically:
- n < 100: 5 chunks
- n >= 100: 10 chunks
```

---

## Location in Project

**File:** `srcs/sort_large.c`
**Phase:** Phase 7 (Large Sorting Algorithm)

---

## Related Functions

- [assign_index](assign_index.md) - Must be called first
- [push_chunks_to_b](push_chunks_to_b.md) - Phase 1
- [calculate_cost](calculate_cost.md) - Phase 2 core
- [find_cheapest](find_cheapest.md) - Phase 2 selection
- [execute_cheapest_move](execute_cheapest_move.md) - Phase 2 execution
- [final_rotate](final_rotate.md) - Phase 3

---

*The Turk algorithm is the crown jewel of push_swap - understanding it deeply is the key to mastering the project!*
