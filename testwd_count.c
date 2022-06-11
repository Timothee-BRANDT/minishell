#include <stdio.h>

int	ft_isspace(int c)
{
	if (((c == '\n') || (c == '\v') || (c == '\t')) \
	|| ((c == '\r') || (c == '\f') || (c == ' ')))
		return (1);
	return (0);
}

int	get_word(char	*str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str && *str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == 39)
		{
			j = *str;
			str++;
			while (*str != j)
				str++;
			i++;
			str++;
		}
		else if (*str == 34)
		{
			j = *str;
			str++;
			while (*str != j)
				str++;
			i++;
			str++;
		}
		else if ((*str != ' ' && *str != 34 && *str != 39 && *str != '\0'))
		{
			i++;
			while (*str != ' ' && *str != 34 && *str != 39 && *str != '\0')
				str++;
		}
		str++;
	}
	return (i);
}