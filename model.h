#include <fstream>
#include <vector>
#include "vector.h"

struct Index
{
  int x;
  int y;
  int z;

  int& operator [](int i)
  {
    return ((&x)[i]);
  }

  const int& operator [](int i) const
  {
    return ((&x)[i]);
  }
};

class Model
{
  public:
    Model(const char* filepath);
    ~Model(){};

    std::vector<Vector3D> vertices;
    std::vector<Index> indices;
    

  private:
    std::ifstream f_obj;
    
};
