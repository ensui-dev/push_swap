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
4. **Handle multiple signs** - Correctly compute final sign from any number of +/- signs
5. **Handle leading zeros** - Naturally converts "007" to 7

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

**Multiple sign handling:**
```
Mathematical truth:
--42  = -(-42)  = +42 (double negative = positive)
---42 = -(--42) = -42 (triple negative = negative)
+-42  = +(-42)  = -42 (positive of negative = negative)

Each '-' flips the sign, '+' has no effect
```

---

## Deep Dive: How It Works

### The Conversion Algorithm

```
ASCII to Integer conversion with multiple signs:

String: "--42"
        ↓
Step 1: Process signs: '-' flips (sign=-1), '-' flips (sign=1)
        Final sign = positive
Step 2: Process '4' → 0 * 10 + 4 = 4
Step 3: Process '2' → 4 * 10 + 2 = 42
Step 4: Apply sign → 42 × 1 = 42
        ↓
Result: 42L
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

**Multiple sign calculation:**
```
Start with sign = 1 (positive)
Each '-' encountered: sign = sign × (-1)  (flip)
Each '+' encountered: sign = sign × 1     (no change)

Examples:
"--42":   sign = 1 → -1 → 1     = positive
"---42":  sign = 1 → -1 → 1 → -1 = negative
"+-42":   sign = 1 → 1 → -1     = negative
"+-+-42": sign = 1 → 1 → -1 → 1 → -1 = negative
```

### Step-by-Step Process

#### Step 1: NULL Check (Defensive Programming)

```c
if (!str)
    return (0);
```

**Why include this?**
- In push_swap, `is_valid_number` is called first, so `ft_atol` should never receive NULL
- However, this is good defensive programming practice
- Protects against bugs elsewhere in your code
- Costs nothing (one comparison)
- Returns 0 as a safe default

#### Step 2: Initialize Variables

```c
long result = 0;  // Accumulated value
int sign = 1;     // 1 for positive, -1 for negative
int i = 0;        // String index
```

#### Step 3: Skip Whitespace (Optional)

```c
while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
       str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
    i++;
```

**Note:** For push_swap, is_valid_number already rejected whitespace, so this step may be optional. However, standard atol includes it for robustness.

#### Step 3: Handle ALL Signs (Multiple Sign Support!)

```c
while (str[i] == '-' || str[i] == '+')
{
    if (str[i] == '-')
        sign *= -1;  // Each '-' flips the sign
    i++;
}
```

**Multiple sign handling:**
```
"--42":   sign starts at 1, '-' makes -1, '-' makes 1 → positive
"---42":  sign starts at 1, '-' makes -1, '-' makes 1, '-' makes -1 → negative
"+-42":   sign starts at 1, '+' keeps 1, '-' makes -1 → negative
"++++42": sign starts at 1, all '+' keep it at 1 → positive
```

#### Step 4: Convert Digits (Leading Zeros Handled Naturally!)

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

**Leading zeros handled automatically:**
```
"007"
Start: result = 0

Process '0':
  result = 0 * 10 + 0 = 0

Process '0':
  result = 0 * 10 + 0 = 0

Process '7':
  result = 0 * 10 + 7 = 7

Result: 7 (correct!)
```

#### Step 5: Apply Sign

```c
return (result * sign);
```

**Final value:**
```
Positive: result × 1 = result
Negative: result × (-1) = -result

"42"    → 42 × 1 = 42
"-42"   → 42 × (-1) = -42
"--42"  → 42 × 1 = 42
"---42" → 42 × (-1) = -42
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
STEP 1: Process signs
═══════════════════════════════════════
str[0] = '4' (not a sign)
Loop doesn't execute
sign remains 1 (positive)

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

### Example 2: Double Negative (NEW!)

```
Input: "--42"

═══════════════════════════════════════
INITIALIZATION
═══════════════════════════════════════
result = 0
sign = 1
i = 0

═══════════════════════════════════════
STEP 1: Process ALL signs
═══════════════════════════════════════
str[0] = '-' (is a sign!)
  sign = sign * (-1) = 1 * (-1) = -1
  i = 1

str[1] = '-' (is a sign!)
  sign = sign * (-1) = -1 * (-1) = 1
  i = 2

str[2] = '4' (not a sign)
  Loop exits

Final sign = 1 (positive!)
Two negatives cancel out ✓

═══════════════════════════════════════
STEP 2: Process '4'
═══════════════════════════════════════
str[2] = '4'
result = 0 * 10 + 4 = 4
i = 3

═══════════════════════════════════════
STEP 3: Process '2'
═══════════════════════════════════════
str[3] = '2'
result = 4 * 10 + 2 = 42
i = 4

═══════════════════════════════════════
STEP 4: End and apply sign
═══════════════════════════════════════
str[4] = '\0'
Loop exits

result = 42 * 1 = 42

═══════════════════════════════════════
RETURN
═══════════════════════════════════════
return 42L

Note: "--42" correctly converts to positive 42!
```

### Example 3: Mixed Signs (NEW!)

```
Input: "+-+-42"

═══════════════════════════════════════
INITIALIZATION
═══════════════════════════════════════
result = 0
sign = 1
i = 0

═══════════════════════════════════════
STEP 1: Process ALL signs
═══════════════════════════════════════
str[0] = '+' (is a sign!)
  sign = sign * 1 = 1 * 1 = 1   (no change)
  i = 1

str[1] = '-' (is a sign!)
  sign = sign * (-1) = 1 * (-1) = -1
  i = 2

str[2] = '+' (is a sign!)
  sign = sign * 1 = -1 * 1 = -1  (no change)
  i = 3

str[3] = '-' (is a sign!)
  sign = sign * (-1) = -1 * (-1) = 1
  i = 4

str[4] = '4' (not a sign)
  Loop exits

Final sign = 1 (positive!)
+, -, +, - → two negatives cancel → positive ✓

═══════════════════════════════════════
STEP 2-3: Process digits
═══════════════════════════════════════
'4': result = 4
'2': result = 42

═══════════════════════════════════════
STEP 4: Apply sign
═══════════════════════════════════════
result = 42 * 1 = 42

═══════════════════════════════════════
RETURN
═══════════════════════════════════════
return 42L
```

### Example 4: Leading Zeros (NEW!)

```
Input: "007"

═══════════════════════════════════════
INITIALIZATION
═══════════════════════════════════════
result = 0
sign = 1
i = 0

═══════════════════════════════════════
STEP 1: Process signs
═══════════════════════════════════════
str[0] = '0' (not a sign)
Loop doesn't execute
sign = 1

═══════════════════════════════════════
STEP 2: Process '0'
═══════════════════════════════════════
str[0] = '0'
result = 0 * 10 + 0 = 0
i = 1

═══════════════════════════════════════
STEP 3: Process '0'
═══════════════════════════════════════
str[1] = '0'
result = 0 * 10 + 0 = 0
i = 2

═══════════════════════════════════════
STEP 4: Process '7'
═══════════════════════════════════════
str[2] = '7'
result = 0 * 10 + 7 = 7
i = 3

═══════════════════════════════════════
STEP 5: Apply sign
═══════════════════════════════════════
result = 7 * 1 = 7

═══════════════════════════════════════
RETURN
═══════════════════════════════════════
return 7L

Note: "007" correctly converts to 7!
Leading zeros are naturally handled.
```

### Example 5: Combined - Multiple Signs AND Leading Zeros (NEW!)

```
Input: "--007"

═══════════════════════════════════════
STEP 1: Process signs
═══════════════════════════════════════
'-': sign = 1 * (-1) = -1
'-': sign = -1 * (-1) = 1
Final sign = 1 (positive)

═══════════════════════════════════════
STEP 2-4: Process digits
═══════════════════════════════════════
'0': result = 0
'0': result = 0
'7': result = 7

═══════════════════════════════════════
STEP 5: Apply sign
═══════════════════════════════════════
result = 7 * 1 = 7

═══════════════════════════════════════
RETURN
═══════════════════════════════════════
return 7L

Note: "--007" correctly converts to +7!
```

### Example 6: INT_MAX

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

### Example 7: Overflow Detection

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
    // Step 1: NULL check (defensive programming)
    IF str is NULL:
        RETURN 0

    // Step 2: Initialize
    result = 0
    sign = 1
    i = 0

    // Step 3: Skip leading whitespace (optional for push_swap)
    WHILE str[i] is whitespace:
        i = i + 1

    // Step 4: Handle ALL signs (multiple sign support!)
    WHILE str[i] is '-' OR str[i] is '+':
        IF str[i] is '-':
            sign = sign * (-1)  // Flip sign
        // '+' does nothing (sign * 1 = sign)
        i = i + 1

    // Step 5: Convert digits (leading zeros handled naturally)
    WHILE str[i] is digit:
        digit_value = str[i] - '0'
        result = result * 10 + digit_value
        i = i + 1

    // Step 6: Apply sign and return
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

### Edge Case 3: Double Negative Zero

```c
long result = ft_atol("--0");
// result = 0L (double negative = positive, but 0 is 0)
```

### Edge Case 4: Leading Zeros (NEW!)

```c
long result1 = ft_atol("007");
// result1 = 7L

long result2 = ft_atol("00123");
// result2 = 123L

long result3 = ft_atol("000");
// result3 = 0L
```

### Edge Case 5: Multiple Signs (NEW!)

```c
long result1 = ft_atol("--42");
// result1 = 42L (double negative = positive)

long result2 = ft_atol("---42");
// result2 = -42L (triple negative = negative)

long result3 = ft_atol("+-42");
// result3 = -42L (positive × negative = negative)

long result4 = ft_atol("-+-+42");
// result4 = 42L (count negatives: 2 → positive)
```

### Edge Case 6: Combined Signs and Leading Zeros (NEW!)

```c
long result1 = ft_atol("--007");
// result1 = 7L (double neg = pos, 007 = 7)

long result2 = ft_atol("+-00123");
// result2 = -123L (one neg = neg, 00123 = 123)
```

### Edge Case 7: INT_MAX

```c
long result = ft_atol("2147483647");
// result = 2147483647L
// Fits in int ✓
```

### Edge Case 8: INT_MIN

```c
long result = ft_atol("-2147483648");
// result = -2147483648L
// Fits in int ✓
```

### Edge Case 9: Just Over INT_MAX

```c
long result = ft_atol("2147483648");
// result = 2147483648L
// Doesn't fit in int! ✗
// Must check with is_int_range()
```

### Edge Case 10: Very Large Number

```c
long result = ft_atol("999999999999");
// result = 999999999999L
// Way over INT_MAX ✗
// is_int_range() will catch this
```

### Edge Case 11: Single Digit

```c
long result = ft_atol("5");
// result = 5L
```

### Edge Case 12: Many Signs

```c
long result = ft_atol("------42");
// Six negatives = positive (even count)
// result = 42L

long result2 = ft_atol("-------42");
// Seven negatives = negative (odd count)
// result2 = -42L
```

---

## Time & Space Complexity

### Time Complexity: O(n)

```
n = length of string

Operations:
- Initialize: O(1)
- Skip whitespace: O(w) where w = whitespace count
- Process signs: O(s) where s = sign count
- Process digits: O(d) where d = digit count
  - Each iteration: O(1)
  - Runs d times

Total: O(1) + O(w) + O(s) + O(d) = O(n)
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

## Comparison with Standard atol

### Key Difference: Multiple Sign Support

```c
// Standard atol only handles single sign:
atol("--42");  // Undefined or stops at second '-'

// Our ft_atol handles multiple signs:
ft_atol("--42");  // Returns 42 (mathematically correct!)
```

### Why This Matters

The 42 subject says input must be "integers". Mathematically:
- `--42` IS the integer 42
- `---42` IS the integer -42
- This is defensible during evaluation

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

---

## Relationship with Other Functions

### Functions Called By ft_atol

- **ft_isdigit()** - Checks if character is digit

### Functions That Use ft_atol

- **init_stack_a()** - Converts validated strings to numbers

### Related Functions

- **is_valid_number()** - Called BEFORE ft_atol (validates format)
- **is_int_range()** - Called AFTER ft_atol (validates range)
- **ft_atoi()** - Similar but returns int

---

## Integration with Push_swap

### Typical Usage Flow

```c
// In init_stack_a:
while (numbers[i])
{
    // Step 1: Validate format (handles multiple signs, leading zeros)
    if (!is_valid_number(numbers[i]))
        return (error_cleanup());

    // Step 2: Convert to long (correctly computes sign)
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

✅ **Function length:** ~20 lines (under 25-line limit)
✅ **Single responsibility:** Only converts string to long
✅ **No global variables:** Everything is local
✅ **Clear variable names:** result, sign, i
✅ **While loops:** No for loops (42 Norm compliant)

### Implementation Example

```c
long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		i;

	if (!str)
		return (0);
	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
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

**Line count:** ~22 lines ✓

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

### Mistake 2: Only Handling Single Sign (OLD approach)

```c
❌ OLD/RESTRICTIVE:
if (str[i] == '-')
{
    sign = -1;
    i++;
}
else if (str[i] == '+')
    i++;
// Only handles ONE sign

✓ NEW/FLEXIBLE:
while (str[i] == '-' || str[i] == '+')
{
    if (str[i] == '-')
        sign *= -1;  // FLIP the sign
    i++;
}
// Handles ANY number of signs
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

### Mistake 4: Assuming Input is Valid

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

### Test Case 4: Multiple Signs (NEW!)

```c
assert(ft_atol("--42") == 42);      // Double negative = positive
assert(ft_atol("---42") == -42);    // Triple negative = negative
assert(ft_atol("----42") == 42);    // Four negatives = positive
assert(ft_atol("+-42") == -42);     // Plus then minus = negative
assert(ft_atol("-+42") == -42);     // Minus then plus = negative
assert(ft_atol("+-+-42") == 42);    // Two negatives = positive
assert(ft_atol("-+-+42") == -42);   // Two negatives, one at start = negative
```

### Test Case 5: Leading Zeros (NEW!)

```c
assert(ft_atol("007") == 7);
assert(ft_atol("042") == 42);
assert(ft_atol("00123") == 123);
assert(ft_atol("000") == 0);
assert(ft_atol("-007") == -7);
assert(ft_atol("+007") == 7);
```

### Test Case 6: Combined - Multiple Signs AND Leading Zeros (NEW!)

```c
assert(ft_atol("--007") == 7);      // Double neg + leading zeros
assert(ft_atol("+-00123") == -123); // Mixed signs + leading zeros
assert(ft_atol("---00042") == -42); // Triple neg + leading zeros
```

### Test Case 7: Overflow Detection

```c
long result1 = ft_atol("2147483648");  // INT_MAX + 1
assert(result1 == 2147483648L);
assert(!is_int_range(result1));  // Should be out of range

long result2 = ft_atol("-2147483649");  // INT_MIN - 1
assert(result2 == -2147483649L);
assert(!is_int_range(result2));  // Should be out of range
```

### Test Case 8: Edge Values

```c
assert(ft_atol("-0") == 0);
assert(ft_atol("+0") == 0);
assert(ft_atol("--0") == 0);
```

---

## Summary: What ft_atol Does

1. **Skips** leading whitespace (optional)
2. **Processes** ALL signs (+/-) and computes final sign
3. **Accumulates** digit values using base-10 math
4. **Handles** leading zeros naturally (they contribute 0)
5. **Applies** final sign to result
6. **Returns** long integer value
7. **Enables** overflow detection by using long type

**Key insight:** By returning long instead of int, we create a "safety buffer" that lets us detect when a number exceeds int range BEFORE casting it to int. This is the critical difference from ft_atoi and why it's essential for push_swap.

**Design decision:** We handle multiple signs because:
- Mathematically, `--42` IS the integer 42
- Mathematically, `---42` IS the integer -42
- The 42 subject says input must be "integers" - these ARE valid representations
- `is_valid_number()` now accepts multiple signs, so `ft_atol` must handle them

---

## Location in Project

**File:** `srcs/validate.c` (or optionally `libft/ft_atol.c`)
**Header:** `includes/push_swap.h` (or `libft/libft.h` if in libft)
**Phase in TODO:** Phase 2.2 (Parsing & Validation - Number Validation)

**Note:** This function is in `validate.c` (not `parser.c`) to comply with 42 Norm's
5 functions per file limit. Parser.c contains parse_arguments + 2 static helpers.

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
- `is_valid_number()` - Format validation (call first, now accepts multiple signs)
- `is_int_range()` - Range validation (call after)
- `ft_atoi()` - Similar but returns int

---

*Remember: Trust but verify. Even with validation, using long for conversion gives you a critical safety check against overflow!*