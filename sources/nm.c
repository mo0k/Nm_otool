/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 10:11:01 by mo0k              #+#    #+#             */
/*   Updated: 2018/03/18 15:49:41 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

int							usage()
{
	dprintf(2, "./nm -%s binary_file\n", OPTIONS);
	return (1);
}



/* */



void 						nm(void *ptr, t_meta *meta)
{
	if (!ptr || !meta || !meta->printfunc)
		return ;
	if (*(unsigned int*)ptr == MH_MAGIC_64)
	{
		//printf("binary 64 bits\n");
		handler64(ptr, meta);
	}
	else if (*(unsigned int*)ptr == MH_MAGIC)
		printf("binay 32 bits\n");
}





int 						load_file(void **ptr, size_t *ptr_size, char *filepath)
{
	int						fd;
	struct stat				buff;

	printf("filepath:%s\n", filepath);
	if ((fd = open(filepath, O_RDONLY)) < 0)
	{
		perror(ERROR_STR);
		return (ERROR_OPEN);	
	}
	if (fstat(fd, &buff) == -1)
	{
		perror(ERROR_STR);
		return (ERROR_FSTAT);
	}
	*ptr_size = buff.st_size;
	if ((*ptr = mmap(0, *ptr_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		perror(ERROR_STR);
		return (ERROR_MMAP);
	}
	return (0);
}

int							main(int ac, char **av)
{
	uint32_t				error;
	uint32_t 				index;

	g_meta.options = 0xc0000000;
	if (ac < 2)
		return usage();
	if ((error = get_opts(ac - 1, av + 1, &index ,&g_meta.options)))
		return (print_error(error));
	g_meta.sortfunc = get_sortfunc(g_meta.options);
	g_meta.printfunc = get_printfunc(g_meta.options);
	if ((error = load_file(&g_meta.ptr, &g_meta.ptr_size, av[index])))
		return (error);
	nm(g_meta.ptr, &g_meta);
	//mummap
	return (0);
}

