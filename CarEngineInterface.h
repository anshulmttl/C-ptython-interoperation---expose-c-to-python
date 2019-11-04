
#pragma once

#ifdef CARENGINE_EXPORTS
#define CARENGINE_API __declspec(dllexport)
#else
#define CARENGINE_API __declspec(dllimport)
#endif

#include <vector>
#include <string.h>

using namespace std;




struct PlateData
{
	RECT lprRect;
	char lprStr[20];
	float conf;
	int isPassed;
};

#define MAXPLATENUM 100
struct LPRResultData
{
	int nPlateNum;
	PlateData data[MAXPLATENUM];
};

typedef void* CARENGINE_HANDLE;
CARENGINE_API int LPR_Process(CARENGINE_HANDLE handle, char* filename, LPRResultData* pResult);

CARENGINE_API CARENGINE_HANDLE fcCarEngine_EngineCreate(string& config_dir);
CARENGINE_API void fcCarEngine_EngineDestroy(CARENGINE_HANDLE handle);

CARENGINE_API CARENGINE_HANDLE LPR_EngineCreate(string& config_dir);
CARENGINE_API void LPR_EngineDestroy(CARENGINE_HANDLE handle);

CARENGINE_API int fcCarEngine_DetectPlate(CARENGINE_HANDLE handle, BYTE* bgrImage, int w, int h, LPRResultData* pResult);
CARENGINE_API int fcCarEngine_RecognitionInPlate(CARENGINE_HANDLE handle, BYTE* bgrImage, int w, int h, LPRResultData* pResult);
CARENGINE_API int fcCarEngine_RecognitionInFullImage(CARENGINE_HANDLE handle, BYTE* bgrImage, int w, int h, LPRResultData* pResult);

