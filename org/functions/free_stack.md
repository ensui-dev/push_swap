# free_stack - Free Entire Stack Linked List

## Function Signature

```c
void free_stack(t_stack **stack)
```

**Return type:** `void` - No return value
**Parameter:** `t_stack **stack` - Pointer to stack pointer (allows setting to NULL)

---

## Purpose & Use Case

`free_stack` is a **memory cleanup function** that deallocates an entire stack linked list, freeing each node in sequence. This prevents memory leaks by properly cleaning up all dynamically allocated stack nodes.

### When You'll Use It

You'll call `free_stack` to:
1. **Clean up on error** - Free partial stack when validation fails
2. **Clean up on exit** - Free complete stack before program ends
3. **Prevent memory leaks** - Essential for passing valgrind
4. **Reset stack** - Sets pointer to NULL after freeing

### Why This Matters

**Memory leak prevention:**
```
Stack with 5 nodes:
[5] → [3] → [1] → [4] → [2] → NULL

Each node allocated with stack_new():
- 5 malloc calls = 5 memory blocks
- Must free all 5 blocks
- Missing even one = memory leak

free_stack ensures:
- Every node freed
- In correct order
- Stack pointer set to NULL
```

---

## Deep Dive: How It Works

### The Iterative Freeing Process

```
Strategy: Save next pointer, free current, move to next

Initial: stack → [5] → [3] → [1] → NULL

Iteration 1:
  temp = [3]           (save next)
  free([5])            (free current)
  stack = [3]          (move to next)

Iteration 2:
  temp = [1]
  free([3])
  stack = [1]

Iteration 3:
  temp = NULL
  free([1])
  stack = NULL

Done: All freed
```

### Step-by-Step Process

#### Step 1: Check for NULL

```c
if (!stack || !*stack)
    return;
```

**Safety check:**
- `!stack` - NULL pointer passed
- `!*stack` - Stack itself is NULL
- Both cases: Nothing to free

#### Step 2: Traverse and Free

```c
t_stack *current = *stack;
t_stack *temp;

while (current)
{
    temp = current->next;  // Save next node
    free(current);         // Free current
    current = temp;        // Move to next
}
```

**Why save next pointer?**
```
Without saving:
current = [5] → [3] → [1]
free(current)
current = current->next  ← Use after free! Undefined behavior!

With saving:
temp = current->next     ← Save before freeing
free(current)            ← Now safe to free
current = temp           ← Use saved pointer
```

#### Step 3: Set Pointer to NULL

```c
*stack = NULL;
```

**Why set to NULL?**
- Prevents use-after-free
- Indicates stack is freed
- Safe for double-free checks

---

## Visual Execution Trace

### Example: Free 3-Node Stack

```
Initial state:
stack_a → [5] → [3] → [1] → NULL
          ↑
        malloc'd memory

═══════════════════════════════════════
STEP 1: Check NULL
═══════════════════════════════════════
stack is not NULL ✓
*stack is not NULL ✓
Proceed with freeing...

═══════════════════════════════════════
SETUP
═══════════════════════════════════════
current = *stack = [5]
temp = NULL

═══════════════════════════════════════
ITERATION 1: Free [5]
═══════════════════════════════════════
current = [5] → [3] → [1] → NULL

Save next:
  temp = current->next = [3]

Free current:
  free([5])
  Memory block for [5] returned to OS

Move to next:
  current = temp = [3]

State:
  [5 freed] → [3] → [1] → NULL
              ↑
            current

═══════════════════════════════════════
ITERATION 2: Free [3]
═══════════════════════════════════════
current = [3] → [1] → NULL

Save next:
  temp = current->next = [1]

Free current:
  free([3])

Move to next:
  current = temp = [1]

State:
  [5 freed] [3 freed] → [1] → NULL
                        ↑
                      current

═══════════════════════════════════════
ITERATION 3: Free [1]
═══════════════════════════════════════
current = [1] → NULL

Save next:
  temp = current->next = NULL

Free current:
  free([1])

Move to next:
  current = temp = NULL

State:
  [5 freed] [3 freed] [1 freed]
  current = NULL → loop exits

═══════════════════════════════════════
STEP 2: Set Pointer to NULL
═══════════════════════════════════════
*stack = NULL

Final state:
  stack_a = NULL (all memory freed)

═══════════════════════════════════════
COMPLETE
═══════════════════════════════════════
All 3 nodes freed
No memory leaks ✓
```

---

## Complete Algorithm Pseudocode

```
FUNCTION free_stack(stack):
    // Step 1: Safety check
    IF stack is NULL OR *stack is NULL:
        RETURN  // Nothing to free

    // Step 2: Initialize traversal
    current = *stack
    temp = NULL

    // Step 3: Free each node
    WHILE current is not NULL:
        // Save next node before freeing
        temp = current.next

        // Free current node
        free(current)

        // Move to next node
        current = temp

    // Step 4: Set stack pointer to NULL
    *stack = NULL
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: NULL Pointer

```c
t_stack **stack = NULL;
free_stack(stack);
// Safe - returns immediately
```

### Edge Case 2: NULL Stack

```c
t_stack *stack_a = NULL;
free_stack(&stack_a);
// Safe - returns immediately
```

### Edge Case 3: Single Node

```c
t_stack *stack_a = stack_new(42);
free_stack(&stack_a);
// Frees one node
// stack_a = NULL
```

### Edge Case 4: Large Stack

```c
// 500 nodes
free_stack(&stack_a);
// Frees all 500 nodes
// No stack overflow (iterative, not recursive)
```

---

## Time & Space Complexity

### Time Complexity: O(n)

```
n = number of nodes

Operations:
- Visit each node once: O(n)
- Free each node: O(1) per node
- Total: n × O(1) = O(n)

Linear time - proportional to stack size
```

### Space Complexity: O(1)

```
Variables:
- current: 8 bytes
- temp: 8 bytes
- No recursion
- No allocations

Total: O(1) - constant space
```

---

## Common Mistakes to Avoid

### Mistake 1: Not Saving Next Pointer

```c
❌ WRONG:
while (current)
{
    free(current);
    current = current->next;  // Use after free!
}

✓ CORRECT:
while (current)
{
    temp = current->next;  // Save first
    free(current);
    current = temp;  // Use saved value
}
```

### Mistake 2: Not Setting to NULL

```c
❌ WRONG:
void free_stack(t_stack **stack)
{
    // Free all nodes...
    // Don't set *stack = NULL
}

Problem: Dangling pointer
Calling code might try to use freed memory

✓ CORRECT:
*stack = NULL;  // Mark as freed
```

### Mistake 3: Using Wrong Parameter Type

```c
❌ WRONG:
void free_stack(t_stack *stack)
{
    // Can't set caller's pointer to NULL!
    stack = NULL;  // Only sets local copy
}

✓ CORRECT:
void free_stack(t_stack **stack)
{
    *stack = NULL;  // Sets caller's pointer
}
```

### Mistake 4: Recursive Implementation

```c
❌ LESS EFFICIENT:
void free_stack(t_stack **stack)
{
    if (!stack || !*stack)
        return;
    free_stack(&(*stack)->next);
    free(*stack);
    *stack = NULL;
}

Problem: Stack overflow for large lists

✓ BETTER:
// Use iterative approach (as shown)
```

---

## Integration with Push_swap

### Usage in Error Cleanup

```c
t_stack *init_stack_a(int argc, char **argv)
{
    t_stack *stack_a = NULL;

    // Building stack...
    
    if (error_occurred)
    {
        free_stack(&stack_a);  // Clean up
        return (NULL);
    }

    return (stack_a);
}
```

### Usage at Program End

```c
int main(int argc, char **argv)
{
    t_stack *stack_a;
    t_stack *stack_b;

    // Sort stacks...

    // Clean up before exit
    free_stack(&stack_a);
    free_stack(&stack_b);
    return (0);
}
```

---

## 42 Norm Considerations

### Implementation Example

```c
void    free_stack(t_stack **stack)
{
    t_stack *current;
    t_stack *temp;

    if (!stack || !*stack)
        return ;
    current = *stack;
    while (current)
    {
        temp = current->next;
        free(current);
        current = temp;
    }
    *stack = NULL;
}
```

**Norm compliant:**
- ~15 lines ✓
- Clear variable names ✓
- Iterative (no recursion) ✓

---

## Testing Strategy

### Test Case 1: Empty Stack

```c
t_stack *stack = NULL;
free_stack(&stack);
assert(stack == NULL);
printf("✓ Empty stack handled\n");
```

### Test Case 2: Single Node

```c
t_stack *stack = stack_new(42);
free_stack(&stack);
assert(stack == NULL);
// Valgrind: no leaks
```

### Test Case 3: Multiple Nodes

```c
t_stack *stack = NULL;
stack_add_back(&stack, stack_new(5));
stack_add_back(&stack, stack_new(3));
stack_add_back(&stack, stack_new(1));
free_stack(&stack);
assert(stack == NULL);
// Valgrind: all freed
```

### Test Case 4: Valgrind Check

```bash
$ valgrind --leak-check=full ./push_swap 5 3 1
# Should show: All heap blocks were freed
```

---

## Summary

1. **Checks** for NULL pointers
2. **Iterates** through linked list
3. **Saves** next pointer before freeing
4. **Frees** each node
5. **Sets** stack pointer to NULL

**Key insight:** Proper cleanup is as important as allocation. This function ensures every malloc has a corresponding free, keeping your program leak-free.

---

## Location in Project

**File:** `srcs/free.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 3.3

**Function prototype:**
```c
void free_stack(t_stack **stack);
```

---

## Related Functions

**Calls:**
- `free()` - System call

**Called by:**
- `error_exit()` - Error cleanup
- `main()` - Normal cleanup
- `init_stack_a()` - Error cleanup

**Related:**
- `stack_new()` - Allocates what this frees
- `free_split()` - Frees string arrays

---

*Remember: Every malloc needs a free. This function ensures your stack memory is properly returned to the system!*
