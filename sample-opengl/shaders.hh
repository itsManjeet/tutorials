#ifndef _SHADERS_H_
#define _SHADERS_H_

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>

inline unsigned int gen_shader_program(std::string const &shaders_dir)
{
    std::vector<unsigned int> shaders;

    for (auto const &shader : std::filesystem::directory_iterator(shaders_dir))
    {
        int result;
        unsigned int type,
            shader_id;
        char const *src;

        if (shader.path().filename() == "vertex")
            type = GL_VERTEX_SHADER;
        else if (shader.path().filename() == "fragment")
            type = GL_FRAGMENT_SHADER;
        else
            throw std::runtime_error("Invalid shader file '" + shader.path().filename().string() + "'");

        shader_id = glCreateShader(type);
        std::ifstream file(shader.path());

        std::string source_code((std::istreambuf_iterator<char>(file)),
                                (std::istreambuf_iterator<char>()));

        src = source_code.c_str();
        glShaderSource(shader_id, 1, &src, nullptr);
        glCompileShader(shader_id);
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
        if (!result)
        {
            int len;
            glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
            char *mesg = (char *)alloca(len);
            glGetShaderInfoLog(shader_id, len, &len, mesg);

            std::cerr << "Error! failed to compile shader " << shader.path().filename() << std::endl;
            std::cerr << mesg << std::endl;

            glDeleteShader(shader_id);
            return 0;
        }
        shaders.push_back(shader_id);
    }

    if (shaders.size() == 0)
    {
        std::cerr << "Error! no shader found" << std::endl;
        return 0;
    }

    unsigned int program = glCreateProgram();

    for (auto i : shaders)
        glAttachShader(program, i);

    glLinkProgram(program);
    glValidateProgram(program);

    for (auto i : shaders)
        glDeleteShader(i);

    return program;
}

#endif