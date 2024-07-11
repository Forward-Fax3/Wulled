#pragma once
#include "Engine/src/Core/EngineCore.h"
#include "Engine/src/Core/Graphics/Renderer/ShaderDataType.h"

#include "shaderc/shaderc.hpp"

#include "glm/glm.hpp"

#include <string>
#include <vector>


namespace WLD
{
	enum class WLD_ShaderType : uint8_t
	{
		None = 0,
		Vertex,
		Fragment,
		Pixel = Fragment,

		// future shader types
//		Compute,
//		Geometry,
//		TessellationControl,
//		TessellationEvaluation,

		// Ray Tracing (hopefully)
//		RayGen,
//		RayAnyHit,
//		RayClosestHit,
//		RayMiss,
//		RayIntersection,
	};

	struct InputShader // At the moment, only supports GLSL shaders and only from a file
	{
		WLD_ShaderType type = WLD_ShaderType::None;
		std::string source;
//		bool isFromFile = false;
//		bool isCompiled = false;
	};

	struct PushConstOpaqueObj
	{
		ShaderDataType type = ShaderDataType::None;
		uint32_t arraySize = 1;
	};

	class WLD_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat2(const std::string& name, const glm::mat2& value) = 0;
		virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual void SetPushConst(const std::string& UBName, const std::vector<PushConstOpaqueObj>& layout, const void* data) = 0;

		static Shader* Create(const std::vector<InputShader>& shaders);

	protected:
		std::vector<uint32_t> CompileToVkSPIRV(const std::string& source, const std::string& filePath, shaderc_shader_kind shaderType) const;
	};
}
