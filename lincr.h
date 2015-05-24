#ifndef _LINCR_H_
#define _LINCR_H_

int removeContinuum(int n, double* wvl, double* dat, int ret_cc, 
		    int verbose, double* out);

int removeContinuumInplace(int n, double* wvl, double* dat, 
			   int ret_cc, int verbose);

#endif /* _LINCR_H_ */
