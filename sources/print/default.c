/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:47 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 15:36:19 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						prinf_default(t_list *list)
{
	//printf("start prinf_default\n");
	struct nlist_64*			elem;
	char 		buf[85];
	//char 		*ptr;
	if (!list)
		return ;
	elem = list->content;
	if (elem->n_type & N_STAB)
		return;
	if (elem->n_value)
		printf("%016llx ", elem->n_value);
	else
		printf("%16s ", "");
	printf("%s %s\n", get_symbol64(buf, elem, CHAR)
					, g_stringtab + elem->n_un.n_strx);
}