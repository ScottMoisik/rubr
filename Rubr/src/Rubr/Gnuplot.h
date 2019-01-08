#pragma once

#include "Rubr/Core.h"

namespace Rubr {
	class RUBR_API Gnuplot {
	public:
		Gnuplot();
		~Gnuplot();
		void static plot(const double* data, int dataSize);
		void operator ()(const std::string& command);
		// send any command to gnuplot
	protected:
		FILE *gnuplotpipe;
	};
}
