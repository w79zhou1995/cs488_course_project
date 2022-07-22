// Fall 2018                                                                                               

#include <iostream>
#include <fstream>

#include <glm/ext.hpp>
#include <map>
#include <string>
#include <random>
#include <stdlib.h>
#include <time.h>
// #include "cs488-framework/ObjFileDecoder.hpp"                                                           
#include "Cloth.hpp"
float TIME_STEP = 0.01;
int TIME = 500;
float k = 2;
float damping = 0.01;
//glm::vec3 GRAVITY = glm::vec3(0, -5, 0); 
char MODE = 'c';

Cloth::Cloth (int N, std::string geometry, glm::vec3 center, float r, float softness) {
  m_max = glm::vec3(N, 0, N);
  m_min = glm::vec3(0, 0, 0);
  glm::vec3 GRAVITY = glm::vec3(0, -softness, 0);


  // add vertices  
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      glm::vec3 V = glm::vec3(j, 0, i);
      m_vertices.push_back(V);
      m_last.push_back(V);
      m_vnorms.push_back(glm::vec3(0));
      m_facecount.push_back(0);
      m_masses.push_back(1);
      m_forces.push_back(glm::vec3(0));
      m_acc.push_back(glm::vec3(0));
      m_movable.push_back(true);
    }
  }

  // add faces
  for (int i = 0; i < N-1; ++i) {
    for (int j = 0; j < N-1; ++j) {
      m_faces.push_back( Triangle(j+i*N, j+i*N+N, j+i*N+1) );
      //glm::vec3 n = glm::normalize(glm::cross(m_vertices[j+i*N+N] - m_vertices[j+i*N],
      //			    m_vertices[j+i*N+1]- m_vertices[j+i*N]));
      //std::cout<< j+i*N << " " << j+i*N+N << " " << j+i*N+1 << std::endl;
      /*
      m_vnorms[j+i*N] += n;
      ++m_facecount[j+i*N];
      m_vnorms[j+i*N+N] += n;
      ++m_facecount[j+i*N+N];
      m_vnorms[j+i*N+1] += n;
      ++m_facecount[j+i*N+1];
      */
      m_faces.push_back( Triangle(j+i*N+N, j+i*N+N+1, j+i*N+1) );
      //n = glm::normalize(glm::cross(m_vertices[j+i*N+N+1] - m_vertices[j+i*N+N],
      //                            m_vertices[j+i*N+1]- m_vertices[j+i*N+N]));
      /*m_vnorms[j+i*N+N] += n;
      ++m_facecount[j+i*N+N];
      m_vnorms[j+i*N+N+1] += n;
      ++m_facecount[j+i*N+N+1];
      m_vnorms[j+i*N+1] += n;
      ++m_facecount[j+i*N+1];
      */
      //std::cout<< j+i*N+N<< " " << j+i*N+N+1 << " " << j+i*N+1 << std::endl;
    }
  }

  // average face normals
  for (int i = 0; i < N*N; ++i) {
    //std::cout << m_vnorms[i][0] << ", " <<  m_vnorms[i][1] << ", " << m_vnorms[i][2] << std::endl; 
    //m_vnorms[i] /= m_facecount[i];
  }

  //std::cout << std::endl;

  // add structural constraints
  for (int i = 0; i < N-1; ++i) {
    for (int j = 0; j < N-1; ++j) {
      m_springs.push_back( Constraint(j+i*N, j+i*N+1, glm::length(m_vertices[j+i*N] - m_vertices[j+i*N+1])) );  
      //std::cout << j+i*N << " " << j+i*N+1 <<std::endl;
      m_springs.push_back( Constraint(j+i*N, j+i*N+N, glm::length(m_vertices[j+i*N] - m_vertices[j+i*N+N])) );
      //std::cout << j+i*N << " " << j+i*N+N << std::endl;
    }
  }
  
  //std::cout << std::endl;
  
  // add shear constraints
  for (int i = 0; i < N-1; ++i) {
    for (int j = 0; j < N-1; ++j) {
      m_springs.push_back( Constraint(j+i*N, j+i*N+N+1, glm::length(m_vertices[j+i*N] - m_vertices[j+i*N+N+1])) );
      //std::cout << j+i*N << " " << j+i*N+N+1 << std::endl;
      m_springs.push_back( Constraint(j+i*N+N, j+i*N+1, glm::length(m_vertices[j+i*N+N] - m_vertices[j+i*N+1])) );
      //std::cout << j+i*N+N << " " << j+i*N+1 << std::endl;
    }
  }

  //std::cout << std::endl;
  
  for (int i = 0; i < N-2; ++i) {
    for (int j = 0; j < N-2; ++j) {
      m_springs.push_back( Constraint(j+i*N, j+i*N+2, glm::length(m_vertices[j+i*N] - m_vertices[j+i*N+2])) );
      //std::cout << j+i*N << " " << j+i*N+2 <<std::endl;
      m_springs.push_back( Constraint(j+i*N, j+i*N+2*N, glm::length(m_vertices[j+i*N] - m_vertices[j+i*N+2*N])) );
      //std::cout << j+i*N << " " << j+i*N+2*N << std::endl;
      m_springs.push_back( Constraint(j+i*N, j+i*N+2*N+2, glm::length(m_vertices[j+i*N] - m_vertices[j+i*N+2*N+2])) );
      //std::cout << j+i*N << " " << j+i*N+2*N+2 << std::endl;
      m_springs.push_back( Constraint(j+i*N+2*N, j+i*N+2, glm::length(m_vertices[j+i*N+2*N] - m_vertices[j+i*N+2])) );
      //std::cout << j+i*N+2*N << " " << j+i*N+2 << std::endl;
    }
  }


  // intersect with a cap
  if (geometry == "cap") {
    for (int i = 0; i < N * N; ++i) {
      if (glm::length(m_vertices[i] - center) < r) {
	    pin(i);
      }
    }
  }

  if (geometry == "hang" || geometry == "ball") {
    //pin(0);
    //pin(N);
    //pin(N-2);
    //pin(N-1);
  }

  if (geometry == "paper") {
    for (int i = 0; i < N * N; ++i) {
      pin(i);
    }
  }

  for (int t = 0; t < TIME; ++t) {
    if (MODE == 'c') {
 
      for (int i = 0; i < N * N; ++i) {
          // apply gravity
          add_force(GRAVITY, i);

          apply_force(i);

      }

      check_constraints();

      for (int i = 0; i < N * N; ++i) {
        move_vertex(i);
      }


      for (int i = 0; i < N * N; ++i) {
	glm::vec3 circle_center;

	if (geometry == "cap") {
	  circle_center = glm::vec3(center[0],  m_vertices[i][1], center[2]);
	}
	else if (geometry == "ball") {
	  circle_center = center;
	}
	else { continue; }

	glm::vec3 to_center = m_vertices[i] - circle_center;
	float distance = glm::length(to_center);
	if (distance < r && m_movable[i]) {
	  m_vertices[i] = m_vertices[i] + glm::normalize(to_center) * (r-distance);
	}
      }
      //check_constraints();
      /*

      if (geometry == "ball") {
	//std::cout << "checking ball collision" << std::endl;
	for (int i = 0; i < N * N; ++i) {
	  collision (center, r, i);
	}
      }
      */

    }

    /*
    else if (MODE == 's') {
      for (int i = 0; i < N * N; ++i) {
	      // apply gravity
          add_force(GRAVITY, i);

          for (Constraint con : m_springs) {
              if (i == con.v1) {
                  glm::vec3 V1 = m_vertices[i];
                  glm::vec3 V2 = m_vertices[con.v2];
                  glm::vec3 x = V2 - V1;
                  float x_cur = glm::length(x);
                  glm::vec3 spring_force = k * (x_cur - con.initial) * glm::normalize(x);
                  add_force(spring_force, i);
              }
              else if (i == con.v2) {
                  glm::vec3 V1 = m_vertices[i];
                  glm::vec3 V2 = m_vertices[con.v1];
                  glm::vec3 x = V2 - V1;
                  float x_cur = glm::length(x);
                  glm::vec3 spring_force = k * (x_cur -con.initial) * glm::normalize(x);
                  add_force(spring_force, i);
              }
          }

          apply_force(i);
      }

      for (int i = 0; i < N * N; ++i) {
	bool collision_check = false;

        move_vertex(collision_check, center, r, i);
      }
    }
    */
  }

  /*
  for (int i = 0; i < N * N; ++i) {
    std::cout << m_vertices[i][0] << " " << m_vertices[i][1] << " " << m_vertices[i][2] << std::endl;
  }
  */
  for (Triangle tri : m_faces) {
    glm::vec3 n = glm::normalize(glm::cross(m_vertices[tri.v2] - m_vertices[tri.v1],
					    m_vertices[tri.v3] - m_vertices[tri.v1]));
    m_vnorms[tri.v1] += n;
    ++m_facecount[tri.v1];
    m_vnorms[tri.v2] += n;
    ++m_facecount[tri.v2];
    m_vnorms[tri.v3] += n;
    ++m_facecount[tri.v3];
  }

  for (int i = 0; i < N*N; ++i) {
    m_vnorms[i] /= m_facecount[i];
  }

  glm::vec3 cur_max = m_vertices[0];
  glm::vec3 cur_min = m_vertices[0];
  for (glm::vec3 v : m_vertices) {
    if (v[0] > cur_max[0]) {cur_max[0] = v[0];}
    if (v[1] > cur_max[1]) {cur_max[1] = v[1];}
    if (v[2] > cur_max[2]) {cur_max[2] = v[2];}
    if (v[0] < cur_min[0]) {cur_min[0] = v[0];}
    if (v[1] < cur_min[1]) {cur_min[1] = v[1];}
    if (v[2] < cur_min[2]) {cur_min[2] = v[2];}
  }
  m_max = cur_max;
  m_min = cur_min;
  
}


void Cloth::apply_force(int index) {
  m_acc[index] = m_forces[index] / m_masses[index];
  m_forces[index] = glm::vec3(0);
}

void Cloth::add_force(glm::vec3 force,int index) {
  m_forces[index] += force;  
}

void Cloth::move_vertex(int index) {

  if (!m_movable[index]) { return; }
  // x_t+1 = x_t + v * t + a * t * t 
  glm::vec3 temp = m_vertices[index];
  m_vertices[index] = m_vertices[index] + (m_vertices[index] - m_last[index])*(1.0 - damping) + m_acc[index] * TIME_STEP;

  /*
  if (collision_check) {
    glm::vec3 to_center = m_vertices[index] - center;
    if (glm::length(to_center) < r) {
      m_vertices[index] += glm::normalize(to_center) * (r - glm::length(to_center));
    }
  }
  */

  m_last[index] = temp;

}

void Cloth::collision (std::string geometry, glm::vec3 center, float r, int index) {
  glm::vec3 to_center = m_vertices[index] - center;
  float distance = glm::length(to_center);
  if (distance < r) {
    m_vertices[index] = m_vertices[index] + glm::normalize(to_center) * (r-distance);
  }
}

void Cloth::check_constraints() {
  for (Constraint con : m_springs) {
    glm::vec3 x = m_vertices[con.v2] - m_vertices[con.v1]; 
    float cur_x = glm::length(x);
    /*
    if (m_movable[con.v1]) { 
      m_vertices[con.v1] += x * (1 - con.initial/cur_x) / 2;
    }
    if (m_movable[con.v2]) {
      m_vertices[con.v2] -= x * (1 - con.initial/cur_x) / 2;
    }
    return;
    */
    
    if (m_movable[con.v1]) {
      if (m_movable[con.v2]) {
	m_vertices[con.v1] += x * (1 - con.initial/cur_x) / 2;
	m_vertices[con.v2] -= x * (1 - con.initial/cur_x) / 2;
      } 
      else {
	m_vertices[con.v1] += x * (1 - con.initial/cur_x);
      }
    } else {
      if (m_movable[con.v2]) {
	m_vertices[con.v2] -= x * (1 - con.initial/cur_x);
      }
    }
  }
}

void Cloth::pin(int index) {
  m_movable[index] = false;
}
