#pragma once

#include "Shape.h"
#include <vtkConeSource.h>

class Cone :
	public Shape
{
private:
	vtkSmartPointer<vtkConeSource> coneSource;

public:
	Cone();

	virtual vtkSmartPointer<vtkPolyDataAlgorithm> getShapeSource();
	virtual  std::vector<std::pair<QString, QString>> getParameters();
	virtual void setParameters(std::vector<double>);
};

