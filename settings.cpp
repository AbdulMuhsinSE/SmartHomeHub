#include "settings.hpp"

Settings* Settings::hubsettings = 0;


Settings* Settings::getHubSettings(){
  if(hubsettings == 0)
  {
    hubsettings = new Settings();
    for (int i = 0; i <= 3; i++)
    {
      fileLocations[i] = nullptr;
    }
  }

  return hubsettings;
}

std::string getLight()
{
  return fileLocations[0];
}

std::string getGarage()
{
  return fileLocations[1];
}

std::string getThermostat()
{
  return fileLocations[2];
}

std::string getDoorbell()
{
  return fileLocations[3];
}

void setLight(std::string light)
{
  fileLocations[0] = light;
}

void setGarage(std::string garage)
{
  fileLocations[1] = garage;
}

void setThermostat(std::string thermostat)
{
  fileLocations[2] = thermostat;
}

void setDoorbell(std::string doorbell)
{
  fileLocations[3] = doorbell;
}

bool readSettings(std::string filename )
{
  string toConsume;
  ifstream settingsfile;
  settingsfile.open(filename);

  if(settingsfile.is_open())
  {
    for(int i = 0; i <= 3; i++)
    {
      if(!(inf >> fileLocations[i]))
      {
        cout << "Met EoF before all settings files could be set";
        settingsfile.close();
        return false;
      }
    }
    settingsfile.close();
    return true;
  }
  settingsfile.close();
  return false;
}

bool writeSettings(std::string filename)
{
  std::ofstream ofs;
  bool allSettingsSet = true;

  ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
  for(int i = 0; i<= 3; i++)
  {
    if(fileLocations[i] == nullptr)
    {
      ofs << "\n";
      allSettingsSet = false;
    }
    else
    {
      ofs << fileLocations[i] << "\n";
    }
  }

  ofs.close();
  return allSettingsSet;
}
