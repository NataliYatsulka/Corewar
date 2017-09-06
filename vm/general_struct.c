#include "vm.h"

t_general		*gen_init(void)
{
	t_general	*gen;

	gen = (t_general *)malloc(sizeof(t_general));
	if (!gen)
		ft_error("Error in allocation");
	gen->field = ft_memalloc(MEM_SIZE);
//	ft_bzero(gen->field, MEM_SIZE);
	gen->total_cycles = 0;
	gen->current_cycles = 0;
	gen->process = 0;
	gen->cycle_to_die = 0;
	gen->nbr_live = 0;
	gen->dump = -1;
	gen->players = NULL;
	gen->champ_num = 0;
	gen->line = NULL;
//	ft_bzero(gen->n_flag, MAX_PLAYERS + 1);
//	ft_bzero(gen->no_flag, MAX_PLAYERS + 1);
	return(gen);
}
