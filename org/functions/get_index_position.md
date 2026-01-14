# get_index_position - Find Index (Rank) of Value in Sorted Array

## Function Signature

```c
int get_index_position(int *arr, int size, int value)
```

**Return type:** `int` - The position (index) where the value is found
**Parameters:**
- `int *arr` - Pointer to sorted integer array
- `int size` - Number of elements in the array
- `int value` - The value to search for

---

## Purpose & Use Case

`get_index_position` is a **search function** that finds where a specific value appears in a sorted array, returning its position (which represents the value's rank). This is a critical helper for `assign_index`, converting arbitrary values into normalized 0-based indices.

### When You'll Use It

You'll call `get_index_position` when you need to:
1. **Find rank of a value** - Determine position in sorted order
2. **Assign indices** - Called by `assign_index` for each stack node
3. **Normalize data** - Convert value to its relative rank
4. **Map values to positions** - Link original values to sorted positions
5. **Implement ranking algorithm** - Core component of index normalization

### Why Position Finding Matters

**Position in sorted array = Rank/Index:**
```
Sorted array: [1, 3, 5, 8, 12]
Positions:     0  1  2  3  4

get_index_position(arr, 5, 8) → returns 3
- Value 8 is at position 3
- Position 3 means 8 is the 4th smallest (3+1)
- This becomes the normalized index!

This mapping is essential:
Value → Position in sorted array → Index (rank)
8     → 3                        → 3
```

### Real-World Analogy

**Finding student's rank in grade list:**
```
Sorted grade list:
Position 0: 65  (lowest)
Position 1: 78
Position 2: 85
Position 3: 92
Position 4: 98  (highest)

Student has grade 85:
Find where 85 appears → Position 2
Position 2 = Rank 2 (3rd best when 0-indexed)

get_index_position does this for stack values!
```

---

## Deep Dive: How It Works

### The Linear Search Algorithm

**Concept:**
- Start at the beginning of the sorted array
- Check each position sequentially
- When value is found, return that position
- Position represents the value's rank

### Algorithm Visualization

**Array Example:** [-5, 3, 42, 1000]

```
Search for value: 42

Step 1: Check position 0
arr[0] = -5
-5 == 42? No

Step 2: Check position 1
arr[1] = 3
3 == 42? No

Step 3: Check position 2
arr[2] = 42
42 == 42? Yes! ✅
Return 2

Result: 42 is at position 2 (the 3rd element)
```

### Search Process Detailed

```
Sorted Array: [-5, 3, 42, 1000]
              ↑   ↑  ↑   ↑
Position:     0   1  2   3

Finding position of 42:
i = 0: arr[0] = -5   ≠ 42
i = 1: arr[1] = 3    ≠ 42
i = 2: arr[2] = 42   = 42 ✅ FOUND!
Return i = 2

Finding position of -5:
i = 0: arr[0] = -5   = -5 ✅ FOUND!
Return i = 0

Finding position of 1000:
i = 0: arr[0] = -5    ≠ 1000
i = 1: arr[1] = 3     ≠ 1000
i = 2: arr[2] = 42    ≠ 1000
i = 3: arr[3] = 1000  = 1000 ✅ FOUND!
Return i = 3
```

---

## Step-by-Step Implementation

### Step 1: Initialize Search Position

**Start at beginning:**
```c
int i = 0;
```

**Why start at 0:**
```
Array is 0-indexed
First element at position 0
Linear search from left to right
```

### Step 2: Iterate Through Array

**Loop through positions:**
```c
while (i < size)
{
    // Check current position
    i++;
}
```

**Bounds checking:**
```
i < size ensures we don't go past array end
size = 4: valid indices are 0, 1, 2, 3
Loop runs for i = 0, 1, 2, 3
Stops when i = 4 (out of bounds)
```

### Step 3: Compare Value at Each Position

**Check if found:**
```c
while (i < size)
{
    if (arr[i] == value)
        return (i);  // Found! Return position
    i++;
}
```

**Comparison logic:**
```
For each position:
- Is arr[i] equal to the target value?
- YES: Return current position (i)
- NO: Move to next position (i++)
```

### Step 4: Handle Not Found Case

**Fallback return:**
```c
return (-1);  // Value not found
```

**Why -1:**
```
Valid positions: 0 to size-1
-1 indicates "not found"
Standard convention for search failure
In assign_index context, should never happen
(all values in stack must exist in array)
```

---

## Complete Algorithm Pseudocode

```
FUNCTION get_index_position(arr, size, value):
    // Step 1: Initialize position
    i = 0

    // Step 2: Search through array
    WHILE i < size:
        // Step 3: Check if current position has value
        IF arr[i] == value:
            RETURN i  // Found! Return position

        // Move to next position
        i = i + 1

    // Step 4: Not found (should not happen in assign_index)
    RETURN -1
END FUNCTION
```

---

## Visual Execution Trace

### Example 1: Finding 42 in [-5, 3, 42, 1000]

```
Array: [-5, 3, 42, 1000]
Size: 4
Target value: 42

Call: position = get_index_position(arr, 4, 42)

Step 1: Initialize
i = 0

Step 2-3: Loop iteration 1
i = 0 (i < 4? Yes, continue)
arr[0] = -5
-5 == 42? No
i++ → i = 1

Step 2-3: Loop iteration 2
i = 1 (i < 4? Yes, continue)
arr[1] = 3
3 == 42? No
i++ → i = 2

Step 2-3: Loop iteration 3
i = 2 (i < 4? Yes, continue)
arr[2] = 42
42 == 42? Yes! ✅
Return 2

Result: position = 2
```

### Example 2: Finding -5 in [-5, 3, 42, 1000]

```
Array: [-5, 3, 42, 1000]
Size: 4
Target value: -5

Call: position = get_index_position(arr, 4, -5)

Step 1: Initialize
i = 0

Step 2-3: Loop iteration 1
i = 0 (i < 4? Yes, continue)
arr[0] = -5
-5 == -5? Yes! ✅
Return 0

Result: position = 0
(Found immediately in first check)
```

### Example 3: Finding 1000 in [-5, 3, 42, 1000]

```
Array: [-5, 3, 42, 1000]
Size: 4
Target value: 1000

Call: position = get_index_position(arr, 4, 1000)

Step 1: Initialize
i = 0

Step 2-3: Loop iterations 1-3
i = 0: arr[0] = -5    ≠ 1000, i++ → 1
i = 1: arr[1] = 3     ≠ 1000, i++ → 2
i = 2: arr[2] = 42    ≠ 1000, i++ → 3

Step 2-3: Loop iteration 4
i = 3 (i < 4? Yes, continue)
arr[3] = 1000
1000 == 1000? Yes! ✅
Return 3

Result: position = 3
(Had to check all 4 positions)
```

---

## Edge Cases

### Case 1: Value at First Position

```c
// Array: [1, 5, 8, 12]
int pos = get_index_position(arr, 4, 1);

// Result: 0 (immediate match)
// Best case: O(1)
```

### Case 2: Value at Last Position

```c
// Array: [1, 5, 8, 12]
int pos = get_index_position(arr, 4, 12);

// Result: 3 (checked all 4 positions)
// Worst case: O(n)
```

### Case 3: Value in Middle

```c
// Array: [1, 5, 8, 12, 20]
int pos = get_index_position(arr, 5, 8);

// Result: 2 (checked 3 positions)
// Average case: O(n/2)
```

### Case 4: Single Element

```c
// Array: [42]
int pos = get_index_position(arr, 1, 42);

// Result: 0
// Only one check needed
```

### Case 5: Value Not in Array

```c
// Array: [1, 5, 8, 12]
int pos = get_index_position(arr, 4, 99);

// Result: -1 (not found)
// Should never happen in assign_index context!
```

### Case 6: Negative Values

```c
// Array: [-100, -50, -10, 0, 10]
int pos = get_index_position(arr, 5, -50);

// Result: 1
// Handles negatives correctly
```

### Case 7: Duplicate Values

```c
// Array: [1, 3, 3, 5, 8]
int pos = get_index_position(arr, 5, 3);

// Result: 1 (first occurrence)
// Returns first match
// Note: assign_index shouldn't have duplicates (no duplicates in stack)
```

---

## Time & Space Complexity

### Time Complexity: **O(n)** - Linear Time

**Linear search:**
```
n = size of array

Best case: O(1)
- Value at position 0
- Immediate match

Average case: O(n/2) = O(n)
- Value somewhere in middle
- Check ~half the array

Worst case: O(n)
- Value at last position
- Check entire array

Overall: O(n) linear search
```

**Can we do better?**
```
YES! Array is sorted → Binary search!

Binary search: O(log n)
Much faster for large arrays

Example:
Array size = 1000
Linear search: up to 1000 comparisons
Binary search: ~10 comparisons (log₂ 1000 ≈ 10)

For assign_index optimization:
- Replace linear with binary search
- Reduces O(n²) to O(n log n)
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
Variables:
- int i (4 bytes)
- Parameters are passed by value/pointer

Total: ~4 bytes, regardless of array size
No additional data structures
No recursion
No allocations

Space = O(1) ✅
```

---

## Relationship with Other Functions

### Called by assign_index

```c
void assign_index(t_stack *stack)
{
    // ... create and sort array

    t_stack *current = stack;
    while (current)
    {
        // For each node, find its rank
        current->index = get_index_position(values, size, current->value);
        //                ↑ Called for every node
        current = current->next;
    }

    // ...
}
```

### Works with Sorted Array

```c
// Prerequisite: array must be sorted!
int *arr = copy_and_sort_stack(stack);  // Creates sorted array

// Now safe to use get_index_position
int pos = get_index_position(arr, size, 42);
```

### Could Use Binary Search Alternative

```c
// Optimized version with binary search
int get_index_position_binary(int *arr, int size, int value)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == value)
            return (mid);
        else if (arr[mid] < value)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return (-1);  // Not found
}

// O(log n) instead of O(n)!
```

---

## Integration with Push_swap

### Scenario: Used in Index Assignment

```c
// Stack: [42, -5, 1000, 3]
// Sorted array: [-5, 3, 42, 1000]

// For node with value 42:
int index = get_index_position(sorted, 4, 42);
// Search: arr[0]=-5, arr[1]=3, arr[2]=42 ✅
// Returns: 2
// node->index = 2

// For node with value -5:
int index = get_index_position(sorted, 4, -5);
// Search: arr[0]=-5 ✅
// Returns: 0
// node->index = 0

// For node with value 1000:
int index = get_index_position(sorted, 4, 1000);
// Search: arr[0]=-5, arr[1]=3, arr[2]=42, arr[3]=1000 ✅
// Returns: 3
// node->index = 3

// For node with value 3:
int index = get_index_position(sorted, 4, 3);
// Search: arr[0]=-5, arr[1]=3 ✅
// Returns: 1
// node->index = 1
```

### Scenario: Performance Impact

```c
// Stack size: 500
// For each of 500 nodes:
//   Linear search through 500-element array
//   Average: 250 comparisons per node
// Total: 500 × 250 = 125,000 comparisons!

// With binary search:
//   log₂(500) ≈ 9 comparisons per node
// Total: 500 × 9 = 4,500 comparisons
// ~28x faster! ✅
```

---

## 42 Norm Considerations

### Function Structure

```c
int	get_index_position(int *arr, int size, int value)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (arr[i] == value)
			return (i);
		i++;
	}
	return (-1);
}
```

**Norm compliance:**
- ✅ Under 25 lines
- ✅ Single responsibility: finds position
- ✅ Only 1 variable (i)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Simple, clear logic

### Binary Search Version (Norm-compliant)

```c
int	get_index_position(int *arr, int size, int value)
{
	int	left;
	int	right;
	int	mid;

	left = 0;
	right = size - 1;
	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (arr[mid] == value)
			return (mid);
		else if (arr[mid] < value)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (-1);
}
```

**Still compliant:**
- ✅ Under 25 lines
- ✅ 3 variables (left, right, mid)
- ✅ Much more efficient O(log n)

---

## Common Mistakes

### Mistake 1: Off-by-One in Loop

```c
// ❌ WRONG
while (i <= size)  // Should be i < size
{
    if (arr[i] == value)
        return (i);
    i++;
}
// When i = size, arr[i] is out of bounds!
```

**✅ Correct:**
```c
while (i < size)  // Stops at i = size-1 (last valid index)
```

### Mistake 2: Not Handling Not Found

```c
// ❌ WRONG - No return if not found
int get_index_position(int *arr, int size, int value)
{
    int i = 0;
    while (i < size)
    {
        if (arr[i] == value)
            return (i);
        i++;
    }
    // Falls off function without return - undefined behavior!
}
```

**✅ Correct:**
```c
return (-1);  // Explicit return for not found case
```

### Mistake 3: Using on Unsorted Array

```c
// ❌ WRONG - Array must be sorted first!
int *arr = copy_values_to_array(stack);  // Unsorted
int pos = get_index_position(arr, size, 42);
// Will still find value, but position is meaningless for ranking!
```

**✅ Correct:**
```c
int *arr = copy_values_to_array(stack);
sort_int_array(arr, size);  // CRITICAL!
int pos = get_index_position(arr, size, 42);
// Now position represents rank
```

### Mistake 4: Not Checking NULL Array

```c
// ❌ WRONG - Potential NULL pointer dereference
int get_index_position(int *arr, int size, int value)
{
    int i = 0;
    while (i < size)
    {
        if (arr[i] == value)  // If arr is NULL, CRASH!
            return (i);
        i++;
    }
    return (-1);
}
```

**✅ Better:**
```c
int get_index_position(int *arr, int size, int value)
{
    int i;

    if (!arr || size <= 0)
        return (-1);
    i = 0;
    while (i < size)
    {
        if (arr[i] == value)
            return (i);
        i++;
    }
    return (-1);
}
```

### Mistake 5: Returning Wrong Type

```c
// ❌ WRONG - Returning pointer instead of index
return (&arr[i]);  // Returns address, not position!
```

**✅ Correct:**
```c
return (i);  // Return integer position
```

---

## Testing Strategy

### Test 1: Basic Search

```c
int arr[] = {1, 3, 5, 8, 12};

// Find each element
assert(get_index_position(arr, 5, 1) == 0);
assert(get_index_position(arr, 5, 3) == 1);
assert(get_index_position(arr, 5, 5) == 2);
assert(get_index_position(arr, 5, 8) == 3);
assert(get_index_position(arr, 5, 12) == 4);
```

### Test 2: Edge Cases

```c
// Single element
int arr1[] = {42};
assert(get_index_position(arr1, 1, 42) == 0);

// Not found
int arr2[] = {1, 3, 5};
assert(get_index_position(arr2, 3, 99) == -1);

// First position
int arr3[] = {10, 20, 30};
assert(get_index_position(arr3, 3, 10) == 0);

// Last position
assert(get_index_position(arr3, 3, 30) == 2);
```

### Test 3: Negative Numbers

```c
int arr[] = {-100, -50, -10, 0, 10, 50};

assert(get_index_position(arr, 6, -100) == 0);
assert(get_index_position(arr, 6, -10) == 2);
assert(get_index_position(arr, 6, 0) == 3);
assert(get_index_position(arr, 6, 50) == 5);
```

### Test 4: Large Array

```c
// Create sorted array of 1000 elements
int *arr = create_sorted_array(1000);

// Test various positions
assert(get_index_position(arr, 1000, arr[0]) == 0);
assert(get_index_position(arr, 1000, arr[500]) == 500);
assert(get_index_position(arr, 1000, arr[999]) == 999);

free(arr);
```

### Test 5: Integration with assign_index

```c
t_stack *stack = create_stack([42, -5, 1000, 3]);

// Create sorted array
int size = stack_size(stack);
int *sorted = malloc(sizeof(int) * size);
copy_values_to_array(stack, sorted, size);
sort_int_array(sorted, size);
// sorted = [-5, 3, 42, 1000]

// Verify each value maps to correct index
t_stack *current = stack;
while (current)
{
    int index = get_index_position(sorted, size, current->value);
    assert(index >= 0 && index < size);  // Valid index

    // Verify it's the correct value
    assert(sorted[index] == current->value);

    current = current->next;
}

free(sorted);
```

---

## Summary

**What get_index_position Does:**
1. Searches through sorted array for target value
2. Returns position (index) where value is found
3. Position represents value's rank (0 = smallest)
4. Critical helper for index normalization

**Key Characteristics:**
- ✅ Simple linear search
- ✅ O(n) time, O(1) space
- ✅ Can be optimized to O(log n) with binary search
- ✅ Returns -1 if not found
- ✅ Works only on sorted arrays

**Critical Uses:**
- Called by assign_index for every node
- Converts values to normalized indices
- Maps arbitrary numbers to predictable ranks
- Foundation of chunking strategy

**Remember:**
- Array MUST be sorted first
- Returns position, not value
- Position = rank in sorted order
- Can optimize with binary search
- Performance critical for large stacks

**Optimization Opportunity:**
```
Current: Linear search O(n)
- Simple to implement
- Works for small arrays
- Gets slow for large arrays

Better: Binary search O(log n)
- More complex code
- Much faster for large arrays
- Reduces assign_index from O(n²) to O(n log n)
```

---

## Location in Project

**File:** `srcs/index.c` or `srcs/index_utils.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 5 (Index Normalization)

---

## Related Functions

- [assign_index](assign_index.md) - Main function that calls this
- [sort_int_array](sort_int_array.md) - Sorts array before searching
- [copy_values_to_array](copy_values_to_array.md) - Creates array to search
- [stack_size](stack_size.md) - Determines array size

---

*Finding position is finding rank - this simple search is the key to transforming arbitrary values into workable indices!*
