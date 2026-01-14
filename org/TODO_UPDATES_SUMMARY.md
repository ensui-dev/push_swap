# TODO.md Updates Summary - 42 Norm Compliance

## Changes Made - 2026-01-14

### Issue 1: Clarified "Ensure proper linking"

**Location:** Phase 1.2, `stack_add_back` function

**Old (ambiguous):**
```
- [ ] Ensure proper linking
```

**New (explained):**
```
- [x] Else find last node and link: `last->next = new`
- [x] **Proper linking explained**: Must set `last->next = new` to connect nodes
- [x] Without linking: node is orphaned → memory leak + traversal breaks
```

**Why this matters:**
- "Linking" means connecting nodes via pointers (`last->next = new`)
- Without linking, the new node is allocated but disconnected (orphaned)
- Orphaned nodes cause memory leaks AND break traversal functions
- All stack operations depend on proper node connectivity

---

### Issue 2: Clarified "Useful for push operations"

**Location:** Phase 1.2, `stack_add_front` function

**Old (confusing - appeared as a task):**
```
- [ ] Useful for push operations
```

**New (explained as context):**
```
- [x] **Push operations**: This O(1) pattern is core logic of pa/pb
```

**Why this matters:**
- This is NOT a task to complete - it's educational context
- `stack_add_front` is O(1), `stack_add_back` is O(n)
- The pa/pb operations use the same linking pattern as `stack_add_front`
- Understanding this helps when you implement push operations later

---

### Issue 3: Fixed 42 Norm Violation (Max 5 functions per file)

**Problem:** Original TODO asked for 10 functions in `srcs/stack_utils.c`
- Phase 1.2: 5 functions
- Phase 1.3: 5 more functions
- **Total: 10 functions ❌ Violates 42 Norm (max 5)**

**Solution:** Split into two files

#### File 1: `srcs/stack_utils.c` (5 functions)
```
1. stack_new          - Create new node
2. stack_size         - Count nodes
3. stack_last         - Find last node
4. stack_add_back     - Add to end
5. stack_add_front    - Add to beginning
```

#### File 2: `srcs/stack_find.c` (5 functions) ⭐ NEW FILE
```
1. find_min           - Find minimum value
2. find_max           - Find maximum value
3. find_min_index     - Find minimum index
4. find_max_index     - Find maximum index
5. is_sorted          - Check if stack is sorted
```

**Changes in TODO.md:**

**Phase 1.2 header - Added clarification:**
```diff
### 1.2 Stack Utility Functions - Basic Operations
+ **File:** `srcs/stack_utils.c` (5 functions - 42 Norm max per file)
```

**Phase 1.3 header - Changed file and added note:**
```diff
- ### 1.3 Stack Utility Functions - Advanced
- - [ ] Add to `srcs/stack_utils.c`

+ ### 1.3 Stack Utility Functions - Search Operations
+ **File:** `srcs/stack_find.c` (5 functions - new file for 42 Norm compliance)
+ - [ ] Create `srcs/stack_find.c`
```

---

### Issue 4: Updated README.md Project Structure

**Location:** README.md line ~211

**Old:**
```
├── stack_utils.c          # Stack utility functions
```

**New:**
```
├── stack_utils.c          # Basic stack operations (new, size, last, add)
├── stack_find.c           # Stack search (min, max, is_sorted)
```

**Why this matters:**
- README must accurately reflect actual file structure
- Helps during evaluation - evaluator can find functions easily
- Documents the logical separation of concerns

---

## Complete Updated File Structure

```
push_swap/
├── srcs/
│   ├── main.c                  # 2-3 functions
│   ├── parser.c                # 5 functions
│   ├── error.c                 # 2-3 functions
│   ├── free.c                  # 2 functions
│   ├── stack_utils.c           # 5 functions ✅
│   ├── stack_find.c            # 5 functions ✅ NEW
│   ├── stack_init.c            # 1-2 functions
│   ├── position.c              # 1-2 functions
│   ├── index.c                 # 3-4 functions
│   ├── operations_swap.c       # 3 functions
│   ├── operations_push.c       # 2 functions
│   ├── operations_rotate.c     # 3 functions
│   ├── operations_reverse.c    # 3 functions
│   ├── sort_small.c            # 4-5 functions
│   ├── sort_large.c            # 3-5 functions
│   └── cost.c                  # 3-5 functions
```

**All files now comply with 42 Norm (≤5 functions each)** ✅

---

## Documentation Updated

### 1. ✅ [CLARIFICATIONS.md](CLARIFICATIONS.md) - NEW
Comprehensive explanation document covering:
- What "proper linking" means (with diagrams)
- Why it's critical for list integrity
- What "useful for push operations" means
- Why stack_add_front is O(1) vs stack_add_back O(n)
- Complete file structure with function counts
- 42 Norm compliance guidelines

### 2. ✅ [TODO.md](TODO.md) - UPDATED
- Phase 1.2: Added file headers and clarifications
- Phase 1.3: Changed from `stack_utils.c` to `stack_find.c`
- All ambiguous tasks now explained
- Checkboxes updated to reflect explanatory nature

### 3. ✅ [README.md](../EX/README.md) - UPDATED
- Project structure section updated
- Shows split between `stack_utils.c` and `stack_find.c`
- Accurate file descriptions

---

## Quick Reference: Where Are Functions?

### stack_utils.c (Basic Operations)
- `stack_new()` - Create node
- `stack_size()` - Count nodes
- `stack_last()` - Find last
- `stack_add_back()` - Add to end (O(n))
- `stack_add_front()` - Add to front (O(1))

### stack_find.c (Search Operations)
- `find_min()` - Minimum value
- `find_max()` - Maximum value
- `find_min_index()` - Minimum index
- `find_max_index()` - Maximum index
- `is_sorted()` - Check if sorted

---

## Action Items for You

### Immediate Actions:
1. ✅ Read [CLARIFICATIONS.md](CLARIFICATIONS.md) for full explanation
2. ✅ Continue with Phase 1.2 (already complete)
3. ⏳ When ready for Phase 1.3, create `srcs/stack_find.c` (not stack_utils.c)
4. ⏳ Ensure each .c file has ≤5 non-static functions

### During Implementation:
- **stack_utils.c**: Stop at 5 functions (don't add find_min, etc.)
- **stack_find.c**: Put all search/query functions here
- **Other files**: Keep checking function count with `grep -c "^[a-z].*(" filename.c`

### Before Submission:
- Run norminette on all files
- Verify no file has >5 non-static functions
- Check that Makefile compiles both stack_utils.c and stack_find.c

---

## Why These Changes Matter

### 1. Clarity
- No more ambiguous task items
- Clear understanding of what "linking" means
- Understand the purpose of each function

### 2. Compliance
- ✅ Now 42 Norm compliant (max 5 functions per file)
- ✅ Proper file organization
- ✅ Documentation matches implementation

### 3. Maintainability
- Logical file separation (basic ops vs search ops)
- Easier to find functions during development
- Cleaner code organization

### 4. Evaluation Success
- Evaluator can easily locate functions
- No norm violations to explain
- Professional project structure

---

## Summary

**Problems Fixed:**
1. ❌ "Ensure proper linking" was unclear → ✅ Now explained with examples
2. ❌ "Useful for push operations" appeared as task → ✅ Now explanatory note
3. ❌ 10 functions in one file (norm violation) → ✅ Split into 2 files (5 each)
4. ❌ README didn't match structure → ✅ Updated to reflect new file

**Files Updated:**
- ✅ TODO.md - Clarifications and file structure
- ✅ README.md - Project structure section
- ✅ CLARIFICATIONS.md - NEW comprehensive guide

**Result:**
- ✅ 100% 42 Norm compliant
- ✅ Clear, unambiguous instructions
- ✅ Professional documentation
- ✅ Ready to implement Phase 1.3

---

*Your project structure is now optimized for 42 Norm compliance and clarity!*
