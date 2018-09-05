/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_fat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 18:32:41 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/05 23:57:33 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arch32.h"
#include <math.h>

/*
** ADD VERIF MEMERY
**
*/

static void		display_all(uint32_t index, t_meta *meta, void *ptr)
{
	uint8_t				swap;
	struct fat_arch		*fat_arch;
	struct fat_header 	*fat_header;
	//char				buf[128];

	fat_header = (struct fat_header*)ptr;
	fat_arch = (struct fat_arch*)(fat_header + 1);
	swap = meta->swap;
	while (index < SWAP32(swap, fat_header->nfat_arch))
	{
		otool(ptr + SWAP32(swap, fat_arch[index].offset), meta);
		++index;
	}
}
void			handler_fat32(void *ptr, t_meta *meta)
{
	struct fat_header 	*fat_header;
	struct fat_arch		*fat_arch;
	uint32_t			i;

	if (!ptr || !meta)
		return ;
	fat_header = (struct fat_header*)ptr;
	i = -1;
	meta->swap = (fat_header->magic == FAT_CIGAM) ? 1 : 0;
	fat_arch = (struct fat_arch*)(fat_header + 1);
	while (++i < SWAP32(meta->swap, fat_header->nfat_arch))
	{
		if (CHK_VAL(meta, (void*)fat_arch + i + 1)
			|| CHK_VAL(meta, ptr + SWAP32(meta->swap, fat_arch[i].offset)))	
			corrupted();
		if (SWAP32(meta->swap, fat_arch[i].cputype) == CPU_TYPE_X86_64)
			break;
	}
	if (i == SWAP32(meta->swap, fat_header->nfat_arch))
		i = 0;
	if (SWAP32(meta->swap, fat_arch[i].cputype) == CPU_TYPE_X86_64)
		return (otool(ptr + SWAP32(meta->swap, fat_arch[i].offset), meta));
	else
		return (display_all(i, meta, ptr));
}
