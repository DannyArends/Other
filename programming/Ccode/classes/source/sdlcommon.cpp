#include "sdlcommon.h"

#ifdef WIN32

int APIENTRY WinMain (HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow){
	char **argv= NULL;
	int argc;
  char   *win_command_line;
	win_command_line = GetCommandLine();
	argc = makeargv(win_command_line,(const char*)" \t\n", &argv);
	main(argc, (char **) argv);
	freemakeargv(argv);  
}

#endif

// splits a char* into a char ** based on the delimiters
int makeargv(char *s,const char *delimiters, char ***argvp){
	int i, numtokens;
	char *snew, *t;

	if ((s == NULL) || (delimiters == NULL) || (argvp == NULL))
		return -1;

	*argvp = NULL;
	snew = s + strspn(s, delimiters);
	if ((t = (char*)malloc(strlen(snew) + 1)) == NULL)
		return -1;
	strcpy(t, snew);	// It's fine that this isn't strncpy, since t is sizeof(snew) + 1.

	numtokens = 0;
	if (strtok(t, delimiters) != NULL)
		for (numtokens = 1; strtok(NULL, delimiters) != NULL; numtokens++);

	if ((*argvp = (char**)malloc((numtokens + 1)*sizeof(char *))) == NULL){
		free(t);
		return -1;
	}
	if (numtokens == 0)
		free(t);
	else{
		strcpy(t, snew);
		**argvp = strtok(t, delimiters);
		for (i = 1; i < numtokens; i++)
			*((*argvp) + i) = strtok(NULL, delimiters);
	}
	*((*argvp) + numtokens) = NULL;
	return numtokens;
}

//frees the char** created by makeargv
void freemakeargv(char **argv){
	if (argv == NULL)
		return;
	if (*argv != NULL)
		free(*argv);
	free(argv);
}
