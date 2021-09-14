#include "Cone.h"

Cone::Cone(): coneSource(vtkSmartPointer<vtkConeSource>::New()){}

vtkSmartPointer<vtkPolyDataAlgorithm> Cone::getShapeSource() {
	return coneSource;
};

std::vector<std::pair<QString, QString>> Cone::getParameters() {
	std::vector<std::pair<QString, QString>> coneParameters;
	coneParameters.push_back({ "Name:","Cone" });
	coneParameters.push_back({ "Radius:", QString::number(coneSource->GetRadius()) });
	coneParameters.push_back({ "Center:", QString::number(*coneSource->GetCenter()) });
	coneParameters.push_back({ "Height:", QString::number(coneSource->GetHeight()) });
	coneParameters.push_back({ "Resolution:", QString::number(coneSource->GetResolution()) });
	coneParameters.push_back({ "Capping:", QString::number(coneSource->GetCapping()) });
	coneParameters.push_back({ "Direction:", QString::number(*coneSource->GetDirection()) });

	return coneParameters;
};

void Cone::setParameters(std::vector<double> parameters){
	coneSource->SetRadius(parameters[0]);
	coneSource->SetCenter(&parameters[1]);
	coneSource->SetHeight(parameters[2]);
	coneSource->SetResolution(parameters[3]);
	coneSource->SetCapping(parameters[4]);
	coneSource->SetDirection(&parameters[5]);
}