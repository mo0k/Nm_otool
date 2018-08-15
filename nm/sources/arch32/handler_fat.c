/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_fat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 18:32:41 by mo0k              #+#    #+#             */
/*   Updated: 2018/08/15 11:23:04 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arch32.h>
#include <math.h>

# define NBR_ARCH 5
typedef struct	s_archtype
{
	unsigned int	cputype;
	char		*string;
}				t_archtype;

static char 	*get_archtype_str(unsigned int cputype)
{
	int					i;
	static t_archtype	tab[NBR_ARCH] = 
	{
		{CPU_TYPE_X86_64, "x86_64"},
		{CPU_TYPE_I386, "i386"},
		{CPU_TYPE_POWERPC, "ppc"},
		{CPU_TYPE_POWERPC64, "ppc64"},
		{CPU_TYPE_X86, "x86"}
	};

	i = 0;
	while (i < NBR_ARCH)
	{
		if (tab[i].cputype == cputype)
			return (tab[i].string);
		i++;
	}
	return ("unknown");
}

static void		display_all(uint32_t index, t_meta *meta, void *ptr)
{
	uint8_t 			swap;
	struct fat_arch		*fat_arch;
	struct fat_header 	*fat_header;
	char				buf[128];

	fat_header = (struct fat_header*)ptr;
	fat_arch = (struct fat_arch*)(fat_header + 1);
	swap = meta->swap;
	while (index < SWAP32(swap, fat_header->nfat_arch))
	{
		buf[0] = 0;
		if (SWAP32(swap, fat_header->nfat_arch) > 1)
		{
			ft_strcpy(buf, " (for architecture ");
			ft_strcat(buf, get_archtype_str(SWAP32(swap, fat_arch[index].cputype)));
			ft_strcat(buf, ")");	
		}
		ft_strcat(buf, ":");
		if (SWAP32(swap, fat_header->nfat_arch) > 1)
			ft_printf("\n%s%s\n", meta->filename, buf);
		else
			ft_printf("%s%s\n", meta->filename, buf);
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
