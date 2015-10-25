Experiments
===========

This repository contains a collection of sample code that was useful
for prototype purposes during the course of developing lumail2.



ui-demo
-------

A simple `ncurses` program with a toggleable "status-panel".


dynamic-calling
---------------

I'm comfortable with wrapping C++ objects, such that they are callable
by lua, and I'm also comfortable invoking methods in Lua, from C++ code.

This example covers the case where:

* A C++ object is wrapped to Lua.
* This means the object is available to Lua via a user-data table.
* The Lua-side defines an __additional__ method, to extend the object.
* That method needs to be called by C++.
