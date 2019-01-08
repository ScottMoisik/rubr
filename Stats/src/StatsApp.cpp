#include <Rubr.h>

#include "CSVread.h"
#include <Eigen/Dense>
#include <Eigen/Core>
#include "matplotlibcpp.h"
#include "Rubr/Gnuplot.h"


using Eigen::MatrixXd;
using Eigen::Map;
namespace plt = matplotlibcpp;


class ExampleLayer : public Rubr::Layer {
public: 
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		//RUBR_INFO("ExampleLayer::Update");
	}

	void OnEvent(Rubr::Event& event) override {
		RUBR_TRACE("{0}", event);
	}
};






class Stats : public Rubr::App {
public:
	Stats() {
		PushLayer(new ExampleLayer());

		std::ifstream file("C:/dev/Rubr/Stats/src/test.csv");
				

		if (file.is_open()) {
			//Count the number of lines
			int count = 0;
			std::string line;
			while (getline(file, line))
				count++;

			file.clear();
			file.seekg(0, std::ios::beg);

			//Create an iterator for the file
			CSVIterator loop(file);

			//Read the header
			CSVRow headerRow = *loop;
			std::vector<std::string> header;
			for (int hIdx = 0; hIdx < headerRow.size(); ++hIdx)
				header.push_back(headerRow[hIdx]);
			++loop;

			//Determine number of columns of data based on header and create matrix
			int numRows = count - 1; 
			int numCols = headerRow.size();
			int rIdx = 0;

			MatrixXd data(numRows, numCols);
			std::cout << data << std::endl;

			//Read each data line and store it into the data matrix
			while (loop != CSVIterator()) {
				CSVRow row = *loop;
				auto sz = row.size();
				
				for (int cIdx = 0; cIdx < sz; ++cIdx) {
					data(rIdx, cIdx) = std::stod(row[cIdx], nullptr);
					RUBR_TRACE("{0}", data(rIdx, cIdx));
				}

				rIdx++;
				++loop;
			}
			std::cout << data << std::endl;
			std::cout << data.row(0) << std::endl;
			 
			file.close();

			data.transposeInPlace();

			Rubr::Gnuplot::plot(data.col(0).data(), data.rows());
		}

	}
	~Stats() {}
};

Rubr::App* Rubr::CreateApp() {
	return new Stats();
}




