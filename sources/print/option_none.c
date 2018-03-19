/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_none.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:47 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 21:30:49 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						print_option_none(t_list *list)
{
	struct nlist_64*			elem;
	char 						buf[85];

	if (!list)
		return ;
	elem = list->content;
	if (elem->n_type & N_STAB && !GET_BIT(g_meta.options, OPT_A))
		return;
	if (elem->n_value)
		printf("%016llx ", elem->n_value);
	else
		printf("%16s ", "");
	printf("%s %s\n", get_symbol64(buf, elem, CHAR)
					, g_stringtab + elem->n_un.n_strx);
}