#include "mainwindow.h"
#include<iostream>
#include<vtksys/SystemTools.hxx>
/*--------------- GUI and QT Headers -------------------*/
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QLineEdit>
/*--------------- File Readers Headers -----------------*/
#include<vtkPLYReader.h>
#include<vtkBYUReader.h>
#include<vtkOBJReader.h>
#include<vtkSTLReader.h>
#include<vtkPLYReader.h>
#include<vtkXMLPolyDataReader.h>
#include<vtkPolyDataReader.h>
/*---------------- Poly shapes Headers -----------------*/
#include "Sphere.h"
#include "Cylinder.h"
#include "Arrow.h"
#include "Cone.h"
#include "Cube.h"
#include "Disk.h"
#include<vtkPolyDataMapper.h>



/*---------------- Constructors and destructors -----------------*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), mRenderer(vtkSmartPointer<vtkRenderer>::New()),
	mRenderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()), mInteractor(vtkSmartPointer<QVTKInteractor>::New()),
	mInteractorStyle(vtkSmartPointer<vtkInteractorStyle>::New())
{
    ui->setupUi(this);
	init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*------------------ Listner to click events --------------------*/

void MainWindow::onDrawClick() {
	// Remove actors from the renderer object and remove its info 
	onClearClick();
	// Get requested shape name and pass it to method factory to create the shape
	QString shapeName = ui->shapes->currentText();
	Shape * shape = createShape(shapeName);
	if (shape == nullptr)
		return;
	// Get shape source from the shape and show its info
	vtkSmartPointer<vtkPolyDataAlgorithm> shapeSource = shape->getShapeSource();
	showShapeInfo(shape);
	// Create mapper to convert the poly data to an actor to be rendered in the scene
	auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(shapeSource->GetOutputPort());
	auto actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	// Adding the actor to the scene and reset the camera then render the scene
	mRenderer->AddActor(actor);
	mRenderer->ResetCamera();
	mRenderer->Render();
	mRenderWindow->Render();
}

void MainWindow::clearScene() {
	// Get all actors from renderer object then remove them
	vtkActorCollection * actors = mRenderer->GetActors();
	vtkActor * actor;
	for (actors->InitTraversal(); (actor = actors->GetNextItem()) != NULL;)
	{
		mRenderer->RemoveActor(actor);
	}
	mRenderer->Clear();
	// Render the scene after removing the actors
	mRenderer->Render();
	mRenderWindow->Render();
}

void MainWindow::onClearClick() {
	clearScene();
	// Removing displayed info about the shape
	QLayoutItem * item;
	while ((item = ui->verticalLayout_2->takeAt(1)) != nullptr)
	{
		delete item->widget();
		delete item;
	}
}

void MainWindow::onDrawFileClick() {
	if (filePath == "")
	{
		QMessageBox::information(this, tr("Info"), "Please choose a file");
		return;
	}
	onClearClick();
	// Getting the data from a file
	auto polyData = readPolyData();
	auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(polyData);

	auto actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	mRenderer->AddActor(actor);
	mRenderer->ResetCamera();
	mRenderer->Render();
	mRenderWindow->Render();
}

void MainWindow::onClearFileClick() {
	filePath = "";
	onClearClick();
}

void MainWindow::onApplyClick() {
	// Get shape parameters
	auto parameters = getShapeParameters();
	// Clear the scene
	onClearClick();
	// update the object
	updateObject(parameters);
}

void MainWindow::onBrowseFile() {
	QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "F://",
		"poly files (*.ply);;vtp files (*.vtp);;object files (*.obj);;stl files (*.stl);;vtk files (*.vtk);; g files (*.g)");
	QMessageBox::information(this, tr("File Name"), file);
	filePath = file.toStdString();
}

/*------------------ Displaying shape information ------------------*/

void MainWindow::showShapeInfo(Shape * shape) {
	auto info = shape->getParameters();
	for_each(info.begin(), info.end(), [&](std::pair<QString, QString> infoData) {
		addNewInfo(infoData.first, infoData.second, ui->verticalLayout_2);
	});
	QPushButton * button = addNewButton("Apply", ui->verticalLayout_2);
	QObject::connect(button, &QPushButton::clicked,
		this, &MainWindow::onApplyClick);
}

void MainWindow::addNewInfo(QString infoName, QString value, QLayout * parentWidgetLayout) {
	// create the layout then add labels into it
	QHBoxLayout * layout = new QHBoxLayout;
	// add the layout into the widget
	QWidget * newWidget = new QWidget();
	newWidget->setLayout(layout);
	// create the label and add it to the layout
	QLabel * label1 = new QLabel(infoName, newWidget);
	QLineEdit * lineEdit = new QLineEdit(value, newWidget);
	lineEdit->setMaximumWidth(100);
	lineEdit->setFixedWidth(100);
	layout->addWidget(label1);
	layout->addWidget(lineEdit);
	parentWidgetLayout->addWidget(newWidget);
}

/*------------------------ Helper methods ------------------------- */

// Method to initialize the object used and ui connections
void MainWindow::init() {

	// add renderer object to a window
	mRenderWindow->AddRenderer(mRenderer);

	// add renderer window to opengl widget
	ui->openGLWidget->setRenderWindow(mRenderWindow);

	//set the ui connections
	QObject::connect(ui->drawButton, &QPushButton::clicked,
		this, &MainWindow::onDrawClick);
	QObject::connect(ui->clear, &QPushButton::clicked,
		this, &MainWindow::onClearClick);
	QObject::connect(ui->browseFile, &QPushButton::clicked,
		this, &MainWindow::onBrowseFile);
	QObject::connect(ui->drawFile, &QPushButton::clicked,
		this, &MainWindow::onDrawFileClick);
	QObject::connect(ui->pushButton, &QPushButton::clicked,
		this, &MainWindow::onClearFileClick);
}

// Method used as a factory method to create the shapes
Shape* MainWindow::createShape(QString shapeName) {
	if (shapeName == "Cylinder") {
		return new Cylinder();
	}
	else if (shapeName == "Sphere") {
		return new Sphere();
	}
	else if (shapeName == "Cone") {
		return new Cone();
	}
	else if (shapeName == "Cube") {
		return new Cube();
	}
	else if (shapeName == "Arrow") {
		return new Arrow();
	}
	else if (shapeName == "Disk") {
		return new Disk();
	}
	else {
		return nullptr;
	}
}

// Method to get the shape new input parameters from GUI
std::vector<double> MainWindow::getShapeParameters() {
	QLayoutItem * item;
	std::vector<double> parameters;
	int count = 2;
	// Looping through all the line edit widgets in the layout to get the parameters
	// then push them into the vector
	while ((item = ui->verticalLayout_2->itemAt(count)) != nullptr)
	{
		auto lineEdit = item->widget()->findChildren<QLineEdit *>();
		if (lineEdit.size() > 0 )
			parameters.push_back(lineEdit[0]->text().toDouble());
		count++;
	}
	return parameters;
}

// Method to update the scene when changing object parameters
void MainWindow::updateObject(std::vector<double> &parameters) {
	// Get requested shape name and pass it to method factory to create the shape
	QString shapeName = ui->shapes->currentText();
	Shape * shape = createShape(shapeName);
	shape->setParameters(parameters);
	// Get shape source from the shape and show its info
	vtkSmartPointer<vtkPolyDataAlgorithm> shapeSource = shape->getShapeSource();
	showShapeInfo(shape);
	// Create mapper to convert the poly data to an actor to be rendered in the scene
	auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(shapeSource->GetOutputPort());
	auto actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	// Adding the actor to the scene and reset the camera then render the scene
	mRenderer->AddActor(actor);
	mRenderer->ResetCamera();
	mRenderer->Render();
	mRenderWindow->Render();
}

// Method to add a button to layout in GUI
QPushButton* MainWindow::addNewButton(QString buttonName, QLayout * parentWidgetLayout) {
	// create the layout then add labels into it
	QHBoxLayout * layout = new QHBoxLayout;
	// add the layout into the widget
	QWidget * newWidget = new QWidget();
	newWidget->setLayout(layout);
	// create the button and add it to the layout
	QPushButton * button = new QPushButton(buttonName, newWidget);
	layout->addWidget(button);
	parentWidgetLayout->addWidget(newWidget);
	return button;
}

// Method to read poly data from files
vtkSmartPointer<vtkPolyData> MainWindow::readPolyData() {
	vtkSmartPointer<vtkPolyData> polyData;
	std::string extension = vtksys::SystemTools::GetFilenameLastExtension(std::string(filePath));
	std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
	if (extension == ".ply")
	{
		vtkNew<vtkPLYReader> reader;
		reader->SetFileName(filePath.c_str());
		reader->Update();
		polyData = reader->GetOutput();
	} else if (extension == ".vtp") {
		vtkNew<vtkXMLPolyDataReader> reader;
		reader->SetFileName(filePath.c_str());
		reader->Update();
		polyData = reader->GetOutput();
	} else if (extension == ".obj") {
		vtkNew<vtkOBJReader> reader;
		reader->SetFileName(filePath.c_str());
		reader->Update();
		polyData = reader->GetOutput();
	} else if (extension == ".stl") {
		vtkNew<vtkSTLReader> reader;
		reader->SetFileName(filePath.c_str());
		reader->Update();
		polyData = reader->GetOutput();
	} else if (extension == ".vtk") {
		vtkNew<vtkPolyDataReader> reader;
		reader->SetFileName(filePath.c_str());
		reader->Update();
		polyData = reader->GetOutput();
	} else if (extension == ".g") {
		vtkNew<vtkBYUReader> reader;
		reader->SetFileName(filePath.c_str());
		reader->Update();
		polyData = reader->GetOutput();
	} else {
		polyData = NULL;
	}
	return polyData;
}

