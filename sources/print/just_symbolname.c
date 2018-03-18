/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_symbol_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:31:40 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 15:34:21 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void						print_just_symbol_names(t_list *list)
{
	if (!list)
		return ;
	printf("%s\n", g_stringtab + ((struct nlist_64*)(list->content))->n_un.n_strx);
}
