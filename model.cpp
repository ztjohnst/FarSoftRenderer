#include "model.h"
#include <sstream>
#include <string>
#include <stdio.h>

Model::Model(const char* filepath)
{
  f_obj.open(filepath);

  std::string line;
  std::string vr = "v ";
  std::string fr = "f ";
  while(std::getline(f_obj, line))
  {
    size_t v_pos = line.find("v ");
    if(v_pos != std::string::npos)
    {
      line.replace(v_pos, vr.length(), "");
      printf("%s\n", line.c_str());
      std::istringstream iss(line);  
      Vector3D v;
      iss >> v.x;
      //v.x *= -1;
      iss >> v.y;
      v.y *= -1;
      iss >> v.z;
      printf("Vertices:\n");
      printf("X: %.6f Y: %.6f Z: %.6f\n", v.x, v.y, v.z); 
      vertices.push_back(v);
    }
    size_t f_pos = line.find("f ");
    if(f_pos != std::string::npos)
    {
      line.replace(f_pos, fr.length(), "");
      printf("%s\n", line.c_str());
      std::istringstream iss(line);  
      char trash;
      int itrash;
      int i;
      Index ind;
      printf("Indices:\n");
      int j = 0;
      while(iss >> i >> trash >> itrash >> trash >> itrash)
      //while(iss >> i >> trash >> trash >> itrash)
      {
        i--; // Waveform obj files start at 1
        printf("I: %d\n", i);
        ind[j] = i;
        j++;
      }
      indices.push_back(ind);
    }
  }

  f_obj.close();
}
