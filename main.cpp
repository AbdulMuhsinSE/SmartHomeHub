#include <gtkmm.h>
#include <iostream>
#include <glibmm/ustring.h>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "settings.hpp"

Gtk::ApplicationWindow* hubwin = nullptr;
Gtk::Button* vidButton;
Gtk::ComboBoxText* vidCombo;
Gtk::Button* pollButton;
Gtk::Button* minmaxButton;
Gtk::Entry* tempEntry;
Gtk::Entry* minEntry;
Gtk::Entry* maxEntry;
Gtk::Button* garageButton;
Gtk::Button* lightButton;
Gtk::ToggleButton* autoButton;
Gtk::MessageDialog* hubDialog;

const char *homedir;

static void on_vidbutton_clicked()
{
  if(vidCombo)
  {
    std::string vid = (vidCombo->get_active_text()).raw();
    std::string path(homedir);
    path += "/shares/doorbellshare/"+ vid + ".h624";
    std::ifstream infile(path);
    if(infile)
    {
      std::string command = "mplayer -fps 30 -vo caca " + path;
      system(command.c_str());
    }
  }
}

static void on_pollbutton_clicked()
{
  if(tempEntry)
  {
    const char* var = "79";
    tempEntry->set_text(Glib::locale_to_utf8(var));
  }
}

static void on_minmaxbutton_clicked()
{
  if(minEntry && maxEntry)
  {
    std::string min = minEntry->get_text().raw();
    std::string max = maxEntry->get_text().raw();
    std::string command = "./temp.sh " + min + " " + max;
    std::cout << command << std::endl;
    system(command.c_str());
  }
}

static void on_garageButton_changed()
{
  if(garageButton)
  {
    int gStatus;
    std::string path(homedir);
    path += "/shares/garageshare/GarageStatus";
    std::ifstream infile(path);
    while (infile >> gStatus)
    {
      hubDialog->set_title(Glib::locale_to_utf8("Garage Door Controls"));
      if(gStatus == 1)
      {
        hubDialog->set_message(Glib::locale_to_utf8("Garage Door Closed"));
      }
      else
      {
        hubDialog->set_message(Glib::locale_to_utf8("Garage Door Opened"));
      }
      system("./garage.sh");
      int result = hubDialog->run();
    }

  }
}

static void on_lightswitch_changed()
{
  if(lightButton)
  {
    int lControlStatus;
    std::string controlpath(homedir);
    controlpath += "/shares/lightshare/lightControlStatus";
    std::ifstream infile(controlpath);
    while (infile >> lControlStatus)
    {
      hubDialog->set_title(Glib::locale_to_utf8("Light Controls"));
      if(lControlStatus == 1)
      {
        int lStatus;
        std::string path(homedir);
        path += "/shares/lightshare/lightStatus";
        std::ifstream lfile(path);
        while(lfile >> lStatus)
        {
          if(lStatus == 1)
          {
            hubDialog->set_message(Glib::locale_to_utf8("Light Switched Off"));
          }
          else
          {
            hubDialog->set_message(Glib::locale_to_utf8("Light Switched On"));
          }
          system("./light.sh");
        }
      }
      else
      {
        hubDialog->set_message(Glib::locale_to_utf8("Light Cannot Be Controlled in Auto Mode"));
      }
      //system("./light.sh");
      int result = hubDialog->run();
    }

  }
}

static void on_autoswitch_changed()
{
  std::cout << "You didn't think this would work be honest" << std::endl;
  system("./automatic.sh");
}

int main(int argc, char* argv[])
{

  if ((homedir = getenv("HOME")) == NULL) {
    homedir = getpwuid(getuid())->pw_dir;
  }

  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example.base");
  Settings* mysettings = Settings::getHubSettings();
  mysettings->readSettings("test.sh");

  auto refBuilder = Gtk::Builder::create();

  try
  {
    refBuilder->add_from_file("hub.glade");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const  Glib::MarkupError & ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }

  refBuilder->get_widget("hubappwindow", hubwin);
  refBuilder->get_widget("gdialog",hubDialog);

  if(hubwin)
  {
    refBuilder->get_widget("videobutton",vidButton);
    if(vidButton)
    {
      refBuilder->get_widget("videocombo",vidCombo);
      vidButton->signal_clicked().connect(sigc::ptr_fun(on_vidbutton_clicked));
    }

    refBuilder->get_widget("pollbutton", pollButton);
    if(pollButton)
    {
      refBuilder->get_widget("currenttempentry", tempEntry);
      pollButton->signal_clicked().connect(sigc::ptr_fun(on_pollbutton_clicked));
    }

    refBuilder->get_widget("minmaxbutton", minmaxButton);
    if(minmaxButton)
    {
      refBuilder->get_widget("minentry", minEntry);
      refBuilder->get_widget("maxentry", maxEntry);
      minmaxButton->signal_clicked().connect(sigc::ptr_fun(on_minmaxbutton_clicked));
    }

    refBuilder->get_widget("garagebutton", garageButton);
    if(garageButton)
    {
      garageButton->signal_clicked().connect(sigc::ptr_fun(on_garageButton_changed));
    }

    refBuilder->get_widget("lightbutton", lightButton);
    if(lightButton)
    {
      lightButton->signal_clicked().connect(sigc::ptr_fun(on_lightswitch_changed));
    }

    refBuilder->get_widget("autobutton", autoButton);
    if(autoButton)
    {
      int lControlStatus;
      std::string controlpath(homedir);
      controlpath += "/shares/lightshare/lightControlStatus";
      std::ifstream infile(controlpath);
      while (infile >> lControlStatus)
      {
        if(lControlStatus == 1)
        {
          autoButton->set_active(false);
        }
        else
        {
          autoButton->set_active();
        }
      }
      autoButton->signal_toggled().connect(sigc::ptr_fun(on_autoswitch_changed));
    }

    app->run(*hubwin);
  }
  delete hubwin;
  return 0;

}
