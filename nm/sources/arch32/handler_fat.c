/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_fat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 18:32:41 by mo0k              #+#    #+#             */
/*   Updated: 2018/05/01 14:45:07 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arch32.h>
#include <math.h>

static void		display_all(uint32_t index, t_meta *meta, void *ptr)
{
	int swap;
	struct fat_arch		*fat_arch;
	struct fat_header 	*fat_header;

	fat_header = (struct fat_header*)ptr;
	fat_arch = (struct fat_arch*)(fat_header + 1);
	swap = meta->swap;
	while (index < SWAP32(swap, fat_header->nfat_arch))
	{
		nm(ptr + SWAP32(swap, fat_arch[index].offset), meta);
		++index;
	}
}

void		handler_fat32(void *ptr, t_meta *meta)
{
	struct fat_header 	*fat_header;
	struct fat_arch		*fat_arch;
	uint32_t i = -1;

	if (!ptr || !meta)
		return ;
	fat_header = (struct fat_header*)ptr;
	
	meta->swap = (fat_header->magic == FAT_CIGAM) ? 1 : 0;
	//printf("meta->swap:%d\n", meta->swap);

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
	if (SWAP32(meta->swap, fat_arch[i].cputype) == CPU_TYPE_X86_64)
		return (nm(ptr + SWAP32(meta->swap, fat_arch[i].offset), meta));
	else
		return (display_all(i, meta, ptr));
}