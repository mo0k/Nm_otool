/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:39:20 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/05 23:57:13 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arch64.h"

void 		*get_addr_sect64(t_seg64 *seg64, char *sectname)
{
	t_sect64 	*sect64;
	unsigned int 		i;

	i = 0;
	if (!seg64)
		return (0);
	sect64 = (t_sect64*)(seg64 + 1);
	if (CHK_VAL(g_meta, (void*)(seg64 + 1)))
		corrupted();
	while (i < SWAP32(g_meta->swap, seg64->nsects))
	{
		if (CHK_VAL(g_meta, (void*)(sect64 + 1)))
			corrupted();
		P_DEBUG_VARGS("%s\n", sect64->sectname);
		if (!ft_strcmp(sect64->sectname, sectname))
			return (sect64);
		++sect64;
		++i;
	}
	return (0);
}

static void			loop_lc(t_meta *meta, uint32_t ncmds, t_lc *lc)
{
	uint32_t			count;

	count = 0;
	while (count < ncmds &&
			(GET_BIT(meta->options, OPT_d) || GET_BIT(meta->options, OPT_t)))
	{
		if (CHK_VAL(meta, (void*)lc)
			|| CHK_VAL(meta, (void*)lc + SWAP32(meta->swap, lc->cmdsize)))
			corrupted();
		else if (lc->cmd == LC_SEGMENT_64)
		{
			if (!ft_strcmp((char*)lc+8, "__TEXT") && GET_BIT(meta->options, OPT_t)
				&& !meta->sect_text)
				meta->sect_text = get_addr_sect64((t_seg64*)lc, "__text");
			else if (!ft_strcmp((char*)lc+8, "__DATA") && GET_BIT(meta->options, OPT_d)
				&& !meta->sect_data)
				meta->sect_data = get_addr_sect64((t_seg64*)lc, "__data");
		}
		lc = (void*)lc + SWAP32(meta->swap, lc->cmdsize);
		++count;
	}
}

void		handler64(void *ptr, t_meta *meta)
{
	t_header64	*header;
	t_lc		*lc;
	uint32_t	count;

	if (!ptr)
		return ;
	count = 0;
	header = (t_header64*)ptr;
	if (CHK_VAL(meta, (void*)header))
		corrupted();
	lc = ptr + sizeof(t_header64);
	meta->swap = (header->magic == MH_CIGAM_64) ? 1 : 0;
	loop_lc(meta, SWAP32(meta->swap, header->ncmds), lc);
	display64(meta, ptr);
}