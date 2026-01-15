# is_valid_number - Validate Number String Format

## Function Signature

```c
int is_valid_number(char *str)
```

**Return type:** `int` - Returns 1 if valid format, 0 if invalid
**Parameter:** `char *str` - String to validate as a number

---

## Purpose & Use Case

`is_valid_number` is a **format validation function** that checks if a string represents a valid integer. This is your first line of defense against invalid input, catching format errors before attempting conversion.

### When You'll Use It

You'll call `is_valid_number` to:
1. **Validate before conversion** - Check format before calling ft_atol
2. **Catch format errors** - Detect letters, symbols, empty strings
3. **Prevent conversion errors** - Ensure ft_atol receives valid input
4. **Provide clear error messages** - Know exactly what went wrong

### Why This Matters

**Input validation examples:**
```
Valid formats (mathematically correct integers):
"42"         → Pure digits ✓
"-42"        → Negative number ✓
"+42"        → Explicit positive ✓
"0"          → Zero ✓
"-0"         → Negative zero (valid, equals 0) ✓
"--42"       → Double negative = positive 42 ✓
"---42"      → Triple negative = negative 42 ✓
"+-42"       → Mixed signs = negative 42 ✓
"-+-+42"     → Multiple mixed = positive 42 ✓
"042"        → Leading zero = 42 ✓
"-007"       → Leading zeros = -7 ✓
"+00123"     → Leading zeros = 123 ✓

Invalid formats:
""           → Empty string ✗
"abc"        → Letters ✗
"4a2"        → Mixed letters and digits ✗
"42+"        → Sign in wrong place (must be at start) ✗
"4 2"        → Contains space ✗
"+"          → Sign only, no digits ✗
"-"          → Sign only, no digits ✗
"--"         → Signs only, no digits ✗
```

### Design Philosophy

The 42 subject specifies that input must be "integers". Mathematically:
- `007` **is** the integer 7
- `--42` **is** the integer 42 (negative of negative)
- `+-42` **is** the integer -42

By accepting these formats, we're being **mathematically correct** rather than overly pedantic about representation. This approach is defensible during evaluation because it correctly parses any valid integer representation.

---

## Deep Dive: How It Works

### The Validation Rules

```
A valid number string must satisfy:
1. Not NULL
2. Not empty (after processing signs)
3. Zero or more signs (+/-) at start (all processed to determine final sign)
4. At least one digit after all signs
5. Only digits after all signs
6. Leading zeros allowed (they're mathematically valid)
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

#### Step 2: Skip All Leading Signs

```c
int i = 0;
while (str[i] == '+' || str[i] == '-')
    i++;  // Skip ALL sign characters
```

**Multiple sign handling:**
```
"--42"    → Skip '-', skip '-', start checking from '4'
"+-+-42"  → Skip '+', '-', '+', '-', start checking from '4'
"-42"     → Skip '-', start checking from '4'
"42"      → No signs to skip, start from '4'
```

**Note:** The actual sign calculation (positive/negative) happens in `ft_atol`, not here.
This function only validates FORMAT - whether the string CAN represent an integer.

#### Step 3: Check for Digits After Signs

```c
if (!str[i])
    return (0);  // Only signs, no digits
```

**Invalid cases:**
```
"+"      → Sign only, no number ✗
"-"      → Sign only, no number ✗
"--"     → Signs only, no number ✗
"+-+-"   → Signs only, no number ✗
""       → Empty (caught earlier) ✗
```

#### Step 4: Validate All Remaining Characters Are Digits

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
For each character after signs:
'0'-'9' → Valid digit ✓
'a'-'z' → Invalid letter ✗
'A'-'Z' → Invalid letter ✗
' '     → Invalid space ✗
'.'     → Invalid decimal point ✗
'+'/'-' → Invalid (sign in wrong place) ✗
Any other → Invalid ✗
```

**Leading zeros are allowed:**
```
"042"    → Digits '0', '4', '2' all valid ✓
"-007"   → Digits '0', '0', '7' all valid ✓
"000"    → Digits '0', '0', '0' all valid ✓ (equals 0)
```

#### Step 5: All Checks Passed

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

Step 2: Skip signs
str[0] = '4' (not '+' or '-')
i = 0 (no signs to skip)

Step 3: Check digits exist
str[0] = '4' (exists) ✓

Step 4: Validate all digits
i = 0: str[0] = '4' → ft_isdigit('4') = 1 ✓
i = 1: str[1] = '2' → ft_isdigit('2') = 1 ✓
i = 2: str[2] = '\0' → loop exits

Step 5: Return success
return (1) ✓
```

### Example 2: Valid Negative Number

```
Input: "-42"

Step 1: Check NULL/empty
str = "-42" ✓

Step 2: Skip signs
str[0] = '-' (is a sign!) → i = 1
str[1] = '4' (not a sign) → stop

Step 3: Check digits exist
str[1] = '4' (exists) ✓

Step 4: Validate digits
i = 1: str[1] = '4' → ft_isdigit('4') = 1 ✓
i = 2: str[2] = '2' → ft_isdigit('2') = 1 ✓
i = 3: str[3] = '\0' → loop exits

Step 5: Return success
return (1) ✓
```

### Example 3: Valid Double Negative (NEW!)

```
Input: "--42"

Step 1: Check NULL/empty
str = "--42" ✓

Step 2: Skip ALL signs
str[0] = '-' (is a sign!) → i = 1
str[1] = '-' (is a sign!) → i = 2
str[2] = '4' (not a sign) → stop

Step 3: Check digits exist
str[2] = '4' (exists) ✓

Step 4: Validate digits
i = 2: str[2] = '4' → ft_isdigit('4') = 1 ✓
i = 3: str[3] = '2' → ft_isdigit('2') = 1 ✓
i = 4: str[4] = '\0' → loop exits

Step 5: Return success
return (1) ✓

Note: ft_atol will calculate that -- means positive
```

### Example 4: Valid Leading Zeros (NEW!)

```
Input: "007"

Step 1: Check NULL/empty
str = "007" ✓

Step 2: Skip signs
str[0] = '0' (not a sign)
i = 0

Step 3: Check digits exist
str[0] = '0' ✓

Step 4: Validate digits
i = 0: str[0] = '0' → ft_isdigit('0') = 1 ✓
i = 1: str[1] = '0' → ft_isdigit('0') = 1 ✓
i = 2: str[2] = '7' → ft_isdigit('7') = 1 ✓
i = 3: str[3] = '\0' → loop exits

Step 5: Return success
return (1) ✓

Note: ft_atol will convert this to 7
```

### Example 5: Valid Mixed Signs (NEW!)

```
Input: "+-+-42"

Step 1: Check NULL/empty
str = "+-+-42" ✓

Step 2: Skip ALL signs
str[0] = '+' → i = 1
str[1] = '-' → i = 2
str[2] = '+' → i = 3
str[3] = '-' → i = 4
str[4] = '4' (not a sign) → stop

Step 3: Check digits exist
str[4] = '4' (exists) ✓

Step 4: Validate digits
i = 4: str[4] = '4' → ft_isdigit('4') = 1 ✓
i = 5: str[5] = '2' → ft_isdigit('2') = 1 ✓
i = 6: str[6] = '\0' → loop exits

Step 5: Return success
return (1) ✓

Note: ft_atol will count signs: +, -, +, - = positive 42
```

### Example 6: Invalid - Letters in Number

```
Input: "4a2"

Step 1: Check NULL/empty
str = "4a2" ✓

Step 2: Skip signs
str[0] = '4' (not a sign)
i = 0

Step 3: Check digits exist
str[0] = '4' ✓

Step 4: Validate digits
i = 0: str[0] = '4' → ft_isdigit('4') = 1 ✓
i = 1: str[1] = 'a' → ft_isdigit('a') = 0 ✗

Found non-digit!
return (0) ✗
```

### Example 7: Invalid - Sign Only

```
Input: "--"

Step 1: Check NULL/empty
str = "--" (not empty) ✓

Step 2: Skip ALL signs
str[0] = '-' → i = 1
str[1] = '-' → i = 2
str[2] = '\0' (not a sign) → stop

Step 3: Check digits exist
str[2] = '\0' (no digits after signs!) ✗

return (0) ✗
```

### Example 8: Invalid - Sign in Middle

```
Input: "4+2"

Step 1: Check NULL/empty
str = "4+2" ✓

Step 2: Skip signs
str[0] = '4' (not a sign)
i = 0

Step 3: Check digits exist
str[0] = '4' ✓

Step 4: Validate digits
i = 0: str[0] = '4' → ft_isdigit('4') = 1 ✓
i = 1: str[1] = '+' → ft_isdigit('+') = 0 ✗

Found non-digit!
return (0) ✗
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

    // Step 3: Skip ALL leading signs (handles multiple signs)
    WHILE str[i] is '+' OR str[i] is '-':
        i = i + 1

    // Step 4: Must have at least one digit after all signs
    IF str[i] is '\0':
        RETURN 0  // Signs only, no digits

    // Step 5: Validate all remaining characters are digits
    // (Leading zeros allowed - they're mathematically valid)
    WHILE str[i] is not '\0':
        IF NOT ft_isdigit(str[i]):
            RETURN 0  // Non-digit character found
        i = i + 1

    // Step 6: All checks passed
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

### Edge Case 3: Just Signs (No Digits)

```c
int result1 = is_valid_number("+");    // 0 (invalid)
int result2 = is_valid_number("-");    // 0 (invalid)
int result3 = is_valid_number("--");   // 0 (invalid)
int result4 = is_valid_number("+-+-"); // 0 (invalid)
```

### Edge Case 4: Multiple Signs (Valid!)

```c
int result1 = is_valid_number("--42");   // 1 (valid!) = +42
int result2 = is_valid_number("---42");  // 1 (valid!) = -42
int result3 = is_valid_number("+-42");   // 1 (valid!) = -42
int result4 = is_valid_number("-+-+42"); // 1 (valid!) = +42
```

### Edge Case 5: Leading Zeros (Valid!)

```c
int result1 = is_valid_number("0");     // 1 (valid)
int result2 = is_valid_number("00");    // 1 (valid!) = 0
int result3 = is_valid_number("007");   // 1 (valid!) = 7
int result4 = is_valid_number("-007");  // 1 (valid!) = -7
int result5 = is_valid_number("000");   // 1 (valid!) = 0
int result6 = is_valid_number("+0042"); // 1 (valid!) = 42
```

### Edge Case 6: Combined - Multiple Signs AND Leading Zeros

```c
int result1 = is_valid_number("--007");   // 1 (valid!) = +7
int result2 = is_valid_number("+-00123"); // 1 (valid!) = -123
```

### Edge Case 7: INT_MIN and INT_MAX Strings

```c
char *str1 = "-2147483648";
int result1 = is_valid_number(str1);
// result1 = 1 (valid format)

char *str2 = "2147483647";
int result2 = is_valid_number(str2);
// result2 = 1 (valid format)

// Note: Range checking happens in is_int_range, not here
```

### Edge Case 8: Very Large Number

```c
char *str = "999999999999999999";
int result = is_valid_number(str);
// result = 1 (valid format!)
// Overflow checking happens in is_int_range, not here
// This function only checks FORMAT
```

### Edge Case 9: Special Characters

```c
int result1 = is_valid_number("4.2");   // 0 (decimal point invalid)
int result2 = is_valid_number("4,2");   // 0 (comma invalid)
int result3 = is_valid_number("4 2");   // 0 (space invalid)
int result4 = is_valid_number("4\t2");  // 0 (tab invalid)
int result5 = is_valid_number("42+");   // 0 (sign at end invalid)
int result6 = is_valid_number("4+2");   // 0 (sign in middle invalid)
```

---

## Time & Space Complexity

### Time Complexity: O(n)

```
n = length of string

Operations:
- Check NULL/empty: O(1)
- Skip all signs: O(s) where s = number of signs
- Loop through remaining characters: O(n - s)
  - Each ft_isdigit call: O(1)

Total: O(1) + O(s) + O(n - s) = O(n)
```

**Best case: O(1)**
```
Input: NULL or "" or "+-+-" (signs only)
Caught immediately after sign loop
```

**Worst case: O(n)**
```
Input: "123456789" or "---123456789"
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
t_stack *init_stack_a(char **numbers)
{
    t_stack *stack_a;
    int     i;

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
            return (NULL);
        }

        // THEN: Safe to convert (handles signs and leading zeros)
        long value = ft_atol(numbers[i]);

        // Check range
        if (!is_int_range(value))
        {
            free_stack(&stack_a);
            return (NULL);
        }

        // ... create node and add to stack
        i++;
    }
    // ...
}
```

---

## 42 Norm Considerations

### Norm Compliance

✅ **Function length:** ~15 lines (well under 25-line limit)
✅ **Single responsibility:** Only checks format validity
✅ **Clear logic flow:** Sequential checks, early returns
✅ **No global variables:** Everything is local
✅ **Proper naming:** Clear, descriptive function name
✅ **While loops:** No for loops (42 Norm compliant)

### Implementation Example

```c
int	is_valid_number(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
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

**Line count:** 14 lines - very concise! ✓

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

### Mistake 2: Only Allowing Single Sign (OLD approach)

```c
❌ OLD/RESTRICTIVE:
if (str[i] == '+' || str[i] == '-')
    i++;  // Only skip ONE sign
// Rejects "--42", "+-42", etc.

✓ NEW/FLEXIBLE:
while (str[i] == '+' || str[i] == '-')
    i++;  // Skip ALL signs
// Accepts any number of leading signs
```

### Mistake 3: Rejecting Leading Zeros (OLD approach)

```c
❌ OLD/RESTRICTIVE:
if (str[i] == '0' && str[i + 1])
    return (0);  // Rejects "007", "042"

✓ NEW/FLEXIBLE:
// Simply don't include this check
// Leading zeros are mathematically valid
// ft_atol will correctly convert "007" to 7
```

### Mistake 4: Allowing Spaces

```c
❌ WRONG:
// Forgetting to check for spaces
// "4 2" would pass digit checks on '4' and '2'

✓ CORRECT:
// ft_isdigit catches space as non-digit
// Our loop correctly rejects "4 2"
```

### Mistake 5: Not Checking After Signs

```c
❌ WRONG:
while (str[i] == '+' || str[i] == '-')
    i++;
// What if string is just "+" or "--" or "+-+-"?
// Must check that digits follow!

✓ CORRECT:
while (str[i] == '+' || str[i] == '-')
    i++;
if (!str[i])
    return (0);  // Signs only, no digits!
```

---

## Testing Strategy

### Test Case 1: Valid Numbers - Basic

```c
assert(is_valid_number("42") == 1);
assert(is_valid_number("-42") == 1);
assert(is_valid_number("+42") == 1);
assert(is_valid_number("0") == 1);
assert(is_valid_number("-0") == 1);
assert(is_valid_number("2147483647") == 1);  // INT_MAX
assert(is_valid_number("-2147483648") == 1); // INT_MIN
```

### Test Case 2: Valid Numbers - Multiple Signs (NEW!)

```c
assert(is_valid_number("--42") == 1);   // Double negative = +42
assert(is_valid_number("---42") == 1);  // Triple negative = -42
assert(is_valid_number("+-42") == 1);   // Mixed = -42
assert(is_valid_number("-+42") == 1);   // Mixed = -42
assert(is_valid_number("+-+-42") == 1); // Multiple mixed = +42
assert(is_valid_number("----42") == 1); // Four negatives = +42
```

### Test Case 3: Valid Numbers - Leading Zeros (NEW!)

```c
assert(is_valid_number("007") == 1);    // = 7
assert(is_valid_number("042") == 1);    // = 42
assert(is_valid_number("-007") == 1);   // = -7
assert(is_valid_number("+00") == 1);    // = 0
assert(is_valid_number("00") == 1);     // = 0
assert(is_valid_number("000123") == 1); // = 123
```

### Test Case 4: Valid Numbers - Combined (NEW!)

```c
assert(is_valid_number("--007") == 1);    // = +7
assert(is_valid_number("+-00123") == 1);  // = -123
assert(is_valid_number("---00042") == 1); // = -42
```

### Test Case 5: Invalid - Empty/NULL

```c
assert(is_valid_number("") == 0);
assert(is_valid_number(NULL) == 0);
```

### Test Case 6: Invalid - Signs Only

```c
assert(is_valid_number("+") == 0);
assert(is_valid_number("-") == 0);
assert(is_valid_number("--") == 0);
assert(is_valid_number("+-+-") == 0);
```

### Test Case 7: Invalid - Non-Digits

```c
assert(is_valid_number("abc") == 0);
assert(is_valid_number("4a2") == 0);
assert(is_valid_number("42a") == 0);
assert(is_valid_number("a42") == 0);
```

### Test Case 8: Invalid - Sign in Wrong Place

```c
assert(is_valid_number("42+") == 0);    // Sign at end
assert(is_valid_number("4+2") == 0);    // Sign in middle
assert(is_valid_number("42-3") == 0);   // Sign in middle
```

### Test Case 9: Invalid - Special Characters

```c
assert(is_valid_number("4.2") == 0);    // Decimal point
assert(is_valid_number("4,2") == 0);    // Comma
assert(is_valid_number("4 2") == 0);    // Space
assert(is_valid_number("4\t2") == 0);   // Tab
assert(is_valid_number("4\n2") == 0);   // Newline
```

---

## Summary: What is_valid_number Does

1. **Checks** string is not NULL or empty
2. **Skips** all leading signs (+/-) - handles multiple signs
3. **Ensures** at least one digit exists after signs
4. **Allows** leading zeros - mathematically valid
5. **Validates** all remaining characters are digits
6. **Returns** 1 for valid format, 0 for invalid

**Key insight:** This function only checks FORMAT, not VALUE. A string like "999999999999" is valid format even though it exceeds INT_MAX. Range checking happens separately in is_int_range().

**Design decision:** We accept leading zeros and multiple signs because:
- Mathematically, `007` IS the integer 7
- Mathematically, `--42` IS the integer 42
- The 42 subject says input must be "integers" - these ARE valid integer representations
- This approach is defensible during evaluation

---

## Location in Project

**File:** `srcs/validate.c`
**Header:** `includes/push_swap.h`
**Phase in TODO:** Phase 2.2 (Parsing & Validation - Number Validation)

**Note:** This function is in `validate.c` (not `parser.c`) to comply with 42 Norm's
5 functions per file limit. Parser.c contains parse_arguments + 2 static helpers.

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
- `ft_atol()` - String to number conversion (must also handle multiple signs!)
- `is_int_range()` - Range validation (called after conversion)
- `has_duplicates()` - Value validation (called after stack built)

---

*Remember: Validate format here, calculate actual value in ft_atol. This separation of concerns keeps each function simple and focused!*