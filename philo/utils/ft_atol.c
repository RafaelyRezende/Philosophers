#include "philo.h"

long	ft_atol(const char *nptr)
{
	long long	res;

	res = 0;
	if (!nptr)
		return (LONG_MAX);
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			return (LONG_MAX);
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		if (res > INT_MAX)
			return (LONG_MAX);
		nptr++;
	}
	return ((long) res);
}
