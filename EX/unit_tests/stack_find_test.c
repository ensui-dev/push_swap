/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_find_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mju-ferr <mju-ferr@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:00:00 by mju-ferr          #+#    #+#             */
/*   Updated: 2026/01/20 19:00:00 by mju-ferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h>

/* ========================================================================== */
/*                            TEST HELPER FUNCTIONS                           */
/* ========================================================================== */

static int	g_tests_passed = 0;
static int	g_tests_failed = 0;

void	print_test_result(const char *test_name, int passed)
{
	if (passed)
	{
		ft_printf("  [PASS] %s\n", test_name);
		g_tests_passed++;
	}
	else
	{
		ft_printf("  [FAIL] %s\n", test_name);
		g_tests_failed++;
	}
}

void	print_test_summary(const char *suite_name)
{
	ft_printf("\n%s Summary: %d passed, %d failed\n",
		suite_name, g_tests_passed, g_tests_failed);
	ft_printf("========================================\n");
}

t_stack	*create_test_stack(int *values, int count)
{
	t_stack	*stack;
	int		i;

	stack = NULL;
	i = 0;
	while (i < count)
	{
		stack_add_back(&stack, stack_new(values[i]));
		i++;
	}
	return (stack);
}

/* ========================================================================== */
/*                            FIND_MIN TESTS                                  */
/* ========================================================================== */

void	test_find_min(void)
{
	t_stack	*stack;
	int		values_5[] = {5, 2, 8, 1, 9};
	int		negative[] = {-5, -2, -8, -1, -9};
	int		mixed[] = {-5, 0, 5, -10, 10};

	ft_printf("\n===== FIND_MIN TESTS =====\n");

	/* Test 1: NULL stack */
	print_test_result("NULL stack: returns INT_MAX",
		find_min(NULL) == INT_MAX);

	/* Test 2: Single element */
	stack = stack_new(42);
	print_test_result("Single element [42]: min is 42",
		find_min(stack) == 42);
	free_stack(&stack);

	/* Test 3: Multiple elements - min in middle */
	stack = create_test_stack(values_5, 5);
	print_test_result("[5,2,8,1,9]: min is 1", find_min(stack) == 1);
	free_stack(&stack);

	/* Test 4: Multiple elements - min at start */
	int min_first[] = {1, 2, 3, 4, 5};
	stack = create_test_stack(min_first, 5);
	print_test_result("[1,2,3,4,5]: min is 1", find_min(stack) == 1);
	free_stack(&stack);

	/* Test 5: Multiple elements - min at end */
	int min_last[] = {5, 4, 3, 2, 1};
	stack = create_test_stack(min_last, 5);
	print_test_result("[5,4,3,2,1]: min is 1", find_min(stack) == 1);
	free_stack(&stack);

	/* Test 6: All same values */
	int all_same[] = {42, 42, 42};
	stack = create_test_stack(all_same, 3);
	print_test_result("[42,42,42]: min is 42", find_min(stack) == 42);
	free_stack(&stack);

	/* Test 7: Negative values */
	stack = create_test_stack(negative, 5);
	print_test_result("[-5,-2,-8,-1,-9]: min is -9", find_min(stack) == -9);
	free_stack(&stack);

	/* Test 8: Mixed positive and negative */
	stack = create_test_stack(mixed, 5);
	print_test_result("[-5,0,5,-10,10]: min is -10", find_min(stack) == -10);
	free_stack(&stack);

	/* Test 9: INT_MIN in stack */
	int with_int_min[] = {0, INT_MIN, 100};
	stack = create_test_stack(with_int_min, 3);
	print_test_result("[0,INT_MIN,100]: min is INT_MIN",
		find_min(stack) == INT_MIN);
	free_stack(&stack);

	/* Test 10: Two elements */
	int two[] = {10, 5};
	stack = create_test_stack(two, 2);
	print_test_result("[10,5]: min is 5", find_min(stack) == 5);
	free_stack(&stack);
}

/* ========================================================================== */
/*                            FIND_MAX TESTS                                  */
/* ========================================================================== */

void	test_find_max(void)
{
	t_stack	*stack;
	int		values_5[] = {5, 2, 8, 1, 9};
	int		negative[] = {-5, -2, -8, -1, -9};
	int		mixed[] = {-5, 0, 5, -10, 10};

	ft_printf("\n===== FIND_MAX TESTS =====\n");

	/* Test 1: NULL stack */
	print_test_result("NULL stack: returns INT_MIN",
		find_max(NULL) == INT_MIN);

	/* Test 2: Single element */
	stack = stack_new(42);
	print_test_result("Single element [42]: max is 42",
		find_max(stack) == 42);
	free_stack(&stack);

	/* Test 3: Multiple elements - max in middle */
	stack = create_test_stack(values_5, 5);
	print_test_result("[5,2,8,1,9]: max is 9", find_max(stack) == 9);
	free_stack(&stack);

	/* Test 4: Multiple elements - max at start */
	int max_first[] = {9, 5, 2, 8, 1};
	stack = create_test_stack(max_first, 5);
	print_test_result("[9,5,2,8,1]: max is 9", find_max(stack) == 9);
	free_stack(&stack);

	/* Test 5: Multiple elements - max at end */
	int max_last[] = {1, 2, 3, 4, 5};
	stack = create_test_stack(max_last, 5);
	print_test_result("[1,2,3,4,5]: max is 5", find_max(stack) == 5);
	free_stack(&stack);

	/* Test 6: All same values */
	int all_same[] = {42, 42, 42};
	stack = create_test_stack(all_same, 3);
	print_test_result("[42,42,42]: max is 42", find_max(stack) == 42);
	free_stack(&stack);

	/* Test 7: Negative values */
	stack = create_test_stack(negative, 5);
	print_test_result("[-5,-2,-8,-1,-9]: max is -1", find_max(stack) == -1);
	free_stack(&stack);

	/* Test 8: Mixed positive and negative */
	stack = create_test_stack(mixed, 5);
	print_test_result("[-5,0,5,-10,10]: max is 10", find_max(stack) == 10);
	free_stack(&stack);

	/* Test 9: INT_MAX in stack */
	int with_int_max[] = {0, INT_MAX, -100};
	stack = create_test_stack(with_int_max, 3);
	print_test_result("[0,INT_MAX,-100]: max is INT_MAX",
		find_max(stack) == INT_MAX);
	free_stack(&stack);

	/* Test 10: Two elements */
	int two[] = {5, 10};
	stack = create_test_stack(two, 2);
	print_test_result("[5,10]: max is 10", find_max(stack) == 10);
	free_stack(&stack);
}

/* ========================================================================== */
/*                         FIND_MIN_INDEX TESTS                               */
/* ========================================================================== */

void	test_find_min_index(void)
{
	t_stack	*stack;
	int		values_5[] = {5, 2, 8, 1, 9};

	ft_printf("\n===== FIND_MIN_INDEX TESTS =====\n");

	/* Test 1: NULL stack */
	print_test_result("NULL stack: returns -1",
		find_min_index(NULL) == -1);

	/* Test 2: Single element */
	stack = stack_new(42);
	print_test_result("Single element: index is 0",
		find_min_index(stack) == 0);
	free_stack(&stack);

	/* Test 3: Min at index 0 */
	int min_first[] = {1, 2, 3, 4, 5};
	stack = create_test_stack(min_first, 5);
	print_test_result("[1,2,3,4,5]: min index is 0",
		find_min_index(stack) == 0);
	free_stack(&stack);

	/* Test 4: Min at last index */
	int min_last[] = {5, 4, 3, 2, 1};
	stack = create_test_stack(min_last, 5);
	print_test_result("[5,4,3,2,1]: min index is 4",
		find_min_index(stack) == 4);
	free_stack(&stack);

	/* Test 5: Min in middle */
	stack = create_test_stack(values_5, 5);
	print_test_result("[5,2,8,1,9]: min index is 3",
		find_min_index(stack) == 3);
	free_stack(&stack);

	/* Test 6: Multiple mins (returns first occurrence) */
	int multiple_mins[] = {3, 1, 5, 1, 2};
	stack = create_test_stack(multiple_mins, 5);
	print_test_result("[3,1,5,1,2]: first min index is 1",
		find_min_index(stack) == 1);
	free_stack(&stack);

	/* Test 7: All same values */
	int all_same[] = {42, 42, 42};
	stack = create_test_stack(all_same, 3);
	print_test_result("[42,42,42]: min index is 0",
		find_min_index(stack) == 0);
	free_stack(&stack);

	/* Test 8: Two elements */
	int two[] = {10, 5};
	stack = create_test_stack(two, 2);
	print_test_result("[10,5]: min index is 1",
		find_min_index(stack) == 1);
	free_stack(&stack);

	/* Test 9: Negative values */
	int negative[] = {-5, -2, -10, -1};
	stack = create_test_stack(negative, 4);
	print_test_result("[-5,-2,-10,-1]: min index is 2",
		find_min_index(stack) == 2);
	free_stack(&stack);
}

/* ========================================================================== */
/*                         FIND_MAX_INDEX TESTS                               */
/* ========================================================================== */

void	test_find_max_index(void)
{
	t_stack	*stack;
	int		values_5[] = {5, 2, 8, 1, 9};

	ft_printf("\n===== FIND_MAX_INDEX TESTS =====\n");

	/* Test 1: NULL stack */
	print_test_result("NULL stack: returns -1",
		find_max_index(NULL) == -1);

	/* Test 2: Single element */
	stack = stack_new(42);
	print_test_result("Single element: index is 0",
		find_max_index(stack) == 0);
	free_stack(&stack);

	/* Test 3: Max at index 0 */
	int max_first[] = {9, 5, 2, 8, 1};
	stack = create_test_stack(max_first, 5);
	print_test_result("[9,5,2,8,1]: max index is 0",
		find_max_index(stack) == 0);
	free_stack(&stack);

	/* Test 4: Max at last index */
	int max_last[] = {1, 2, 3, 4, 5};
	stack = create_test_stack(max_last, 5);
	print_test_result("[1,2,3,4,5]: max index is 4",
		find_max_index(stack) == 4);
	free_stack(&stack);

	/* Test 5: Max in middle */
	stack = create_test_stack(values_5, 5);
	print_test_result("[5,2,8,1,9]: max index is 4",
		find_max_index(stack) == 4);
	free_stack(&stack);

	/* Test 6: Multiple maxs (returns first occurrence) */
	int multiple_maxs[] = {3, 9, 5, 9, 2};
	stack = create_test_stack(multiple_maxs, 5);
	print_test_result("[3,9,5,9,2]: first max index is 1",
		find_max_index(stack) == 1);
	free_stack(&stack);

	/* Test 7: All same values */
	int all_same[] = {42, 42, 42};
	stack = create_test_stack(all_same, 3);
	print_test_result("[42,42,42]: max index is 0",
		find_max_index(stack) == 0);
	free_stack(&stack);

	/* Test 8: Two elements */
	int two[] = {5, 10};
	stack = create_test_stack(two, 2);
	print_test_result("[5,10]: max index is 1",
		find_max_index(stack) == 1);
	free_stack(&stack);

	/* Test 9: Negative values */
	int negative[] = {-10, -2, -5, -1};
	stack = create_test_stack(negative, 4);
	print_test_result("[-10,-2,-5,-1]: max index is 3",
		find_max_index(stack) == 3);
	free_stack(&stack);
}

/* ========================================================================== */
/*                           IS_SORTED TESTS                                  */
/* ========================================================================== */

void	test_is_sorted(void)
{
	t_stack	*stack;

	ft_printf("\n===== IS_SORTED TESTS =====\n");

	/* Test 1: NULL stack */
	print_test_result("NULL stack: returns 1 (sorted)",
		is_sorted(NULL) == 1);

	/* Test 2: Single element */
	stack = stack_new(42);
	print_test_result("Single element: sorted", is_sorted(stack) == 1);
	free_stack(&stack);

	/* Test 3: Two elements sorted */
	int two_sorted[] = {1, 2};
	stack = create_test_stack(two_sorted, 2);
	print_test_result("[1,2]: sorted", is_sorted(stack) == 1);
	free_stack(&stack);

	/* Test 4: Two elements unsorted */
	int two_unsorted[] = {2, 1};
	stack = create_test_stack(two_unsorted, 2);
	print_test_result("[2,1]: not sorted", is_sorted(stack) == 0);
	free_stack(&stack);

	/* Test 5: Ascending order (sorted) */
	int ascending[] = {1, 2, 3, 4, 5};
	stack = create_test_stack(ascending, 5);
	print_test_result("[1,2,3,4,5]: sorted", is_sorted(stack) == 1);
	free_stack(&stack);

	/* Test 6: Descending order (not sorted) */
	int descending[] = {5, 4, 3, 2, 1};
	stack = create_test_stack(descending, 5);
	print_test_result("[5,4,3,2,1]: not sorted", is_sorted(stack) == 0);
	free_stack(&stack);

	/* Test 7: Partially sorted (unsorted) */
	int partial[] = {1, 2, 5, 3, 4};
	stack = create_test_stack(partial, 5);
	print_test_result("[1,2,5,3,4]: not sorted", is_sorted(stack) == 0);
	free_stack(&stack);

	/* Test 8: All same values (sorted) */
	int all_same[] = {42, 42, 42};
	stack = create_test_stack(all_same, 3);
	print_test_result("[42,42,42]: sorted", is_sorted(stack) == 1);
	free_stack(&stack);

	/* Test 9: Almost sorted (one swap away) */
	int almost[] = {1, 3, 2, 4, 5};
	stack = create_test_stack(almost, 5);
	print_test_result("[1,3,2,4,5]: not sorted", is_sorted(stack) == 0);
	free_stack(&stack);

	/* Test 10: Negative values sorted */
	int neg_sorted[] = {-10, -5, -2, 0, 3};
	stack = create_test_stack(neg_sorted, 5);
	print_test_result("[-10,-5,-2,0,3]: sorted", is_sorted(stack) == 1);
	free_stack(&stack);

	/* Test 11: Negative values unsorted */
	int neg_unsorted[] = {-2, -10, -5};
	stack = create_test_stack(neg_unsorted, 3);
	print_test_result("[-2,-10,-5]: not sorted", is_sorted(stack) == 0);
	free_stack(&stack);

	/* Test 12: With duplicates, sorted */
	int dup_sorted[] = {1, 2, 2, 3, 4};
	stack = create_test_stack(dup_sorted, 5);
	print_test_result("[1,2,2,3,4]: sorted (with duplicates)",
		is_sorted(stack) == 1);
	free_stack(&stack);

	/* Test 13: Last two unsorted */
	int last_unsorted[] = {1, 2, 3, 5, 4};
	stack = create_test_stack(last_unsorted, 5);
	print_test_result("[1,2,3,5,4]: not sorted (last pair)",
		is_sorted(stack) == 0);
	free_stack(&stack);
}

/* ========================================================================== */
/*                              MAIN                                          */
/* ========================================================================== */

int	main(void)
{
	ft_printf("========================================\n");
	ft_printf("      STACK_FIND.C UNIT TESTS\n");
	ft_printf("========================================\n");

	test_find_min();
	test_find_max();
	test_find_min_index();
	test_find_max_index();
	test_is_sorted();

	print_test_summary("stack_find.c");

	return (g_tests_failed > 0 ? 1 : 0);
}
