

#pragma once

#include <unordered_map>
#include <string>

#include "singleton.h"
#include "observer.h"


/*
 * Singleton to hold configuration variables.
 */
class CConfig : public Singleton<CConfig> , public Subject
{
public:
    CConfig();
    ~CConfig();

public:

    /*
     * Get the value associated with a name.
     */
    std::string get(std::string name);

    /*
     * Set a configuration key to contain the specified value.
     */
    void set(std::string name, std::string value, bool notify = false);

private:

    /*
     * The actual storage.
     */
    std::unordered_map < std::string, std::string > m_data;
};
