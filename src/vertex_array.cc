#include "vertex_array.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../tinyobjloader/tiny_obj_loader.h"

VertexArray::VertexArray(Vertices const & vertices, Indices const & indices)
: vertices_(vertices),
  indices_(indices) {
  bind_buffer();
}

VertexArray::VertexArray(Vertices && vertices, Indices && indices)
: vertices_(std::move(vertices)),
  indices_(std::move(indices)) {
  bind_buffer();
}

VertexArray::VertexArray(std::string const & filepath) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn;
  std::string err;
  auto ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str());

  if (!warn.empty()) {
    std::cout << "tinyobj::LoadObj() reported warnings: " << warn << std::endl;
  }

  if (!err.empty()) {
    std::cerr << "tinyobj::LoadObj() failed: " << err << std::endl;
    return;
  }

  if (!ret) {
    std::cerr << "tinyobj::LoadObj() failed." << std::endl;
    return;
  }

  {
    auto const v_count = attrib.vertices.size();
    auto const n_count = attrib.normals.size();
    auto const t_count = attrib.texcoords.size();
    auto vec3_count = v_count / 3;

    vertices_.resize(vec3_count);
    auto i = 0u;
    auto iv = 0u;
    auto in = 0u;
    auto it = 0u;
    while (iv < v_count &&
           i < vec3_count) {
      auto const vx = attrib.vertices[iv];
      auto const vy = attrib.vertices[iv + 1];
      auto const vz = attrib.vertices[iv + 2];
      iv += 3;

      auto const has_normal = in < n_count;
      auto const nx = has_normal ? attrib.normals[in] : 0.0f;
      auto const ny = has_normal ? attrib.normals[in + 1] : 0.0f;
      auto const nz = has_normal ? attrib.normals[in + 2] : 0.0f;
      in += 3;

      auto const has_texcoord = it < t_count;
      auto const tx = has_texcoord ? attrib.texcoords[it] : 0.0f;
      auto const ty = has_texcoord ? attrib.texcoords[it + 1] : 0.0f;
      it += 2;

      vertices_[i] = Vertex{
        {vx, vy, vz},
        {nx, ny, nz},
        {tx, ty}
      };

      // std::cout << "DEBUG: i=" << i << std::endl;
      i++;
    }
  }

  {
    if (shapes.empty()) {
      std::cerr << "tinyobj::LoadObj() returned no shapes." << std::endl;
      return;
    }

    auto const & shape = shapes[0];
    if (shape.mesh.num_face_vertices.empty()) {
      std::cerr << "tinyobj::LoadObj() returned a shape with no face." << std::endl;
      return;
    }

    auto const & mesh = shape.mesh;

    auto const count = mesh.indices.size();
    indices_.resize(count);
    for (auto i = 0u;  i < count; ++i) {
      auto const & item = mesh.indices[i];
      indices_[i] = item.vertex_index;
    }
  }

  bind_buffer();
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &id_);
}

void VertexArray::bind_buffer() {
  glGenVertexArrays(1, &id_);

  {
    glBindVertexArray(id_);

    glBindBuffer(GL_ARRAY_BUFFER, buffer_vertices_.id());
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices_.size(), &vertices_[0], GL_STATIC_DRAW);

    // Describe the arrangement of bytes in the Vertex:
    // These same attribute ids are used later in the call to
    // glBindAttribLocation().
    glEnableVertexAttribArray(AttributeID::POSITION);
    glVertexAttribPointer(AttributeID::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position_)));

    glEnableVertexAttribArray(AttributeID::NORMAL);
    glVertexAttribPointer(AttributeID::NORMAL, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal_)));

    glEnableVertexAttribArray(AttributeID::TEXTURE_POS);
    glVertexAttribPointer(AttributeID::TEXTURE_POS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texture_pos_)));

    glBindVertexArray(0);
  }

  {
    glBindVertexArray(id_);

    // GL_ELEMENT_ARRAY_BUFFER means that these values reference items in
    // another array.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_indices_.id());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices::value_type) * indices_.size(), &indices_[0], GL_STATIC_DRAW);

    // Describe the arrangement of bytes in the Vertex:
    // These same attribute ids are used later in the call to
    // glBindAttribLocation().
    glEnableVertexAttribArray(AttributeID::INDEX);
    glVertexAttribPointer(AttributeID::INDEX, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
  }
}

void VertexArray::draw_triangles() const {
  glBindVertexArray(id_);

  // We draw by specifying the indices instead of the elements directly (with
  // glDrawArrays()).
  // TODO: How does OpenGL know that these are indices into the other buffer's data?
  glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
