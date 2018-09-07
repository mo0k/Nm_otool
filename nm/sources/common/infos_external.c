/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos_external.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 22:10:40 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/07 11:47:15 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

char *get_infos_external64(struct nlist_64 *nlist, char *buf)
{
	if (SWAP16(g_meta->swap, nlist->n_desc) == REFERENCED_DYNAMICALLY
		&& (nlist->n_type & N_EXT))
		ft_strcpy(buf, "[referenced dynamically] external");
	else if ((nlist->n_type & N_PEXT))
		ft_strcat(buf, "non-external (was a private external)");
	else if ((nlist->n_type & N_EXT))
		ft_strcat(buf, "external");
	else if (!(nlist->n_type & N_EXT))
		ft_strcat(buf, "non-external");
	return (buf);
}

char *get_infos_external32(struct nlist *nlist, char *buf)
{
	if (SWAP16(g_meta->swap, nlist->n_desc) == REFERENCED_DYNAMICALLY
		&& (nlist->n_type & N_EXT))
		ft_strcpy(buf, "[referenced dynamically] external");
	else if ((nlist->n_type & N_PEXT))
		ft_strcat(buf, "non-external (was a private external)");
	else if ((nlist->n_type & N_EXT))
		ft_strcat(buf, "external");
	else if (!(nlist->n_type & N_EXT))
		ft_strcat(buf, "non-external");
	return (buf);
}
