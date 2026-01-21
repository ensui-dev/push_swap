# sort_int_array - Sort Integer Array Using Simple Algorithm

## Function Signature

```c
void sort_int_array(int *arr, int size)
```

**Return type:** `void` - Sorts array in place
**Parameters:**
- `int *arr` - Pointer to integer array to sort
- `int size` - Number of elements in the array

---

## Purpose & Use Case

`sort_int_array` is a **sorting function** that arranges an integer array in ascending order (smallest to largest). It's used as a helper in index normalization to create a sorted reference array for determining value ranks. The implementation uses a simple sorting algorithm like selection sort or bubble sort, prioritizing simplicity over optimal performance.

### When You'll Use It

You'll call `sort_int_array` when you need to:
1. **Index normalization** - Sort copied values to determine ranks
2. **Create ranking reference** - Produce sorted array for position lookup
3. **Prepare for binary search** - Sorted array enables efficient searching
4. **Order values** - Simple in-place sorting of small to medium arrays
5. **Helper for assign_index** - Critical step in normalization process

### Why Array Sorting Matters

**Sorted array reveals ranking order:**
```
Unsorted: [42, -5, 1000, 3]
Sorted:   [-5, 3, 42, 1000]
          ↑   ↑  ↑   ↑
          0   1  2   3  ← Positions = Ranks!

Now we can map values to ranks:
-5 is at position 0 → rank 0 (smallest)
3 is at position 1 → rank 1
42 is at position 2 → rank 2
1000 is at position 3 → rank 3 (largest)

This mapping is the foundation of index normalization!
```

### Real-World Analogy

**Sorting test scores to assign grades:**
```
Raw scores (unsorted): [78, 92, 65, 88, 100]

Sort scores ascending: [65, 78, 88, 92, 100]

Now assign letter grades by rank:
Position 0 (65): D  ← Lowest
Position 1 (78): C
Position 2 (88): B
Position 3 (92): B+
Position 4 (100): A ← Highest

sort_int_array does the same for stack values!
```

---

## Deep Dive: How It Works

### Selection Sort Algorithm

**Concept:**
- Divide array into sorted and unsorted portions
- Find minimum element in unsorted portion
- Swap it to the end of sorted portion
- Repeat until entire array is sorted

**Why Selection Sort:**
```
Advantages:
✅ Simple to implement
✅ Works in-place (O(1) space)
✅ Predictable behavior
✅ Good for small arrays

Disadvantages:
❌ O(n²) time complexity
❌ Not efficient for large arrays
❌ Not stable (equal elements may swap)

For push_swap:
- Arrays typically small to medium (up to 500)
- Simplicity valued over optimal performance
- O(n²) acceptable for this use case
```

### Algorithm Visualization

**Array Example:** [42, -5, 1000, 3]

```
Initial: [42, -5, 1000, 3]
         ↑ Unsorted portion starts here

Pass 1: Find minimum in unsorted portion
Unsorted: [42, -5, 1000, 3]
Minimum: -5 (at index 1)
Swap with first unsorted (index 0):
Result: [-5, 42, 1000, 3]
        ↑sorted ↑ Unsorted starts here

Pass 2: Find minimum in unsorted portion
Unsorted: [42, 1000, 3]
Minimum: 3 (at index 3)
Swap with first unsorted (index 1):
Result: [-5, 3, 1000, 42]
        ↑sorted↑sorted ↑ Unsorted starts here

Pass 3: Find minimum in unsorted portion
Unsorted: [1000, 42]
Minimum: 42 (at index 3)
Swap with first unsorted (index 2):
Result: [-5, 3, 42, 1000]
        ↑sorted↑sorted↑sorted ↑ Last element

Pass 4: Only one element left, already sorted!

Final: [-5, 3, 42, 1000] ✅ Fully sorted!
```

### Step-by-Step Process

```
Array: [42, -5, 1000, 3]
Size: 4

Outer loop (i): Marks end of sorted portion
Inner loop (j): Finds minimum in unsorted portion

i=0: Sorted: [] Unsorted: [42, -5, 1000, 3]
  Find min in unsorted: -5 at index 1
  Swap arr[0] ↔ arr[1]: [42, -5] → [-5, 42]
  Result: [-5, 42, 1000, 3]

i=1: Sorted: [-5] Unsorted: [42, 1000, 3]
  Find min in unsorted: 3 at index 3
  Swap arr[1] ↔ arr[3]: [42, 3] → [3, 42]
  Result: [-5, 3, 1000, 42]

i=2: Sorted: [-5, 3] Unsorted: [1000, 42]
  Find min in unsorted: 42 at index 3
  Swap arr[2] ↔ arr[3]: [1000, 42] → [42, 1000]
  Result: [-5, 3, 42, 1000]

i=3: Sorted: [-5, 3, 42] Unsorted: [1000]
  Only one element, already in place
  Result: [-5, 3, 42, 1000] ✅
```

---

## Step-by-Step Implementation

### Step 1: Outer Loop - Iterate Through Array

**Build sorted portion:**
```c
int i = 0;
while (i < size - 1)
{
    // Process each position
    i++;
}
```

**Why size - 1:**
```
Array of 4 elements: indices 0, 1, 2, 3

i = 0: Sort position 0 (find min in 0-3, place at 0)
i = 1: Sort position 1 (find min in 1-3, place at 1)
i = 2: Sort position 2 (find min in 2-3, place at 2)
i = 3: Last element already sorted!

Loop runs i = 0 to size-2 (0 to 2 for size 4)
Final iteration unnecessary (only 1 element left)
```

### Step 2: Find Minimum Index

**Initialize:**
```c
int min_idx = i;
```

**Starting assumption:**
```
Assume first element of unsorted portion is minimum
Will update if we find smaller
```

### Step 3: Inner Loop - Search for Minimum

**Scan unsorted portion:**
```c
int j = i + 1;
while (j < size)
{
    if (arr[j] < arr[min_idx])
        min_idx = j;
    j++;
}
```

**Process:**
```
Start at i+1 (first unsorted element)
Compare each element with current minimum
Update min_idx when smaller element found
Continue to end of array
```

### Step 4: Swap Minimum to Sorted Position

**Exchange values:**
```c
int temp = arr[i];
arr[i] = arr[min_idx];
arr[min_idx] = temp;
```

**Three-step swap:**
```
Before: arr[i] = 42, arr[min_idx] = -5

Step 1: temp = arr[i]        → temp = 42
Step 2: arr[i] = arr[min_idx] → arr[i] = -5
Step 3: arr[min_idx] = temp   → arr[min_idx] = 42

After: arr[i] = -5, arr[min_idx] = 42
```

---

## Complete Algorithm Pseudocode

### Basic Implementation (Using WHILE loops)

```
FUNCTION sort_int_array(arr, size):
    // Outer loop: build sorted portion
    i = 0
    WHILE i < size - 1:
        // Step 1: Assume first unsorted is minimum
        min_idx = i

        // Step 2: Find actual minimum in unsorted portion
        j = i + 1
        WHILE j < size:
            IF arr[j] < arr[min_idx]:
                min_idx = j  // Update minimum index
            j = j + 1

        // Step 3: Swap minimum to sorted position
        IF min_idx != i:  // Only swap if different
            temp = arr[i]
            arr[i] = arr[min_idx]
            arr[min_idx] = temp

        i = i + 1

    // Done! Array sorted in ascending order
END FUNCTION
```

### Defensive Implementation

```
FUNCTION sort_int_array(arr, size):
    // Step 1: DEFENSIVE - Validate inputs
    IF arr is NULL OR size <= 1:
        RETURN  // Nothing to sort

    // Step 2: Outer loop - build sorted portion
    i = 0
    WHILE i < size - 1:
        // Step 3: Assume first unsorted is minimum
        min_idx = i

        // Step 4: Find actual minimum in unsorted portion
        j = i + 1
        WHILE j < size:
            IF arr[j] < arr[min_idx]:
                min_idx = j  // Update minimum index
            j = j + 1

        // Step 5: Swap minimum to sorted position
        IF min_idx != i:  // Only swap if necessary
            temp = arr[i]
            arr[i] = arr[min_idx]
            arr[min_idx] = temp

        i = i + 1

    // Done! Array sorted in ascending order
END FUNCTION
```

---

## Visual Execution Trace

### Example: Sorting [42, -5, 1000, 3]

```
Initial State:
Array: [42, -5, 1000, 3]
Size: 4

Call: sort_int_array(arr, 4)

Outer Loop i=0:
  Sorted: []
  Unsorted: [42, -5, 1000, 3]

  min_idx = 0 (assume arr[0] = 42 is min)

  Inner loop j=1:
    arr[1] = -5 < arr[0] = 42? Yes!
    min_idx = 1

  Inner loop j=2:
    arr[2] = 1000 < arr[1] = -5? No
    min_idx = 1

  Inner loop j=3:
    arr[3] = 3 < arr[1] = -5? No
    min_idx = 1

  Minimum found: -5 at index 1
  Swap arr[0] ↔ arr[1]: [42, -5] → [-5, 42]
  Array: [-5, 42, 1000, 3]

Outer Loop i=1:
  Sorted: [-5]
  Unsorted: [42, 1000, 3]

  min_idx = 1 (assume arr[1] = 42 is min)

  Inner loop j=2:
    arr[2] = 1000 < arr[1] = 42? No
    min_idx = 1

  Inner loop j=3:
    arr[3] = 3 < arr[1] = 42? Yes!
    min_idx = 3

  Minimum found: 3 at index 3
  Swap arr[1] ↔ arr[3]: [42, 3] → [3, 42]
  Array: [-5, 3, 1000, 42]

Outer Loop i=2:
  Sorted: [-5, 3]
  Unsorted: [1000, 42]

  min_idx = 2 (assume arr[2] = 1000 is min)

  Inner loop j=3:
    arr[3] = 42 < arr[2] = 1000? Yes!
    min_idx = 3

  Minimum found: 42 at index 3
  Swap arr[2] ↔ arr[3]: [1000, 42] → [42, 1000]
  Array: [-5, 3, 42, 1000]

Outer Loop exits (i = 3, 3 < 4-1? No)

Final State:
Array: [-5, 3, 42, 1000] ✅ Sorted!

Verification:
-5 ≤ 3 ≤ 42 ≤ 1000 ✅ Ascending order
```

---

## Edge Cases

### Case 1: Empty Array

```c
int arr[0];
sort_int_array(arr, 0);

// Outer loop: i < 0-1? No, never runs
// No operations
// Safe ✅
```

### Case 2: Single Element

```c
int arr[] = {42};
sort_int_array(arr, 1);

// Outer loop: i < 1-1 = 0? No, never runs
// Single element already "sorted"
// Result: [42] ✅
```

### Case 3: Two Elements (Sorted)

```c
int arr[] = {3, 5};
sort_int_array(arr, 2);

// i=0: min in [3,5] is 3 at index 0
//      Swap with self (no change)
// Result: [3, 5] ✅
```

### Case 4: Two Elements (Unsorted)

```c
int arr[] = {5, 3};
sort_int_array(arr, 2);

// i=0: min in [5,3] is 3 at index 1
//      Swap arr[0] ↔ arr[1]
// Result: [3, 5] ✅
```

### Case 5: Already Sorted

```c
int arr[] = {1, 2, 3, 4, 5};
sort_int_array(arr, 5);

// Each pass finds minimum at current position
// No swaps needed (min_idx == i every time)
// Result: [1, 2, 3, 4, 5] ✅ Unchanged
```

### Case 6: Reverse Sorted

```c
int arr[] = {5, 4, 3, 2, 1};
sort_int_array(arr, 5);

// Worst case: every pass needs swap
// i=0: swap 5↔1 → [1, 4, 3, 2, 5]
// i=1: swap 4↔2 → [1, 2, 3, 4, 5]
// i=2: 3 already min, no swap
// i=3: 4 already min, no swap
// Result: [1, 2, 3, 4, 5] ✅
```

### Case 7: Duplicates

```c
int arr[] = {3, 1, 3, 2, 1};
sort_int_array(arr, 5);

// Handles duplicates (not stable, order may change)
// Result: [1, 1, 2, 3, 3] ✅ Sorted
```

### Case 8: Negative Numbers

```c
int arr[] = {5, -10, 0, -5, 3};
sort_int_array(arr, 5);

// Handles negatives correctly
// Result: [-10, -5, 0, 3, 5] ✅
```

### Case 9: All Same Values

```c
int arr[] = {7, 7, 7, 7, 7};
sort_int_array(arr, 5);

// No swaps (all equal)
// Result: [7, 7, 7, 7, 7] ✅
```

---

## Time & Space Complexity

### Time Complexity: **O(n²)** - Quadratic Time

**Nested loops:**
```
n = size of array

Outer loop: runs n-1 times
Inner loop: runs n-i-1 times for each i

Total comparisons:
i=0: (n-1) comparisons
i=1: (n-2) comparisons
i=2: (n-3) comparisons
...
i=n-2: 1 comparison

Total = (n-1) + (n-2) + ... + 1
     = n(n-1)/2
     = (n² - n)/2
     = O(n²)
```

**Performance examples:**
```
n=4:   6 comparisons  (4×3/2 = 6)
n=10:  45 comparisons (10×9/2 = 45)
n=100: 4,950 comparisons (100×99/2 = 4,950)
n=500: 124,750 comparisons (500×499/2 = 124,750)

Grows quadratically!
```

**Is this acceptable?**
```
For small arrays (n < 50): Perfectly fine
For medium arrays (50-500): Acceptable
For large arrays (n > 1000): Consider O(n log n) algorithms

In push_swap context:
- Max 500 elements typical
- Simple implementation preferred
- O(n²) is acceptable ✅
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
Variables:
- int i (4 bytes)
- int j (4 bytes)
- int min_idx (4 bytes)
- int temp (4 bytes for swap)

Total: ~16 bytes, regardless of array size

Sorts in place (modifies original array)
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
    int size = stack_size(stack);
    int *values = malloc(sizeof(int) * size);

    copy_values_to_array(stack, values, size);

    // Sort the copied array
    sort_int_array(values, size);  // ← Used here

    // Now use sorted array to assign indices
    // ...
}
```

### Alternative: Bubble Sort Implementation

```c
void sort_int_array_bubble(int *arr, int size)
{
    int i;
    int j;
    int temp;
    int swapped;

    i = 0;
    while (i < size - 1)
    {
        swapped = 0;
        j = 0;
        while (j < size - i - 1)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
            j++;
        }
        if (!swapped)
            break;  // Already sorted
        i++;
    }
}
```

### Could Use Standard Library (Not Recommended)

```c
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void sort_int_array(int *arr, int size)
{
    qsort(arr, size, sizeof(int), compare);
    // O(n log n) but uses stdlib
    // Not allowed in 42 projects!
}
```

---

## Integration with Push_swap

### Scenario: Creating Sorted Reference

```c
// Stack: [42, -5, 1000, 3]

// Step 1: Copy to array
int size = 4;
int *values = malloc(sizeof(int) * size);
copy_values_to_array(stack, values, size);
// Array: [42, -5, 1000, 3]

// Step 2: Sort array
sort_int_array(values, size);
// Array: [-5, 3, 42, 1000] ✅

// Step 3: Use for index assignment
// Position 0: -5 → index 0
// Position 1: 3 → index 1
// Position 2: 42 → index 2
// Position 3: 1000 → index 3

// Clean up
free(values);
```

---

## 42 Norm Considerations

### Selection Sort Implementation

```c
void	sort_int_array(int *arr, int size)
{
	int	i;
	int	j;
	int	min_idx;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		min_idx = i;
		j = i + 1;
		while (j < size)
		{
			if (arr[j] < arr[min_idx])
				min_idx = j;
			j++;
		}
		if (min_idx != i)
		{
			temp = arr[i];
			arr[i] = arr[min_idx];
			arr[min_idx] = temp;
		}
		i++;
	}
}
```

**Norm compliance:**
- ✅ Under 25 lines
- ✅ 4 variables (i, j, min_idx, temp)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ In-place sorting

---

## Common Mistakes

### Mistake 1: Off-by-One in Outer Loop

```c
// ❌ WRONG
while (i < size)  // Should be size-1
{
    // Last iteration unnecessary
}
```

**✅ Correct:**
```c
while (i < size - 1)  // Stop one before end
```

### Mistake 2: Starting Inner Loop at Wrong Position

```c
// ❌ WRONG
j = i;  // Should be i+1
while (j < size)
{
    if (arr[j] < arr[min_idx])
        min_idx = j;
    j++;
}
// Compares element with itself!
```

**✅ Correct:**
```c
j = i + 1;  // Start after current position
```

### Mistake 3: Forgetting to Swap

```c
// ❌ WRONG - Found minimum but didn't swap!
min_idx = find_minimum_index(arr, i, size);
// Result: array unchanged
```

**✅ Correct:**
```c
// After finding min_idx, swap:
temp = arr[i];
arr[i] = arr[min_idx];
arr[min_idx] = temp;
```

### Mistake 4: Incorrect Swap

```c
// ❌ WRONG - Lost data!
arr[i] = arr[min_idx];
arr[min_idx] = arr[i];
// Both have same value now!
```

**✅ Correct:**
```c
temp = arr[i];           // Save first
arr[i] = arr[min_idx];   // Overwrite first
arr[min_idx] = temp;     // Use saved value
```

### Mistake 5: Not Handling NULL or Size 0

```c
// ❌ WRONG
void sort_int_array(int *arr, int size)
{
    int i = 0;
    while (i < size - 1)
    {
        // If arr is NULL or size is 0, problems!
    }
}
```

**✅ Better:**
```c
void sort_int_array(int *arr, int size)
{
    if (!arr || size <= 1)
        return;  // Nothing to sort
    // ... rest of code
}
```

---

## Testing Strategy

### Test 1: Basic Sorting

```c
int arr[] = {5, 2, 8, 1, 9};
sort_int_array(arr, 5);

// Verify sorted
assert(arr[0] == 1);
assert(arr[1] == 2);
assert(arr[2] == 5);
assert(arr[3] == 8);
assert(arr[4] == 9);

// Verify ascending order
for (int i = 0; i < 4; i++)
    assert(arr[i] <= arr[i + 1]);
```

### Test 2: Edge Cases

```c
// Empty
int arr1[0];
sort_int_array(arr1, 0);  // Should not crash

// Single element
int arr2[] = {42};
sort_int_array(arr2, 1);
assert(arr2[0] == 42);

// Two elements
int arr3[] = {5, 3};
sort_int_array(arr3, 2);
assert(arr3[0] == 3 && arr3[1] == 5);
```

### Test 3: Already Sorted

```c
int arr[] = {1, 2, 3, 4, 5};
sort_int_array(arr, 5);

// Should remain unchanged
assert(arr[0] == 1);
assert(arr[1] == 2);
assert(arr[2] == 3);
assert(arr[3] == 4);
assert(arr[4] == 5);
```

### Test 4: Reverse Sorted

```c
int arr[] = {5, 4, 3, 2, 1};
sort_int_array(arr, 5);

// Should be fully reversed
assert(arr[0] == 1);
assert(arr[1] == 2);
assert(arr[2] == 3);
assert(arr[3] == 4);
assert(arr[4] == 5);
```

### Test 5: Duplicates

```c
int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
sort_int_array(arr, 9);

// Verify sorted with duplicates
int expected[] = {1, 1, 2, 3, 4, 5, 5, 6, 9};
for (int i = 0; i < 9; i++)
    assert(arr[i] == expected[i]);
```

### Test 6: Negative Numbers

```c
int arr[] = {5, -10, 0, -5, 3};
sort_int_array(arr, 5);

int expected[] = {-10, -5, 0, 3, 5};
for (int i = 0; i < 5; i++)
    assert(arr[i] == expected[i]);
```

### Test 7: Large Array

```c
int *arr = create_random_array(500);
sort_int_array(arr, 500);

// Verify sorted
for (int i = 0; i < 499; i++)
    assert(arr[i] <= arr[i + 1]);

free(arr);
```

---

## Summary

**What sort_int_array Does:**
1. Sorts integer array in ascending order (smallest to largest)
2. Uses selection sort (or bubble sort)
3. Sorts in place (modifies original array)
4. O(n²) time, O(1) space

**Key Characteristics:**
- ✅ Simple, straightforward algorithm
- ✅ In-place sorting (no extra memory)
- ✅ Works for any integer values
- ✅ Handles duplicates and negatives
- ❌ O(n²) not optimal for large arrays

**Critical Uses:**
- Sort copied stack values for ranking
- Create reference for index assignment
- Enable position-based ranking
- Foundation of index normalization

**Remember:**
- Ascending order (smallest first)
- In-place modification
- O(n²) acceptable for push_swap
- Simple > optimal for this use case
- Array must be allocated before calling

**Algorithm Choice:**
```
Selection Sort: Fewer swaps, more comparisons
Bubble Sort: More swaps, early termination possible
Quick Sort: O(n log n) but complex
Merge Sort: O(n log n) but O(n) space

For push_swap: Selection or bubble sort preferred
Simplicity and in-place sorting prioritized ✅
```

---

## Location in Project

**File:** `srcs/sort_utils.c` or `srcs/array_utils.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 5 (Index Normalization)

---

## Related Functions

- [assign_index](assign_index.md) - Main caller of this function
- [copy_values_to_array](copy_values_to_array.md) - Prepares array for sorting
- [get_index_position](get_index_position.md) - Uses sorted array for search

---

*Simple sorting enables sophisticated normalization - don't underestimate the power of basic algorithms done right!*
