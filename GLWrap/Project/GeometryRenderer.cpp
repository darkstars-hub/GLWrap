#include "GeometryRenderer.h"

#include "Helper.h"
#include "Application.h"
#include "ResourceManager.h"


bool my::GeometryRenderer::InitializeFillTriangle(void) {
    using Vertex = my::SimpleVertex;
    _pair_map.emplace("fill_triangle", Pair());
    auto& shader = _pair_map.at("fill_triangle").shader;
    auto& buffer = _pair_map.at("fill_triangle").buffer;
    // シェーダ
    shader = ::g_pResource->Get<std::shared_ptr<my::Shader>>("shader/colored.shader");
    

    // バッファ
    std::vector<my::SimpleVertex> vertices = {
    glm::vec3(-1.0f, -1.0f, 0.0f),
    glm::vec3(1.0f, -1.0f, 0.0f),
    glm::vec3(0.0f,  1.0f, 0.0f)
    };
    std::vector<uint32_t> indices = {
        0,1,2
    };
    // 生成
    buffer = my::VertexArray<my::SimpleVertex>(vertices, indices);
    buffer.Generate();
    buffer.ToTriangleStrip();
    return true;

}
bool my::GeometryRenderer::InitializeFillCircle(void) {
    using Vertex = my::SimpleVertex;
    _pair_map.emplace("fill_circle", Pair());
    auto& shader = _pair_map.at("fill_circle").shader;
    auto& buffer = _pair_map.at("fill_circle").buffer;
    // シェーダ
    shader = ::g_pResource->Get<std::shared_ptr<my::Shader>>("shader/circle.shader");
    // バッファ
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    vertices.push_back(Vertex());
    for (uint32_t i = 1, n = 256 + 1; i <= n + 1; i++) {
        float rate = static_cast<float>(i) / static_cast<float>(n);
        auto pos = glm::vec2(std::cosf(2.0f * def::kPi * rate),
                             std::sinf(2.0f * def::kPi * rate));
        // 頂点作成
        auto ver = Vertex();
        ver.position = glm::vec3(pos.x, pos.y, 0.0f);
        vertices.push_back(ver);
        indices.push_back(i);
        indices.push_back(0);
    } // for

    // 生成
    buffer = my::VertexArray<Vertex>(vertices, indices);
    buffer.Generate();
    buffer.ToTriangleStrip();
    return true;
}

bool my::GeometryRenderer::InitializeLineCircle(void) {
    using Vertex = my::SimpleVertex;
    _pair_map.emplace("line_circle", Pair());
    auto& shader = _pair_map.at("line_circle").shader;
    auto& buffer = _pair_map.at("line_circle").buffer;

    // シェーダ
    shader = ::g_pResource->Get<std::shared_ptr<my::Shader>>("shader/circle.shader");

    // バッファ
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    for (uint32_t i = 0, n = 256; i <= n; i++) {
        float rate = static_cast<float>(i) / static_cast<float>(n);
        auto pos = glm::vec2(std::cosf(2.0f * def::kPi * rate),
                             std::sinf(2.0f * def::kPi * rate));
        // 頂点作成
        auto ver = Vertex();
        ver.position = glm::vec3(pos.x, pos.y, 0.0f);
        vertices.push_back(ver);
        indices.push_back(i);
    } // for

    // 生成
    buffer = my::VertexArray(vertices, indices);
    buffer.Generate();
    buffer.ToLineStrip();
    return true;
}
bool my::GeometryRenderer::InitializeFillRectangle(void) {
    _pair_map.emplace("fill_rectangle", Pair());
    auto& shader = _pair_map.at("fill_rectangle").shader;
    auto& buffer = _pair_map.at("fill_rectangle").buffer;
    // シェーダ
    shader = ::g_pResource->Get<std::shared_ptr<my::Shader>>("shader/colored.shader");

    return true;
}
my::GeometryRenderer::GeometryRenderer() {
}
my::GeometryRenderer::~GeometryRenderer() {
}

bool my::GeometryRenderer::Initialize(void) {
    if (!this->InitializeFillTriangle()) {
        return false;
    } // if
    if (!this->InitializeFillCircle()) {
        return false;
    } // if
    if (!this->InitializeLineCircle()) {
        return false;
    } // if
    if (!this->InitializeFillRectangle()) {
        return false;
    } // if
    return true;
}

bool my::GeometryRenderer::Release(void) {
    for (auto& pair : _pair_map) {
        //pair.second.shader.Release();
        pair.second.shader.reset();
        pair.second.buffer.Delete();
    } // for
    return true;
}

bool my::GeometryRenderer::RenderFillTriangle(glm::vec3 position, glm::quat rotate, glm::vec3 scale, glm::vec4 color, glm::mat4 view, glm::mat4 proj) {
    auto shader = _pair_map.at("fill_triangle").shader.lock();
    auto& vertex = _pair_map.at("fill_triangle").buffer;
    auto translation = glm::translate(glm::identity<glm::mat4>(), position);
    auto rotation = glm::toMat4(rotate);
    auto scaling = glm::scale(glm::identity<glm::mat4>(), scale);
    auto transform = translation * rotation * scaling;
    // セット
    shader->Enable();
    shader->SetVector4Uniform("uniform_color", color);
    shader->SetMatrixUniform("transform", transform);
    shader->SetMatrixUniform("view", view);
    shader->SetMatrixUniform("proj", proj);
    // 描画
    vertex.Bind();
    vertex.Render();
    shader->Disable();
    return true;
}

bool my::GeometryRenderer::RenderFillCircle(const my::Circle& circle, glm::vec4 color, glm::mat4 view, glm::mat4 proj) {
    auto shader = _pair_map.at("fill_circle").shader.lock();
    auto& vertex = _pair_map.at("fill_circle").buffer;
    auto translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(circle.position, 0.0f));
    auto transform = translation;
    // セット
    shader->Enable();
    shader->SetFloatUniform("radius", circle.radius);
    shader->SetVector4Uniform("uniform_color", color);
    shader->SetMatrixUniform("transform", transform);
    shader->SetMatrixUniform("view", view);
    shader->SetMatrixUniform("proj", proj);

//    shader->SetMatrixUniform("view_projection", view_proj);
    // 描画
    vertex.Bind();
    vertex.Render();
    shader->Disable();
    return true;
}

bool my::GeometryRenderer::RenderLineCircle(const my::Circle& circle, glm::vec4 color, glm::mat4 view, glm::mat4 proj) {
    auto shader = _pair_map.at("line_circle").shader.lock();
    auto& vertex = _pair_map.at("line_circle").buffer;
    auto translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(circle.position, 0.0f));
    auto transform = translation;
    // セット
    shader->Enable();
    shader->SetFloatUniform("radius", circle.radius);
    shader->SetVector4Uniform("uniform_color", color);
    shader->SetMatrixUniform("transform", transform);
  
    shader->SetMatrixUniform("view", view);
    shader->SetMatrixUniform("proj", proj);
//  shader->SetMatrixUniform("view_projection", view_proj);
    // 描画
    vertex.Bind();
    vertex.Render();
    shader->Disable();
    return true;
}

bool my::GeometryRenderer::RenderFillRectangle(const my::Rectangle& rectangle, glm::vec4 color, glm::mat4 view, glm::mat4 proj) {
    auto shader = _pair_map.at("fill_rectangle").shader.lock();
    auto transform = glm::identity<glm::mat4>();
    shader->Enable();
    shader->SetVector4Uniform("uniform_color", color);
    shader->SetMatrixUniform("transform", transform);

    shader->SetMatrixUniform("view", view);
    shader->SetMatrixUniform("proj", proj);

    my::VertexArray<SimpleVertex> buffer;
    // バッファ
    std::vector<my::SimpleVertex> vertices(4);
    std::vector<uint32_t> indices(6);
    // 頂点作成
    vertices.at(0) = (my::SimpleVertex(glm::vec2(rectangle.left, rectangle.top))); // left top
    vertices.at(3) = (my::SimpleVertex(glm::vec2(rectangle.right, rectangle.top))); // right top
    vertices.at(2) = (my::SimpleVertex(glm::vec2(rectangle.right, rectangle.bottom))); // right bottom
    vertices.at(1) = (my::SimpleVertex(glm::vec2(rectangle.left, rectangle.bottom))); // left bottom
    indices.at(0) = (0); indices.at(1) = (1); indices.at(2) = (2);
    indices.at(3) = (2); indices.at(4) = (3); indices.at(5) = (0);

    // 生成
    buffer = my::VertexArray(vertices, indices);
    buffer.Generate();
    buffer.ToTriangles();
    // 描画
    buffer.Bind();
    buffer.Render();
    // 解放
    buffer.Delete();
    shader->Disable();
    return true;
}
