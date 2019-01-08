#include "rubrpch.h"
#include "Gnuplot.h"

namespace Rubr {

	Gnuplot::Gnuplot() {
		// with -persist option you will see the windows as your program ends
		//gnuplotpipe=_popen("gnuplot -persist","w");
		//without that option you will not see the window
		 // because I choose the terminal to output files so I don't want to see the window
		gnuplotpipe = _popen("c:\\gnuplot\\bin\\gnuplot -persist", "w");
		if (!gnuplotpipe) {
			std::cerr << ("Gnuplot not found !");
		} else {
			fprintf(gnuplotpipe, "set term wxt\n");
			fflush(gnuplotpipe);
		}
	}
	Gnuplot::~Gnuplot() {
		fprintf(gnuplotpipe, "exit\n");
		_pclose(gnuplotpipe);
	}

	void Gnuplot::operator()(const std::string& command) {
		fprintf(gnuplotpipe, "%s\n", command.c_str());
		fflush(gnuplotpipe);
		// flush is necessary, nothing gets plotted else
	};

	void Gnuplot::plot(const double* data, int dataSize) {

		std::ofstream outdata; // outdata is like cin
		int i; // loop index

		outdata.open("temp.dat"); // opens the file
		if (!outdata) { // file couldn't be opened
			std::cerr << "Error: file could not be opened" << std::endl;
		}
		else {

			for (i = 0; i < 5; ++i)
				outdata << i + 1 << "" << '\t' << data[i] << std::endl;
			outdata.close();

			Gnuplot plot;
			plot("set style line 1 \linecolor rgb '#0060ad' \linetype 1 linewidth 2 \pointtype 7 pointsize 1.5");
			
			char buff[100];
			snprintf(buff, sizeof(buff), "set xrange [0:%d]", dataSize + 1);
			std::string buffAsStdStr = buff;
			plot(buffAsStdStr);
			
			plot("plot 'temp.dat' with linespoints linestyle 1");// using 1:2 title 'Column'");
		}
	}
}