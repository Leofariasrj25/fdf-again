/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:33:36 by lfarias-          #+#    #+#             */
/*   Updated: 2022/05/17 17:12:21 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_dgts(unsigned long nbr)
{
	unsigned int	digits;

	digits = 1;
	while (nbr > 9)
	{
		nbr = nbr / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	unsigned long	nbr;
	unsigned int	digits;
	char			*nbr_s;

	digits = 0;
	if (n < 0)
	{
		nbr = (unsigned long) n * -1;
		digits++;
	}
	else
		nbr = n;
	digits += ft_get_dgts(nbr);
	nbr_s = ft_calloc(digits + 1, sizeof(char));
	if (!nbr_s)
		return (NULL);
	while (digits)
	{
		nbr_s[--digits] = nbr % 10 + 48;
		nbr = nbr / 10;
	}
	if (n < 0)
		nbr_s[0] = '-';
	return (nbr_s);
}
