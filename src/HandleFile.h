#pragma once
class HandleFile
{
public:
	std::string filepath;

	HandleFile(const std::string& filepath);
	bool write(const std::string& line);
	std::stringstream read();

};


