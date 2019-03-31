#pragma once
#include<string>
#include<unordered_map>
#include "../Components/BasicComponents.hpp"
#include "../Utility/Easing.hpp"
#include "../Components/Renderer.hpp"
namespace ECS
{
	class EasingMove : public ComponentSystem
	{
	public:
		EasingMove()
			:mStart(0),
			mEnd(0),
			mDuration(0)
		{
		}
		void initialize() override
		{
			//easing.init(mFunc, mStart, mEnd, mDuration);
			if (!owner->hasComponent<ECS::Position>())
			{
				owner->addComponent<ECS::Position>();
			}
			pos_ = &owner->getComponent<ECS::Position>();
			//easingFunc = &EasingFunctions::GetFunction;
			easing->init(mFunc, mStart, mEnd, mDuration);
		}
		void update() override
		{
			pos_->val.x = easing->getVolume();
			//“G‚ª¶‚«‚Ä‚¢‚éŽž‚¾‚¯“®‚¯‚é
			while (owner->isActive())
			{
				//Easing‚ªI‚í‚Á‚ÄA“G‚ÌˆÊ’u‚ª‰æ–Ê‚ªo‚Å‚È‚©‚Á‚½‚ç“®‚©‚·
				if (easing->isEaseEnd() && 
					owner->getComponent<ECS::Position>().val.y + 
					owner->getComponent<ECS::SpriteDraw>().getSize().y < System::SCREEN_HEIGHT)
				{
					easing->init(mFunc, mStart, mEnd, mDuration);
				}
			}
		
		}
		
		void SetEasing(const std::string funcname, const float start, const float end, const float duration)
		{
			mFunc = EasingFunctions::GetFunction(funcname);
			mStart = start;
			mEnd = end;
			mDuration = duration;
		}
	private:
		Position* pos_ = nullptr;
		/*Easing (*easingFunc)(const std::string& funcName);*/
		Easing* easing;
		float mStart;
		float mEnd;
		float mDuration;
		Ease mFunc{};
		
	};
}
