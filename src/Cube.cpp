#include "Cube.h"

Cube::Cube(): cubeSource(vtkSmartPointer<vtkCubeSource>::New()){}

vtkSmartPointer<vtkPolyDataAlgorithm> Cube::getShapeSource() {
	return cubeSource;
};

std::vector<std::pair<QString, QString>> Cube::getParameters() {
	std::vector<std::pair<QString, QString>> cubeParameters;
	cubeParameters.push_back({ "Name:","Cube" });
	cubeParameters.push_back({ "X length:", QString::number(cubeSource->GetXLength())});
	cubeParameters.push_back({ "Y length:", QString::number(cubeSource->GetYLength())});
	cubeParameters.push_back({ "Z length:", QString::number(cubeSource->GetZLength())});
	cubeParameters.push_back({ "Center:", QString::number(*cubeSource->GetCenter())});
	return cubeParameters;

};

void Cube::setParameters(std::vector<double> parameters){
	cubeSource->SetXLength(parameters[0]);
	cubeSource->SetYLength(parameters[1]);
	cubeSource->SetZLength(parameters[2]);
	cubeSource->SetCenter(&parameters[3]);
}