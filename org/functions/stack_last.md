# stack_last - Find Last Node in Stack

## Function Signature

```c
t_stack *stack_last(t_stack *stack)
```

**Return type:** `t_stack *` - Pointer to the last node (or NULL if stack is empty)
**Parameter:** `t_stack *stack` - Pointer to the first node of the stack

---

## Purpose & Use Case

`stack_last` traverses a linked list to find and return a pointer to the last node (the one whose `next` pointer is NULL).

### When You'll Use It

You'll call `stack_last` whenever you need to:
1. **Add nodes to the end** - `stack_add_back()` needs the last node
2. **Reverse rotate operations** - rra/rrb move last element to front
3. **Check stack state** - Verify end of stack during debugging
4. **Link nodes together** - Connect new node after current last node

---

## How It Works

### Conceptual Algorithm

This is a **traversal to end** operation.

**The Process:**
1. Start at the first node (head of stack)
2. While the current node has a next node:
   - Move to the next node
3. When current node's `next` is NULL, you've found the last node
4. Return pointer to that last node

### Step-by-Step Breakdown

#### Step 1: Handle Edge Case - Empty Stack
- If the stack pointer is NULL, there is no last node
- Return NULL immediately
- Prevents dereferencing NULL pointer

#### Step 2: Initialize Traversal Pointer
- Create a pointer to traverse the list
- Set it to point to the head (first node)
- This pointer will "walk" to the end

#### Step 3: Traverse to End
- While current node has a next node (current->next != NULL):
  - Move to next node (current = current->next)
- Stop when current->next is NULL
- Current now points to the last node

#### Step 4: Return Last Node
- Return the pointer to the last node
- Caller can now access or modify this node

---

## Visual Example

### Scenario: Find last node in Stack A with values [5, 3, 1]

**Initial State:**
```
Stack A:
[5] -> [3] -> [1] -> NULL
 ^             ^
head          last
```

**Execution Trace:**

```
Call: stack_last(stack_a)

Step 1: Check if stack is NULL
  stack_a != NULL ✓ Continue

Step 2: Initialize traversal pointer
  current = stack_a (points to node [5])

Step 3: Traverse to end
  Iteration 1:
    current = [5]
    current->next = [3] (not NULL)
    current = [3]

  Iteration 2:
    current = [3]
    current->next = [1] (not NULL)
    current = [1]

  Iteration 3:
    current = [1]
    current->next = NULL ← STOP HERE
    Exit loop

Step 4: Return last node
  return current (pointer to node [1])
```

**Result:** Function returns pointer to node containing value 1

---

## Edge Cases

### Case 1: Empty Stack
```
Input: NULL
Process:
  - Check if stack is NULL: YES
  - Return NULL immediately
Output: NULL
```

### Case 2: Single Node
```
Input: [42] -> NULL
       ^
      head & last

Process:
  - current = [42]
  - current->next = NULL (already at end!)
  - No iterations needed
Output: Pointer to [42]
```

### Case 3: Two Nodes
```
Input: [5] -> [3] -> NULL
              ^
             last

Process:
  - current starts at [5]
  - Iteration 1: move to [3]
  - [3]->next is NULL, stop
Output: Pointer to [3]
```

### Case 4: Large Stack
```
Input: [1] -> [2] -> [3] -> ... -> [500] -> NULL
                                    ^
                                   last

Process:
  - Traverse through all 500 nodes
  - Stop at last node [500]
Output: Pointer to [500]
```

---

## Time Complexity

**O(n)** where n is the number of nodes

**Why?**
- Must traverse from head to tail
- Linked list has no direct access to last element
- Must visit each node until finding one with next == NULL
- Linear time - doubles when input size doubles

**Space Complexity:** O(1)
- Only uses a single pointer variable
- No additional data structures
- Constant space regardless of input size

---

## Usage Examples in Push_swap

### Example 1: Adding Node to End of Stack
```c
// In stack_add_back() function
t_stack *last = stack_last(*stack);

if (last == NULL)
    *stack = new_node;  // Stack was empty
else
    last->next = new_node;  // Link new node to end
```

### Example 2: Reverse Rotate Operation (rra)
```c
// Reverse rotate: move last element to front
t_stack *last = stack_last(stack_a);

if (!last || !last->prev)  // Can't rra with <2 elements
    return;

// Detach last node and move to front
// (actual implementation needs to find second-to-last too)
```

### Example 3: Debugging - Print Stack
```c
void print_stack(t_stack *stack)
{
    t_stack *last = stack_last(stack);
    t_stack *current = stack;

    while (current)
    {
        printf("%d", current->value);
        if (current != last)
            printf(" -> ");
        current = current->next;
    }
    printf(" -> NULL\n");
}
```

### Example 4: Verification
```c
// Verify stack integrity
t_stack *last = stack_last(stack);

if (last && last->next != NULL)
{
    // ERROR: Last node's next should be NULL!
    error_exit();
}
```

---

## Implementation Pseudocode

```
FUNCTION stack_last(stack):
    // Step 1: Handle empty stack
    IF stack is NULL:
        RETURN NULL

    // Step 2: Initialize traversal pointer
    current = stack

    // Step 3: Traverse to end
    WHILE current->next is not NULL:
        current = current->next

    // Step 4: Return last node
    RETURN current
END FUNCTION
```

---

## 42 Norm Considerations

✅ **Function length:** Very short (4-8 lines), well under 25 line limit
✅ **Parameters:** Only 1 parameter (under 4 limit)
✅ **Variables:** Need 1 variable (current pointer)
✅ **Loop:** Use while loop (no for loops allowed)
✅ **No global variables:** Everything is local
✅ **Return value:** Always returns a pointer (or NULL)

**Variable Declaration:**
```c
t_stack *current;
```

---

## Common Mistakes to Avoid

### Mistake 1: Not Checking for NULL Stack
```c
❌ WRONG:
t_stack *stack_last(t_stack *stack)
{
    // If stack is NULL, this crashes!
    while (stack->next != NULL)
        ...
}
```
**Fix:** Check `if (!stack) return NULL;` first

### Mistake 2: Checking Wrong Condition
```c
❌ WRONG:
while (current != NULL)  // Moves past last node!
    current = current->next;
return current;  // Returns NULL, not last node!
```
**Fix:** Check `while (current->next != NULL)`

### Mistake 3: Not Handling Single Node
```c
❌ WRONG:
if (stack->next == NULL)
    return NULL;  // Should return stack itself!

// Single node IS the last node!
```
**Fix:** Single node case works automatically with correct loop

### Mistake 4: Modifying Original Pointer
```c
❌ WRONG:
while (stack->next != NULL)
    stack = stack->next;  // Lost head pointer!
return stack;
```
**Fix:** Use separate `current` pointer for traversal

---

## Relationship with Libft

This function is very similar to `ft_lstlast()` from your libft bonus!

**Libft function:**
```c
t_list *ft_lstlast(t_list *lst);
```

**Key Differences:**
- Different structure type (`t_list` vs `t_stack`)
- Same algorithm and logic
- Same edge cases

**You can reference your ft_lstlast.c for implementation guidance!**

---

## Comparison with stack_size

Both functions traverse the list, but with different goals:

| Aspect | stack_size | stack_last |
|--------|-----------|-----------|
| **Purpose** | Count all nodes | Find last node |
| **Return** | Integer (count) | Pointer (last node) |
| **Loop condition** | `while (current)` | `while (current->next)` |
| **Tracks** | Counter variable | Just pointer |
| **Use case** | Algorithm decisions | Node linking |

---

## Testing Strategy

### Test Cases

1. **Empty stack:**
   ```c
   t_stack *empty = NULL;
   assert(stack_last(empty) == NULL);
   ```

2. **Single node:**
   ```c
   t_stack *single = stack_new(42);
   t_stack *last = stack_last(single);
   assert(last == single);  // Same node!
   assert(last->value == 42);
   assert(last->next == NULL);
   free(single);
   ```

3. **Two nodes:**
   ```c
   t_stack *first = stack_new(1);
   t_stack *second = stack_new(2);
   first->next = second;

   t_stack *last = stack_last(first);
   assert(last == second);
   assert(last->value == 2);
   assert(last->next == NULL);
   ```

4. **Multiple nodes:**
   ```c
   // Create: [1] -> [2] -> [3] -> NULL
   t_stack *stack = create_test_stack(3);
   t_stack *last = stack_last(stack);

   assert(last != stack);  // Not the first node
   assert(last->value == 3);  // Last value
   assert(last->next == NULL);  // Truly last
   ```

---

## Performance Characteristics

### Best Case: O(1)
- Single node: immediate return
- No traversal needed

### Average Case: O(n)
- Must traverse half to all nodes
- Depends on stack size

### Worst Case: O(n)
- Large stack requires full traversal
- Still very fast (500 nodes = 500 iterations)

**Real-world timing:**
- 1 node: ~10 nanoseconds
- 100 nodes: ~100 nanoseconds
- 500 nodes: ~500 nanoseconds
- Negligible impact on overall performance

---

## When to Call This Function

### ✅ Good Use Cases

1. **In stack_add_back()** - Need last node to append
2. **In reverse rotate operations** - Need to detach last
3. **During verification** - Check list integrity

### ⚠️ Avoid Excessive Calls

```c
❌ BAD: Calling in loop
for (int i = 0; i < n; i++)
{
    t_stack *last = stack_last(stack);  // O(n) each time!
    // Do something with last
}
// Total: O(n²) time!

✅ GOOD: Cache if stack doesn't change
t_stack *last = stack_last(stack);
for (int i = 0; i < n; i++)
{
    // Use cached last pointer
}
```

**Note:** If you're adding nodes to the end, the last node changes, so you must call stack_last again.

---

## Related Functions

- **stack_new()** - Creates nodes that become last
- **stack_size()** - Also traverses list (counts instead)
- **stack_add_back()** - Uses stack_last to append nodes
- **rra/rrb** - Reverse rotate operations use last node
- **ft_lstlast()** - Libft equivalent for reference

---

## Location in Project

**File:** `srcs/stack_utils.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 1.2 (Stack Utility Functions - Basic Operations)
**Dependencies:** Requires `t_stack` structure defined

---

## Summary

**What stack_last does:**
1. Traverses linked list from head
2. Finds node where `next == NULL`
3. Returns pointer to that node

**Key characteristics:**
- Simple traversal algorithm
- O(n) time complexity (O(1) for single node)
- O(1) space complexity
- Must handle NULL input
- Similar to ft_lstlast from libft

**Critical for:** Adding nodes to end, reverse rotate operations, list manipulation

---

*A simple but essential function - you'll use it mainly in stack_add_back and reverse rotate operations!*
