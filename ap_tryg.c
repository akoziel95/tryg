#include "ap_tryg.h"

#define PI 3.141592

double *init_s(int m)
{	double *s=malloc(sizeof*s*m);
	int i,j;
	for(i=0; i<m; i++)
		s[i]=0;
	return s;
}

int aprox(points_t *points, FILE *ouf, double *y, int m){
	int i,j;
	if(m==0)
		m=points->n/2-1;

	double a=0,psb=0,psa=0;
	double *sa=init_s(m);
	double *sb=init_s(m);
	FILE *outa=fopen("wspol", "w");
	for(i=0; i<m; i++)
	{	sa[i]=0;
		sb[i]=0;
		for(j=0;j<points->n; j++)
		{
			sa[i]+=points->y[j]*cos(2*M_PI*(i+1)*(j+1)/points->n);
			sb[i]+=points->y[j]*sin(2*M_PI*(i+1)*(j+1)/points->n);
		}
		sa[i]=sa[i]*2/points->n;
		sb[i]=sb[i]*2/points->n;
		fprintf(outa,"%f %f\n", sa[i], sb[i]);	
	}


	for(j=0; j<points->n; j++)
		a+=points->y[j];
	a/=points->n;

	for(i=0; i<points->n; i++)
	{	
		for(j=0; j<m;j++){
			psa+=sa[j]*cos((2*M_PI*(j+1))/points->n)*points->y[i];
			psb+=sb[j]*sin((2*M_PI*(j+1))/points->n)*points->y[i];
		}
		y[i]=a+psa+psb;
		fprintf(ouf, "%f %f \n", points->x[i], y[i]);
		psa=psb=0;
	}
	printf("%f\n",a);
	return 0;
}
