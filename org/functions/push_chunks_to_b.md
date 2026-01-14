# push_chunks_to_b - Push Elements to B in Chunks Based on Index Ranges

## Function Signature

```c
void push_chunks_to_b(t_stack **a, t_stack **b, int chunks)
```

**Return type:** `void` - Modifies both stacks
**Parameters:**
- `t_stack **a` - Pointer to stack A (source)
- `t_stack **b` - Pointer to stack B (destination)
- `int chunks` - Number of chunks to divide the stack into

---

## Purpose & Use Case

`push_chunks_to_b` is a **partitioning function** that implements the first phase of the Turk algorithm by dividing stack A into chunks based on normalized indices and pushing elements to stack B in a specific order. This creates an intelligent initial distribution that sets up optimal sorting in the second phase.

### When You'll Use It

You'll call `push_chunks_to_b` when you need to:
1. **Start Turk algorithm** - First phase of large sorting
2. **Partition by index ranges** - Divide elements into manageable groups
3. **Create B working set** - Move elements to B for optimization
4. **Enable efficient sorting** - Set up for cost-based push back
5. **Handle large stacks** - Critical for stacks > 5 elements

### Why Chunking Matters

**Divide and conquer strategy:**
```
Stack A (100 elements, indices 0-99):
Without chunking:
- Push all 99 to B randomly
- Hard to optimize
- Many rotations wasted

With chunking (5 chunks):
Chunk 0: indices 0-19   → Push first
Chunk 1: indices 20-39  → Push second
Chunk 2: indices 40-59  → Push third
Chunk 3: indices 60-79  → Push fourth
Chunk 4: indices 80-99  → Keep in A

Result:
- B has lower indices (easier to sort)
- A has highest indices (already near-sorted)
- Reduced rotation costs
- Intelligent partitioning
```

### Real-World Analogy

**Sorting books by organizing in groups first:**
```
100 books to sort:

Bad approach:
- Take books randomly
- Stack them elsewhere
- Sort one by one

Good approach (chunking):
- Group 1: Books A-D → Move to table 1
- Group 2: Books E-H → Move to table 2
- Group 3: Books I-L → Move to table 3
- Group 4: Books M-P → Move to table 4
- Group 5: Books Q-Z → Keep on main shelf

Now sort within each group intelligently!
push_chunks_to_b does this with stack indices!
```

---

## Deep Dive: How It Works

### The Chunking Strategy

**Concept:**
- Calculate chunk size based on total elements and desired chunks
- For each chunk (starting from lowest indices):
  - Define index range (min_idx to max_idx)
  - Push all elements in that range from A to B
  - Rotate A to find elements in range
  - Move to next chunk
- Result: B has lower indices, A has highest indices

### Algorithm Visualization

**Stack Example:** 12 elements with indices [0-11], 3 chunks

```
Initial State:
Stack A: [elem₀, elem₁, elem₂, elem₃, elem₄, elem₅, elem₆, elem₇, elem₈, elem₉, elem₁₀, elem₁₁]
Indices: [  0,     1,     2,     3,     4,     5,     6,     7,     8,     9,     10,     11]
Stack B: []

Chunk size = 12 / 3 = 4

Chunk 0: Push indices 0-3
Target: elements with indices 0, 1, 2, 3
Process:
  - Find elem with index in [0,3]
  - If at top, pb
  - If not, ra to bring to top
  - Repeat until all 0-3 pushed

After Chunk 0:
Stack A: [elem₄, elem₅, elem₆, elem₇, elem₈, elem₉, elem₁₀, elem₁₁]
Stack B: [elem₃, elem₂, elem₁, elem₀] (or some order)

Chunk 1: Push indices 4-7
Target: elements with indices 4, 5, 6, 7
Process: Same as Chunk 0

After Chunk 1:
Stack A: [elem₈, elem₉, elem₁₀, elem₁₁]
Stack B: [mixed elements with indices 0-7]

Chunk 2: Keep indices 8-11
Don't push! Keep highest indices in A

Final State:
Stack A: [elem₈, elem₉, elem₁₀, elem₁₁] ← Highest indices
Stack B: [mixed elements with indices 0-7] ← Lower indices to sort
```

### Chunk Calculation

```
Total elements: n
Number of chunks: k (typically 5-10)
Chunk size: n / k

Example: n=100, k=5
Chunk size = 100/5 = 20

Chunk 0: indices 0-19
Chunk 1: indices 20-39
Chunk 2: indices 40-59
Chunk 3: indices 60-79
Chunk 4: indices 80-99 (keep in A)

Number of pushes = 4 chunks × 20 elements = 80 elements to B
Remaining in A = 20 elements (highest indices)
```

---

## Step-by-Step Implementation

### Step 1: Calculate Chunk Size

**Determine partition size:**
```c
int size = stack_size(*a);
int chunk_size = size / chunks;
```

**Why divide by chunks:**
```
Divides total elements into equal-sized groups

Example:
size = 100, chunks = 5
chunk_size = 20

Each chunk handles 20 elements
5 chunks cover all 100 elements
```

### Step 2: Iterate Through Chunks

**Process each chunk:**
```c
int chunk = 0;
while (chunk < chunks - 1)  // Note: -1 to keep last chunk in A
{
    // Process this chunk
    chunk++;
}
```

**Why chunks - 1:**
```
Don't push the last chunk!
Keep highest indices in A
Already near their final position

Example: 5 chunks → push 4, keep 1
```

### Step 3: Calculate Chunk Range

**Define index boundaries:**
```c
int min_idx = chunk * chunk_size;
int max_idx = (chunk + 1) * chunk_size - 1;
```

**Range calculation:**
```
Chunk 0: min=0×20=0,   max=1×20-1=19   → [0,19]
Chunk 1: min=1×20=20,  max=2×20-1=39   → [20,39]
Chunk 2: min=2×20=40,  max=3×20-1=59   → [40,59]
Chunk 3: min=3×20=60,  max=4×20-1=79   → [60,79]
Chunk 4: min=4×20=80,  max=5×20-1=99   → [80,99] (not pushed)
```

### Step 4: Push Elements in Range

**Find and push:**
```c
int pushed = 0;
int target_count = chunk_size;

while (pushed < target_count && *a)
{
    if ((*a)->index >= min_idx && (*a)->index <= max_idx)
    {
        pb(a, b, 1);  // Push to B
        pushed++;
    }
    else
    {
        ra(a, 1);  // Rotate to find next
    }
}
```

**Process:**
```
For each element in current chunk:
1. Check if top of A is in current chunk range
2. YES: Push to B, increment pushed counter
3. NO: Rotate A to bring next element to top
4. Repeat until all elements in chunk pushed
```

### Step 5: Optimization - Rotate Intelligently

**Avoid infinite loops:**
```c
int rotations = 0;
int max_rotations = stack_size(*a);

while (pushed < target_count && rotations < max_rotations)
{
    if ((*a)->index >= min_idx && (*a)->index <= max_idx)
    {
        pb(a, b, 1);
        pushed++;
        rotations = 0;  // Reset rotation counter
    }
    else
    {
        ra(a, 1);
        rotations++;
    }
}
```

---

## Complete Algorithm Pseudocode

```
FUNCTION push_chunks_to_b(a, b, chunks):
    // Step 1: Calculate chunk size
    size = stack_size(a)
    chunk_size = size / chunks

    // Handle edge case: if chunk_size is 0, set to 1
    IF chunk_size == 0:
        chunk_size = 1

    // Step 2: Process each chunk (except last)
    chunk = 0
    WHILE chunk < chunks - 1:
        // Step 3: Calculate chunk range
        min_idx = chunk × chunk_size
        max_idx = (chunk + 1) × chunk_size - 1

        // Step 4: Push all elements in this range
        pushed = 0
        target = chunk_size
        rotations = 0

        WHILE pushed < target AND stack a is not empty:
            // Check if top element is in current chunk
            IF a.top.index >= min_idx AND a.top.index <= max_idx:
                pb(a, b)  // Push to B
                pushed++
                rotations = 0  // Reset

            ELSE:
                ra(a)  // Rotate to find next
                rotations++

            // Safety: prevent infinite loop
            IF rotations >= stack_size(a):
                BREAK

        chunk++

    // Done! B has lower indices, A has highest indices
END FUNCTION
```

---

## Visual Execution Trace

### Example: 12 Elements, 3 Chunks

```
Initial State:
Stack A (values): [5, 12, 3, 8, 1, 11, 6, 2, 9, 4, 10, 7]
Stack A (indices):[2,  5,  1, 4, 0,  5,  3, 1, 4,  2,  5,  3]
Stack B: []
Size: 12
Chunks: 3
Chunk size: 12/3 = 4

Call: push_chunks_to_b(&a, &b, 3)

Chunk 0: Push indices 0-3
min_idx = 0, max_idx = 3

Iteration 1:
  Top index: 2 (in range [0,3]? Yes!)
  pb → Push to B
  A: [12, 3, 8, 1, 11, 6, 2, 9, 4, 10, 7]
  B: [5]
  pushed = 1

Iteration 2:
  Top index: 5 (in range [0,3]? No)
  ra → Rotate A
  A: [3, 8, 1, 11, 6, 2, 9, 4, 10, 7, 12]

Iteration 3:
  Top index: 1 (in range [0,3]? Yes!)
  pb → Push to B
  A: [8, 1, 11, 6, 2, 9, 4, 10, 7, 12]
  B: [3, 5]
  pushed = 2

... continue until all indices 0-3 pushed ...

After Chunk 0:
A: [elements with indices 4-11]
B: [elements with indices 0-3]

Chunk 1: Push indices 4-7
min_idx = 4, max_idx = 7

... process similarly ...

After Chunk 1:
A: [elements with indices 8-11]
B: [elements with indices 0-7]

Chunk 2: indices 8-11 (NOT PUSHED - stay in A)

Final State:
A: [elem₈, elem₉, elem₁₀, elem₁₁] ← Highest 4 indices
B: [mixed elements with indices 0-7] ← Lower 8 indices

Now ready for phase 2: cost-based push back!
```

---

## Edge Cases

### Case 1: Small Stack (< chunks)

```c
// Stack: 3 elements, 5 chunks requested
// chunk_size = 3/5 = 0

push_chunks_to_b(&a, &b, 5);

// Need to handle chunk_size = 0
// Set chunk_size = 1 or skip chunking
```

### Case 2: Stack Size Equals Chunks

```c
// Stack: 5 elements, 5 chunks
// chunk_size = 5/5 = 1

// Each chunk has 1 element
// Push 4, keep 1 in A
```

### Case 3: Uneven Division

```c
// Stack: 23 elements, 5 chunks
// chunk_size = 23/5 = 4 (integer division)

// Chunk 0: indices 0-3   (4 elements)
// Chunk 1: indices 4-7   (4 elements)
// Chunk 2: indices 8-11  (4 elements)
// Chunk 3: indices 12-15 (4 elements)
// Chunk 4: indices 16-22 (7 elements) ← Larger, kept in A

// Last chunk gets remainder
```

### Case 4: Already Partially Sorted

```c
// Stack A has some elements already in B range
// Chunking still works, just pushes fewer elements
```

### Case 5: All Elements in One Chunk

```c
// Stack: 10 elements, but all indices 0-9
// All pushed except highest chunk
// Works correctly
```

---

## Time & Space Complexity

### Time Complexity: **O(n²)** - Quadratic

**Analysis:**
```
n = number of elements

Outer loop: O(chunks) = O(1) (typically 5-10 chunks, constant)
Inner loop for each chunk:
  - Need to find all elements in chunk
  - May need to rotate through entire stack multiple times
  - Worst case: O(n) rotations per element
  - O(chunk_size × n) per chunk

Total: O(chunks × chunk_size × n)
     = O(k × (n/k) × n)  where k = chunks
     = O(n²)

In practice: Much better than worst case
- Each element visited ~once per chunk
- Typically O(n × chunks) = O(n) since chunks is small
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
Variables:
- int size
- int chunk_size
- int chunk
- int min_idx, max_idx
- int pushed, target, rotations

Total: ~28 bytes, regardless of stack size
No allocations
No recursion
Modifies stacks in place

Space = O(1) ✅
```

---

## Relationship with Other Functions

### Called by sort_large

```c
void sort_large(t_stack **a, t_stack **b)
{
    // Phase 1: Partition using chunks
    push_chunks_to_b(a, b, 5);  // ← Initial partitioning

    // Phase 2: Cost-based push back
    while (*b)
    {
        calculate_cost(*a, *b);
        execute_cheapest_move(a, b);
    }

    // Phase 3: Final rotation
    final_rotate(a);
}
```

### Uses assign_index (Prerequisite)

```c
void choose_sort(t_stack **a, t_stack **b)
{
    if (stack_size(*a) > 5)
    {
        assign_index(*a);  // ← MUST normalize first!
        push_chunks_to_b(a, b, 5);  // ← Then chunk by indices
        // ...
    }
}
```

### Works with Stack Operations

```c
// Uses pb and ra operations
pb(a, b, 1);  // Push to B
ra(a, 1);     // Rotate A
```

---

## Integration with Push_swap

### Scenario: 100-Element Sort

```c
// Input: 100 random numbers
// After assign_index: indices 0-99

// Chunking with 5 chunks:
push_chunks_to_b(&a, &b, 5);

// Result:
// A: 20 elements with indices 80-99
// B: 80 elements with indices 0-79

// Benefits:
// 1. B has elements to sort back optimally
// 2. A has highest values (near final position)
// 3. Reduced total rotation costs
// 4. Intelligent partitioning for phase 2
```

---

## 42 Norm Considerations

### Function Structure

```c
void	push_chunks_to_b(t_stack **a, t_stack **b, int chunks)
{
	int	size;
	int	chunk_size;
	int	chunk;
	int	min_idx;
	int	max_idx;

	size = stack_size(*a);
	chunk_size = size / chunks;
	if (chunk_size == 0)
		chunk_size = 1;
	chunk = 0;
	while (chunk < chunks - 1)
	{
		min_idx = chunk * chunk_size;
		max_idx = (chunk + 1) * chunk_size - 1;
		push_chunk_range(a, b, min_idx, max_idx, chunk_size);
		chunk++;
	}
}
```

**Helper function for norm compliance:**
```c
static void	push_chunk_range(t_stack **a, t_stack **b,
				int min, int max, int target)
{
	int	pushed;
	int	rotations;
	int	size;

	pushed = 0;
	rotations = 0;
	size = stack_size(*a);
	while (pushed < target && *a && rotations < size)
	{
		if ((*a)->index >= min && (*a)->index <= max)
		{
			pb(a, b, 1);
			pushed++;
			rotations = 0;
		}
		else
		{
			ra(a, 1);
			rotations++;
		}
	}
}
```

---

## Common Mistakes

### Mistake 1: Not Keeping Last Chunk

```c
// ❌ WRONG - Pushes all elements!
while (chunk < chunks)  // Should be chunks - 1
{
    // Pushes everything, A becomes empty!
}
```

**✅ Correct:**
```c
while (chunk < chunks - 1)  // Keep last chunk in A
```

### Mistake 2: Using Value Instead of Index

```c
// ❌ WRONG
if ((*a)->value >= min_idx && (*a)->value <= max_idx)
    pb(a, b, 1);
// Should compare index, not value!
```

**✅ Correct:**
```c
if ((*a)->index >= min_idx && (*a)->index <= max_idx)
    pb(a, b, 1);
```

### Mistake 3: Infinite Loop

```c
// ❌ WRONG - No rotation limit
while (pushed < target)
{
    if (/* in range */)
        pb(a, b, 1);
    else
        ra(a, 1);  // Could rotate forever!
}
```

**✅ Correct:**
```c
int rotations = 0;
while (pushed < target && rotations < stack_size(*a))
{
    // ... with rotation counter
}
```

### Mistake 4: Not Handling chunk_size = 0

```c
// ❌ WRONG - Division by zero or infinite loop
chunk_size = size / chunks;  // Could be 0 if size < chunks
// Use directly without checking
```

**✅ Correct:**
```c
chunk_size = size / chunks;
if (chunk_size == 0)
    chunk_size = 1;  // Minimum 1
```

---

## Testing Strategy

### Test 1: Standard Chunking

```c
stack = create_indexed_stack(100);  // Indices 0-99
push_chunks_to_b(&stack, &b, 5);

// Verify A has ~20 elements (indices 80-99)
assert(stack_size(stack) >= 18 && stack_size(stack) <= 22);

// Verify B has ~80 elements (indices 0-79)
assert(stack_size(b) >= 78 && stack_size(b) <= 82);

// Verify all indices in A are high
t_stack *temp = stack;
while (temp)
{
    assert(temp->index >= 80);
    temp = temp->next;
}
```

### Test 2: Small Stack

```c
stack = create_indexed_stack(3);
push_chunks_to_b(&stack, &b, 5);

// Should handle gracefully
// Keep at least 1 in A
assert(stack_size(stack) >= 1);
```

### Test 3: Edge Cases

```c
// Empty stack
push_chunks_to_b(&empty, &b, 5);  // Should not crash

// Single element
stack = create_indexed_stack(1);
push_chunks_to_b(&stack, &b, 5);
assert(stack_size(stack) == 1);  // Keep the one element
```

---

## Summary

**What push_chunks_to_b Does:**
1. Divides stack into chunks based on normalized indices
2. Pushes lower index chunks to B
3. Keeps highest index chunk in A
4. Creates intelligent initial distribution for sorting

**Key Characteristics:**
- ✅ Partitions by normalized indices
- ✅ O(n²) worst case, O(n) typical
- ✅ O(1) space
- ✅ Keeps highest indices in A
- ✅ Sets up optimal sorting in phase 2

**Critical Uses:**
- Phase 1 of Turk algorithm
- Reduces problem size for phase 2
- Creates favorable distribution
- Minimizes total rotation costs

**Remember:**
- Must call assign_index first
- Keep last chunk in A (chunks - 1)
- Use index field, not value
- Prevent infinite loops
- Typically 5-10 chunks optimal

---

## Location in Project

**File:** `srcs/sort_large.c` or `srcs/turk_algorithm.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 7 (Large Sorting Algorithm)

---

## Related Functions

- [assign_index](assign_index.md) - Must be called first
- [sort_large](sort_large.md) - Calls this as phase 1
- [calculate_cost](calculate_cost.md) - Used in phase 2
- [pb](pb.md) - Used to push elements
- [ra](ra.md) - Used to rotate stack

---

*Chunking is the key to efficient large sorting - intelligent partitioning makes phase 2 optimization possible!*
