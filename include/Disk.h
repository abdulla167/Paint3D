#pragma once

#include "Shape.h"
#include <vtkDiskSource.h>

class Disk :
	public Shape
{
private:
	vtkSmartPointer<vtkDiskSource> diskSource;

public:
	Disk();

	virtual vtkSmartPointer<vtkPolyDataAlgorithm> getShapeSource();
	virtual  std::vector<std::pair<QString, QString>> getParameters();
	virtual void setParameters(std::vector<double>);
};

