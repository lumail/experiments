
#include "config.h"
#include "observer.h"


/**
 * Setup a default value.
 */
CConfig::CConfig()
{
    set("foo", "bar", false);
}

/**
 * Destructor.
 */
CConfig::~CConfig()
{
}

/**
 * Get the value of the configuration-value with the given name.
 */
std::string CConfig::get(std::string name)
{
    return (m_data[name]);
}

/**
 * Set the value of the configuration-value with the given name to be
 * the given value.
 */
void CConfig::set(std::string name, std::string value, bool notify)
{

    m_data[name] = value;

    /**
     * Notifying?  Update all our watchers.
     */
    if (notify)
      {
        for (int i = 0; i < views.size(); i++)
          views[i]->update(name);
      }
}
