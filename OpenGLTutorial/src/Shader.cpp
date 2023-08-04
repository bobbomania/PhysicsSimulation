#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"


Shader::Shader(const std::string& filepath)
    : m_FilePath(filepath), m_RendererID(0)
{

    // working directory is relative to the project directory
    ShaderProgramSource source = ParseShader(filepath);

    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

// parse our .shader file into the vertex and fragment shader
ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos) {
                // set mode to vertex
                type = ShaderType::VERTEX;

            }
            else if (line.find("fragment") != std::string::npos) {
                // set mode to fragment
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            if (type != ShaderType::NONE) {
                // first element is the vertex shader, the second one is the fragment shader
                ss[(int)type] << line << '\n';
            }
        }
    }

    return { ss[0].str(), ss[1].str() };
}

// here we pass on the type of the shader, and the source code to compile in the GPU
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    // create new id for shader
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); // equivalent of &source[0]

    // add the source to the id for the shader
    glShaderSource(id, 1, &src, nullptr);

    // compile the shader code
    glCompileShader(id);

    int res;

    //return the value of parameter : gl_compile_status
    glGetShaderiv(id, GL_COMPILE_STATUS, &res);

    if (res == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        // allocates enough space for the message on the STACK
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << ((type == GL_VERTEX_SHADER) ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);

        return 0;
    }

    return id;

}


// create, compile and link shaders into the program given shader source code
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // id for the shader program
    unsigned int program = glCreateProgram();

    // id for the vertex shader program
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // attaching both files with ids
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    // linking the program
    glLinkProgram(program);

    // checks if the executables in program can execute in this context
    glValidateProgram(program);

    // delete the intermediary steps
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniform1iv(const std::string& name, int count, int* v0)
{
    GLCall(glUniform1iv(GetUniformLocation(name), count, v0));
}

void Shader::SetUniform1i(const std::string& name, int v0)
{
    GLCall(glUniform1i(GetUniformLocation(name), v0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];


    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}
