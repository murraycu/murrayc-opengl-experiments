#ifndef MURRAYC_OPENGL_EXPERIMENTS_VERTEX_ARRAY_H
#define MURRAYC_OPENGL_EXPERIMENTS_VERTEX_ARRAY_H

#include "buffer.h"
#include "vertex.h"
#include <GL/glew.h>
#include <vector>
#include <string>

class VertexArray {
public:
  using Vertices = std::vector<Vertex>;
  using Indices = std::vector<GLuint>;

  /**
   * @param vertices One entry for each vertex.
   * @param indices One index, referring to a position in @a vertices, for each
   * actual vertex in the mesh.
   */
  VertexArray(Vertices const & vertices, Indices const & indices);

  /**
   * @param vertices One entry for each vertex.
   * @param indices One index, referring to a position in @a vertices, for each
   * actual vertex in the mesh.
   */
  VertexArray(Vertices&& vertices, Indices&& indices);

  explicit VertexArray(std::string const & filepath);

  ~VertexArray();

  using ID = GLuint;

  ID id() const {
    return id_;
  }

  enum AttributeID{
    POSITION = 0,
    NORMAL,
    TEXTURE_POS,
    INDEX
  };

  void draw_triangles() const;

private:
  void bind_buffer();

  ID id_{};
  AttributeID id_attribute_position_;
  AttributeID id_attribute_texture_pos_;
  Buffer buffer_vertices_;
  Buffer buffer_indices_;
  Vertices vertices_;
  Indices indices_;
};

#endif // MURRAYC_OPENGL_EXPERIMENTS_VERTEX_ARRAY_H
