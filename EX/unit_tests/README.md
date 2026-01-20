# Push_Swap Unit Tests

Comprehensive unit test suite for the push_swap project, testing all core functions with edge cases and failure scenarios.

## Test Coverage

### 1. **stack_utils_test.c** - Stack Utility Functions
Tests for basic stack operations:
- `stack_new()` - Node creation with all field initialization
- `stack_size()` - Stack size calculation
- `stack_last()` - Finding last element
- `stack_add_back()` - Adding elements to end
- `stack_add_front()` - Adding elements to front

**Edge cases tested:**
- NULL pointers
- Empty stacks
- Single element stacks
- Large stacks (100+ elements)
- INT_MIN/INT_MAX values

### 2. **stack_find_test.c** - Stack Search Functions
Tests for finding min/max values and checking sort status:
- `find_min()` - Find minimum value
- `find_max()` - Find maximum value
- `find_min_index()` - Find position of minimum
- `find_max_index()` - Find position of maximum
- `is_sorted()` - Check if stack is sorted

**Edge cases tested:**
- NULL stacks
- Single elements
- All same values
- Negative values
- Mixed positive/negative
- INT_MIN/INT_MAX boundaries
- Multiple occurrences

### 3. **validate_test.c** - Input Validation
Tests for argument parsing and validation:
- `is_valid_number()` - Format validation
- `ft_atol()` - String to long conversion
- `is_int_range()` - INT_MIN/INT_MAX range checking
- `has_duplicate()` - Duplicate detection

**Edge cases tested:**
- NULL/empty strings
- Invalid formats (letters, spaces, special chars)
- Sign handling (+/-)
- Overflow/underflow
- Leading zeros
- Boundary values
- Duplicate detection in various positions

### 4. **operations_swap_test.c** - Swap Operations
Tests for swap operations:
- `sa()` - Swap first two of stack A
- `sb()` - Swap first two of stack B
- `ss()` - Swap both stacks simultaneously

**Edge cases tested:**
- NULL pointers
- Empty stacks
- Single element (no-op)
- Two elements (basic swap)
- Multiple elements (only first two swap)
- Print mode vs silent mode
- Double swap returns to original
- INT_MIN/INT_MAX values

### 5. **operations_push_test.c** - Push Operations
Tests for push operations:
- `pa()` - Push from B to A
- `pb()` - Push from A to B

**Edge cases tested:**
- NULL pointers
- Empty source stack
- Empty destination stack
- Single element pushes
- Multiple pushes
- Push all elements
- Combined pa/pb operations
- Interleaved push operations
- INT_MIN/INT_MAX values

### 6. **operations_rotate_test.c** - Rotate Operations
Tests for forward rotation:
- `ra()` - Rotate A up (first becomes last)
- `rb()` - Rotate B up
- `rr()` - Rotate both simultaneously

**Edge cases tested:**
- NULL pointers
- Empty stacks
- Single element (no-op)
- Two elements
- Multiple rotations
- N rotations (where N = size) returns to original
- Combined operations
- INT_MIN/INT_MAX values

### 7. **operations_reverse_test.c** - Reverse Rotate Operations
Tests for backward rotation:
- `rra()` - Reverse rotate A (last becomes first)
- `rrb()` - Reverse rotate B
- `rrr()` - Reverse rotate both simultaneously

**Edge cases tested:**
- NULL pointers
- Empty stacks
- Single element (no-op)
- Two elements
- Multiple reverse rotations
- N rotations returns to original
- ra/rra inverse relationship
- Combined operations
- INT_MIN/INT_MAX values

## Building and Running

### Build All Tests
```bash
make
```

### Run All Tests
```bash
make test
```

### Run Individual Test Suites
```bash
make test_stack_utils   # Stack utility functions
make test_stack_find    # Find min/max/sorted
make test_validate      # Input validation
make test_swap          # Swap operations
make test_push          # Push operations
make test_rotate        # Rotate operations
make test_reverse       # Reverse rotate operations
```

### Memory Leak Testing
```bash
make valgrind
```
Runs all tests through valgrind to detect memory leaks.

### Clean
```bash
make clean   # Remove test executables
make fclean  # Full clean including libft
make re      # Rebuild everything
```

### Help
```bash
make help    # Show all available targets
```

## Test Output Format

Each test prints results in this format:
```
========================================
     STACK_UTILS.C UNIT TESTS
========================================

===== STACK_NEW TESTS =====
  [PASS] Create node with value 42
  [PASS] Create node with value -100
  [PASS] Create node with value 0
  ...

stack_utils.c Summary: 35 passed, 0 failed
========================================
```

## Test Philosophy

### Comprehensive Coverage
- **NULL safety**: Every function tested with NULL inputs
- **Boundary testing**: INT_MIN, INT_MAX, empty, single element
- **Edge cases**: Duplicates, negatives, zeros, large inputs
- **State verification**: Check both operation success AND state correctness

### Failure Points Tested
Each test suite focuses on realistic failure scenarios:
- Null pointer dereferences
- Off-by-one errors
- Memory leaks
- Incorrect state after operations
- Silent failures (operations that should do nothing)
- Circular list creation
- Lost references

### Test Structure
Each test file follows this pattern:
1. **Helper functions** - Reusable test utilities
2. **Test counters** - Track passes/fails
3. **Grouped tests** - One function per test group
4. **Summary** - Final pass/fail count

## Expected Test Results

All tests should pass with 0 failures:
- **stack_utils**: ~35 tests
- **stack_find**: ~45 tests
- **validate**: ~50 tests
- **operations_swap**: ~40 tests
- **operations_push**: ~50 tests
- **operations_rotate**: ~45 tests
- **operations_reverse**: ~50 tests

**Total: ~315 individual test cases**

## Integration with Development

### During Development
Run specific test suites while working on features:
```bash
# Working on swap operations
make test_swap

# Working on validation
make test_validate
```

### Before Commits
Always run full test suite:
```bash
make test
```

### Memory Verification
Before final submission:
```bash
make valgrind
```

## Common Test Failures

### Segmentation Fault
- Usually NULL pointer dereference
- Check validation at function entry

### Wrong Values
- Check operation logic
- Verify pointer updates
- Check edge case handling

### Memory Leaks
- Ensure `free_stack()` is called
- Check for orphaned nodes
- Verify circular list prevention

## Extending Tests

To add new tests:

1. **Create test file**: `new_feature_test.c`
2. **Follow existing pattern**:
   - Include test helpers
   - Create test functions
   - Add to main()
3. **Update Makefile**:
   - Add to `ALL_TESTS`
   - Add compilation rule
   - Add individual test target

## Notes

- Tests use existing project functions (`stack_new`, `free_stack`, etc.)
- Silent mode (`print=0`) used in most tests to avoid output clutter
- Print mode (`print=1`) tested explicitly where relevant
- Helper function `create_test_stack()` builds stacks from arrays
- Helper function `verify_stack_values()` checks expected outcomes

## Troubleshooting

### Compilation Errors
- Ensure libft is built: `make -C ../libft`
- Check include paths in Makefile
- Verify all source files exist

### Test Failures
- Read the test name to understand what failed
- Check expected vs actual values
- Use debugger: `gdb ./test_stack_utils`

### Valgrind Issues
- Ensure all tests pass first
- Check for uninitialized values
- Look for "definitely lost" in output

---

**Note**: These tests are designed to catch common errors before they become bugs. They're not a replacement for manual testing with the actual push_swap program, but they provide a solid foundation of correctness.
