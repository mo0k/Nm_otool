/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_fat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 18:32:41 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/25 22:10:44 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <handler.h>
#include <math.h>

void		handler_fat32(void *ptr, t_meta *meta)
{
	struct fat_header 	*fat_header;
	struct fat_arch		*fat_arch;
	uint32_t i = 0;

	if (!ptr || !meta)
		return ;
	fat_header = (struct fat_header*)ptr;
	g_meta.swap = (fat_header->magic == FAT_CIGAM) ? 1 : 0;
	fat_arch = (struct fat_arch*)(fat_header + 1);
	while (i < SWAP(g_meta.swap, fat_header->nfat_arch))
	{
		ft_printf("offset:%d,size:%d,align:%d\n", SWAP(g_meta.swap, fat_arch[i].offset)
											, SWAP(g_meta.swap, fat_arch[i].size)
											, SWAP(g_meta.swap, fat_arch[i].align));
		printf("0x%08x\n", *(unsigned int*)(ptr + SWAP(g_meta.swap, fat_arch[i].offset)));
		nm(ptr + SWAP(g_meta.swap, fat_arch[i].offset), meta);
		i++; 
	}
	//ft_printf("nombre de fat struct:%2d\n", SWAP(g_meta.swap, fat_header->nfat_arch));
	//fat_arch = (struct fat_arch*)(fat_header + 1);
	//ft_printf("offset:%d,size:%d,align:%d\n", SWAP(g_meta.swap, fat_arch->offset)
	//										, SWAP(g_meta.swap, fat_arch->size)
	//										, SWAP(g_meta.swap, fat_arch->align)); 
}