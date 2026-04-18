/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                          :::      ::::::::   */
/*                                                    :::      :::     */
/*   By: lfarias- <lfarias-@student.42.rio>         #+# #+#  #+#             */
/*                                                ./+#+#.+#.#+.##.#+.##.#+ */
/*   Created: 2026/04/18 by lfarias-                 ###    ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char	**ft_split(const char *s, char c);
void	free_2d_array(void **matrix);
int		get_line_size(char **fields);
int		check_line_format(char **fields);

void	test_get_line_size(void);
void	test_check_line_format(void);
void	test_ft_split_edge_cases(void);
void	test_split_null_empty(void);

int	main(void)
{
	printf("\033[0;34m--- Map Parsing Tests ---\033[0m\n");
	test_get_line_size();
	test_check_line_format();
	test_ft_split_edge_cases();
	test_split_null_empty();
	printf("\033[0;34m--- Summary ---\033[0m\n");
	printf("Total: %d, Passed: %d, Failed: %d\n", g_total_tests, g_tests_passed, g_tests_failed);
	if (g_tests_failed > 0)
		return (1);
	return (0);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	int		count;
	char	**result;

	if (!s)
		return (NULL);
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			int start = i;
			while (s[i] && s[i] != c)
				i++;
			result[j] = malloc(i - start + 1);
			if (!result[j])
			{
				while (j > 0)
					free(result[--j]);
				free(result);
				return (NULL);
			}
			strncpy(result[j], s + start, i - start);
			result[j][i - start] = '\0';
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}

void	free_2d_array(void **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	get_line_size(char **fields)
{
	int	size;

	if (!fields)
		return (0);
	size = 0;
	while (fields[size])
		size++;
	return (size);
}

int	check_line_format(char **fields)
{
	static int	min_len = -1;
	static int	curr_line = -1;
	int			line_len;

	curr_line++;
	line_len = get_line_size(fields);
	if ((line_len == 0 && curr_line == 0)
		|| (fields[0] && fields[0][0] == '\n' && curr_line == 0))
		return (0);
	if (min_len == -1)
		min_len = line_len;
	if (line_len < min_len)
		return (0);
	return (1);
}

void	test_get_line_size(void)
{
	char	**fields;

	printf("\033[0;33m=== get_line_size ===\033[0m\n");

	fields = (char *[]){"1", "2", "3", NULL};
	TEST_ASSERT_EQ_INT(3, get_line_size(fields), "3 fields");

	fields = (char *[]){"1", "2", NULL};
	TEST_ASSERT_EQ_INT(2, get_line_size(fields), "2 fields");

	fields = (char *[]){NULL};
	TEST_ASSERT_EQ_INT(0, get_line_size(fields), "empty line");

	fields = NULL;
	TEST_ASSERT_EQ_INT(0, get_line_size(fields), "NULL input");
}

void	test_check_line_format(void)
{
	char	**fields;

	printf("\033[0;33m=== check_line_format ===\033[0m\n");

	fields = (char *[]){"1", "2", "3", NULL};
	TEST_ASSERT(check_line_format(fields) == 1, "first valid line");

	fields = (char *[]){"1", "2", "3", NULL};
	TEST_ASSERT(check_line_format(fields) == 1, "same length valid");

	fields = (char *[]){NULL};
	TEST_ASSERT(check_line_format(fields) == 0, "empty line invalid");
}

void	test_ft_split_edge_cases(void)
{
	char	**result;

	printf("\033[0;33m=== ft_split edge cases ===\033[0m\n");

	/* Empty string */
	result = ft_split("", ' ');
	TEST_ASSERT(result != NULL, "empty string split");
	if (result)
	{
		TEST_ASSERT(result[0] == NULL, "empty has NULL sentinel");
		free_2d_array((void **)result);
	}

	/* Leading/trailing spaces */
	result = ft_split("  1  2  3  ", ' ');
	TEST_ASSERT(result != NULL, "spaces split");
	if (result)
	{
		TEST_ASSERT(strcmp(result[0], "1") == 0, "first token");
		free_2d_array((void **)result);
	}

	/* Negative numbers */
	result = ft_split("-1 0 1", ' ');
	TEST_ASSERT(result != NULL, "negatives split");
	if (result)
	{
		TEST_ASSERT(strcmp(result[0], "-1") == 0, "neg as string");
		free_2d_array((void **)result);
	}

	/* Floats */
	result = ft_split("1.5 2.5", ' ');
	TEST_ASSERT(result != NULL, "floats split");
	if (result)
	{
		TEST_ASSERT(strcmp(result[0], "1.5") == 0, "1.5 kept");
		free_2d_array((void **)result);
	}
}

void	test_split_null_empty(void)
{
	printf("\033[0;33m=== split NULL/empty ===\033[0m\n");

	/* NULL input */
	char **result = ft_split(NULL, ' ');
	TEST_ASSERT(result == NULL, "NULL returns NULL");

	/* Multiple spaces between */
	result = ft_split("1   2     3", ' ');
	TEST_ASSERT(result != NULL, "multiple spaces");
	if (result)
	{
		int count = 0;
		while (result[count])
			count++;
		TEST_ASSERT_EQ_INT(3, count, "3 tokens");
		free_2d_array((void **)result);
	}

	/* Single token */
	result = ft_split("1", ' ');
	TEST_ASSERT(result != NULL, "single token");
	if (result)
	{
		TEST_ASSERT(strcmp(result[0], "1") == 0, "token is 1");
		free_2d_array((void **)result);
	}
}