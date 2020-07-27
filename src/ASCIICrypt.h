#pragma once
class ASCIICrypt
{
public:
	ASCIICrypt();
	static std::string encrypt(const std::string& pass, const std::string& key);
	static std::string decrypt(const std::string& key, const std::string& passCrypted);
	static void clear();
private:
	static unsigned long hex2dec(std::string hex);
};

