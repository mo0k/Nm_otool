/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_none32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:47 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/25 03:09:07 by mo0k             ###   ########.fr       */
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
	if (((elem->n_type & N_STAB) && !GET_BIT(g_meta.options, OPT_A))
		|| ((elem->n_type & N_TYPE) != N_UNDF && GET_BIT(g_meta.options, OPT_u))
		|| ((elem->n_type & N_TYPE) == N_UNDF && GET_BIT(g_meta.options, OPT_U)))
		return;
	if (elem->n_value || (GET_BIT(g_meta.options, OPT_A) && (elem->n_type & N_STAB)))
		printf("%08x ", elem->n_value);
	else
		printf("%8s ", "");
	if (elem->n_type & N_STAB)
		printf("%s %02x %04x %5s %s\n", get_symbol32(buf, elem, SYMBOL_CHAR)
			 			, 	elem->n_sect
						,	elem->n_desc
						, get_type_stab(elem->n_type)
						, g_stringtab + elem->n_un.n_strx);
	else
		printf("%s %s\n", get_symbol32(buf, elem, SYMBOL_CHAR)
					, g_stringtab + elem->n_un.n_strx);
}