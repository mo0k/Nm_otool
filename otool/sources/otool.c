/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 14:01:21 by mo0k              #+#    #+#             */
/*   Updated: 2018/09/06 00:10:23 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/otool.h"

int		usage()
{
	dprintf(2, "./otool -%s binary_file\n", OPTIONS);
	return (1);
}

void 	otool(void *ptr, t_meta *meta)
{
	P_DEBUG("Launch function otool\n");
	meta->sect_text = 0;
	meta->sect_data = 0;
	if (!ptr || !meta)
		return ;
	if (*(unsigned int*)ptr == MH_MAGIC_64 || *(unsigned int*)ptr == MH_CIGAM_64)
	{
		P_DEBUG("binary 64 bits\n");
		handler64(ptr, meta);
	}
	else if (*(unsigned int*)ptr == MH_MAGIC || *(unsigned int*)ptr == MH_CIGAM)
	{
		P_DEBUG("binay 32 bits\n");
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
		ft_dprintf(1, "%s: is not an object file\n", meta->filename);
}


static int					is_valid_bin(void *ptr)
{
	return (*(unsigned int*)ptr == MH_MAGIC
			|| *(unsigned int*)ptr == MH_CIGAM
			|| *(unsigned int*)ptr == MH_MAGIC_64
			|| *(unsigned int*)ptr == MH_CIGAM_64
			|| *(unsigned int*)ptr == FAT_MAGIC
			|| *(unsigned int*)ptr == FAT_CIGAM
			|| *(unsigned int*)ptr == FAT_MAGIC_64
			|| *(unsigned int*)ptr == FAT_CIGAM_64);
}

int main(int ac, char **av)
{
	uint32_t				error;
	uint32_t 				index;
	t_meta					meta;

	g_meta = &meta;
	g_meta->options = 0x00000000;
	if (ac < 3)
		return usage();
	if ((error = get_opts(ac - 1, av + 1, &index ,&g_meta->options)))
		return (print_error(error));
	--index;
	while (++index < (uint32_t)ac)
	{
		g_meta->filename = av[index];
		if ((error = open_file(&g_meta->ptr, &g_meta->size, g_meta->filename, O_RDONLY)))
		{
			perror(g_meta->filename);
			return (error);
		}
		if ((GET_BIT(g_meta->options, OPT_d) || GET_BIT(g_meta->options, OPT_t))
			&& is_valid_bin(g_meta->ptr))
			ft_printf("%s:\n", g_meta->filename);
		otool(g_meta->ptr, g_meta);
		munmap(g_meta->ptr, g_meta->size);
		//sleep(1);
	}
	//while(1);
	return 0;
}