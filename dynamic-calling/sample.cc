/**
 * This is an example of a C++ object which is exported to Lua.
 *
 * The Lua code calls some C++, and vice-versa.
 */


extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <iostream>
#include <string>


/**
 * Sample C++ object - this is wrapped and exported to Lua.
 */
class CSample
{
public:
    CSample() { };
    ~CSample() { };

public:
    std::string one()
    {
        return "one";
    }
    std::string two()
    {
        return "two";
    }
};



/**
 * Wrap the constructor to Lua.
 */
int l_CSample_constructor(lua_State * l)
{
    CSample **udata = (CSample **) lua_newuserdata(l, sizeof(CSample *));
    *udata = new CSample();

    luaL_getmetatable(l, "luaL_CSample");
    lua_setmetatable(l, -2);
    return 1;
}

/**
 * Ensure we have a CSample object on the stack.
 */
CSample * l_CheckSample(lua_State * l, int n)
{
    return *(CSample **) luaL_checkudata(l, n, "luaL_CSample");
}

/**
 * Wrap CSample:one();
 */
int l_CSample_one(lua_State * l)
{
    CSample *foo = l_CheckSample(l, 1);
    lua_pushstring(l, foo->one().c_str());
    return 1;
}

/**
 * Wrap CSample:two();
 */
int l_CSample_two(lua_State * l)
{
    CSample *foo = l_CheckSample(l, 1);
    lua_pushstring(l, foo->two().c_str());
    return 1;
}



/**
 * Driver.
 */
int main(int argc, char *argv[])
{
    /**
     * Setup defualt lua.
     */
    lua_State *m_lua = luaL_newstate();
    luaopen_base(m_lua);
    luaL_openlibs(m_lua);

    /**
     * Register our new "Sample" object.
     */
    luaL_Reg sFooRegs[] =
    {
        {"new", l_CSample_constructor},
        {"one", l_CSample_one},
        {"two", l_CSample_two},
        {NULL, NULL}
    };
    luaL_newmetatable(m_lua, "luaL_CSample");

#if LUA_VERSION_NUM == 501
    luaL_register(m_lua, NULL, sFooRegs);
#elif LUA_VERSION_NUM == 502
    luaL_setfuncs(m_lua, sFooRegs, 0);
#else
#error unsupported Lua version
#endif

    lua_pushvalue(m_lua, -1);
    lua_setfield(m_lua, -1, "__index");
    lua_setglobal(m_lua, "Sample");

    /**
     * Now load and execute the sample.lua file.
     */
    int err = luaL_dofile(m_lua, "sample.lua");

    if (err)
    {
        std::cerr << "Error loading file" << std::endl;
    }

    /**
     * At this point we've created a Sample object which has
     * two methods `one` and `two` which are defined in C++.
     *
     * Thanks to the definition in the file we've loaded we've
     * got `Sample:three` implemented in Lua.
     *
     * We want to call that method from C++
     */
    lua_getglobal(m_lua, "Sample");
    lua_getfield(m_lua, -1, "three");

    /**
     * Add a new CSample object to the stack.
     */
    l_CSample_constructor(m_lua);


    /**
     * Call the method.
     */

    if (lua_pcall(m_lua, 1, 1 , 0) != 0)
    {
        std::cerr << "Error calling Sample:three() - " << lua_tostring(m_lua, -1);
    }

    /**
     * Fingers crossed we now have the message.
     */
    if (lua_tostring(m_lua, -1) == NULL)
    {
        std::cerr << "NULL OUTPUT!!!1!! " << std::endl;
    }
    else
    {
        std::cerr << "Got output: " << lua_tostring(m_lua, -1) << std::endl;
    }

    return 0;
}
