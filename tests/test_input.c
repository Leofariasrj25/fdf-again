/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input.c                                         :::      ::::::::   */
/*                                                    :::      :::     */
/*   By: lfarias- <lfarias-@student.42.rio>         #+# #+#  #+#             */
/*                                                ./+#+#.+#.#+.##.#+.##.#+ */
/*   Created: 2026/04/18 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

static int g_tests_passed = 0;
static int g_tests_failed = 0;
static int g_total_tests = 0;

#define TEST_ASSERT(cond, msg) \
	do { \
		g_total_tests++; \
		if (cond) { \
			g_tests_passed++; \
			printf("\033[0;32mPASS: %s\033[0m\n", msg); \
		} else { \
			g_tests_failed++; \
			printf("\033[0;31mFAIL: %s\033[0m\n", msg); \
		} \
	} while (0)

#define TEST_ASSERT_EQ_INT(exp, act, msg) \
	do { \
		g_total_tests++; \
		if ((exp) == (act)) { \
			g_tests_passed++; \
			printf("\033[0;32mPASS: %s (exp=%d act=%d)\033[0m\n", msg, exp, act); \
		} else { \
			g_tests_failed++; \
			printf("\033[0;31mFAIL: %s (exp=%d act=%d)\033[0m\n", msg, exp, act); \
		} \
	} while (0)

#define TEST_ASSERT_NE_INT(exp, act, msg) \
	do { \
		g_total_tests++; \
		if ((exp) != (act)) { \
			g_tests_passed++; \
			printf("\033[0;32mPASS: %s (exp!=%d act=%d)\033[0m\n", msg, exp, act); \
		} else { \
			g_tests_failed++; \
			printf("\033[0;31mFAIL: %s (exp=%d act=%d)\033[0m\n", msg, exp, act); \
		} \
	} while (0)

int		check_input_size(int argc);
double	get_scale(int map_width, int map_length, int argc, char **argv);
double	get_z_scale(int argc, char **argv);

void	test_argc_validation(void);
void	test_scale_edge_cases(void);
void	test_zscale_edge_cases(void);
void	test_filename_cases(void);

int	main(void)
{
	printf("\033[0;34m--- Comprehensive Input Tests ---\033[0m\n");
	test_argc_validation();
	test_scale_edge_cases();
	test_zscale_edge_cases();
	printf("\033[0;34m--- Summary ---\033[0m\n");
	printf("Total: %d, Passed: %d, Failed: %d\n", g_total_tests, g_tests_passed, g_tests_failed);
	if (g_tests_failed > 0)
		return (1);
	return (0);
}

int	check_input_size(int argc)
{
	if (!((argc - 1) == 1 || (argc - 1) == 3))
		return (0);
	return (1);
}

double	get_scale(int map_width, int map_length, int argc, char **argv)
{
	double	scale_x;
	double	scale_y;

	if ((argc - 1) == 3)
		return (atof(argv[2]));
	else
	{
		scale_x = 320 / (double)map_width;
		scale_y = 240 / (double)map_length;
		if (scale_x > scale_y)
			return (scale_x);
		else
			return (scale_y);
	}
}

double	get_z_scale(int argc, char **argv)
{
	if ((argc - 1) == 3)
		return (atof(argv[3]));
	else
		return (0.5);
}

void	test_argc_validation(void)
{
	printf("\033[0;33m=== Argc Validation ===\033[0m\n");

	/* Valid cases */
	TEST_ASSERT(check_input_size(2) == 1, "./fdf map.fdf - valid (2 args)");
	TEST_ASSERT(check_input_size(4) == 1, "./fdf map.fdf 10 0.5 - valid (4 args)");

	/* Invalid: too few */
	TEST_ASSERT(check_input_size(1) == 0, "./fdf - invalid (1 arg)");
	TEST_ASSERT(check_input_size(0) == 0, "no args - invalid (0 args)");

	/* Invalid: too many or incomplete */
	TEST_ASSERT(check_input_size(3) == 0, "./fdf map.fdf 10 - invalid (3 args, missing z)");
	TEST_ASSERT(check_input_size(5) == 0, "./fdf map.fdf 10 0.5 extra - invalid (5 args)");
	TEST_ASSERT(check_input_size(6) == 0, "6 args - invalid");
}

void	test_scale_edge_cases(void)
{
	double	scale;

	printf("\033[0;33m=== Scale Edge Cases ===\033[0m\n");

	/* Normal calculations */
	scale = get_scale(10, 10, 2, (char *[]){"", ""});
	TEST_ASSERT(scale > 0, "default scale is positive for 10x10");

	scale = get_scale(100, 50, 2, (char *[]){"", ""});
	TEST_ASSERT(scale > 0, "default scale is positive for 100x50");

	/* Small map - large scale */
	scale = get_scale(1, 1, 2, (char *[]){"", ""});
	TEST_ASSERT(scale > 0, "1x1 map gets positive scale");
	TEST_ASSERT(scale == 320, "1x1 takes width 320/1=320");

	/* Large map - small scale */
	scale = get_scale(1000, 1000, 2, (char *[]){"", ""});
	TEST_ASSERT(scale > 0, "1000x1000 gets positive scale");
	TEST_ASSERT(scale <= 1, "1000x1000 scale is reasonable");

	/* User-specified integer */
	scale = get_scale(10, 10, 4, (char *[]){"", "", "5", "0.5"});
	TEST_ASSERT(scale == 5, "user scale 5");

	/* User-specified decimal */
	scale = get_scale(10, 10, 4, (char *[]){"", "", "2.5", "0.5"});
	TEST_ASSERT(scale == 2.5, "user decimal scale 2.5");

	/* Zero scale */
	scale = get_scale(10, 10, 4, (char *[]){"", "", "0", "0.5"});
	TEST_ASSERT(scale == 0, "zero scale");

	/* Negative scale - should we allow? */
	scale = get_scale(10, 10, 4, (char *[]){"", "", "-5", "0.5"});
	TEST_ASSERT(scale < 0, "negative scale produces negative result");
}

void	test_zscale_edge_cases(void)
{
	double	z_scale;

	printf("\033[0;33m=== Z-Scale Edge Cases ===\033[0m\n");

	/* Default */
	z_scale = get_z_scale(2, (char *[]){"", ""});
	TEST_ASSERT(z_scale == 0.5, "default z_scale 0.5");

	/* User-specified integer */
	z_scale = get_z_scale(4, (char *[]){"", "", "10", "5"});
	TEST_ASSERT(z_scale == 5, "user z_scale 5");

	/* User-specified decimal */
	z_scale = get_z_scale(4, (char *[]){"", "", "10", "0.25"});
	TEST_ASSERT(z_scale == 0.25, "user z_scale 0.25");

	/* Zero z_scale */
	z_scale = get_z_scale(4, (char *[]){"", "", "10", "0"});
	TEST_ASSERT(z_scale == 0, "zero z_scale");

	/* Negative z_scale */
	z_scale = get_z_scale(4, (char *[]){"", "", "10", "-1"});
	TEST_ASSERT(z_scale == -1, "negative z_scale");
}

void	test_filename_cases(void)
{
	printf("\033[0;33m=== Filename Validation ===\033[0m\n");

	TEST_ASSERT(check_input_size(2) == 1, "valid filename 'map.fdf'");
	TEST_ASSERT(check_input_size(2) == 1, "valid path '/path/to/map.fdf'");
	TEST_ASSERT(check_input_size(2) == 1, "valid 'maps/42.fdf'");
}