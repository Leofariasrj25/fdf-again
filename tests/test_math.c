/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_math.c                                          :::      ::::::::   */
/*                                                    :::      :::     */
/*   By: lfarias- <lfarias-@student.42.rio>         #+# #+#  #+#             */
/*                                                ./+#+#.+#.#+.##.#+.##.#+ */
/*   Created: 2026/04/18 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

#define TEST_ASSERT_EQ_FLT(exp, act, tolerance, msg) \
	do { \
		g_total_tests++; \
		if (fabs((exp) - (act)) < (tolerance)) { \
			g_tests_passed++; \
			printf("\033[0;32mPASS: %s (exp=%.4f act=%.4f)\033[0m\n", msg, exp, act); \
		} else { \
			g_tests_failed++; \
			printf("\033[0;31mFAIL: %s (exp=%.4f act=%.4f)\033[0m\n", msg, exp, act); \
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

#define PI 3.14159265358979323846

/*
 * t_coord - simplified coordinate struct
 */
typedef struct
{
	double	x;
	double	y;
	double	z;
} t_coord;

/* Forward declarations */
double	dg2_rad(double angle);
int		round_to_i(double value);
void	scale(t_coord *point, double scale_factor, int size);
void	translate(t_coord *point, t_coord *move, int size);
void	z_scale(t_coord *projection, double z_scale_factor, int size);

void	test_dg2_rad(void);
void	test_round_to_i(void);
void	test_scale(void);
void	test_translate(void);
void	test_z_scale(void);

int	main(void)
{
	printf("\033[0;34m--- Math Utility Tests ---\033[0m\n");
	test_dg2_rad();
	test_round_to_i();
	test_scale();
	test_translate();
	test_z_scale();
	printf("\033[0;34m--- Summary ---\033[0m\n");
	printf("Total: %d, Passed: %d, Failed: %d\n", g_total_tests, g_tests_passed, g_tests_failed);
	if (g_tests_failed > 0)
		return (1);
	return (0);
}

/*
 * Implementation
 */
double	dg2_rad(double angle)
{
	static const double	pi = 3.14159;

	return (pi * angle / (double)180.00);
}

int	round_to_i(double value)
{
	int	rounded;

	rounded = (int)(value);
	if (fmod(value, 1) >= 0.5)
		return (rounded + 1);
	else
		return (rounded);
}

void	scale(t_coord *point, double scale_factor, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		point[i].x = point[i].x * scale_factor;
		point[i].y = point[i].y * scale_factor;
		point[i].z = point[i].z * scale_factor;
		i++;
	}
}

void	translate(t_coord *point, t_coord *move, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		point[i].x = point[i].x + move->x;
		point[i].y = point[i].y + move->y;
		point[i].z = point[i].z + move->z;
		i++;
	}
}

void	z_scale(t_coord *projection, double z_scale_factor, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		projection[i].z = (double)projection[i].z * z_scale_factor;
		i++;
	}
}

/*
 * Tests
 */
void	test_dg2_rad(void)
{
	double	result;

	printf("\033[0;33m=== dg2_rad (degrees to radians) ===\033[0m\n");

	result = dg2_rad(0);
	TEST_ASSERT_EQ_FLT(0.0, result, 0.0001, "0 degrees = 0 radians");

	result = dg2_rad(180);
	TEST_ASSERT_EQ_FLT(PI, result, 0.0001, "180 degrees = PI");

	result = dg2_rad(90);
	TEST_ASSERT_EQ_FLT(PI / 2, result, 0.0001, "90 degrees = PI/2");

	result = dg2_rad(360);
	TEST_ASSERT_EQ_FLT(2 * PI, result, 0.0001, "360 degrees = 2*PI");

	result = dg2_rad(-90);
	TEST_ASSERT_EQ_FLT(-PI / 2, result, 0.0001, "-90 degrees = -PI/2");

	result = dg2_rad(45);
	TEST_ASSERT_EQ_FLT(PI / 4, result, 0.0001, "45 degrees = PI/4");
}

void	test_round_to_i(void)
{
	int	result;

	printf("\033[0;33m=== round_to_i (double to int) ===\033[0m\n");

	result = round_to_i(1.0);
	TEST_ASSERT_EQ_INT(1, result, "1.0 rounds to 1");

	result = round_to_i(5.0);
	TEST_ASSERT_EQ_INT(5, result, "5.0 rounds to 5");

	result = round_to_i(1.4);
	TEST_ASSERT_EQ_INT(1, result, "1.4 rounds down to 1");

	result = round_to_i(1.5);
	TEST_ASSERT_EQ_INT(2, result, "1.5 rounds up to 2");

	result = round_to_i(1.9);
	TEST_ASSERT_EQ_INT(2, result, "1.9 rounds up to 2");

	result = round_to_i(-1.4);
	TEST_ASSERT_EQ_INT(-1, result, "-1.4 rounds to -1");

	result = round_to_i(-1.5);
	TEST_ASSERT_EQ_INT(-1, result, "-1.5 rounds to -1");

	result = round_to_i(-1.9);
	TEST_ASSERT_EQ_INT(-1, result, "-1.9 rounds toward zero");

	result = round_to_i(0.5);
	TEST_ASSERT_EQ_INT(1, result, "0.5 rounds to 1");

	result = round_to_i(-0.5);
	TEST_ASSERT_EQ_INT(0, result, "-0.5 rounds to 0");
}

void	test_scale(void)
{
	t_coord	points[3];

	printf("\033[0;33m=== scale (multiply all coords) ===\033[0m\n");

	points[0].x = 1.0; points[0].y = 2.0; points[0].z = 3.0;
	points[1].x = 4.0; points[1].y = 5.0; points[1].z = 6.0;
	points[2].x = 7.0; points[2].y = 8.0; points[2].z = 9.0;

	scale(points, 2.0, 3);
	TEST_ASSERT(points[0].x == 2.0, "point[0].x scaled by 2");
	TEST_ASSERT(points[0].y == 4.0, "point[0].y scaled by 2");
	TEST_ASSERT(points[0].z == 6.0, "point[0].z scaled by 2");
	TEST_ASSERT(points[1].x == 8.0, "point[1].x scaled by 2");
	TEST_ASSERT(points[2].y == 16.0, "point[2].y scaled by 2");

	/* Reset and test scale by 0 */
	points[0].x = 5.0; points[0].y = 10.0;
	points[1].x = 0.0; points[1].y = 0.0;
	scale(points, 0.0, 2);
	TEST_ASSERT(points[0].x == 0.0, "scale by 0 zeros x");
	TEST_ASSERT(points[0].y == 0.0, "scale by 0 zeros y");
	TEST_ASSERT(points[1].x == 0.0, "scale 0 stays 0");
}

void	test_translate(void)
{
	t_coord	points[3];
	t_coord	offset;

	printf("\033[0;33m=== translate (add offset) ===\033[0m\n");

	points[0].x = 0.0; points[0].y = 0.0; points[0].z = 0.0;
	points[1].x = 1.0; points[1].y = 2.0; points[1].z = 3.0;
	offset.x = 10.0; offset.y = 20.0; offset.z = 30.0;

	translate(points, &offset, 2);
	TEST_ASSERT(points[0].x == 10.0, "point[0].x + offset");
	TEST_ASSERT(points[0].y == 20.0, "point[0].y + offset");
	TEST_ASSERT(points[0].z == 30.0, "point[0].z + offset");
	TEST_ASSERT(points[1].x == 11.0, "point[1].x + offset");
	TEST_ASSERT(points[1].y == 22.0, "point[1].y + offset");

	/* Negative translation */
	offset.x = -5.0; offset.y = -10.0; offset.z = -15.0;
	points[0].x = 10.0; points[0].y = 20.0;
	translate(points, &offset, 1);
	TEST_ASSERT(points[0].x == 5.0, "negative translate x");
	TEST_ASSERT(points[0].y == 10.0, "negative translate y");
}

void	test_z_scale(void)
{
	t_coord	points[3];

	printf("\033[0;33m=== z_scale (z coord scaling) ===\033[0m\n");

	points[0].z = 1.0;
	points[1].z = 2.0;
	points[2].z = 3.0;
	z_scale(points, 2.0, 3);
	TEST_ASSERT(points[0].z == 2.0, "z scaled by 2");
	TEST_ASSERT(points[1].z == 4.0, "z 2 scaled to 4");
	TEST_ASSERT(points[2].z == 6.0, "z 3 scaled to 6");

	/* z_scale by 0 */
	points[0].z = 5.0;
	z_scale(points, 0.0, 1);
	TEST_ASSERT(points[0].z == 0.0, "z scaled to 0");

	/* z_scale by 0.5 */
	points[0].z = 10.0;
	z_scale(points, 0.5, 1);
	TEST_ASSERT(points[0].z == 5.0, "z halved");
}