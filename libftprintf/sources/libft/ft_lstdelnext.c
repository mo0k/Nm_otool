/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 10:45:03 by mo0ky             #+#    #+#             */
/*   Updated: 2017/01/30 14:53:18 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_lstdelnext(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*next;

	if (!*alst && !del)
		return ;
	if (!(*alst)->next)
		return ;
	del((*alst)->next->content, (*alst)->next->content_size);
	free((*alst)->next);
	if (!(next = (*alst)->next->next))
	{
		(*alst)->next->prev = *alst;
		(*alst)->next = NULL;
	}
	else
	{
		next->prev = *alst;
		(*alst)->next = next;
	}
}
