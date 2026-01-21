# is_int_range - Check if Long Value Fits in Integer Range

## Function Signature

```c
int is_int_range(long num)
```

**Return type:** `int` - Returns 1 if in range, 0 if out of range
**Parameter:** `long num` - Long integer value to check

---

## Purpose & Use Case

`is_int_range` is a **range validation function** that checks if a long integer value fits within the standard integer range (INT_MIN to INT_MAX). This is the critical safety check that prevents integer overflow in your push_swap implementation.

### When You'll Use It

You'll call `is_int_range` to:
1. **Validate after conversion** - Check ft_atol result before casting to int
2. **Prevent overflow** - Detect values outside int range
3. **Ensure safe casting** - Guarantee (int)value won't truncate
4. **Catch input errors** - Reject too-large or too-small numbers

### Why This Matters

**The overflow problem:**
```
Without range check:
Input: "2147483648"
→ ft_atol() → 2147483648L (valid long)
→ Cast to int → -2147483648 (OVERFLOW! Wraps around)
→ Wrong value in stack!

With range check:
Input: "2147483648"
→ ft_atol() → 2147483648L
→ is_int_range() → 0 (out of range!)
→ Error detected, input rejected ✓
```

---

## Deep Dive: How It Works

### The Integer Range

```
Standard int (32-bit):
INT_MIN = -2,147,483,648
INT_MAX =  2,147,483,647

Valid range: INT_MIN ≤ value ≤ INT_MAX

Examples:
-2,147,483,648  → In range ✓
-2,147,483,649  → Too small ✗
 2,147,483,647  → In range ✓
 2,147,483,648  → Too big ✗
```

### The Simple Check

```c
if (num >= INT_MIN && num <= INT_MAX)
    return (1);  // In range
return (0);      // Out of range
```

### Step-by-Step Process

#### Step 1: Check Lower Bound

```c
if (num < INT_MIN)
    return (0);  // Too small
```

**Underflow detection:**
```
INT_MIN = -2,147,483,648

Examples:
-2,147,483,648  → >= INT_MIN ✓
-2,147,483,649  → <  INT_MIN ✗ (underflow)
-9,999,999,999  → <  INT_MIN ✗ (way under)
```

#### Step 2: Check Upper Bound

```c
if (num > INT_MAX)
    return (0);  // Too big
```

**Overflow detection:**
```
INT_MAX = 2,147,483,647

Examples:
2,147,483,647  → <= INT_MAX ✓
2,147,483,648  → >  INT_MAX ✗ (overflow)
9,999,999,999  → >  INT_MAX ✗ (way over)
```

#### Step 3: In Range

```c
return (1);  // Passed both checks
```

---

## Visual Execution Trace

### Example 1: Valid INT_MAX

```
Input: 2147483647L

═══════════════════════════════════════
CHECK LOWER BOUND
═══════════════════════════════════════
num = 2147483647
INT_MIN = -2147483648

Is num < INT_MIN?
2147483647 < -2147483648?
NO ✓

Continue...

═══════════════════════════════════════
CHECK UPPER BOUND
═══════════════════════════════════════
INT_MAX = 2147483647

Is num > INT_MAX?
2147483647 > 2147483647?
NO ✓

Exactly at the limit!

═══════════════════════════════════════
RESULT
═══════════════════════════════════════
return 1 (IN RANGE) ✓
```

### Example 2: Overflow (Too Big)

```
Input: 2147483648L

═══════════════════════════════════════
CHECK LOWER BOUND
═══════════════════════════════════════
num = 2147483648
INT_MIN = -2147483648

Is num < INT_MIN?
2147483648 < -2147483648?
NO ✓

Continue...

═══════════════════════════════════════
CHECK UPPER BOUND
═══════════════════════════════════════
INT_MAX = 2147483647

Is num > INT_MAX?
2147483648 > 2147483647?
YES! ✗

One more than maximum!

═══════════════════════════════════════
RESULT
═══════════════════════════════════════
return 0 (OUT OF RANGE) ✗
```

### Example 3: Valid INT_MIN

```
Input: -2147483648L

═══════════════════════════════════════
CHECK LOWER BOUND
═══════════════════════════════════════
num = -2147483648
INT_MIN = -2147483648

Is num < INT_MIN?
-2147483648 < -2147483648?
NO ✓ (equal is OK)

Continue...

═══════════════════════════════════════
CHECK UPPER BOUND
═══════════════════════════════════════
INT_MAX = 2147483647

Is num > INT_MAX?
-2147483648 > 2147483647?
NO ✓

Far from maximum!

═══════════════════════════════════════
RESULT
═══════════════════════════════════════
return 1 (IN RANGE) ✓
```

### Example 4: Underflow (Too Small)

```
Input: -2147483649L

═══════════════════════════════════════
CHECK LOWER BOUND
═══════════════════════════════════════
num = -2147483649
INT_MIN = -2147483648

Is num < INT_MIN?
-2147483649 < -2147483648?
YES! ✗

One less than minimum!

═══════════════════════════════════════
RESULT
═══════════════════════════════════════
return 0 (OUT OF RANGE) ✗

(Upper bound check skipped - already failed)
```

---

## Defensive Checks

### Input Validation
| Check | Priority | Failure Mode | Consequence |
|-------|----------|--------------|-------------|
| `num > INT_MAX` | **CRITICAL** | Overflow | Silent truncation to negative value on cast to int |
| `num < INT_MIN` | **CRITICAL** | Underflow | Silent truncation to positive value on cast to int |
| (uses `long` type) | **CRITICAL** | Type safety | Allows detection before cast happens |

### Why These Checks Matter

#### 1. Overflow Detection (num > INT_MAX) - CRITICAL
- **Without:** Casting 2147483648L to int wraps to -2147483648
- **With:** Returns 0, triggering error before bad cast
- **Cost:** O(1) - single comparison
- **Benefit:** Prevents silent data corruption
- **Example:**
  ```c
  long value = 2147483648L;  // INT_MAX + 1
  // Without check: (int)value = -2147483648 (WRONG!)
  // With check: is_int_range(value) = 0 (DETECTED!)
  ```

#### 2. Underflow Detection (num < INT_MIN) - CRITICAL
- **Without:** Casting -2147483649L to int wraps to 2147483647
- **With:** Returns 0, triggering error before bad cast
- **Cost:** O(1) - single comparison
- **Benefit:** Prevents silent data corruption
- **Example:**
  ```c
  long value = -2147483649L;  // INT_MIN - 1
  // Without check: (int)value = 2147483647 (WRONG!)
  // With check: is_int_range(value) = 0 (DETECTED!)
  ```

#### 3. Long Type Strategy - CRITICAL
- **Why long:** 64-bit long can hold values outside 32-bit int range
- **Detection window:** Values from 2^31 to 2^63 are valid long but invalid int
- **Safety guarantee:** Check happens BEFORE destructive cast
- **Type flow:**
  ```
  String → ft_atol() → long value → is_int_range() → int (safe cast)
                                          ↑
                                    DEFENSIVE GATE
  ```

### Defensive Implementation Strategy

**Single Responsibility:** Only validates range, doesn't perform conversion
**No Side Effects:** Read-only comparison, safe to call multiple times
**Boolean Return:** Clear success (1) or failure (0) indication
**Type Preservation:** Uses long parameter to preserve full value during check

### What Happens Without These Checks

```
SCENARIO: User input "2147483648"
─────────────────────────────────────────────────────

WITHOUT is_int_range:
1. ft_atol("2147483648") → 2147483648L ✓
2. (int)2147483648L → -2147483648 ✗ SILENT OVERFLOW!
3. Stack contains wrong value
4. Sorting produces incorrect results
5. No error indication to user

WITH is_int_range:
1. ft_atol("2147483648") → 2147483648L ✓
2. is_int_range(2147483648L) → 0 ✗ DETECTED!
3. Error cleanup triggered
4. Print "Error" to stderr
5. Program exits cleanly
6. No corrupted data
```

### Protection Against Integer Wraparound

**The Wraparound Problem:**
```
32-bit signed integer representation:
INT_MAX:     01111111 11111111 11111111 11111111 = 2,147,483,647
INT_MAX + 1: 10000000 00000000 00000000 00000000 = -2,147,483,648
                                                      ↑ Sign bit flips!

INT_MIN:     10000000 00000000 00000000 00000000 = -2,147,483,648
INT_MIN - 1: 01111111 11111111 11111111 11111111 = 2,147,483,647
                                                      ↑ Wraps around!
```

**How is_int_range Prevents This:**
- Checks value while still in long type (64-bit)
- Detects overflow BEFORE truncation to int (32-bit)
- Returns failure code instead of allowing bad cast
- Calling code can handle error appropriately

### Critical Integration Points

This function serves as the defensive barrier in the validation pipeline:

```
VALIDATION PIPELINE WITH DEFENSIVE CHECKS:
─────────────────────────────────────────────────────

Input: "2147483648"
    ↓
[DEFENSIVE CHECK 1: Format Validation]
is_valid_number("2147483648")
→ Contains only digits and optional sign? YES ✓
→ Valid number format? YES ✓
    ↓
[CONVERSION TO LONG TYPE]
ft_atol("2147483648")
→ Converts to 2147483648L ✓
→ No overflow in long (64-bit can hold this)
    ↓
[DEFENSIVE CHECK 2: Range Validation] ← is_int_range
is_int_range(2147483648L)
→ Is 2147483648 > INT_MAX (2147483647)? YES ✗
→ OUT OF RANGE DETECTED!
→ Return 0 (failure)
    ↓
[ERROR HANDLING]
Cleanup and exit
→ Print "Error"
→ Free allocated memory
→ Exit program
→ CORRUPTED DATA PREVENTED ✓
```

**Without this defensive check:**
- Value proceeds to cast: `(int)2147483648L`
- Becomes -2147483648 (silent overflow)
- Corrupted value enters your stack
- Program sorts wrong values
- No indication of error

---

## Complete Algorithm Pseudocode

```
FUNCTION is_int_range(num):
    // Check if value is within int bounds
    IF num < INT_MIN OR num > INT_MAX:
        RETURN 0  // Out of range

    RETURN 1  // In range
END FUNCTION
```

### Alternative Implementation

```
FUNCTION is_int_range(num):
    // Explicit bounds check
    IF num < -2147483648:
        RETURN 0  // Underflow

    IF num > 2147483647:
        RETURN 0  // Overflow

    RETURN 1  // Valid
END FUNCTION
```

### Single-Expression Implementation

```
FUNCTION is_int_range(num):
    RETURN (num >= INT_MIN AND num <= INT_MAX)
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: Exactly INT_MIN

```c
long value = -2147483648L;
int result = is_int_range(value);
// result = 1 (valid) ✓
```

### Edge Case 2: Exactly INT_MAX

```c
long value = 2147483647L;
int result = is_int_range(value);
// result = 1 (valid) ✓
```

### Edge Case 3: INT_MIN - 1

```c
long value = -2147483649L;
int result = is_int_range(value);
// result = 0 (underflow) ✗
```

### Edge Case 4: INT_MAX + 1

```c
long value = 2147483648L;
int result = is_int_range(value);
// result = 0 (overflow) ✗
```

### Edge Case 5: Zero

```c
long value = 0L;
int result = is_int_range(value);
// result = 1 (valid) ✓
```

### Edge Case 6: Small Values

```c
long value = 42L;
int result = is_int_range(value);
// result = 1 (valid) ✓
// Well within range
```

### Edge Case 7: Very Large Overflow

```c
long value = 9999999999L;
int result = is_int_range(value);
// result = 0 (way over INT_MAX) ✗
```

### Edge Case 8: Very Large Underflow

```c
long value = -9999999999L;
int result = is_int_range(value);
// result = 0 (way under INT_MIN) ✗
```

---

## Time & Space Complexity

### Time Complexity: O(1)

```
Operations:
- Compare with INT_MIN: O(1)
- Compare with INT_MAX: O(1)
- Return result: O(1)

Total: O(1) - constant time
Always exactly 1-2 comparisons
```

### Space Complexity: O(1)

```
Variables:
- Parameter num: 8 bytes
- No additional variables
- No allocations
- No recursion

Total: O(1) - constant space
```

---

## Why Use limits.h Constants

### INT_MIN and INT_MAX

```c
#include <limits.h>

// System provides:
INT_MIN = -2147483648
INT_MAX =  2147483647

// Don't hardcode these!
❌ WRONG:
if (num < -2147483648 || num > 2147483647)

✓ CORRECT:
if (num < INT_MIN || num > INT_MAX)
```

**Why use constants?**
1. **Portability** - Works on different systems
2. **Readability** - Clear what you're checking
3. **Maintainability** - Change once in limits.h
4. **Correctness** - Compiler guarantees correct values

---

## Relationship with Other Functions

### Functions Called By is_int_range

- **None** - Pure comparison function

### Functions That Use is_int_range

- **init_stack_a()** - Range validation after ft_atol

### Related Functions

- **ft_atol()** - Called before is_int_range
- **is_valid_number()** - Format check (called before ft_atol)

---

## Integration with Push_swap

### Complete Validation Flow

```c
// In init_stack_a:
while (numbers[i])
{
    // Step 1: Format validation
    if (!is_valid_number(numbers[i]))
    {
        // Not a valid number format
        return (error_cleanup());
    }

    // Step 2: String to long conversion
    long value = ft_atol(numbers[i]);

    // Step 3: Range validation ← is_int_range used here
    if (!is_int_range(value))
    {
        // Value doesn't fit in int
        return (error_cleanup());
    }

    // Step 4: Safe cast to int
    // We know it fits because is_int_range passed
    t_stack *node = stack_new((int)value);

    i++;
}
```

### Why This Order Matters

```
Correct order:
1. is_valid_number("2147483648") → YES (format OK)
2. ft_atol("2147483648") → 2147483648L (conversion OK)
3. is_int_range(2147483648L) → NO (out of range!)
4. Error before bad cast ✓

Wrong order (skipping range check):
1. is_valid_number("2147483648") → YES
2. ft_atol("2147483648") → 2147483648L
3. (int)2147483648L → -2147483648 (OVERFLOW!)
4. Wrong value in stack ✗
```

---

## 42 Norm Considerations

### Norm Compliance

✅ **Function length:** 1-3 lines (well under 25-line limit)
✅ **Single responsibility:** Only checks range
✅ **No global variables:** Uses standard library constants
✅ **Clear naming:** Function name clearly describes purpose
✅ **Simple logic:** One conditional, no complex operations

### Implementation Example

```c
int is_int_range(long num)
{
    if (num < INT_MIN || num > INT_MAX)
        return (0);
    return (1);
}
```

### Alternative Single-Line Implementation

```c
int is_int_range(long num)
{
    return (num >= INT_MIN && num <= INT_MAX);
}
```

**Both are valid!** Choose based on style preference.

---

## Common Mistakes to Avoid

### Mistake 1: Using int Parameter

```c
❌ WRONG:
int is_int_range(int num)
{
    // num is already int!
    // Can't detect overflow that already happened
    return (1);  // Always returns 1
}

✓ CORRECT:
int is_int_range(long num)
{
    // long can hold values outside int range
    // Can detect overflow
}
```

### Mistake 2: Forgetting to Check

```c
❌ WRONG:
long value = ft_atol(str);
int int_value = (int)value;  // Direct cast, no check!

✓ CORRECT:
long value = ft_atol(str);
if (!is_int_range(value))
    return (error);
int int_value = (int)value;  // Safe cast
```

### Mistake 3: Wrong Comparison Operators

```c
❌ WRONG:
if (num > INT_MIN && num < INT_MAX)  // Excludes boundaries!

✓ CORRECT:
if (num >= INT_MIN && num <= INT_MAX)  // Includes boundaries
```

### Mistake 4: Hardcoding Values

```c
❌ WRONG:
if (num < -2147483648 || num > 2147483647)

Problems:
- Not portable
- Typo risk
- Hard to read

✓ CORRECT:
if (num < INT_MIN || num > INT_MAX)
```

### Mistake 5: Casting Before Checking

```c
❌ WRONG:
long value = ft_atol(str);
if (!is_int_range((int)value))  // Cast before check!

Problem: Already lost precision in cast

✓ CORRECT:
long value = ft_atol(str);
if (!is_int_range(value))  // Check before cast
```

---

## Testing Strategy

### Test Case 1: Within Range

```c
assert(is_int_range(0L) == 1);
assert(is_int_range(42L) == 1);
assert(is_int_range(-42L) == 1);
assert(is_int_range(1000L) == 1);
assert(is_int_range(-1000L) == 1);
```

### Test Case 2: Boundary Values

```c
assert(is_int_range(2147483647L) == 1);   // INT_MAX
assert(is_int_range(-2147483648L) == 1);  // INT_MIN
```

### Test Case 3: Just Over Boundary

```c
assert(is_int_range(2147483648L) == 0);   // INT_MAX + 1
assert(is_int_range(-2147483649L) == 0);  // INT_MIN - 1
```

### Test Case 4: Way Out of Range

```c
assert(is_int_range(9999999999L) == 0);
assert(is_int_range(-9999999999L) == 0);
assert(is_int_range(LONG_MAX) == 0);
assert(is_int_range(LONG_MIN) == 0);
```

### Test Case 5: Integration Test

```c
void test_full_conversion(void)
{
    char *str = "2147483648";

    // Should fail range check
    if (!is_valid_number(str))
        return;  // Won't happen

    long value = ft_atol(str);
    assert(value == 2147483648L);

    assert(is_int_range(value) == 0);  // Should fail here
    printf("✓ Overflow detected correctly\n");
}
```

---

## Why This Function Exists

### The Problem It Solves

```
Without is_int_range:
User input: "2147483648"
↓
Parse and convert
↓
Cast to int: -2147483648 (silent overflow!)
↓
Program processes wrong value
↓
Incorrect sorting behavior

With is_int_range:
User input: "2147483648"
↓
Parse and convert to long: 2147483648L
↓
is_int_range check: FAIL (out of range)
↓
Print "Error" and exit
↓
Correct error handling ✓
```

### Why long Type is Key

```
long on most systems: 64-bit (-2^63 to 2^63-1)
int on most systems:  32-bit (-2^31 to 2^31-1)

This gap allows detection:
Value = 2^31 (2147483648)
→ Fits in long ✓
→ Doesn't fit in int ✗
→ We can detect and reject!
```

---

## Summary: What is_int_range Does

1. **Receives** long integer value
2. **Compares** against INT_MIN lower bound
3. **Compares** against INT_MAX upper bound
4. **Returns** 1 if in range, 0 if out of range
5. **Enables** safe casting from long to int

**Key insight:** This tiny function is your safety net against integer overflow. It's the final check before committing a value to your stack, ensuring data integrity throughout your program.

---

## Location in Project

**File:** `srcs/validate.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 2.2 (Parsing & Validation - Number Validation)

**Note:** This function is in `validate.c` (not `parser.c`) to comply with 42 Norm's
5 functions per file limit. Parser.c contains parse_arguments + 2 static helpers.

**Function prototype:**
```c
int is_int_range(long num);
```

**Typical implementation:**
```c
int is_int_range(long num)
{
    return (num >= INT_MIN && num <= INT_MAX);
}
```

---

## Related Functions

**Called before is_int_range:**
- `is_valid_number()` - Format validation
- `ft_atol()` - String to long conversion

**Calls is_int_range:**
- `init_stack_a()` - Stack initialization

**Related validation:**
- `has_duplicates()` - Value uniqueness check

---

*Remember: The simplest functions are often the most critical. This three-line function stands between your program and integer overflow disasters!*
