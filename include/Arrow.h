#pragma once
#include "Shape.h"
#include <vtkArrowSource.h>

class Arrow :
	public Shape
{
private:
	vtkSmartPointer<vtkArrowSource> arrowSource;
public:
	Arrow();

	virtual vtkSmartPointer<vtkPolyDataAlgorithm> getShapeSource();
	virtual  std::vector<std::pair<QString, QString>> getParameters();
	virtual void setParameters(std::vector<double>);
};

