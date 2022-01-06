#pragma once

struct Vector3Df
{
  float x,y,z;

  // Default constructor that allows for declaration without assigning values
  // This is needed because we will define another constructor that allows for assigning values
  // If one constructor is defined the default one isn't generated
  Vector3Df() = default;

  Vector3Df(float a, float b, float c)
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

struct Vector2Df
{
  float x,y;

  // Default constructor that allows for declaration without assigning values
  // This is needed because we will define another constructor that allows for assigning values
  // If one constructor is defined the default one isn't generated
  Vector2Df() = default;

  Vector2Df(float a, float b)
  {
    x = a;
    y = b;
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

struct Vector2Di
{
  int x,y;

  // Default constructor that allows for declaration without assigning values
  // This is needed because we will define another constructor that allows for assigning values
  // If one constructor is defined the default one isn't generated
  Vector2Di() = default;

  Vector2Di(int a, int b)
  {
    x = a;
    y = b;
  }

  int& operator [](int i)
  {
    return ((&x)[i]);
  }

  const int& operator [](int i) const
  {
    return ((&x)[i]);
  }
};
