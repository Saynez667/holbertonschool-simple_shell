#include "shell.h"

/**
 * _getenv - Retrieves the value of an environment variable
 * @name: Name of the environment variable
 * @environ: Environment variables array
 *
 * Return: Pointer to variable value, or NULL if not found
 */
char *_getenv(const char *name, char **environ)
{
	int i, name_len;
	char *env_var;

	if (name == NULL || environ == NULL)
		return (NULL);

	name_len = _strlen(name);
	if (name_len == 0)
		return (NULL);

	for (i = 0; environ[i] != NULL; i++)
	{
		env_var = environ[i];
		if (strncmp(env_var, name, name_len) == 0 &&
			env_var[name_len] == '=')
		{
			return (env_var + name_len + 1);
		}
	}

	return (NULL);
}