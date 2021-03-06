#include "planet.hpp"
#include <iostream>

Planet::Planet()
{
    id = -1;
    pos_x = 0.0;
    pos_y = 0.0;
    vel_x = 0.0;
    vel_y = 0.0;
    mass = 0.0;
    force_x = 0.0;
    force_y = 0.0;
}

Planet::Planet(int ID, float PosX, float PosY, float VelX, float VelY, float Mass, string FileName)
{
    id = ID;
    pos_x = PosX;
    pos_y = PosY;
    vel_x = VelX;
    vel_y = VelY;
    mass = Mass;
    filename = FileName;
    force_x = 0.0;
    force_y = 0.0;
}

Planet::~Planet()
{

}

int Planet::get_id() const
{
    return id;
}

float Planet::get_pos_x() const
{
    return pos_x;
}

float Planet::get_pos_y() const
{
    return pos_y;
}

float Planet::get_vel_x() const
{
    return vel_x;
}

float Planet::get_vel_y() const
{
    return vel_y;
}

float Planet::get_force_x() const
{
    return force_x;
}

float Planet::get_force_y() const
{
    return force_y;
}

float Planet::get_mass() const
{
    return mass;
}

string Planet::get_filename() const
{
    return filename;
}

sf::Sprite* Planet::get_sprite()
{
    return &sprite;
}

//Mutators
void Planet::set_id(int ID)
{
    id = ID;
}

void Planet::set_pos_x(float PosX)
{
    pos_x = PosX;
}

void Planet::set_pos_y(float PosY)
{
    pos_y = PosY;
}

void Planet::set_vel_x(float VelX)
{
    vel_x = VelX;
}

void Planet::set_vel_y(float VelY)
{
    vel_y = VelY;
}

void Planet::set_force_x(float ForceX)
{
    force_x = ForceX;
}

void Planet::set_force_y(float ForceY)
{
    force_y = ForceY;
}

void Planet::add_to_force_x(float ForceX)
{
    force_x += ForceX;
}

void Planet::add_to_force_y(float ForceY)
{
    force_y += ForceY;
}

void Planet::set_mass(float Mass)
{
    mass = Mass;
}

void Planet::set_filename(string FileName)
{
    filename = FileName;
}

void Planet::set_sprite(sf::Sprite* Sprite)
{
    sprite = *Sprite;
}
