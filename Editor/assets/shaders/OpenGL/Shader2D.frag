#version 440 core

layout (location = 0) out vec4 color;
layout (location = 1) out int id;

uniform sampler2D u_Textures[32];

in vec4 v_Color;
in vec2 v_texCoord;
in flat float v_TexIndex;
in flat int v_ID;

void main()
{
	// Texture + Tint (batch)
	vec4 texColor = v_Color;
	switch(int(v_TexIndex)){
		default: break;
		case 1: texColor *= texture(u_Textures[1], v_texCoord) * v_Color; break;
		case 2: texColor *= texture(u_Textures[2], v_texCoord) * v_Color; break;
		case 3: texColor *= texture(u_Textures[3], v_texCoord) * v_Color; break;
		case 4: texColor *= texture(u_Textures[4], v_texCoord) * v_Color; break;
		case 5: texColor *= texture(u_Textures[5], v_texCoord) * v_Color; break;
		case 6: texColor *= texture(u_Textures[6], v_texCoord) * v_Color; break;
		case 7: texColor *= texture(u_Textures[7], v_texCoord) * v_Color; break;
		case 8: texColor *= texture(u_Textures[8], v_texCoord) * v_Color; break;
		case 9: texColor *= texture(u_Textures[9], v_texCoord) * v_Color; break;
		case 10: texColor *= texture(u_Textures[10], v_texCoord) * v_Color; break;
		case 11: texColor *= texture(u_Textures[11], v_texCoord) * v_Color; break;
		case 12: texColor *= texture(u_Textures[12], v_texCoord) * v_Color; break;
		case 13: texColor *= texture(u_Textures[13], v_texCoord) * v_Color; break;
		case 14: texColor *= texture(u_Textures[14], v_texCoord) * v_Color; break;
		case 15: texColor *= texture(u_Textures[15], v_texCoord) * v_Color; break;
		case 16: texColor *= texture(u_Textures[16], v_texCoord) * v_Color; break;
		case 17: texColor *= texture(u_Textures[17], v_texCoord) * v_Color; break;
		case 18: texColor *= texture(u_Textures[18], v_texCoord) * v_Color; break;
		case 19: texColor *= texture(u_Textures[19], v_texCoord) * v_Color; break;
		case 20: texColor *= texture(u_Textures[20], v_texCoord) * v_Color; break;
		case 21: texColor *= texture(u_Textures[21], v_texCoord) * v_Color; break;
		case 22: texColor *= texture(u_Textures[22], v_texCoord) * v_Color; break;
		case 23: texColor *= texture(u_Textures[23], v_texCoord) * v_Color; break;
		case 24: texColor *= texture(u_Textures[24], v_texCoord) * v_Color; break;
		case 25: texColor *= texture(u_Textures[25], v_texCoord) * v_Color; break;
		case 26: texColor *= texture(u_Textures[26], v_texCoord) * v_Color; break;
		case 27: texColor *= texture(u_Textures[27], v_texCoord) * v_Color; break;
		case 28: texColor *= texture(u_Textures[28], v_texCoord) * v_Color; break;
		case 29: texColor *= texture(u_Textures[29], v_texCoord) * v_Color; break;
		case 30: texColor *= texture(u_Textures[30], v_texCoord) * v_Color; break;
		case 31: texColor *= texture(u_Textures[31], v_texCoord) * v_Color; break;
	}
	color = texColor;
	id = v_ID; // EntityID placeholder
}
