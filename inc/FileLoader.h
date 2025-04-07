#pragma once

class FileLoader
{
public:
	static FileLoader& GetInstance();
	void Initialize();
private:
	FileLoader();

	FileLoader(const FileLoader&) = delete;
	FileLoader& operator=(const FileLoader&) = delete;
};



//typedef struct StringData
//{
//	int m;
//	int n;
//	int count;
//	int additional1;
//	int additional2;
//	int additional3;
//	wchar_t* data;
//} StringData;
//
//
//
//
//StringData* LoadSingleLineData(const wchar_t* file_name);
//
//StringData* LoadMultiLineData(const wchar_t* file_name);