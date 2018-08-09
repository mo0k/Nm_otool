/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 10:11:01 by mo0k              #+#    #+#             */
/*   Updated: 2018/07/24 20:03:59 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

int							usage()
{
	dprintf(2, "./nm -%s binary_file\n", OPTIONS);
	return (1);
}


static int					is_simplebin(void *ptr)
{
	return (*(unsigned int*)ptr == MH_MAGIC
			|| *(unsigned int*)ptr == MH_CIGAM
			|| *(unsigned int*)ptr == MH_MAGIC_64
			|| *(unsigned int*)ptr == MH_CIGAM_64);
}

void 						nm(void *ptr, t_meta *meta)
{
	P_DEBUG_VARGS("Launch function nm ; ptr(%p)\n", ptr);
	if (!ptr || !meta)
		return ;
	
	if (*(unsigned int*)ptr == MH_MAGIC_64 || *(unsigned int*)ptr == MH_CIGAM_64)
	{
		P_DEBUG("binary 64 bits\n");
		meta->sortfunc = get_sortfunc(meta->options, ARCH64);
		meta->printfunc = get_printfunc_arch64(meta->options);
		handler64(ptr, meta);
	}
	else if (*(unsigned int*)ptr == MH_MAGIC || *(unsigned int*)ptr == MH_CIGAM)
	{
		P_DEBUG("binay 32 bits\n");
		P_DEBUG_VARGS("magic number:0x%08x\n", *(unsigned int*)ptr);
		meta->printfunc = get_printfunc_arch32(meta->options);
		meta->sortfunc = get_sortfunc(meta->options, ARCH32);
		handler32(ptr, meta);
	}
	else if (*(unsigned int*)ptr == FAT_MAGIC || *(unsigned int*)ptr == FAT_CIGAM)
	{
		P_DEBUG("FAT 32\n");
		P_DEBUG_VARGS("magic number:0x%08x\n", *(unsigned int*)ptr);
		handler_fat32(ptr, meta);
	}
	else if (*(unsigned int*)ptr == FAT_MAGIC_64 || *(unsigned int*)ptr == FAT_CIGAM_64)
	{
		P_DEBUG("FAT 64\n");
		P_DEBUG_VARGS("magic number:0x%08x\n", *(unsigned int*)ptr);

	}
	else
		ft_dprintf(2, "%s: %s The file was not recognized as a valid object file\n\n", ft_getenv("_"), meta->filename);
}

int							main(int ac, char **av)
{
	uint32_t				error;
	uint32_t 				index;
	uint8_t					multi;
	t_meta					meta;

	g_meta = &meta;
	meta.options = 0xc0000000;
	if (ac < 2)
		return (usage());
	if ((error = get_opts(ac - 1, av + 1, &index ,&meta.options)))
		return (print_error(error));
	multi = (index + 1 < (uint32_t)ac) ? 1 : 0;
	--index;
	while (++index < (uint32_t)ac)
	{
		meta.filename = av[index];
		if ((error = open_file(&meta.ptr, &meta.size, meta.filename, O_RDONLY)))
		{
			open_error(error, meta.filename);
			continue;
		}
		if (multi && is_simplebin(meta.ptr) && !GET_BIT(meta.options, OPT_m))
			ft_printf("\n%s:\n", meta.filename);
		nm(meta.ptr, &meta);
		munmap(meta.ptr, meta.size);
	}
	return (0);
}

