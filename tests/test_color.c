/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_color.c                                         :::      ::::::::   */
/*                                                    :::      :::     */
/*   By: lfarias- <lfarias-@student.42.rio>         #+# #+#  #+#             */
/*                                                ./+#+#.+#.#+.##.#+.##.#+ */
/*   Created: 2026/04/18 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

#define TEST_ASSERT_EQ_HEX(exp, act, msg) \
	do { \
		g_total_tests++; \
		if ((exp) == (act)) { \
			g_tests_passed++; \
			printf("\033[0;32mPASS: %s (0x%08x)\033[0m\n", msg, act); \
		} else { \
			g_tests_failed++; \
			printf("\033[0;31mFAIL: %s exp=0x%08x act=0x%08x\033[0m\n", msg, exp, act); \
		} \
	} while (0)

static uint32_t	extract_r(uint32_t c);
static uint32_t	extract_g(uint32_t c);
static uint32_t	extract_b(uint32_t c);
static uint32_t	extract_a(uint32_t c);
static uint32_t	convert_color(int color);

void	test_conversion_preserves_channels(void);
void	test_alpha_default(void);
void	test_app_colors(void);

int	main(void)
{
	printf("\033[0;34m--- Color Conversion Tests ---\033[0m\n");
	test_conversion_preserves_channels();
	test_alpha_default();
	test_app_colors();
	printf("\033[0;34m--- Summary ---\033[0m\n");
	printf("Total: %d, Passed: %d, Failed: %d\n", g_total_tests, g_tests_passed, g_tests_failed);
	if (g_tests_failed > 0)
		return (1);
	return (0);
}

/* Helpers to verify channel extraction post-conversion */
static uint32_t	extract_r(uint32_t c) { return (c >> 24) & 0xFF; }
static uint32_t	extract_g(uint32_t c) { return (c >> 16) & 0xFF; }
static uint32_t	extract_b(uint32_t c) { return (c >> 8) & 0xFF; }
static uint32_t	extract_a(uint32_t c) { return c & 0xFF; }

/*
 * Convert from old mlx format 0xAABBGGRR to MLX42 0xRRGGBBAA
 */
static uint32_t	convert_color(int color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	a = (color >> 24) & 0xFF;
	if (a == 0)
		a = 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	test_conversion_preserves_channels(void)
{
	uint32_t	result;
	uint8_t	r, g, b, a;

	printf("\033[0;33m=== Channel Preservation ===\033[0m\n");

	/* Input: R=FF, G=00, B=00 (red only) = 0x00FF0000 */
	result = convert_color(0x00FF0000);
	r = extract_r(result); g = extract_g(result); b = extract_b(result); a = extract_a(result);
	TEST_ASSERT(r == 0xFF && g == 0x00 && b == 0x00 && a == 0xFF,
		"Red 0x00FF0000 -> R=FF,G=0,B=0,A=FF");

	/* Input: R=00, G=FF, B=00 (green only) = 0x0000FF00 */
	result = convert_color(0x0000FF00);
	r = extract_r(result); g = extract_g(result); b = extract_b(result); a = extract_a(result);
	TEST_ASSERT(r == 0x00 && g == 0xFF && b == 0x00 && a == 0xFF,
		"Green 0x0000FF00 -> R=0,G=FF,B=0,A=FF");

	/* Input: R=00, G=00, B=FF (blue only) = 0x000000FF */
	result = convert_color(0x000000FF);
	r = extract_r(result); g = extract_g(result); b = extract_b(result); a = extract_a(result);
	TEST_ASSERT(r == 0x00 && g == 0x00 && b == 0xFF && a == 0xFF,
		"Blue 0x000000FF -> R=0,G=0,B=FF,A=FF");
}

void	test_alpha_default(void)
{
	uint32_t	result;
	uint8_t	a;

	printf("\033[0;33m=== Alpha Handling ===\033[0m\n");

	/* Alpha=0 -> should become 255 */
	result = convert_color(0x00000000);
	a = extract_a(result);
	TEST_ASSERT(a == 0xFF, "alpha=0 becomes 255");

	/* No alpha field (format missing AA): A defaults to 0x00 -> becomes FF */
	result = convert_color(0x0033CC99);  /* RGB only, no AA */
	a = extract_a(result);
	TEST_ASSERT(a == 0xFF, "no AA field defaults to FF");

	/* Explicit alpha preserved */
	result = convert_color(0x80000000);  /* AA=80 */
	a = extract_a(result);
	TEST_ASSERT(a == 0x80, "AA=80 preserved");
}

void	test_app_colors(void)
{
	uint32_t	result;

	printf("\033[0;33m=== App Color Palettes ===\033[0m\n");

	/* base_color = 0x4B4B4B */
	result = convert_color(0x004B4B4B);
	TEST_ASSERT_EQ_HEX(0x4B4B4BFF, result, "base 0x004B4B4B");

	/* medium_color = 0xC4C4C4 */
	result = convert_color(0x00C4C4C4);
	TEST_ASSERT_EQ_HEX(0xC4C4C4FF, result, "medium 0x00C4C4C4");

	/* top_color = 0xff9001 in old formatAABBGGRR = 0x00FF9001
 * Input: AA=00, BB=FF, GG=90, RR=01
 * Extracted: R=0x00FF, G=0x90, B=0x01
 * Converted: RR=0xFF, GG=0x90, BB=0x01, AA=0x00->0xFF
 * -> 0xFF << 24 | 0x90 << 16 | 0x01 << 8 | 0xFF = 0xFF9001FF
 */
	result = convert_color(0x00FF9001);
	TEST_ASSERT_EQ_HEX(0xFF9001FF, result, "top orange");

	/* menu colors */
	result = convert_color(0x00333333);
	TEST_ASSERT_EQ_HEX(0x333333FF, result, "menu BG");

	result = convert_color(0x00FFFFFF);
	TEST_ASSERT_EQ_HEX(0xFFFFFFFF, result, "white");

	result = convert_color(0x00000000);
	TEST_ASSERT_EQ_HEX(0x000000FF, result, "black");
}