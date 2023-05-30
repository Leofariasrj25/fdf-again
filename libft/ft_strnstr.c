/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:29:48 by lfarias-          #+#    #+#             */
/*   Updated: 2022/05/15 21:59:47 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	size_t	i;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	str = (char *) haystack;
	while (haystack[i] != '\0')
	{
		if (ft_strncmp(str, needle, needle_len) == 0
			&& needle_len + i <= len)
			return (str);
		str++;
		i++;
	}
	return (NULL);
}
