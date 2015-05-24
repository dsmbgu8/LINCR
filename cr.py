import getopt, sys
import numpy as np

from lincr import removeContinuumInplace

def main(argv=None):
    class usage(Exception):
    	def __init__(self, msg):
	    self.msg = msg

    if argv is None:
        argv = sys.argv
    try:
        try:
            longopts   = ['verbose','plot',]	  
	    longoptsp  = ['infile','outfile']   
            shortopts  = ''.join([o[0] for o in longopts])
	    shortopts += ''.join([o[0]+':' for o in longoptsp])
            opts, args = getopt.getopt(argv[1:], shortopts, longopts)
                                       
        except getopt.error, msg:
            raise usage(msg)

        infile,outfile = '','crdat.txt'
	verbose,doplot = False,False
	for opt, val in opts:
	    if opt in ('--verbose','-v'):
	        verbose=True
	    elif opt in ('--plot','-p'):
	        doplot=True
	    if opt in ('--infile','-i'):
	        infile=val
	    if opt in ('--outfile','-o'):
	        outfile=val
                
            	          
    except usage, err:
        print >>sys.stderr, err.msg
        return 2	

    
    [wvl,cidat] = np.loadtxt(infile,skiprows=1).T
    crdat,ccdat = cidat.copy(),cidat.copy()
    removeContinuumInplace(wvl,crdat,0,verbose)
    removeContinuumInplace(wvl,ccdat,1,verbose)

    np.savetxt(outfile,np.c_[wvl,cidat,crdat,ccdat])
    print "CR complete, %s written"%outfile
    if doplot: 
        import pylab as pl
        pl.figure()
        pl.suptitle('Input file: '+infile)
        pl.subplot(211)
        pl.plot(wvl,cidat,label='Continuum Intact Spectrum')
        pl.plot(wvl,ccdat,label='Continuum Curve')
        pl.legend(loc='best')
       
        pl.subplot(212)
        pl.axhline(1.0,color='k')
        pl.axhline(0.0,color='k')
        pl.plot(wvl,crdat,label='Continuum Removed Spectrum')
        pl.ylim(-0.1,1.1)
        pl.xlabel('wavelength')
        pl.legend(loc='best')
       
        pl.show()


if __name__ == '__main__':
    sys.exit(main())




