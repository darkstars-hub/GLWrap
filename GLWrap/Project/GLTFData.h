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
    /// Image��Sampler�����
    /// </summary>
    struct Texture {
        int sampler_index = -1;
        int source_image_index = -1;
    };
    /// <summary>
    /// �}�e���A��
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
        bool double_sided = false; // ���̒l��false�̏ꍇ�A���ʃJ�����O���L��
        glm::vec3 emissive_factor;
        PbrMetallicRoughness pbr_metallic_roughness = PbrMetallicRoughness();
        NormalTexture normal_texture = NormalTexture();
        OcclusionTexture occlusion_texture = OcclusionTexture();
        EmissiveTexture emissive_texture = EmissiveTexture();
        Extensions extensions = Extensions();
    };
    /// <summary>
    /// �o�b�t�@�f�[�^
    /// </summary>
    struct Binary {
        std::string data;
        std::string uri;
    };
    /// <summary>
    /// �o�b�t�@
    /// </summary>
    struct Buffer {
        std::string uri;
        std::size_t byte_length = 0;
    };
    /// <summary>
    /// �o�b�t�@�r���[
    /// </summary>
    struct BufferView {
        int buffer_index = -1;
        std::size_t byte_offset = 0;
        std::size_t byte_length = 0;
        std::size_t byte_stride = 0;
        int target = -1;
    };
    /// <summary>
    /// �e�f�[�^�ւ̎Q��
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
        std::vector<float> max; // �o�E���f�B���O�{�b�N�X
        std::vector<float> min; // �o�E���f�B���O�{�b�N�X
        std::string type;
        Sparse sparse = Sparse();
    };
    /// <summary>
    /// �A�j���[�V����
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
    /// �X�L�j���O�̃p�����[�^
    /// </summary>
    struct Skin {
        int inverse_bind_matrices = -1;
        int skeleton = -1;
        std::vector<int>joints;
    };
    /// <summary>
    /// �V�[���̃����_�����O�̃r���[�\��
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
    /// ���b�V��
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
    /// �V�[���O���t�̊K�w
    /// </summary>
    struct Node {
        std::string name;
        std::vector<uint32_t>child_indices;
        int mesh_index = -1;
        int skin_index = -1;
        int camera_index = -1;
        std::optional<glm::mat4> matrix; // ��D�� local transform =  translation_matrix * rotation_matrix * scale_matrix;
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
    /// �G���g���|�C���g
    /// </summary>
    struct Scene {
        std::vector<uint32_t> node_indices;
    };
private:
public:
//! �f�B���N�g���p�X
    std::string directory_path;
    //! �o�[�W����
    my::GLTFData::Asset asset;
    //! �g��
    my::GLTFData::ExtensionsUsed extensions_used;
    //! �g��
    my::GLTFData::ExtensionsRequired extensions_required;
    //! �f�t�H���g�V�[��
    my::GLTFData::Scene* general_scene;
    //! �V�[��
    std::vector<my::GLTFData::Scene> scenes;
    //! �V�[���̗v�f
    std::vector<my::GLTFData::Node> nodes;
    //! ���b�V��
    std::vector<my::GLTFData::Mesh> meshes;
    //! �o�b�t�@�A�N�Z�b�T
    std::vector<my::GLTFData::Accessor> accessors;
    //! �o�b�t�@�r���[
    std::vector<my::GLTFData::BufferView>buffer_views;
    //! �o�b�t�@
    std::vector<my::GLTFData::Buffer> buffers;
    //! �o�b�t�@�f�[�^
    std::vector<my::GLTFData::Binary> binarys;
    //! �}�e���A��
    std::vector<my::GLTFData::Material> materials;
    //! �e�N�X�`��
    std::vector<my::GLTFData::Texture> textures;
    //! �C���[�W�f�[�^
    std::vector<my::GLTFData::Image> images;
    //! �e�N�X�`���T���v���[
    std::vector<my::GLTFData::Sampler> samplers;
    //! �J����
    std::vector<my::GLTFData::Camera> cameras;
    //! �X�L��
    std::vector<my::GLTFData::Skin> skins;
    //! �A�j���[�V����
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
    /// �R���X�g���N�^
    /// </summary>
    GLTFData();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GLTFData();
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="path">�p�X</param>
    /// <returns>����</returns>
    bool Load(const char* path);
    /// <summary>
    /// �o�C�i���f�[�^�擾
    /// </summary>
    /// <param name="accessor_key">�A�N�Z�b�T</param>
    /// <returns></returns>
    void* BinaryData(const int accessor_key);
};
}
#endif // !MY_GLTF_DATA_H