/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos_external.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 22:10:40 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/09 09:58:16 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

char *get_infos_external64(struct nlist_64 *nlist, char *buf)
{
	if (SWAP16(g_meta.swap, nlist->n_desc) == REFERENCED_DYNAMICALLY && (nlist->n_type \
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

char *get_infos_external32(struct nlist *nlist, char *buf)
{
	if (SWAP16(g_meta.swap, nlist->n_desc) == REFERENCED_DYNAMICALLY && (nlist->n_type \
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