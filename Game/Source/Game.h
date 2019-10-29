#ifndef __Game_H__
#define __Game_H__

struct VertexFormat
{
    float x, y, u, v;
    unsigned char r, g, b, a;

    VertexFormat(float nx, float ny, unsigned char nr, unsigned char ng, unsigned char nb, unsigned char na, float nu, float nv)
    {
        x = nx;
        y = ny;
        r = nr;
        g = ng;
        b = nb;
        a = na;
        u = nu;
        v = nv;
    }
};

class Game : public fw::GameCore
{
protected:
    GLuint m_VBO;
    GLuint m_TextureID;
    fw::ShaderProgram* m_pShader;

public:
    Game(fw::Framework* pFramework);
    ~Game();

    virtual void Init() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__Game_H__
