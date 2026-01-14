# Push_swap - Getting Started Guide

## 📚 Documentation Overview

Welcome to push_swap! I've created comprehensive documentation to guide you through this project. Here's what each file contains:

### 1. **TODO.md** (YOUR MAIN GUIDE)
- **339 bite-sized tasks** broken down into 13 phases
- Step-by-step implementation guide
- Every function you need to write
- Testing procedures and benchmarks
- Complete checklist format

### 2. **PROJECT_ANALYSIS.md**
- Detailed project requirements
- Stack operations explained
- Benchmark requirements breakdown
- Algorithm complexity analysis
- Common pitfalls to avoid

### 3. **42_NORM_CHECKLIST.md**
- Quick reference for 42 Norm compliance
- Common violations and how to fix them
- Code examples (correct vs wrong)
- Verification commands

### 4. **This File (GETTING_STARTED.md)**
- Quick start guide
- Recommended workflow
- Tips for success

---

## 🎯 Your Implementation Choices

Based on your selections, here's what you'll be building:

### Algorithm: **Hybrid Approach**
- **Small numbers (≤5)**: Hardcoded optimal solutions
- **Medium numbers (6-100)**: Turk/Chunk algorithm
- **Large numbers (100-500)**: Optimized chunk algorithm with cost calculation

**Why this approach?**
- Best overall performance
- Achieves <700 ops for 100 numbers, <5500 for 500
- Educational - you'll learn multiple strategies
- Most reliable for passing all benchmarks

### Data Structure: **Linked List**
- Dynamic memory allocation
- Efficient O(1) push/pop operations
- Standard ADT for stack implementation
- Each node contains: value, index, position, costs, next pointer

### Optimization: **Index Normalization**
- Maps input values to indices 0...N-1
- Simplifies algorithm logic
- Enables efficient comparisons
- Required for optimal performance

---

## 🚀 Quick Start - First Steps

### Step 1: Setup (15 minutes)
```bash
cd /home/mju-ferr/42COMMON_CORE/42cursus/push_swap

# Create directory structure
mkdir -p includes srcs srcs_bonus libft

# Copy your libft
cp -r /path/to/your/libft/* libft/

# Start with Phase 0 in TODO.md
```

### Step 2: Create Basic Files (30 minutes)
1. **Makefile** - Follow TODO.md Phase 0.2
2. **includes/push_swap.h** - Follow TODO.md Phase 0.3
3. **srcs/main.c** - Create empty main function

Test compilation:
```bash
make
# Should compile without errors (even if main does nothing yet)
```

### Step 3: Implement Core Structures (1-2 hours)
Follow TODO.md Phase 1:
1. Define `t_stack` structure in header
2. Implement `stack_new()`, `stack_size()`, `stack_last()`
3. Test each function as you write it

### Step 4: Input Parsing (2-3 hours)
Follow TODO.md Phase 2:
1. Implement argument parsing
2. Implement validation (number format, range, duplicates)
3. Test with various inputs

**Test early and often!**

---

## 📋 Recommended Workflow

### Daily Development Cycle

#### 1. **Start of Session**
- Open TODO.md
- Review completed tasks (check them off)
- Choose 3-5 related tasks for today
- Read relevant section in PROJECT_ANALYSIS.md if needed

#### 2. **Development**
- Implement one function at a time
- Test the function immediately after writing
- Run norminette on the file
- Check memory with valgrind if using malloc
- Check off task in TODO.md when done

#### 3. **End of Session**
- Commit your progress to git
- Run `make fclean && make` to verify clean build
- Note any issues or questions for next session

### Weekly Milestones

**Week 1: Foundation**
- Complete Phases 0-3 (Setup, Data Structures, Parsing, Error Handling)
- Goal: Have working stack, can parse input, handle errors
- Test: `./push_swap 3 2 1` should parse without crashing

**Week 2: Operations**
- Complete Phase 4 (All stack operations)
- Goal: All 11 operations working correctly
- Test: Manually verify each operation (sa, pa, ra, rra, etc.)

**Week 3: Small Sorts + Index**
- Complete Phases 5-6 (Index normalization, Small sorts)
- Goal: Perfect sorting for 2-5 numbers
- Test: `./push_swap 5 4 3 2 1` should sort optimally

**Week 4: Large Sort Algorithm**
- Complete Phase 7 (Turk/Chunk algorithm)
- Goal: Sort 100 and 500 numbers
- Test: Benchmark with random numbers

**Week 5: Optimization + Testing**
- Complete Phases 8-10 (Main program, Testing, Norm)
- Goal: Pass all benchmarks, no norm errors
- Test: Full benchmark suite

**Week 6: Bonus (Optional)**
- Complete Phase 11 (Checker program)
- Goal: Working checker program
- Test: `./push_swap <nums> | ./checker <nums>` outputs OK

---

## 🎓 Learning Tips

### Understanding Before Coding
- **Read the operation descriptions carefully** - Know exactly what each operation does
- **Draw on paper** - Visualize the stack operations before coding
- **Understand the algorithm** - Don't just copy code, understand why it works

### Debugging Strategies
- **Print stack states** - Create a function to print both stacks for debugging
- **Test small inputs** - Debug with 3-5 numbers before testing 100
- **Use visualizers** - Search for "push_swap visualizer" online
- **Count operations manually** - Verify your algorithm with simple cases

### When Stuck
1. **Read TODO.md step again** - Maybe you missed a detail
2. **Check PROJECT_ANALYSIS.md** - Understand the concept better
3. **Test simpler case** - If 100 numbers fails, test with 10
4. **Check for norm errors** - Sometimes code works but isn't norm-compliant
5. **Ask peers** - Discuss concepts (not copy code)
6. **Take a break** - Fresh eyes often spot issues faster

---

## ⚠️ Common Pitfalls (Avoid These!)

### 1. Not Testing Incrementally
❌ Writing 10 functions before testing any
✅ Test each function immediately after writing

### 2. Ignoring Memory Management
❌ Allocating without freeing
✅ Every malloc has a corresponding free

### 3. Not Checking Edge Cases
❌ Only testing with 5 random numbers
✅ Test: empty, 1 number, sorted, reverse sorted, duplicates, overflows

### 4. Norm Violations Accumulating
❌ Waiting until end to check norm
✅ Run norminette after every file

### 5. Over-Complicating Early
❌ Trying to optimize before basic version works
✅ Get it working first, then optimize

### 6. Not Understanding the Algorithm
❌ Copying code without understanding
✅ Implement step by step, understand each piece

### 7. Forgetting About Benchmarks
❌ Not testing with 100/500 numbers until evaluation
✅ Test benchmarks regularly during development

---

## 🧪 Testing Strategy

### Phase-by-Phase Testing

**After Phase 1 (Data Structures):**
```c
// Test in main.c temporarily
t_stack *test = stack_new(42);
printf("Value: %d\n", test->value);  // Should print 42
free(test);
```

**After Phase 2 (Parsing):**
```bash
./push_swap 3 2 1        # Should parse
./push_swap "3 2 1"      # Should parse (single arg)
./push_swap 1 2 2        # Should error (duplicate)
./push_swap 1 a 3        # Should error (non-integer)
```

**After Phase 4 (Operations):**
```bash
# Test manually: does sa swap first two?
# Print stack before and after each operation
```

**After Phase 6 (Small Sorts):**
```bash
./push_swap 2 1          # Should output: sa (1 op)
./push_swap 3 2 1        # Should output ≤2 ops
./push_swap 5 4 3 2 1    # Should output ≤12 ops
```

**After Phase 7 (Large Sorts):**
```bash
# Test 100 numbers
ARG=$(seq 1 100 | shuf | tr '\n' ' ')
./push_swap $ARG | wc -l  # Should be <700

# Test 500 numbers
ARG=$(seq 1 500 | shuf | tr '\n' ' ')
./push_swap $ARG | wc -l  # Should be <5500
```

### Automated Testing Script
Create `test.sh`:
```bash
#!/bin/bash

echo "Testing 3 numbers (should be ≤3 ops):"
for i in {1..5}; do
    ARG=$(seq 1 3 | shuf | tr '\n' ' ')
    OPS=$(./push_swap $ARG | wc -l)
    echo "  Test $i: $OPS operations"
done

echo "\nTesting 5 numbers (should be ≤12 ops):"
for i in {1..5}; do
    ARG=$(seq 1 5 | shuf | tr '\n' ' ')
    OPS=$(./push_swap $ARG | wc -l)
    echo "  Test $i: $OPS operations"
done

echo "\nTesting 100 numbers (should be <700 ops):"
for i in {1..5}; do
    ARG=$(seq 1 100 | shuf | tr '\n' ' ')
    OPS=$(./push_swap $ARG | wc -l)
    echo "  Test $i: $OPS operations"
done
```

Make executable: `chmod +x test.sh`

---

## 📊 Performance Targets

### Minimum (80% Grade)
- 3 numbers: ≤3 operations
- 5 numbers: ≤12 operations
- 100 numbers: <1100 operations
- 500 numbers: <8500 operations

### Maximum (100% + Bonus Eligible)
- 3 numbers: ≤3 operations
- 5 numbers: ≤12 operations
- 100 numbers: <700 operations
- 500 numbers: ≤5500 operations

**Your hybrid algorithm should achieve the maximum targets!**

---

## 📖 Resources

### Recommended Reading Order
1. Read this file (GETTING_STARTED.md) - you're doing it!
2. Skim PROJECT_ANALYSIS.md - understand the big picture
3. Read TODO.md Phase 0 - start setup
4. Keep TODO.md open while coding - your main guide
5. Reference 42_NORM_CHECKLIST.md - when checking norm
6. Re-read relevant sections of PROJECT_ANALYSIS.md as needed

### External Resources
- **Sorting Algorithms**: [Wikipedia - Sorting Algorithm](https://en.wikipedia.org/wiki/Sorting_algorithm)
- **Push Swap Visualizer**: Search GitHub for "push_swap visualizer"
- **42 Docs**: Intranet project page
- **Big O Notation**: Understanding time complexity

### Getting Help
- **Peers**: Discuss concepts, not code
- **42 Slack/Discord**: Ask general questions
- **Evaluation**: Learn from evaluating others
- **These docs**: Re-read when stuck

---

## ✅ Pre-Submission Checklist

Before submitting to git and requesting evaluation:

### Code Quality
- [ ] All functions follow 42 Norm (0 errors)
- [ ] No memory leaks (valgrind clean)
- [ ] No crashes on any input
- [ ] Handles all error cases properly
- [ ] Code is clean and readable
- [ ] Comments explain complex logic

### Functionality
- [ ] Sorts 3 numbers correctly (≤3 ops)
- [ ] Sorts 5 numbers correctly (≤12 ops)
- [ ] Sorts 100 numbers (<700 ops average)
- [ ] Sorts 500 numbers (<5500 ops average)
- [ ] Works with checker_OS (all tests output OK)
- [ ] No output when already sorted
- [ ] No output when no arguments

### Makefile
- [ ] `make` compiles without errors
- [ ] `make clean` removes only .o files
- [ ] `make fclean` removes .o and binaries
- [ ] `make re` rebuilds correctly
- [ ] No relinking on second `make`
- [ ] `make bonus` compiles checker (if doing bonus)

### Documentation
- [ ] README.md is complete and well-written
- [ ] First line of README is correct format
- [ ] AI usage is documented (if applicable)
- [ ] Instructions are clear

### Repository
- [ ] All required files committed
- [ ] No .o files in repo
- [ ] No binaries in repo (unless allowed)
- [ ] .gitignore is set up
- [ ] Can clone and compile successfully

---

## 🎯 Final Advice

### Keys to Success
1. **Follow TODO.md religiously** - It's your roadmap
2. **Test continuously** - Don't accumulate bugs
3. **Understand, don't memorize** - You'll be evaluated on understanding
4. **Start early** - This project takes time
5. **Ask for help** - But understand the answers
6. **Stay organized** - Check off tasks as you complete them
7. **Have fun** - This is a great learning opportunity!

### Remember
- **Quality over speed** - Better to do it right than fast
- **Learning is the goal** - Not just passing
- **You can do this** - Many have succeeded before you
- **Patience** - Complex projects take time

---

## 🚦 Start Now!

1. **Open TODO.md**
2. **Start with Phase 0, Task 0.1**
3. **Check off each task as you complete it**
4. **Refer to this guide when you need orientation**

**Good luck! You've got this! 🚀**

---

*This project has been documented to help you succeed. Use these resources, follow the plan, test thoroughly, and you'll build a great push_swap program!*
