/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 00:19:31 by mo0ky             #+#    #+#             */
/*   Updated: 2018/01/27 21:15:34 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelfirst(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdelnext(t_list **alst, void (*del)(void*, size_t));
void				ft_lstadd_start(t_list **alst, t_list *new);
void				ft_lstadd_end(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstselect(t_list **l, char *elem, int (*f)(t_list*, \
																	char*));
void				ft_lstrev(t_list **alst);
size_t				ft_lstlen(t_list *lst);

#endif
