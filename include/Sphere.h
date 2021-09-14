#pragma once

#include <vtkSphereSource.h>
#include <Shape.h>

class Sphere : public Shape
{
private:
	vtkSmartPointer<vtkSphereSource> sphereSource;
public:
	Sphere();

	virtual vtkSmartPointer<vtkPolyDataAlgorithm> getShapeSource();
	virtual  std::vector<std::pair<QString, QString>> getParameters();
	virtual void setParameters(std::vector<double>);
};

