#pragma once
#include "common.h"
#include "commands.h"

class CConvar
{
public:
	CConvar( std::string name, std::string defValue ) { this->name = name; this->defValue = defValue; this->value = defValue; }
	CConvar() {};
	void SetValue( std::string value ) { this->value = value; }
	std::string GetName() { return name; }
	std::string GetValue() { return value; }
	std::string GetDefaultValue() { return defValue; }
	int GetIntValue() { return atoi( value.c_str() ); }
	float GetFloatValue() { return atof( value.c_str() ); }
	bool GetBoolValue() { return GetIntValue() >= 1 || GetValue().compare( "true" ) == 0; }
private:
	std::string name;
	std::string defValue;
	std::string value;
};