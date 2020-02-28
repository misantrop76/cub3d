/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:38:50 by mminet            #+#    #+#             */
/*   Updated: 2020/02/28 16:06:35 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t maxlen)
{
	size_t srclen;

	if (!dst || !src)
		return (0);
	srclen = 0;
	while (src[srclen] != '\0')
		srclen++;
	if (srclen + 1 < maxlen)
		ft_memcpy(dst, src, srclen + 1);
	else if (maxlen != 0)
	{
		ft_memcpy(dst, src, maxlen - 1);
		dst[maxlen - 1] = '\0';
	}
	return (srclen);
}
