#include "Config.h"


void CConfig::Setup()
{


	SetupValue(M.MenuOpen, 1, "Main", "MenuOpen");
	SetupValue(M.ConsoleOpen, 1, "Main", "ConsoleOpen");
	SetupValue(M.AntiLag, 1, "Main", "AntiLag");
	//SetupValue(M.Configs, 0, "Main", "Configs");

	SetupValue(M.AARange.Master, 0, "AARange", "Master");
	SetupValue(M.AARange.Local, 0, "AARange", "Local");
	SetupValue(M.AARange.Turrets, 0, "AARange", "Turrets");
	SetupValue(M.AARange.Slider[0], 14, "AARange", "SliderPoints");
	SetupValue(M.AARange.Slider[1], 20, "AARange", "SliderThickness");

	SetupValue(M.AARange.Color[0], 0.965517f, "AARange", "ColorR");
	SetupValue(M.AARange.Color[1], 0.207541f, "AARange", "ColorG");
	SetupValue(M.AARange.Color[2], 0.076100f, "AARange", "ColorB");
	SetupValue(M.AARange.Color[3], 1.f, "AARange", "ColorA");

	SetupValue(M.AARange.LocalColor[0], 0.116188f, "AARange", "LocalColorR");
	SetupValue(M.AARange.LocalColor[1], 0.209196f, "AARange", "LocalColorG");
	SetupValue(M.AARange.LocalColor[2], 0.842365f, "AARange", "LocalColorB");
	SetupValue(M.AARange.LocalColor[3], 1.f, "AARange", "LocalColorA");


	SetupValue(M.Tracers.Master, 0, "Tracers", "Master");
	SetupValue(M.Tracers.Thickness, 10, "Tracers", "Thickness");


	SetupValue(M.Cooldowns.Master, 0, "Cooldowns", "Master");

	SetupValue(M.LastHit.Master, 0, "LastHit", "Master");
	SetupValue(M.LastHit.Color[0], 0.f, "LastHit", "ColorR");
	SetupValue(M.LastHit.Color[1], 1.f, "LastHit", "ColorG");
	SetupValue(M.LastHit.Color[2], 0.f, "LastHit", "ColorB");
	SetupValue(M.LastHit.Color[3], 1.f, "LastHit", "ColorA");

	SetupValue(M.AutoSmite.Master, 0, "AutoSmite", "Master");
	SetupValue(M.AutoSmite.Slot, 1, "AutoSmite", "Slot");

	SetupValue(M.Wards.Master, 0, "Wards", "Master");

	SetupValue(M.Inhibs.Master, 0, "Inhibs", "Master");


}

void CConfig::SetupValue(int& value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValue< int >(category, name, &value));
}

void CConfig::SetupValue(float& value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue< float >(category, name, &value));
}

void CConfig::SetupValue(bool& value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValue< bool >(category, name, &value));
}


void CConfig::Save(std::string fileName)
{
	static CHAR path[MAX_PATH];
	std::string folder, file;

//	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path)))
//	{
		//folder = std::string(path) + ".\\config\\";
	file = std::string(path) + ".\\" + fileName + ".ini";
//	}

	//CreateDirectoryA(folder.c_str(), NULL);
	WritePrivateProfileStringA("Main", "Configs", std::to_string(M.Configs).c_str(), ".\\cfg.ini");


	for (auto value : bools)
		WritePrivateProfileStringA(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());

	for (auto value : ints)
		WritePrivateProfileStringA(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileStringA(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());
}

void CConfig::Load(std::string fileName)
{
	static CHAR path[MAX_PATH];
	std::string folder, file;

	//if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path)))
//	{
		//folder = std::string(path) + ".\\config\\";
	file = std::string(path) + ".\\" + fileName + ".ini";
//	}

	//CreateDirectoryA(folder.c_str(), NULL);


	char value_l[32] = { '\0' };

	GetPrivateProfileStringA("Main", "Configs", "", value_l, 32, ".\\cfg.ini");
	M.Configs = atoi(value_l);

	for (auto value : ints)
	{
		GetPrivateProfileStringA(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		if (GetLastError() == 0x2) // if file not found dont load settings
			return;
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileStringA(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}


	for (auto value : bools)
	{
		GetPrivateProfileStringA(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}

	
}

CConfig* Config = new CConfig();
Menu M;