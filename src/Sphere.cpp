#include "Sphere.h"

Sphere::Sphere(): sphereSource(vtkSmartPointer<vtkSphereSource>::New()) {}

vtkSmartPointer<vtkPolyDataAlgorithm> Sphere::getShapeSource() {
	return sphereSource;
}

std::vector<std::pair<QString, QString>> Sphere::getParameters() {
	std::vector<std::pair<QString, QString>> sphereParameters;
	sphereParameters.push_back({ "Name:","Sphere" });
	sphereParameters.push_back({ "Radius:", QString::number(sphereSource->GetRadius()) });
	sphereParameters.push_back({ "Center:", QString::number(*(sphereSource->GetCenter())) });
	sphereParameters.push_back({ "Theta resolution:", QString::number(sphereSource->GetThetaResolution()) });
	sphereParameters.push_back({ "Phi resolution:", QString::number(sphereSource->GetPhiResolution()) });	
	return sphereParameters;
}

void Sphere::setParameters(std::vector<double> parameters){
	sphereSource->SetRadius(parameters[0]);
	sphereSource->SetCenter(&parameters[1]);
	sphereSource->SetThetaResolution(parameters[2]);
	sphereSource->SetPhiResolution(parameters[3]);
}