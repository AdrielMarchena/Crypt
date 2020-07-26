#pragma once
class ASCIICrypt
{
public:
	ASCIICrypt();
	std::string encrypt(const std::string& pass, const std::string& key);
	std::string decrypt(const std::string& key, const std::string& passCrypted);
	void clear();
private:
	unsigned long hex2dec(std::string hex);
};

