#include "settings.hpp"

Settings* Settings::hubsettings = 0;


Settings* Settings::getHubSettings(){
  if(hubsettings == 0)
  {
    hubsettings = new Settings();
  }

  return hubsettings;
}

std::string Settings::getLight()
{
  return fileLocations[0];
}

std::string Settings::getGarage()
{
  return fileLocations[1];
}

std::string Settings::getThermostat()
{
  return fileLocations[2];
}

std::string Settings::getDoorbell()
{
  return fileLocations[3];
}

void Settings::setLight(std::string light)
{
  fileLocations[0] = light;
}

void Settings::setGarage(std::string garage)
{
  fileLocations[1] = garage;
}

void Settings::setThermostat(std::string thermostat)
{
  fileLocations[2] = thermostat;
}

void Settings::setDoorbell(std::string doorbell)
{
  fileLocations[3] = doorbell;
}

bool Settings::readSettings(std::string filename )
{
  std::string toConsume;
  std::ifstream settingsfile;
  settingsfile.open(filename);

  if(settingsfile.is_open())
  {
    for(int i = 0; i <= 3; i++)
    {
      if(!(settingsfile >> fileLocations[i]))
      {
        std::cout << "Met EoF before all settings files could be set" << std::endl;
        settingsfile.close();
        return false;
      }
      std::cout << fileLocations[i] << std::endl;
    }
    settingsfile.close();
    return true;
  }
  return false;
}

bool Settings::writeSettings(std::string filename)
{
  std::ofstream ofs;
  bool allSettingsSet = true;

  ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
  for(int i = 0; i<= 3; i++)
  {
    if(!(fileLocations[i].empty()))
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
