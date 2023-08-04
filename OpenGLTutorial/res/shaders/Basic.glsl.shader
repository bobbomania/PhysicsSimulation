// shader source code
#shader vertex
#version 330 core
// attribute is located at index 0 ( === layout(location = 0) )
// opengl automatically casts our 2-vector into a 4-vector as it knows its a 2-vecctor from glVertexAttribPointer
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

// model view projection matrix
uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * position;
   v_TexCoord = texCoord;
};

//fragment source code
#shader fragment
#version 330 core

// attribute is located at index 0 ( === layout(location = 0) )
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

// uniform value from cpus
uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	// for showy/ changing stuff
	//color = u_Color;
	color = texColor * u_Color;
};