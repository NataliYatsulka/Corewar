#include "vm.h"

unsigned int		is_valid_num(char *arg, char flag)
{
	int		num;

	num = ft_atoi(arg);
	if (num <= 0)
		ft_error("Bad numb in input line\n");
	if (!((flag == 'n' && num <= MAX_PLAYERS) || flag == 'd'))
		ft_error("Bad numb of players in input line\n");
	return((unsigned int)num);
}

int					is_flag(char **args, size_t *i, t_general *gen)
{
	unsigned int	j;

	j = 0;
	if (args[*(i)][0] == '-')
	{
		if (ft_strequ(args[*i], "-v"))
		{
			ft_printf("switch on vizualization\n");
		}
		else if (ft_strequ(args[*i], "-d"))
		{
			if (!args[*i + 1])
				ft_error("Not enough argumets\n");
			gen->dump = is_valid_num(args[++(*i)], 'd');
			ft_printf("dumps %d cycles\n", gen->dump); // test
		}
		else if (ft_strequ(args[*i], "-n"))
		{
			if (!args[*i + 1] || !args[*i + 2])
				ft_error("Not enough argumets\n");
			if (gen->champ_num == MAX_PLAYERS)
				ft_error("To many champions\n");
			j = is_valid_num(args[++(*i)], 'n');
			(gen->n_flag[j]) ? ft_error("Wrong num of player\n") : 0;
			if (is_champ(args[++(*i)]))
				gen->n_flag[j] = *i;
			else
				ft_error("Wrong type of file (-n flag)\n");
			gen->champ_num++;
			ft_printf("adds num to player\n");	// test
		}
		else
			ft_error("Invalid flag\n"); // proper error message
		return (1);
	}
	return (0);
}

int 				is_champ(char *arg)
{
	int		k;

	k = ft_strlen(arg);
	if (arg[k - 4] == '.' && arg[k - 3] == 'c' && arg[k - 2] == 'o'
		&& arg[k - 1] == 'r' && (arg[k] == '\0' || arg[k] == '\n'))
		return (1);
	else
		return (0);
}

int		validate_champ(unsigned char *line, int i)
{
 	unsigned int	magic;

	magic = (unsigned int)line[0];
	magic = magic << 8;
	magic |= (unsigned int)line[1];
	magic = magic << 8;
	magic |= (unsigned int)line[2];
	magic = magic << 8;
	magic |= (unsigned int)line[3];
	if (!(magic == COREWAR_EXEC_MAGIC))
	{
		ft_error("Wrong magic number\n");
//		return (0);
	}
	magic = (unsigned int)line[136];
	magic = magic << 8;
	magic |= (unsigned int)line[137];
	magic = magic << 8;
	magic |= (unsigned int)line[138];
	magic = magic << 8;
	magic |= (unsigned int)line[139];
	if (!(magic == i - PROG_HEADER_LENGTH) || magic > CHAMP_MAX_SIZE)
	{
		ft_error("Program size mismatch\n");
//		return (0);
	}
	return (1);
}

int 	is_valid_champ(char *arg, t_general *gen, size_t j)
{
	int 	fd;
	ssize_t len;

//	ft_printf("header: %u\n", PROG_HEADER_LENGTH); // test
//	ft_printf("FILE_MAX_LENGTH: %u\n", FILE_MAX_LENGTH); // test
	gen->line = ft_memalloc(FILE_MAX_LENGTH);
	fd = open(arg, O_RDONLY);
	len = read(fd, gen->line, FILE_MAX_LENGTH);
//	ft_printf("len: %u\n", len); // test
	if (fd == -1 || len == -1)
		ft_error("can't read the file\n");
	if (len < PROG_HEADER_LENGTH)
		ft_error("the size of champion is to small\n");
	if (read(fd, NULL, 1))
		ft_error("the size of champion is to big\n");
	if (validate_champ(gen->line, len))
	{
		write_player(gen, j);
		free(gen->line);
		gen->line = NULL;
		ft_printf("valid champion\n"); // test
	}
	return (1);
}

void		write_player(t_general *gen, size_t j)
{
	gen->players[j] = (t_player *)malloc(sizeof(t_player));
}

void				read_players(char **av, t_general *gen)
{
	size_t		j;
	size_t		i;

	j = 0;
	gen->players = (t_player **)malloc(sizeof(t_player *) * gen->champ_num);
	while (j < gen->champ_num)
	{
		i = gen->n_flag[j + 1];
		if (is_valid_champ(av[i], gen, j))
		{
			gen->players[j]->num = (j + 1) * -1;
			j++;
		}
	}
}