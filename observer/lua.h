
#include "config.h"
#include "singleton.h"
#include "observer.h"


/**
 * This class roughly approximates the Lumail 2 Lua-class.
 *
 * It is a singleton.
 *
 * It is also an observer, of the configuration-holding class
 * CConfig.
 *
 */
class CLua : public Singleton<CLua> , public Observer
{
public:

  /*
   * Constructor - Register with the object we're watching.
   */
 CLua() : Observer(CConfig::instance()) {};

  /*
   * Destructor.
   */
  ~CLua() {};

    /*
     * This is called via the observer-pattern.
     */
    void update(std::string name)
    {
        CConfig *c = CConfig::instance();

        std::cout << "Lua sees Key changed: " << name << std::endl;
        std::cout << "\tNew value " << c->get(name) << std::endl;
    }

};
