/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 08:44:26 by lfarias-          #+#    #+#             */
/*   Updated: 2022/06/23 12:44:32 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

char	*ft_hexstr(unsigned long long n, char hexcase)
{
	char				*base;
	char				*ret;
	int					digits;
	unsigned long long	nbr;

	if (hexcase == 'u' || hexcase == 'U')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	digits = 1;
	nbr = n;
	while (nbr > 15)
	{
		nbr = nbr / 16;
		digits++;
	}
	nbr = n;
	ret = malloc(sizeof(char) * (digits + 1));
	ret[digits] = '\0';
	while (digits)
	{
		ret[--digits] = base[nbr % 16];
		nbr = nbr / 16;
	}
	return (ret);
}
