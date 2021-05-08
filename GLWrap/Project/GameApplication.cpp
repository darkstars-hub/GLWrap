#include "GameApplication.h"

#include "Helper.h"
#include "Application.h"
#include "InputManager.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Texture.h"
#include "Collision.h"
#include "SpriteAnimation.h"
#include "Font.h"


my::Transform world(glm::vec3(0.0f, 0.0f, 0.0f));
std::vector<my::Texture::InstancedData>instancing_data(512);
my::SpriteAnimation animation;
float instancing_data_refresh_time = 0.0f;
my::Font font;


struct SceneParam {
    glm::vec3 camera_position;
    glm::vec3 light_position;
};

my::GameApplication::GameApplication() :
    _camera() {
}

my::GameApplication::~GameApplication() {
}

bool my::GameApplication::Initialize(void) {
    bool init = false;
    _geometry_renderer.Initialize();
    _camera.SetPosition(glm::vec3(0.0f, 4.0f, 5.0));

    animation.Load("../Resource/animation/basic.json");
    font.Load("../Resource/font/RictyDiminishedDiscord-Regular.ttf");



    {
        auto shader = ::g_pResource->Get<std::shared_ptr<my::Shader>>("shader/instanced_texture.shader");
        shader->Enable();
        auto texture = ::g_pResource->Get<std::shared_ptr<my::Texture>>("texture/map.png");
        texture->GenerateInstancingData();
    }

    {
        auto param = SceneParam();
        param.camera_position = _camera.GetPosition();
        param.light_position = glm::vec3(0.6f, 0.6f, 0.6f);
        auto shader = ::g_pResource->Get<std::shared_ptr<my::Shader>>("shader/mesh.shader");
        shader->Enable();
        shader->GenerateUniformBuffer("SceneParam", sizeof(SceneParam), &param);
    }
    return true;
}

bool my::GameApplication::Input(void) {
//    _camera.DebugMoveTurn(glm::vec3(), 10.0f, 10.0f);
    return true;
}

bool my::GameApplication::Update(void) {
    _camera.Update();
    float delta = ::g_pClock->GetDeltaTime();
    instancing_data_refresh_time += delta;

    if (::g_pKeyboard->IsHold(my::KeyCode::Right)) {
        world.position.x += 10 * delta;
    } // if
    if (::g_pKeyboard->IsHold(my::KeyCode::Left)) {
        world.position.x -= 10 * delta;
    } // if
    if (::g_pKeyboard->IsHold(my::KeyCode::Down)) {
        world.position.z += 10 * delta;
    } // if
    if (::g_pKeyboard->IsHold(my::KeyCode::Up)) {
        world.position.z -= 10 * delta;
    } // if
    if (::g_pKeyboard->IsHold(my::KeyCode::Space)) {
        world.rotate.z -= 10 * delta;
    } // if
    return true;
}

bool my::GameApplication::Render(void) {
    auto view = _camera.GetViewMatrix();
    auto proj = _camera.GetProjectionMatrix();
    auto identity = glm::identity<glm::mat4>();


    // デフォルトのフレームバッファ
    auto c = glm::vec4(0.0f, 0.4f, 0.4f, 0.0f);
    ::glClearColor(c.r, c.g, c.b, c.a);
    ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    ::glViewport(0, 0, 1024, 768); // フレームバッファ全体に描画する。左下隅から右上隅へ。

    // render 3d
    ::glEnable(GL_CULL_FACE);
    ::glCullFace(GL_BACK);
    ::glFrontFace(GL_CCW);

    ::glEnable(GL_DEPTH_TEST);
    ::glDepthFunc(GL_LESS);
    ::glDepthMask(GL_TRUE);
//    ::glEnable(GL_STENCIL_TEST);
//    ::glStencilFunc(GL_EQUAL, 1, 0xFF);
//    ::glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//    ::glStencilMask(0xFF);
//    ::glDisable(GL_STENCIL_TEST);


    std::shared_ptr<my::Model> model;
    auto model_shader = ::g_pResource->Get<std::shared_ptr<my::Shader>>("shader/mesh.shader");

    // 三角形表示
    {
        auto w = my::Transform();
        model = ::g_pResource->Get<std::shared_ptr<my::Model>>("model/SimpleMorph/SimpleMorph.gltf");
        model->SetShader(model_shader);
        model_shader->Enable();
        model->Render(w.Matrix(), view, proj);
        model_shader->Disable();
    }

    // モデル表示
    {
        auto translation = glm::translate(glm::identity<glm::mat4>(), world.position);
        auto rotation = glm::toMat4(glm::quat(world.rotate));
        auto scaling = glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.01f));
        auto transform = translation * rotation * scaling;

        model_shader->Enable();
        model = ::g_pResource->Get<std::shared_ptr<my::Model>>("model/buster_drone/scene.gltf");
        model->SetShader(model_shader);
        model->Render(transform, view, proj);
        model_shader->Disable();
    }



    ::glDisable(GL_DEPTH_TEST);
    ::glDisable(GL_CULL_FACE);

    // render 2d
    ::glEnable(GL_TEXTURE_2D);
    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    animation.Update();
    auto texture = ::g_pResource->Get<std::shared_ptr<my::Texture>>("texture/map.png");

    if (0.5f < instancing_data_refresh_time) {
        instancing_data_refresh_time = 0.0f;
        for (auto& data : instancing_data) {
            data.translate = glm::vec3(ut::GenerateRandomF(-3.0f, 3.0f), ut::GenerateRandomF(-3.0f, 3.0f), 3.0f);
            data.rotate = glm::vec3();
            data.scale = glm::vec3(0.001f);
            data.rectangle = animation.GetRectangle();
        } // for
    } // if

    texture->SetShader(::g_pResource->Get<std::shared_ptr<my::Shader>>("shader/instanced_texture.shader"));
    texture->Render(instancing_data, view, proj);

    // font
    font.SetShader(::g_pResource->Get<std::shared_ptr<my::Shader>>("shader/font.shader"));
    font.Render("Redner", glm::vec2(0.0f, 0));
    auto collision = Collision();
    auto color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);



    static int count = 0;
    static float amplitude = 10;
    count++;
    auto circle = my::Circle(100.0f, 500.0f + std::sin(std::numbers::pi * 2 / 60.0f * count) * amplitude, 100.0f);
    auto rect = my::Rectangle(0.0f, 600.0f, 200.0f, 664.0f);
    color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    if (collision.CollisionCircleRectangle(circle, rect)) {
        color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    } // if

    _geometry_renderer.RenderFillRectangle(rect, color,
                                           identity, glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f));
    _geometry_renderer.RenderFillCircle(circle, color,
                                        identity, glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f));


    ::glDisable(GL_TEXTURE_2D);
    ::glDisable(GL_BLEND);
    return true;
}
bool my::GameApplication::Release(void) {
    _geometry_renderer.Release();
    return true;
}