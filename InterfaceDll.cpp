#include "pch.h"
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
#include "CarEngineInterface.h"
#include <iostream>
using namespace std;
class CarEngineHandle_Holder : private boost::noncopyable
{
public: 
	CarEngineHandle_Holder(){}

	// Write constructor to initialize value_
	CarEngineHandle_Holder(void* engine)
	{
		value_.reset(engine);
	}
	
	void* get_Pointer()
	{
		return value_.get();
	}

private:
	std::shared_ptr<void> value_;
};

CarEngineHandle_Holder* fcCarEngine_EngineCreatePy(const string& configDir)
{	
	string configDir_lcl = configDir;
	return new CarEngineHandle_Holder(fcCarEngine_EngineCreate(configDir_lcl));
}

CarEngineHandle_Holder* LPR_EngineCreatePy(const string& configDir)
{
	string configDir_lcl = configDir;
	return new CarEngineHandle_Holder(LPR_EngineCreate(configDir_lcl));
}

void fcCarEngine_EngineDestroyPy(CarEngineHandle_Holder &engine)
{
	CARENGINE_HANDLE engine_l = engine.get_Pointer();
	fcCarEngine_EngineDestroy(engine_l);
}

void LPR_EngineDestroyPy(CarEngineHandle_Holder &engine)
{
	CARENGINE_HANDLE engine_l = engine.get_Pointer();
	LPR_EngineDestroy(engine_l);
}

int LPR_ProcessPy(CarEngineHandle_Holder &engine, char* fileName, shared_ptr<LPRResultData> &resultData)
{
	CARENGINE_HANDLE engine_l = engine.get_Pointer();
	LPRResultData* resultDataPointer = resultData.get();
	return LPR_Process(engine_l, fileName, resultDataPointer);
}

// Complete the following 3 function wrappers

int fcCarEngine_DetectPlatePy(CarEngineHandle_Holder &engine, boost::python::object pyBuffer, int w, int h, shared_ptr<LPRResultData> &resultData)
{
	CARENGINE_HANDLE engine_l = engine.get_Pointer();
	LPRResultData* resultDataPointer = resultData.get();

	// Decode pyBuffer to unsigned char *
	namespace python = boost::python;
	python::object locals(python::borrowed(PyEval_GetLocals()));
	python::object py_iter = locals["__builtins__"].attr("iter");
	python::stl_input_iterator<char> begin(py_iter(pyBuffer)), end;
	std::vector<char> buffer(begin,end);
	
	return fcCarEngine_DetectPlate(engine_l, reinterpret_cast<unsigned char*>(&buffer[0]), w, h, resultDataPointer);
}

int fcCarEngine_RecognitionInPlatePy(CarEngineHandle_Holder &engine, boost::python::object pyBuffer, int w, int h, shared_ptr<LPRResultData> &resultData)
{
	CARENGINE_HANDLE engine_l = engine.get_Pointer();
	LPRResultData* resultDataPointer = resultData.get();

	// Decode pyBuffer to unsigned char *
	namespace python = boost::python;
	python::object locals(python::borrowed(PyEval_GetLocals()));
	python::object py_iter = locals["__builtins__"].attr("iter");
	python::stl_input_iterator<char> begin(py_iter(pyBuffer)), end;
	std::vector<char> buffer(begin, end);

	return fcCarEngine_RecognitionInPlate(engine_l, reinterpret_cast<unsigned char*>(&buffer[0]), w, h, resultDataPointer);
}

int fcCarEngine_RecognitionInFullImagePy(CarEngineHandle_Holder &engine, boost::python::object pyBuffer, int w, int h, shared_ptr<LPRResultData> &resultData)
{
	CARENGINE_HANDLE engine_l = engine.get_Pointer();
	LPRResultData* resultDataPointer = resultData.get();

	// Decode pyBuffer to unsigned char *
	namespace python = boost::python;
	python::object locals(python::borrowed(PyEval_GetLocals()));
	python::object py_iter = locals["__builtins__"].attr("iter");
	python::stl_input_iterator<char> begin(py_iter(pyBuffer)), end;
	std::vector<char> buffer(begin, end);

	return fcCarEngine_RecognitionInFullImage(engine_l, reinterpret_cast<unsigned char*>(&buffer[0]), w, h, resultDataPointer);
}

BOOST_PYTHON_MODULE(HelloExt)
{
	using namespace boost::python;
	//def("SayHello", SayHello);

	class_< CarEngineHandle_Holder, boost::noncopyable>("CarEngineHandle_Holder", no_init);
	def("fcCarEngine_EngineCreatePy", fcCarEngine_EngineCreatePy, return_value_policy<manage_new_object>());
	def("LPR_EngineCreatePy", LPR_EngineCreatePy, return_value_policy<manage_new_object>());
	def("fcCarEngine_EngineDestroyPy", fcCarEngine_EngineDestroyPy);
	def("LPR_EngineDestroyPy", LPR_EngineDestroyPy);
	
	def("LPR_ProcessPy", LPR_ProcessPy);
	def("fcCarEngine_DetectPlatePy", fcCarEngine_DetectPlatePy);
	def("fcCarEngine_RecognitionInPlatePy", fcCarEngine_RecognitionInPlatePy);
	def("fcCarEngine_RecognitionInFullImagePy", fcCarEngine_RecognitionInFullImagePy);
	// Register shared pointer for LPRResultData to python
	register_ptr_to_python<shared_ptr<LPRResultData>>();
}