/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:00:35 by lfarias-          #+#    #+#             */
/*   Updated: 2022/05/15 00:11:27 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	substr = ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	if (start >= ft_strlen(s))
		return (substr);
	ft_strlcpy(substr, &s[start], len + 1);
	return (substr);
}
