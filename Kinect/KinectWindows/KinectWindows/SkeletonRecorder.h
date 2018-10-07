#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <NiTE.h>

class SkeletonRecorder
{
private:
	std::string destinationPath;
	std::vector<nite::Skeleton> buffer;
public:
	SkeletonRecorder();
	~SkeletonRecorder();

	void record(nite::Skeleton);
	void writeBufferToFile();
};

