/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:21:49 by mminet            #+#    #+#             */
/*   Updated: 2020/02/28 16:04:55 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ptr;
	const char	*str;

	ptr = dest;
	str = src;
	if (dest == 0 && src == 0)
		return (0);
	while (n > 0)
	{
		*ptr = *str;
		str++;
		ptr++;
		n--;
	}
	return (dest);
}
