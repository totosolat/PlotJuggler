#ifndef FFT_H
#define FFT_H

#include <qwt_series_data.h>
#include <complex>


class FFT
{
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
	ComplexVector ditfft2(size_t i0, size_t N, size_t s)
	{
        ComplexVector X(N, Complex(0.0, 0.0));
		ComplexVector X_left;
		ComplexVector X_right;

		if (N == 1)
			X[0] = _x[i0];
		else
		{
			X_left  = ditfft2(i0,   N/2, 2*s);
			X_right = ditfft2(i0+s, N/2, 2*s);

			for (size_t i = 0 ; i < N/2 ; i++)
			{
				X[i] = X_left[i];
				X[i + N/2] = X_right[i];
			}

			for (size_t k = 0 ; k <  N/2 ; k++) {
                Complex t = X[k];
                Complex angle(0.0, -2*M_PI*k/N);

				X[k] = t + std::exp(angle) * X[k + N/2];
				X[k + N/2] = t - std::exp(angle) * X[k + N/2];
			}
		}

		return X;
	}

public:
	FFT() {}
	~FFT() {}

	// Perform a Fast Fourier Transform, based on the Cooley-Tukey algorithm
	// (https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm)
	// Parameters :
	// 	- x_data : xy dataset to process. The data are on the y axis, the corresponding times
	//			   on the x axis
	//	- f_data : final vector of points (f, Fourier(f))
    void fft(const PlotDataPtr &x_data, std::vector<QPointF> &f_data)
	{
		// Fill the _x vector
		size_t N = x_data->size();
        _x.resize(N);
		for (size_t i = 0 ; i < N ; i++)
			_x[i] = x_data->at(i).y;

		// Append zeros to have a power-of-two-sized vector
		size_t power = 1;

		while (power < N)
			power *= 2;

		_x.resize(power, 0.0);

		// Perform FFT
        ComplexVector X = ditfft2(0, power, 1);

		// Build output
		f_data.resize(power);
		double fs = N / (x_data->at(N-1).x - x_data->at(0).x);	// sample frequency

		for (size_t k = 0 ; k < power ; k++)
		{
			QPointF p(k*fs/power, std::abs(X[k])/N);
			f_data[k] = p;
        }
	}

};

#endif  // FFT_H
