#pragma once
#include <string>
using namespace std;

class ShaderManager
{
public:
	
	~ShaderManager();

	static ShaderManager* getInstance();
	void loadDefaultShader();

	void LoadVertexShader(const char* filename);
	void LoadPixelShader(const char* filename);

	void LoadShader(const char* vs, const char* ps);

private:
	ShaderManager();

	static ShaderManager* m_pInstance;
};

