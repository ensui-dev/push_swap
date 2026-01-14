# assign_position - Assign Current Position to Each Node

## Function Signature

```c
void assign_position(t_stack *stack)
```

**Return type:** `void` - Modifies the stack in place
**Parameter:** `t_stack *stack` - Pointer to the head of the stack

---

## Purpose & Use Case

`assign_position` is a **position-assignment function** that traverses the stack and assigns each node's current position (0, 1, 2, 3, ...) to its `pos` field. This creates a snapshot of where each element currently sits in the stack, which is essential for cost calculations in the Turk algorithm.

### When You'll Use It

You'll call `assign_position` whenever you need to:
1. **Before cost calculation** - Update positions before calculating move costs
2. **After operations** - Refresh positions after pushing/rotating
3. **Turk algorithm** - Maintain accurate position data for optimization
4. **Cost analysis** - Determine how far each element is from the top
5. **Algorithm decision-making** - Choose operations based on current positions

### Why Position Assignment Matters

**The `pos` field stores the current distance from the top:**
```
Stack before assign_position:
Node values: [5, 8, 2, 9, 1]
Node pos:    [?, ?, ?, ?, ?]  ← Uninitialized or outdated

Stack after assign_position:
Node values: [5, 8, 2, 9, 1]
Node pos:    [0, 1, 2, 3, 4]  ← Updated!

Now we can calculate:
- How many rotations to bring node to top
- Whether to use ra (rotate) or rra (reverse rotate)
- Combined costs for moving elements between stacks
```

### Real-World Analogy

**Numbering people in a queue:**
```
Queue at a store:
Person A: "I'm at position 0 (front)"
Person B: "I'm at position 1"
Person C: "I'm at position 2"
Person D: "I'm at position 3"

Now everyone knows:
- How far from the front they are
- How long until their turn
- Whether they're in front half or back half

assign_position does this for stack nodes!
```

---

## Deep Dive: How It Works

### The Sequential Labeling Algorithm

**Concept:**
- Start at the top of the stack (position 0)
- For each node, assign the current position counter to its `pos` field
- Increment the position counter
- Move to the next node
- Repeat until the end of the stack

### Algorithm Visualization

**Stack Example:** [5, 8, 2, 9, 1]

```
Initial state:
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> NULL
pos:   [?]    [?]    [?]    [?]    [?]

Position counter: 0

Step 1: Assign position 0
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> NULL
pos:   [0]    [?]    [?]    [?]    [?]
       ^
       Assigned pos=0

Step 2: Move to next, counter++
Position counter: 1

Step 3: Assign position 1
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> NULL
pos:   [0]    [1]    [?]    [?]    [?]
              ^
              Assigned pos=1

Step 4: Move to next, counter++
Position counter: 2

Step 5: Assign position 2
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> NULL
pos:   [0]    [1]    [2]    [?]    [?]
                     ^
                     Assigned pos=2

Step 6: Move to next, counter++
Position counter: 3

Step 7: Assign position 3
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> NULL
pos:   [0]    [1]    [2]    [3]    [?]
                            ^
                            Assigned pos=3

Step 8: Move to next, counter++
Position counter: 4

Step 9: Assign position 4
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> NULL
pos:   [0]    [1]    [2]    [3]    [4]
                                   ^
                                   Assigned pos=4

Step 10: Move to next
stack = NULL, loop exits

Final result: All positions assigned!
```

### Memory State Visualization

```
Before assign_position:
┌──────────────────┐
│ Node 1           │
│ value: 5         │
│ pos: 0 (old/?)   │ ← May be outdated
│ next: ─────┐     │
└──────────────────┘
               │
               v
┌──────────────────┐
│ Node 2           │
│ value: 8         │
│ pos: 0 (old/?)   │
│ next: ─────┐     │
└──────────────────┘

After assign_position:
┌──────────────────┐
│ Node 1           │
│ value: 5         │
│ pos: 0 ✅        │ ← Correctly assigned
│ next: ─────┐     │
└──────────────────┘
               │
               v
┌──────────────────┐
│ Node 2           │
│ value: 8         │
│ pos: 1 ✅        │ ← Correctly assigned
│ next: ─────┐     │
└──────────────────┘
```

---

## Step-by-Step Implementation

### Step 1: Handle Empty Stack

**Validate input:**
```c
if (!stack)
    return;  // Nothing to do
```

**Why check for NULL:**
```
Empty stack:
- No nodes to assign positions to
- Attempting to access stack->pos would segfault
- Early return prevents crash

Valid optimization:
- Return immediately, no wasted cycles
```

### Step 2: Initialize Position Counter

**Set up tracking:**
```c
int pos = 0;
```

**Starting point:**
```
Position 0 = top of stack (head)
- First node is always at position 0
- Each subsequent node increments by 1
- Position represents "distance from top"
```

### Step 3: Traverse and Assign

**Main loop:**
```c
while (stack)
{
    stack->pos = pos;  // Assign current position
    pos++;             // Increment for next node
    stack = stack->next;  // Move to next node
}
```

**Loop mechanics:**
```
For each node:
1. Assign current position counter to node->pos
2. Increment position counter
3. Move to next node
4. Repeat until NULL

Simple, efficient, O(n) traversal
```

---

## Complete Algorithm Pseudocode

```
FUNCTION assign_position(stack):
    // Step 1: Validate input
    IF stack is NULL:
        RETURN  // Nothing to do

    // Step 2: Initialize position counter
    pos = 0

    // Step 3: Traverse and assign positions
    WHILE stack is not NULL:
        stack.pos = pos      // Assign current position
        pos = pos + 1        // Increment counter
        stack = stack.next   // Move to next node

    // Done! All positions assigned
END FUNCTION
```

---

## Visual Execution Trace

### Example: Assigning Positions to [5, 8, 2, 9, 1]

```
Initial State:
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> NULL
pos:   [?]    [?]    [?]    [?]    [?]

Call: assign_position(stack)

Step 1: Validate
stack != NULL ✅ Continue

Step 2: Initialize
pos = 0

Step 3: Loop

Iteration 1:
  Current node: [5]
  Assign: node->pos = 0
  Increment: pos++ → pos=1
  Move: stack = stack->next → [8]

Iteration 2:
  Current node: [8]
  Assign: node->pos = 1
  Increment: pos++ → pos=2
  Move: stack = stack->next → [2]

Iteration 3:
  Current node: [2]
  Assign: node->pos = 2
  Increment: pos++ → pos=3
  Move: stack = stack->next → [9]

Iteration 4:
  Current node: [9]
  Assign: node->pos = 3
  Increment: pos++ → pos=4
  Move: stack = stack->next → [1]

Iteration 5:
  Current node: [1]
  Assign: node->pos = 4
  Increment: pos++ → pos=5
  Move: stack = stack->next → NULL

Loop exits (stack is NULL)

Final State:
Stack: [5] -> [8] -> [2] -> [9] -> [1] -> NULL
pos:   [0]    [1]    [2]    [3]    [4]  ✅ All assigned!
```

---

## Edge Cases

### Case 1: Empty Stack

```c
t_stack *stack = NULL;

assign_position(stack);

// Result: Function returns immediately
// No crash ✅
```

### Case 2: Single Element

```c
// Stack: [42] -> NULL
// pos:   [?]

assign_position(stack);

// Process:
// pos = 0
// stack->pos = 0
// stack = stack->next = NULL
// Loop exits

// Result:
// Stack: [42] -> NULL
// pos:   [0]  ✅
```

### Case 3: Two Elements

```c
// Stack: [5, 8]
// pos:   [?, ?]

assign_position(stack);

// Result:
// Stack: [5, 8]
// pos:   [0, 1]  ✅
```

### Case 4: Large Stack

```c
// Stack: [1, 2, 3, ..., 100]
// pos:   [?, ?, ?, ..., ?]

assign_position(stack);

// Result:
// Stack: [1, 2, 3, ..., 100]
// pos:   [0, 1, 2, ..., 99]  ✅
// All 100 positions correctly assigned
```

### Case 5: After Rotation

```c
// Original:
// Stack: [5, 8, 2]
// pos:   [0, 1, 2]

// After ra (rotate):
// Stack: [8, 2, 5]  ← Elements moved!
// pos:   [0, 1, 2]  ← Positions now WRONG!

// Need to reassign:
assign_position(stack);

// Result:
// Stack: [8, 2, 5]
// pos:   [0, 1, 2]  ✅ Now correct for new order
```

### Case 6: After Push Operation

```c
// Stack A: [5, 8, 2]
// pos:     [0, 1, 2]

// Stack B: [9]
// pos:     [0]

// After pb (push to B):
// Stack A: [8, 2]  ← Top element removed
// pos:     [1, 2]  ← Positions now WRONG!

// Stack B: [5, 9]  ← New element added
// pos:     [0, 0]  ← Position wrong for second element!

// Reassign both stacks:
assign_position(stack_a);
assign_position(stack_b);

// Result:
// Stack A: [8, 2]
// pos:     [0, 1]  ✅

// Stack B: [5, 9]
// pos:     [0, 1]  ✅
```

---

## Time & Space Complexity

### Time Complexity: **O(n)** - Linear Time

**Single pass through stack:**
```
n = number of nodes in stack

Operations per node:
- Assign position: O(1)
- Increment counter: O(1)
- Move to next: O(1)

Total: n nodes × O(1) = O(n)
```

**Performance:**
```
Small stack (3 elements): 3 assignments
Medium stack (50 elements): 50 assignments
Large stack (500 elements): 500 assignments

Linear growth - efficient! ✅
```

### Space Complexity: **O(1)** - Constant Space

**Memory used:**
```
Variables:
- int pos (4 bytes)
- t_stack *stack (8 bytes on 64-bit)

Total: 12 bytes, regardless of stack size

Modifies existing nodes in place
No additional data structures
No recursion
No allocations

Space = O(1) ✅
```

---

## Relationship with Other Functions

### Used Before calculate_cost

```c
void calculate_cost(t_stack *stack_a, t_stack *stack_b)
{
    // CRITICAL: Must assign positions first!
    assign_position(stack_a);  // ← Update positions
    assign_position(stack_b);  // ← Update positions

    // Now calculate costs using accurate positions
    t_stack *b = stack_b;
    while (b)
    {
        // Use b->pos to calculate rotation cost
        // Use target position in A to calculate cost
        // ...
        b = b->next;
    }
}
```

### Updated After Operations

```c
void execute_move(t_stack **a, t_stack **b)
{
    // Perform operations
    ra(a, 1);
    rb(b, 1);
    pa(a, b, 1);

    // IMPORTANT: Positions are now outdated!
    // Must reassign before next cost calculation
    assign_position(*a);  // ← Update
    assign_position(*b);  // ← Update
}
```

### Enables Cost Optimization

```c
// Calculate rotation cost for element at position pos
int calculate_rotation_cost(t_stack *stack, int pos)
{
    int size = stack_size(stack);

    // Use assigned position to calculate cost
    int rotate_cost = pos;              // ra operations
    int reverse_cost = size - pos;      // rra operations

    // Return cheapest
    if (rotate_cost <= reverse_cost)
        return (rotate_cost);
    else
        return (-reverse_cost);  // Negative = reverse rotation
}

// This function depends on accurate pos values!
// assign_position must be called first
```

### Critical for Turk Algorithm

```c
void turk_algorithm(t_stack **a, t_stack **b)
{
    while (*b)
    {
        // Step 1: Update positions (CRITICAL!)
        assign_position(*a);
        assign_position(*b);

        // Step 2: Calculate costs using accurate positions
        calculate_cost(*a, *b);

        // Step 3: Find cheapest move
        t_stack *cheapest = find_cheapest(*b);

        // Step 4: Execute move
        execute_cheapest_move(a, b, cheapest);

        // Loop back - positions need updating again!
    }
}
```

---

## Integration with Push_swap

### Scenario: Before Cost Calculation

```c
// Stack A: [3, 7, 5, 9, 2]
// Stack B: [8, 1, 6]

// Before calculating costs, update positions:
assign_position(stack_a);
assign_position(stack_b);

// Now accurate:
// Stack A positions: [0, 1, 2, 3, 4]
// Stack B positions: [0, 1, 2]

// Can now correctly calculate:
// - How far each element is from top
// - Cost to rotate element to top
// - Combined costs for optimal moves
```

### Scenario: After Multiple Operations

```c
// Initial:
// A: [5, 8, 2]  pos: [0, 1, 2]
// B: [9]        pos: [0]

// Operation 1: ra (rotate A)
ra(&stack_a, 1);
// A: [8, 2, 5]  pos: [0, 1, 2] ← Still says [0,1,2] but order changed!

// Operation 2: pb (push to B)
pb(&stack_a, &stack_b, 1);
// A: [2, 5]     pos: [1, 2] ← WRONG! Should be [0, 1]
// B: [8, 9]     pos: [0, 0] ← WRONG! Should be [0, 1]

// Solution: Reassign after operations
assign_position(stack_a);
assign_position(stack_b);

// Now correct:
// A: [2, 5]     pos: [0, 1] ✅
// B: [8, 9]     pos: [0, 1] ✅
```

### Scenario: Cost Calculation Example

```c
// Stack B: [8, 1, 6]
assign_position(stack_b);
// Positions: [0, 1, 2]

// For element at pos=2 (value 6):
int size = stack_size(stack_b);  // 3
int pos = 2;

// Calculate rotation costs:
int ra_cost = pos;           // 2 operations (rotate up)
int rra_cost = size - pos;   // 1 operation (rotate down) ✅ Cheaper!

// Choose rra (reverse rotate) because 1 < 2
// This optimization is only possible with accurate positions!
```

---

## 42 Norm Considerations

### Function Structure

```c
void	assign_position(t_stack *stack)
{
	int	pos;

	if (!stack)
		return ;
	pos = 0;
	while (stack)
	{
		stack->pos = pos;
		pos++;
		stack = stack->next;
	}
}
```

**Norm compliance:**
- ✅ Under 25 lines
- ✅ Single responsibility: assigns positions
- ✅ Only 1 variable (pos)
- ✅ No line over 80 characters
- ✅ Tabs for indentation
- ✅ Simple, readable logic

### Variable Naming

```c
✅ GOOD: pos, stack
❌ BAD: position_counter, current_stack_node
```

Short and clear!

---

## Common Mistakes

### Mistake 1: Not Handling NULL

```c
// ❌ WRONG
void assign_position(t_stack *stack)
{
    int pos = 0;
    while (stack)  // If stack is NULL, this is fine
    {
        stack->pos = pos;  // But if called with NULL, undefined behavior
        // ...
    }
}
```

**✅ Correct:**
```c
if (!stack)
    return;  // Explicit NULL check
int pos = 0;
// ... rest of code
```

### Mistake 2: Starting Position at 1

```c
// ❌ WRONG
int pos = 1;  // Positions should be 0-based!
while (stack)
{
    stack->pos = pos;
    pos++;
    // ...
}
// First element gets pos=1 instead of pos=0
```

**✅ Correct:**
```c
int pos = 0;  // Start at 0
```

### Mistake 3: Incrementing Before Assigning

```c
// ❌ WRONG
int pos = 0;
while (stack)
{
    pos++;  // Increment first
    stack->pos = pos;  // Assign second
    // ...
}
// First element gets pos=1, second gets pos=2, etc. (off by 1)
```

**✅ Correct:**
```c
while (stack)
{
    stack->pos = pos;  // Assign first
    pos++;             // Increment second
    // ...
}
```

### Mistake 4: Not Advancing Pointer

```c
// ❌ WRONG - Infinite loop!
while (stack)
{
    stack->pos = pos;
    pos++;
    // Forgot: stack = stack->next;
}
// Loop never exits!
```

**✅ Correct:**
```c
while (stack)
{
    stack->pos = pos;
    pos++;
    stack = stack->next;  // CRITICAL!
}
```

### Mistake 5: Forgetting to Reassign After Operations

```c
// ❌ WRONG
assign_position(stack_a);
assign_position(stack_b);

// Perform operations
ra(&stack_a, 1);
pb(&stack_a, &stack_b, 1);

// Now calculate costs
calculate_cost(stack_a, stack_b);  // Using OUTDATED positions!
```

**✅ Correct:**
```c
// Reassign AFTER operations, BEFORE cost calculation
ra(&stack_a, 1);
pb(&stack_a, &stack_b, 1);

assign_position(stack_a);  // Update!
assign_position(stack_b);  // Update!

calculate_cost(stack_a, stack_b);  // Now using correct positions ✅
```

---

## Testing Strategy

### Test 1: Basic Assignment

```c
// Create stack
stack = create_stack([5, 8, 2]);

// Assign positions
assign_position(stack);

// Verify
assert(stack->pos == 0);
assert(stack->next->pos == 1);
assert(stack->next->next->pos == 2);
```

### Test 2: Edge Cases

```c
// Empty stack
assign_position(NULL);  // Should not crash

// Single element
stack = create_stack([42]);
assign_position(stack);
assert(stack->pos == 0);

// Two elements
stack = create_stack([5, 8]);
assign_position(stack);
assert(stack->pos == 0);
assert(stack->next->pos == 1);
```

### Test 3: After Operations

```c
// Initial
stack = create_stack([5, 8, 2]);
assign_position(stack);
// Positions: [0, 1, 2]

// Rotate
ra(&stack, 1);  // Stack now: [8, 2, 5]

// Reassign
assign_position(stack);

// Verify positions are correct for new order
assert(stack->pos == 0);        // 8 is now at pos 0
assert(stack->next->pos == 1);  // 2 is now at pos 1
assert(stack->next->next->pos == 2);  // 5 is now at pos 2
```

### Test 4: Large Stack

```c
// 100 elements
stack = create_stack_size(100);
assign_position(stack);

// Verify all positions
t_stack *temp = stack;
int expected_pos = 0;
while (temp)
{
    assert(temp->pos == expected_pos);
    expected_pos++;
    temp = temp->next;
}
assert(expected_pos == 100);  // All 100 assigned
```

### Test 5: Multiple Reassignments

```c
stack = create_stack([5, 8, 2, 9]);

// Assign
assign_position(stack);
assert(stack->pos == 0);

// Modify stack
ra(&stack, 1);

// Reassign
assign_position(stack);
assert(stack->pos == 0);  // New top at pos 0

// Modify again
rra(&stack, 1);

// Reassign again
assign_position(stack);
assert(stack->pos == 0);  // Back to original top at pos 0
```

---

## Summary

**What assign_position Does:**
1. Traverses stack once (O(n))
2. Assigns sequential positions (0, 1, 2, ...) to each node's pos field
3. Creates snapshot of current element positions
4. Enables accurate cost calculations

**Key Characteristics:**
- ✅ Simple sequential assignment
- ✅ O(n) time, O(1) space
- ✅ Modifies nodes in place
- ✅ Must be called after operations
- ✅ Critical for cost calculation accuracy

**Critical Uses:**
- Before cost calculation in Turk algorithm
- After any stack-modifying operations
- Enabling rotation cost optimization
- Determining ra vs rra decisions

**Remember:**
- Always call before calculating costs
- Always call after stack operations
- Positions are 0-based (start at 0)
- Simple but absolutely critical function
- Outdated positions = wrong costs = suboptimal sorting

**Integration Pattern:**
```
1. Perform operations (ra, pb, etc.)
2. assign_position() ← Update positions
3. calculate_cost() ← Uses accurate positions
4. Execute cheapest move
5. Repeat
```

---

## Location in Project

**File:** `srcs/position.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 2.4 (Position and Cost Calculation)

---

## Related Functions

- [calculate_cost](calculate_cost.md) - Uses pos field for cost calculation
- [find_min_index](find_min_index.md) - Different: finds specific value's position
- [find_max_index](find_max_index.md) - Different: finds specific value's position
- [calculate_move_cost](calculate_move_cost.md) - Uses pos for rotation cost
- [find_cheapest](find_cheapest.md) - Relies on accurate cost calculations
- [turk_algorithm](turk_algorithm.md) - Calls assign_position repeatedly

---

*Simple but absolutely essential - assign_position is the foundation of accurate cost calculation in the Turk algorithm!*
