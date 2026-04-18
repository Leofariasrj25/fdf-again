/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_draw.c                                          :::      ::::::::   */
/*                                                    :::      :::     */
/*   By: lfarias- <lfarias-@student.42.rio>         #+# #+#  #+#             */
/*                                                ./+#+#.+#.#+.##.#+.##.#+ */
/*   Created: 2026/04/18 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

#define SCREEN_W 1920
#define SCREEN_L 1080

/* Simplified coordinate */
typedef struct
{
	double	x;
	double	y;
	double	z;
	int		color;
} t_coord;

/* Screen bounds functions */
int	on_screen(double x, double y);
int	out_of_screen(t_coord *p0, t_coord *p1);

/* Line drawing helpers */
void	setup_vars(int delta[2], int axis[2], t_coord *p0, t_coord *p1);

/* Pixel buffer to track drawn pixels */
#define MAX_PIXELS 10000
static int g_pixels_drawn[MAX_PIXELS][2];
static int g_pixel_count = 0;

void	reset_pixels(void);
void	add_pixel(int x, int y);
int	count_pixels_at_y(int y);

void	test_on_screen_bounds(void);
void	test_out_of_screen(void);
void	test_line_slopes(void);

int	main(void)
{
	printf("\033[0;34m--- Drawing Algorithm Tests ---\033[0m\n");
	test_on_screen_bounds();
	test_out_of_screen();
	test_line_slopes();
	printf("\033[0;34m--- Summary ---\033[0m\n");
	printf("Total: %d, Passed: %d, Failed: %d\n", g_total_tests, g_tests_passed, g_tests_failed);
	if (g_tests_failed > 0)
		return (1);
	return (0);
}

/*
 * Implementation - from draw_utils.c
 */
int	on_screen(double x, double y)
{
	if ((x >= 0.0 && x <= SCREEN_W) && (y >= 0.0 && y <= SCREEN_L))
		return (1);
	else
		return (0);
}

int	out_of_screen(t_coord *p0, t_coord *p1)
{
	if (!on_screen(p0->x, p0->y) && !on_screen(p1->x, p1->y))
		return (1);
	else
		return (0);
}

void	setup_vars(int delta[2], int axis[2], t_coord *p0, t_coord *p1)
{
	delta[0] = p1->x - p0->x;
	delta[1] = p1->y - p0->y;
	axis[1] = p0->y;
	axis[0] = p0->x;
}

void	reset_pixels(void)
{
	g_pixel_count = 0;
}

void	add_pixel(int x, int y)
{
	if (g_pixel_count < MAX_PIXELS)
	{
		g_pixels_drawn[g_pixel_count][0] = x;
		g_pixels_drawn[g_pixel_count][1] = y;
		g_pixel_count++;
	}
}

/*
 * Tests
 */
void	test_on_screen_bounds(void)
{
	printf("\033[0;33m=== on_screen (bounds checking) ===\033[0m\n");

	/* Corner cases */
	TEST_ASSERT(on_screen(0, 0) == 1, "origin (0,0) is on screen");
	TEST_ASSERT(on_screen(SCREEN_W, SCREEN_L) == 1, "max corner on screen");
	TEST_ASSERT(on_screen(SCREEN_W - 1, SCREEN_L - 1) == 1, "inside max corner");

	/* Off-screen cases */
	TEST_ASSERT(on_screen(-1, 0) == 0, "x = -1 is off screen");
	TEST_ASSERT(on_screen(0, -1) == 0, "y = -1 is off screen");
	TEST_ASSERT(on_screen(SCREEN_W + 1, 0) == 0, "x > width is off screen");
	TEST_ASSERT(on_screen(0, SCREEN_L + 1) == 0, "y > height is off screen");

	/* Edge of screen */
	TEST_ASSERT(on_screen(SCREEN_W - 0.1, 0) == 1, "x just inside width");
	TEST_ASSERT(on_screen(0, SCREEN_L - 0.1) == 1, "y just inside height");

	/* Center of screen */
	TEST_ASSERT(on_screen(SCREEN_W / 2, SCREEN_L / 2) == 1, "center is on screen");
	TEST_ASSERT(on_screen(960, 540) == 1, "960x540 is on screen");
}

void	test_out_of_screen(void)
{
	t_coord	p0, p1;

	printf("\033[0;33m=== out_of_screen (line clipping) ===\033[0m\n");

	/* Both points off-screen - should skip */
	p0.x = -10; p0.y = -10;
	p1.x = -20; p1.y = -20;
	TEST_ASSERT(out_of_screen(&p0, &p1) == 1, "both off-screen -> skip");

	/* One point on, one off - should draw */
	p0.x = 100; p0.y = 100;
	p1.x = -10; p1.y = -10;
	TEST_ASSERT(out_of_screen(&p0, &p1) == 0, "one on, one off -> draw");

	/* Both on-screen - should draw */
	p0.x = 100; p0.y = 100;
	p1.x = 200; p1.y = 200;
	TEST_ASSERT(out_of_screen(&p0, &p1) == 0, "both on-screen -> draw");

	/* Edge case: exactly at boundary */
	p0.x = 0; p0.y = 0;
	p1.x = 100; p1.y = 100;
	TEST_ASSERT(out_of_screen(&p0, &p1) == 0, "at boundary is on-screen");

	/* All off-screen with one just outside */
	p0.x = SCREEN_W + 1; p0.y = 0;
	p1.x = SCREEN_W + 10; p1.y = 10;
	TEST_ASSERT(out_of_screen(&p0, &p1) == 1, "just outside width -> skip");
}

void	test_line_slopes(void)
{
	int	delta[2];
	int	axis[2];
	t_coord	p0, p1;

	printf("\033[0;33m=== Line slope detection ===\033[0m\n");

	/* Horizontal line (slope < 1) - should use draw_low_line */
	p0.x = 0; p0.y = 50;
	p1.x = 100; p1.y = 60;  /* dy < dx */
	setup_vars(delta, axis, &p0, &p1);
	TEST_ASSERT(abs(delta[1]) < abs(delta[0]), "horizontal: |dy| < |dx|");

	/* Vertical line (slope > 1) - should use draw_high_line */
	p0.x = 50; p0.y = 0;
	p1.x = 60; p1.y = 100;  /* dy > dx */
	setup_vars(delta, axis, &p0, &p1);
	TEST_ASSERT(abs(delta[1]) > abs(delta[0]), "vertical: |dy| > |dx|");

	/* Diagonal 45 degrees */
	p0.x = 0; p0.y = 0;
	p1.x = 100; p1.y = 100;
	setup_vars(delta, axis, &p0, &p1);
	TEST_ASSERT(abs(delta[1]) == abs(delta[0]), "diagonal: |dy| == |dx|");

	/* Negative direction (reversed) */
	p0.x = 100; p0.y = 100;
	p1.x = 0; p1.y = 0;
	setup_vars(delta, axis, &p0, &p1);
	TEST_ASSERT(abs(delta[1]) == abs(delta[0]), "reverse diagonal: |dy| == |dx|");

	/* Bresenham delta calculations */
	p0.x = 0; p0.y = 0;
	p1.x = 10; p1.y = 5;
	setup_vars(delta, axis, &p0, &p1);
	TEST_ASSERT(delta[0] == 10, "delta X = 10");
	TEST_ASSERT(delta[1] == 5, "delta Y = 5");

	/* Very shallow line */
	p0.x = 0; p0.y = 10;
	p1.x = 1000; p1.y = 11;
	setup_vars(delta, axis, &p0, &p1);
	TEST_ASSERT(abs(delta[1]) < abs(delta[0]), "shallow: very small dy vs dx");

	/* Very steep line */
	p0.x = 10; p0.y = 0;
	p1.x = 11; p1.y = 1000;
	setup_vars(delta, axis, &p0, &p1);
	TEST_ASSERT(abs(delta[1]) > abs(delta[0]), "steep: very large dy vs dx");
}