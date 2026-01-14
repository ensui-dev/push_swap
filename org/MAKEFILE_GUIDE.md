# Push_swap Makefile Guide

## Overview

This Makefile is designed according to 42 School requirements with **special attention to preventing unnecessary relinking**. It compiles both the mandatory `push_swap` program and the bonus `checker` program.

---

## 📋 Subject Requirements

According to the subject PDF (Chapter IV - Common Instructions):

### Mandatory Requirements
- ✅ **Compiler**: Must use `cc`
- ✅ **Compilation flags**: Must include `-Wall -Wextra -Werror`
- ✅ **No relinking**: Makefile must not relink unnecessarily
- ✅ **Required rules**: `$(NAME)`, `all`, `clean`, `fclean`, `re`
- ✅ **Bonus rule**: `bonus` for compiling bonus files
- ✅ **Libft integration**: Must compile libft using its Makefile
- ✅ **Bonus files**: Must use `_bonus.{c/h}` suffix

---

## 🎯 How Relinking Prevention Works

### The Problem
Without proper dependency management, running `make` twice in a row might recompile and relink the program even when nothing has changed. This is inefficient and indicates poor Makefile design.

### The Solution
This Makefile prevents relinking through several mechanisms:

#### 1. **Target Dependencies**
```makefile
$(NAME): $(LIBFT) $(OBJS)
    @$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
```

- `$(NAME)` (push_swap) depends on `$(LIBFT)` and `$(OBJS)`
- Make compares timestamps:
  - If `push_swap` is **newer** than all its dependencies → **No action**
  - If any dependency is **newer** than `push_swap` → **Relink**

#### 2. **Object File Dependencies**
```makefile
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
    @$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c $< -o $@
```

- Each `.o` file depends on its corresponding `.c` file
- Pattern rule: `objs/main.o` depends on `srcs/main.c`
- Only modified source files are recompiled

#### 3. **Automatic Header Dependencies**
```makefile
DEPFLAGS = -MMD -MP
-include $(DEPS)
```

- The `-MMD -MP` flags generate `.d` (dependency) files
- These track which headers each source file includes
- If a header changes, only affected sources recompile
- Example: If `push_swap.h` changes, all files that include it recompile

#### 4. **Libft Dependency**
```makefile
$(LIBFT):
    @$(MAKE) -C $(LIBFT_DIR) --no-print-directory
```

- `$(LIBFT)` target only runs if:
  - `libft.a` doesn't exist, OR
  - Any libft source is newer than `libft.a`
- Libft's own Makefile handles its internal dependencies
- If libft is up-to-date, it won't recompile

---

## 🧪 Testing No-Relink Behavior

### Test 1: Double Make
```bash
# First compilation
$ make
# Compiles everything

# Second compilation immediately after
$ make
make: Nothing to be done for 'all'.  # ✅ No relinking!
```

### Test 2: Modify a Single File
```bash
$ make              # Everything up-to-date
$ touch srcs/main.c # Modify one source file
$ make              # Only main.o recompiles, then relinks
```

### Test 3: Modify a Header
```bash
$ make                    # Everything up-to-date
$ touch includes/push_swap.h  # Modify header
$ make                    # All files that include this header recompile
```

### Test 4: Libft Changes
```bash
$ make                     # Everything up-to-date
$ touch libft/ft_atoi.c   # Modify libft source
$ make                     # Libft recompiles, push_swap relinks
```

---

## 📂 Directory Structure

```
EX/
├── Makefile                # Main Makefile (this file manages everything)
├── includes/               # Header files (.h)
│   └── push_swap.h
├── srcs/                   # Mandatory source files (.c)
│   ├── main.c
│   ├── parser.c
│   └── ...
├── srcs_bonus/             # Bonus source files (_bonus.c)
│   ├── checker_bonus.c
│   └── ...
├── objs/                   # Compiled object files (.o) [generated]
│   ├── main.o
│   ├── main.d              # Dependency files [generated]
│   └── ...
├── objs_bonus/             # Bonus object files [generated]
├── libft/                  # Libft library
│   ├── Makefile
│   ├── libft.h
│   └── *.c
├── push_swap               # Compiled executable [generated]
└── checker                 # Bonus executable [generated]
```

---

## 🔧 Available Commands

### `make` or `make all`
Compiles the mandatory `push_swap` program.

**What it does:**
1. Compiles libft (if needed)
2. Compiles all `.c` files in `srcs/` to `.o` files in `objs/`
3. Links everything into `push_swap` executable

**Output:**
```
Compiling libft...
✓ libft compiled!
Compiling srcs/main.c...
Compiling srcs/parser.c...
...
Linking push_swap...
✓ push_swap compiled successfully!
```

### `make bonus`
Compiles the bonus `checker` program.

**What it does:**
1. Compiles libft (if needed)
2. Compiles all `*_bonus.c` files in `srcs_bonus/` to `.o` files in `objs_bonus/`
3. Links everything into `checker` executable

### `make clean`
Removes object files and dependency files.

**What it removes:**
- `objs/` directory (all `.o` and `.d` files)
- `objs_bonus/` directory
- Object files in libft

**What it keeps:**
- Executables (`push_swap`, `checker`)
- Source files
- `libft.a`

### `make fclean`
Removes everything (objects + executables).

**What it removes:**
- Everything from `clean`
- `push_swap` executable
- `checker` executable
- `libft.a`

### `make re`
Rebuilds everything from scratch.

**Equivalent to:**
```bash
make fclean
make all
```

### `make help`
Displays help message with all available commands.

---

## ⚙️ Compilation Details

### Compilation Flags

```makefile
CFLAGS = -Wall -Wextra -Werror
```

- **`-Wall`**: Enable all common warnings
- **`-Wextra`**: Enable extra warnings
- **`-Werror`**: Treat warnings as errors (compilation fails if warnings exist)

### Include Paths

```makefile
INCLUDES = -I$(INCLUDES_DIR) -I$(LIBFT_DIR)
```

- Tells compiler where to find header files
- `-I$(INCLUDES_DIR)`: Your project headers (`includes/`)
- `-I$(LIBFT_DIR)`: Libft headers (`libft/`)

### Linking Flags

```makefile
LDFLAGS = -L$(LIBFT_DIR) -lft
```

- **`-L$(LIBFT_DIR)`**: Directory to search for libraries
- **`-lft`**: Link with `libft.a` (lib**ft**.a)

### Dependency Flags

```makefile
DEPFLAGS = -MMD -MP
```

- **`-MMD`**: Generate dependency files (`.d`)
- **`-MP`**: Add phony targets for headers (prevents errors if headers are removed)

---

## 🎨 Color Output

The Makefile includes colored output for better readability:

- 🔵 **CYAN**: Linking messages
- 🟢 **GREEN**: Success messages
- 🟡 **YELLOW**: Compilation progress
- 🔴 **RED**: Cleaning messages
- 🟣 **MAGENTA**: Library compilation

---

## 🔍 Advanced Features

### 1. **Automatic Directory Creation**
```makefile
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
```

The `| $(OBJS_DIR)` is an **order-only prerequisite**:
- Creates `objs/` directory if it doesn't exist
- Doesn't trigger recompilation if directory timestamp changes

### 2. **Silent Compilation**
All commands are prefixed with `@` to hide the actual commands:
```makefile
@$(CC) $(CFLAGS) ...
```

Without `@`, you'd see:
```
cc -Wall -Wextra -Werror -Iincludes -Ilibft -MMD -MP -c srcs/main.c -o objs/main.o
```

With `@`, you see:
```
Compiling srcs/main.c...
```

### 3. **Quiet Libft Compilation**
```makefile
@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
```

- **`-C $(LIBFT_DIR)`**: Change to libft directory before running make
- **`--no-print-directory`**: Don't print "Entering directory" messages

### 4. **Phony Targets**
```makefile
.PHONY: all clean fclean re bonus help
```

Declares targets that aren't actual files. Without this:
- If you accidentally create a file named `clean`, `make clean` won't work
- `.PHONY` ensures these targets always run when called

---

## 🐛 Common Issues and Solutions

### Issue 1: "Nothing to be done" but binary doesn't exist
**Cause**: Target name mismatch

**Solution**: Verify `NAME = push_swap` matches actual output

### Issue 2: Relinking occurs on every `make`
**Cause**: Dependencies or timestamps are incorrect

**Solution**:
1. Check that all prerequisites are listed correctly
2. Verify no target modifies its own timestamp
3. Ensure no commands use `rm` on targets then recreate them

### Issue 3: Changes to header don't trigger recompilation
**Cause**: Dependency files not included

**Solution**: Ensure `-include $(DEPS)` is present and `-MMD -MP` flags are used

### Issue 4: Libft always recompiles
**Cause**: Timestamp issue or missing libft target

**Solution**:
1. Check `$(LIBFT)` target exists and has correct path
2. Verify libft's Makefile doesn't have issues
3. Make sure `$(LIBFT)` is a prerequisite of `$(NAME)`

---

## 📊 Compilation Flow Diagram

```
┌─────────────────────────┐
│   make / make all       │
└───────────┬─────────────┘
            │
            ▼
    ┌───────────────────┐
    │  Need $(LIBFT)?   │
    └─────┬─────────────┘
          │ yes
          ▼
    ┌─────────────────┐
    │ make -C libft   │ ──► libft.a created/updated
    └─────┬───────────┘
          │
          ▼
    ┌──────────────────┐
    │ Need $(OBJS)?    │
    └────┬─────────────┘
         │ yes
         ▼
    ┌──────────────────────────┐
    │ Compile each .c to .o    │
    │ (only if .c newer)       │
    └────┬─────────────────────┘
         │
         ▼
    ┌──────────────────────────┐
    │ Need to link $(NAME)?    │
    └────┬─────────────────────┘
         │ yes (if any .o or libft.a is newer)
         ▼
    ┌──────────────────────────┐
    │ Link push_swap           │
    └────┬─────────────────────┘
         │
         ▼
    ┌──────────────────────────┐
    │ push_swap ready!         │
    └──────────────────────────┘
```

---

## 📚 Makefile Variables Reference

| Variable | Value | Purpose |
|----------|-------|---------|
| `NAME` | `push_swap` | Name of mandatory executable |
| `BONUS_NAME` | `checker` | Name of bonus executable |
| `CC` | `cc` | Compiler (required by subject) |
| `CFLAGS` | `-Wall -Wextra -Werror` | Compilation flags (required) |
| `INCLUDES` | `-Iincludes -Ilibft` | Header search paths |
| `LDFLAGS` | `-Llibft -lft` | Linker flags |
| `DEPFLAGS` | `-MMD -MP` | Dependency generation flags |
| `SRCS_DIR` | `srcs` | Mandatory source directory |
| `BONUS_DIR` | `srcs_bonus` | Bonus source directory |
| `OBJS_DIR` | `objs` | Object files directory |
| `INCLUDES_DIR` | `includes` | Header files directory |
| `LIBFT_DIR` | `libft` | Libft library directory |
| `LIBFT` | `libft/libft.a` | Path to compiled libft |

---

## ✅ Checklist for 42 Evaluation

Before submitting, verify:

- [ ] `make` compiles without errors
- [ ] `make` compiles without warnings
- [ ] Running `make` twice shows "Nothing to be done"
- [ ] `make clean` removes only `.o` files
- [ ] `make fclean` removes `.o` files and executables
- [ ] `make re` rebuilds everything
- [ ] `make bonus` compiles checker (if implemented)
- [ ] Libft compiles using its own Makefile
- [ ] No hardcoded paths (all use variables)
- [ ] No global relinking (only when sources change)
- [ ] All flags are correct: `-Wall -Wextra -Werror`
- [ ] Compiler is `cc` (not `gcc`)

---

## 🎓 Learning Resources

### Make Documentation
- [GNU Make Manual](https://www.gnu.org/software/make/manual/)
- [Make Tutorial](https://makefiletutorial.com/)

### Understanding Timestamps
```bash
# See file timestamps
ls -l push_swap srcs/main.c

# Example output:
# -rw-r--r-- 1 user user 1234 Jan 14 10:00 srcs/main.c
# -rwxr-xr-x 1 user user 5678 Jan 14 09:00 push_swap
#
# push_swap is OLDER than main.c → Recompile needed
```

### Dependency Files
```bash
# View a .d file to see header dependencies
cat objs/main.d

# Example output:
# objs/main.o: srcs/main.c includes/push_swap.h libft/libft.h
```

---

## 🚀 Next Steps

1. **Create source files** as you implement the project
2. **Test compilation** frequently with `make`
3. **Verify no-relink** by running `make` twice
4. **Check for leaks** with valgrind after compilation

Good luck with your push_swap project! 🎉
