#pragma once

#include "Shape.h"
#include <vtkCubeSource.h>

class Cube :
	public Shape
{
private:
	vtkSmartPointer<vtkCubeSource> cubeSource;
public:
	Cube();

	virtual vtkSmartPointer<vtkPolyDataAlgorithm> getShapeSource();
	virtual  std::vector<std::pair<QString, QString>> getParameters();
	virtual void setParameters(std::vector<double>);

};

