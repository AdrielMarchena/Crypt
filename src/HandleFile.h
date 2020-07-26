#pragma once
class HandleFile
{
public:
	std::string filepath;

	HandleFile(const std::string& filepath);
	HandleFile();
	bool write(const std::string& line);
	std::string read();
};

