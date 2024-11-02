#include "inc/game.h"

int	main(int ac, char **av)
{
	int	len;

	if (ac == 2)
	{
		len = ft_strlen(av[1]);
		if (len > 3 && valid_name(av[1], len))
			init_map(av[1]);
		else
			error_message(2);
	}
	else
		error_message(1);
	return (0);
}
