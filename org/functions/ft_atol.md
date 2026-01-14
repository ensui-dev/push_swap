# ft_atol - Convert String to Long Integer

## Function Signature

```c
long ft_atol(const char *str)
```

**Return type:** `long` - Long integer value of the string
**Parameter:** `const char *str` - String to convert to long integer

---

## Purpose & Use Case

`ft_atol` is a **string-to-number conversion function** that converts a valid number string into a long integer. The "l" in atol stands for "long", which is crucial for detecting integer overflow in push_swap.

### When You'll Use It

You'll call `ft_atol` to:
1. **Convert validated strings** - After is_valid_number confirms format
2. **Detect overflow** - Use long to check if value exceeds int range
3. **Parse command line numbers** - Convert argument strings to usable integers
4. **Preserve sign** - Handle both positive and negative numbers

### Why This Matters

**The overflow detection strategy:**
```
Problem: INT_MAX = 2,147,483,647

Input: "2147483648"
→ If we convert to int directly, overflow!
→ 2,147,483,648 wraps around to negative

Solution: Convert to long first
→ long can hold larger values
→ Check if > INT_MAX or < INT_MIN
→ Only then cast to int

Flow:
"2147483648" → ft_atol() → 2147483648L
             → is_int_range() → FALSE (too big!)
             → Error before bad cast
```

---

## Deep Dive: How It Works

### The Conversion Algorithm

```
ASCII to Integer conversion:

String: "-42"
        ↓
Step 1: Detect sign → negative
Step 2: Process '4' → 0 * 10 + 4 = 4
Step 3: Process '2' → 4 * 10 + 2 = 42
Step 4: Apply sign → -42
        ↓
Result: -42L
```

### Mathematical Explanation

**Digit accumulation:**
```
"123" converts as:
Start:     result = 0
See '1':   result = 0 * 10 + 1 = 1
See '2':   result = 1 * 10 + 2 = 12
See '3':   result = 12 * 10 + 3 = 123
```

**Why multiply by 10?**
```
Decimal positional notation:
"123" = 1×100 + 2×10 + 3×1
      = 1×10² + 2×10¹ + 3×10⁰

Processing left-to-right:
1     = 1
12    = 1×10 + 2
123   = (1×10 + 2)×10 + 3
      = 1×10² + 2×10 + 3
```

### Step-by-Step Process

#### Step 1: Initialize Variables

```c
long result = 0;  // Accumulated value
int sign = 1;     // 1 for positive, -1 for negative
int i = 0;        // String index
```

#### Step 2: Skip Whitespace (Optional)

```c
while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
       str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
    i++;
```

**Note:** For push_swap, is_valid_number already rejected whitespace, so this step may be optional. However, standard atol includes it for robustness.

#### Step 3: Handle Sign

```c
if (str[i] == '-')
{
    sign = -1;
    i++;
}
else if (str[i] == '+')
{
    i++;
}
```

**Sign detection:**
```
"-42" → sign = -1, i moves to '4'
"+42" → sign = 1, i moves to '4'
"42"  → sign = 1 (default), i stays at '4'
```

#### Step 4: Convert Digits

```c
while (ft_isdigit(str[i]))
{
    result = result * 10 + (str[i] - '0');
    i++;
}
```

**Digit conversion:**
```
Character '0' has ASCII value 48
Character '9' has ASCII value 57

To convert '5' to 5:
'5' - '0' = 53 - 48 = 5

General formula:
digit_value = character - '0'
```

**Accumulation:**
```
"42"
Start: result = 0

Process '4':
  result = 0 * 10 + ('4' - '0')
  result = 0 * 10 + 4
  result = 4

Process '2':
  result = 4 * 10 + ('2' - '0')
  result = 40 + 2
  result = 42
```

#### Step 5: Apply Sign

```c
return (result * sign);
```

**Final value:**
```
Positive: result × 1 = result
Negative: result × (-1) = -result

"42"  → 42 × 1 = 42
"-42" → 42 × (-1) = -42
```

---

## Visual Execution Trace

### Example 1: Positive Number

```
Input: "42"

═══════════════════════════════════════
INITIALIZATION
═══════════════════════════════════════
result = 0
sign = 1
i = 0

═══════════════════════════════════════
STEP 1: Check for sign
═══════════════════════════════════════
str[0] = '4' (not a sign)
sign remains 1
i remains 0

═══════════════════════════════════════
STEP 2: Process first digit '4'
═══════════════════════════════════════
str[0] = '4'
ft_isdigit('4') = TRUE

Convert character:
'4' - '0' = 52 - 48 = 4

Update result:
result = result * 10 + 4
result = 0 * 10 + 4
result = 4

Move to next: i = 1

═══════════════════════════════════════
STEP 3: Process second digit '2'
═══════════════════════════════════════
str[1] = '2'
ft_isdigit('2') = TRUE

Convert character:
'2' - '0' = 50 - 48 = 2

Update result:
result = result * 10 + 2
result = 4 * 10 + 2
result = 40 + 2
result = 42

Move to next: i = 2

═══════════════════════════════════════
STEP 4: End of string
═══════════════════════════════════════
str[2] = '\0'
ft_isdigit('\0') = FALSE
Loop exits

═══════════════════════════════════════
STEP 5: Apply sign
═══════════════════════════════════════
result = result * sign
result = 42 * 1
result = 42

═══════════════════════════════════════
RETURN
═══════════════════════════════════════
return 42L
```

### Example 2: Negative Number

```
Input: "-123"

═══════════════════════════════════════
INITIALIZATION
═══════════════════════════════════════
result = 0
sign = 1
i = 0

═══════════════════════════════════════
STEP 1: Detect sign
═══════════════════════════════════════
str[0] = '-'
sign = -1
i = 1

═══════════════════════════════════════
STEP 2: Process '1'
═══════════════════════════════════════
str[1] = '1'
result = 0 * 10 + 1 = 1
i = 2

═══════════════════════════════════════
STEP 3: Process '2'
═══════════════════════════════════════
str[2] = '2'
result = 1 * 10 + 2 = 12
i = 3

═══════════════════════════════════════
STEP 4: Process '3'
═══════════════════════════════════════
str[3] = '3'
result = 12 * 10 + 3 = 123
i = 4

═══════════════════════════════════════
STEP 5: End and apply sign
═══════════════════════════════════════
str[4] = '\0'
Loop exits

result = 123 * (-1) = -123

═══════════════════════════════════════
RETURN
═══════════════════════════════════════
return -123L
```

### Example 3: INT_MAX

```
Input: "2147483647"

Process each digit:
result = 0
'2': result = 0 * 10 + 2 = 2
'1': result = 2 * 10 + 1 = 21
'4': result = 21 * 10 + 4 = 214
'7': result = 214 * 10 + 7 = 2147
'4': result = 2147 * 10 + 4 = 21474
'8': result = 21474 * 10 + 8 = 214748
'3': result = 214748 * 10 + 3 = 2147483
'6': result = 2147483 * 10 + 6 = 21474836
'4': result = 21474836 * 10 + 4 = 214748364
'7': result = 214748364 * 10 + 7 = 2147483647

Return: 2147483647L

Note: This fits in INT_MAX exactly ✓
```

### Example 4: Overflow Detection

```
Input: "2147483648" (INT_MAX + 1)

Process each digit:
result = 0
'2': result = 2
'1': result = 21
'4': result = 214
'7': result = 2147
'4': result = 21474
'8': result = 214748
'3': result = 2147483
'6': result = 21474836
'4': result = 214748364
'8': result = 2147483648  ← This is > INT_MAX!

Return: 2147483648L

Note: long can hold this value
Caller must check: is_int_range(2147483648L) → FALSE
```

---

## Complete Algorithm Pseudocode

```
FUNCTION ft_atol(str):
    // Step 1: Initialize
    result = 0
    sign = 1
    i = 0

    // Step 2: Skip leading whitespace (optional for push_swap)
    WHILE str[i] is whitespace:
        i = i + 1

    // Step 3: Handle sign
    IF str[i] is '-':
        sign = -1
        i = i + 1
    ELSE IF str[i] is '+':
        i = i + 1

    // Step 4: Convert digits
    WHILE str[i] is digit:
        digit_value = str[i] - '0'
        result = result * 10 + digit_value
        i = i + 1

    // Step 5: Apply sign and return
    RETURN result * sign
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: Zero

```c
long result = ft_atol("0");
// result = 0L
```

### Edge Case 2: Negative Zero

```c
long result = ft_atol("-0");
// result = 0L (negative sign applied to 0 is still 0)
```

### Edge Case 3: INT_MAX

```c
long result = ft_atol("2147483647");
// result = 2147483647L
// Fits in int ✓
```

### Edge Case 4: INT_MIN

```c
long result = ft_atol("-2147483648");
// result = -2147483648L
// Fits in int ✓
```

### Edge Case 5: Just Over INT_MAX

```c
long result = ft_atol("2147483648");
// result = 2147483648L
// Doesn't fit in int! ✗
// Must check with is_int_range()
```

### Edge Case 6: Very Large Number

```c
long result = ft_atol("999999999999");
// result = 999999999999L
// Way over INT_MAX ✗
// is_int_range() will catch this
```

### Edge Case 7: Single Digit

```c
long result = ft_atol("5");
// result = 5L
```

### Edge Case 8: Leading Plus

```c
long result = ft_atol("+42");
// result = 42L (plus sign is optional)
```

---

## Time & Space Complexity

### Time Complexity: O(n)

```
n = length of string

Operations:
- Initialize: O(1)
- Skip whitespace: O(w) where w = whitespace count
- Check sign: O(1)
- Process digits: O(d) where d = digit count
  - Each iteration: O(1)
  - Runs d times

Total: O(1) + O(w) + O(1) + O(d) = O(n)
Linear in string length
```

### Space Complexity: O(1)

```
Variables:
- result: 8 bytes (long)
- sign: 4 bytes (int)
- i: 4 bytes (int)
- No arrays
- No recursion

Total: O(1) - constant space
```

---

## Comparison with ft_atoi

### Differences

```c
ft_atoi:  Returns int
ft_atol:  Returns long

Why long for push_swap?
- Need to detect overflow
- INT_MAX = 2,147,483,647
- "2147483648" overflows int
- But fits in long!
- Check range, then cast safely
```

### Implementation Similarity

```c
// Almost identical, just return type differs

int ft_atoi(const char *str)
{
    int result = 0;  // int instead of long
    // ... same logic
    return (result * sign);
}

long ft_atol(const char *str)
{
    long result = 0;  // long instead of int
    // ... same logic
    return (result * sign);
}
```

---

## Relationship with Other Functions

### Functions Called By ft_atol

- **ft_isdigit()** - Checks if character is digit

### Functions That Use ft_atol

- **init_stack_a()** - Converts validated strings to numbers

### Related Functions

- **is_valid_number()** - Called BEFORE ft_atol
- **is_int_range()** - Called AFTER ft_atol
- **ft_atoi()** - Similar but returns int

---

## Integration with Push_swap

### Typical Usage Flow

```c
// In init_stack_a:
while (numbers[i])
{
    // Step 1: Validate format
    if (!is_valid_number(numbers[i]))
        return (error_cleanup());

    // Step 2: Convert to long
    long value = ft_atol(numbers[i]);

    // Step 3: Check range
    if (!is_int_range(value))
        return (error_cleanup());

    // Step 4: Safe to cast to int
    t_stack *node = stack_new((int)value);

    i++;
}
```

---

## 42 Norm Considerations

### Norm Compliance

✅ **Function length:** 15-20 lines (under 25-line limit)
✅ **Single responsibility:** Only converts string to long
✅ **No global variables:** Everything is local
✅ **Clear variable names:** result, sign, i
✅ **Standard algorithm:** Classic atoi/atol implementation

### Implementation Example

```c
long    ft_atol(const char *str)
{
    long    result;
    int     sign;
    int     i;

    result = 0;
    sign = 1;
    i = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (ft_isdigit(str[i]))
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result * sign);
}
```

---

## Common Mistakes to Avoid

### Mistake 1: Using int Instead of long

```c
❌ WRONG:
int ft_atol(const char *str)
{
    int result = 0;  // Can't detect overflow!
    // ...
}

✓ CORRECT:
long ft_atol(const char *str)
{
    long result = 0;  // Can hold values > INT_MAX
    // ...
}
```

### Mistake 2: Not Handling Sign

```c
❌ WRONG:
long ft_atol(const char *str)
{
    long result = 0;
    // Skip sign handling
    while (*str)
        result = result * 10 + (*str++ - '0');
    return (result);
}

Problem: "-42" becomes 42 (wrong!)
```

### Mistake 3: Not Checking for Digits

```c
❌ WRONG:
while (str[i])
{
    result = result * 10 + (str[i] - '0');
    i++;
}

Problem: Processes non-digits too!
"42a" would try to convert 'a'

✓ CORRECT:
while (ft_isdigit(str[i]))
{
    result = result * 10 + (str[i] - '0');
    i++;
}
```

### Mistake 4: Integer Overflow in Accumulation

```c
❌ POTENTIAL ISSUE:
// For very large strings exceeding LONG_MAX
// result * 10 can overflow even in long

Note: For push_swap, is_valid_number limits input
But robust atol should check for this
```

### Mistake 5: Assuming Input is Valid

```c
❌ WRONG:
// Calling ft_atol without validating first
long value = ft_atol("abc");  // Undefined behavior!

✓ CORRECT:
if (!is_valid_number(str))
    return (error);
long value = ft_atol(str);  // Now safe
```

---

## Testing Strategy

### Test Case 1: Positive Numbers

```c
assert(ft_atol("0") == 0);
assert(ft_atol("1") == 1);
assert(ft_atol("42") == 42);
assert(ft_atol("123") == 123);
assert(ft_atol("2147483647") == 2147483647);  // INT_MAX
```

### Test Case 2: Negative Numbers

```c
assert(ft_atol("-1") == -1);
assert(ft_atol("-42") == -42);
assert(ft_atol("-123") == -123);
assert(ft_atol("-2147483648") == -2147483648);  // INT_MIN
```

### Test Case 3: With Plus Sign

```c
assert(ft_atol("+0") == 0);
assert(ft_atol("+42") == 42);
assert(ft_atol("+123") == 123);
```

### Test Case 4: Overflow Detection

```c
long result1 = ft_atol("2147483648");  // INT_MAX + 1
assert(result1 == 2147483648L);
assert(!is_int_range(result1));  // Should be out of range

long result2 = ft_atol("-2147483649");  // INT_MIN - 1
assert(result2 == -2147483649L);
assert(!is_int_range(result2));  // Should be out of range
```

### Test Case 5: Edge Values

```c
assert(ft_atol("-0") == 0);
assert(ft_atol("+0") == 0);
```

---

## Summary: What ft_atol Does

1. **Skips** leading whitespace (optional)
2. **Detects** optional sign (+/-)
3. **Accumulates** digit values using base-10 math
4. **Applies** sign to final result
5. **Returns** long integer value
6. **Enables** overflow detection by using long type

**Key insight:** By returning long instead of int, we create a "safety buffer" that lets us detect when a number exceeds int range BEFORE casting it to int. This is the critical difference from ft_atoi and why it's essential for push_swap.

---

## Location in Project

**File:** `srcs/parser.c` or `libft/ft_atol.c`
**Header:** `includes/push_swap.h` or `libft/libft.h`
**Phase in TODO:** Phase 2.4 (Parsing & Validation - String Conversion)

**Function prototype:**
```c
long ft_atol(const char *str);
```

---

## Related Functions

**Uses:**
- `ft_isdigit()` - Character validation

**Used by:**
- `init_stack_a()` - String to number conversion

**Related:**
- `is_valid_number()` - Format validation (call first)
- `is_int_range()` - Range validation (call after)
- `ft_atoi()` - Similar but returns int

---

*Remember: Trust but verify. Even with validation, using long for conversion gives you a critical safety check against overflow!*
