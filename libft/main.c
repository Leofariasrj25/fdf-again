/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:45:01 by lfarias-          #+#    #+#             */
/*   Updated: 2022/09/19 22:12:21 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf/ft_printf.h"
#include <stdio.h>
#include <ctype.h>

void	test_islower();
void	test_isupper();
void	test_iscntrl();
void	test_ispunct();
void	test_isspace();

int	main(void)
{
	printf("\t=== LIBFT tests ===\n");
	test_islower();
	test_isupper();
	test_iscntrl();
	test_ispunct();
	test_isspace();
	ft_printf("Hey %s\n", "it works");
}

void	check_outside_range(int (*ft)(int c), int (*og)(int c), int start, int end, int num_test)
{
	int i = start;
	while (i <= end)
	{
		if (!ft(i) && !og(i))
			i++;
		else
			break ;
	} 
	printf("Test %d: ", num_test);
	if (i <= end)
	{
		printf("%d\n", i);
		printf("ERROR\n");
	}
	else
		printf("OK\n");
}

void	check_in_range(int (*ft)(int c), int (*og)(int c), int start, int end, int num_test)
{
	int i = start;
	while (i <= end)
	{
		if (ft(i) && og(i))
			i++;
		else
			break ;
	} 
	printf("Test %d: ", num_test);
	if (i <= end)
		printf("ERROR\n");
	else
		printf("OK\n");
}

void	test_islower()
{
	printf("\n= ft_islower =\n");
	check_in_range(ft_islower, islower, 97, 122, 1);
	check_outside_range(ft_islower, islower, 0, 96, 2);
	check_outside_range(ft_islower, islower, 127, 127, 3);
	check_outside_range(ft_islower, islower, -127, -1, 4);
	check_outside_range(ft_islower, islower, 128, 256, 5);
}

void	test_isupper()
{
	printf("\n= ft_isupper =\n");
	check_in_range(ft_isupper, isupper, 65, 90, 1);
	check_outside_range(ft_isupper, isupper, 0, 64, 2);
	check_outside_range(ft_isupper, isupper, 91, 127, 3);
	check_outside_range(ft_isupper, isupper, -127, -1, 4);
	check_outside_range(ft_isupper, isupper, 128, 256, 5);
}

void	test_iscntrl()
{
	printf("\n = ft_iscntrl = \n");
	check_in_range(ft_iscntrl, iscntrl, 0, 31, 1);
	check_in_range(ft_iscntrl, iscntrl, 127, 127, 2);
	check_outside_range(ft_iscntrl, iscntrl, 32, 126, 3);
	check_outside_range(ft_iscntrl, iscntrl, -127, -1, 4);
	check_outside_range(ft_iscntrl, iscntrl, 128, 256, 5);
}

void	test_ispunct()
{
	printf("\n = ft_ispunct = \n");
	check_outside_range(ft_ispunct, ispunct, 0, 31, 1);
	check_outside_range(ft_ispunct, ispunct, 48, 57, 2);
	check_outside_range(ft_ispunct, ispunct, 65, 90, 3);
	check_outside_range(ft_ispunct, ispunct, 97, 122, 4);
	check_outside_range(ft_ispunct, ispunct, 127, 127, 5);
	check_outside_range(ft_ispunct, ispunct, -127, -1, 6);
	check_outside_range(ft_ispunct, ispunct, 128, 256, 7);
	check_outside_range(ft_ispunct, ispunct, 32, 32, 8);
}

void	test_isspace()
{
	printf("\n = ft_isspace =\n");
	check_in_range(ft_isspace, isspace, 32, 32, 1);
	check_in_range(ft_isspace, isspace, 9, 13, 2);
	check_outside_range(ft_isspace, isspace, 0, 8, 3);
	check_outside_range(ft_isspace, isspace, 14, 31, 4);
	check_outside_range(ft_isspace, isspace, 33, 127, 5);
	check_outside_range(ft_isspace, isspace, -127, -1, 6);
}
