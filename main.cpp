#include <gtkmm.h>
#include <iostream>

Gtk::ApplicationWindow* hubwin = nullptr;

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
    app->run(*hubwin);
  }
  delete hubwin;
  return 0;

}
