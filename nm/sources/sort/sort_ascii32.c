/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 09:39:08 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/30 22:03:53 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sort.h>

t_list		*sort_ascii32(t_list *l1, t_list *l2)
{
	t_list	*new;

	new = NULL;
	if (!l1)
		return (l2);
	if (!l2)
		return (l1);
	if (ft_strcmp(g_stringtab + SWAP32(g_meta->swap, ((struct nlist*)(l1->content))->n_un.n_strx)
			, g_stringtab + SWAP32(g_meta->swap, ((struct nlist*)(l2->content))->n_un.n_strx)) > 0)
	{
		new = l2;
		new->next = sort_ascii32(l1, l2->next);
	}
	else
	{
		new = l1;
		new->next = sort_ascii32(l1->next, l2);
	}
	return (new);
}