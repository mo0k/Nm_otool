/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_x64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:29 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/01 19:42:10 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						print_option_x_arch64(t_list *list)
{
	struct nlist_64*			elem;

	if (!list)
		return ;
	elem = list->content;
	if (((elem->n_type & N_STAB) && !GET_BIT(g_meta->options, OPT_a))
		|| ((elem->n_type & N_TYPE) != N_UNDF && GET_BIT(g_meta->options, OPT_u))
		|| ((elem->n_type & N_TYPE) == N_UNDF && GET_BIT(g_meta->options, OPT_U)))
		return;
	ft_printf("%016llx %02x %02x %04x %08x %s\n", 
									SWAP64(g_meta->swap, elem->n_value),
									elem->n_type,
									elem->n_sect,
									SWAP16(g_meta->swap, elem->n_desc),
									elem->n_un.n_strx,
									g_stringtab + SWAP32(g_meta->swap, elem->n_un.n_strx)
									);	
}
