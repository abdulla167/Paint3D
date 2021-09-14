#include "Cylinder.h"

Cylinder::Cylinder() : cylinderSource(vtkSmartPointer<vtkCylinderSource>::New()) {}

vtkSmartPointer<vtkPolyDataAlgorithm> Cylinder::getShapeSource() {
	return cylinderSource;
};

std::vector<std::pair<QString, QString>> Cylinder::getParameters() {
	std::vector<std::pair<QString, QString>> cylinderParameters;
	cylinderParameters.push_back({ "Name:","Cylinder" });
	cylinderParameters.push_back({ "Radius:", QString::number(cylinderSource->GetRadius()) });
	cylinderParameters.push_back({ "Center:", QString::number(*(cylinderSource->GetCenter())) });
	cylinderParameters.push_back({ "Height:", QString::number(cylinderSource->GetHeight()) });
	cylinderParameters.push_back({ "Resolution:", QString::number(cylinderSource->GetResolution())});
	return cylinderParameters;
};

void Cylinder::setParameters(std::vector<double> parameters){
	cylinderSource->SetRadius(parameters[0]);
	cylinderSource->SetCenter(&parameters[1]);
	cylinderSource->SetHeight(parameters[2]);
	cylinderSource->SetResolution(parameters[3]);
}