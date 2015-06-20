%module lincr
%{
   #define SWIG_FILE_WITH_INIT
   #include "lincr.h"
%}

%include "numpy.i"

%init %{
   import_array();
%}

%apply (int DIM1, double* IN_ARRAY1) {(int len1, double* vec1), (int len2,double* vec2)}

%include "lincr.h"
%rename (removeContinuumInplace) my_lincr;

%inline %{
    double my_lincr(int len1, double* vec1, int len2, double* vec2, 
		 int ret_cc, int verbose) 
    {
    if (len1 != len2) {
        PyErr_Format(PyExc_ValueError, "Arrays of lengths (%d,%d) given", len1, len2);
        return 0.0;
    }
    removeContinuumInplace(len1, vec1, vec2, ret_cc, verbose);
}
%}




