/**
* @file BasicComponents.hpp
* @brief 座標や速度などの基本的なコンポーネント群です。
* @author tonarinohito
* @date 2018/10/05
* @par History
- 2018/12/19 tonarinohito
-# Canvas追加
*/
#pragma once
#include "../ECS/ECS.hpp"
#include "../Utility/Vec.hpp"
#include <DxLib.h>
#include <functional>
namespace ECS
{
	/*!
	@brief  座標です。データの型はVec2です
	*/
	struct Position final : public ComponentData
	{
		Vec2 val;
		Position() = default;
		explicit Position(const Vec2& v) :val(v) {}
		explicit Position(const float& x, const float& y) :val(x, y) {}

	};

	/*!
	@brief  回転値です。データの型はfloatです
	*/
	struct Rotation final : public ComponentData
	{
		float val;
		Rotation() = default;
		explicit Rotation(const float& r) : val(r) {}

	};
	/*!
	@brief  x,y方向の拡大率です。データの型はVec2です
	*/
	struct Scale final : public ComponentData
	{
		Vec2 val;
		Scale() = default;
		explicit Scale(const Vec2& scale) : val(scale) {}
		explicit Scale(const float& scale) : val(scale, scale) {}
		explicit Scale(const float& scaleX, const float& scaleY) : val(scaleX, scaleY) {}
	};
	/*!
	@brief  速度です。データの型はVec2です
	*/
	struct Velocity final : public ComponentData
	{
		Vec2 val;
		Velocity() = default;
		explicit Velocity(const Vec2& v) :val(v) {}
		explicit Velocity(const float& x, const float& y) : val(x, y) {}

	};
	/*!
	@brief  向きです。データの型はenum class Dirです
	*/
	struct Direction final : public ComponentData
	{
		enum class Dir : short
		{
			RIGHT,
			LEFT,
			UP,
			DOWN
		};
		Dir val;
		explicit Direction() : val(Dir::RIGHT) {};

	};
	/*!
	@brief 重力です。データの型はfloatです
	*/
	struct Gravity final : public ComponentData
	{
		static constexpr float DEFAULT = 9.8f / 60 / 60 * 32 * 3;
		float val;
		Gravity() :val(DEFAULT) {};
		explicit Gravity(const float g) :val(g) {}
	};

	/*!
	@brief  線分です。データの型は始点、終点ともにVec2です
	*/
	struct LineData final : public ComponentData
	{
		Vec2 p1;
		Vec2 p2;
		LineData() = default;
		explicit LineData(const Vec2& start, const Vec2& end) :
			p1(start),
			p2(end)
		{}
	};

	/*
	@brief Entityに重力を加えます。
	また簡易的な衝突応答処理も含まれますが、これは明示的に呼び出してください
	@details Gravity, Velocity, Positionが必要です。衝突応答を行う場合はColliderが必要です
	@TODO 現状だと1つのグループとの衝突応答しかできないのでこれを別のコンポーネントにするかもしれない
	*/
	class Physics final : public ComponentSystem
	{
	private:

		Gravity* gravity_ = nullptr;
		Velocity* velocity_ = nullptr;
		Position* pos_ = nullptr;
		std::vector<Entity*> otherEntity_{};
		std::function<bool(const Entity&, const Entity&)> collisionFunc_;
		void checkMove(Vec2& pos, Vec2& velocity)
		{
			Vec2 pointEntityMove(velocity);
			//横軸に対する移動
			while (pointEntityMove.x != 0.f)
			{
				float preX = pos.x;

				if (pointEntityMove.x >= 1)
				{
					pos.x += 1; pointEntityMove.x -= 1;
				}
				else if (pointEntityMove.x <= -1)
				{
					pos.x -= 1; pointEntityMove.x += 1;
				}
				else
				{
					pos.x += pointEntityMove.x;
					pointEntityMove.x = 0;
				}
				for (const auto& it : otherEntity_)
				{
					if (collisionFunc_(*owner, *it))
					{
						velocity_->val.x = 0;
						pos.x = preX;		//移動をキャンセル
						break;
					}
				}

			}
			//縦軸に対する移動
			while (pointEntityMove.y != 0.f)
			{
				float preY = pos.y;
				if (pointEntityMove.y >= 1)
				{
					pos.y += 1; pointEntityMove.y -= 1;
				}
				else if (pointEntityMove.y <= -1)
				{
					pos.y -= 1; pointEntityMove.y += 1;
				}
				else
				{
					pos.y += pointEntityMove.y;
					pointEntityMove.y = 0;
				}
				for (const auto& it : otherEntity_)
				{
					if (collisionFunc_(*owner, *it))
					{
						velocity_->val.y = 0;
						pos.y = preY;		//移動をキャンセル
						break;
					}
				}
			}
		}
	public:
		void initialize() override
		{
			if (!owner->hasComponent<Gravity>())
			{
				owner->addComponent<Gravity>();
			}
			if (!owner->hasComponent<Velocity>())
			{
				owner->addComponent<Velocity>();
			}
			velocity_ = &owner->getComponent<Velocity>();
			gravity_ = &owner->getComponent<Gravity>();
			pos_ = &owner->getComponent<Position>();
		}
		void update() override
		{
			velocity_->val.y += gravity_->val;
			checkMove(pos_->val, velocity_->val);
		}
		void setVelocity(const float& x, const float& y)
		{
			velocity_->val.x = x;
			velocity_->val.y = y;
		}
		void setGravity(const float& g = Gravity::DEFAULT)
		{
			gravity_->val = g;
		}
		//!あたり判定の関数をセットする
		void setCollisionFunction(std::function<bool(const Entity&, const Entity&)> func)
		{
			collisionFunc_ = func;
		}
		//!引数に指定したEntityにめり込まないようにする
		void pushOutEntity(std::vector<Entity*>&  e)
		{
			otherEntity_ = e;
		}
	};

	/*!
	@brief PositionとRotationとScaleの親子をsetParent()で作ります
	@detail 親子関係を作ると生のPosition等のデータを直接変更できなくなります
	- このコンポーネントがある場合は、translate系メソッドで動かすことができます
	*/ 
	class Transform final : public ComponentSystem
	{
	private:
		Vec2 initPos_;
		float initRota_ = 0;
		Vec2 initScale_{1.f,1.f};
		Vec2 offsetPos_;
		float offsetRota_ = 0;
		Vec2 offsetScale_;
		Position* pos_ = nullptr;
		Rotation* rota_ = nullptr;
		Scale* scale_ = nullptr;
		Entity* parent_ = nullptr;
	
	public:
		Transform() = default;
		Transform(const Vec2& pos):
			initPos_(pos)
		{}
		Transform(const Vec2& pos, const Vec2& scale) :
			initPos_(pos),
			initRota_(0.f),
			initScale_(scale)
		{}
		Transform(const Vec2& pos, const Vec2& scale, const float& rotation) :
			initPos_(pos),
			initRota_(rotation),
			initScale_(scale)
		{}

		void initialize() override
		{
			if (!owner->hasComponent<Position>())
			{
				owner->addComponent<Position>(initPos_);
			}
			if (!owner->hasComponent<Rotation>())
			{
				owner->addComponent<Rotation>(initRota_);
			}
			if (!owner->hasComponent<Scale>())
			{
				owner->addComponent<Scale>(initScale_);
			}
			pos_ = &owner->getComponent<Position>();
			rota_ = &owner->getComponent<Rotation>();
			scale_ = &owner->getComponent<Scale>();
		}

		void update() override
		{
			if (parent_ != nullptr)
			{
				pos_->val = parent_->getComponent<Position>().val.offsetCopy(offsetPos_);
				scale_->val = parent_->getComponent<Scale>().val.offsetCopy(offsetScale_);
				rota_->val = parent_->getComponent<Rotation>().val + offsetRota_;
			}
		}

		/*このEntityに親を設定します
		@details 親のEntityにもTransformが必要です
		- 親を設定するとこのEntityは生のPosition等のデータを直接変更できなくなります
		- 親との縁を切る場合はnullptrを指定してください
		- 設定後はsetRelative系のメソッドやtranslate系のメソッドで動かしてください
		*/
		void setParent(Entity* pEntity)
		{
			if (pEntity == nullptr)
			{
				parent_ = nullptr;
				return;
			}
			if (pEntity->hasComponent<Transform>())
			{
				parent_ = pEntity;
				offsetPos_ = pos_->val - parent_->getComponent<Position>().val;
				offsetRota_ = rota_->val - parent_->getComponent<Rotation>().val;
				offsetScale_ = scale_->val - parent_->getComponent<Scale>().val;
			}
			else
			{
				DOUT << "parent has not Transform" << std::endl;
			}
		}

		/*Entityをtranslation分移動します
		@param translation 移動量
		*/
		void translatePosition(const Vec2& translation)
		{
			if (parent_)
			{
				offsetPos_ += translation;
			}
			else
			{
				pos_->val += translation;
			}
		}

		/*Entityをtranslation分回転します
		@param translation 回転量
		*/
		void translateRotation(const float& translation)
		{
			if (parent_)
			{
				offsetRota_ += translation;
			}
			else
			{
				rota_->val += translation;
			}
		}

		/*Entityをtranslation分拡大します
		@param translation 拡大量
		*/
		void translateScale(const Vec2& translation)
		{
			if (parent_)
			{
				offsetScale_ += translation;
			}
			else
			{
				scale_->val += translation;
			}
		}

		//!Entityの相対座標を設定します
		void setRelativePosition(const float& x, const float& y)
		{
			offsetPos_.x = x;
			offsetPos_.y = y;
		}
		//!Entityの相対座標を設定します
		void setRelativePosition(const Vec2& setPos)
		{
			offsetPos_.x = setPos.x;
			offsetPos_.y = setPos.y;
		}
		//!Entityの相対回転率を設定します
		void setRelativeRotation(const float& r)
		{
			offsetRota_ = r;
		}
		//!Entityの相対拡大率を設定します
		void setRelativeScale(const float& scaleX, const float& scaleY)
		{
			offsetScale_.x = scaleX;
			offsetScale_.y = scaleY;
		}
		//!Entityの相対拡大率を設定します
		void setRelativeScale(const Vec2& scale)
		{
			offsetScale_.x = scale.x;
			offsetScale_.y = scale.y;
		}
	};

	/*!
	@brief UI等の配置に適したコンポーネントです
	@details Transformが必要です。
	- Canvasに追従する形で子のエンティティは動きます
	*/
	class Canvas final : public ComponentSystem
	{
	private:
		//ScaleとRotationは加算値でPositonは相対座標になる
		std::vector<std::tuple<Entity*, Position, Scale, Rotation>> e_{};
	public:
		Canvas() = default;
		//!Canvasに乗せるエンティティを指定します。
		void addChild(Entity* e)
		{
			e_.emplace_back
			(
				std::make_tuple
				(
					e,
					e->getComponent<Position>(),
					e->getComponent<Scale>(),
					e->getComponent<Rotation>()
				)
			);
			auto& scale = std::get<2>(e_.back());
			scale.val = 0;
			auto& rota = std::get<3>(e_.back());
			rota.val = 0;
		}
		/*
		@brief 子のエンティティの座標を指定した分だけずらします
		@param index 登録した番号
		@param offsetVal オフセット値
		*/
		void offsetChildPosition(const size_t index, const Vec2& offsetVal)
		{
			auto& pos = std::get<1>(e_.at(index));
			pos.val += offsetVal;
		}

		/*
		@brief 子のエンティティのスケールを指定した分だけ加算します
		@param index 登録した番号
		@param offsetVal オフセット値
		*/
		void offsetChildScale(const size_t index, const Vec2& offsetVal)
		{
			auto& scale = std::get<2>(e_.at(index));
			scale.val += offsetVal;
		}
		/*
		@brief 子のエンティティの回転率(ラジアン)を指定した分だけ加算します
		@param index 登録した番号
		@param offsetVal オフセット値
		*/
		void offsetChildRotation(const size_t index, const float& offsetVal)
		{
			auto& rota = std::get<3>(e_.at(index));
			rota.val += offsetVal;
		}
		void update() override
		{
			for (auto& it : e_)
			{
				auto child_entity = std::get<0>(it);
				auto pos = std::get<1>(it);
				auto scale = std::get<2>(it);
				auto rota = std::get<3>(it);

				child_entity->getComponent<Position>().val = pos.val + owner->getComponent<Position>().val;
				child_entity->getComponent<Scale>().val = owner->getComponent<Scale>().val + scale.val;
				child_entity->getComponent<Rotation>().val = owner->getComponent<Rotation>().val + rota.val;
			}
		}
	};

	/*!
	@brief コンストラクタで指定したフレーム後にEntityを殺します
	*/
	class KillEntity final : public ComponentSystem
	{
	private:
		int cnt_;
	public:
		KillEntity(const int span) :cnt_(span) {}

		void update() override
		{
			--cnt_;
			if (cnt_ <= 0)
			{
				owner->destroy();
			}
		}
		void kill()
		{
			cnt_ = 0;
		}
		void setKillLimit(const int limit)
		{
			cnt_ = limit;
		}
	};

	/*!
	@brief このコンポーネントがついているEntityにイベント(関数)を追加し,マネージャーから呼び出せるようにします
	* テンプレート引数   1戻り値,2タグとして扱う型(ただの識別子なので重複しなければなんでもよい、Defaultでvoid)
	*/
	template<class T, class Tag = void>
	class EventFunctionSystem final : public ComponentSystem
	{
	private:
		std::function<T(Entity*)> func_;
	public:
		EventFunctionSystem(std::function<T(Entity*)> addFunc) :func_(addFunc) {}

		void update() override
		{
			func_(owner);
		}

	};
}