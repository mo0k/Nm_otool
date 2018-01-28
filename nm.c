/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 10:11:01 by mo0k              #+#    #+#             */
/*   Updated: 2018/01/28 21:46:02 by mo0k             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int							usage()
{
	dprintf(2, "./nm -%s binary_file\n", OPTIONS);
	return (1);
}

void						print_just_symbol_names(t_list *list)
{
	//uint8_t					type;

	if (!list)
		return ;
	printf("%s\n", g_stringtab + ((struct nlist_64*)(list->content))->n_un.n_strx);
	/*printf("nlist[i].n_un.n_strx:%d => 0x%x => %s\n", nlist[i].n_un.n_strx, nlist[i].n_un.n_strx, stringtab + nlist[i].n_un.n_strx);
		printf("nlist[i].n_type:%d => 0x%02x\n", nlist[i].n_type, nlist[i].n_type);
		printf("nlist[i].n_type & N_STAB : 0x%02x\n", nlist[i].n_type & N_STAB);
		if (nlist[i].n_type & N_STAB)
		{
			printf("SYmbol debugging\n");
		}
		printf("nlist[i].n_type & N_TYPE : 0x%02x\n", nlist[i].n_type & N_TYPE);
		type = nlist[i].n_type & N_TYPE;	
		if (type == N_UNDF)
			printf("UNDEFINED NO_SECT\n");
		else if (type == N_ABS)
			printf("ABSOLUTE NO_SECT\n");
		else if (type == N_SECT)
			printf("defined in section number n_sect\n");
		else if (type == N_PBUD)
			printf("prebound undefined (defined in a dylib)\n");
		else if (type == N_INDR)
			printf("indirect\n");
		else
			printf("ERROR\n");
		printf("nlist[i].n_sect:%d => 0x%02x\n", nlist[i].n_sect, nlist[i].n_sect);
		(nlist[i].n_sect == NO_SECT) ? printf("NO SECT\n") : printf("MAX SECT\n");  
		printf("nlist[i].n_desc:%d => 0x%02x\n", nlist[i].n_desc, nlist[i].n_desc);
		printf("nlist[i].n_value:%lld => %016llx\n\n", nlist[i].n_value, nlist[i].n_value);
		*/
}

void						print_hexa(t_list *list)
{
	//uint8_t					type;
	struct nlist_64*			elem;
	if (!list)
		return ;
	elem = list->content;
	printf("%016llx %02x %02x %04x %08x %s\n", 
									elem->n_value,
									elem->n_type,
									elem->n_sect,
									elem->n_desc,
									elem->n_un.n_strx,
									g_stringtab + elem->n_un.n_strx);
}
void						handler_systab(void* lc, void *ptr, t_meta *meta)
{
	struct symtab_command	*stab_command;
	struct nlist_64			*nlist;
	t_list					*list;
	uint32_t				i;

	if (!ptr)
		return ;
	i = -1;
	stab_command = (struct symtab_command*)lc;
	/*
	printf("cmd:0x%x\n", stab_command->cmd);
	printf("cmdsize:%d\n", stab_command->cmdsize);
	printf("symoff:%d\n", stab_command->symoff);
	printf("nsyms:%d\n", stab_command->nsyms);
	printf("stroff:%d\n", stab_command->stroff);
	printf("strsize:%d\n", stab_command->strsize);
	*/
	nlist = ptr + stab_command->symoff;
	g_stringtab = ptr + stab_command->stroff;
	list = 0;
	while (++i < stab_command->nsyms)
		ft_lstadd_end(&list, ft_lstnew(&nlist[i], sizeof(struct nlist_64)));
	sort(&list, &meta->options, meta->sortfunc);
	ft_lstiter(list, meta->printfunc);
	//delete list chaine nlist
}

void						handler_64(void *ptr, t_meta *meta)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	uint32_t				count;

	if (!ptr)
		return ;
	count = 0;
	header = (struct mach_header_64*)ptr;
	lc = ptr + sizeof(struct mach_header_64);
	while (count < header->ncmds)
	{
		/*
		printf("lc->cmd:0x%x\n", lc->cmd);
		printf("lc->cmdsize:%x\n", lc->cmdsize);*/
		if (lc->cmd == LC_SYMTAB)
		{
			handler_systab((void*)lc, ptr, meta);
			break ;
		}
		lc = (void*)lc + lc->cmdsize;
		++count;
	}

}
void 						nm(void *ptr, t_meta *meta)
{
	if (!ptr || !meta || !meta->printfunc)
		return ;
	if (*(unsigned int*)ptr == MH_MAGIC_64)
	{
		//printf("binary 64 bits\n");
		handler_64(ptr, meta);
	}
	else if (*(unsigned int*)ptr == MH_MAGIC)
		printf("binay 32 bits\n");
}



t_pfunc						get_printfunc(t_opts *options)
{
	if (!options)
		return (NULL);
	if (options->hexa)
		return (&print_hexa);
	else if (options->just_symbol_names)
		return (&print_just_symbol_names);
	else
		//default a changer
		return (&print_just_symbol_names);
}

t_sfunc						get_sortfunc(t_opts *options)
{
	if (!options || options->nosort)
		return (NULL);
	if (options->ascii)
		return (&sort_ascii);
	else
		return (NULL);
}

int 						input(int ac, char **av, t_opts *options)
{
	int 					count;

	if (!av || !*av)
		return (ERROR_ARGS);
	count = 0;
	while (count < ac)
	{
		if (av[count][0] == '-')
		{
			if (set_options(options, &av[count][1]) == ERROR_ARGS)
			{
				printf("NO VALID OPTION\n");
				return (ERROR_ARGS);
			}
		}
		else
		{
			printf("return index fisrt filepath\n");	
			return (count + 1);
		}
		++count;
	}
	return (ERROR_ARGS);
}

int 						load_file(void **ptr, size_t *ptr_size, char *filepath)
{
	int						fd;
	struct stat				buff;

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
	t_meta					meta;
	uint16_t				error;
	int 					index;

	init_options(&meta.options);
	if (ac < 2 ||
		(index = input(ac - 1, av + 1, &meta.options)) == ERROR_ARGS)
		return (usage());
	//check options
	//define printfunc & sortfunc
	meta.sortfunc = get_sortfunc(&meta.options);
	meta.printfunc = get_printfunc(&meta.options);
	if ((error = load_file(&meta.ptr, &meta.ptr_size, av[index])))
		return (error);
	nm(meta.ptr, &meta);
	//mummap
	return (0);
}

