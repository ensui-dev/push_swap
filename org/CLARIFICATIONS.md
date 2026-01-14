# Push_swap TODO Clarifications

## Question 1: "Ensure proper linking" - What does this mean?

**Location:** TODO.md Phase 1.2, `stack_add_back` function

### What "Ensure proper linking" Means:

When you add a new node to the end of a stack, you must establish a **pointer connection** (link) between the old last node and the new node.

#### The Linking Process:

```
Before adding new node [X]:
Stack: [A] -> [B] -> [C] -> NULL
                      ^
                    last

After linking new node [X]:
Stack: [A] -> [B] -> [C] -> [X] -> NULL
                      |       ^
                      |_______|
                    This is the "link"
```

### Why This Is Important:

1. **List Integrity**: Without proper linking, the node is "floating" in memory - accessible but disconnected from your stack

2. **Memory Leak Risk**: If you create a node but don't link it, you lose access to it but it's still allocated
   ```c
   // WRONG - Missing link
   t_stack *new = stack_new(42);
   // If you don't link it, you've lost the pointer!
   // Memory leak because you can't free it later
   ```

3. **Traversal Breaks**: Functions like `stack_size`, `stack_last`, and `free_stack` traverse using `next` pointers
   ```c
   // If last->next is not set to new:
   Stack: [A] -> [B] -> [C] -> NULL
                              X [New] -> NULL (orphaned!)

   // stack_size will return 3 instead of 4
   // stack_last will return [C] instead of [New]
   // free_stack will miss [New] - memory leak!
   ```

4. **Stack Operations Fail**: Operations like `pa`/`pb` that expect to access all nodes will miss the unlinked node

### Correct Linking Example:

```c
void stack_add_back(t_stack **stack, t_stack *new)
{
    t_stack *last;

    if (!*stack)
    {
        *stack = new;  // New becomes head
        return;
    }

    last = stack_last(*stack);  // Find current last node
    last->next = new;           // ← THIS IS THE LINKING!
                                // Connect old last to new node
}
```

### What To Verify:

✅ **Check 1**: The old last node's `next` pointer points to the new node
✅ **Check 2**: The new node's `next` pointer is NULL (end of list)
✅ **Check 3**: You can traverse from head to new node following `next` pointers
✅ **Check 4**: `stack_size` returns the correct count including the new node

---

## Question 2: "Useful for push operations" - Why is this a TODO task?

**Location:** TODO.md Phase 1.2, `stack_add_front` function

### Why This Comment Exists:

This is **explanatory, not a task to complete**. It's there to help you understand WHY you're implementing `stack_add_front`.

### Understanding the Context:

#### stack_add_back vs stack_add_front:

```
stack_add_back(&stack, new):   O(n) - must traverse to find last
stack_add_front(&stack, new):  O(1) - just link to head
```

#### Where Each Is Used:

1. **stack_add_back** (slower):
   - Used during **initial parsing** only
   - Preserves input order: `./push_swap 5 3 1` → Stack: [5]->[3]->[1]
   - Called ~100-500 times total (once per input number)
   - O(n²) total time acceptable because it's one-time initialization

2. **stack_add_front** (faster):
   - Used in **pa/pb operations** (push operations)
   - Called potentially thousands of times during sorting
   - O(1) is critical for performance
   - Every `pa` and `pb` essentially does a stack_add_front

### Why "Useful for push operations"?

The `pa` (push to A) and `pb` (push to B) operations work like this:

```c
// Simplified pa operation:
void pa(t_stack **stack_a, t_stack **stack_b)
{
    t_stack *temp;

    temp = *stack_b;              // Get top of B
    *stack_b = (*stack_b)->next;  // Remove from B

    // Add to front of A - THIS USES stack_add_front LOGIC!
    temp->next = *stack_a;
    *stack_a = temp;
}
```

**The comment means**: "You'll understand why this function is important when you implement pa/pb - it's the core logic of push operations"

### It's NOT a task to complete:

- ❌ Don't write "implement push operations" in stack_add_front
- ❌ Don't add push logic to stack_add_front
- ✅ Just implement stack_add_front as specified
- ✅ Understand that pa/pb will use this same linking pattern

---

## Question 3: 42 Norm Violation - More than 5 functions per file

**Problem:** TODO.md asks for 5 functions in Phase 1.2 and 5 more in Phase 1.3, totaling 10 functions in `srcs/stack_utils.c`

### 42 Norm Rule:

**Maximum 5 functions per file** (excluding static helper functions)

### The Fix: Split Into Multiple Files

Here's the corrected file structure:

#### File 1: `srcs/stack_utils.c` (5 functions)
```
1. stack_new          - Create new node
2. stack_size         - Count nodes
3. stack_last         - Find last node
4. stack_add_back     - Add to end
5. stack_add_front    - Add to beginning
```

#### File 2: `srcs/stack_search.c` (4 functions)
```
1. find_min           - Find minimum value
2. find_max           - Find maximum value
3. find_min_index     - Find minimum index
4. find_max_index     - Find maximum index
```

#### File 3: `srcs/stack_check.c` (1 function)
```
1. is_sorted          - Check if stack is sorted
```

OR combine into:

#### File 2: `srcs/stack_find.c` (5 functions)
```
1. find_min           - Find minimum value
2. find_max           - Find maximum value
3. find_min_index     - Find minimum index
4. find_max_index     - Find maximum index
5. is_sorted          - Check if stack is sorted
```

### Recommended Structure:

```
srcs/
├── stack_utils.c      # Basic operations (5 functions)
├── stack_find.c       # Finding/searching operations (5 functions)
├── position.c         # Position assignment (1-2 functions)
├── parser.c           # Parsing functions (5 functions)
├── error.c            # Error handling (2-3 functions)
├── free.c             # Memory cleanup (2 functions)
├── operations_swap.c  # sa, sb, ss (3 functions)
├── operations_push.c  # pa, pb (2 functions)
├── operations_rotate.c    # ra, rb, rr (3 functions)
├── operations_reverse.c   # rra, rrb, rrr (3 functions)
├── sort_small.c       # sort_two, sort_three, sort_four, sort_five (4-5 functions)
├── sort_large.c       # Large sorting algorithm (3-5 functions)
├── cost.c             # Cost calculations (3-5 functions)
├── index.c            # Index normalization (3-4 functions)
├── stack_init.c       # Stack initialization (1-2 functions)
└── main.c             # Main and routing (2-3 functions)
```

### Why This Structure Works:

✅ **No file exceeds 5 functions**
✅ **Logical grouping** - related functions together
✅ **Easy to find** - clear file names
✅ **Norm compliant** - follows all 42 rules
✅ **Maintainable** - organized by functionality

---

## Updated Project Structure

### Corrected Directory Tree:

```
push_swap/
├── Makefile
├── includes/
│   ├── push_swap.h
│   └── push_swap_bonus.h
├── srcs/
│   ├── main.c                  # Entry point (2-3 functions)
│   ├── parser.c                # Argument parsing (5 functions)
│   ├── error.c                 # Error handling (2-3 functions)
│   ├── free.c                  # Memory cleanup (2 functions)
│   ├── stack_utils.c           # Basic utilities (5 functions) ⭐
│   ├── stack_find.c            # Finding operations (5 functions) ⭐
│   ├── stack_init.c            # Initialization (1-2 functions)
│   ├── position.c              # Position assignment (1-2 functions)
│   ├── index.c                 # Index normalization (3-4 functions)
│   ├── operations_swap.c       # Swap operations (3 functions)
│   ├── operations_push.c       # Push operations (2 functions)
│   ├── operations_rotate.c     # Rotate operations (3 functions)
│   ├── operations_reverse.c    # Reverse rotate (3 functions)
│   ├── sort_small.c            # Small sorts (4-5 functions)
│   ├── sort_large.c            # Large algorithm (3-5 functions)
│   └── cost.c                  # Cost calculation (3-5 functions)
├── srcs_bonus/
│   └── (bonus files)
└── libft/
    └── (your libft)
```

**Key changes:**
- ⭐ Split original `stack_utils.c` into two files:
  - `stack_utils.c` (basic operations)
  - `stack_find.c` (search operations)

---

## Impact on README.md

The README.md file structure section needs to be updated to reflect the new file split.

### What Needs to Change:

**Old (in README line 212):**
```
│   ├── stack_utils.c          # Stack utility functions
```

**New:**
```
│   ├── stack_utils.c          # Basic stack operations (new, size, add)
│   ├── stack_find.c           # Stack search functions (min, max, sorted)
```

### Other Files Are Already Correct:

The README already shows proper file separation for operations:
```
│   ├── operations_swap.c      # sa, sb, ss operations
│   ├── operations_push.c      # pa, pb operations
│   ├── operations_rotate.c    # ra, rb, rr operations
│   ├── operations_reverse.c   # rra, rrb, rrr operations
```

These are correctly split (3 functions, 2 functions, 3 functions, 3 functions respectively).

---

## Summary of Changes Needed

### 1. TODO.md Updates:

**Phase 1.2** - Change header:
```
- [ ] Create `srcs/stack_utils.c` (5 functions max)
```

**Phase 1.3** - Change to:
```
### 1.3 Stack Utility Functions - Search Operations
- [ ] Create `srcs/stack_find.c` (5 functions max)
  - [ ] Write `find_min(t_stack *stack)` function
  ...
```

**Phase 1.2, line 91** - Change from task to explanation:
```
- [x] Write `stack_add_back(t_stack **stack, t_stack *new)` function
  - [x] If stack is empty, set *stack = new
  - [x] Else find last node and add new to its next
  - [x] Ensure proper linking (set last->next = new)
```

**Phase 1.2, line 96** - Change from task to explanation:
```
- [x] Write `stack_add_front(t_stack **stack, t_stack *new)` function
  - [x] Set new->next to current *stack
  - [x] Set *stack to new
  (Note: This pattern is used in pa/pb push operations)
```

### 2. README.md Update:

**Line 212** - Update to:
```
│   ├── stack_utils.c          # Basic stack operations (new, size, last, add)
│   ├── stack_find.c           # Stack search (min, max, is_sorted)
```

---

## Quick Reference Card

### Files and Function Limits:

| File | Functions | Status |
|------|-----------|--------|
| stack_utils.c | 5 | ✅ Max reached |
| stack_find.c | 5 | ✅ Max reached |
| operations_swap.c | 3 | ✅ Under limit |
| operations_push.c | 2 | ✅ Under limit |
| operations_rotate.c | 3 | ✅ Under limit |
| operations_reverse.c | 3 | ✅ Under limit |

### Remember:

- ✅ Static helper functions DON'T count toward the 5-function limit
- ✅ You can have multiple files with <5 functions
- ❌ You CANNOT have a file with >5 non-static functions
- ✅ Group related functions logically

---

*These clarifications ensure your project is 42 Norm compliant and well-organized!*
