#ifndef __GameCore_H__
#define __GameCore_H__

namespace fw
{
    class Framework;

    class GameCore
    {
    protected:
        Framework* m_pFramework;

    public:
        GameCore(Framework* pFramework);

        virtual void Init() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Draw() = 0;
    };

} // namespace fw

#endif //__GameCore_H__
