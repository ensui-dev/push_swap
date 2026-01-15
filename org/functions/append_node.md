# append_node - Validate, Convert, and Add Single Node to Stack (Static Helper)

## Function Signature

```c
static t_stack *append_node(t_stack **stack, char *str)
```

**IMPORTANT:** This is a **STATIC helper function** - not declared in header file!

**Return type:** `t_stack *` - Pointer to newly created node, or NULL on error
**Parameters:**
- `t_stack **stack` - Double pointer to stack to add node to
- `char *str` - Number string to validate, convert, and add

**Visibility:** File-scope only (static) - internal to `stack_init.c`

---

## Purpose & Use Case

`append_node` is a **static helper function** that encapsulates the complete process of adding a single validated number to the stack. It combines validation, conversion, range checking, node creation, and stack addition into one clean, reusable function.

### When You'll Use It

This function is called internally by `build_stack` to:
1. **Validate** the number string format
2. **Convert** the string to a long integer
3. **Check** the value fits in int range
4. **Create** a new stack node
5. **Add** the node to the end of the stack

### Why This Matters

**The Problem (Without Helper):**
```c
// In build_stack - REPEATED for each validation step!
while (numbers[i])
{
    if (!is_valid_number(numbers[i]))
    {
        free_stack(&stack);
        return (NULL);
    }
    value = ft_atol(numbers[i]);
    if (!is_int_range(value))
    {
        free_stack(&stack);
        return (NULL);
    }
    node = stack_new((int)value);
    if (!node)
    {
        free_stack(&stack);
        return (NULL);
    }
    stack_add_back(&stack, node);
    i++;
}
// Function exceeds 25 lines!
// 42 Norm VIOLATION!
```

**The Solution (With Helper):**
```c
// Clean, simple loop
while (numbers[i])
{
    if (!append_node(&stack, numbers[i]))
    {
        free_stack(&stack);
        return (NULL);
    }
    i++;
}
// Function stays under 25 lines
// 42 Norm COMPLIANT!
```

---

## Deep Dive: How It Works

### The Core Logic

```
append_node(stack, str):
    1. Validate string format (is_valid_number)
    2. Convert to long (ft_atol)
    3. Check integer range (is_int_range)
    4. Create node (stack_new)
    5. Add to stack (stack_add_back)
    6. Return node pointer (or NULL on any failure)
```

### Why Return t_stack*?

**Return value strategy:**
- NULL: Any validation or creation failed
- Non-NULL: Node successfully created and added

```c
// Caller can easily check success:
if (!append_node(&stack, str))
{
    // Handle error
}
// On success, node is already in stack
```

### Step-by-Step Process

#### Step 1: Validate Number Format

```c
if (!is_valid_number(str))
    return (NULL);
```

**What is_valid_number checks:**
- Optional leading sign (+/-)
- All remaining characters are digits
- Not empty string
- No invalid characters

**Examples:**
```
"42"     -> valid
"-42"    -> valid
"+42"    -> valid
"42a"    -> INVALID (non-digit)
"abc"    -> INVALID (no digits)
""       -> INVALID (empty)
"--42"   -> INVALID (multiple signs)
```

#### Step 2: Convert String to Long

```c
value = ft_atol(str);
```

**Why long instead of int?**
- Need to detect overflow before casting
- long can hold values outside int range
- Allows proper range checking in next step

**Example:**
```
"2147483647"  -> 2147483647L (INT_MAX, valid)
"2147483648"  -> 2147483648L (INT_MAX + 1, will fail range check)
"-2147483649" -> -2147483649L (INT_MIN - 1, will fail range check)
```

#### Step 3: Check Integer Range

```c
if (!is_int_range(value))
    return (NULL);
```

**Range check:**
```
Valid range: INT_MIN to INT_MAX
             -2147483648 to 2147483647

is_int_range checks:
value >= INT_MIN && value <= INT_MAX
```

#### Step 4: Create Stack Node

```c
node = stack_new((int)value);
if (!node)
    return (NULL);
```

**What stack_new does:**
- Allocates memory for t_stack node
- Initializes value field
- Initializes index to -1
- Sets next to NULL
- Returns NULL if malloc fails

**Cast safety:**
- We already verified value is in int range
- Cast from long to int is safe

#### Step 5: Add Node to Stack

```c
stack_add_back(stack, node);
return (node);
```

**What stack_add_back does:**
- If stack is empty: node becomes head
- Otherwise: finds last node, links new node

**Return value:**
- Returns the newly created node
- Allows caller to know operation succeeded

---

## Visual Execution Trace

### Example 1: Valid Number

```
Input: append_node(&stack, "42")
stack before: [5] -> [3] -> NULL

Step 1: Validate
is_valid_number("42")? -> YES
"42" contains only digits, valid format

Step 2: Convert
value = ft_atol("42")
value = 42L

Step 3: Range Check
is_int_range(42L)? -> YES
-2147483648 <= 42 <= 2147483647

Step 4: Create Node
node = stack_new(42)
node = [value:42, index:-1, next:NULL]

Step 5: Add to Stack
stack_add_back(&stack, node)
stack = [5] -> [3] -> [42] -> NULL

Return: node (success!)
```

### Example 2: Invalid Number Format

```
Input: append_node(&stack, "42abc")
stack before: [5] -> [3] -> NULL

Step 1: Validate
is_valid_number("42abc")? -> NO!
Contains non-digit character 'a'

Return: NULL (error)

stack after: [5] -> [3] -> NULL (unchanged)
```

### Example 3: Integer Overflow

```
Input: append_node(&stack, "9999999999")
stack before: [5] -> NULL

Step 1: Validate
is_valid_number("9999999999")? -> YES
All digits, valid format

Step 2: Convert
value = ft_atol("9999999999")
value = 9999999999L

Step 3: Range Check
is_int_range(9999999999L)? -> NO!
9999999999 > INT_MAX (2147483647)

Return: NULL (error)

stack after: [5] -> NULL (unchanged)
```

### Example 4: Malloc Failure

```
Input: append_node(&stack, "42")
stack before: [5] -> NULL
Scenario: malloc fails in stack_new

Step 1: Validate
is_valid_number("42")? -> YES

Step 2: Convert
value = ft_atol("42")
value = 42L

Step 3: Range Check
is_int_range(42L)? -> YES

Step 4: Create Node
node = stack_new(42)
-> malloc fails inside stack_new
node = NULL

Return: NULL (error)

stack after: [5] -> NULL (unchanged)
```

---

## Complete Algorithm Pseudocode

### High-Level Overview

```
FUNCTION append_node(stack, str):
    // Step 1: Validate format
    IF NOT is_valid_number(str):
        RETURN NULL

    // Step 2: Convert to long
    value = ft_atol(str)

    // Step 3: Check range
    IF NOT is_int_range(value):
        RETURN NULL

    // Step 4: Create node
    node = stack_new((int)value)
    IF node is NULL:
        RETURN NULL

    // Step 5: Add to stack and return
    stack_add_back(stack, node)
    RETURN node
END FUNCTION
```

### Detailed Implementation

```
FUNCTION append_node(stack, str):
    DECLARE value AS long
    DECLARE node AS pointer to t_stack

    // Validate: Check number string format
    IF is_valid_number(str) returns false:
        // Invalid format (non-digits, empty, etc.)
        RETURN NULL

    // Convert: String to long integer
    value = ft_atol(str)

    // Range: Verify value fits in int type
    IF is_int_range(value) returns false:
        // Overflow or underflow
        RETURN NULL

    // Create: Allocate and initialize node
    node = stack_new(cast value to int)
    IF node equals NULL:
        // Memory allocation failed
        RETURN NULL

    // Add: Append node to end of stack
    stack_add_back(stack, node)

    // Success: Return the new node
    RETURN node
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: Empty String

```c
t_stack *result = append_node(&stack, "");
// is_valid_number("") returns 0
// result = NULL
```

**Handling:** is_valid_number rejects empty strings.

### Edge Case 2: Sign Only

```c
t_stack *result = append_node(&stack, "-");
// is_valid_number("-") returns 0
// result = NULL
```

**Handling:** is_valid_number requires digits after sign.

### Edge Case 3: INT_MIN Boundary

```c
t_stack *result = append_node(&stack, "-2147483648");
// is_valid_number("-2147483648") -> valid format
// ft_atol("-2147483648") -> -2147483648L
// is_int_range(-2147483648L) -> true (equals INT_MIN)
// result = valid node
```

**Handling:** INT_MIN is a valid value.

### Edge Case 4: INT_MAX Boundary

```c
t_stack *result = append_node(&stack, "2147483647");
// is_valid_number("2147483647") -> valid format
// ft_atol("2147483647") -> 2147483647L
// is_int_range(2147483647L) -> true (equals INT_MAX)
// result = valid node
```

**Handling:** INT_MAX is a valid value.

### Edge Case 5: Leading Plus Sign

```c
t_stack *result = append_node(&stack, "+42");
// is_valid_number("+42") -> depends on implementation
// Typically valid (optional sign)
// result = valid node with value 42
```

**Handling:** Depends on is_valid_number implementation.

### Edge Case 6: NULL Stack

```c
t_stack *stack = NULL;
t_stack *result = append_node(&stack, "42");
// Creates first node in stack
// stack = [42] -> NULL
// result = valid node
```

**Handling:** stack_add_back handles NULL stack correctly.

---

## Time & Space Complexity

### Time Complexity: O(m + n)

```
m = length of string str
n = current size of stack

Operations:
- is_valid_number: O(m) - scan string once
- ft_atol: O(m) - scan string once
- is_int_range: O(1) - simple comparison
- stack_new: O(1) - single allocation
- stack_add_back: O(n) - traverse to end of stack

Total: O(m + n)
```

### Space Complexity: O(1)

```
Memory used:
- value (long): O(1)
- node (pointer): O(1)
- Node allocation: O(1) - fixed size struct

Total: O(1) additional space
(Note: The node itself is O(1) and returned to caller)
```

---

## Relationship with Other Functions

### Functions Called By append_node

1. **is_valid_number()** - Validates string format
2. **ft_atol()** - Converts string to long
3. **is_int_range()** - Checks value fits in int
4. **stack_new()** - Creates node
5. **stack_add_back()** - Adds node to stack

### Functions That Call append_node

1. **build_stack()** - Calls for each number in array

---

## Integration with Push_swap

### Usage in build_stack()

```c
static t_stack *build_stack(char **numbers)
{
    t_stack *stack;
    int     i;

    stack = NULL;
    i = 0;
    while (numbers[i])
    {
        if (!append_node(&stack, numbers[i]))  // <-- Used here
        {
            free_stack(&stack);
            return (NULL);
        }
        i++;
    }
    if (has_duplicates(stack))
    {
        free_stack(&stack);
        return (NULL);
    }
    return (stack);
}
```

**Flow diagram:**
```
build_stack(["5", "3", "1"])
    |
    +-- i=0: append_node(&stack, "5")
    |        -> validates "5"
    |        -> creates node [5]
    |        -> stack = [5] -> NULL
    |
    +-- i=1: append_node(&stack, "3")
    |        -> validates "3"
    |        -> creates node [3]
    |        -> stack = [5] -> [3] -> NULL
    |
    +-- i=2: append_node(&stack, "1")
    |        -> validates "1"
    |        -> creates node [1]
    |        -> stack = [5] -> [3] -> [1] -> NULL
    |
    +-- Check duplicates
    |
    +-- Return stack
```

---

## 42 Norm Considerations

### Norm Compliance Checklist

| Requirement | Status | Notes |
|-------------|--------|-------|
| Function length | ~12 lines | Under 25-line limit |
| Static function | File-scope | Not in header |
| Single responsibility | One node | Validates and adds |
| Parameters | 2 | Within limit |
| Return type | t_stack* | Clear success/failure |

### Why Static is Important

**42 Norm requirements:**
- Main functions should be under 25 lines
- Helper functions should be static (file-scope)
- No unnecessary exposure in header files

**Without static helper:**
```c
// build_stack would have all validation logic inline
// Function would exceed 25 lines
// 42 Norm violation!
```

**With static helper:**
```c
// build_stack: ~18 lines
// append_node: ~12 lines
// Both under limit, norm compliant!
```

### Implementation Structure

```c
// File: srcs/stack_init.c

// Static helper 1 - NOT in header
static t_stack *append_node(t_stack **stack, char *str)
{
    long    value;
    t_stack *node;

    if (!is_valid_number(str))
        return (NULL);
    value = ft_atol(str);
    if (!is_int_range(value))
        return (NULL);
    node = stack_new((int)value);
    if (!node)
        return (NULL);
    stack_add_back(stack, node);
    return (node);
}

// Static helper 2 - NOT in header
static t_stack *build_stack(char **numbers)
{
    // Uses append_node
}

// Public function - declared in header
t_stack *init_stack_a(int argc, char **argv)
{
    // Uses build_stack
}
```

---

## Common Mistakes to Avoid

### Mistake 1: Not Checking All Validations

```c
// WRONG:
static t_stack *append_node(t_stack **stack, char *str)
{
    long value = ft_atol(str);  // What if str = "abc"?
    t_stack *node = stack_new((int)value);
    stack_add_back(stack, node);
    return (node);
}

Problem: No validation, no range check
Solution: Always validate format and range before conversion
```

### Mistake 2: Forgetting Malloc Check

```c
// WRONG:
node = stack_new((int)value);
stack_add_back(stack, node);  // What if node is NULL?
return (node);

Problem: Crash if malloc fails
Solution: Check node before using
```

### Mistake 3: Using Int Instead of Long

```c
// WRONG:
int value = ft_atoi(str);  // Can't detect overflow!
if (!is_int_range(value))  // Too late, already truncated!

Problem: Overflow happens during conversion
Solution: Use long and ft_atol, then check range
```

### Mistake 4: Wrong Return Type

```c
// WRONG:
static int append_node(t_stack **stack, char *str)
{
    // ...
    return (1);  // or return (0)
}

Problem: Can't return the actual node
Solution: Return t_stack* for flexibility
```

### Mistake 5: Modifying Stack on Failure

```c
// WRONG:
node = stack_new((int)value);
stack_add_back(stack, node);  // Added before checking!
if (!node)
    return (NULL);

Problem: NULL node added to stack
Solution: Check before adding
```

---

## Testing Strategy

### Test Case 1: Valid Number

```c
t_stack *stack = NULL;
t_stack *result = append_node(&stack, "42");
assert(result != NULL);
assert(stack != NULL);
assert(stack->value == 42);
```

### Test Case 2: Invalid Format

```c
t_stack *stack = NULL;
t_stack *result = append_node(&stack, "abc");
assert(result == NULL);
assert(stack == NULL);  // Stack unchanged
```

### Test Case 3: Overflow

```c
t_stack *stack = NULL;
t_stack *result = append_node(&stack, "9999999999");
assert(result == NULL);
assert(stack == NULL);  // Stack unchanged
```

### Test Case 4: Negative Number

```c
t_stack *stack = NULL;
t_stack *result = append_node(&stack, "-42");
assert(result != NULL);
assert(stack->value == -42);
```

### Test Case 5: INT_MIN

```c
t_stack *stack = NULL;
t_stack *result = append_node(&stack, "-2147483648");
assert(result != NULL);
assert(stack->value == -2147483648);
```

### Test Case 6: Multiple Additions

```c
t_stack *stack = NULL;
append_node(&stack, "5");
append_node(&stack, "3");
append_node(&stack, "1");
// Verify stack: [5] -> [3] -> [1] -> NULL
assert(stack->value == 5);
assert(stack->next->value == 3);
assert(stack->next->next->value == 1);
```

---

## Summary: What append_node Does

1. **Validates** number string format using is_valid_number
2. **Converts** string to long using ft_atol
3. **Checks** value fits in int range using is_int_range
4. **Creates** node using stack_new with cast to int
5. **Adds** node to stack using stack_add_back
6. **Returns** node pointer on success, NULL on any failure

**Key insights:**
- Static helper function (file-scope only)
- Created to meet 42 Norm requirements
- Encapsulates complete single-number processing
- Early exit pattern on any validation failure
- Stack unchanged if validation fails

**Purpose in bigger picture:**
```
init_stack_a flow:
1. parse_arguments() -> get numbers array

2. build_stack() -> iterate through numbers
   |
   +-- for each number:
   |   append_node()  <- You are here
   |   - Validate format
   |   - Convert to long
   |   - Check range
   |   - Create node
   |   - Add to stack
   |
   +-- check duplicates

3. Return completed stack
```

---

## Location in Project

**File:** `srcs/stack_init.c`
**Header:** NOT in header file (static function)
**Phase in TODO:** Phase 2.4 (Parsing & Validation - Stack Initialization Helper)

**Implementation location:**
```c
// File: srcs/stack_init.c

// Static helper - internal to this file only
static t_stack *append_node(t_stack **stack, char *str)
{
    // Implementation here
}

// NOT declared in push_swap.h
// Only visible within stack_init.c
```

---

## Related Functions

**Calls:**
- `is_valid_number()` - Format validation
- `ft_atol()` - String to long conversion
- `is_int_range()` - Range verification
- `stack_new()` - Node creation
- `stack_add_back()` - Stack addition

**Called by:**
- `build_stack()` - Uses for each number in array

**Works with:**
- `build_stack()` - Parent function that iterates
- `init_stack_a()` - Main entry point

**Related concepts:**
- Static functions in C
- Validation pipelines
- Early exit error handling
- 42 Norm compliance strategies

---

*Remember: Each number goes through a complete validation pipeline before becoming a node. This helper ensures consistent handling and keeps the calling function clean and norm-compliant.*
