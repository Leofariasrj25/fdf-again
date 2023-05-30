/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:40:58 by lfarias-          #+#    #+#             */
/*   Updated: 2022/05/15 20:10:43 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	n;
	size_t	i;

	n = dstsize;
	i = 0;
	while (n != 0 && dst[i] != '\0')
	{
		i++;
		n--;
	}
	dstlen = i;
	if (n == 0)
		return (dstlen + ft_strlen(src));
	i = -1;
	while (src[++i] != '\0')
	{
		if (n > 1)
		{
			dst[dstlen + i] = src[i];
			n--;
		}
	}
	dst[dstlen + i] = '\0';
	return (dstlen + i);
}
