/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 00:00:00 by lfarias-          #+#    #+#             */
/*   Updated: 2026/04/17 00:00:00 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/test_utils.h"

// Global variables for test tracking
int g_tests_passed = 0;
int g_tests_failed = 0;
int g_total_tests = 0;

static void test_hello_world(void)
{
    TEST_ASSERT(1 == 1, "Hello World Test: 1 equals 1");
    TEST_ASSERT_EQ_INT(1, 1, "Hello World Test: 1 equals 1 using EQ_INT");
    TEST_ASSERT(0, "Hello World Test: This should fail");
}

int main(void)
{
    printf("\033[0;34m--- Running FdF Test Suite ---\033[0m\n");

    test_hello_world();

    printf("\n\033[0;34m--- Test Summary ---\033[0m\n");
    printf("Total: %d, Passed: %d, Failed: %d\n", g_total_tests, g_tests_passed, g_tests_failed);

    if (g_tests_failed > 0)
        return (1);
    return (0);
}
