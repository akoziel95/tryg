#include "points.h"
#include "ap_tryg.h"
#include <stdio.h>
#include <stdlib.h>

char *info="Aby poprawnie uruchomić program należy podać argumenty:\n"
"	1 - nazwa pliku z danymi źródlowymi\n "
"	2 - nazwa pliku z danymi wynikowymi\n "
"	3 - opcjonalny stopień wielomianu aproksymującego\n";




int main(int argc, char **argv)
{	//FILE *in = fopen(argv[1], "r");
	FILE *in= fopen(argv[1], "r");
	points_t points;
	points.n=0;
	int res;
	//FILE *out= fopen(argv[2], "w");
	FILE *out=   fopen(argv[2], "w");
	int m= argc>3 ? atoi(argv[3]): 0 ;	
	if(!in){
		printf("Błąd otwarcia pliku %s\n\n %s", argv[1],info);
		return EXIT_FAILURE;
	}
	 if(!out){
                printf("Nie została podana nazwa pliku wynikowego\n\n %s",info);
                return EXIT_FAILURE;
        }


	res=read_pts_failed(in, &points);
	if(res==1){
		printf("Blad odczytu punktow\n");
		return 1;
	}
	
	double *y=malloc(sizeof *y *points.n);
	aprox(&points, out, y, m);
	return 0;
}
