#include "GLTFData.h"

#include "Helper.h"


bool my::GLTFData::LoadAsset(const rapidjson::Document& document) {
    if (!document.HasMember("asset")) {
        return false;
    } // if
    auto& asset_data = document["asset"];

    if (asset_data.HasMember("generator")) {
        assert(asset_data["generator"].IsString());
        asset.generator = asset_data["generator"].GetString();
    } // if
    if (asset_data.HasMember("version")) {
        assert(asset_data["version"].IsString());
        asset.version = ut::lexical_cast<float, std::string> (asset_data["version"].GetString());
    } // if
    return true;
}

bool my::GLTFData::LoadExtensionsRequired(const rapidjson::Document& document) {
    if (!document.HasMember("extensionsRequired")) {
        return false;
    } // if
    // 
    const auto& extensions_data = document["extensionsRequired"];

    auto n = extensions_data.Size();
    for (size_t i = 0; i < n; i++) {
        this->extensions_required.required.push_back(extensions_data[i].GetString());
    } // for
    return true;
}

bool my::GLTFData::LoadExtensionsUsed(const rapidjson::Document& document) {
    if (!document.HasMember("extensionsUsed")) {
        return false;
    } // if
    // 
    const auto& extensions_data = document["extensionsUsed"];

    auto n = extensions_data.Size();
    for (size_t i = 0; i < n; i++) {
        this->extensions_used.used.push_back(extensions_data[i].GetString());
    } // for
    return true;
}

bool my::GLTFData::LoadScene(const rapidjson::Document& document) {
    if (!document.HasMember("scenes")) {
        return false;
    } // if
    // 
    const auto& scenes_data = document["scenes"];
    auto n = scenes_data.Size();
    scenes.reserve(n);

    for (size_t i = 0; i < n; i++) {
        auto scene = Scene();
        // ノード
        if (scenes_data[i].HasMember("nodes")) {
            const auto& nodes_data = scenes_data[i]["nodes"];
            assert(nodes_data.IsArray());
            auto m = nodes_data.Size();
            for (size_t j = 0; j < m; j++) {
                scene.node_indices.push_back(nodes_data[j].GetInt());
            } // for
        } // if
        scenes.push_back(scene);
    } // for

    // ルートシーン

    const auto& scene_data = document["scene"];
    assert(scene_data.IsInt());
    general_scene = &scenes.at(scene_data.GetInt());
    return true;
}

bool my::GLTFData::LoadNode(const rapidjson::Document& document) {
    if (!document.HasMember("nodes")) {
        return false;
    } // if
    const auto& nodes_data = document["nodes"];

    auto n = nodes_data.Size();
    nodes.reserve(n);

    for (size_t i = 0; i < n; i++) {
        auto node = Node();
        // name
        if (nodes_data[i].HasMember("name")) {
            const auto& name = nodes_data[i]["name"];
            assert(name.IsString());
            node.name = name.GetString();
        } // if
        // children
        if (nodes_data[i].HasMember("children")) {
            const auto& children = nodes_data[i]["children"];
            assert(children.IsArray());
            auto m = children.Size();
            for (size_t j = 0; j < m; j++) {
                auto index = children[j].GetInt();
                node.child_indices.push_back(index);
            } // for
        } // if
        // mesh
        if (nodes_data[i].HasMember("mesh")) {
            const auto& mesh = nodes_data[i]["mesh"];
            assert(mesh.IsInt());
            node.mesh_index = mesh.GetInt();
        } // if
        // skin
        if (nodes_data[i].HasMember("skin")) {
            const auto& skin = nodes_data[i]["skin"];
            assert(skin.IsInt());
            node.skin_index = skin.GetInt();
        } // if
        // camera
        if (nodes_data[i].HasMember("camera")) {
            const auto& camera = nodes_data[i]["camera"];
            assert(camera.IsInt());
            node.camera_index = camera.GetInt();
        } // if
        // matrix
        if (nodes_data[i].HasMember("matrix")) {
            const auto& matrix = nodes_data[i]["matrix"];
            assert(matrix.IsArray());
            auto m = matrix.Size();
            for (size_t j = 0; j < m; j++) {
                float* ptr = reinterpret_cast<float*>(&node.matrix);
                ptr[j] = matrix[j].GetFloat();
            } // for
        } // if
        // translation
        if (nodes_data[i].HasMember("translation")) {
            const auto& translation = nodes_data[i]["translation"];
            assert(translation.IsArray());
            auto m = translation.Size();
            for (size_t j = 0; j < m; j++) {
                float* ptr = reinterpret_cast<float*>(&node.translation);
                ptr[j] = translation[j].GetFloat();
            } // for
        } // if
        // rotation
        if (nodes_data[i].HasMember("rotation")) {
            const auto& rotation = nodes_data[i]["rotation"];
            assert(rotation.IsArray());
            auto m = rotation.Size();
            for (size_t j = 0; j < m; j++) {
                float* ptr = reinterpret_cast<float*>(&node.rotation);
                ptr[j] = rotation[j].GetFloat();
            } // for
        } // if
        // scale
        if (nodes_data[i].HasMember("scale")) {
            const auto& scale = nodes_data[i]["scale"];
            assert(scale.IsArray());
            auto m = scale.Size();
            for (size_t j = 0; j < m; j++) {
                float* ptr = reinterpret_cast<float*>(&node.scale);
                ptr[j] = scale[j].GetFloat();
            } // for
        } // if
        nodes.push_back(node);
    } // for
    return true;
}
bool my::GLTFData::LoadMesh(const rapidjson::Document& document) {
    if (!document.HasMember("meshes")) {
        return false;
    } // if
    const auto& meshes_data = document["meshes"];

    auto n = meshes_data.Size();
    meshes.reserve(n);
    for (size_t i = 0; i < n; i++) {
        auto mesh = Mesh();
        // name
        if (meshes_data[i].HasMember("name")) {
            const auto& name = meshes_data[i]["name"];
            assert(name.IsString());
            mesh.name = name.GetString();
        } // if
        // primitives
        if (meshes_data[i].HasMember("primitives")) {
            const auto& primitives = meshes_data[i]["primitives"];
            assert(primitives.IsArray());
            auto m = primitives.Size();
            for (size_t j = 0; j < m; j++) {
                auto primitive = Mesh::Primitive();
                // indices
                if (primitives[j].HasMember("indices")) {
                    assert(primitives[j]["indices"].IsInt());
                    primitive.indices = primitives[j]["indices"].GetInt();
                } // if
                // material
                if (primitives[j].HasMember("material")) {
                    assert(primitives[j]["material"].IsInt());
                    primitive.material = primitives[j]["material"].GetInt();
                } // if
                // mode
                if (primitives[j].HasMember("mode")) {
                    assert(primitives[j]["mode"].IsInt());
                    primitive.mode = primitives[j]["mode"].GetInt();
                } // if
                // attributes
                if (primitives[j].HasMember("attributes")) {
                    auto attribute = Mesh::Primitive::Attribute();
                    const auto& attributes = primitives[j]["attributes"];
                    assert(attributes.IsObject());

                    // position
                    if (attributes.HasMember("POSITION")) {
                        const auto& position = attributes["POSITION"];
                        assert(position.IsInt());
                        attribute.position = position.GetInt();
                    } // if
                    // normal
                    if (attributes.HasMember("NORMAL")) {
                        const auto& normal = attributes["NORMAL"];
                        assert(normal.IsInt());
                        attribute.normal = normal.GetInt();
                    } // if
                    // texcoord0
                    if (attributes.HasMember("TEXCOORD_0")) {
                        const auto& texcoord0 = attributes["TEXCOORD_0"];
                        assert(texcoord0.IsInt());
                        attribute.texcoord0 = texcoord0.GetInt();
                    } // if
                    // texcoord1
                    if (attributes.HasMember("TEXCOORD_1")) {
                        const auto& texcoord1 = attributes["TEXCOORD_1"];
                        assert(texcoord1.IsInt());
                        attribute.texcoord1 = texcoord1.GetInt();
                    } // if
                    // texcoord2
                    if (attributes.HasMember("TEXCOORD_2")) {
                        const auto& texcoord2 = attributes["TEXCOORD_2"];
                        assert(texcoord2.IsInt());
                        attribute.texcoord2 = texcoord2.GetInt();
                    } // if
                    // texcoord3
                    if (attributes.HasMember("TEXCOORD_3")) {
                        const auto& texcoord3 = attributes["TEXCOORD_3"];
                        assert(texcoord3.IsInt());
                        attribute.texcoord3 = texcoord3.GetInt();
                    } // if
                    // texcoord4
                    if (attributes.HasMember("TEXCOORD_4")) {
                        const auto& texcoord4 = attributes["TEXCOORD_4"];
                        assert(texcoord4.IsInt());
                        attribute.texcoord4 = texcoord4.GetInt();
                    } // if
                    // color
                    if (attributes.HasMember("COLOR_0")) {
                        const auto& color = attributes["COLOR_0"];
                        assert(color.IsInt());
                        attribute.color = color.GetInt();
                    } // if
                    // joint
                    if (attributes.HasMember("JOINTS_0")) {
                        const auto& joint = attributes["JOINTS_0"];
                        assert(joint.IsInt());
                        attribute.joint = joint.GetInt();
                    } // if
                    // weight
                    if (attributes.HasMember("WEIGHTS_0")) {
                        const auto& weight = attributes["WEIGHTS_0"];
                        assert(weight.IsInt());
                        attribute.weight = weight.GetInt();
                    } // if
                    // tangent
                    if (attributes.HasMember("TANGENT")) {
                        const auto& tangent = attributes["TANGENT"];
                        assert(tangent.IsInt());
                        attribute.tangent = tangent.GetInt();
                    } // if
                    primitive.attribute = attribute;
                } // if
                // targets
                if (primitives[j].HasMember("targets")) {
                    auto target = Mesh::Primitive::Target();
                    const auto& targets = primitives[j]["targets"];
                    assert(targets.IsArray());
                    auto l = targets.Size();
                    for (size_t k = 0; k < l; k++) {
                        // position
                        if (targets[k].HasMember("POSITION")) {
                            const auto& position = targets[k]["POSITION"];
                            assert(position.IsInt());
                            target.position = position.GetInt();
                        } // if
                        // normal
                        if (targets[k].HasMember("NORMAL")) {
                            const auto& normal = targets[k]["NORMAL"];
                            assert(normal.IsInt());
                            target.normal = normal.GetInt();
                        } // if

                        primitive.targets.push_back(target);
                    } // for
                } // if

                mesh.primitives.push_back(primitive);
            } // for
            if (meshes_data[i].HasMember("weights")) {
                const auto& weights = meshes_data[i]["weights"];
                assert(weights.IsArray());
                auto m = weights.Size();
                for (size_t j = 0; j < m; j++) {
                    assert(weights[j].IsInt() || weights[j].IsFloat());
                    mesh.weights.push_back(weights[j].GetFloat());
                } // for
            } // if
        } // if
        meshes.push_back(mesh);
    } // for
    return true;
}

bool my::GLTFData::LoadAccessor(const rapidjson::Document& document) {
    if (!document.HasMember("accessors")) {
        return false;
    } // if
    const auto& accessors_data = document["accessors"];
    auto n = accessors_data.Size();
    accessors.reserve(n);
    for (size_t i = 0; i < n; i++) {
        auto accessor = Accessor();

        // buffer view
        if (accessors_data[i].HasMember("bufferView")) {
            const auto& buffer_view = accessors_data[i]["bufferView"];
            assert(buffer_view.IsInt());
            accessor.buffer_view_index = buffer_view.GetInt();
        } // if
        // buffer offset
        if (accessors_data[i].HasMember("byteOffset")) {
            const auto& buffer_offset = accessors_data[i]["byteOffset"];
            assert(buffer_offset.IsInt());
            accessor.buffer_byte_offset = buffer_offset.GetInt();
        } // if
        // component type 
        if (accessors_data[i].HasMember("componentType")) {
            const auto& component_type = accessors_data[i]["componentType"];
            assert(component_type.IsInt());
            accessor.component_type = component_type.GetInt();
        } // if
        // count 
        if (accessors_data[i].HasMember("count")) {
            const auto& count = accessors_data[i]["count"];
            assert(count.IsInt());
            accessor.count = count.GetInt();
        } // if
        // max
        if (accessors_data[i].HasMember("max")) {
            const auto& max_array = accessors_data[i]["max"];
            assert(max_array.IsArray());
            auto m = max_array.Size();
            for (size_t j = 0; j < m; j++) {
                accessor.max.push_back(max_array[j].GetFloat());
            } // for
        } // if
        // min
        if (accessors_data[i].HasMember("min")) {
            const auto& min_array = accessors_data[i]["min"];
            assert(min_array.IsArray());
            auto m = min_array.Size();
            for (size_t j = 0; j < m; j++) {
                accessor.min.push_back(min_array[j].GetFloat());
            } // for
        } // if
        // type 
        if (accessors_data[i].HasMember("type")) {
            const auto& type = accessors_data[i]["type"];
            assert(type.IsString());
            accessor.type = type.GetString();
        } // if
        // sparse
        if (accessors_data[i].HasMember("sparse")) {
            const auto& sparse_data = accessors_data[i]["sparse"];
            assert(sparse_data.IsObject());

            // count
            if (sparse_data.HasMember("count")) {
                const auto& count = sparse_data["count"];
                assert(count.IsInt());
                accessor.sparse.count = count.GetInt();
            } // if
            // indices
            if (sparse_data.HasMember("indices")) {
                const auto& indices = sparse_data["indices"];
                assert(indices.IsObject());
                // buffer view
                if (indices.HasMember("bufferView")) {
                    const auto& buffer_view = indices["bufferView"];
                    assert(buffer_view.IsInt());
                    accessor.sparse.index.buffer_view = buffer_view.GetInt();
                } // if
                // buffer offset
                if (indices.HasMember("byteOffset")) {
                    const auto& buffer_offset = indices["byteOffset"];
                    assert(buffer_offset.IsInt());
                    accessor.sparse.index.buffer_offset = buffer_offset.GetInt();
                } // if
                // component type 
                if (indices.HasMember("componentType")) {
                    const auto& component_type = indices["componentType"];
                    assert(component_type.IsInt());
                    accessor.sparse.index.component_type = component_type.GetInt();
                } // if
            } // if
            // values
            if (sparse_data.HasMember("values")) {
                const auto& values = sparse_data["values"];
                assert(values.IsObject());
                // buffer view
                if (values.HasMember("bufferView")) {
                    const auto& buffer_view = values["bufferView"];
                    assert(buffer_view.IsInt());
                    accessor.sparse.value.buffer_view = buffer_view.GetInt();
                } // if
                // buffer offset
                if (values.HasMember("byteOffset")) {
                    const auto& buffer_offset = values["byteOffset"];
                    assert(buffer_offset.IsInt());
                    accessor.sparse.value.buffer_offset = buffer_offset.GetInt();
                } // if
            } // if
        } // if
        accessors.push_back(accessor);
    } // for
    return true;
}
bool my::GLTFData::LoadBufferView(const rapidjson::Document& document) {
    if (!document.HasMember("bufferViews")) {
        return false;
    } // if
    const auto& buffer_views_data = document["bufferViews"];
    assert(buffer_views_data.IsArray());

    auto n = buffer_views_data.Size();
    buffer_views.reserve(n);
    for (size_t i = 0; i < n; i++) {
        auto buffer_view = BufferView();

        // buffer
        if (buffer_views_data[i].HasMember("buffer")) {
            const auto& buffer_data = buffer_views_data[i]["buffer"];
            assert(buffer_data.IsInt());
            buffer_view.buffer_index = buffer_data.GetInt();
        } // if
        // byte offset
        if (buffer_views_data[i].HasMember("byteOffset")) {
            const auto& byte_offset_data = buffer_views_data[i]["byteOffset"];
            assert(byte_offset_data.IsInt());
            buffer_view.byte_offset = byte_offset_data.GetInt();
        } // if
        // byte length
        if (buffer_views_data[i].HasMember("byteLength")) {
            const auto& byte_length_data = buffer_views_data[i]["byteLength"];
            assert(byte_length_data.IsInt());
            buffer_view.byte_length = byte_length_data.GetInt();
        } // if
        // byte stride
        if (buffer_views_data[i].HasMember("byteStride")) {
            const auto& byte_stride_data = buffer_views_data[i]["byteStride"];
            assert(byte_stride_data.IsInt());
            buffer_view.byte_stride = byte_stride_data.GetInt();
        } // if
        // target
        if (buffer_views_data[i].HasMember("target")) {
            const auto& target_data = buffer_views_data[i]["target"];
            assert(target_data.IsInt());
            buffer_view.target = target_data.GetInt();
        } // if
        buffer_views.push_back(buffer_view);
    } // for
    return true;
}
bool my::GLTFData::LoadBuffer(const rapidjson::Document& document) {
    if (!document.HasMember("buffers")) {
        return false;
    } // if
    const auto& buffers_data = document["buffers"];
    assert(buffers_data.IsArray());

    auto n = buffers_data.Size();
    buffers.reserve(n);
    for (size_t i = 0; i < n; i++) {
        auto buffer = Buffer();

        // byte length
        if (buffers_data[i].HasMember("byteLength")) {
            const auto& byte_length_data = buffers_data[i]["byteLength"];
            assert(byte_length_data.IsInt());
            buffer.byte_length = byte_length_data.GetInt();
        } // if
        // uri
        if (buffers_data[i].HasMember("uri")) {
            const auto& uri_data = buffers_data[i]["uri"];
            assert(uri_data.IsString());
            buffer.uri = uri_data.GetString();
        } // if
        buffers.push_back(buffer);
    } // for
    return true;
}

bool my::GLTFData::LoadBinary(void) {
    std::vector<std::string> uris;
    for (auto& buffer : buffers) {
        uris.push_back(buffer.uri);
    } // for
    std::sort(uris.begin(), uris.end());
    uris.erase(std::unique(uris.begin(), uris.end()), uris.end());

    for (auto& uri : uris) {
        auto& path = directory_path;
        std::ifstream file(path + uri, std::ios::in | std::ios::binary);
        if (!file.is_open()) {
            continue;
        } // if
        std::stringstream stream;
        stream << file.rdbuf();
        std::string data = stream.str();

        auto binary = Binary();
        binary.uri = uri;
        binary.data = data;
        binarys.push_back(std::move(binary));
    } // for
    return true;
}

bool my::GLTFData::LoadMaterial(const rapidjson::Document& document) {
    if (!document.HasMember("materials")) {
        return false;
    } // if
    const auto& materials_data = document["materials"];
    assert(materials_data.IsArray());

    auto n = materials_data.Size();
    materials.reserve(n);
    for (size_t i = 0; i < n; i++) {
        auto material = Material();
        // name
        if (materials_data[i].HasMember("name")) {
            const auto& name = materials_data[i]["name"];
            assert(name.IsString());
            material.name = name.GetString();
        } // if
        if (materials_data[i].HasMember("doubleSided")) {
            const auto& double_sided = materials_data[i]["doubleSided"];
            assert(double_sided.IsBool());
            // double sided 
            material.double_sided = double_sided.GetBool();
        } // if
        // pbr_metallic_roughness 
        if (materials_data[i].HasMember("pbrMetallicRoughness")) {
            const auto& pbr_metallic_roughness = materials_data[i]["pbrMetallicRoughness"];
            assert(pbr_metallic_roughness.IsObject());
            // base color factor
            if (pbr_metallic_roughness.HasMember("baseColorFactor")) {
                const auto& base_color_factor = pbr_metallic_roughness["baseColorFactor"];
                assert(base_color_factor.IsArray());
                size_t m = base_color_factor.Size();
                for (size_t j = 0; j < m; j++) {
                    material.pbr_metallic_roughness.base_color_factor[j] = base_color_factor[j].GetFloat();
                } // for
            } // if
            // metallic factor
            if (pbr_metallic_roughness.HasMember("metallicFactor")) {
                const auto& metallic_factor = pbr_metallic_roughness["metallicFactor"];
                assert(metallic_factor.IsFloat() || metallic_factor.IsInt());
                material.pbr_metallic_roughness.metallic_factor = metallic_factor.GetFloat();
            } // if
            // roughness factor
            if (pbr_metallic_roughness.HasMember("roughnessFactor")) {
                const auto& roughness_factor = pbr_metallic_roughness["roughnessFactor"];
                assert(roughness_factor.IsFloat() || roughness_factor.IsInt());
                material.pbr_metallic_roughness.roughness_factor = roughness_factor.GetFloat();
            } // if
            
            // base color texture
            if (pbr_metallic_roughness.HasMember("baseColorTexture")) {
                const auto& base_color_texture = pbr_metallic_roughness["baseColorTexture"];
                assert(base_color_texture.IsObject());
                if (base_color_texture.HasMember("index")) {
                    const auto& index = base_color_texture["index"];
                    assert(index.IsInt());
                    material.pbr_metallic_roughness.base_color_texture.texture_index = index.GetInt();
                } // if
                if (base_color_texture.HasMember("texCoord")) {
                    const auto& texcoord = base_color_texture["texCoord"];
                    assert(texcoord.IsInt());
                    material.pbr_metallic_roughness.base_color_texture.texcoord_index= texcoord.GetInt();
                } // if
            } // if
            // metallic roughness texture
            if (pbr_metallic_roughness.HasMember("metallicRoughnessTexture")) {
                const auto& pbr_metallic_roughness_texture = pbr_metallic_roughness["metallicRoughnessTexture"];
                assert(pbr_metallic_roughness_texture.IsObject());
                if (pbr_metallic_roughness_texture.HasMember("index")) {
                    const auto& index = pbr_metallic_roughness_texture["index"];
                    assert(index.IsInt());
                    material.pbr_metallic_roughness.metallic_roughness_texture.texture_index = index.GetInt();
                } // if
                if (pbr_metallic_roughness_texture.HasMember("texCoord")) {
                    const auto& texcoord = pbr_metallic_roughness_texture["texCoord"];
                    assert(texcoord.IsInt());
                    material.pbr_metallic_roughness.metallic_roughness_texture.texcoord_index = texcoord.GetInt();
                } // if
            } // if
        } // if
        // normal texture
        if (materials_data[i].HasMember("normalTexture")) {
            const auto& normal_texture = materials_data[i]["normalTexture"];
            assert(normal_texture.IsObject());
            if (normal_texture.HasMember("index")) {
                const auto& index = normal_texture["index"];
                assert(index.IsInt());
                material.normal_texture.texture_index = index.GetInt();
            } // if
            if (normal_texture.HasMember("texCoord")) {
                const auto& texcoord = normal_texture["texCoord"];
                assert(texcoord.IsInt());
                material.normal_texture.texcoord_index = texcoord.GetInt();
            } // if
            if (normal_texture.HasMember("scale")) {
                const auto& scale = normal_texture["scale"];
                assert(scale.IsInt());
                material.normal_texture.scale_index = scale.GetInt();
            } // if
        } // if
        // occlusion texture
        if (materials_data[i].HasMember("occlusionTexture")) {
            const auto& occlusion_texture = materials_data[i]["occlusionTexture"];
            assert(occlusion_texture.IsObject());
            if (occlusion_texture.HasMember("index")) {
                const auto& index = occlusion_texture["index"];
                assert(index.IsInt());
                material.occlusion_texture.texture_index = index.GetInt();
            } // if
            if (occlusion_texture.HasMember("texCoord")) {
                const auto& texcoord = occlusion_texture["texCoord"];
                assert(texcoord.IsInt());
                material.occlusion_texture.texcoord_index = texcoord.GetInt();
            } // if
        } // if
        
        // emissive texture
        if (materials_data[i].HasMember("emissiveTexture")) {
            const auto& emissive_texture = materials_data[i]["emissiveTexture"];
            assert(emissive_texture.IsObject());
            if (emissive_texture.HasMember("index")) {
                const auto& index = emissive_texture["index"];
                assert(index.IsInt());
                material.emissive_texture.texture_index = index.GetInt();
            } // if
            if (emissive_texture.HasMember("texCoord")) {
                const auto& texcoord = emissive_texture["texCoord"];
                assert(texcoord.IsInt());
                material.emissive_texture.texcoord_index = texcoord.GetInt();
            } // if
        } // if
        // emissive factor
        if (materials_data[i].HasMember("emissiveFactor")) {
            const auto& emissive_factor = materials_data[i]["emissiveFactor"];
            assert(emissive_factor.IsArray());
            size_t m = emissive_factor.Size();
            for (size_t j = 0; j < m; j++) {
                material.emissive_factor[j] = emissive_factor[j].GetFloat();
            } // for
            
        } // if
        

        materials.push_back(material);
    } // for
    return true;
}

bool my::GLTFData::LoadTexture(const rapidjson::Document& document) {
    if (!document.HasMember("textures")) {
        return false;
    } // if
    const auto& textures_data = document["textures"];
    assert(textures_data.IsArray());

    auto n = textures_data.Size();
    textures.reserve(n);
    for (size_t i = 0; i < n; i++) {
        auto texture = Texture();

        if (textures_data[i].HasMember("sampler")) {
            const auto& sampler = textures_data[i]["sampler"];
            assert(sampler.IsInt());
            texture.sampler_index = sampler.GetInt();
        } // if
        if (textures_data[i].HasMember("source")) {
            const auto& source = textures_data[i]["source"];
            assert(source.IsInt());
            texture.source_image_index = source.GetInt();
        } // if
        textures.push_back(texture);
    } // for
    return true;
}
bool my::GLTFData::LoadImage(const rapidjson::Document& document) {
    if (!document.HasMember("images")) {
        return false;
    } // if
    const auto& images_data = document["images"];
    assert(images_data.IsArray());

    auto n = images_data.Size();
    images.reserve(n);
    for (size_t i = 0; i < n; i++) {
        auto image = Image();

        if (images_data[i].HasMember("uri")) {
            const auto& uri = images_data[i]["uri"];
            assert(uri.IsString());
            image.uri = uri.GetString();
        } // if
        if (images_data[i].HasMember("mimeType")) {
            const auto& mime_type = images_data[i]["mimeType"];
            assert(mime_type.IsString());
            image.mime_type = mime_type.GetString();
        } // if
        images.push_back(image);
    } // for
    return true;
}
bool my::GLTFData::LoadSampler(const rapidjson::Document& document) {
    if (!document.HasMember("samplers")) {
        return false;
    } // if
    const auto& samplers_data = document["samplers"];
    assert(samplers_data.IsArray());

    auto n = samplers_data.Size();
    samplers.reserve(n);
    for (size_t i = 0; i < n; i++) {
        auto sampler = Sampler();

        if (samplers_data[i].HasMember("magFilter")) {
            const auto& mag_filter = samplers_data[i]["magFilter"];
            assert(mag_filter.IsInt());
            sampler.mag_filter = mag_filter.GetInt();
        } // if
        if (samplers_data[i].HasMember("minFilter")) {
            const auto& min_filter = samplers_data[i]["minFilter"];
            assert(min_filter.IsInt());
            sampler.min_filter = min_filter.GetInt();
        } // if
        if (samplers_data[i].HasMember("wrapS")) {
            const auto& wrap_s = samplers_data[i]["wrapS"];
            assert(wrap_s.IsInt());
            sampler.wrap_s = wrap_s.GetInt();
        } // if
        if (samplers_data[i].HasMember("wrapT")) {
            const auto& wrap_t = samplers_data[i]["wrapT"];
            assert(wrap_t.IsInt());
            sampler.wrap_t = wrap_t.GetInt();
        } // if
        samplers.push_back(sampler);
    } // for
    return true;
}

bool my::GLTFData::LoadCamera(const rapidjson::Document& document) {
    if (!document.HasMember("cameras")) {
        return false;
    } // if
    const auto& cameras_data = document["cameras"];
    assert(cameras_data.IsArray());

    auto n = cameras_data.Size();
    cameras.reserve(n);
    for (size_t i = 0; i < n; i++) {
        auto camera = Camera();

        // type 
        if (cameras_data[i].HasMember("type")) {
            const auto& type = cameras_data[i]["type"];
            assert(type.IsString());
            camera.type = type.GetString();
        } // if
        // perspective
        if (cameras_data[i].HasMember("perspective")) {
            auto perspective = Camera::Perspective();
            const auto& perspective_data = cameras_data[i]["perspective"];
            assert(perspective_data.IsObject());
            // aspect
            if (perspective_data.HasMember("aspectRatio")) {
                const auto& aspect_ratio = perspective_data["aspectRatio"];
                assert(aspect_ratio.IsFloat());
                camera.perspective.aspect_ratio = aspect_ratio.GetFloat();
            } // if
            // yfov
            if (perspective_data.HasMember("yfov")) {
                const auto& yfov = perspective_data["yfov"];
                assert(yfov.IsFloat());
                camera.perspective.yfov = yfov.GetFloat();
            } // if
            // zfar
            if (perspective_data.HasMember("zfar")) {
                const auto& zfar = perspective_data["zfar"];
                assert(zfar.IsInt() || zfar.IsFloat());
                camera.perspective.zfar = zfar.GetFloat();
            } // if
            // znear
            if (perspective_data.HasMember("znear")) {
                const auto& znear = perspective_data["znear"];
                assert(znear.IsFloat());
                camera.perspective.znear = znear.GetFloat();
            } // if
        } // if

        // orthographic
        if (cameras_data[i].HasMember("orthographic")) {
            auto orthographic = Camera::Orthographic();
            const auto& orthographic_data = cameras_data[i]["orthographic"];
            assert(orthographic_data.IsObject());
            // xmag 
            if (orthographic_data.HasMember("xmag")) {
                const auto& xmag = orthographic_data["xmag"];
                assert(xmag.IsFloat());
                camera.orthographic.xmag = xmag.GetFloat();
            } // if
            // ymag
            if (orthographic_data.HasMember("ymag")) {
                const auto& ymag = orthographic_data["ymag"];
                assert(ymag.IsFloat());
                camera.orthographic.ymag = ymag.GetFloat();
            } // if
            // zfar
            if (orthographic_data.HasMember("zfar")) {
                const auto& zfar = orthographic_data["zfar"];
                assert(zfar.IsInt() || zfar.IsFloat());
                camera.orthographic.zfar = zfar.GetFloat();
            } // if
            // znear
            if (orthographic_data.HasMember("znear")) {
                const auto& znear = orthographic_data["znear"];
                assert(znear.IsFloat());
                camera.orthographic.znear = znear.GetFloat();
            } // if
        } // if
        cameras.push_back(camera);
    } // for
    return true;
}
bool my::GLTFData::LoadSkin(const rapidjson::Document& document) {
    if (!document.HasMember("skins")) {
        return false;
    } // if
    const auto& skins_data = document["skins"];
    assert(skins_data.IsArray());

    auto n = skins_data.Size();
    skins.reserve(n);
    for (size_t i = 0; i < n; i++) {
        auto skin = Skin();
        // inverse bind matrices
        if (skins_data[i].HasMember("inverseBindMatrices")) {
            const auto& inverse_bind_matrices = skins_data[i]["inverseBindMatrices"];
            assert(inverse_bind_matrices.IsInt());
            skin.inverse_bind_matrices = inverse_bind_matrices.GetInt();
        } // if
        // skeleton
        if (skins_data[i].HasMember("skeleton")) {
            const auto& skeleton = skins_data[i]["skeleton"];
            assert(skeleton.IsInt());
            skin.skeleton = skeleton.GetInt();
        } // if
        // joints
        if (skins_data[i].HasMember("joints")) {
            const auto& joints = skins_data[i]["joints"];
            assert(joints.IsArray());

            auto m = joints.Size();
            for (size_t j = 0; j < m; j++) {
                assert(joints[j].IsInt());
                skin.joints.push_back(joints[j].GetInt());
            } // for
        } // if
        skins.push_back(skin);
    } // for
    return true;
}

bool my::GLTFData::LoadAnimation(const rapidjson::Document& document) {
    if (!document.HasMember("animations")) {
        return false;
    } // if
    const auto& animations_data = document["animations"];
    assert(animations_data.IsArray());
    auto n = animations_data.Size();
    animations.reserve(n);
    for (size_t i = 0; i < n; i++) {
        auto animation = Animation();

        // name
        if (animations_data[i].HasMember("name")) {
            const auto& name = animations_data[i]["name"];
            assert(name.IsString());
            animation.name = name.GetString();
        } // if
        // samplers
        if (animations_data[i].HasMember("samplers")) {
            auto sampler = Animation::Sampler();
            const auto& samplers = animations_data[i]["samplers"];
            assert(samplers.IsArray());
            auto m = samplers.Size();
            for (size_t j = 0; j < m; j++) {
                // input
                if (samplers[j].HasMember("input")) {
                    const auto& input = samplers[j]["input"];
                    assert(input.IsInt());
                    sampler.input_index = input.GetInt();
                } // if
                // output
                if (samplers[j].HasMember("output")) {
                    const auto& output = samplers[j]["output"];
                    assert(output.IsInt());
                    sampler.output_index = output.GetInt();
                } // if
                // interpolation
                if (samplers[j].HasMember("interpolation")) {
                    const auto& interpolation = samplers[j]["interpolation"];
                    assert(interpolation.IsString());
                    sampler.interpolation = interpolation.GetString();
                } // if
                animation.samplers.push_back(sampler);
            } // for
        } // if

        // channels
        if (animations_data[i].HasMember("channels")) {
            auto channel = Animation::Channel();
            const auto& channels = animations_data[i]["channels"];
            assert(channels.IsArray());
            auto m = channels.Size();
            for (size_t j = 0; j < m; j++) {
                // sampler
                if (channels[j].HasMember("sampler")) {
                    const auto& sampler = channels[j]["sampler"];
                    assert(sampler.IsInt());
                    channel.sampler_index = sampler.GetInt();
                } // if
                // target
                if (channels[j].HasMember("target")) {
                    const auto& target = channels[j]["target"];
                    assert(target.IsObject());
                    // node
                    if (target.HasMember("node")) {
                        const auto& index = target["node"];
                        channel.target.node_index = index.GetInt();
                    } // if
                    // path
                    if (target.HasMember("path")) {
                        const auto& path = target["path"].GetString();
                        channel.target.path = path;
                    } // if
                } // if
                animation.channels.push_back(channel);
            } // for
        } // if

        animations.push_back(animation);
    } // for
    return true;
}
my::GLTFData::GLTFData() :
    directory_path(),
    asset(),
    general_scene(),
    scenes(),
    nodes(),
    meshes(),
    accessors(),
    buffer_views(),
    buffers(),
    binarys(),
    materials(),
    textures(),
    images(),
    samplers(),
    cameras(),
    skins(),
    animations() {
}

my::GLTFData::~GLTFData() {
}

bool my::GLTFData::Load(const char* path) {
    directory_path = path;
    auto pos = directory_path.rfind("/");
    directory_path = std::string(path, path + pos + 1);

    rapidjson::Document document;
    if (!ut::ParseJsonDocument(path, document)) {
        return false;
    } // if

    this->LoadAsset(document);
    this->LoadExtensionsRequired(document);
    this->LoadExtensionsUsed(document);
    this->LoadScene(document);
    this->LoadNode(document);
    this->LoadMesh(document);
    this->LoadAccessor(document);
    this->LoadBufferView(document);
    this->LoadBuffer(document);
    this->LoadBinary();
    this->LoadMaterial(document);
    this->LoadTexture(document);
    this->LoadImage(document);
    this->LoadSampler(document);
    this->LoadCamera(document);
    this->LoadSkin(document);
    this->LoadAnimation(document);
    return true;
}

void* my::GLTFData::BinaryData(const int accessor_key) {
    if (accessor_key == -1) {
        return nullptr;
    } // if

    auto& accessor = accessors.at(accessor_key);
    auto& buffer_view = buffer_views.at(accessor.buffer_view_index);
    auto& buffer = buffers.at(buffer_view.buffer_index);

    auto offset_accessor = accessor.buffer_byte_offset;
    auto offset_view = buffer_view.byte_offset;
    auto offset = offset_accessor + offset_view;

    for (auto& binary : binarys) {
        if (binary.uri == buffer.uri) {
            return reinterpret_cast<void*>(&binary.data.at(offset));
        } // if
    } // for

    return nullptr;
}