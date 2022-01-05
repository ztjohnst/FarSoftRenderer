#pragma once

struct Vector3D
{
  float x,y,z;

  // Default constructor that allows for declaration without assigning values
  // This is needed because we will define another constructor that allows for assigning values
  // If one constructor is defined the default one isn't generated
  Vector3D() = default;

  Vector3D(float a, float b, float c)
  {
    x = a;
    y = b;
    z = c;
  }

  float& operator [](int i)
  {
    return ((&x)[i]);
  }

  const float& operator [](int i) const
  {
    return ((&x)[i]);
  }
};
