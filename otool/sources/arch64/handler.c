/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:39:20 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/04 23:20:55 by mo0k             ###   ########.fr       */
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
		corrupted("handler64 5");
	while (i < SWAP32(g_meta->swap, seg64->nsects))
	{
		if (CHK_VAL(g_meta, (void*)(sect64 + 1)))
			corrupted("handler64 6");
		P_DEBUG_VARGS("%s\n", sect64->sectname);
		if (!ft_strcmp(sect64->sectname, sectname))
			return (sect64);
		++sect64;
		++i;
	}
	return (0);
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
		corrupted("handler64 1");
	lc = ptr + sizeof(t_header64);
	meta->swap = (header->magic == MH_CIGAM_64) ? 1 : 0;
	while (count < SWAP32(meta->swap, header->ncmds)
			&& (GET_BIT(meta->options, OPT_d) || GET_BIT(meta->options, OPT_t)))
	{
		if (CHK_VAL(meta, (void*)lc)
			|| CHK_VAL(meta, (void*)lc + SWAP32(meta->swap, lc->cmdsize)))
			corrupted("handler64 2");
		else if (lc->cmd == LC_SEGMENT_64)
		{
			if (!ft_strcmp((char*)lc+8, "__TEXT") && GET_BIT(meta->options, OPT_t)
				&& !meta->sect_text)
			{
				P_DEBUG("go find section _text in _TEXT\n");
				meta->sect_text = get_addr_sect64((t_seg64*)lc, "__text");
			}
			else if (!ft_strcmp((char*)lc+8, "__DATA") && GET_BIT(meta->options, OPT_d)
				&& !meta->sect_data)
			{
				P_DEBUG("go find section _data in _DATA\n");
				meta->sect_data = get_addr_sect64((t_seg64*)lc, "__data");
				//ft_printf("meta->sect_data:%p\n", meta->sect_data);
			}
		}
		lc = (void*)lc + SWAP32(meta->swap, lc->cmdsize);
		++count;
	}
	display64(meta, ptr);
}