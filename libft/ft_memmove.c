/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:43:15 by lfarias-          #+#    #+#             */
/*   Updated: 2022/05/17 16:07:14 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*source;
	char	*dest;
	size_t	i;

	if (dst == src || len == 0)
		return ((char *) dst);
	source = (char *) src;
	dest = (char *) dst;
	if (source > dest)
	{
		i = 0;
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
		return (dest);
	}
	i = len - 1;
	while ((int) i >= 0)
	{
		dest[i] = source[i];
		i--;
	}
	return (dest);
}
