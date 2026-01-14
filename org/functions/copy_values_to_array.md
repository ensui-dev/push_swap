# copy_values_to_array - Copy Stack Values to Integer Array

## Function Signature

```c
void copy_values_to_array(t_stack *stack, int *arr, int size)
```

**Return type:** `void` - Modifies array in place
**Parameters:**
- `t_stack *stack` - Pointer to the head of the stack
- `int *arr` - Pointer to pre-allocated integer array
- `int size` - Number of elements to copy

---

## Purpose & Use Case

`copy_values_to_array` is a **data transfer function** that traverses a linked list stack and copies all node values into a contiguous integer array. This conversion is essential for index normalization, as arrays can be efficiently sorted while preserving the original stack structure.

### When You'll Use It

You'll call `copy_values_to_array` when you need to:
1. **Prepare for sorting** - Copy values before sorting for index assignment
2. **Convert data structures** - Transform linked list to array
3. **Enable efficient operations** - Arrays allow O(1) access and efficient sorting
4. **Preserve original structure** - Copy without modifying stack
5. **Index normalization setup** - First step in `assign_index` process

### Why Array Conversion Matters

**Linked list vs Array for sorting:**
```
Stack (Linked List):
[5] -> [8] -> [2] -> [9] -> [1] -> NULL
❌ Random access: O(n)
❌ Can't use efficient sorting algorithms directly
❌ Cache-unfriendly (scattered in memory)
✅ Easy insertion/deletion

Array:
[5, 8, 2, 9, 1]
✅ Random access: O(1)
✅ Can use quicksort, mergesort, etc.
✅ Cache-friendly (contiguous memory)
❌ Fixed size

Solution: Copy to array, sort, then use for indexing!
```

### Real-World Analogy

**Copying names from chain of people to a list:**
```
People standing in line (linked list):
Person A → Person B → Person C → Person D

Copy to clipboard (array):
1. Person A's name
2. Person B's name
3. Person C's name
4. Person D's name

Now you can:
- Sort the list alphabetically
- Quick lookup by position
- Work with data without moving people

copy_values_to_array does this for stack nodes!
```

---

## Deep Dive: How It Works

### The Sequential Copy Algorithm

**Concept:**
- Start at the head of the stack
- For each node, copy its value to the next array position
- Move to the next node
- Repeat until all values copied or size reached

### Algorithm Visualization

**Stack Example:** [42, -5, 1000, 3]

```
Initial State:
Stack: [42] -> [-5] -> [1000] -> [3] -> NULL
Array: [?, ?, ?, ?]  ← Uninitialized
       0   1   2   3

Step 1: Copy first value
current = [42]
i = 0
arr[0] = current->value = 42
Array: [42, ?, ?, ?]
Move to next: current = current->next

Step 2: Copy second value
current = [-5]
i = 1
arr[1] = current->value = -5
Array: [42, -5, ?, ?]
Move to next: current = current->next

Step 3: Copy third value
current = [1000]
i = 2
arr[2] = current->value = 1000
Array: [42, -5, 1000, ?]
Move to next: current = current->next

Step 4: Copy fourth value
current = [3]
i = 3
arr[3] = current->value = 3
Array: [42, -5, 1000, 3] ✅
Move to next: current = current->next = NULL

Step 5: Loop exits
i = 4 (i < size? 4 < 4? No)
OR current = NULL

Final Result:
Array: [42, -5, 1000, 3] ✅ All values copied!
```

### Memory Layout Visualization

```
Before copy_values_to_array:

Stack (scattered in heap):
┌─────────┐     ┌─────────┐     ┌─────────┐
│ value:42│ →   │ value:-5│ →   │value:1000│ → ...
│ next: ─→│     │ next: ─→│     │ next: ─→│
└─────────┘     └─────────┘     └─────────┘
Memory addr:    Memory addr:    Memory addr:
0x1000         0x2500          0x1A00
(scattered, cache-unfriendly)

Array (contiguous in memory):
┌───┬───┬───┬───┐
│ ? │ ? │ ? │ ? │
└───┴───┴───┴───┘
0x5000
(allocated but uninitialized)

After copy_values_to_array:

Stack (unchanged):
┌─────────┐     ┌─────────┐     ┌─────────┐
│ value:42│ →   │ value:-5│ →   │value:1000│ → ...
│ next: ─→│     │ next: ─→│     │ next: ─→│
└─────────┘     └─────────┘     └─────────┘

Array (filled, contiguous):
┌────┬────┬──────┬───┐
│ 42 │ -5 │ 1000 │ 3 │
└────┴────┴──────┴───┘
0x5000  0x5004  0x5008  0x500C
(contiguous, cache-friendly!)
```

---

## Step-by-Step Implementation

### Step 1: Initialize Array Index

**Start at beginning:**
```c
int i = 0;
```

**Why start at 0:**
```
Array is 0-indexed
First element at arr[0]
Sequential filling from left to right
```

### Step 2: Loop Through Stack and Array

**Dual condition check:**
```c
while (i < size && stack)
{
    // Copy and advance
}
```

**Why both conditions:**
```
i < size:
- Prevents array overflow
- Ensures we don't write past allocated memory
- Critical for safety

stack:
- Ensures node exists
- Prevents NULL pointer dereference
- Handles cases where size > actual stack size

Both needed for robustness:
- Normal case: stack reaches NULL when i == size
- Edge case: stack shorter than size → stop early
- Edge case: size smaller than stack → copy only size elements
```

### Step 3: Copy Value to Array

**Transfer data:**
```c
arr[i] = stack->value;
```

**Direct assignment:**
```
Copy the integer value (not the node)
arr[i] gets the value field
Stack node structure unchanged
```

### Step 4: Advance Both Pointers

**Move to next positions:**
```c
stack = stack->next;
i++;
```

**Synchronous advancement:**
```
Stack pointer: Move to next node
Array index: Move to next position
Both move in lockstep
```

---

## Complete Algorithm Pseudocode

```
FUNCTION copy_values_to_array(stack, arr, size):
    // Step 1: Initialize array index
    i = 0

    // Step 2: Loop through stack and array
    WHILE i < size AND stack is not NULL:
        // Step 3: Copy current value
        arr[i] = stack.value

        // Step 4: Advance both pointers
        stack = stack.next
        i = i + 1

    // Done! Values copied to array
END FUNCTION
```

---

## Visual Execution Trace

### Example: Copying [42, -5, 1000, 3]

```
Initial State:
Stack: [42] -> [-5] -> [1000] -> [3] -> NULL
Array: [?, ?, ?, ?]
Size: 4

Call: copy_values_to_array(stack, arr, 4)

Step 1: Initialize
i = 0

Step 2-4: Loop iteration 1
Check: i < size? (0 < 4? Yes)
Check: stack? (Yes, points to [42])
Copy: arr[0] = stack->value = 42
Array: [42, ?, ?, ?]
Advance: stack = stack->next → [-5]
Advance: i++ → i = 1

Step 2-4: Loop iteration 2
Check: i < size? (1 < 4? Yes)
Check: stack? (Yes, points to [-5])
Copy: arr[1] = stack->value = -5
Array: [42, -5, ?, ?]
Advance: stack = stack->next → [1000]
Advance: i++ → i = 2

Step 2-4: Loop iteration 3
Check: i < size? (2 < 4? Yes)
Check: stack? (Yes, points to [1000])
Copy: arr[2] = stack->value = 1000
Array: [42, -5, 1000, ?]
Advance: stack = stack->next → [3]
Advance: i++ → i = 3

Step 2-4: Loop iteration 4
Check: i < size? (3 < 4? Yes)
Check: stack? (Yes, points to [3])
Copy: arr[3] = stack->value = 3
Array: [42, -5, 1000, 3] ✅
Advance: stack = stack->next → NULL
Advance: i++ → i = 4

Step 2: Loop check
Check: i < size? (4 < 4? No) ← Loop exits
Check: stack? (NULL)

Final State:
Array: [42, -5, 1000, 3] ✅ Fully copied!
Stack: Unchanged, still [42] -> [-5] -> [1000] -> [3] -> NULL
```

---

## Edge Cases

### Case 1: Empty Stack

```c
t_stack *stack = NULL;
int arr[10];

copy_values_to_array(stack, arr, 10);

// Loop never executes (stack is NULL)
// Array unchanged (still uninitialized)
// No crash ✅
```

### Case 2: Single Element

```c
// Stack: [42] -> NULL
int arr[1];

copy_values_to_array(stack, arr, 1);

// Result:
// arr[0] = 42
// Array: [42] ✅
```

### Case 3: Size Larger Than Stack

```c
// Stack: [5, 8] -> NULL (only 2 elements)
int arr[5];

copy_values_to_array(stack, arr, 5);

// Loop stops when stack = NULL after 2 copies
// Result:
// arr[0] = 5
// arr[1] = 8
// arr[2], arr[3], arr[4] = uninitialized
// Copied 2 elements, not 5
```

### Case 4: Size Smaller Than Stack

```c
// Stack: [5, 8, 2, 9] -> NULL (4 elements)
int arr[2];

copy_values_to_array(stack, arr, 2);

// Loop stops when i = 2
// Result:
// arr[0] = 5
// arr[1] = 8
// Only copied first 2 elements
// Stack still has [2, 9] but not copied
```

### Case 5: Exact Size Match

```c
// Stack: [5, 8, 2] -> NULL (3 elements)
int arr[3];

copy_values_to_array(stack, arr, 3);

// Perfect match
// Result:
// arr[0] = 5
// arr[1] = 8
// arr[2] = 2
// All elements copied ✅
```

### Case 6: Negative Values

```c
// Stack: [-5, 0, -100, 42]
int arr[4];

copy_values_to_array(stack, arr, 4);

// Result:
// arr = [-5, 0, -100, 42]
// Handles negatives correctly ✅
```

### Case 7: Large Stack

```c
// Stack: 500 elements
int *arr = malloc(sizeof(int) * 500);

copy_values_to_array(stack, arr, 500);

// All 500 values copied
// Linear time O(500)
// ✅ Scales correctly
```

---

## Time & Space Complexity

### Time Complexity: **O(n)** - Linear Time

**Single pass through stack:**
```
n = number of elements to copy (min(size, stack_size))

For each element:
- Access stack->value: O(1)
- Assign to arr[i]: O(1)
- Advance pointers: O(1)

Total: n × O(1) = O(n)

Examples:
3 elements: 3 operations
100 elements: 100 operations
500 elements: 500 operations

Linear growth ✅
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
Variables:
- int i (4 bytes)
- t_stack *stack (8 bytes, local copy of pointer)

Total: ~12 bytes, regardless of stack/array size

Array is passed in (already allocated)
No additional allocations
No recursion
No temporary storage

Space = O(1) ✅
```

**Note:** The array itself is O(n) space, but it's allocated by the caller, not by this function.

---

## Relationship with Other Functions

### Called by assign_index

```c
void assign_index(t_stack *stack)
{
    int size = stack_size(stack);
    int *values = malloc(sizeof(int) * size);

    // Copy stack values to array
    copy_values_to_array(stack, values, size);  // ← Used here

    // Sort array
    sort_int_array(values, size);

    // Assign indices based on sorted positions
    // ...
}
```

### Works with Malloc

```c
// Caller must allocate array first
int size = stack_size(stack);
int *arr = malloc(sizeof(int) * size);  // ← Allocate

if (arr)
{
    copy_values_to_array(stack, arr, size);  // ← Copy
    // Use array...
    free(arr);  // ← Free
}
```

### Prepares for Sort

```c
// Typical usage pattern
int *values = malloc(sizeof(int) * size);

copy_values_to_array(stack, values, size);  // 1. Copy
sort_int_array(values, size);                // 2. Sort
// Use sorted values for indexing             // 3. Use

free(values);  // 4. Clean up
```

---

## Integration with Push_swap

### Scenario: Index Normalization

```c
// Input: ./push_swap 42 -5 1000 3

// Stack A: [42] -> [-5] -> [1000] -> [3] -> NULL

// Step 1: Allocate array
int size = stack_size(stack_a);  // 4
int *values = malloc(sizeof(int) * size);

// Step 2: Copy values
copy_values_to_array(stack_a, values, size);
// Array: [42, -5, 1000, 3]

// Step 3: Sort array
sort_int_array(values, size);
// Array: [-5, 3, 42, 1000]

// Step 4: Assign indices based on sorted positions
// 42 at position 2 → index 2
// -5 at position 0 → index 0
// 1000 at position 3 → index 3
// 3 at position 1 → index 1

// Step 5: Clean up
free(values);
```

---

## 42 Norm Considerations

### Function Structure

```c
void	copy_values_to_array(t_stack *stack, int *arr, int size)
{
	int	i;

	i = 0;
	while (i < size && stack)
	{
		arr[i] = stack->value;
		stack = stack->next;
		i++;
	}
}
```

**Norm compliance:**
- ✅ Under 25 lines
- ✅ Single responsibility: copies values
- ✅ Only 1 variable (i)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Simple, clear logic

---

## Common Mistakes

### Mistake 1: Not Checking Stack for NULL

```c
// ❌ WRONG
void copy_values_to_array(t_stack *stack, int *arr, int size)
{
    int i = 0;
    while (i < size)  // Only checks size, not stack
    {
        arr[i] = stack->value;  // If stack is NULL, CRASH!
        stack = stack->next;
        i++;
    }
}
```

**✅ Correct:**
```c
while (i < size && stack)  // Check both conditions
```

### Mistake 2: Array Overflow

```c
// ❌ WRONG
while (stack)  // No size check!
{
    arr[i] = stack->value;  // Can write past array end!
    stack = stack->next;
    i++;
}
```

**✅ Correct:**
```c
while (i < size && stack)  // Bounds checking
```

### Mistake 3: Not Advancing Stack Pointer

```c
// ❌ WRONG - Infinite loop!
while (i < size && stack)
{
    arr[i] = stack->value;
    i++;
    // Forgot: stack = stack->next;
}
// stack never changes, loops forever copying same value!
```

**✅ Correct:**
```c
stack = stack->next;  // CRITICAL!
```

### Mistake 4: Copying Wrong Field

```c
// ❌ WRONG
arr[i] = stack->index;  // Copying index, not value!
```

**✅ Correct:**
```c
arr[i] = stack->value;  // Copy value field
```

### Mistake 5: Not Checking Array for NULL

```c
// ❌ WRONG - arr could be NULL if malloc failed
void copy_values_to_array(t_stack *stack, int *arr, int size)
{
    int i = 0;
    while (i < size && stack)
    {
        arr[i] = stack->value;  // If arr is NULL, CRASH!
        // ...
    }
}
```

**✅ Better:**
```c
void copy_values_to_array(t_stack *stack, int *arr, int size)
{
    int i;

    if (!arr)  // Check for NULL array
        return;
    i = 0;
    while (i < size && stack)
    {
        arr[i] = stack->value;
        stack = stack->next;
        i++;
    }
}
```

---

## Testing Strategy

### Test 1: Basic Copy

```c
t_stack *stack = create_stack([5, 8, 2, 9]);
int arr[4];

copy_values_to_array(stack, arr, 4);

// Verify
assert(arr[0] == 5);
assert(arr[1] == 8);
assert(arr[2] == 2);
assert(arr[3] == 9);
```

### Test 2: Edge Cases

```c
// Empty stack
copy_values_to_array(NULL, arr, 10);
// Should not crash

// Single element
stack = create_stack([42]);
int arr1[1];
copy_values_to_array(stack, arr1, 1);
assert(arr1[0] == 42);

// Two elements
stack = create_stack([5, 8]);
int arr2[2];
copy_values_to_array(stack, arr2, 2);
assert(arr2[0] == 5);
assert(arr2[1] == 8);
```

### Test 3: Size Mismatches

```c
// Size larger than stack
stack = create_stack([5, 8]);  // 2 elements
int arr[5];
copy_values_to_array(stack, arr, 5);
assert(arr[0] == 5);
assert(arr[1] == 8);
// arr[2], arr[3], arr[4] uninitialized

// Size smaller than stack
stack = create_stack([5, 8, 2, 9]);  // 4 elements
int arr2[2];
copy_values_to_array(stack, arr2, 2);
assert(arr2[0] == 5);
assert(arr2[1] == 8);
// Only first 2 copied
```

### Test 4: Negative Values

```c
stack = create_stack([-5, 0, -100, 42]);
int arr[4];

copy_values_to_array(stack, arr, 4);

assert(arr[0] == -5);
assert(arr[1] == 0);
assert(arr[2] == -100);
assert(arr[3] == 42);
```

### Test 5: Large Stack

```c
t_stack *stack = create_random_stack(500);
int *arr = malloc(sizeof(int) * 500);

copy_values_to_array(stack, arr, 500);

// Verify all 500 values copied correctly
t_stack *temp = stack;
for (int i = 0; i < 500; i++)
{
    assert(arr[i] == temp->value);
    temp = temp->next;
}

free(arr);
```

### Test 6: Stack Unchanged

```c
stack = create_stack([5, 8, 2]);
int arr[3];

// Copy values
copy_values_to_array(stack, arr, 3);

// Verify stack unchanged
assert(stack->value == 5);
assert(stack->next->value == 8);
assert(stack->next->next->value == 2);
```

---

## Summary

**What copy_values_to_array Does:**
1. Traverses stack from head to tail
2. Copies each node's value into array sequentially
3. Stops when size reached or stack ends
4. Leaves original stack unchanged

**Key Characteristics:**
- ✅ Simple sequential copy
- ✅ O(n) time, O(1) space
- ✅ Non-destructive (stack preserved)
- ✅ Bounds-safe (checks size)
- ✅ Handles mismatched sizes

**Critical Uses:**
- Prerequisite for sorting in assign_index
- Converts linked list to array
- Enables efficient sorting algorithms
- Preserves stack structure

**Remember:**
- Check both size and stack for NULL
- Array must be pre-allocated
- Copies values, not nodes
- Original stack unchanged
- Essential for index normalization

**Usage Pattern:**
```
1. Allocate array (malloc)
2. Copy values (copy_values_to_array)
3. Process array (sort, search, etc.)
4. Use results with stack
5. Free array (free)
```

---

## Location in Project

**File:** `srcs/index_utils.c` or `srcs/array_utils.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 5 (Index Normalization)

---

## Related Functions

- [assign_index](assign_index.md) - Main caller of this function
- [sort_int_array](sort_int_array.md) - Sorts copied array
- [get_index_position](get_index_position.md) - Searches sorted array
- [stack_size](stack_size.md) - Determines array size needed

---

*Simple data transfer, but essential - converting linked list to array unlocks efficient sorting for index normalization!*
