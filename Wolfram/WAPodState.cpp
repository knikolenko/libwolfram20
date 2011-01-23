/*
 *      WAPodState.cpp
 *
 *      Copyright 2011 Nikolenko Konstantin <knikolenko@yandex.ru>
 *
 */

#include "WAPodState.h"

WAPodState::WAPodState()
{
    //ctor
}

WAPodState::~WAPodState()
{
    //dtor
}

/**
 * Returning a 'name' attribute of state
 *
 * @return Name of image
 */
string
WAPodState::getName()
{
    return string(name);
}

/**
 * Returning a 'input' attribute of state
 *
 * @return Input of image
 */
string
WAPodState::getInput()
{
    return string(input);
}

/**
 * Parsing a input 'state' xml node
 *
 * @param   states XML Node of state
 * @return  false, if error
 */
bool
WAPodState::Parse(xml_node<>* states)
{
    // Reading attribute
    name    = states->first_attribute("name")->value();
    input   = states->first_attribute("input")->value();
    return true;
}
