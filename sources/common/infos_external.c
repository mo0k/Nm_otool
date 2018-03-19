/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos_external.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 22:10:40 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 22:32:10 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

char *get_infos_external(struct nlist_64 *nlist, char *buf)
{
	if (nlist->n_desc == REFERENCED_DYNAMICALLY && (nlist->n_type \
															& N_EXT))
		strcpy(buf, "[referenced dynamically] external");
	else if ((nlist->n_type & N_PEXT))
		strcat(buf, "non-external (was a private external)");
	else if ((nlist->n_type & N_EXT))
		strcat(buf, "external");
	else if (!(nlist->n_type & N_EXT))
		strcat(buf, "non-external");
	return (buf);
}