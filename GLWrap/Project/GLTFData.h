#ifndef MY_GLTF_DATA_H
#define MY_GLTF_DATA_H


#include <optional>
#include <string>
#include <vector>

#include "rapidjson/document.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/quaternion.hpp"


namespace my {
class GLTFData {
    struct Asset {
        std::string generator;
        float version = 0.0f;
    };
    struct ExtensionsUsed {
        std::vector<std::string>used;
    };
    struct ExtensionsRequired {
        std::vector<std::string>required;
    };
    struct Sampler {
        int mag_filter = -1;
        int min_filter = -1;
        int wrap_s = -1;
        int wrap_t = -1;
    };
    struct Image {
        std::string uri;
        std::string mime_type;
    };
    /// <summary>
    /// ImageとSamplerを内包
    /// </summary>
    struct Texture {
        int sampler_index = -1;
        int source_image_index = -1;
    };
    /// <summary>
    /// マテリアル
    /// </summary>
    struct Material {
        struct PbrMetallicRoughness {
            struct BaseColorTexture {
                int texture_index = -1;
                uint32_t texcoord_index = 0;
                BaseColorTexture() {}
            };
            struct MetallicRoughnessTexture {
                int texture_index = -1;
                uint32_t texcoord_index = 0;
                MetallicRoughnessTexture() {}
            };
            glm::vec4 base_color_factor;
            float metallic_factor = 0.0f;
            float roughness_factor = 0.0f;
            BaseColorTexture base_color_texture = BaseColorTexture();
            MetallicRoughnessTexture metallic_roughness_texture = MetallicRoughnessTexture();
        };
        struct NormalTexture {
            int texture_index = -1;
            uint32_t texcoord_index = 0;
            int scale_index = -1;
            NormalTexture() {}
        };
        struct OcclusionTexture {
            int texture_index = -1;
            uint32_t texcoord_index = 0;
        };
        struct EmissiveTexture {
            int texture_index = -1;
            uint32_t texcoord_index = 0;
            EmissiveTexture() {}
        };
        struct Extensions {
            struct KHRMaterialsCommon {
                KHRMaterialsCommon() {}
            };
            struct KHRMaterialsPbrSpecularGlossiness {
                struct DiffuseTexture {
                    int texture_index = -1;
                    uint32_t texcoord_index = 0;
                    DiffuseTexture() {}
                };
                struct SpecularGlossinessTexture {
                    int texture_index = -1;
                    uint32_t texcoord_index = 0;
                    SpecularGlossinessTexture() {}
                };
                glm::vec4 diffuse_factor;
                DiffuseTexture diffuse_texture = DiffuseTexture();
                float glossiness_factor = 0.0f;
                glm::vec3 specular_factor;
                SpecularGlossinessTexture specular_glossiness_texture = SpecularGlossinessTexture();
            };
        };
        std::string name;
        bool double_sided = false; // この値がfalseの場合、裏面カリングが有効
        glm::vec3 emissive_factor;
        PbrMetallicRoughness pbr_metallic_roughness = PbrMetallicRoughness();
        NormalTexture normal_texture = NormalTexture();
        OcclusionTexture occlusion_texture = OcclusionTexture();
        EmissiveTexture emissive_texture = EmissiveTexture();
        Extensions extensions = Extensions();
    };
    /// <summary>
    /// バッファデータ
    /// </summary>
    struct Binary {
        std::string data;
        std::string uri;
    };
    /// <summary>
    /// バッファ
    /// </summary>
    struct Buffer {
        std::string uri;
        std::size_t byte_length = 0;
    };
    /// <summary>
    /// バッファビュー
    /// </summary>
    struct BufferView {
        int buffer_index = -1;
        std::size_t byte_offset = 0;
        std::size_t byte_length = 0;
        std::size_t byte_stride = 0;
        int target = -1;
    };
    /// <summary>
    /// 各データへの参照
    /// </summary>
    struct Accessor {
        struct Sparse {
            struct Index {
                int buffer_view = -1;
                std::size_t buffer_offset = 0;
                int component_type = -1;
                Index() {}
            };
            struct Value {
                int buffer_view = -1;
                int buffer_offset = -1;
                Value() {}
            };
            std::size_t count = 0;
            Index index = Index();
            Value value = Value();
            Sparse() {}
        };
        int buffer_view_index = -1;
        std::size_t buffer_byte_offset = 0;
        int component_type = -1;
        std::size_t count = 0;
        std::vector<float> max; // バウンディングボックス
        std::vector<float> min; // バウンディングボックス
        std::string type;
        Sparse sparse = Sparse();
    };
    /// <summary>
    /// アニメーション
    /// </summary>
    struct Animation {
        struct Sampler {
            int input_index = -1; // accesstor index
            int output_index = -1; // accesstor index
            std::string interpolation;
            Sampler() {}
        };
        struct Channel {
            struct Target {
                int node_index = -1;
                std::string path;
            };
            int sampler_index = -1;
            Target target = Target();
            Channel() {}
        };
        std::string name;
        std::vector<Channel> channels;
        std::vector<Sampler>samplers;
    };
    /// <summary>
    /// スキニングのパラメータ
    /// </summary>
    struct Skin {
        int inverse_bind_matrices = -1;
        int skeleton = -1;
        std::vector<int>joints;
    };
    /// <summary>
    /// シーンのレンダリングのビュー構成
    /// </summary>
    struct Camera {
        struct Perspective {
            float aspect_ratio;
            float yfov;
            float zfar;
            float znear;
        };
        struct Orthographic {
            float xmag;
            float ymag;
            float zfar;
            float znear;
        };
        std::string type;
        Perspective perspective = Perspective();
        Orthographic orthographic = Orthographic();
    };
    /// <summary>
    /// メッシュ
    /// </summary>
    struct Mesh {
        struct Primitive {
            struct Attribute {
                int position = -1;
                int normal = -1;
                int texcoord0 = -1;
                int texcoord1 = -1;
                int texcoord2 = -1;
                int texcoord3 = -1;
                int texcoord4 = -1;
                int color = -1;
                int joint = -1;
                int weight = -1;
                int tangent = -1;
            };
            struct Target {
                int position = -1;
                int normal = -1;
            };
            Attribute attribute = Attribute();
            std::vector<Target>targets;
            int indices = -1;
            int mode = -1;
            int material = -1;
        };
        std::string name;
        std::vector<Primitive>primitives;
        std::vector<float>weights;
    };
    /// <summary>
    /// シーングラフの階層
    /// </summary>
    struct Node {
        std::string name;
        std::vector<uint32_t>child_indices;
        int mesh_index = -1;
        int skin_index = -1;
        int camera_index = -1;
        std::optional<glm::mat4> matrix; // 列優先 local transform =  translation_matrix * rotation_matrix * scale_matrix;
        glm::vec3 translation = glm::vec3();
        glm::quat rotation = glm::quat();
        glm::vec3 scale = glm::vec3(1.0f);
        //Structure:           local transform      global transform
        //    root                 R                    R
        //    + -nodeA            A                    R * A
        //    + -nodeB        B                    R * A * B
        //    + -nodeC        C                    R * A * C
        glm::mat4 ConputeLocalTransform(void) const {
            auto identity = glm::mat4(1.0f);

            auto translation_matrix = glm::translate(identity, translation);
            auto rotation_matrix = glm::toMat4(rotation);
            auto scale_matrix = glm::scale(identity, scale);
            return translation_matrix * rotation_matrix * scale_matrix;
        }
    };
    /// <summary>
    /// エントリポイント
    /// </summary>
    struct Scene {
        std::vector<uint32_t> node_indices;
    };
private:
public:
//! ディレクトリパス
    std::string directory_path;
    //! バージョン
    my::GLTFData::Asset asset;
    //! 拡張
    my::GLTFData::ExtensionsUsed extensions_used;
    //! 拡張
    my::GLTFData::ExtensionsRequired extensions_required;
    //! デフォルトシーン
    my::GLTFData::Scene* general_scene;
    //! シーン
    std::vector<my::GLTFData::Scene> scenes;
    //! シーンの要素
    std::vector<my::GLTFData::Node> nodes;
    //! メッシュ
    std::vector<my::GLTFData::Mesh> meshes;
    //! バッファアクセッサ
    std::vector<my::GLTFData::Accessor> accessors;
    //! バッファビュー
    std::vector<my::GLTFData::BufferView>buffer_views;
    //! バッファ
    std::vector<my::GLTFData::Buffer> buffers;
    //! バッファデータ
    std::vector<my::GLTFData::Binary> binarys;
    //! マテリアル
    std::vector<my::GLTFData::Material> materials;
    //! テクスチャ
    std::vector<my::GLTFData::Texture> textures;
    //! イメージデータ
    std::vector<my::GLTFData::Image> images;
    //! テクスチャサンプラー
    std::vector<my::GLTFData::Sampler> samplers;
    //! カメラ
    std::vector<my::GLTFData::Camera> cameras;
    //! スキン
    std::vector<my::GLTFData::Skin> skins;
    //! アニメーション
    std::vector<Animation> animations;


    bool LoadAsset(const rapidjson::Document& document);
    bool LoadExtensionsRequired(const rapidjson::Document& document);
    bool LoadExtensionsUsed(const rapidjson::Document& document);
    bool LoadScene(const rapidjson::Document& document);
    bool LoadNode(const rapidjson::Document& document);
    bool LoadMesh(const rapidjson::Document& document);
    bool LoadAccessor(const rapidjson::Document& document);
    bool LoadBufferView(const rapidjson::Document& document);
    bool LoadBuffer(const rapidjson::Document& document);
    bool LoadBinary(void);
    bool LoadMaterial(const rapidjson::Document& document);
    bool LoadTexture(const rapidjson::Document& document);
    bool LoadImage(const rapidjson::Document& document);
    bool LoadSampler(const rapidjson::Document& document);
    bool LoadCamera(const rapidjson::Document& document);
    bool LoadSkin(const rapidjson::Document& document);
    bool LoadAnimation(const rapidjson::Document& document);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GLTFData();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GLTFData();
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path">パス</param>
    /// <returns>成功</returns>
    bool Load(const char* path);
    /// <summary>
    /// バイナリデータ取得
    /// </summary>
    /// <param name="accessor_key">アクセッサ</param>
    /// <returns></returns>
    void* BinaryData(const int accessor_key);
};
}
#endif // !MY_GLTF_DATA_H