#pragma once
#include <string>
#include "../ArcheType/ArcheType.hpp"
namespace ECS
{
	class BGMove :public ComponentSystem
	{
	public:
		void initialize() override
		{
			//owner‚©‚çposition‚ð“¾‚é
			pos_ = &owner->getComponent<Position>();
		}
		void update() override
		{
			//‰º‚É‚¸‚ç‚µ‚Ä‚¢‚­
			pos_->val.y++;
			if (pos_->val.y > System::SCREEN_HEIGHT)
			{
				pos_->val.y = -System::SCREEN_HEIGHT;
			}
		}
		
	private:
		Position* pos_;
	};

}