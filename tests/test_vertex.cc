#include <cstdlib>
//#include <functional>
#include "gtest/gtest.h"
#include <vertex.h>


TEST(Vertex, Simple) {
  auto const position = glm::vec3{1.0f, 2.2f, 3.3f};
  auto const texture_pos = glm::vec2{7.0f, 8.0f};

  auto const vertex = Vertex{
    position,
    texture_pos};

  EXPECT_EQ(position, vertex.position_);
  EXPECT_EQ(texture_pos, vertex.texture_pos_);
}

