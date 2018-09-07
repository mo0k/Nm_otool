/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:39:20 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/06 00:23:28 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arch32.h"

static void 		*get_addr_sect32(t_seg32 *seg32, char *sectname)
{
	t_sect32 			*sect32;
	unsigned int 		i;

	i = 0;
	if (!seg32)
		return (0);
	sect32 = (t_sect32*)(seg32 + 1);
	if (CHK_VAL(g_meta, (void*)(seg32 + 1)))
		corrupted();
	while (i < SWAP32(g_meta->swap, seg32->nsects))
	{
		if (CHK_VAL(g_meta, (void*)(sect32 + 1)))
			corrupted();
		P_DEBUG_VARGS("%s\n", sect32->sectname);
		if (!ft_strcmp(sect32->sectname, sectname))
			return (sect32);
		++sect32;
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
		else if (lc->cmd == LC_SEGMENT)
		{
			if (!ft_strcmp((char*)lc+8, "__TEXT") && GET_BIT(meta->options, OPT_t)
					&& !meta->sect_text)
				meta->sect_text = get_addr_sect32((t_seg32*)lc, "__text");
			else if (!ft_strcmp((char*)lc+8, "__DATA")
					&& GET_BIT(meta->options, OPT_d)
					&& !meta->sect_data)
				meta->sect_data = get_addr_sect32((t_seg32*)lc, "__data");
		}
		lc = (void*)lc + SWAP32(meta->swap, lc->cmdsize);
		++count;
	}
}

void				handler32(void *ptr, t_meta *meta)
{
	t_header32			*header;
	t_lc				*lc;

	if (!ptr)
		return ;
	header = (t_header32*)ptr;
	lc = (t_lc*)(header + 1);
	if (CHK_VAL(meta, (void*)(lc + 1)))
		corrupted();
	meta->swap = (header->magic == MH_CIGAM) ? 1 : 0;
	loop_lc(meta, SWAP32(meta->swap, header->ncmds), lc);
	display32(meta, ptr);
}
