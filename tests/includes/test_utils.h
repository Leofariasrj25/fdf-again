/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 00:00:00 by lfarias-          #+#    #+#             */
/*   Updated: 2026/04/17 00:00:00 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTILS_H
# define TEST_UTILS_H

# include <stdio.h>

extern int g_tests_passed;
extern int g_tests_failed;
extern int g_total_tests;

# define TEST_ASSERT(condition, message) \
    do { \
        g_total_tests++; \
        if (condition) { \
            g_tests_passed++; \
            printf("\033[0;32mPASSED: %s\033[0m\n", message); \
        } else { \
            g_tests_failed++; \
            printf("\033[0;31mFAILED: %s (Condition: %s)\033[0m\n", message, #condition); \
        } \
    } while (0)

# define TEST_ASSERT_EQ_INT(expected, actual, message) \
    do { \
        g_total_tests++; \
        if ((expected) == (actual)) { \
            g_tests_passed++; \
            printf("\033[0;32mPASSED: %s (Expected: %d, Actual: %d)\033[0m\n", message, expected, actual); \
        } else { \
            g_tests_failed++; \
            printf("\033[0;31mFAILED: %s (Expected: %d, Actual: %d)\033[0m\n", message, expected, actual); \
        } \
    } while (0)

// You can add more specific assertion macros here as needed, e.g., for doubles, strings.

#endif
