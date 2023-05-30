/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 07:38:56 by lfarias-          #+#    #+#             */
/*   Updated: 2022/06/23 12:43:50 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

char	*ft_utoa(unsigned int n)
{
	unsigned long	nbr;
	unsigned long	digits;
	char			*ret;

	nbr = n;
	digits = 1;
	while (nbr > 9)
	{
		nbr = nbr / 10;
		digits++;
	}
	nbr = n;
	ret = malloc(sizeof(char) * (digits + 1));
	ret[digits] = '\0';
	while (digits)
	{
		ret[--digits] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	return (ret);
}
