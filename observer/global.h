
#include "config.h"
#include "singleton.h"
#include "observer.h"


/**
 * This class roughly approximates the Lumail 2 global-state
 * class.
 *
 * It is a singleton.
 *
 * It is also an observer, of the configuration-holding class
 * CConfig.
 *
 */
class CGlobal : public Singleton<CGlobal> , public Observer
{
public:

  /*
   * Constructor - Register with the object we're watching.
   */
 CGlobal() : Observer(CConfig::instance()) {};

  /*
   * Destructor.
   */
  ~CGlobal() {};

    /*
     * This is called via the observer-pattern.
     */
    void update(std::string name)
    {
        CConfig *c = CConfig::instance();

        std::cout << "Global sees key changed: " << name << std::endl;
        std::cout << "\tNew value " << c->get(name) << std::endl;
    }

};
