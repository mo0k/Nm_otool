/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelfirst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 10:44:36 by mo0ky             #+#    #+#             */
/*   Updated: 2017/01/24 11:01:31 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_lstdelfirst(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*next;

	if (!*alst && !del)
		return ;
	next = (*alst)->next;
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = next;
	if (*alst)
		(*alst)->prev = NULL;
}
