/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_x32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:29 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/07 11:48:59 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						print_option_x_arch32(t_list *list)
{
	struct nlist*			elem;

	if (!list)
		return ;
	elem = list->content;
	if (((elem->n_type & N_STAB) && !GET_BIT(g_meta->options, OPT_a))
		|| ((elem->n_type & N_TYPE) != N_UNDF && GET_BIT(g_meta->options, OPT_u))
		|| ((elem->n_type & N_TYPE) == N_UNDF && GET_BIT(g_meta->options, OPT_U)))
		return;
	ft_printf("%08x %02x %02x %04x %08x %s\n", 
						SWAP32(g_meta->swap, elem->n_value),
						elem->n_type,
						elem->n_sect,
						SWAP16(g_meta->swap, elem->n_desc),
						elem->n_un.n_strx,
						g_stringtab + SWAP32(g_meta->swap, elem->n_un.n_strx)
						);
	if ((elem->n_type & N_TYPE) == N_INDR)
		ft_printf(" (indirect for %016llx %s)\n",
					SWAP32(g_meta->swap, elem->n_value),
					g_stringtab + SWAP32(g_meta->swap, elem->n_un.n_strx));
	else
		ft_printf("\n");
}
