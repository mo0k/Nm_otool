/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_fat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 18:32:41 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/09 23:50:10 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arch32.h"
#include <math.h>

void		handler_fat32(void *ptr, t_meta *meta)
{
	struct fat_header 	*fat_header;
	struct fat_arch		*fat_arch;
	uint32_t i = -1;

	if (!ptr || !meta)
		return ;
	fat_header = (struct fat_header*)ptr;
	meta->swap = (fat_header->magic == FAT_CIGAM) ? 1 : 0;
	fat_arch = (struct fat_arch*)(fat_header + 1);
	while (++i < SWAP32(meta->swap, fat_header->nfat_arch))
	{
		if (CHK_VAL(ptr, ptr + meta->size, (void*)fat_arch + i + 1)
			|| CHK_VAL(ptr, ptr + meta->size, ptr + SWAP32(meta->swap, fat_arch[i].offset)))	
			corrupted("handler_fat32");
		if (SWAP32(meta->swap, fat_arch[i].cputype) == CPU_TYPE_X86_64)
			break;

	}
	if (i == SWAP32(meta->swap, fat_header->nfat_arch))
		i = 0;
	otool(ptr + SWAP32(meta->swap, fat_arch[i].offset), meta);
}