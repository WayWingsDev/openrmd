static int open_console(char *title)
{
	FILE *file;

	if (AllocConsole() == FALSE)
		return -1;

	if (SetConsoleTitle(title) == FALSE)
		return -1;

	if (freopen_s(&file, "CONOUT$", "w", stdout) != 0)
		return -1;

	return 0;
}
