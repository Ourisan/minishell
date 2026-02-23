#include "libft.h"

long	ft_atol(const char *str)
{
	int		i;
	long	res;
	long	sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		res = 10 * res + (str[i] - '0');
		i++;
	}
	return (res * sign);
}
