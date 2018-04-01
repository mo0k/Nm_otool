/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_j32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:40 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/01 19:41:54 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						print_option_j_arch32(t_list *list)
{
	struct nlist*			elem;

	if (!list)
		return ;
	elem = list->content;
	if ((elem->n_type & N_STAB && !GET_BIT(g_meta.options, OPT_a))
		|| ((elem->n_type & N_TYPE) != N_UNDF && GET_BIT(g_meta.options, OPT_u))
		|| ((elem->n_type & N_TYPE) == N_UNDF && GET_BIT(g_meta.options, OPT_U)))
		return;
	//szap n_strx
	ft_printf("%s\n", g_stringtab +
		SWAP32(g_meta.swap, ((struct nlist_64*)(list->content))->n_un.n_strx));
}