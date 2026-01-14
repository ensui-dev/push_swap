# is_valid_number - Validate Number String Format

## Function Signature

```c
int is_valid_number(char *str)
```

**Return type:** `int` - Returns 1 if valid format, 0 if invalid
**Parameter:** `char *str` - String to validate as a number

---

## Purpose & Use Case

`is_valid_number` is a **format validation function** that checks if a string represents a properly formatted integer. This is your first line of defense against invalid input, catching format errors before attempting conversion.

### When You'll Use It

You'll call `is_valid_number` to:
1. **Validate before conversion** - Check format before calling ft_atol
2. **Catch format errors** - Detect letters, symbols, empty strings
3. **Prevent conversion errors** - Ensure ft_atol receives valid input
4. **Provide clear error messages** - Know exactly what went wrong

### Why This Matters

**Input validation examples:**
```
Valid formats:
"42"         → Pure digits ✓
"-42"        → Negative number ✓
"+42"        → Explicit positive ✓
"0"          → Zero ✓
"-0"         → Negative zero (valid but equals 0) ✓

Invalid formats:
""           → Empty string ✗
"abc"        → Letters ✗
"4a2"        → Mixed letters and digits ✗
"--42"       → Double sign ✗
"42+"        → Sign in wrong place ✗
"4 2"        → Contains space ✗
"042"        → Leading zero ✗
"+00"        → Leading zeros after sign ✗
```

---

## Deep Dive: How It Works

### The Validation Rules

```
A valid number string must satisfy:
1. Not NULL
2. Not empty
3. Optional single sign (+/-) at start
4. At least one digit
5. Only digits after optional sign
6. No leading zeros (except "0", "+0", "-0")
```

### Step-by-Step Process

#### Step 1: Check for NULL or Empty

```c
if (!str || !str[0])
    return (0);  // NULL pointer or empty string
```

**Why check both?**
- `!str`: Protects against NULL pointer dereferencing
- `!str[0]`: Catches empty string ""
- Both are invalid number formats

#### Step 2: Handle Optional Sign

```c
int i = 0;
if (str[i] == '+' || str[i] == '-')
    i++;  // Skip sign character
```

**Sign handling:**
```
"+42"  → Skip '+', start checking from '4'
"-42"  → Skip '-', start checking from '4'
"42"   → No sign, start checking from '4'
```

#### Step 3: Check for Digits After Sign

```c
if (!str[i])
    return (0);  // Only sign, no digits ("+", "-")
```

**Invalid cases:**
```
"+"    → Sign only, no number ✗
"-"    → Sign only, no number ✗
""     → Empty (caught earlier) ✗
```

#### Step 4: Check for Leading Zeros

```c
if (str[i] == '0' && str[i + 1])
    return (0);  // Leading zero with more digits
```

**Leading zero rules:**
```
"0"      → Valid, single zero ✓
"-0"     → Valid, negative zero ✓
"+0"     → Valid, positive zero ✓
"042"    → Invalid, leading zero ✗
"-007"   → Invalid, leading zeros ✗
"00"     → Invalid, multiple zeros ✗
```

**Why no leading zeros?**
- Ambiguity with octal notation (042 = 34 in octal)
- Project requirements specify no leading zeros
- Cleaner, unambiguous representation

#### Step 5: Validate Remaining Digits

```c
while (str[i])
{
    if (!ft_isdigit(str[i]))
        return (0);  // Found non-digit character
    i++;
}
```

**Character validation:**
```
For each character:
'0'-'9' → Valid digit ✓
'a'-'z' → Invalid letter ✗
'A'-'Z' → Invalid letter ✗
' '     → Invalid space ✗
'.'     → Invalid decimal point ✗
Any other → Invalid ✗
```

#### Step 6: All Checks Passed

```c
return (1);  // Valid number format!
```

---

## Visual Execution Trace

### Example 1: Valid Positive Number

```
Input: "42"

Step 1: Check NULL/empty
str = "42" (not NULL, not empty) ✓

Step 2: Check for sign
str[0] = '4' (not '+' or '-')
i = 0 (no sign to skip)

Step 3: Check digits exist
str[0] = '4' (exists) ✓

Step 4: Check leading zeros
str[0] = '4' (not '0')
No leading zero ✓

Step 5: Validate all digits
i = 0: str[0] = '4' → ft_isdigit('4') = 1 ✓
i = 1: str[1] = '2' → ft_isdigit('2') = 1 ✓
i = 2: str[2] = '\0' → loop exits

Step 6: Return success
return (1) ✓
```

### Example 2: Valid Negative Number

```
Input: "-42"

Step 1: Check NULL/empty
str = "-42" ✓

Step 2: Check for sign
str[0] = '-' (is a sign!)
i = 1 (skip the '-')

Step 3: Check digits exist
str[1] = '4' (exists) ✓

Step 4: Check leading zeros
str[1] = '4' (not '0') ✓

Step 5: Validate digits
i = 1: str[1] = '4' → ft_isdigit('4') = 1 ✓
i = 2: str[2] = '2' → ft_isdigit('2') = 1 ✓
i = 3: str[3] = '\0' → loop exits

Step 6: Return success
return (1) ✓
```

### Example 3: Invalid - Letters in Number

```
Input: "4a2"

Step 1: Check NULL/empty
str = "4a2" ✓

Step 2: Check for sign
str[0] = '4' (not a sign)
i = 0

Step 3: Check digits exist
str[0] = '4' ✓

Step 4: Check leading zeros
str[0] = '4' (not '0') ✓

Step 5: Validate digits
i = 0: str[0] = '4' → ft_isdigit('4') = 1 ✓
i = 1: str[1] = 'a' → ft_isdigit('a') = 0 ✗

Found non-digit!
return (0) ✗
```

### Example 4: Invalid - Leading Zero

```
Input: "042"

Step 1: Check NULL/empty
str = "042" ✓

Step 2: Check for sign
str[0] = '0' (not a sign)
i = 0

Step 3: Check digits exist
str[0] = '0' ✓

Step 4: Check leading zeros
str[0] = '0' AND str[1] = '4' (exists)
Leading zero detected! ✗

return (0) ✗
```

### Example 5: Invalid - Sign Only

```
Input: "-"

Step 1: Check NULL/empty
str = "-" (not empty) ✓

Step 2: Check for sign
str[0] = '-' (is a sign)
i = 1

Step 3: Check digits exist
str[1] = '\0' (no digits after sign!) ✗

return (0) ✗
```

### Example 6: Valid - Zero

```
Input: "0"

Step 1: Check NULL/empty
str = "0" ✓

Step 2: Check for sign
str[0] = '0' (not a sign)
i = 0

Step 3: Check digits exist
str[0] = '0' ✓

Step 4: Check leading zeros
str[0] = '0' BUT str[1] = '\0' (no more digits)
Single zero is OK ✓

Step 5: Validate digits
i = 0: str[0] = '0' → ft_isdigit('0') = 1 ✓
i = 1: str[1] = '\0' → loop exits

Step 6: Return success
return (1) ✓
```

---

## Complete Algorithm Pseudocode

```
FUNCTION is_valid_number(str):
    // Step 1: Check for NULL or empty string
    IF str is NULL OR str[0] is '\0':
        RETURN 0

    // Step 2: Initialize index
    i = 0

    // Step 3: Handle optional sign
    IF str[i] is '+' OR str[i] is '-':
        i = i + 1

    // Step 4: Must have at least one digit after sign
    IF str[i] is '\0':
        RETURN 0  // Sign only, no digits

    // Step 5: Check for invalid leading zeros
    IF str[i] is '0' AND str[i + 1] is not '\0':
        RETURN 0  // Leading zero with more digits

    // Step 6: Validate all remaining characters are digits
    WHILE str[i] is not '\0':
        IF NOT ft_isdigit(str[i]):
            RETURN 0  // Non-digit character found
        i = i + 1

    // Step 7: All checks passed
    RETURN 1
END FUNCTION
```

---

## Edge Cases

### Edge Case 1: NULL String

```c
char *str = NULL;
int result = is_valid_number(str);
// result = 0 (invalid)
```

### Edge Case 2: Empty String

```c
char *str = "";
int result = is_valid_number(str);
// result = 0 (invalid)
```

### Edge Case 3: Just a Sign

```c
int result1 = is_valid_number("+");  // 0 (invalid)
int result2 = is_valid_number("-");  // 0 (invalid)
```

### Edge Case 4: Double Sign

```c
int result = is_valid_number("--42");
// First '-' is treated as sign
// Second '-' fails ft_isdigit check
// result = 0 (invalid)
```

### Edge Case 5: Zero Variants

```c
int result1 = is_valid_number("0");    // 1 (valid)
int result2 = is_valid_number("+0");   // 1 (valid)
int result3 = is_valid_number("-0");   // 1 (valid)
int result4 = is_valid_number("00");   // 0 (invalid - leading zero)
int result5 = is_valid_number("000");  // 0 (invalid - leading zeros)
```

### Edge Case 6: INT_MIN

```c
char *str = "-2147483648";
int result = is_valid_number(str);
// result = 1 (valid format)
// Note: Range checking happens in is_int_range, not here
```

### Edge Case 7: Very Large Number

```c
char *str = "999999999999999999";
int result = is_valid_number(str);
// result = 1 (valid format!)
// Overflow checking happens in is_int_range, not here
// This function only checks FORMAT
```

### Edge Case 8: Special Characters

```c
int result1 = is_valid_number("4.2");   // 0 (decimal point invalid)
int result2 = is_valid_number("4,2");   // 0 (comma invalid)
int result3 = is_valid_number("4 2");   // 0 (space invalid)
int result4 = is_valid_number("4\t2");  // 0 (tab invalid)
```

---

## Time & Space Complexity

### Time Complexity: O(n)

```
n = length of string

Operations:
- Check NULL/empty: O(1)
- Skip sign: O(1)
- Leading zero check: O(1)
- Loop through all characters: O(n)
  - Each ft_isdigit call: O(1)
  - n iterations total

Total: O(1) + O(1) + O(n) = O(n)
```

**Best case: O(1)**
```
Input: NULL or "" or "+" or "-"
Caught immediately without loop
```

**Worst case: O(n)**
```
Input: "123456789"
Must check every character
```

### Space Complexity: O(1)

```
Variables used:
- i (index): 4 bytes
- No arrays
- No recursion
- No allocations

Total: O(1) - constant space
```

---

## Relationship with Other Functions

### Functions Called By is_valid_number

- **ft_isdigit()** - Checks if character is digit ('0'-'9')

### Functions That Use is_valid_number

- **init_stack_a()** - Validates each parsed number string
- **parse_and_validate()** - Helper function in parsing phase

---

## Integration with Push_swap

### Usage in init_stack_a()

```c
t_stack *init_stack_a(int argc, char **argv)
{
    char    **numbers;
    t_stack *stack_a;
    int     i;

    numbers = parse_arguments(argc, argv);
    if (!numbers)
        return (NULL);

    stack_a = NULL;
    i = 0;
    while (numbers[i])
    {
        // FIRST: Validate format
        if (!is_valid_number(numbers[i]))
        {
            // Invalid format! Clean up and error
            free_stack(&stack_a);
            if (argc == 2)
                free_split(numbers);
            return (NULL);
        }

        // THEN: Safe to convert
        long value = ft_atol(numbers[i]);
        // ... rest of processing
        i++;
    }
    // ...
}
```

---

## 42 Norm Considerations

### Norm Compliance

✅ **Function length:** 15-20 lines (well under 25-line limit)
✅ **Single responsibility:** Only checks format validity
✅ **Clear logic flow:** Sequential checks, early returns
✅ **No global variables:** Everything is local
✅ **Proper naming:** Clear, descriptive function name

### Implementation Example

```c
int is_valid_number(char *str)
{
    int i;

    if (!str || !str[0])
        return (0);
    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (!str[i])
        return (0);
    if (str[i] == '0' && str[i + 1])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}
```

---

## Common Mistakes to Avoid

### Mistake 1: Not Checking for NULL

```c
❌ WRONG:
int is_valid_number(char *str)
{
    if (str[0] == '\0')  // CRASH if str is NULL!
        return (0);
    // ...
}

✓ CORRECT:
if (!str || !str[0])
    return (0);
```

### Mistake 2: Allowing Multiple Signs

```c
❌ WRONG:
// Only checking if first char is sign
// Doesn't catch "--42" or "+-42"

✓ CORRECT:
// After skipping one sign, check all remaining are digits
```

### Mistake 3: Forgetting Leading Zero Check

```c
❌ WRONG:
// Just checking all digits
// Allows "042", "007", etc.

✓ CORRECT:
if (str[i] == '0' && str[i + 1])
    return (0);
```

### Mistake 4: Allowing Spaces

```c
❌ WRONG:
// Forgetting to check for spaces
// "4 2" would pass digit checks on '4' and '2'

✓ CORRECT:
// ft_isdigit catches space as non-digit
```

### Mistake 5: Not Checking After Sign

```c
❌ WRONG:
if (str[i] == '+' || str[i] == '-')
    i++;
// What if string is just "+" or "-"?

✓ CORRECT:
if (str[i] == '+' || str[i] == '-')
    i++;
if (!str[i])
    return (0);
```

---

## Testing Strategy

### Test Case 1: Valid Numbers

```c
assert(is_valid_number("42") == 1);
assert(is_valid_number("-42") == 1);
assert(is_valid_number("+42") == 1);
assert(is_valid_number("0") == 1);
assert(is_valid_number("-0") == 1);
assert(is_valid_number("2147483647") == 1);  // INT_MAX
assert(is_valid_number("-2147483648") == 1); // INT_MIN
```

### Test Case 2: Invalid Format

```c
assert(is_valid_number("") == 0);
assert(is_valid_number(NULL) == 0);
assert(is_valid_number("+") == 0);
assert(is_valid_number("-") == 0);
assert(is_valid_number("abc") == 0);
assert(is_valid_number("4a2") == 0);
assert(is_valid_number("--42") == 0);
assert(is_valid_number("4 2") == 0);
```

### Test Case 3: Leading Zeros

```c
assert(is_valid_number("042") == 0);
assert(is_valid_number("-007") == 0);
assert(is_valid_number("+00") == 0);
assert(is_valid_number("00") == 0);
```

### Test Case 4: Edge Cases

```c
assert(is_valid_number("999999999999999") == 1);  // Format valid
assert(is_valid_number("4.2") == 0);   // Decimal point
assert(is_valid_number("4,2") == 0);   // Comma
assert(is_valid_number("42+") == 0);   // Sign at end
```

---

## Summary: What is_valid_number Does

1. **Checks** string is not NULL or empty
2. **Handles** optional sign (+/-) at start
3. **Ensures** at least one digit exists
4. **Rejects** leading zeros (except single "0")
5. **Validates** all characters are digits
6. **Returns** 1 for valid format, 0 for invalid

**Key insight:** This function only checks FORMAT, not VALUE. A string like "999999999999" is valid format even though it exceeds INT_MAX. Range checking happens separately in is_int_range().

---

## Location in Project

**File:** `srcs/parser.c` or `srcs/validation.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 2.3 (Parsing & Validation - Format Validation)

**Function prototype:**
```c
int is_valid_number(char *str);
```

---

## Related Functions

**Uses:**
- `ft_isdigit()` - Character validation

**Used by:**
- `init_stack_a()` - Pre-conversion validation

**Related validators:**
- `ft_atol()` - String to number conversion (called after this)
- `is_int_range()` - Range validation (called after conversion)
- `has_duplicates()` - Value validation (called after stack built)

---

*Remember: Validate early, validate thoroughly. Catching format errors here prevents crashes and undefined behavior in conversion functions!*
