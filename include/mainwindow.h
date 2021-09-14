#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<vtkGenericOpenGLRenderWindow.h>
#include<vtkRenderer.h>
#include<QVTKInteractor.h>
#include<vtkInteractorStyle.h>
#include<vtkCylinderSource.h>
#include <Shape.h>
#include <QPushButton>


namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void onDrawClick();
	void onDrawFileClick();
	void onBrowseFile();
	void onClearClick();
	void onClearFileClick();
	void onApplyClick();

private:
	Ui::MainWindow *ui;
	std::string filePath;
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow;
	vtkSmartPointer<vtkRenderer> mRenderer;
	vtkSmartPointer<QVTKInteractor> mInteractor;
	vtkSmartPointer<vtkInteractorStyle> mInteractorStyle;

	void showShapeInfo(Shape * shape);
	Shape * createShape(QString shapeName);
	void addNewInfo(QString infoName, QString value, QLayout * parentWidgetLayout);
	void init();
	vtkSmartPointer<vtkPolyData> readPolyData();
	QPushButton* addNewButton(QString buttonName, QLayout * parentWidgetLayout);
	void clearScene();
	void updateObject(std::vector<double> &);
	std::vector<double> getShapeParameters();
};

#endif // MAINWINDOW_H
