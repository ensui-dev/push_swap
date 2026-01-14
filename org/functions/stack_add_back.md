# stack_add_back - Add Node to End of Stack

## Function Signature

```c
void stack_add_back(t_stack **stack, t_stack *new)
```

**Return type:** `void` - No return value
**Parameters:**
- `t_stack **stack` - Pointer to pointer to the first node (head) of stack
- `t_stack *new` - Pointer to the new node to add

---

## Purpose & Use Case

`stack_add_back` adds a new node to the END of a linked list stack. It handles both empty stacks and non-empty stacks.

### When You'll Use It

You'll call `stack_add_back` whenever you need to:
1. **Build initial stack** - Add parsed numbers to end of stack A
2. **Maintain order** - Preserve input order when creating stack
3. **Append elements** - Add nodes to tail of list

---

## How It Works

### Conceptual Algorithm

This is a **conditional linking** operation.

**The Process:**
1. Check if stack is empty (NULL)
2. If empty: new node becomes the head
3. If not empty: find last node and link new node after it

### Step-by-Step Breakdown

#### Step 1: Check if Stack is Empty
- Dereference the double pointer to get actual stack pointer
- If `*stack` is NULL, the stack is empty
- In this case, make new node the first node

**Empty Stack Scenario:**
```
Before: *stack = NULL
After:  *stack = new_node
```

#### Step 2: If Empty - Set as Head
- Set `*stack = new`
- The new node is now the only node
- Its `next` should already be NULL (from stack_new)

#### Step 3: If Not Empty - Find Last Node
- Call `stack_last(*stack)` to get pointer to last node
- Last node is the one where `next == NULL`

#### Step 4: Link New Node to End
- Set `last->next = new`
- The old last node now points to new node
- New node becomes the new last node
- New node's `next` is already NULL

---

## Visual Example

### Scenario 1: Adding to Empty Stack

**Before:**
```
*stack = NULL

new = [42] -> NULL
```

**After stack_add_back(&stack, new):**
```
*stack = [42] -> NULL
```

### Scenario 2: Adding to Non-Empty Stack

**Before:**
```
*stack -> [5] -> [3] -> NULL
                  ^
                 last

new = [1] -> NULL
```

**Step-by-step:**
```
1. Check: *stack != NULL (not empty)
2. Find last: last = stack_last(*stack) → points to [3]
3. Link: last->next = new
```

**After:**
```
*stack -> [5] -> [3] -> [1] -> NULL
                         ^
                       new last
```

---

## Why Double Pointer?

### The Problem with Single Pointer

If we used `void stack_add_back(t_stack *stack, t_stack *new)`:

```c
// This DOESN'T work for empty stack!
void stack_add_back(t_stack *stack, t_stack *new)
{
    if (!stack)
        stack = new;  // Only modifies LOCAL copy!
    // ...
}

// Caller:
t_stack *my_stack = NULL;
stack_add_back(my_stack, new);
// my_stack is STILL NULL! (change didn't persist)
```

### The Solution with Double Pointer

```c
void stack_add_back(t_stack **stack, t_stack *new)
{
    if (!*stack)
        *stack = new;  // Modifies ACTUAL pointer!
    // ...
}

// Caller:
t_stack *my_stack = NULL;
stack_add_back(&my_stack, new);  // Pass ADDRESS of pointer
// my_stack now points to new! (change persisted)
```

**Memory Visualization:**
```
Caller has:
my_stack = NULL (stored at address 0x1000)

Call stack_add_back(&my_stack, new):
  stack parameter = 0x1000 (address of my_stack)
  *stack = value at 0x1000 = NULL
  *stack = new  → writes new pointer to address 0x1000

After function:
my_stack = new (address 0x1000 now contains new's address)
```

---

## Implementation Pseudocode

```
FUNCTION stack_add_back(stack, new):
    // Step 1 & 2: Handle empty stack
    IF *stack is NULL:
        *stack = new
        RETURN  // Done, new is now the head

    // Step 3: Find last node
    last = stack_last(*stack)

    // Step 4: Link new node to end
    last->next = new

END FUNCTION
```

---

## Usage Examples in Push_swap

### Example 1: Building Stack from Input

```c
// Parsing: ./push_swap 5 3 1
t_stack *stack_a = NULL;

// Parse first number: 5
t_stack *node1 = stack_new(5);
stack_add_back(&stack_a, node1);
// stack_a: [5] -> NULL

// Parse second number: 3
t_stack *node2 = stack_new(3);
stack_add_back(&stack_a, node2);
// stack_a: [5] -> [3] -> NULL

// Parse third number: 1
t_stack *node3 = stack_new(1);
stack_add_back(&stack_a, node3);
// stack_a: [5] -> [3] -> [1] -> NULL
```

### Example 2: Combined with Parsing Loop

```c
t_stack *stack_a = NULL;

int i = 1;
while (i < argc)
{
    int value = ft_atoi(argv[i]);
    t_stack *new_node = stack_new(value);

    if (!new_node)
        error_exit(&stack_a, NULL);  // Malloc failed

    stack_add_back(&stack_a, new_node);
    i++;
}
// Stack built in order: first arg → top, last arg → bottom
```

### Example 3: Error Handling

```c
t_stack *new = stack_new(42);
if (!new)
{
    // Handle malloc failure
    free_stack(&stack_a);
    error_exit();
}

stack_add_back(&stack_a, new);
// Only add if allocation succeeded
```

---

## Edge Cases

### Case 1: Adding to NULL Stack (Empty)
```
Input:
  *stack = NULL
  new = [42] -> NULL

Process:
  *stack is NULL? YES
  *stack = new

Output:
  *stack = [42] -> NULL
```

### Case 2: Adding to Single Node
```
Input:
  *stack = [5] -> NULL
  new = [3] -> NULL

Process:
  *stack is NULL? NO
  Find last: [5]
  [5]->next = new

Output:
  *stack = [5] -> [3] -> NULL
```

### Case 3: Adding Multiple Times
```
Start: *stack = NULL

Add [1]: *stack = [1] -> NULL
Add [2]: *stack = [1] -> [2] -> NULL
Add [3]: *stack = [1] -> [2] -> [3] -> NULL
Add [4]: *stack = [1] -> [2] -> [3] -> [4] -> NULL
```

---

## Time Complexity

**O(n)** where n is the number of existing nodes

**Why?**
- If stack is empty: O(1) (just set head)
- If stack has nodes: O(n) (must call stack_last which traverses)
- Dominated by stack_last traversal

**Space Complexity:** O(1)
- Only stores one pointer variable (last)
- No additional data structures

**Implication for Building Stack:**
- Adding n nodes one by one: O(1) + O(2) + O(3) + ... + O(n) = O(n²)
- For 100 numbers: ~5,000 operations
- For 500 numbers: ~125,000 operations
- Still acceptable for one-time initialization

---

## 42 Norm Considerations

✅ **Function length:** Short (6-10 lines), under 25 line limit
✅ **Parameters:** 2 parameters (under 4 limit)
✅ **Variables:** Need 1 variable (last pointer)
✅ **No loops:** Just conditional and function call
✅ **No global variables:** Everything is local
✅ **Return value:** void (no return needed)

**Variable Declaration:**
```c
t_stack *last;
```

---

## Common Mistakes to Avoid

### Mistake 1: Using Single Pointer for Empty Stack
```c
❌ WRONG:
void stack_add_back(t_stack *stack, t_stack *new)
{
    if (!stack)
        stack = new;  // Doesn't modify caller's pointer!
}
```
**Fix:** Use double pointer `**stack`

### Mistake 2: Not Checking if New is NULL
```c
❌ WRONG:
void stack_add_back(t_stack **stack, t_stack *new)
{
    // What if new is NULL?
    if (!*stack)
        *stack = new;  // Adding NULL to stack!
}
```
**Fix:** Add check `if (!new) return;` or ensure caller checks

### Mistake 3: Forgetting Early Return
```c
❌ WRONG:
void stack_add_back(t_stack **stack, t_stack *new)
{
    if (!*stack)
        *stack = new;

    // Continues to execute even if stack was empty!
    t_stack *last = stack_last(*stack);
    last->next = new;  // Now new->next = new (loop!)
}
```
**Fix:** `return;` after setting head for empty stack

### Mistake 4: Not Handling NULL Stack Parameter
```c
❌ WRONG:
void stack_add_back(t_stack **stack, t_stack *new)
{
    if (!*stack)  // Crashes if stack itself is NULL!
        ...
}
```
**Fix:** Check `if (!stack)` before `if (!*stack)`

---

## Relationship with Libft

Similar to `ft_lstadd_back()` from your libft bonus!

**Libft function:**
```c
void ft_lstadd_back(t_list **lst, t_list *new);
```

**Key Differences:**
- Different structure type (`t_list` vs `t_stack`)
- Same algorithm and logic
- Same use of double pointer

**You can reference your ft_lstadd_back.c for implementation guidance!**

---

## Alternative: stack_add_front

You'll also implement `stack_add_front` which is much faster (O(1)):

```c
// Comparison
stack_add_back(&stack, new);   // O(n) - must find end
stack_add_front(&stack, new);  // O(1) - just link to head

// Use stack_add_back when: order matters (parsing input)
// Use stack_add_front when: speed matters (push operations)
```

---

## Testing Strategy

### Test Cases

1. **Adding to empty stack:**
   ```c
   t_stack *stack = NULL;
   t_stack *new = stack_new(42);

   stack_add_back(&stack, new);

   assert(stack != NULL);
   assert(stack == new);
   assert(stack->value == 42);
   assert(stack->next == NULL);
   ```

2. **Adding to single node:**
   ```c
   t_stack *stack = stack_new(1);
   t_stack *new = stack_new(2);

   stack_add_back(&stack, new);

   assert(stack->value == 1);
   assert(stack->next == new);
   assert(new->next == NULL);
   ```

3. **Adding multiple nodes:**
   ```c
   t_stack *stack = NULL;

   for (int i = 1; i <= 5; i++)
   {
       t_stack *new = stack_new(i);
       stack_add_back(&stack, new);
   }

   // Verify order: 1 -> 2 -> 3 -> 4 -> 5 -> NULL
   assert(stack->value == 1);
   assert(stack_last(stack)->value == 5);
   assert(stack_size(stack) == 5);
   ```

---

## Performance Optimization Note

If you're adding many nodes in sequence, consider:

```c
// Slower: O(n²) total
for (each node)
    stack_add_back(&stack, new);  // Each call traverses

// Faster: O(n) total - keep track of last
t_stack *last = NULL;
for (each node)
{
    if (!stack)
    {
        stack = new;
        last = new;
    }
    else
    {
        last->next = new;
        last = new;
    }
}
```

**However:** For push_swap, the simpler `stack_add_back` is fine since:
- You only build stack once (initialization)
- Maximum 500 nodes = acceptable O(n²) performance
- Cleaner, more maintainable code

---

## Related Functions

- **stack_new()** - Creates nodes to add
- **stack_last()** - Used internally to find end
- **stack_add_front()** - Faster alternative (adds to beginning)
- **ft_lstadd_back()** - Libft equivalent for reference

---

## Location in Project

**File:** `srcs/stack_utils.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 1.2 (Stack Utility Functions - Basic Operations)
**Dependencies:** `stack_last()`

---

## Summary

**What stack_add_back does:**
1. Checks if stack is empty
2. If empty: new node becomes head
3. If not empty: finds last node and links new node after it

**Key characteristics:**
- Uses double pointer to modify caller's pointer
- O(n) time complexity (due to finding last node)
- O(1) space complexity
- Maintains insertion order
- Similar to ft_lstadd_back from libft

**Critical for:** Building initial stack during parsing

---

*Essential for stack initialization - ensures elements are added in correct order!*
