# stack_new - Stack Node Constructor Function

## Function Signature

```c
t_stack *stack_new(int value)
```

**Return type:** `t_stack *` - Pointer to newly created stack node (or NULL on failure)
**Parameter:** `int value` - The integer value to store in the node

---

## Purpose & Use Case

`stack_new` is a **factory function** (also called a constructor function) that creates a single new node for your stack linked list. Think of it as a "node maker" - every time you need a new element in your stack, you call this function.

### When You'll Use It

You'll call `stack_new` whenever you need to:
1. **Parse input** - Each number from command line becomes a node
2. **Initialize stack A** - Converting `./push_swap 5 3 1` into three nodes
3. **Any operation that needs a new node** (though in push_swap, you mainly create nodes during initialization)

---

## Deep Dive: How It Works

### Step 1: Memory Allocation

First, the function needs to **reserve space in memory** for a new node.

**Conceptual Process:**
- Your program asks the operating system: "Hey, can I have enough memory to store one `t_stack` structure?"
- The OS finds a free spot in the heap (dynamic memory area)
- It returns the address of that memory location
- You store this address in a pointer variable

**Memory Layout:**
```
Before allocation:
HEAP: [... free memory ...]

After allocation:
HEAP: [... | YOUR_NODE_HERE (uninitialized) | free memory ...]
            ^
            pointer points here
```

**Size calculation:**
- The system calculates: `sizeof(t_stack)`
- For your structure with 6 fields (int value, int index, int pos, int target_pos, int cost_a, int cost_b, pointer next)
- This is typically: 4+4+4+4+4+4+8 = 32 bytes (on 64-bit system)
- Note: actual size may vary due to padding/alignment

### Step 2: Check Allocation Success

**Critical security step:** What if the OS couldn't give you memory?

**Scenarios where allocation fails:**
- System is out of memory
- Memory fragmentation issues
- Operating system limits reached

**What to check:**
- After requesting memory, you receive a pointer
- If allocation failed, this pointer is `NULL` (address 0x0)
- You MUST check if pointer is NULL before using it
- If NULL, you cannot continue - you must return NULL to signal failure

**Memory safety:**
```
If malloc succeeded:
  pointer = valid address (e.g., 0x7fff5fbff8e0)
  ✅ Safe to use

If malloc failed:
  pointer = NULL (0x0)
  ❌ DO NOT DEREFERENCE! Return NULL immediately
```

### Step 3: Initialize the Structure Fields

Now you have raw memory, but it contains **garbage values** (whatever was there before).

**The memory contains random data:**
```
Allocated memory (uninitialized):
[45A3B2C1][7F8E9012][00000001][FFFFFFFF][12345678][9ABCDEF0][00007FFF]
  value     index      pos     target_pos  cost_a    cost_b     next
  (random)  (random)  (random) (random)   (random)  (random)  (random)
```

**You must initialize each field:**

#### Field 1: `value`
- **Set to:** The integer parameter passed to the function
- **Purpose:** Store the actual number from command line
- **Example:** If user typed `./push_swap 42`, this field = 42

#### Field 2: `index`
- **Set to:** -1 (or any invalid marker)
- **Purpose:** Will be filled later during index normalization phase
- **Why -1:** Indicates "not yet assigned" since valid indices are 0, 1, 2, ...

#### Field 3: `pos`
- **Set to:** 0 (initial position)
- **Purpose:** Will be updated when calculating costs
- **Why 0:** Default starting position before it's placed in stack

#### Field 4: `target_pos`
- **Set to:** 0 (no target yet)
- **Purpose:** Used in Turk algorithm to find where element should go in other stack
- **Why 0:** Not needed until sorting algorithm runs

#### Field 5: `cost_a`
- **Set to:** 0 (no cost calculated yet)
- **Purpose:** Number of operations needed to move element to top of stack A
- **Why 0:** Cost is calculated later during sorting

#### Field 6: `cost_b`
- **Set to:** 0 (no cost calculated yet)
- **Purpose:** Number of operations needed to move element to top of stack B
- **Why 0:** Cost is calculated later during sorting

#### Field 7: `next`
- **Set to:** `NULL` (end of list marker)
- **Purpose:** Points to the next node in linked list
- **Why NULL:** This node is standalone initially; gets linked later

**After initialization:**
```
Initialized memory:
[00000042][-1      ][00000000][00000000][00000000][00000000][00000000]
  value=42  index=-1  pos=0    target=0   cost_a=0  cost_b=0   next=NULL
```

### Step 4: Return the Node

**Final step:** Give back the pointer to this newly created, initialized node.

**What happens:**
- The function returns the memory address
- Calling function receives this pointer
- Calling function can now use this node

---

## Real-World Example: Creating a Node

Let's trace through creating a node for the value `42`:

### Before Calling `stack_new(42)`
```
Stack A: (empty)
Memory:  [free heap space]
```

### During `stack_new(42)` Execution

**Step 1: Allocate**
```
Request: "Give me sizeof(t_stack) bytes"
OS Response: "Here's memory at address 0x7fff5fbff8e0"
```

**Step 2: Check Success**
```
Is pointer NULL?
→ No, it's 0x7fff5fbff8e0
→ Proceed
```

**Step 3: Initialize**
```
Memory at 0x7fff5fbff8e0:

Offset +0:  value = 42         (parameter passed in)
Offset +4:  index = -1         (not assigned yet)
Offset +8:  pos = 0            (default position)
Offset +12: target_pos = 0     (no target yet)
Offset +16: cost_a = 0         (no cost calculated)
Offset +20: cost_b = 0         (no cost calculated)
Offset +24: next = NULL        (not linked yet)
```

**Step 4: Return**
```
Return: 0x7fff5fbff8e0 (address of the new node)
```

### After Calling `stack_new(42)`
```
Calling code now has:
t_stack *node = [address to initialized node]

Can access:
node->value       = 42
node->index       = -1
node->pos         = 0
node->target_pos  = 0
node->cost_a      = 0
node->cost_b      = 0
node->next        = NULL
```

---

## Error Handling Detail

### Why Check for NULL?

**Scenario 1: Success Path**
```
malloc returns valid address
↓
Initialize all fields
↓
Return address to caller
↓
Caller can use the node ✅
```

**Scenario 2: Failure Path**
```
malloc returns NULL (allocation failed)
↓
Immediately return NULL
↓
Caller receives NULL
↓
Caller must handle error (free memory, print error, exit) ✅
```

**What if you DON'T check?**
```
malloc returns NULL (allocation failed)
↓
Try to initialize fields: node->value = 42
↓
SEGMENTATION FAULT 💥 (dereferencing NULL pointer)
↓
Program crashes ❌
```

---

## Integration Example: How It's Used

### Scenario: Parsing `./push_swap 5 3 1`

**Step 1: Parse first number (5)**
```
1. Call: node1 = stack_new(5)
2. Node created with value=5, all other fields initialized
3. Add node1 to stack A
```

**Step 2: Parse second number (3)**
```
1. Call: node2 = stack_new(3)
2. Node created with value=3
3. Add node2 to stack A
4. Link: node1->next = node2 (or node2->next = node1, depending on order)
```

**Step 3: Parse third number (1)**
```
1. Call: node3 = stack_new(1)
2. Node created with value=1
3. Add node3 to stack A
4. Link appropriately
```

**Result:**
```
Stack A structure:
[node1: value=5] -> [node2: value=3] -> [node3: value=1] -> NULL

Each node was created by stack_new()!
```

---

## Memory Management Implications

### Allocation
- Each call to `stack_new` allocates ~32 bytes (one node)
- For 100 numbers: 100 × 32 = 3,200 bytes
- For 500 numbers: 500 × 32 = 16,000 bytes
- This is heap memory - stays until you explicitly free it

### Responsibility
**Important:** `stack_new` allocates memory, but:
- Caller is responsible for freeing it later
- You'll write `free_stack()` to clean up
- Every allocated node MUST be freed before program ends
- Memory leaks = failing the project ❌

---

## Common Mistakes to Avoid

### Mistake 1: Not Checking malloc Return
```c
❌ WRONG:
new = malloc(size)
new->value = 42  // CRASH if malloc failed!
```

### Mistake 2: Not Initializing All Fields
```c
❌ WRONG:
new->value = 42
// Forgot to initialize other fields
// They contain garbage values!
```

### Mistake 3: Not Setting `next` to NULL
```c
❌ WRONG:
new->next = [uninitialized]
// Later: while (node->next) will loop forever!
```

### Mistake 4: Returning Uninitialized Memory
```c
❌ WRONG:
new = malloc(size)
return new  // Fields contain garbage!
```

---

## Why This Design?

### Encapsulation
- Creating nodes is always done the same way
- One function = one place to maintain/debug
- Ensures consistency across codebase

### Safety
- Centralizes error checking
- Guarantees proper initialization
- Prevents uninitialized memory bugs

### Simplicity
- Caller doesn't need to know initialization details
- Just call: `node = stack_new(value)`
- Clean, readable code

---

## Function Signature Breakdown

```c
t_stack *stack_new(int value)
```

**Return type:** `t_stack *`
- Returns a pointer to a `t_stack` structure
- Can return NULL on failure
- Caller must store this pointer to access the node

**Function name:** `stack_new`
- Naming convention: `stack_` prefix for all stack functions
- `new` indicates it creates a new object

**Parameter:** `int value`
- The only data you need at creation time
- All other fields are initialized to defaults
- Can be any integer (negative, positive, zero)

---

## Implementation Pseudocode

```
FUNCTION stack_new(value):
    // Step 1: Allocate memory
    new_node = allocate memory of size(t_stack)

    // Step 2: Check if allocation succeeded
    IF new_node is NULL:
        RETURN NULL  // Allocation failed

    // Step 3: Initialize all fields
    new_node.value = value         // Store the parameter
    new_node.index = -1            // Not assigned yet
    new_node.pos = 0               // Default position
    new_node.target_pos = 0        // No target yet
    new_node.cost_a = 0            // No cost calculated
    new_node.cost_b = 0            // No cost calculated
    new_node.next = NULL           // Not linked yet

    // Step 4: Return the initialized node
    RETURN new_node
END FUNCTION
```

---

## 42 Norm Considerations

When implementing this function:

✅ **Keep it simple** - This function should be well under 25 lines
✅ **Single responsibility** - Only creates and initializes a node
✅ **No global variables** - Everything is local or passed as parameter
✅ **Error handling** - Return NULL on malloc failure
✅ **Proper initialization** - Set all fields explicitly
✅ **Return value** - Always return pointer or NULL

---

## Testing Strategy

### Test Cases to Verify

1. **Normal case:**
   ```c
   t_stack *node = stack_new(42);
   // Check: node != NULL
   // Check: node->value == 42
   // Check: node->index == -1
   // Check: node->next == NULL
   ```

2. **Edge values:**
   ```c
   stack_new(0);           // Zero
   stack_new(-2147483648); // INT_MIN
   stack_new(2147483647);  // INT_MAX
   stack_new(-1);          // Negative
   ```

3. **Memory leak check:**
   ```c
   t_stack *node = stack_new(42);
   free(node);  // Must be able to free
   // Run with valgrind: no leaks
   ```

4. **NULL handling:**
   ```c
   // Simulate malloc failure (difficult to test directly)
   // But code should handle NULL return gracefully
   ```

---

## Summary: What `stack_new` Does

1. **Allocates** memory for one `t_stack` node
2. **Checks** if allocation succeeded
3. **Initializes** all fields with appropriate values
4. **Returns** pointer to the new node (or NULL on failure)

**It's the foundation of your stack data structure!** Every node in your linked list stacks starts life by being created with this function.

---

## Related Functions

- **stack_add_back()** - Adds this node to end of stack
- **stack_add_front()** - Adds this node to beginning of stack
- **free_stack()** - Frees memory allocated by stack_new
- **stack_last()** - Finds last node in list
- **stack_size()** - Counts nodes created with stack_new

---

## Location in Project

**File:** `srcs/stack_utils.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 1.2 (Stack Utility Functions - Basic Operations)

---

*This function is your first building block. Master it, and the rest of the project becomes much easier!*
