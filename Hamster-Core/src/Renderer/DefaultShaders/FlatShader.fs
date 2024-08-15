#version 400 core

// in vec2 TexCoords;
uniform vec3 colour;

out vec4 FragColour;

// uniform sampler2D image;
// uniform vec3 spriteColour;

void main()
{
//     FragColour = vec4(spriteColour, 1.0) * texture(image, TexCoords);

    FragColour = vec4(colour, 1.0);

//     FragColour = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}

