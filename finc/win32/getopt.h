#ifndef _GETOPT_H_
#define _GETOPT_H_

extern char *optarg;
extern int optind;
extern int opterr;
extern int optopt;

int getopt(int argc, char **argv, const char *optstring);

#endif	/* _GETOPT_H_ */
