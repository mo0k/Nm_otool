/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 10:43:16 by mo0ky             #+#    #+#             */
/*   Updated: 2017/01/24 11:00:54 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_lstrev(t_list **alst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*tmp;

	prev = NULL;
	cur = *alst;
	if (!*alst)
		return ;
	while (cur)
	{
		tmp = cur->next;
		cur->next = cur->prev;
		cur->prev = tmp;
		prev = cur;
		cur = cur->prev;
	}
	*alst = prev;
}
