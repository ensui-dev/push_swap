# assign_index - Normalize Stack Values to 0...N-1 Indices

## Function Signature

```c
void assign_index(t_stack *stack)
```

**Return type:** `void` - Modifies the stack in place
**Parameter:** `t_stack *stack` - Pointer to the head of the stack

---

## Purpose & Use Case

`assign_index` is an **index normalization function** that transforms arbitrary stack values into normalized sequential indices from 0 to N-1, where each index represents the relative rank of the value. This is the cornerstone of the large sorting algorithm, enabling efficient bitwise operations on normalized data.

### When You'll Use It

You'll call `assign_index` when you need to:
1. **Large sorting setup** - Prepare stack for Turk algorithm (stacks > 5 elements)
2. **Normalize values** - Convert arbitrary integers to 0-based ranks
3. **Enable chunking** - Use normalized indices for efficient partitioning
4. **Simplify comparisons** - Work with predictable 0...N-1 range instead of arbitrary values
5. **Optimize bitwise operations** - Use index bits for radix-based sorting

### Why Index Normalization Matters

**Transform arbitrary values into predictable ranks:**
```
Original stack (arbitrary values):
Values: [42, -5, 1000, 3, -999]
Indices: [?, ?, ?, ?, ?]

After assign_index (normalized):
Values: [42, -5, 1000, 3, -999]
Indices: [2, 1, 4, 3, 0]
        ↑  ↑  ↑  ↑  ↑
        |  |  |  |  └─ Smallest value → index 0
        |  |  |  └──── 4th smallest → index 3
        |  |  └─────── Largest value → index 4
        |  └────────── 2nd smallest → index 1
        └───────────── 3rd smallest → index 2

Now we can use indices for chunking!
Chunk 1: indices 0-1
Chunk 2: indices 2-3
Chunk 3: indices 4
```

### Real-World Analogy

**Ranking students by test scores:**
```
Students with raw scores:
Alice: 87    ← 3rd best score → Rank 3
Bob: 92      ← 2nd best score → Rank 2
Charlie: 100 ← 1st best score → Rank 4 (highest index)
David: 65    ← 5th best score → Rank 0 (lowest index)
Eve: 88      ← 4th best score → Rank 1

Raw scores are arbitrary (65, 87, 88, 92, 100)
Ranks are normalized (0, 3, 1, 2, 4)

With ranks, you can easily:
- Divide into groups (bottom 40%, middle 40%, top 20%)
- Compare positions
- Sort by relative performance

assign_index does this for stack values!
```

---

## Deep Dive: How It Works

### The Ranking Algorithm

**Concept:**
- Create a copy of all stack values in an array
- Sort the array (smallest to largest)
- For each node in the stack:
  - Find where its value appears in the sorted array
  - Assign that position as the node's index
- Result: Every value gets an index representing its rank (0 = smallest)

### Algorithm Visualization

**Stack Example:** [42, -5, 1000, 3]

```
Step 1: Copy values to array
Stack:  [42] -> [-5] -> [1000] -> [3] -> NULL
Array:  [42, -5, 1000, 3]

Step 2: Sort the array
Unsorted: [42, -5, 1000, 3]
Sorted:   [-5, 3, 42, 1000]
          ↑   ↑  ↑   ↑
          0   1  2   3  ← These are the indices/ranks!

Step 3: Build index mapping
Value → Index
-5    → 0  (position in sorted array)
3     → 1
42    → 2
1000  → 3

Step 4: Assign indices to stack nodes
For node with value 42:
  Find 42 in sorted array → position 2
  Assign: node->index = 2

For node with value -5:
  Find -5 in sorted array → position 0
  Assign: node->index = 0

For node with value 1000:
  Find 1000 in sorted array → position 3
  Assign: node->index = 3

For node with value 3:
  Find 3 in sorted array → position 1
  Assign: node->index = 1

Final Result:
Stack:   [42] -> [-5] -> [1000] -> [3] -> NULL
Indices: [2]  -> [0]  -> [3]    -> [1]  -> NULL
```

### Memory State Visualization

```
Before assign_index:
┌────────────────┐
│ Node 1         │
│ value: 42      │
│ index: 0 (?)   │ ← Uninitialized
│ next: ─────┐   │
└────────────────┘
             │
             v
┌────────────────┐
│ Node 2         │
│ value: -5      │
│ index: 0 (?)   │
│ next: ─────┐   │
└────────────────┘

After copying to array and sorting:
Array: [-5, 3, 42, 1000]
Index:  0   1   2    3

After assign_index:
┌────────────────┐
│ Node 1         │
│ value: 42      │
│ index: 2 ✅    │ ← 42 is 3rd smallest → index 2
│ next: ─────┐   │
└────────────────┘
             │
             v
┌────────────────┐
│ Node 2         │
│ value: -5      │
│ index: 0 ✅    │ ← -5 is smallest → index 0
│ next: ─────┐   │
└────────────────┘
```

---

## Step-by-Step Implementation

### Step 1: Get Stack Size

**Count elements:**
```c
int size = stack_size(stack);
```

**Why we need size:**
```
Need to know:
- How many elements to copy
- Array allocation size
- Range of indices (0 to size-1)

Example:
Stack: [42, -5, 1000, 3]
size = 4
Indices will be: 0, 1, 2, 3
```

### Step 2: Allocate Array for Values

**Create temporary storage:**
```c
int *values = malloc(sizeof(int) * size);
if (!values)
    return;  // Allocation failed
```

**Why use an array:**
```
Advantages:
✅ Can sort efficiently (O(n log n))
✅ Contiguous memory = cache-friendly
✅ Easy to search
✅ Doesn't modify original stack

Stack (linked list):
❌ Can't use efficient sorting algorithms directly
❌ Poor cache locality for sorting
✅ But we keep original structure intact
```

### Step 3: Copy Stack Values to Array

**Transfer data:**
```c
copy_values_to_array(stack, values, size);
```

**Implementation:**
```c
void copy_values_to_array(t_stack *stack, int *arr, int size)
{
    int i = 0;

    while (i < size && stack)
    {
        arr[i] = stack->value;
        stack = stack->next;
        i++;
    }
}
```

**Result:**
```
Stack:  [42] -> [-5] -> [1000] -> [3]
Array:  [42, -5, 1000, 3]
        ↑    ↑    ↑      ↑
        0    1    2      3  ← Array indices
```

### Step 4: Sort the Array

**Order values smallest to largest:**
```c
sort_int_array(values, size);
```

**Before and after:**
```
Before: [42, -5, 1000, 3]
After:  [-5, 3, 42, 1000]

Now position in sorted array = rank/index:
Position 0: -5    ← Smallest
Position 1: 3     ← 2nd smallest
Position 2: 42    ← 3rd smallest
Position 3: 1000  ← Largest
```

### Step 5: Find Index for Each Node

**Assign ranks:**
```c
t_stack *current = stack;
while (current)
{
    current->index = get_index_position(values, size, current->value);
    current = current->next;
}
```

**Process for each node:**
```
For node with value 42:
  Search sorted array [-5, 3, 42, 1000]
  Found at position 2
  Assign: node->index = 2

For node with value -5:
  Search sorted array [-5, 3, 42, 1000]
  Found at position 0
  Assign: node->index = 0

For node with value 1000:
  Search sorted array [-5, 3, 42, 1000]
  Found at position 3
  Assign: node->index = 3

For node with value 3:
  Search sorted array [-5, 3, 42, 1000]
  Found at position 1
  Assign: node->index = 1
```

### Step 6: Free Temporary Array

**Clean up:**
```c
free(values);
```

**Why free:**
```
Array was only needed temporarily
No longer needed after indices assigned
Prevent memory leak
```

---

## Complete Algorithm Pseudocode

```
FUNCTION assign_index(stack):
    // Step 1: Get size
    size = stack_size(stack)

    IF size == 0:
        RETURN  // Empty stack

    // Step 2: Allocate temporary array
    values = allocate_array(size)
    IF values is NULL:
        RETURN  // Allocation failed

    // Step 3: Copy stack values to array
    copy_values_to_array(stack, values, size)
    // Result: values = [42, -5, 1000, 3]

    // Step 4: Sort array
    sort_int_array(values, size)
    // Result: values = [-5, 3, 42, 1000]

    // Step 5: Assign indices based on sorted position
    current = stack
    WHILE current is not NULL:
        // Find where current->value appears in sorted array
        index = get_index_position(values, size, current.value)
        current.index = index
        current = current.next

    // Step 6: Free temporary array
    free(values)

    // Done! All indices assigned
END FUNCTION
```

---

## Visual Execution Trace

### Example: Normalizing [42, -5, 1000, 3]

```
Initial State:
Stack: [42] -> [-5] -> [1000] -> [3] -> NULL
Values: [42, -5, 1000, 3]
Indices: [?, ?, ?, ?]

Call: assign_index(stack)

Step 1: Get size
size = 4

Step 2: Allocate array
values = malloc(sizeof(int) * 4)
Allocated: [?, ?, ?, ?]

Step 3: Copy values to array
i=0: arr[0] = 42   → [42, ?, ?, ?]
i=1: arr[1] = -5   → [42, -5, ?, ?]
i=2: arr[2] = 1000 → [42, -5, 1000, ?]
i=3: arr[3] = 3    → [42, -5, 1000, 3]

Step 4: Sort array
Before: [42, -5, 1000, 3]
After:  [-5, 3, 42, 1000]
        ↑   ↑  ↑   ↑
        0   1  2   3  ← Position = Index

Step 5: Assign indices
Current node: value=42
  get_index_position([-5, 3, 42, 1000], 4, 42)
  Found at position 2
  node->index = 2 ✅

Current node: value=-5
  get_index_position([-5, 3, 42, 1000], 4, -5)
  Found at position 0
  node->index = 0 ✅

Current node: value=1000
  get_index_position([-5, 3, 42, 1000], 4, 1000)
  Found at position 3
  node->index = 3 ✅

Current node: value=3
  get_index_position([-5, 3, 42, 1000], 4, 3)
  Found at position 1
  node->index = 1 ✅

Step 6: Free array
free(values)

Final State:
Stack:   [42] -> [-5] -> [1000] -> [3] -> NULL
Values:  [42,    -5,     1000,     3]
Indices: [2,     0,      3,        1]  ✅ All normalized!

Verification:
Index 0: -5    (smallest value)
Index 1: 3     (2nd smallest)
Index 2: 42    (3rd smallest)
Index 3: 1000  (largest value)
✅ Correct!
```

---

## Edge Cases

### Case 1: Empty Stack

```c
t_stack *stack = NULL;

assign_index(stack);

// Result: Function returns immediately
// No crash ✅
```

### Case 2: Single Element

```c
// Stack: [42] -> NULL

assign_index(stack);

// Process:
// size = 1
// Array: [42]
// Sorted: [42]
// Index for 42: position 0
// node->index = 0

// Result:
// Stack:   [42]
// Indices: [0]  ✅
```

### Case 3: Two Elements

```c
// Stack: [5, 3]

assign_index(stack);

// Sorted array: [3, 5]
// 5 → index 1
// 3 → index 0

// Result:
// Stack:   [5, 3]
// Indices: [1, 0]  ✅
```

### Case 4: Already Sorted Stack

```c
// Stack: [1, 2, 3, 4, 5]

assign_index(stack);

// Sorted array: [1, 2, 3, 4, 5] (no change)
// 1 → index 0
// 2 → index 1
// 3 → index 2
// 4 → index 3
// 5 → index 4

// Result:
// Stack:   [1, 2, 3, 4, 5]
// Indices: [0, 1, 2, 3, 4]  ✅
// Indices match values for 1-indexed sorted stack!
```

### Case 5: Reverse Sorted Stack

```c
// Stack: [5, 4, 3, 2, 1]

assign_index(stack);

// Sorted array: [1, 2, 3, 4, 5]
// 5 → index 4
// 4 → index 3
// 3 → index 2
// 2 → index 1
// 1 → index 0

// Result:
// Stack:   [5, 4, 3, 2, 1]
// Indices: [4, 3, 2, 1, 0]  ✅
// Indices are reversed!
```

### Case 6: Negative Numbers

```c
// Stack: [5, -10, 0, -5, 3]

assign_index(stack);

// Sorted array: [-10, -5, 0, 3, 5]
// 5   → index 4
// -10 → index 0
// 0   → index 2
// -5  → index 1
// 3   → index 3

// Result:
// Stack:   [5, -10, 0, -5, 3]
// Indices: [4, 0, 2, 1, 3]  ✅
// Handles negatives correctly
```

### Case 7: Large Range

```c
// Stack: [INT_MAX, INT_MIN, 0]

assign_index(stack);

// Sorted array: [INT_MIN, 0, INT_MAX]
// INT_MAX → index 2
// INT_MIN → index 0
// 0       → index 1

// Result:
// Stack:   [INT_MAX, INT_MIN, 0]
// Indices: [2, 0, 1]  ✅
// Handles extreme values correctly
```

### Case 8: Large Stack

```c
// Stack: 100 random values

assign_index(stack);

// Result:
// All 100 values get indices 0-99
// Smallest value → index 0
// Largest value  → index 99
// ✅ Scales correctly
```

---

## Time & Space Complexity

### Time Complexity: **O(n² log n)** or **O(n²)** - Quadratic

**Breakdown:**
```
n = number of nodes

Step 1: Get size
- stack_size(): O(n)

Step 2: Allocate array
- malloc(): O(1)

Step 3: Copy values
- copy_values_to_array(): O(n)

Step 4: Sort array
- sort_int_array(): O(n²) or O(n log n) depending on algorithm
- Simple sorts (bubble, selection): O(n²)
- Advanced sorts (merge, quick): O(n log n)

Step 5: Assign indices
- For each node (n iterations):
  - get_index_position() does linear search: O(n)
- Total: n × O(n) = O(n²)

Step 6: Free array
- free(): O(1)

Total:
If using simple sort: O(n) + O(n²) + O(n²) = O(n²)
If using advanced sort: O(n) + O(n log n) + O(n²) = O(n²)

Dominant term: O(n²) from index assignment
```

**Can we optimize?**
```
The O(n²) comes from:
- For each of n nodes
- Linear search in sorted array (O(n))

Could use binary search:
- get_index_position() with binary search: O(log n)
- Total index assignment: n × O(log n) = O(n log n)
- Overall: O(n log n) ✅ Much better!

Or use hash map:
- Build map: value → index, O(n)
- Lookup for each node: O(1)
- Total: O(n) ✅ Even better!
```

### Space Complexity: **O(n)** - Linear Space

**Memory used:**
```
Variables:
- int size (4 bytes)
- int *values (8 bytes pointer + n×4 bytes array)
- t_stack *current (8 bytes)

Total: ~12 bytes + 4n bytes for array

Array is the dominant term: O(n) space
```

---

## Relationship with Other Functions

### Uses Stack Size

```c
void assign_index(t_stack *stack)
{
    int size = stack_size(stack);  // ← Get total elements

    // Use size for array allocation
    int *values = malloc(sizeof(int) * size);
    // ...
}
```

### Uses Copy Function

```c
void assign_index(t_stack *stack)
{
    // ...
    copy_values_to_array(stack, values, size);  // ← Copy to array
    // ...
}
```

### Uses Sort Function

```c
void assign_index(t_stack *stack)
{
    // ...
    sort_int_array(values, size);  // ← Sort copied values
    // ...
}
```

### Uses Index Position Finder

```c
void assign_index(t_stack *stack)
{
    // ...
    while (current)
    {
        current->index = get_index_position(values, size, current->value);
        // ↑ Find rank in sorted array
        current = current->next;
    }
}
```

### Called Before Large Sort

```c
void choose_sort(t_stack **a, t_stack **b)
{
    int size = stack_size(*a);

    if (size <= 3)
        sort_three(a);
    else if (size == 4)
        sort_four(a, b);
    else if (size == 5)
        sort_five(a, b);
    else
    {
        assign_index(*a);  // ← CRITICAL: Normalize before large sort
        sort_large(a, b);
    }
}
```

---

## Integration with Push_swap

### Scenario: Preparing for Large Sort

```c
// Input: ./push_swap 42 -5 1000 3 88 -12 500

// Stack A: [42, -5, 1000, 3, 88, -12, 500]
// Indices: [?, ?, ?, ?, ?, ?, ?]

// Before sorting, normalize:
assign_index(stack_a);

// Now:
// Stack A:   [42, -5, 1000, 3, 88, -12, 500]
// Indices:   [3,  1,  6,    2, 4,  0,   5]

// Sorted order:
// Index 0: -12   (smallest)
// Index 1: -5
// Index 2: 3
// Index 3: 42
// Index 4: 88
// Index 5: 500
// Index 6: 1000  (largest)

// Now can use chunking strategy:
// Chunk 1: indices 0-1  → push -12, -5 to B
// Chunk 2: indices 2-3  → push 3, 42 to B
// Chunk 3: indices 4-5  → push 88, 500 to B
// Keep index 6 (1000) in A
```

### Scenario: Chunking Based on Indices

```c
void push_chunks_to_b(t_stack **a, t_stack **b)
{
    int size = stack_size(*a);
    int chunk_size = size / 5;  // Divide into 5 chunks

    // Chunks based on indices:
    // Chunk 0: indices 0 to chunk_size-1
    // Chunk 1: indices chunk_size to 2*chunk_size-1
    // etc.

    for (int chunk = 0; chunk < 5; chunk++)
    {
        int min_idx = chunk * chunk_size;
        int max_idx = (chunk + 1) * chunk_size - 1;

        // Push all elements in this index range
        while (has_elements_in_range(*a, min_idx, max_idx))
        {
            if ((*a)->index >= min_idx && (*a)->index <= max_idx)
                pb(a, b, 1);  // Push to B
            else
                ra(a, 1);     // Rotate to find next
        }
    }
}

// This strategy ONLY works because indices are normalized!
// Can't do this with arbitrary values like 42, -5, 1000
```

### Scenario: Verification

```c
// After assign_index, verify correctness:
void verify_indices(t_stack *stack)
{
    int size = stack_size(stack);
    int *seen = calloc(size, sizeof(int));

    t_stack *current = stack;
    while (current)
    {
        // Check index is in valid range
        if (current->index < 0 || current->index >= size)
        {
            printf("Error: Invalid index %d\n", current->index);
            return;
        }

        // Check no duplicate indices
        if (seen[current->index])
        {
            printf("Error: Duplicate index %d\n", current->index);
            return;
        }

        seen[current->index] = 1;
        current = current->next;
    }

    // Check all indices present
    for (int i = 0; i < size; i++)
    {
        if (!seen[i])
        {
            printf("Error: Missing index %d\n", i);
            return;
        }
    }

    printf("✅ All indices valid and unique!\n");
    free(seen);
}
```

---

## 42 Norm Considerations

### Function Structure

```c
void	assign_index(t_stack *stack)
{
	int		size;
	int		*values;
	t_stack	*current;

	size = stack_size(stack);
	if (size == 0)
		return ;
	values = malloc(sizeof(int) * size);
	if (!values)
		return ;
	copy_values_to_array(stack, values, size);
	sort_int_array(values, size);
	current = stack;
	while (current)
	{
		current->index = get_index_position(values, size, current->value);
		current = current->next;
	}
	free(values);
}
```

**Norm compliance:**
- ✅ Under 25 lines
- ✅ Single responsibility: assigns normalized indices
- ✅ 3 variables (size, values, current)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Delegates to helper functions (copy, sort, get_index_position)

### Helper Functions Required

```c
// All these must be separate functions (Norm requirement)
int		stack_size(t_stack *stack);
void	copy_values_to_array(t_stack *stack, int *arr, int size);
void	sort_int_array(int *arr, int size);
int		get_index_position(int *arr, int size, int value);
```

---

## Common Mistakes

### Mistake 1: Not Checking Malloc Failure

```c
// ❌ WRONG
void assign_index(t_stack *stack)
{
    int size = stack_size(stack);
    int *values = malloc(sizeof(int) * size);

    // If malloc fails, values is NULL
    copy_values_to_array(stack, values, size);  // CRASH!
}
```

**✅ Correct:**
```c
int *values = malloc(sizeof(int) * size);
if (!values)
    return;  // Handle allocation failure
```

### Mistake 2: Forgetting to Free Array

```c
// ❌ WRONG - Memory leak!
void assign_index(t_stack *stack)
{
    int *values = malloc(sizeof(int) * size);
    copy_values_to_array(stack, values, size);
    sort_int_array(values, size);
    // ... assign indices
    // Forgot: free(values);
}
```

**✅ Correct:**
```c
// ... assign indices
free(values);  // CRITICAL!
```

### Mistake 3: Using Value Instead of Index

```c
// ❌ WRONG - Using wrong field for comparison
if ((*a)->value >= min_idx && (*a)->value <= max_idx)
    pb(a, b, 1);
// Should use index, not value!
```

**✅ Correct:**
```c
if ((*a)->index >= min_idx && (*a)->index <= max_idx)
    pb(a, b, 1);
```

### Mistake 4: Off-by-One in Index Range

```c
// ❌ WRONG - Indices should be 0 to size-1, not 1 to size
for (int i = 1; i <= size; i++)  // Wrong range!
{
    // ...
}
```

**✅ Correct:**
```c
for (int i = 0; i < size; i++)  // Correct: 0 to size-1
{
    // ...
}
```

### Mistake 5: Not Sorting Before Finding Indices

```c
// ❌ WRONG - Array must be sorted!
copy_values_to_array(stack, values, size);
// Forgot: sort_int_array(values, size);
current = stack;
while (current)
{
    current->index = get_index_position(values, size, current->value);
    // Will find wrong positions in unsorted array!
}
```

**✅ Correct:**
```c
copy_values_to_array(stack, values, size);
sort_int_array(values, size);  // CRITICAL!
// Now positions represent ranks
```

---

## Testing Strategy

### Test 1: Basic Normalization

```c
// Create stack
stack = create_stack([5, 3, 8, 1]);

// Assign indices
assign_index(stack);

// Verify
// Values:  [5, 3, 8, 1]
// Sorted:  [1, 3, 5, 8]
// Indices: [2, 1, 3, 0]
assert(get_node_at(stack, 0)->index == 2);  // 5 → index 2
assert(get_node_at(stack, 1)->index == 1);  // 3 → index 1
assert(get_node_at(stack, 2)->index == 3);  // 8 → index 3
assert(get_node_at(stack, 3)->index == 0);  // 1 → index 0
```

### Test 2: Edge Cases

```c
// Empty
assign_index(NULL);  // Should not crash

// Single element
stack = create_stack([42]);
assign_index(stack);
assert(stack->index == 0);

// Two elements
stack = create_stack([5, 3]);
assign_index(stack);
assert(stack->index == 1);        // 5 → index 1
assert(stack->next->index == 0);  // 3 → index 0
```

### Test 3: Negative Numbers

```c
stack = create_stack([5, -10, 0, -5, 3]);
assign_index(stack);

// Sorted: [-10, -5, 0, 3, 5]
// Expected indices: [4, 0, 2, 1, 3]
assert(get_node_at(stack, 0)->index == 4);  // 5
assert(get_node_at(stack, 1)->index == 0);  // -10
assert(get_node_at(stack, 2)->index == 2);  // 0
assert(get_node_at(stack, 3)->index == 1);  // -5
assert(get_node_at(stack, 4)->index == 3);  // 3
```

### Test 4: Already Sorted

```c
stack = create_stack([1, 2, 3, 4, 5]);
assign_index(stack);

// Should get indices [0, 1, 2, 3, 4]
for (int i = 0; i < 5; i++)
    assert(get_node_at(stack, i)->index == i);
```

### Test 5: Reverse Sorted

```c
stack = create_stack([5, 4, 3, 2, 1]);
assign_index(stack);

// Should get indices [4, 3, 2, 1, 0]
for (int i = 0; i < 5; i++)
    assert(get_node_at(stack, i)->index == 4 - i);
```

### Test 6: Unique Indices

```c
// All indices must be unique and in range 0 to n-1
stack = create_random_stack(100);
assign_index(stack);

int seen[100] = {0};
t_stack *temp = stack;
while (temp)
{
    assert(temp->index >= 0 && temp->index < 100);
    assert(seen[temp->index] == 0);  // No duplicates
    seen[temp->index] = 1;
    temp = temp->next;
}

// All indices present
for (int i = 0; i < 100; i++)
    assert(seen[i] == 1);
```

---

## Summary

**What assign_index Does:**
1. Copies stack values to array
2. Sorts array to determine ranking order
3. Assigns each node an index representing its rank (0 = smallest)
4. Enables efficient chunking and comparison in large sort

**Key Characteristics:**
- ✅ Transforms arbitrary values to 0...N-1 indices
- ✅ O(n²) time with linear search, O(n log n) with binary search
- ✅ O(n) space for temporary array
- ✅ Essential preprocessing for large sorting algorithm
- ✅ Creates predictable, normalized data

**Critical Uses:**
- Prerequisite for Turk algorithm
- Enables efficient chunking strategy
- Simplifies comparisons and partitioning
- Allows bitwise operations on normalized data

**Remember:**
- Must be called before large sort
- Indices represent relative rank, not values
- Smallest value always gets index 0
- Largest value always gets index N-1
- All indices unique and in range [0, N-1]

**Integration Pattern:**
```
1. Parse input → stack with arbitrary values
2. assign_index() → normalize to 0...N-1
3. Use indices for chunking and sorting
4. Final result based on original values
```

---

## Location in Project

**File:** `srcs/index.c` or `srcs/normalization.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 5 (Index Normalization)

---

## Related Functions

- [copy_values_to_array](copy_values_to_array.md) - Copies stack values to array
- [sort_int_array](sort_int_array.md) - Sorts the copied array
- [get_index_position](get_index_position.md) - Finds rank in sorted array
- [stack_size](stack_size.md) - Gets number of elements
- [sort_large](sort_large.md) - Uses indices for large sorting
- [push_chunks_to_b](push_chunks_to_b.md) - Uses indices for chunking

---

*Index normalization is the bridge between arbitrary input and efficient sorting - master this and you understand why the Turk algorithm works so well!*
