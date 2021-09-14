#pragma once
#include<vtkPolyDataAlgorithm.h>
#include <map>
#include <qstring.h>

class Shape {

public:
	Shape() {};
	virtual vtkSmartPointer<vtkPolyDataAlgorithm> getShapeSource() = 0;
	virtual  std::vector<std::pair<QString, QString>> getParameters() = 0;
	virtual void setParameters(std::vector<double>) = 0;
};
