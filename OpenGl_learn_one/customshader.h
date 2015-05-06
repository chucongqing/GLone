#ifndef _c_s_h_
#define _c_s_h_

const char* vShader = 
	"#version 330 core\n"
	"uniform Uniforms {"
	" vec3 translation;"
	" float scale;"
	" vec4 rotation;"
	" bool enabled;"
	"};"
	"in vec2 vPos;"
	"in vec3 vColor;"
	"out vec4 fColor;"
	"void main()"
	"{"
	" vec3 pos = vec3(vPos, 0.0);"
	" float angle = radians(rotation[0]);"
	" vec3 axis = normalize(rotation.yzw);"
	" mat3 I = mat3(1.0);"
	" mat3 S = mat3( 0, -axis.z, axis.y, "
	" axis.z, 0, -axis.x, "
	" -axis.y, axis.x, 0);"
	" mat3 uuT = outerProduct(axis, axis);"
	" mat3 rot = uuT + cos(angle)*(I - uuT) + sin(angle)*S; "
	" pos *= scale;"
	" pos *= rot;"
	" pos += translation;"
	" fColor = vec4(scale, scale, scale, 1);"
	" gl_Position = vec4(pos, 1);"
	"}"
;

const char* fShader = {
	"#version 330 core\n"
	"uniform Uniforms {"
	" vec3 translation;"
	" float scale;"
	" vec4 rotation;"
	" bool enabled;"
	"};"
	"in vec4 fColor;"
	"out vec4 color;"
	"void main()"
	"{"
	" color = fColor;"
	"}"
};

const char* t11 = "123\n"
"2323\n"
"2323\n"
"2555\n"
"51232\n";

#endif