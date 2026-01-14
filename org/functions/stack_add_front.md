# stack_add_front - Add Node to Beginning of Stack

## Function Signature

```c
void stack_add_front(t_stack **stack, t_stack *new)
```

**Return type:** `void` - No return value (modifies stack in place)
**Parameter 1:** `t_stack **stack` - Double pointer to the head of the stack
**Parameter 2:** `t_stack *new` - Pointer to the new node to add

---

## Purpose & Use Case

`stack_add_front` is a **fundamental linked list operation** that adds a new node to the **beginning** (front/head) of your stack. This is one of the most important operations because adding to the front is **O(1)** - constant time - making it extremely efficient.

### When You'll Use It

You'll call `stack_add_front` whenever you need to:
1. **Push operations** - `pa` and `pb` add elements to the front of stacks
2. **Quick insertion** - Add new node without traversing the entire list
3. **Stack initialization** - Build your stack by adding nodes to the front
4. **Maintaining top of stack** - The front is the "top" in push_swap terminology

### Why Front Addition Matters

In stack operations, the **front/head** of the linked list represents the **top** of the stack:
```
Stack visualization:
[3] <- top (front of list)
[5]
[8]
[2] <- bottom (end of list)

Linked list structure:
head -> [3] -> [5] -> [8] -> [2] -> NULL
```

---

## Deep Dive: How It Works

### Understanding Double Pointers

Before diving into the function, you need to understand **why** we use `t_stack **stack`.

**Single Pointer (`t_stack *stack`):**
- Gives you a copy of the pointer
- Cannot modify the original pointer in the calling function
- Like receiving a photocopy - changes don't affect the original

**Double Pointer (`t_stack **stack`):**
- Gives you the address of the pointer
- CAN modify the original pointer in the calling function
- Like receiving the original document - changes are permanent

**Why it matters:**
```c
// With single pointer (WRONG):
void add_front_wrong(t_stack *stack, t_stack *new)
{
    new->next = stack;
    stack = new;  // Only modifies local copy!
}

// Caller's perspective:
t_stack *my_stack = NULL;
add_front_wrong(my_stack, node);
// my_stack is still NULL! ❌

// With double pointer (CORRECT):
void stack_add_front(t_stack **stack, t_stack *new)
{
    new->next = *stack;
    *stack = new;  // Modifies original pointer!
}

// Caller's perspective:
t_stack *my_stack = NULL;
stack_add_front(&my_stack, node);
// my_stack now points to node! ✅
```

---

## Step-by-Step Breakdown

### Step 1: Link New Node to Current Head

**Operation:** `new->next = *stack`

This makes the new node point to what is currently the first node in the list.

**Memory perspective:**
```
Before:
stack -> [5] -> [8] -> NULL
new   -> [3] -> ?

After new->next = *stack:
stack -> [5] -> [8] -> NULL
new   -> [3] -> [5] (points to same node as stack)
```

**Key insight:** We must do this FIRST. If we change `*stack` first, we'd lose the reference to the original list!

### Step 2: Update Head Pointer

**Operation:** `*stack = new`

This makes the stack head pointer point to our new node.

**Memory perspective:**
```
Before *stack = new:
stack -> [5] -> [8] -> NULL
new   -> [3] -> [5]

After *stack = new:
stack -> [3] -> [5] -> [8] -> NULL
new   -> [3] (same node)
```

**Result:** The new node is now at the front, and the old front is second.

---

## Real-World Example: Adding to Front

Let's trace through adding `3` to a stack containing `[5, 8]`:

### Before Calling `stack_add_front(&stack_a, node_3)`

```
Stack A state:
stack_a -> [5] -> [8] -> NULL

New node (created by stack_new(3)):
node_3 -> [3] -> NULL

Memory addresses (example):
stack_a     = 0x1000 (points to node with value 5)
node_3      = 0x2000 (points to node with value 3)
node_3->next = NULL (0x0)
```

### During Execution: Step 1 - `new->next = *stack`

```
Explanation:
- *stack means "what stack_a points to" (address 0x1000)
- We set new->next to that address
- Now node_3 points to the same node stack_a points to

After Step 1:
stack_a     -> [5] -> [8] -> NULL  (unchanged)
node_3      -> [3] -> [5] -> [8] -> NULL

Memory:
stack_a     = 0x1000
node_3      = 0x2000
node_3->next = 0x1000 (points to node with value 5)
```

### During Execution: Step 2 - `*stack = new`

```
Explanation:
- *stack means "what stack_a points to"
- We change stack_a to point to new instead
- Now stack_a points to node_3

After Step 2:
stack_a -> [3] -> [5] -> [8] -> NULL

Memory:
stack_a     = 0x2000 (now points to node_3)
node_3      = 0x2000
node_3->next = 0x1000
```

### After Calling `stack_add_front(&stack_a, node_3)`

```
Final state:
stack_a -> [3] -> [5] -> [8] -> NULL

The stack now has 3 at the front!
```

---

## Visual Example: Building a Stack

Let's build a stack by adding nodes to the front:

### Starting with Empty Stack

```
t_stack *stack_a = NULL;

State: stack_a -> NULL
```

### Add First Node (value 5)

```c
t_stack *node1 = stack_new(5);
stack_add_front(&stack_a, node1);
```

**Before:**
```
stack_a -> NULL
node1   -> [5] -> NULL
```

**Execution:**
```
Step 1: node1->next = *stack_a → node1->next = NULL
Step 2: *stack_a = node1

Result: stack_a -> [5] -> NULL
```

### Add Second Node (value 3)

```c
t_stack *node2 = stack_new(3);
stack_add_front(&stack_a, node2);
```

**Before:**
```
stack_a -> [5] -> NULL
node2   -> [3] -> NULL
```

**Execution:**
```
Step 1: node2->next = *stack_a → node2->next points to [5]
Step 2: *stack_a = node2

Result: stack_a -> [3] -> [5] -> NULL
```

### Add Third Node (value 8)

```c
t_stack *node3 = stack_new(8);
stack_add_front(&stack_a, node3);
```

**Before:**
```
stack_a -> [3] -> [5] -> NULL
node3   -> [8] -> NULL
```

**Execution:**
```
Step 1: node3->next = *stack_a → node3->next points to [3]
Step 2: *stack_a = node3

Result: stack_a -> [8] -> [3] -> [5] -> NULL
```

**Notice:** Each new node becomes the new front. The list is built in reverse order!

---

## Edge Cases

### Edge Case 1: Adding to Empty Stack

**Scenario:**
```c
t_stack *stack_a = NULL;
t_stack *new = stack_new(42);
stack_add_front(&stack_a, new);
```

**Analysis:**
```
Step 1: new->next = *stack_a
        new->next = NULL (stack is empty)

Step 2: *stack_a = new
        stack_a now points to new

Result: stack_a -> [42] -> NULL ✅
```

**Outcome:** Works perfectly! The new node becomes the only node.

### Edge Case 2: Adding to Single-Element Stack

**Scenario:**
```c
t_stack *stack_a = stack_new(10);
t_stack *new = stack_new(20);
stack_add_front(&stack_a, new);
```

**Analysis:**
```
Before: stack_a -> [10] -> NULL

Step 1: new->next = *stack_a
        new->next points to [10]

Step 2: *stack_a = new

After: stack_a -> [20] -> [10] -> NULL ✅
```

**Outcome:** Works perfectly! New node links to existing node.

### Edge Case 3: Adding NULL Node (Don't Do This!)

**Scenario:**
```c
t_stack *stack_a = stack_new(5);
stack_add_front(&stack_a, NULL);  // ❌ BAD!
```

**Analysis:**
```
Step 1: new->next = *stack_a
        NULL->next = ???
        SEGMENTATION FAULT! 💥
```

**Protection:** You should check if `new` is NULL before calling this function!

### Edge Case 4: Passing NULL Stack Pointer (Don't Do This!)

**Scenario:**
```c
t_stack *new = stack_new(42);
stack_add_front(NULL, new);  // ❌ BAD!
```

**Analysis:**
```
Step 1: new->next = *stack
        *stack means dereference NULL
        SEGMENTATION FAULT! 💥
```

**Protection:** The calling function must pass a valid pointer address!

---

## Time & Space Complexity

### Time Complexity: O(1)

**Constant time** - This is the key advantage of adding to the front!

**Why O(1)?**
```
Operations performed:
1. Assign new->next = *stack     → 1 operation
2. Assign *stack = new            → 1 operation

Total: 2 operations (constant)
No loops, no traversal, no searching!
```

**Comparison with add_back:**
```
stack_add_front: O(1)
  → Just update head pointer

stack_add_back: O(n)
  → Must traverse entire list to find end
  → n = number of nodes
```

### Space Complexity: O(1)

**Constant space** - No additional memory allocated.

**Why O(1)?**
```
Memory used:
- No new allocations
- No temporary arrays
- Only pointer reassignments

No matter how large the stack, uses same amount of memory!
```

---

## Implementation Pseudocode

```
FUNCTION stack_add_front(stack, new):
    // Input: stack is a double pointer to head
    //        new is a pointer to the node to add

    // Step 1: Link new node to current head
    // This makes new point to what stack currently points to
    new.next = *stack

    // Step 2: Update head pointer to point to new node
    // This makes stack point to new, making it the new front
    *stack = new

    // Done! No return value needed (modified in place)
END FUNCTION
```

**Alternative implementation with safety check:**
```
FUNCTION stack_add_front_safe(stack, new):
    // Check for NULL inputs
    IF stack is NULL:
        RETURN  // Cannot modify NULL pointer

    IF new is NULL:
        RETURN  // Cannot add NULL node

    // Perform the operation
    new.next = *stack
    *stack = new
END FUNCTION
```

---

## 42 Norm Considerations

### Norm Compliance

✅ **Function length:** 2-3 lines (well under 25-line limit)
✅ **Single responsibility:** Only adds node to front
✅ **No global variables:** Everything is passed as parameters
✅ **Return type:** `void` (modifies in place)
✅ **Clear naming:** `stack_add_front` clearly describes what it does
✅ **Proper parameter types:** Uses double pointer correctly

### Naming Convention

```
stack_add_front
│    │   │
│    │   └─── front (where it adds)
│    └─────── add (what it does)
└──────────── stack (what it operates on)
```

Following the same pattern as other stack functions:
- `stack_add_back`
- `stack_new`
- `stack_last`
- `stack_size`

---

## Common Mistakes to Avoid

### Mistake 1: Wrong Order of Operations

```c
❌ WRONG:
void stack_add_front(t_stack **stack, t_stack *new)
{
    *stack = new;        // Changed head first!
    new->next = *stack;  // Now points to itself! Circular reference!
}

Result: stack -> [new] -> [new] -> [new] -> ... (infinite loop)
```

**Why it's wrong:** After `*stack = new`, dereferencing `*stack` gives you `new`, so you're setting `new->next = new`.

### Mistake 2: Using Single Pointer

```c
❌ WRONG:
void stack_add_front(t_stack *stack, t_stack *new)
{
    new->next = stack;
    stack = new;  // Only modifies local copy!
}

// Calling function:
stack_add_front(my_stack, node);
// my_stack unchanged! ❌
```

### Mistake 3: Not Handling Empty Stack

```c
❌ WRONG (but common misconception):
void stack_add_front(t_stack **stack, t_stack *new)
{
    if (*stack == NULL)
        // Do nothing? Wrong!

    new->next = *stack;  // This handles NULL correctly!
    *stack = new;
}
```

**Why it's not needed:** Setting `new->next = NULL` is perfectly fine! That's how you start a list.

### Mistake 4: Forgetting to Update Next Pointer

```c
❌ WRONG:
void stack_add_front(t_stack **stack, t_stack *new)
{
    *stack = new;  // Only updated head
    // Forgot: new->next = old_head
}

Result: Lost all nodes except new! ❌
```

### Mistake 5: Memory Management Confusion

```c
❌ WRONG:
void stack_add_front(t_stack **stack, t_stack *new)
{
    t_stack *copy = malloc(sizeof(t_stack));
    *copy = *new;  // Unnecessary copy!
    copy->next = *stack;
    *stack = copy;
}

Why wrong: Wastes memory, creates duplicate, loses reference to new
```

---

## Testing Strategy

### Test Case 1: Add to Empty Stack

```c
// Test
t_stack *stack = NULL;
t_stack *node = stack_new(42);
stack_add_front(&stack, node);

// Verify
assert(stack != NULL);
assert(stack->value == 42);
assert(stack->next == NULL);
assert(stack_size(stack) == 1);
```

### Test Case 2: Add to Existing Stack

```c
// Setup
t_stack *stack = stack_new(5);
t_stack *node = stack_new(3);

// Test
stack_add_front(&stack, node);

// Verify
assert(stack->value == 3);           // New node is front
assert(stack->next->value == 5);     // Old node is second
assert(stack->next->next == NULL);   // End of list
assert(stack_size(stack) == 2);
```

### Test Case 3: Add Multiple Nodes

```c
// Setup
t_stack *stack = NULL;

// Test
stack_add_front(&stack, stack_new(1));
stack_add_front(&stack, stack_new(2));
stack_add_front(&stack, stack_new(3));

// Verify order (should be reverse of addition)
assert(stack->value == 3);
assert(stack->next->value == 2);
assert(stack->next->next->value == 1);
assert(stack_size(stack) == 3);
```

### Test Case 4: Integration with Push Operation

```c
// Setup
t_stack *stack_a = stack_new(5);
stack_add_front(&stack_a, stack_new(3));
t_stack *stack_b = NULL;

// Test push operation (which uses stack_add_front)
t_stack *temp = stack_a;
stack_a = stack_a->next;
stack_add_front(&stack_b, temp);

// Verify
assert(stack_a->value == 5);  // 5 now at front of A
assert(stack_b->value == 3);  // 3 pushed to B
```

### Test Case 5: Memory Integrity

```c
// Test with valgrind
t_stack *stack = NULL;
for (int i = 0; i < 100; i++)
    stack_add_front(&stack, stack_new(i));

free_stack(&stack);
// Run with: valgrind --leak-check=full ./test
// Should show: no leaks are possible
```

---

## Why This Design?

### Simplicity

The function is incredibly simple - just 2 lines of actual code:
```c
new->next = *stack;
*stack = new;
```

This simplicity makes it:
- Easy to understand
- Easy to debug
- Hard to get wrong
- Fast to execute

### Efficiency

O(1) time complexity means:
- No performance degradation as stack grows
- Perfect for frequent operations
- Essential for push_swap optimization

**Comparison:**
```
Adding 1000 nodes to front: 1000 × O(1) = 1000 operations
Adding 1000 nodes to back:  1000 × O(n) = ~500,000 operations

Front addition is ~500x faster! 🚀
```

### Flexibility

Works perfectly for:
- Empty stacks
- Single-element stacks
- Large stacks
- Any integer value

No special cases needed!

---

## Integration: How It's Used in push_swap

### Usage 1: Push Operations

Every `pa` and `pb` operation uses `stack_add_front`:

```c
void pa(t_stack **stack_a, t_stack **stack_b, int print)
{
    t_stack *temp;

    if (!*stack_b)
        return;

    temp = *stack_b;              // Save top of B
    *stack_b = (*stack_b)->next;  // Remove from B
    stack_add_front(stack_a, temp); // Add to front of A

    if (print)
        write(1, "pa\n", 3);
}
```

### Usage 2: Stack Initialization

Some parsing strategies add nodes to the front:

```c
t_stack *parse_arguments(int argc, char **argv)
{
    t_stack *stack = NULL;
    int i;

    for (i = argc - 1; i >= 1; i--)
    {
        t_stack *node = stack_new(ft_atoi(argv[i]));
        stack_add_front(&stack, node);
    }
    return stack;
}
```

### Usage 3: Comparison with stack_add_back

```c
// Building stack with add_front (fast but reversed order):
for (int i = 0; i < n; i++)
    stack_add_front(&stack, stack_new(values[i]));
// Result: stack = [values[n-1], ..., values[1], values[0]]

// Building stack with add_back (slow but correct order):
for (int i = 0; i < n; i++)
    stack_add_back(&stack, stack_new(values[i]));
// Result: stack = [values[0], values[1], ..., values[n-1]]
```

---

## Related Functions

### Complementary Functions

- **stack_add_back()** - Adds node to end of stack (O(n) operation)
- **stack_last()** - Finds last node (needed by stack_add_back)
- **stack_new()** - Creates the nodes you add

### Functions That Use This

- **pa()** - Push to A uses stack_add_front
- **pb()** - Push to B uses stack_add_front
- **init_stack_a()** - May use this during parsing

### Inverse Operations

- **Remove from front** - Done in push operations:
  ```c
  temp = *stack;
  *stack = (*stack)->next;
  // temp is now removed from front
  ```

---

## Location in Project

**File:** `srcs/stack_utils.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 1.2 (Stack Utility Functions - Basic Operations)

**Function prototype:**
```c
void stack_add_front(t_stack **stack, t_stack *new);
```

**Typical implementation:**
```c
void stack_add_front(t_stack **stack, t_stack *new)
{
    new->next = *stack;
    *stack = new;
}
```

---

## Summary: What stack_add_front Does

1. **Takes new node** and makes it point to current head
2. **Updates head pointer** to point to new node
3. **Result:** New node is now at the front
4. **Time:** O(1) - constant time, super fast!
5. **Critical for:** Push operations, efficient stack building

**Key takeaway:** This is one of the simplest yet most important functions in your entire push_swap project. Master this, and you understand the fundamental operation of stacks as linked lists!

---

*Remember: The front of the linked list is the top of the stack. Adding to front is adding to top!*
