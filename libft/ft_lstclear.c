/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstclear.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/28 15:34:21 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 17:05:46 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
