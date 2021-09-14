#include "Disk.h"

Disk::Disk(): diskSource(vtkSmartPointer<vtkDiskSource>::New()){}

vtkSmartPointer<vtkPolyDataAlgorithm> Disk::getShapeSource() {
	return diskSource;
}

std::vector<std::pair<QString, QString>> Disk::getParameters() {
	std::vector<std::pair<QString, QString>> diskParameters;
	diskParameters.push_back({ "Name:","Disk" });
	diskParameters.push_back({ "Inner radius:", QString::number(diskSource->GetInnerRadius()) });
	diskParameters.push_back({ "Outer radius:", QString::number(diskSource->GetOuterRadius()) });
	diskParameters.push_back({ "Radial resolution:", QString::number(diskSource->GetRadialResolution()) });
	diskParameters.push_back({ "Circumferential resolution:", QString::number(diskSource->GetCircumferentialResolution()) });
	return diskParameters;
}

void Disk::setParameters(std::vector<double> parameters){
	diskSource->SetInnerRadius(parameters[0]);
	diskSource->SetOuterRadius(parameters[1]);
	diskSource->SetRadialResolution(parameters[2]);
	diskSource->SetCircumferentialResolution(parameters[3]);
}