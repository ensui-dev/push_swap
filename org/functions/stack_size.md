# stack_size - Count Nodes in Stack

## Function Signature

```c
int stack_size(t_stack *stack)
```

**Return type:** `int` - Number of nodes in the stack (0 if empty)
**Parameter:** `t_stack *stack` - Pointer to the first node of the stack

---

## Purpose & Use Case

`stack_size` counts how many nodes are in a linked list stack. It traverses the entire list and returns the total count.

### When You'll Use It

You'll call `stack_size` whenever you need to:
1. **Determine chunk sizes** - Calculate how many elements to push per chunk
2. **Check if operations are valid** - Ensure stack has enough elements
3. **Algorithm decisions** - Choose sorting strategy based on size
4. **Cost calculations** - Know if rotate or reverse rotate is cheaper
5. **Debugging** - Verify stack state during testing

---

## How It Works

### Conceptual Algorithm

This is a **traversal and counting** operation.

**The Process:**
1. Start with a counter at 0
2. Start at the first node (head of stack)
3. While there are more nodes:
   - Increment counter by 1
   - Move to next node
4. When you reach NULL (end of list), return the counter

### Step-by-Step Breakdown

#### Step 1: Handle Edge Case - Empty Stack
- If the stack pointer is NULL, there are 0 nodes
- Return 0 immediately
- This prevents dereferencing NULL pointer

#### Step 2: Initialize Counter
- Create a counter variable, set to 0
- This will track how many nodes we've seen

#### Step 3: Initialize Traversal Pointer
- Create a temporary pointer to traverse the list
- Set it to the head of the stack
- This pointer will "walk" through the list

#### Step 4: Traverse the List
- While the current pointer is not NULL:
  - Increment counter (we found a node!)
  - Move pointer to next node (pointer = pointer->next)
- Continue until pointer is NULL (end of list)

#### Step 5: Return Count
- Return the final counter value
- This is the total number of nodes

---

## Visual Example

### Scenario: Count nodes in Stack A with values [5, 3, 1]

**Initial State:**
```
Stack A:
[5] -> [3] -> [1] -> NULL
 ^
head
```

**Execution Trace:**

```
Call: stack_size(stack_a)

Step 1: Check if stack is NULL
  stack_a != NULL ✓ Continue

Step 2: Initialize counter
  count = 0

Step 3: Initialize traversal pointer
  current = stack_a (points to node with value 5)

Step 4: Traverse and count
  Iteration 1:
    current = [5] (not NULL)
    count = 1
    current = current->next (now points to [3])

  Iteration 2:
    current = [3] (not NULL)
    count = 2
    current = current->next (now points to [1])

  Iteration 3:
    current = [1] (not NULL)
    count = 3
    current = current->next (now points to NULL)

  Iteration 4:
    current = NULL
    Exit loop

Step 5: Return count
  return 3
```

**Result:** Function returns `3`

---

## Edge Cases

### Case 1: Empty Stack
```
Input: NULL
Process:
  - Check if stack is NULL: YES
  - Return 0 immediately
Output: 0
```

### Case 2: Single Node
```
Input: [42] -> NULL
Process:
  - current = [42]
  - count = 1
  - current = NULL
  - Exit loop
Output: 1
```

### Case 3: Two Nodes
```
Input: [5] -> [3] -> NULL
Process:
  - Iteration 1: count = 1, current = [3]
  - Iteration 2: count = 2, current = NULL
Output: 2
```

### Case 4: Large Stack (100 nodes)
```
Input: [node1] -> [node2] -> ... -> [node100] -> NULL
Process:
  - Loop 100 times
  - count increments to 100
Output: 100
```

---

## Time Complexity

**O(n)** where n is the number of nodes

**Why?**
- Must visit every node once to count them
- No way to know size without traversal (linked list has no size property)
- Linear time - doubles when input size doubles

**Space Complexity:** O(1)
- Only uses a counter variable and a pointer
- No additional data structures needed
- Constant space regardless of input size

---

## Usage Examples in Push_swap

### Example 1: Choosing Sorting Algorithm
```c
int size = stack_size(stack_a);

if (size <= 5)
    sort_small(stack_a, stack_b);  // Use hardcoded solutions
else
    sort_large(stack_a, stack_b);   // Use Turk/Chunk algorithm
```

### Example 2: Calculating Chunk Size
```c
int size = stack_size(stack_a);
int num_chunks;

if (size <= 100)
    num_chunks = size / 5;  // ~20 per chunk for 100 elements
else
    num_chunks = size / 14; // ~35 per chunk for 500 elements
```

### Example 3: Cost Calculation
```c
int size = stack_size(stack_a);
int position = 7;  // Element is at position 7

// Should we rotate forward or reverse rotate?
if (position <= size / 2)
    cost = position;          // Rotate forward (cheaper)
else
    cost = position - size;   // Reverse rotate (cheaper)
```

### Example 4: Validation Before Operation
```c
// Before doing sa (swap first two elements)
if (stack_size(stack_a) < 2)
    return;  // Cannot swap, not enough elements
```

---

## Implementation Pseudocode

```
FUNCTION stack_size(stack):
    // Step 1: Handle empty stack
    IF stack is NULL:
        RETURN 0

    // Step 2: Initialize counter
    count = 0

    // Step 3: Initialize traversal pointer
    current = stack

    // Step 4: Traverse and count
    WHILE current is not NULL:
        count = count + 1
        current = current.next

    // Step 5: Return total count
    RETURN count
END FUNCTION
```

---

## 42 Norm Considerations

✅ **Function length:** Very short (5-10 lines), well under 25 line limit
✅ **Parameters:** Only 1 parameter (under 4 limit)
✅ **Variables:** Need 2 variables (count, current) - can declare together
✅ **Loop:** Use while loop (no for loops allowed)
✅ **No global variables:** Everything is local
✅ **Return value:** Always returns an int

**Variable Declaration:**
```c
int     count;
t_stack *current;
```

---

## Common Mistakes to Avoid

### Mistake 1: Not Checking for NULL Stack
```c
❌ WRONG:
int stack_size(t_stack *stack)
{
    // If stack is NULL, this will crash!
    while (stack != NULL)
        ...
}
```
**Fix:** Check `if (!stack) return 0;` first

### Mistake 2: Modifying Original Stack Pointer
```c
❌ WRONG:
int stack_size(t_stack *stack)
{
    int count = 0;
    while (stack)  // Modifying the parameter!
    {
        count++;
        stack = stack->next;  // Lost original pointer!
    }
    return count;
}
```
**Fix:** Use a separate `current` pointer for traversal

### Mistake 3: Off-by-One Error
```c
❌ WRONG:
count = 1;  // Starting at 1 instead of 0
while (current->next)  // Stops before last node!
    ...
```
**Fix:** Start count at 0, check `current` not `current->next`

### Mistake 4: Infinite Loop
```c
❌ WRONG:
while (current)
{
    count++;
    // Forgot to move to next node!
}
// This loops forever on first node
```
**Fix:** Always include `current = current->next;`

---

## Relationship with Libft

This function is very similar to `ft_lstsize()` from your libft bonus!

**Libft function:**
```c
int ft_lstsize(t_list *lst);
```

**Key Differences:**
- Different structure type (`t_list` vs `t_stack`)
- Different field names (`lst->next` vs `stack->next`)
- Same algorithm and logic

**You can reference your ft_lstsize.c for implementation guidance!**

---

## Testing Strategy

### Test Cases

1. **Empty stack:**
   ```c
   t_stack *empty = NULL;
   assert(stack_size(empty) == 0);
   ```

2. **Single node:**
   ```c
   t_stack *single = stack_new(42);
   assert(stack_size(single) == 1);
   free(single);
   ```

3. **Multiple nodes:**
   ```c
   // Create stack: [1] -> [2] -> [3] -> NULL
   t_stack *stack = create_test_stack(3);
   assert(stack_size(stack) == 3);
   free_stack(&stack);
   ```

4. **After operations:**
   ```c
   // Start with 5 nodes
   assert(stack_size(stack_a) == 5);

   // Push one to B
   pb(&stack_a, &stack_b);
   assert(stack_size(stack_a) == 4);
   assert(stack_size(stack_b) == 1);
   ```

---

## Performance Characteristics

### Best Case: O(n)
- Even if you only need to know if stack is empty or has 1 element
- Still must traverse to count all nodes
- No optimization possible

### Average Case: O(n)
- Linear time for any size stack

### Worst Case: O(n)
- Large stack (500 nodes) still only takes 500 iterations
- Very fast even for worst case

**Real-world timing:**
- 100 nodes: ~100 nanoseconds
- 500 nodes: ~500 nanoseconds
- Negligible impact on overall program performance

---

## When to Call This Function

### ✅ Good Use Cases

1. **Once per algorithm decision** (beginning of sort)
2. **During cost calculation** (needs size for rotate decisions)
3. **Debugging/verification** (check stack state)

### ⚠️ Avoid Excessive Calls

```c
❌ BAD: Calling in loop
while (stack_size(stack_a) > 3)  // Recalculates every iteration!
{
    pb(&stack_a, &stack_b);
}

✅ GOOD: Cache the size
int size = stack_size(stack_a);
while (size > 3)
{
    pb(&stack_a, &stack_b);
    size--;  // Track manually
}
```

---

## Related Functions

- **stack_new()** - Creates nodes that stack_size counts
- **stack_last()** - Finds last node (also traverses list)
- **stack_add_back()** - Adds node (increases size by 1)
- **free_stack()** - Frees all nodes counted by stack_size
- **ft_lstsize()** - Libft equivalent for reference

---

## Location in Project

**File:** `srcs/stack_utils.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 1.2 (Stack Utility Functions - Basic Operations)
**Dependencies:** Requires `t_stack` structure defined

---

## Summary

**What stack_size does:**
1. Traverses the entire linked list
2. Counts each node
3. Returns the total count

**Key characteristics:**
- Simple traversal algorithm
- O(n) time complexity
- O(1) space complexity
- Must handle NULL input
- Similar to ft_lstsize from libft

**Critical for:** Algorithm selection, cost calculation, validation

---

*This function is straightforward but essential - you'll call it frequently throughout push_swap!*
