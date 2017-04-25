#include <fstream>
#include <iostream>
#include <algorithm>

class Settings
{
private:
  static Settings* hubsettings;
  Settings();
  /*
  FileLocations Mapping is as follows:
  0 - light
  1 - garage
  2 - thermostat
  3 - doorbell
  */
  std::string fileLocations[4];
public:
  static Settings* getHubSettings();
  std::string getLight();
  std::string getGarage();
  std::string getThermostat();
  std::string getDoorbell();
  void setLight(std::string light);
  void setGarage(std::string garage);
  void setThermostat(std::string thermostat);
  void setDoorbell(std::string doorbell);
  bool readSettings(std::string filename);
  bool writeSettings(std::string filename);
};
