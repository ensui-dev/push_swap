/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_test.c                                   :+:      :+:    :+:   */
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
/*                        IS_VALID_NUMBER TESTS                               */
/* ========================================================================== */

void	test_is_valid_number(void)
{
	ft_printf("\n===== IS_VALID_NUMBER TESTS =====\n");

	/* Test 1: NULL string */
	print_test_result("NULL string: returns 0",
		is_valid_number(NULL) == 0);

	/* Test 2: Empty string */
	print_test_result("Empty string: returns 0",
		is_valid_number("") == 0);

	/* Test 3: Valid positive number */
	print_test_result("\"42\": valid",
		is_valid_number("42") == 1);

	/* Test 4: Valid negative number */
	print_test_result("\"-42\": valid",
		is_valid_number("-42") == 1);

	/* Test 5: Valid with plus sign */
	print_test_result("\"+42\": valid",
		is_valid_number("+42") == 1);

	/* Test 6: Zero */
	print_test_result("\"0\": valid",
		is_valid_number("0") == 1);

	/* Test 7: Just a minus sign */
	print_test_result("\"-\": invalid",
		is_valid_number("-") == 0);

	/* Test 8: Just a plus sign */
	print_test_result("\"+\": invalid",
		is_valid_number("+") == 0);

	/* Test 9: Letters only */
	print_test_result("\"abc\": invalid",
		is_valid_number("abc") == 0);

	/* Test 10: Mixed letters and digits */
	print_test_result("\"12abc\": invalid",
		is_valid_number("12abc") == 0);

	/* Test 11: Letters then digits */
	print_test_result("\"abc12\": invalid",
		is_valid_number("abc12") == 0);

	/* Test 12: Digit in middle of letters */
	print_test_result("\"a1b\": invalid",
		is_valid_number("a1b") == 0);

	/* Test 13: Space at start */
	print_test_result("\" 42\": invalid (space)",
		is_valid_number(" 42") == 0);

	/* Test 14: Space at end */
	print_test_result("\"42 \": invalid (space)",
		is_valid_number("42 ") == 0);

	/* Test 15: Double negative (allowed by implementation) */
	print_test_result("\"--42\": valid format",
		is_valid_number("--42") == 1);

	/* Test 16: Plus and minus (allowed by implementation) */
	print_test_result("\"+-42\": valid format",
		is_valid_number("+-42") == 1);

	/* Test 17: Large number (valid format) */
	print_test_result("\"2147483647\": valid format",
		is_valid_number("2147483647") == 1);

	/* Test 18: Negative large number (valid format) */
	print_test_result("\"-2147483648\": valid format",
		is_valid_number("-2147483648") == 1);

	/* Test 19: Leading zeros */
	print_test_result("\"007\": valid",
		is_valid_number("007") == 1);

	/* Test 20: Decimal point (invalid) */
	print_test_result("\"3.14\": invalid",
		is_valid_number("3.14") == 0);

	/* Test 21: Scientific notation (invalid) */
	print_test_result("\"1e5\": invalid",
		is_valid_number("1e5") == 0);

	/* Test 22: Special characters */
	print_test_result("\"42!\": invalid",
		is_valid_number("42!") == 0);
}

/* ========================================================================== */
/*                            FT_ATOL TESTS                                   */
/* ========================================================================== */

void	test_ft_atol(void)
{
	ft_printf("\n===== FT_ATOL TESTS =====\n");

	/* Test 1: NULL string */
	print_test_result("NULL string: returns 0",
		ft_atol(NULL) == 0);

	/* Test 2: Simple positive */
	print_test_result("\"42\": returns 42",
		ft_atol("42") == 42);

	/* Test 3: Simple negative */
	print_test_result("\"-42\": returns -42",
		ft_atol("-42") == -42);

	/* Test 4: Zero */
	print_test_result("\"0\": returns 0",
		ft_atol("0") == 0);

	/* Test 5: With plus sign */
	print_test_result("\"+42\": returns 42",
		ft_atol("+42") == 42);

	/* Test 6: With leading spaces */
	print_test_result("\"   42\": returns 42",
		ft_atol("   42") == 42);

	/* Test 7: With leading tabs */
	print_test_result("\"\\t42\": returns 42",
		ft_atol("\t42") == 42);

	/* Test 8: With leading spaces and negative */
	print_test_result("\"   -42\": returns -42",
		ft_atol("   -42") == -42);

	/* Test 9: INT_MAX */
	print_test_result("\"2147483647\" (INT_MAX): correct",
		ft_atol("2147483647") == 2147483647L);

	/* Test 10: INT_MIN */
	print_test_result("\"-2147483648\" (INT_MIN): correct",
		ft_atol("-2147483648") == -2147483648L);

	/* Test 11: Larger than INT_MAX */
	print_test_result("\"2147483648\" (INT_MAX+1): returns correct long",
		ft_atol("2147483648") == 2147483648L);

	/* Test 12: Smaller than INT_MIN */
	print_test_result("\"-2147483649\" (INT_MIN-1): returns correct long",
		ft_atol("-2147483649") == -2147483649L);

	/* Test 13: Leading zeros */
	print_test_result("\"007\": returns 7",
		ft_atol("007") == 7);

	/* Test 14: Negative zero */
	print_test_result("\"-0\": returns 0",
		ft_atol("-0") == 0);

	/* Test 15: Large positive long */
	print_test_result("\"9999999999\": returns 9999999999",
		ft_atol("9999999999") == 9999999999L);

	/* Test 16: Mixed whitespace */
	print_test_result("\" \\t\\n42\": returns 42",
		ft_atol(" \t\n42") == 42);
}

/* ========================================================================== */
/*                          IS_INT_RANGE TESTS                                */
/* ========================================================================== */

void	test_is_int_range(void)
{
	ft_printf("\n===== IS_INT_RANGE TESTS =====\n");

	/* Test 1: Zero */
	print_test_result("0: in range",
		is_int_range(0) == 1);

	/* Test 2: Positive number */
	print_test_result("42: in range",
		is_int_range(42) == 1);

	/* Test 3: Negative number */
	print_test_result("-42: in range",
		is_int_range(-42) == 1);

	/* Test 4: INT_MAX */
	print_test_result("INT_MAX: in range",
		is_int_range((long)INT_MAX) == 1);

	/* Test 5: INT_MIN */
	print_test_result("INT_MIN: in range",
		is_int_range((long)INT_MIN) == 1);

	/* Test 6: INT_MAX + 1 */
	print_test_result("INT_MAX + 1: out of range",
		is_int_range((long)INT_MAX + 1) == 0);

	/* Test 7: INT_MIN - 1 */
	print_test_result("INT_MIN - 1: out of range",
		is_int_range((long)INT_MIN - 1) == 0);

	/* Test 8: Large positive */
	print_test_result("9999999999: out of range",
		is_int_range(9999999999L) == 0);

	/* Test 9: Large negative */
	print_test_result("-9999999999: out of range",
		is_int_range(-9999999999L) == 0);
}

/* ========================================================================== */
/*                         HAS_DUPLICATES TESTS                               */
/* ========================================================================== */

void	test_has_duplicates(void)
{
	t_stack	*stack;
	int		no_dups[] = {1, 2, 3, 4, 5};
	int		with_dups[] = {1, 2, 3, 2, 5};
	int		all_same[] = {42, 42, 42};
	int		dups_at_ends[] = {1, 2, 3, 4, 1};

	ft_printf("\n===== HAS_DUPLICATE TESTS =====\n");

	/* Test 1: NULL stack */
	print_test_result("NULL stack: no duplicates (0)",
		has_duplicates(NULL) == 0);

	/* Test 2: Single element */
	stack = stack_new(42);
	print_test_result("Single element: no duplicates",
		has_duplicates(stack) == 0);
	free_stack(&stack);

	/* Test 3: No duplicates */
	stack = create_test_stack(no_dups, 5);
	print_test_result("[1,2,3,4,5]: no duplicates",
		has_duplicates(stack) == 0);
	free_stack(&stack);

	/* Test 4: With duplicates in middle */
	stack = create_test_stack(with_dups, 5);
	print_test_result("[1,2,3,2,5]: has duplicates",
		has_duplicates(stack) == 1);
	free_stack(&stack);

	/* Test 5: All same values */
	stack = create_test_stack(all_same, 3);
	print_test_result("[42,42,42]: has duplicates",
		has_duplicates(stack) == 1);
	free_stack(&stack);

	/* Test 6: Duplicates at start and end */
	stack = create_test_stack(dups_at_ends, 5);
	print_test_result("[1,2,3,4,1]: has duplicates",
		has_duplicates(stack) == 1);
	free_stack(&stack);

	/* Test 7: Two elements, same */
	int two_same[] = {5, 5};
	stack = create_test_stack(two_same, 2);
	print_test_result("[5,5]: has duplicates",
		has_duplicates(stack) == 1);
	free_stack(&stack);

	/* Test 8: Two elements, different */
	int two_diff[] = {5, 10};
	stack = create_test_stack(two_diff, 2);
	print_test_result("[5,10]: no duplicates",
		has_duplicates(stack) == 0);
	free_stack(&stack);

	/* Test 9: Adjacent duplicates */
	int adjacent[] = {1, 2, 2, 3};
	stack = create_test_stack(adjacent, 4);
	print_test_result("[1,2,2,3]: has duplicates",
		has_duplicates(stack) == 1);
	free_stack(&stack);

	/* Test 10: Negative duplicates */
	int neg_dups[] = {-1, -2, -1};
	stack = create_test_stack(neg_dups, 3);
	print_test_result("[-1,-2,-1]: has duplicates",
		has_duplicates(stack) == 1);
	free_stack(&stack);

	/* Test 11: Zero duplicates */
	int zero_dups[] = {0, 1, 0};
	stack = create_test_stack(zero_dups, 3);
	print_test_result("[0,1,0]: has duplicates",
		has_duplicates(stack) == 1);
	free_stack(&stack);
}

/* ========================================================================== */
/*                       COMBINED VALIDATION TESTS                            */
/* ========================================================================== */

void	test_combined_validation(void)
{
	long	num;

	ft_printf("\n===== COMBINED VALIDATION TESTS =====\n");

	/* Test 1: Valid number string -> parse -> range check */
	print_test_result("\"42\" valid -> atol -> in range",
		is_valid_number("42") &&
		is_int_range(ft_atol("42")));

	/* Test 2: Overflow number string */
	num = ft_atol("9999999999");
	print_test_result("\"9999999999\" valid format but out of range",
		is_valid_number("9999999999") &&
		!is_int_range(num));

	/* Test 3: INT_MAX boundary */
	print_test_result("INT_MAX string valid and in range",
		is_valid_number("2147483647") &&
		is_int_range(ft_atol("2147483647")));

	/* Test 4: INT_MAX + 1 boundary */
	print_test_result("INT_MAX+1 string valid format but out of range",
		is_valid_number("2147483648") &&
		!is_int_range(ft_atol("2147483648")));

	/* Test 5: INT_MIN boundary */
	print_test_result("INT_MIN string valid and in range",
		is_valid_number("-2147483648") &&
		is_int_range(ft_atol("-2147483648")));

	/* Test 6: INT_MIN - 1 boundary */
	print_test_result("INT_MIN-1 string valid format but out of range",
		is_valid_number("-2147483649") &&
		!is_int_range(ft_atol("-2147483649")));

	/* Test 7: Invalid format early rejection */
	print_test_result("\"abc\" rejected at format check",
		!is_valid_number("abc"));

	/* Test 8: Empty string early rejection */
	print_test_result("\"\" rejected at format check",
		!is_valid_number(""));
}

/* ========================================================================== */
/*                              MAIN                                          */
/* ========================================================================== */

int	main(void)
{
	ft_printf("========================================\n");
	ft_printf("       VALIDATE.C UNIT TESTS\n");
	ft_printf("========================================\n");

	test_is_valid_number();
	test_ft_atol();
	test_is_int_range();
	test_has_duplicates();
	test_combined_validation();

	print_test_summary("validate.c");

	return (g_tests_failed > 0 ? 1 : 0);
}
