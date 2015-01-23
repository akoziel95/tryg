#include "points.h"
#include "aproks_trygonom.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
char *usage="Aby poprawnie uruchomić program należy podać argumenty:\n"
"	-p nazwa pliku z danymi źródlowymi\n "
"	-s nazwa pliku z danymi wynikowymi\n "
"	-m opcjonalny stopień wielomianu aproksymującego\n";




int main(int argc, char **argv)
{	
	int opt;
	char *inp = NULL;
	char *outc = NULL;
	char *progname= argv[0];

	points_t points;
	points.n=0;
	int 	res, m = 0;
while ((opt = getopt (argc, argv, "p:s:m:")) != -1) {
    switch (opt) {
    case 'p':
      inp = optarg;
      break;
    case 's':
      outc = optarg;
      break;
    case 'm':
      m = atoi (optarg);
      break;
    default:                   /* '?' */
      fprintf (stderr, usage, progname);
      exit (EXIT_FAILURE);
    }
 }
	if( optind < argc ) {
                fprintf( stderr, "\nBad parameters!\n" );
                for( ; optind < argc; optind++ )
                        fprintf( stderr, "\t\"%s\"\n", argv[optind] );
                fprintf( stderr, "\n" );
                fprintf( stderr, usage, progname );
                exit( EXIT_FAILURE );
        }


    FILE *inf = fopen (inp, "r");
    if (inf == NULL) {
      fprintf (stderr, "%s Blad otwierania pliku z punktami %s\n\n", argv[0], inp);
      exit (EXIT_FAILURE);
    }
FILE *out = fopen (outc, "w");
    if (out == NULL) {
      fprintf (stderr, "%s Blad otwierania pliku do zapisu punktow %s\n\n", argv[0], outc);
	fclose(inf);
      exit (EXIT_FAILURE);
    }


	res=read_pts_failed(inf, &points);
	if(res==1){
		printf("Blad odczytu punktow\n");
		return 1;
	}
	
	
	double *y=malloc(sizeof *y*points.n);
	aprox(&points, out, y, m);
	free(y);
	return 0;
}
