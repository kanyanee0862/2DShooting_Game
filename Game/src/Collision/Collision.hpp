/**
* @file Collision.hpp
* @brief Collisionの式をまとめたファイルです
* @author tonarinohito
* @date 2018/10/05
*/
#pragma once
#include "../ECS/ECS.hpp"
#include "../Components/BasicComponents.hpp"
#include "../Components/Collider.hpp"

/**
* @brief Collisionの式をまとめたクラスです。
* -メソッドはすべてstaticです
* -引数にEntity*を指定するものはデフォルトのテンプレート引数が指定されています
*/
class Collision
{
public:
	/**
	* @brief 矩形と矩形のあたり判定
	* @param b1 Entity
	* @param b2 Entity
	* @return bool
	* @details テンプレート引数にはIBoxColliderを継承したコンポーネントを指定してください
	* テンプレート引数に指定したコンポーネント同士で衝突判定を行います
	*/
	template<class T = ECS::BoxCollider, class T2 = ECS::BoxCollider>
	[[nodiscard]] inline static bool BoxAndBox(const ECS::Entity* b1, const ECS::Entity* b2)
	{
		if (!b1->hasComponent<T>() || !b2->hasComponent<T2>())
		{
			return false;
		}
		const auto& box1 = b1->getComponent<T>();
		const auto& box2 = b2->getComponent<T2>();
		if (box1.x() < box2.x() + box2.w() &&
			box2.x() < box1.x() + box1.w() &&
			box1.y() < box2.y() + box2.h() &&
			box2.y() < box1.y() + box1.h())
		{
			return true;
		}
		return false;
	}
	/**
	* @brief 矩形と矩形のあたり判定
	* @param b1Pos 矩形1の座標
	* @param b1Size 矩形1のサイズ
	* @param b2Pos 矩形2の座標
	* @param b2Size 矩形2のサイズ
	* @return bool
	*/
	[[nodiscard]] inline static bool BoxAndBox(const Vec2& b1Pos, const Vec2& b1Size, const Vec2& b2Pos, const Vec2& b2Size) noexcept
	{
		if (b1Pos.x < b2Pos.x + b2Size.x &&
			b2Pos.x < b1Pos.x + b1Size.x &&
			b1Pos.y < b2Pos.y + b2Size.y &&
			b2Pos.y < b1Pos.y + b1Size.y)
		{
			return true;
		}
		return false;
	}
	
	/**
	* @brief 円と円のあたり判定
	* @param e1 Entity
	* @param e2 Entity
	* @return bool
	* @details テンプレート引数にはICircleColliderを継承したコンポーネントを指定してください
	* テンプレート引数に指定したコンポーネント同士で衝突判定を行います
	*/
	template<class T = ECS::CircleCollider, class T2 = ECS::CircleCollider>
	[[nodiscard]] inline static bool CircleAndCircle(const ECS::Entity* e1, const ECS::Entity* e2)
	{
		if (!e1->hasComponent<T>() || !e2->hasComponent<T2>())
		{
			return false;
		}
		const auto& c1 = e1->getComponent<T>();
		const auto& c2 = e2->getComponent<T2>();
		if (((c1.x() - c2.x()) *(c1.x() - c2.x())) + ((c1.y() - c2.y()) * (c1.y() - c2.y())) <=
			(c1.radius() + c2.radius()) * (c1.radius() + c2.radius()))
		{
			return true;
		}
		return false;
	}

	/**
	* @brief 円と円のあたり判定
	* @param c1Pos 円1の座標
	* @param c1r 円1の半径
	* @param c2Pos 円2の座標
	* @param c2r 円2の半径
	* @return bool
	*/
	[[nodiscard]] inline static bool CircleAndCircle(const Vec2& c1Pos, const float& c1r, const Vec2& c2Pos, const float& c2r) noexcept
	{
		if (((c1Pos.x - c2Pos.x) *(c1Pos.x - c2Pos.x)) + ((c1Pos.y - c2Pos.y) * (c1Pos.y - c2Pos.y)) <=
			(c1r + c2r) * (c1r + c2r))
		{
			return true;
		}
		return false;
	}
	/**
	* @brief 円と矩形のあたり判定
	* @param e1 Entity
	* @param e2 Entity
	* @details テンプレート第一引数にはICircleColliderを、第二引数にはIBoxCollider継承したコンポーネントを指定してください
	* テンプレート引数に指定したコンポーネント同士で衝突判定を行います
	* @return bool
	*/
	template<class T1 = ECS::CircleCollider,class T2 = ECS::BoxCollider>
	[[nodiscard]] inline static bool CircleAndBox(const ECS::Entity* e1, const ECS::Entity* e2) noexcept
	{
		if (!e1->hasComponent<T1>() || !e2->hasComponent<T2>())
		{
			return false;
		}
		const auto& c = e1->getComponent<T1>();
		const auto& b = e2->getComponent<T2>();
		if (c.x() + c.radius() <= b.x() ||
			c.y() + c.radius() <= b.y() ||
			b.x() + b.w() <= c.x() - c.radius() ||
			b.y() + b.h() <= c.y() - c.radius())
			return false;
		else
			return true;

	}
	/**
	* @brief 円と矩形のあたり判定
	* @param circlePos 円の座標
	* @param radius 円の半径
	* @param boxPos 矩形の座標
	* @param boxSize 矩形のサイズ
	* @return bool
	*/
	[[nodiscard]] inline static bool CircleAndBox(const Vec2& circlePos, const float& radius, const Vec2& boxPos, const Vec2& boxSize) noexcept
	{
		if (circlePos.x + radius <= boxPos.x ||
			circlePos.y + radius <= boxPos.y ||
			boxPos.x + boxSize.x <= circlePos.x - radius ||
			boxPos.y + boxSize.y <= circlePos.y - radius)
			return false;
		else
			return true;

	}

	/**
	* @brief 円と点の当たり判定
	* @param e1 Entity
	* @param e2 Entity
	* @details テンプレート第一引数にはICircleColliderを継承したコンポーネントを指定してください
	* テンプレート引数に指定したコンポーネント同士で衝突判定を行います
	* @return bool
	*/
	template<class T = ECS::CircleCollider, class T2 = ECS::Position>
	[[nodiscard]] inline static bool CircleAndPoint(const ECS::Entity* e1, const ECS::Entity* e2)
	{
		if (!e1->hasComponent<T>() || !e2->hasComponent<T2>())
		{
			return false;
		}
		const auto& circle = e1->getComponent<T>();
		const auto& point = e2->getComponent<T2>();

		Vec2 buttonPos = Vec2(circle.x(), circle.y());
		Vec2 distance = buttonPos - point.val();
		if (distance.Length() <= circle.radius())
		{
			return true;
		}
		return false;
	}

	/**
	* @brief 円と点の当たり判定
	* @param circlePos 円の座標
	* @param circleRadius 円の半径
	* @param pointPos 点の座標
	* @return bool
	*/
	[[nodiscard]] inline static bool CircleAndPoint(const Vec2& circlePos, const float& circleRadius, const Vec2& pointPos) noexcept
	{
		Vec2 distance = circlePos - pointPos;
		if (distance.length() <= circleRadius)
		{
			return true;
		}
		return false;
	}

	/**
	* @brief 線分と線分の当たり判定
	* @param e1 Entity
	* @param e2 Entity
	* LineDataが必要です
	* テンプレート引数に指定したコンポーネント同士で衝突判定を行います
	* @return bool
	*/
	template<class T1 = ECS::LineData, class T2 = ECS::LineData>
	[[nodiscard]] inline static bool LineAndLine(const ECS::Entity* e1, const ECS::Entity* e2)
	{
		if (!e1->hasComponent<T1>() || !e2->hasComponent<T2>())
		{
			return false;
		}
		const auto& l1 = e1->getComponent<T1>();
		const auto& l2 = e2->getComponent<T2>();
		{
			const float baseX = l2.p2.x - l2.p1.x;
			const float baseY = l2.p2.y - l2.p1.y;
			const float sub1X = l1.p1.x - l2.p1.x;
			const float sub1Y = l1.p1.y - l2.p1.y;
			const float sub2X = l1.p2.x - l2.p1.x;
			const float sub2Y = l1.p2.y - l2.p1.y;

			const float bs1 = baseX * sub1Y - baseY * sub1X;
			const float bs2 = baseX * sub2Y - baseY * sub2X;
			const float re = bs1 * bs2;
			if (re > 0)
			{
				return false;
			}
		}
		{
			const float baseX = l1.p2.x - l1.p1.x;
			const float baseY = l1.p2.y - l1.p1.y;
			const float sub1X = l2.p1.x - l1.p1.x;
			const float sub1Y = l2.p1.y - l1.p1.y;
			const float sub2X = l2.p2.x - l1.p1.x;
			const float sub2Y = l2.p2.y - l1.p1.y;

			const float bs1 = baseX * sub1Y - baseY * sub1X;
			const float bs2 = baseX * sub2Y - baseY * sub2X;
			const float re = bs1 * bs2;
			if (re > 0)
			{
				return false;
			}
		}
		return true;
	}
	/**
	* @brief 線分と線分の当たり判定
	* @param l1 線分1
	* @param l2 線分2
	* @return bool
	*/
	[[nodiscard]] inline static bool LineAndLine(const ECS::LineData& l1, const ECS::LineData& l2) noexcept
	{
		{
			const float baseX = l2.p2.x - l2.p1.x;
			const float baseY = l2.p2.y - l2.p1.y;
			const float sub1X = l1.p1.x - l2.p1.x;
			const float sub1Y = l1.p1.y - l2.p1.y;
			const float sub2X = l1.p2.x - l2.p1.x;
			const float sub2Y = l1.p2.y - l2.p1.y;

			const float bs1 = baseX * sub1Y - baseY * sub1X;
			const float bs2 = baseX * sub2Y - baseY * sub2X;
			const float re = bs1 * bs2;
			if (re > 0)
			{
				return false;
			}
		}
		{
			const float baseX = l1.p2.x - l1.p1.x;
			const float baseY = l1.p2.y - l1.p1.y;
			const float sub1X = l2.p1.x - l1.p1.x;
			const float sub1Y = l2.p1.y - l1.p1.y;
			const float sub2X = l2.p2.x - l1.p1.x;
			const float sub2Y = l2.p2.y - l1.p1.y;

			const float bs1 = baseX * sub1Y - baseY * sub1X;
			const float bs2 = baseX * sub2Y - baseY * sub2X;
			const float re = bs1 * bs2;
			if (re > 0)
			{
				return false;
			}
		}
		return true;
	}
	/**
	* @brief 円と線分の当たり判定
	* @param e1 Entity
	* @param e2 Entity
	* @details テンプレート第一引数にはICircleColliderを継承したコンポーネントを指定してください
	* テンプレート引数に指定したコンポーネント同士で衝突判定を行います
	* @return bool
	*/
	template<class T1 = ECS::CircleCollider, class T2 = ECS::LineData>
	[[nodiscard]] inline static bool CirecleAndLine(const ECS::Entity* e1, const ECS::Entity* e2)
	{

		if (!e1->hasComponent<T1>() || !e2->hasComponent<T2>())
		{
			return false;
		}
		const auto& c = e1->getComponent<T1>();
		const auto& l = e2->getComponent<T2>();

		const Vec2 A = { c.x() - l.p1.x, c.y() - l.p1.y };		//線分の始点から円の中心点までのベクトルA
		const Vec2 B = { l.p2.x - l.p1.x,l.p2.y - l.p1.y };		//線分の始点から線分の終点までのベクトルB
		const Vec2 C = { c.x() - l.p2.x, c.y() - l.p2.y };		//線分の終点から円の中心点までのベクトルC

		//円の中心が線分の中（端点の間）に入っている
		if (Vec2::Dot(A, B) * Vec2::Dot(B, C) <= 0)
		{
			//線分のベクトル（ベクトルB）を単位ベクトルに変換
			Vec2 temp = B.getNormalize();
			//円の中心と線分の距離を外積を使って計算
			float dist = Vec2::Cross(A, temp);
			//外積がマイナス値だったら符号を変える
			if (dist < 0) { dist *= -1; }
			//半径との比較
			if (dist <= c.radius())
			{
				return true;
			}
		}
		else
		{
			//端点との距離をそれぞれ計算
			if (A.length() <= c.radius() || C.length() <= c.radius())
			{
				return true;
			}
		}
		return false;
	}

	/**
	* @brief 円と線分の当たり判定
	* @param pos 円の座標
	* @param r	 半径
	* @param l   線分
	* @return bool
	*/
	[[nodiscard]] inline static bool CirecleAndLine(const Vec2& pos,const float r, const ECS::LineData& l) noexcept
	{
		const Vec2 A = { pos.x - l.p1.x,pos.y - l.p1.y };		//線分の始点から円の中心点までのベクトルA
		const Vec2 B = { l.p2.x - l.p1.x,l.p2.y - l.p1.y };		//線分の始点から線分の終点までのベクトルB
		const Vec2 C = { pos.x - l.p2.x, pos.y - l.p2.y };		//線分の終点から円の中心点までのベクトルC

		//円の中心が線分の中（端点の間）に入っている
		if (Vec2::Dot(A, B) * Vec2::Dot(B, C) <= 0)
		{
			//線分のベクトル（ベクトルB）を単位ベクトルに変換
			Vec2 temp = B.getNormalize();
			//円の中心と線分の距離を外積を使って計算
			float dist = Vec2::Cross(A, temp);
			//外積がマイナス値だったら符号を変える
			if (dist < 0) { dist *= -1; }
			//半径との比較
			if (dist <= r)
			{
				return true;
			}
		}
		else
		{
			//端点との距離をそれぞれ計算
			if (A.length() <= r || C.length() <= r)
			{
				return true;
			}
		}
		return false;
	}
};
