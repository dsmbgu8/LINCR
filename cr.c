#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lincr.h"

char out_name[256]; 

int main(int argc, char *argv[])
{
    int i=0, n;
    FILE *fin = NULL, *fout = NULL;

    double *dat = NULL, *wvl = NULL, *cr = NULL, *cc = NULL;

    int verbose = 0;

    if (argc > 0 && argc <= 3) /* parse an existing file */
    {
	fin = fopen(argv[1],"r");
	if (fin==NULL)
	{
	  fprintf(stderr,"error: cannot open file %s\n",argv[1]);
	  exit(1);
	}
	fscanf(fin,"%d\n",&n);

	dat = (double*)malloc(n*sizeof(double));
	wvl = (double*)malloc(n*sizeof(double));
	cr  = (double*)malloc(n*sizeof(double));
	cc  = (double*)malloc(n*sizeof(double));

	while(i<n)
	{
	    fscanf(fin,"%lf %lf\n",&(wvl[i]),&(dat[i]));
	    i++;
	}
	
	fclose(fin);

	if (argc == 3)
	{
	  sprintf(out_name,"%s",argv[2]);
	}
	else
	{
	  sprintf(out_name,"crdat.txt");
	}
	fout = fopen(out_name,"w");
	if (fout==NULL)
	{
	  fprintf(stderr,"error: cannot open file %s\n",out_name);
	  exit(1);
	}
    }
    else
    {
	fprintf(stderr,"Usage: %s infile [outfile]\n", argv[0]);
	return -1;
    }

    /* compute continuum-removed representation */
    removeContinuum(n,wvl,dat,0,verbose,cr);
    /* compute continuum-curve representation */
    removeContinuum(n,wvl,dat,1,verbose,cc);

    fprintf(fout,"%d\n", n);
    for (i=0; i<n; i++)
    {
	fprintf(fout,"%lf %lf %lf %lf\n",
		wvl[i],dat[i],cr[i],cc[i]); 
    }
    fclose(fout);
    printf("CR complete, %s written\n", out_name);

    free(wvl);
    free(dat);
    free(cr);
    free(cc);
    exit(0);
}
