#ifndef FFT_H
#define FFT_H

#include <qwt_series_data.h>
#include "PlotJuggler/plotdata.h"
#include <complex>
#include <vector>


class FFT
{
public:
	FFT();
	~FFT();

	// Perform a Fast Fourier Transform, based on the Cooley-Tukey algorithm
	// (https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm)
	// Parameters :
	// 	- x_data : xy dataset to process. The data are on the y axis, the corresponding times
	//			   on the x axis
	//	- f_data : final vector of points (f, Fourier(f))
    void fft(const PlotData* &x_data, std::vector<QPointF> &f_data);

private:
    typedef std::vector<std::complex<double>> ComplexVector;
    typedef std::complex<double> Complex;

	// Input dataset to process (only the y field of the "fft()" input)
    std::vector<double> _x;

	// Recursive function called to compute the FFT
	// Parameters :
	//	- i0 : start index of the list
	//	- N : size of the ouput to produce
	// 	- s : offset size
	// The function will compute the fft of [_x(i0), _x(i0+s), ..., _x((N-1)s)]
	ComplexVector ditfft2(size_t i0, size_t N, size_t s);

};

#endif  // FFT_H
