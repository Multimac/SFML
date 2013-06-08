////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2013 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/opengl_2/Shader_2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/GLCheck.hpp>
#include <SFML/System/InputStream.hpp>
#include <SFML/System/Err.hpp>
#include <fstream>


namespace sf
{
////////////////////////////////////////////////////////////
bool Shader_2::loadFromFile(const std::string& filename, Type type)
{
    if(type != Geometry)
        return Shader::loadFromFile(filename, type);
    else
    {
        err() << "Cannot load geometry shaders in OpenGL 2.0" << std::endl;
        return false;
    }
}


////////////////////////////////////////////////////////////
bool Shader_2::loadFromFile(const std::string& vertexShaderFilename, const std::string& geometryShaderFilename, const std::string& fragmentShaderFilename)
{
    if(geometryShaderFilename.size() > 0)
        err() << "Cannot load geometry shaders in OpenGL 2.0" << std::endl;

    return Shader::loadFromFile(vertexShaderFilename, std::string(), fragmentShaderFilename);
}


////////////////////////////////////////////////////////////
bool Shader_2::loadFromMemory(const std::string& shader, Type type)
{
    if(type != Geometry)
        return Shader::loadFromMemory(shader, type);
    else
    {
        err() << "Cannot load geometry shaders in OpenGL 2.0" << std::endl;
        return false;
    }
}


////////////////////////////////////////////////////////////
bool Shader_2::loadFromMemory(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader)
{
    if(geometryShader.size() > 0)
        err() << "Cannot load geometry shaders in OpenGL 2.0" << std::endl;

    // Compile the shader program
    return compile(vertexShader.c_str(), NULL, fragmentShader.c_str());
}


////////////////////////////////////////////////////////////
bool Shader_2::loadFromStream(InputStream& stream, Type type)
{
    if(type != Geometry)
        return Shader::loadFromStream(stream, type);
    else
    {
        err() << "Cannot load geometry shaders in OpenGL 2.0" << std::endl;
        return false;
    }
}


////////////////////////////////////////////////////////////
bool Shader_2::loadFromStream(InputStream& vertexShaderStream, InputStream& geometryShaderStream, InputStream& fragmentShaderStream)
{
    if(geometryShaderStream.getSize() > 0)
        err() << "Cannot load geometry shaders in OpenGL 2.0" << std::endl;

    // Read the vertex shader code from the stream
    std::vector<char> vertexShader;
    if (!getStreamContents(vertexShaderStream, vertexShader))
    {
        err() << "Failed to read vertex shader from stream" << std::endl;
        return false;
    }

    // Read the fragment shader code from the stream
    std::vector<char> fragmentShader;
    if (!getStreamContents(fragmentShaderStream, fragmentShader))
    {
        err() << "Failed to read fragment shader from stream" << std::endl;
        return false;
    }

    // Compile the shader program
    return compile(&vertexShader[0], NULL, &fragmentShader[0]);
}


////////////////////////////////////////////////////////////
void Shader_2::setParameter(const std::string& name, float x)
{
    if (m_shaderProgram)
    {
        ensureGlContext();

        // Enable program
        GLhandleARB program = glGetHandleARB(GL_PROGRAM_OBJECT_ARB);
        glCheck(glUseProgramObjectARB(m_shaderProgram));

        // Get parameter location and assign it new values
        GLint location = glGetUniformLocationARB(m_shaderProgram, name.c_str());
        if (location != -1)
            glCheck(glUniform1fARB(location, x));
        else
            err() << "Parameter \"" << name << "\" not found in shader" << std::endl;

        // Disable program
        glCheck(glUseProgramObjectARB(program));
    }
}


////////////////////////////////////////////////////////////
void Shader_2::setParameter(const std::string& name, float x, float y)
{
    if (m_shaderProgram)
    {
        ensureGlContext();

        // Enable program
        GLhandleARB program = glGetHandleARB(GL_PROGRAM_OBJECT_ARB);
        glCheck(glUseProgramObjectARB(m_shaderProgram));

        // Get parameter location and assign it new values
        GLint location = glGetUniformLocationARB(m_shaderProgram, name.c_str());
        if (location != -1)
            glCheck(glUniform2fARB(location, x, y));
        else
            err() << "Parameter \"" << name << "\" not found in shader" << std::endl;

        // Disable program
        glCheck(glUseProgramObjectARB(program));
    }
}


////////////////////////////////////////////////////////////
void Shader_2::setParameter(const std::string& name, float x, float y, float z)
{
    if (m_shaderProgram)
    {
        ensureGlContext();

        // Enable program
        GLhandleARB program = glGetHandleARB(GL_PROGRAM_OBJECT_ARB);
        glCheck(glUseProgramObjectARB(m_shaderProgram));

        // Get parameter location and assign it new values
        GLint location = glGetUniformLocationARB(m_shaderProgram, name.c_str());
        if (location != -1)
            glCheck(glUniform3fARB(location, x, y, z));
        else
            err() << "Parameter \"" << name << "\" not found in shader" << std::endl;

        // Disable program
        glCheck(glUseProgramObjectARB(program));
    }
}


////////////////////////////////////////////////////////////
void Shader_2::setParameter(const std::string& name, float x, float y, float z, float w)
{
    if (m_shaderProgram)
    {
        ensureGlContext();

        // Enable program
        GLhandleARB program = glGetHandleARB(GL_PROGRAM_OBJECT_ARB);
        glCheck(glUseProgramObjectARB(m_shaderProgram));

        // Get parameter location and assign it new values
        GLint location = glGetUniformLocationARB(m_shaderProgram, name.c_str());
        if (location != -1)
            glCheck(glUniform4fARB(location, x, y, z, w));
        else
            err() << "Parameter \"" << name << "\" not found in shader" << std::endl;

        // Disable program
        glCheck(glUseProgramObjectARB(program));
    }
}


////////////////////////////////////////////////////////////
void Shader_2::setParameter(const std::string& name, const Vector2f& v)
{
    setParameter(name, v.x, v.y);
}


////////////////////////////////////////////////////////////
void Shader_2::setParameter(const std::string& name, const Vector3f& v)
{
    setParameter(name, v.x, v.y, v.z);
}


////////////////////////////////////////////////////////////
void Shader_2::setParameter(const std::string& name, const Color& color)
{
    setParameter(name, color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
}


////////////////////////////////////////////////////////////
void Shader_2::setParameter(const std::string& name, const sf::Transform& transform)
{
    if (m_shaderProgram)
    {
        ensureGlContext();

        // Enable program
        GLhandleARB program = glGetHandleARB(GL_PROGRAM_OBJECT_ARB);
        glCheck(glUseProgramObjectARB(m_shaderProgram));

        // Get parameter location and assign it new values
        GLint location = glGetUniformLocationARB(m_shaderProgram, name.c_str());
        if (location != -1)
            glCheck(glUniformMatrix4fvARB(location, 1, GL_FALSE, transform.getMatrix()));
        else
            err() << "Parameter \"" << name << "\" not found in shader" << std::endl;

        // Disable program
        glCheck(glUseProgramObjectARB(program));
    }
}


////////////////////////////////////////////////////////////
void Shader_2::setParameter(const std::string& name, const Texture& texture)
{
    if (m_shaderProgram)
    {
        ensureGlContext();

        // Find the location of the variable in the shader
        int location = glGetUniformLocationARB(m_shaderProgram, name.c_str());
        if (location == -1)
        {
            err() << "Texture \"" << name << "\" not found in shader" << std::endl;
            return;
        }

        // Store the location -> texture mapping
        TextureTable::iterator it = m_textures.find(location);
        if (it == m_textures.end())
        {
            // New entry, make sure there are enough texture units
            static const GLint maxUnits = getMaxTextureUnits();
            if (m_textures.size() + 1 >= static_cast<std::size_t>(maxUnits))
            {
                err() << "Impossible to use texture \"" << name << "\" for shader: all available texture units are used" << std::endl;
                return;
            }

            m_textures[location] = &texture;
        }
        else
        {
            // Location already used, just replace the texture
            it->second = &texture;
        }
    }
}


////////////////////////////////////////////////////////////
void Shader_2::setParameter(const std::string& name, CurrentTextureType)
{
    if (m_shaderProgram)
    {
        ensureGlContext();

        // Find the location of the variable in the shader
        m_currentTexture = glGetUniformLocationARB(m_shaderProgram, name.c_str());
        if (m_currentTexture == -1)
            err() << "Texture \"" << name << "\" not found in shader" << std::endl;
    }
}

} // namespace sf
