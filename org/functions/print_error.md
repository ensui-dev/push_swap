# print_error - Print Error Message to stderr

## Function Signature

```c
void print_error(void)
```

**Return type:** `void` - No return value
**Parameters:** None

---

## Purpose & Use Case

`print_error` is a **simple error reporting function** that outputs the standardized error message "Error\n" to standard error (stderr). According to the push_swap subject, this is the ONLY error message your program should ever print.

### When You'll Use It

You'll call `print_error` whenever:
1. **Invalid input detected** - Wrong format, duplicates, out of range
2. **Memory allocation fails** - malloc returns NULL
3. **Any validation check fails** - Before exiting with error code
4. **Subject requires error output** - Exactly "Error\n", nothing more

### Why This Matters

**Subject requirements:**
```
Any error must result in:
1. "Error\n" printed to stderr
2. Program exits with code 1
3. No other messages allowed

Valid errors:
- Non-numeric arguments
- Numbers outside int range
- Duplicate numbers
- Memory allocation failures

No error for:
- No arguments (./push_swap)
- Already sorted (./push_swap 1 2 3)
```

---

## Deep Dive: How It Works

### The write() System Call

```c
write(2, "Error\n", 6);
```

**Parameters explained:**
- `2` - File descriptor for stderr
- `"Error\n"` - String to write
- `6` - Number of bytes to write

**Why write() instead of printf()?**
- More reliable (no buffering issues)
- Works even if stdio is corrupted
- Simple and direct
- Required by many 42 projects

### File Descriptors

```
Standard file descriptors:
0 = stdin  (standard input)
1 = stdout (standard output)
2 = stderr (standard error)

Why use stderr (2)?
- Error messages belong on error stream
- Allows separating errors from regular output
- Standard Unix/Linux convention
```

### Step-by-Step Process

#### Step 1: Call write()

```c
write(2, "Error\n", 6);
```

**What happens:**
1. System call invoked
2. Kernel writes to stderr
3. Message appears on terminal
4. Returns number of bytes written (6)

#### Step 2: Return

```c
return;  // Or simply fall through to end of function
```

**No return value needed** - void function

---

## Visual Execution Trace

### Example: Error Output

```
Program detects invalid input:
"abc" is not a valid number

Call: print_error()

═══════════════════════════════════════
FUNCTION EXECUTION
═══════════════════════════════════════

write(2, "Error\n", 6)
  ↓
Kernel writes to file descriptor 2 (stderr)
  ↓
Terminal displays:
Error
  ↓
Function returns

═══════════════════════════════════════
RESULT
═══════════════════════════════════════
Error message displayed on stderr
Program can now exit
```

### Terminal Output Example

```bash
$ ./push_swap 5 3 abc
Error
$ echo $?
1
```

**What happened:**
1. Program parsed arguments
2. Detected "abc" is invalid
3. Called print_error()
4. "Error\n" printed to stderr
5. Program exited with code 1

---

## Complete Algorithm Pseudocode

```
FUNCTION print_error():
    // Write error message to stderr
    write(file_descriptor: 2,
          message: "Error\n",
          length: 6)
END FUNCTION
```

---

## Alternative Implementations

### Using ft_putstr_fd (if available)

```c
void print_error(void)
{
    ft_putstr_fd("Error\n", 2);
}
```

**Pros:**
- More readable
- Consistent with libft style
- Easier to maintain

**Cons:**
- Requires ft_putstr_fd implementation
- One more function dependency

### Using write directly (recommended)

```c
void print_error(void)
{
    write(2, "Error\n", 6);
}
```

**Pros:**
- Zero dependencies
- Guaranteed to work
- Standard system call
- Simple and fast

**Cons:**
- Less readable for beginners
- Magic numbers (2, 6)

---

## Edge Cases

### Edge Case 1: Multiple Calls

```c
print_error();
print_error();
print_error();

Output:
Error
Error
Error
```

**Note:** Each call prints once. Usually you only call once before exit.

### Edge Case 2: stderr Redirected

```bash
$ ./push_swap abc 2> error.txt
$ cat error.txt
Error
```

**Works correctly** - writes to wherever stderr is directed.

### Edge Case 3: stdout vs stderr

```bash
$ ./push_swap abc 1> out.txt 2> err.txt
$ cat out.txt
(empty)
$ cat err.txt
Error
```

**Correct behavior** - error goes to stderr, not stdout.

---

## Time & Space Complexity

### Time Complexity: O(1)

```
Operations:
- One write() system call
- Writes fixed 6 bytes
- Constant time regardless of input

Total: O(1) - constant time
```

### Space Complexity: O(1)

```
Memory:
- No variables
- No allocations
- String literal in code segment

Total: O(1) - constant space
```

---

## Relationship with Other Functions

### Functions Called By print_error

- **write()** - System call (not a user function)

### Functions That Use print_error

- **error_exit()** - Prints error then cleans up and exits
- **main()** - May call directly on validation failures
- **init_stack_a()** - On parsing/validation errors

---

## Integration with Push_swap

### Usage Pattern 1: Direct Call

```c
int main(int argc, char **argv)
{
    t_stack *stack_a;

    if (argc < 2)
        return (0);  // No error message for no args

    stack_a = init_stack_a(argc, argv);
    if (!stack_a)
    {
        print_error();  // Print error
        return (1);     // Exit with error code
    }

    // Continue program...
}
```

### Usage Pattern 2: Via error_exit()

```c
t_stack *init_stack_a(int argc, char **argv)
{
    // ... parsing code ...

    if (!is_valid_number(numbers[i]))
    {
        free_stack(&stack_a);
        if (argc == 2)
            free_split(numbers);
        print_error();
        exit(1);
    }

    // ... more code ...
}
```

### Usage Pattern 3: Centralized Error Handling

```c
void error_exit(t_stack **stack_a, t_stack **stack_b)
{
    print_error();
    
    if (stack_a && *stack_a)
        free_stack(stack_a);
    if (stack_b && *stack_b)
        free_stack(stack_b);
    
    exit(1);
}
```

---

## 42 Norm Considerations

### Norm Compliance

✅ **Function length:** 1 line (well under 25-line limit)
✅ **Single responsibility:** Only prints error
✅ **No global variables:** None needed
✅ **Clear naming:** Function name describes purpose
✅ **Standard practice:** Common pattern in 42 projects

### Implementation Example

```c
void    print_error(void)
{
    write(2, "Error\n", 6);
}
```

**That's it!** Simplest possible implementation.

---

## Common Mistakes to Avoid

### Mistake 1: Writing to stdout

```c
❌ WRONG:
void print_error(void)
{
    write(1, "Error\n", 6);  // stdout instead of stderr!
}

Problem: Error message on wrong stream
Solution: Use file descriptor 2, not 1
```

### Mistake 2: Wrong String Length

```c
❌ WRONG:
write(2, "Error\n", 5);  // Missing newline byte

Result: "Error" without newline

✓ CORRECT:
write(2, "Error\n", 6);  // All 6 bytes: E-r-r-o-r-\n
```

### Mistake 3: Custom Error Messages

```c
❌ WRONG (for push_swap):
write(2, "Error: Invalid number\n", 22);
write(2, "Error: Duplicate found\n", 23);

Problem: Subject requires exactly "Error\n"

✓ CORRECT:
write(2, "Error\n", 6);  // Always the same message
```

### Mistake 4: Using printf/fprintf

```c
❌ ALLOWED BUT LESS PREFERRED:
fprintf(stderr, "Error\n");
printf("Error\n");  // Wrong stream!

✓ BETTER:
write(2, "Error\n", 6);  // Standard for 42 projects
```

### Mistake 5: Printing When No Error

```c
❌ WRONG:
// No arguments case
if (argc < 2)
{
    print_error();  // Don't print for no args!
    return (0);
}

✓ CORRECT:
if (argc < 2)
    return (0);  // Silent exit for no arguments
```

---

## Testing Strategy

### Test Case 1: Invalid Number

```bash
$ ./push_swap 42 abc
Error
$ echo $?
1
```

### Test Case 2: Duplicate

```bash
$ ./push_swap 5 3 1 3 2
Error
$ echo $?
1
```

### Test Case 3: Out of Range

```bash
$ ./push_swap 2147483648
Error
$ echo $?
1
```

### Test Case 4: stderr Redirection

```bash
$ ./push_swap abc 2> errors.log
$ cat errors.log
Error
```

### Test Case 5: Both Streams

```bash
$ ./push_swap 1 2 3 > out.txt 2> err.txt
$ cat out.txt
(sorted output, if any)
$ cat err.txt
(empty - no errors)
```

---

## Why This Function Exists

### Centralization

```
Benefits of dedicated function:
1. Single place to modify error output
2. Consistent error messages
3. Easy to find all error points (search for print_error)
4. Testable error handling
```

### Simplicity

```
Could inline everywhere:
write(2, "Error\n", 6);

But function is better:
print_error();

- More readable
- Easier to maintain
- Can change implementation easily
```

---

## Summary: What print_error Does

1. **Writes** exactly "Error\n" (6 bytes)
2. **Outputs** to stderr (file descriptor 2)
3. **Uses** write() system call
4. **Returns** nothing (void function)

**Key insight:** This is the simplest function in your entire project, yet it's critical for proper error reporting. One line, one purpose: tell the user something went wrong.

---

## Location in Project

**File:** `srcs/error.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 3.1 (Error Handling - Error Output)

**Function prototype:**
```c
void print_error(void);
```

**Implementation:**
```c
void    print_error(void)
{
    write(2, "Error\n", 6);
}
```

---

## Related Functions

**Calls:**
- `write()` - System call

**Called by:**
- `error_exit()` - Error cleanup function
- `main()` - On validation failures
- `init_stack_a()` - On parsing errors

---

*Remember: Sometimes the simplest functions are the most important. One line of code, but essential for proper error handling!*
