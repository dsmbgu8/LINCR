# LINCR: Library for (piecewise) LINear Continuum Removal 

## Usage 

Please see README_C.txt or README_PYTHON.txt for usage information for
the standalone (C) and python versions, respectively.

## Algorithm summary 

Calculates the continuum-removed signature for a given spectrum. We
first locate the concave inflection points in the spectrum and connect
them via straight line segments, forming the initial approximation to
the continuum. Next we locate the bands for which this piecewise
linear function underestimates the band's reflectance value, and add
those bands to the continuum.

Once the continuum is estimated, the continuum-removed representation
is calculated according to:

> cr[i] = spectrum[i]/continuum[i]

where spectrum is the input spectrum, continuum is the estimated
continuum, and `i` is the index of the `i`th band.



## Build / Standalone C version

### Requirements
- OSX 10.6+
- gcc 4.0+

### Build instructions

To build the demo program "cr" just run "make". 

Tested on:  
- OSX 10.6
- gcc 4.0


### Input / Output file formats

The cr program takes an input file of the following format:
```
[N]
[band 1 wavelength] [band 1 DN]
      	...	    	...
[band N wavelength] [band N DN]
```
and produces an output file of the following format:

```
[N]
[band 1 wavelength] [band 1 DN] [band 1 CR] [band 1 CC]
      	...	    	... 	    ...	    	...
[band N wavelength] [band N DN] [band N CR] [band N CC]

where 
[band i DN] = value of the original spectrum at band i 
[band i CR] = value of the continuum-removed spectrum at band i
[band i CC] = value of the estimated continuum at band i
```

### Testing

To test the "cr" program with an example spectrum, run:

>   cr example/cidat.txt

This will produce the output file "crdat.txt" of the format given above. 


## Python version 

### Requirements
- Python 2.6
- numpy 1.6.1
- numpy.i (http://docs.scipy.org/doc/numpy/reference/swig.interface-file.html)
- matplotlib (optional, for plotting spectra)

### Build instructions 

The command

>    python setup.py build

will build the `_lincr.so` library in the build/(architecture)/
directory. 

### Testing 

The cr.py program is an example wrapper for the lincr library. To try
it, run the command:

>    python cr.py -i example/cidat.txt -p -v

The format of the example/cidat.txt file are provided in README_C.txt

## Matlab version 

### Requirements
- Matlab 2011a+


### Testing 

Run the `lincr.m` wrapper after building the standalone (C) version.

## Citation 

Please cite the following paper if you publish any works using this
code:

> B. D. Bue, E. Merényi, and B. Csathó, “Automated Labeling of Materials
in Hyperspectral Imagery,” IEEE Trans. on Geoscience and Remote
Sensing, vol. 48, no. 11, pp. 4059–4070, 2010.

## Troubleshooting 

If you receive CR values > 1, try reducing the value of the DIFFEPS
variable in lincr.c.

## Contact 

Please contact the author (bbue@alumni.rice.edu) if you have any questions
regarding this program.

## Changelog 

08/11/14 - added Matlab functions

