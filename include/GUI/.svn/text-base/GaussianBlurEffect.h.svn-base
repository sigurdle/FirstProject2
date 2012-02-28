namespace System
{
namespace Gui
{

class GUIEXT GaussianBlurEffect : public CEffect
{
public:
	CTOR GaussianBlurEffect();
	CTOR GaussianBlurEffect(IEffect* input, float stdDeviationX, float stdDeviationY);

	virtual void Render(RenderTarget* rt, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection);

	virtual unsigned int GetInputCount();
	virtual IEffect* GetInput(unsigned int index);
	virtual void SetInput(unsigned int index, IEffect* input);

	float m_stdDeviationX;
	float m_stdDeviationY;

	IEffect* m_inEffect;

};

}
}
