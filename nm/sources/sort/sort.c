/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2018/05/01 14:59:34 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sort.h>

static void		fixe_prev(t_list *lst, t_list *prev)
{
	t_list	*cur;

	cur = lst;
	if (!cur)
		return ;
	cur->prev = prev;
	fixe_prev(cur->next, cur);
}

static void		divise_lst(t_list *source, t_list **dest_1, t_list **dest_2)
{
	t_list	*t_1;
	t_list	*t_2;

	if (!source && !source->next)
	{
		*dest_1 = source;
		*dest_2 = NULL;
	}
	else
	{
		t_1 = source;
		t_2 = source->next;
		while (t_2)
		{
			t_2 = t_2->next;
			if (t_2)
			{
				t_1 = t_1->next;
				t_2 = t_2->next;
			}
		}
		*dest_1 = source;
		*dest_2 = t_1->next;
		t_1->next = NULL;
	}
}

static void		merge_sort(t_list **lst, t_sfunc sfunc)
{
	t_list	*current;
	t_list	*lst_1;
	t_list	*lst_2;

	current = *lst;
	if (!current || !current->next || !sfunc)
		return ;
	divise_lst(current, &lst_1, &lst_2);
	merge_sort(&lst_1, sfunc);
	merge_sort(&lst_2, sfunc);
	*lst = sfunc(lst_1, lst_2);
	fixe_prev(*lst, NULL);
}

void			sort(t_list **lst, uint32_t opts, t_sfunc sfunc)
{
	if (!lst || !*lst)
		return ;
	if (sfunc)
		merge_sort(lst, sfunc);
	if (GET_BIT(opts, OPT_r) && !GET_BIT(opts, OPT_p))
		ft_lstrev(lst);
}