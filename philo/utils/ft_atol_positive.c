#include "philo.h"

long	ft_atol_positive(const char *nptr)
{
	long long	res;

	res = 0;
	if (!nptr)
		return (-1);
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		if (res > INT_MAX)
			return (-1);
		nptr++;
	}
	return ((long) res);
}

int	ft_isspace(char s)
{
	unsigned char c = (unsigned char) s;

	if (!s)
		return (1);
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
