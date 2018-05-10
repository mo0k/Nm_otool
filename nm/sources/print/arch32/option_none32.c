/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_none32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:47 by mo0k              #+#    #+#             */
/*   Updated: 2018/04/01 19:42:29 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						print_option_none_arch32(t_list *list)
{
	struct nlist*				elem;
	char 						buf[85];

	if (!list)
		return ;
	elem = list->content;
	if (((elem->n_type & N_STAB) && !GET_BIT(g_meta.options, OPT_a))
		|| ((elem->n_type & N_TYPE) != N_UNDF && GET_BIT(g_meta.options, OPT_u))
		|| ((elem->n_type & N_TYPE) == N_UNDF && GET_BIT(g_meta.options, OPT_U)))
		return;
	if (SWAP32(g_meta.swap, elem->n_value) || (GET_BIT(g_meta.options, OPT_a) && (elem->n_type & N_STAB)))
		ft_printf("%08x ", SWAP32(g_meta.swap, elem->n_value));
	else
		ft_printf("%8s ", "");
	if (elem->n_type & N_STAB)
		ft_printf("%s %02x %04x %5s %s\n", get_symbol32(buf, elem, SYMBOL_CHAR)
			 			, 	elem->n_sect
						,	SWAP16(g_meta.swap, elem->n_desc)
						, get_type_stab(elem->n_type)
						, g_stringtab + SWAP32(g_meta.swap, elem->n_un.n_strx));
	else
		ft_printf("%s %s\n", get_symbol32(buf, elem, SYMBOL_CHAR)
					, g_stringtab + SWAP32(g_meta.swap, elem->n_un.n_strx));
}