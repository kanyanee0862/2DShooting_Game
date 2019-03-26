#pragma once
#include<string>
#include "../Components/BasicComponents.hpp"
#include "../Utility/Easing.hpp"

namespace ECS
{
	class EasingMove : public ComponentSystem
	{
	public:
		EasingMove()
			:mFunc(nullptr),
			mStart(0),
			mEnd(0),
			mDuration(0)
		{
		}
		void initialize() override
		{
			easing.init(mFunc, mStart, mEnd, mDuration);
			if (!owner->hasComponent<ECS::Position>())
			{
				owner->addComponent<ECS::Position>();
			}
			pos_ = &owner->getComponent<ECS::Position>();
		}
		void update() override
		{
			pos_->val.x = easing.getVolume();
			//�G�������Ă��鎞����������
			while (owner->isActive)
			{
				//Easing���I����āA�G�̈ʒu����ʂ��o�łȂ������瓮����
				if (easing.isEaseEnd && 
					owner->getComponent<ECS::Position>().val.y + 
					owner->getComponent<ECS::SpriteDraw>().getSize().y < System::SCREEN_HEIGHT)
				{
					easing.init(mFunc, mStart, mEnd, mDuration);
				}
			}
		
		}
		
		void SetEasing(EasingFunctions &function, const float start, const float end, const float duration)
		{
			mFunc = &function;
			mStart = start;
			mEnd = end;
			mDuration = duration;
		}
	private:
		Position* pos_ = nullptr;
		Easing easing;
		EasingFunctions* mFunc;
		float mStart;
		float mEnd;
		float mDuration;
	};
}
