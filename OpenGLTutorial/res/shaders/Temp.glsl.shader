// shader source code
#shader vertex
#version 330 core
// attribute is located at index 0 ( === layout(location = 0) )
// opengl automatically casts our 2-vector into a 4-vector as it knows its a 2-vecctor from glVertexAttribPointer
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texIndex;

out vec2 v_TexCoord;
out float v_TexIndex;

// model view projection matrix
uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord;
    v_TexIndex = texIndex;
};

//fragment source code
#shader fragment
#version 330 core

// attribute is located at index 0 ( === layout(location = 0) )
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex;

// uniform value from cpus
uniform sampler2D u_Textures[2];

void main()
{
    int index = int(v_TexIndex);
    color = texture(u_Textures[index], v_TexCoord);
    //color = vec4(v_TexIndex, v_TexIndex, v_TexIndex, 1.0f);
};