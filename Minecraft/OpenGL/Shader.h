#pragma once
#include "../Core.h"
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader {
public:
    Shader();
    explicit Shader(const std::string&  path, bool debug = false);
    ~Shader();
    void Bind();
    inline unsigned int GetProgram() const {return m_Program;}
    void SetUniformInt(const char* name, int value);
    void SetUniformIntArray(const char* name, int size, const int* data);
    void SetUniformFloat(const char* name, float value);
    void SetUniformFloatArray(const char* name, int size, const float* data);
    void SetUniformVec2(const char* name, const glm::vec2& vec2);
    void SetUniformVec2Array(const char* name, int size, const float* data);
    void SetUniformVec3(const char* name, const glm::vec3& vec3);
    void SetUniformVec3Array(const char* name, int size, const float* data);
    void SetUniformVec4(const char* name, const glm::vec4& vec4);
    void SetUniformVec4Array( const char* name, int size, const float* data);
    void SetUniformBool( const char* name, bool value);
    void SetUniformBoolArray( const char* name, int size,const bool* data);
    void SetUniformMatrix4f( const char* name, const glm::mat4& mat);
private:
    unsigned int compileShader(unsigned int type, const char *source);
    bool m_Debug = false;
    std::string m_Path;
    unsigned int m_Program = 0;
    unsigned int m_Vertex = 0;
    unsigned int m_Fragment = 0;
    unsigned int m_Geometry = 0;
    unsigned int m_TessellationControl = 0;
    unsigned int m_TessellationEvaluation  = 0;
    unsigned int m_Compute = 0;
    std::unordered_map<std::string, unsigned int> m_Locations;
};
