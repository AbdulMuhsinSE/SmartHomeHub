#include <gtkmm.h>
#include <iostream>
#include <glibmm/ustring.h>
#include "settings.hpp"

Gtk::ApplicationWindow* hubwin = nullptr;
Gtk::Button* vidButton;
Gtk::ComboBoxText* vidCombo;
Gtk::Button* pollButton;
Gtk::Button* minmaxButton;
Gtk::Entry* tempEntry;
Gtk::Entry* minEntry;
Gtk::Entry* maxEntry;
Gtk::Switch* garageSwitch;
Gtk::Switch* lightSwitch;


static void on_vidbutton_clicked()
{
  if(vidCombo)
  {
    std::string vid = (vidCombo->get_active_text()).raw();
    std::cout << vid << std::endl;
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
    std::cout << "The heater will turn on at: " << min << ".\nThe air conditioner will turn on at: " << max << std::endl;
  }
}

static void on_garageswitch_changed()
{
  if(garageSwitch)
  {
    std::cout << garageSwitch->get_active() << std::endl;
  }
}

static void on_lightswitch_changed()
{
  if(lightSwitch)
  {
    std::cout << lightSwitch->get_active() << std::endl;
  }
}

int main(int argc, char* argv[])
{
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

    refBuilder->get_widget("garageswitch", garageSwitch);
    if(garageSwitch)
    {
      garageSwitch->property_active().signal_changed().connect(sigc::ptr_fun(on_garageswitch_changed));
    }

    refBuilder->get_widget("lightswitch", lightSwitch);
    if(lightSwitch)
    {
      lightSwitch->property_active().signal_changed().connect(sigc::ptr_fun(on_lightswitch_changed));
    }

    app->run(*hubwin);
  }
  delete hubwin;
  return 0;

}
