#include "odvmpch.h"
#include "Renderer3D.hpp"

#include "Buffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RenderCommand.hpp"

#include <unordered_map>

#include "OBJ_Loader.h"

namespace ODVM
{
    struct Renderer3DData
    {
        Ref<VertexBuffer> CubeVB;
        Ref<IndexBuffer> CubeIB;
        Ref<VertexArray> CubeVA;
        Ref<Shader> TDShader;
        Ref<Shader> TDTShader;
        Ref<VertexBuffer> CubeTVB;
        Ref<IndexBuffer> CubeTIB;
        Ref<VertexArray> CubeTVA;
        std::unordered_map<std::string, objl::Loader> loadedModels;
    };

    static Renderer3DData s_3DData;

    void Renderer3D::Init()
    {
        ODVM_PROFILE_FUNCTION();

        s_3DData.CubeVA = VertexArray::Create();

        float cubeVertices[36 * 3] = {
            -0.5f, -0.5f, -0.5f, 
            0.5f, -0.5f, -0.5f,  
            0.5f,  0.5f, -0.5f,  
            0.5f,  0.5f, -0.5f,  
            -0.5f,  0.5f, -0.5f,  
            -0.5f, -0.5f, -0.5f,  
            -0.5f, -0.5f,  0.5f,  
            0.5f, -0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f,  0.5f,  
            -0.5f, -0.5f,  0.5f,  
            -0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f, -0.5f,  
            -0.5f, -0.5f, -0.5f,  
            -0.5f, -0.5f, -0.5f,  
            -0.5f, -0.5f,  0.5f,  
            -0.5f,  0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f,  
            0.5f,  0.5f, -0.5f,  
            0.5f, -0.5f, -0.5f,  
            0.5f, -0.5f, -0.5f,  
            0.5f, -0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f,  
            -0.5f, -0.5f, -0.5f,  
            0.5f, -0.5f, -0.5f,  
            0.5f, -0.5f,  0.5f,  
            0.5f, -0.5f,  0.5f,  
            -0.5f, -0.5f,  0.5f,  
            -0.5f, -0.5f, -0.5f,  
            -0.5f,  0.5f, -0.5f,  
            0.5f,  0.5f, -0.5f,  
            0.5f,  0.5f,  0.5f,  
            0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f,  0.5f,  
            -0.5f,  0.5f, -0.5f
        };
        
        s_3DData.CubeVB = VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));

        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"}
        };
        
        s_3DData.CubeVB->SetLayout(layout);
        s_3DData.CubeVA->AddVertexBuffer(s_3DData.CubeVB);

        uint32_t indices[36] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
        s_3DData.CubeIB = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        s_3DData.CubeVA->SetIndexBuffer(s_3DData.CubeIB);

        s_3DData.TDShader = Shader::Create("assets/shaders/3D.glsl");

        s_3DData.CubeTVA = VertexArray::Create();

        float cubeTVertices[36 * 5] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
        
        s_3DData.CubeTVB = VertexBuffer::Create(cubeTVertices, sizeof(cubeTVertices));

        BufferLayout Tlayout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float2, "a_TextureCoords"}
        };
        
        s_3DData.CubeTVB->SetLayout(Tlayout);
        s_3DData.CubeTVA->AddVertexBuffer(s_3DData.CubeTVB);

        uint32_t Tindices[36] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
        s_3DData.CubeTIB = IndexBuffer::Create(Tindices, sizeof(Tindices) / sizeof(uint32_t));
        s_3DData.CubeTVA->SetIndexBuffer(s_3DData.CubeTIB);

        s_3DData.TDTShader = Shader::Create("assets/shaders/3DTS.glsl");
    }

    void Renderer3D::BeginScene(const PerspectiveCamera& camera)
    {
        s_3DData.TDShader->Bind();
        s_3DData.TDShader->SetMat4("u_View", camera.GetViewMatrix());
        s_3DData.TDShader->SetMat4("u_Projection", camera.GetProjectionMatrix());

        s_3DData.TDTShader->Bind();
        s_3DData.TDTShader->SetMat4("u_View", camera.GetViewMatrix());
        s_3DData.TDTShader->SetMat4("u_Projection", camera.GetProjectionMatrix());

    }

    void Renderer3D::EndScene()
    {

    }

    void Renderer3D::DrawCube(const glm::vec3& pos, const glm::vec4& color)
    {
        s_3DData.TDShader->Bind();
        s_3DData.TDShader->SetFloat4("u_Color", color);
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        s_3DData.TDShader->SetMat4("u_Model", model);

        RenderCommand::DrawIndexed(s_3DData.CubeVA, 36);
    }

    void Renderer3D::DrawCube(const glm::vec3& pos, const Ref<Texture2D> texture)
    {
        s_3DData.TDTShader->Bind();
        texture->Bind();
        s_3DData.TDTShader->SetInt("u_Texture", 0);
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        s_3DData.TDTShader->SetMat4("u_Model", model);

        RenderCommand::DrawIndexed(s_3DData.CubeTVA, 36);
    }

    void Renderer3D::DrawModel(const glm::vec3& pos, std::string& path, const glm::vec4& color)
    {
        s_3DData.TDShader->Bind();

        bool loaded = false;
        objl::Loader loader;

        for(auto i = s_3DData.loadedModels.begin(); i != s_3DData.loadedModels.end(); i++)
        {
            loaded = i->first == path;
            if(loaded)
            {
                loader = i->second;
            }
        }

        if(!loaded)
        {
            bool loadout = loader.LoadFile(path);
            loaded = loadout;
            s_3DData.loadedModels.emplace(path, loader);
        }
        uint64_t size = 0;
        float* vertices;

        uint32_t offset = 0;
        uint32_t* indices;
        uint32_t indicesSize = 0;
        if(loaded)
        {
            for(int i = 0; i < loader.LoadedMeshes.size(); i++)
            {
                
                objl::Mesh mesh = loader.LoadedMeshes[i];
                size += mesh.Vertices.size() * 3;
                for(int j = 0; j < mesh.Vertices.size(); j++)
                {
                    //vertices[offset] = mesh.Vertices[j].Position.X;
                    //offset++;
                    //vertices[offset] = mesh.Vertices[j].Position.Y;
                    //offset++;
                    //vertices[offset] = mesh.Vertices[j].Position.Z;
                    //offset++;
                    //ODVM_CORE_INFO("{0}", vertices[offset]);
                }
                for(int j = 0; j < mesh.Indices.size(); j++)
                {
                    //indices[j] = mesh.Indices[j];
                }
                indicesSize += mesh.Indices.size();
            }
        }



        indices = new uint32_t[indicesSize];
        vertices = new float[size];

        for (int i = 0; i < loader.LoadedMeshes.size(); i++)
        {

            objl::Mesh mesh = loader.LoadedMeshes[i];
            //size += mesh.Vertices.size() * 3;
            for (int j = 0; j < mesh.Vertices.size(); j++)
            {
                vertices[offset] = mesh.Vertices[j].Position.X;
                offset++;
                vertices[offset] = mesh.Vertices[j].Position.Y;
                offset++;
                vertices[offset] = mesh.Vertices[j].Position.Z;
                offset++;
                //ODVM_CORE_INFO("{0}", vertices[offset]);
            }
            for (int j = 0; j < mesh.Indices.size(); j++)
            {
                indices[j] = mesh.Indices[j];
            }
            //indicesSize += mesh.Indices.size();
        }
        
        Ref<VertexArray> mVA = VertexArray::Create();
        mVA->Bind();
        Ref<VertexBuffer> mVB = VertexBuffer::Create(vertices, size * sizeof(float));
        mVB->Bind();
        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"}
        };
        mVB->SetLayout(layout);

        mVA->AddVertexBuffer(mVB);
        Ref<IndexBuffer> mIB = IndexBuffer::Create(indices, indicesSize);
        mIB->Bind();
        mVA->SetIndexBuffer(mIB);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        s_3DData.TDShader->SetMat4("u_Model", model);

        s_3DData.TDShader->SetFloat4("u_Color", color);


        RenderCommand::DrawIndexed(mVA);
    }
}