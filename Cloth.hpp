// Fall 2018                                                                                               

#pragma once

#include <vector>
#include <iosfwd>
#include <string>

#include <glm/glm.hpp>

#include "Mesh.hpp"

struct Constraint {
  int v1;
  int v2;
  float initial;

  Constraint(int pv1, int pv2, float len)
    : v1( pv1 )
    , v2( pv2 )
    , initial( len )
  {}

};

class Cloth : public Mesh {
 public:
  Cloth(int N, std::string geometry, glm::vec3 center, float r, float softness);

  void add_force(glm::vec3 force, int index);

  void apply_force(int index);
  
  void move_vertex(int index);

  void check_constraints();

  void pin(int index);
 
  void collision (std::string geometry, glm::vec3 center, float r, int index);

 private:

  std::vector<bool> m_movable;
  std::vector<glm::vec3> m_last;
  std::vector<float> m_masses;
  std::vector<glm::vec3> m_forces;
  std::vector<glm::vec3> m_acc;
  std::vector<Constraint> m_springs;
  std::vector<glm::vec3> m_normals; //Phong Shade 
};
