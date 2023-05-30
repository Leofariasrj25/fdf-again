/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:36:21 by lfarias-          #+#    #+#             */
/*   Updated: 2022/05/17 15:37:15 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char *set, char c)
{
	while (*set && *set != c)
		set++;
	if (c == *set)
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;

	end = 0;
	if (!s1 || !set)
		return (NULL);
	while (*s1 && is_charset((char *) set, *s1))
	{
		s1++;
	}
	end = ft_strlen(s1);
	while (end && is_charset((char *) set, s1[end]))
	{
		end--;
	}
	return (ft_substr(s1, 0, end + 1));
}
