#include "vm.h"

void	dump_map(unsigned char *line)
{
	size_t	i;
	size_t	k;
	size_t	j;

	k = 0;
	j = 0;
	while (k < MEM_SIZE)
	{
		i = 0;
		ft_printf("%-5d: ", (j++ * 64));
		while (i++ < 64)
		{
			ft_printf("%.2hhx ", line[k++]);
		}
		ft_printf("\n");
	}
}

void 	write_to_map(t_general *gen)
{
	size_t		i;
	size_t		j;
	size_t		step;
	void		*ptr;
	t_process	*head;

	i = 0;
	j = 0;
//	dump_map(gen->field); //test
	step = (size_t)(MEM_SIZE) / gen->champ_num;
	while (j < gen->champ_num)
	{
		head = (t_process *)ft_memalloc(sizeof(t_process));
		ft_printf("write_to_map 1\n"); // test
		(gen->process->reg)[1] = (gen->players)[j]->num;
		ft_printf("write_to_map 1\n"); // test
		head->next = gen->process;
		gen->process = head;
		ptr = gen->players[j]->opcode;
		ft_memcpy(gen->field + i, ptr, gen->players[j]->size);
		j++;
		i += step;
	}
	dump_map(gen->field); //test
}