Experiments
===========

This repository contains a collection of sample code that was useful
for prototype purposes during the course of developing lumail2.


colour-string
-------------

A sample program to demonstrate how I think I can split up strings
with embedded colour-information within them.  We need to be able
to change the colour before drawing each "segment".


dynamic-calling
---------------

I'm comfortable with wrapping C++ objects, such that they are callable
by lua, and I'm also comfortable invoking methods in Lua, from C++ code.

This example covers the case where:

* A C++ object is wrapped to Lua.
* This means the object is available to Lua via a user-data table.
* The Lua-side defines an __additional__ method, to extend the object.
* That method needs to be called by C++.


mime
----

A basic example of using `libmagic` to determine the MIME-type of
a file, via content.


observer
--------

Mock-up of a "Observer" pattern implementation which will suit
lumail2.


ui-demo
-------

A simple `ncurses` program with a toggleable "status-panel".



