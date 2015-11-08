#pragma once

#include <vector>
#include <string>


/**
 * This is the subject-class for the observer-pattern.
 *
 * This class-interface allows watchers to register themselves
 * via the `attach` method - and then they will be updated
 * whenever something changes.
 */
class Subject
{
public:
    std::vector < class Observer * > views;

public:
    /**
     * Attach a new observer to this subject.
     */
    void attach(Observer *obs)
    {
        views.push_back(obs);
    };

};




/**
 * This interface allows a class to be notified of a change
 * in state, via our subject-class.
 *
 * It is a simplified class, because we don't keep a reference
 * to the subject, instead we broadcast the changed item directly.
 */
class Observer
{
public:

  /**
   * Constructor.
   *
   * Call this with a reference to the subject you wish to be watching.
   *
   * When a change is made then the update-method will be called later.
   */
    Observer(Subject *mod)
    {
        mod->attach(this);
    }

    /**
     * This is the virtual function sub-classes much implement to
     * be notified of key-changes.
     */
    virtual void update(std::string name) = 0;

};
