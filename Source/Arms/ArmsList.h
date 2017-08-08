#pragma once
#include <string>

struct ArmsList {
public:
	static ArmsList& get(void) {
		static ArmsList armslist;
		return armslist;
	}
	ArmsList(const ArmsList&) = delete;
	ArmsList& operator = (const ArmsList&) = delete;
	ArmsList(ArmsList&&) = delete;
	ArmsList operator = (ArmsList&&) = delete;

private:
	ArmsList() {}
	~ArmsList() {}

public:
	void init();
	std::string getCategoryName(int id);
	std::string getCategoryPass(int id);
	std::string getArmsName(int c, int id);
	std::string getArmsPass(int c, int id);

private:
	struct Category{
		std::string name;
		std::string arms[10];
	};

	Category category[10];
};