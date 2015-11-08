#include <algorithm>
#include <assert.h>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <unistd.h>

#include "global.h"
#include "lua.h"
#include "config.h"


int main(int argc, char *argv[])
{
    CGlobal *global = CGlobal::instance();
    CLua    *lua    = CLua::instance();
    CConfig *config = CConfig::instance();


    std::cerr << "The value of 'foo' is" << config->get("foo") << std::endl;

    config->set("cat", "meow", true);
    config->set("dog", "woof", true);
    config->set("leon", "assassin", true);

    return 1;
}
