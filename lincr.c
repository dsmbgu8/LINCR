#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include "lincr.h"

#ifndef DIFFEPS 
#define DIFFEPS 10e-10
#endif

void
printIndicator(char* name, unsigned char* ind, unsigned int n)
{
    /* Prints the nonzero elements of an indicator function */
    unsigned int i;
    printf("%s [ ", name);
    for (i=0; i<n; i++) if(ind[i]) printf("%d ",i);
    printf("]\n");
}

int
sweep(double* wvl, double* dat, int n, int verbose, unsigned char* hull)
{
    /*
    Sweeps spectrum, detecting points below piecewise linear 
    function approximation of continuum curve, adding as necessary.
    
    Input Arguments:
    - double* wvl: wavelength vector
    - double* dat: signal vector
    - int n: length of signal vector 
    - char verbose: print verbose output
    - unsigned char* hull: current hull
    
    Returns (unsigned int): number of points added to hull 
    */
    
    int i, l=0, r=1, nu=0;
    double slope,datpr;
    
    while(r < n) 
    {
	/* keep stepping through until both left and right are hull points */
        if (hull[r]) 
	{
	    /* get the slope between the left and right points */
	    slope = (dat[r]-dat[l]) / (wvl[r]-wvl[l]);
	    for (i=l; i<r; i++)
	    {
		/* predict position given current slope value */
		datpr = dat[l]+((wvl[i]-wvl[l])*slope);

		/* if prediction below actual, add actual to hull */
		if (dat[i]-datpr > DIFFEPS)
		{
		    hull[i]  = 1;
		    if (verbose) printf("under: %d (%f vs. %f)\n",i,dat[i],datpr); 
		    nu += 1; /* new hull point added */
		}
	    }
	    l = r;
	}
	r++;
    }

    return nu;
}


int removeContinuum(int n, double* wvl, double* dat, int ret_cc, 
		    int verbose, double* out)
{
    /*
    Removes the continuum from a spectrum via piecewise linear envelope
    fitting. 

    Returns either the (A) CR spectrum with values in [0,1] where values of
    1 are on the continuum or (B) the estimated continuum envelope.
    
    Input arguments:
    - int n: length of signal vector 
    - double* wvl: wavelength vector
    - double* dat: signal vector
    - int ret_cc: if 1, return continuum instead of cr spectrum
    - int verbose: enable verbose output

    Output arguments:
    - double* out: output spectrum (continuum-removed or continuum curve)

    Returns 0 for success, -1 for failure
    */

    int i,j,k,nu=0;
    double slope; 
    unsigned char* hull = (unsigned char*)malloc(n*sizeof(unsigned char));
    double* cr = (double*)malloc(n*sizeof(double));
    double* cc = (double*)malloc(n*sizeof(double));
    int retval = 0;

    /* by default, assume everything is on the continuum */
    memset(cr,1,n*sizeof(double));
    memcpy(cc,dat,n*sizeof(double));

    /* initial hull = inflection points */
    memset(hull,0,n*sizeof(unsigned char));
    for (i=1; i<n-1; i++)
    {
        if (dat[i] > dat[i-1] && dat[i] > dat[i+1])
	{
	    hull[i] = 1;
	}
    }
    hull[0] = hull[n-1] = 1; /* endpoints always on hull */
    if (verbose) printIndicator("Initial hull (C): ",hull,n);
    
    /* sweep the hull until we add/remove no more points */
    i=0;
    while (1)
    {
	nu=sweep(wvl, dat, n, verbose, hull);
	if (nu==0) { 
	    break; /* no new points added */
	}	
	if (verbose) printf("Sweep[%d]: %d points added\n",i,nu);
	i++;
    }
    if (verbose) printIndicator("Final hull (C): ",hull,n);
    i=0;
    while(i<n)
    {
	if (hull[i])
	{
	    j=i+1;
	    if (j==n)
	    {		
		cr[i] = 1.0;
		cc[i] = dat[i];
		break;
	    }

	    while(!hull[j])
	    {
		j++;
	    }

	    slope = (dat[j]-dat[i]) / (wvl[j]-wvl[i]);

	    if (verbose) printf("[%lf,%lf]: %lf\n",wvl[i],wvl[j],slope);
	    for (k=i; k<j; k++)
	    {
		cc[k] = dat[i]+((wvl[k]-wvl[i])*slope);
		cr[k] = dat[k] / cc[k];
	    }
	    i = j;
	}
	else
	{
	    fprintf(stderr,"Failed to match hull points at index %d",i);
	    retval = -1;
	    goto cleanup;
	}
    }

    if (ret_cc)
	memcpy(out,cc,n*sizeof(double));
    else 
	memcpy(out,cr,n*sizeof(double));

cleanup:
    free(hull);
    free(cr);
    free(cc);
    
    return retval;
}

int removeContinuumInplace(int n, double* wvl, double* dat, 
			   int ret_cc, int verbose)
{
    return removeContinuum(n,wvl,dat,ret_cc,verbose,dat);
}
