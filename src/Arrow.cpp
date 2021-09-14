#include "Arrow.h"
#include <vtkArrowSource.h>

Arrow::Arrow(): arrowSource(vtkSmartPointer<vtkArrowSource>::New()) {}

vtkSmartPointer<vtkPolyDataAlgorithm> Arrow::getShapeSource() {
	return arrowSource;
};

std::vector<std::pair<QString, QString>> Arrow::getParameters() {
	std::vector<std::pair<QString, QString>> arrowParameters;
	arrowParameters.push_back({ "Name:","Arrow" });
	arrowParameters.push_back({"Tip radius:", QString::number(arrowSource->GetTipRadius())});
	arrowParameters.push_back({"Tip length:", QString::number(arrowSource->GetTipLength())});
	arrowParameters.push_back({"Shaft radius:", QString::number(arrowSource->GetTipResolution())});
	arrowParameters.push_back({"Shaft resolution:", QString::number(arrowSource->GetShaftResolution())});
	return arrowParameters;
};

void Arrow::setParameters(std::vector<double> parameters) {
	arrowSource->SetTipRadius(parameters[0]);
	arrowSource->SetTipLength(parameters[1]);
	arrowSource->SetTipResolution(parameters[2]);
	arrowSource->SetShaftResolution(parameters[3]);
}
