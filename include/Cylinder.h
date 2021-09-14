#pragma once

#include "Shape.h"
#include <vtkCylinderSource.h>

class Cylinder :
	public Shape
{
private:
	vtkSmartPointer<vtkCylinderSource> cylinderSource;
public:
	Cylinder();
	virtual vtkSmartPointer<vtkPolyDataAlgorithm> getShapeSource();
	virtual  std::vector<std::pair<QString, QString>> getParameters();
	virtual void setParameters(std::vector<double>);
};

