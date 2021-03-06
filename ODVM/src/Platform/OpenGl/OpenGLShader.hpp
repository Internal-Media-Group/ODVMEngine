#pragma once
#include "ODVM/Renderer/Shader.hpp"

#include <glad/glad.h>

namespace ODVM
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& path);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformInt(const std::string& name, int value) override;
		virtual void UploadUniformFloat(const std::string& name, float value) override;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vec2) override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vec3) override;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& mat3) override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vec4) override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& mat4) override;

		virtual std::string& GetName() override { return m_Name; };


		void SetInt(const std::string& name, int value) override;

		void SetFloat(const std::string& name, float value) override;
		void SetFloat2(const std::string& name, const glm::vec2& vec2) override;
		void SetFloat3(const std::string& name, const glm::vec3& vec3) override;
		void SetFloat4(const std::string& name, const glm::vec4& vec4) override;

		void SetMat3(const std::string& name, const glm::mat3& mat3) override;
		void SetMat4(const std::string& name, const glm::mat4& mat4) override;

	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrc);

	private:
		uint32_t m_RendererID;

		std::string m_Name;

	};


}
