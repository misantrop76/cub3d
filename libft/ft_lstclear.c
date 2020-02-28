/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:34:21 by mminet            #+#    #+#             */
/*   Updated: 2020/02/28 16:04:39 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	**elm;

	elm = lst;
	*elm = *lst;
	while (*elm)
	{
		*lst = *elm;
		del((*lst)->content);
		free(*lst);
		*elm = (*elm)->next;
	}
	elm = NULL;
}
