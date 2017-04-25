#include <gtkmm.h>
#include <iostream>
#include <glibmm/ustring.h>
#include "settings.hpp"

Gtk::ApplicationWindow* hubwin = nullptr;
Gtk::Button* vidButton;
Gtk::ComboBoxText* vidCombo;
Gtk::Button* pollButton;
Gtk::Entry* tempEntry;


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

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example.base");

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

    app->run(*hubwin);
  }
  delete hubwin;
  return 0;

}