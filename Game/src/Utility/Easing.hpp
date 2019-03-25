/**
* @file Easing.hpp
* @brief Easingのまとめ
* @author tonarinohito
* @par History
- 2018/08/20 tonarinohito
-# 静的でないメソッド名をキャメルケースに変更
-# コメント文をDoxy形式に変更。[[nodiscard]]を追加
*/
#pragma once
#include <cmath>
#include <unordered_map>
#include "Counter.hpp"
typedef float(*Ease)(float, float);

class EasingFunctions final
{
private:
	static constexpr float PI = 3.141592653589793f;
public:
	static Ease GetFunction(const std::string& name) noexcept
	{
		const static std::unordered_map<std::string, Ease> funcs =
		{
			{ "LinearIn", LinearIn },
			{ "LinearOut", LinearOut },
			{ "LinearInOut", LinearInOut },
			{ "BackIn", BackIn },
			{ "BackOut", BackOut },
			{ "BackInOut", BackInOut },
			{ "BounceIn", BounceIn },
			{ "BounceOut", BounceOut },
			{ "BounceInOut", BounceInOut },
			{ "CircIn", CircIn },
			{ "CircOut", CircOut },
			{ "CircInOut", CircInOut },
			{ "CubicIn", CubicIn },
			{ "CubicOut", CubicOut },
			{ "CubicInOut", CubicInOut },
			{ "ElasticIn", ElasticIn },
			{ "ElasticOut", ElasticOut },
			{ "ElasticInOut", ElasticInOut },
			{ "ExpoIn", ExpoIn },
			{ "ExpoInOut", ExpoInOut },
			{ "QuadIn", QuadIn },
			{ "QuadOut", QuadOut },
			{ "QuadInOut", QuadInOut },
			{ "QuartIn", QuartIn },
			{ "QuartOut", QuartOut },
			{ "QuartInOut", QuartInOut },
			{ "QuintIn", QuintIn },
			{ "QuintOut", QuintOut },
			{ "QuintInOut", QuintInOut },
			{ "SineIn", SineIn },
			{ "SineOut", SineOut },
			{ "SineInOut", SineInOut },
		};
		return funcs.at(name);
	}

	static float LinearIn(float time, float duration)
	{
		return time / duration;
	}
	static float LinearOut(float time, float duration)
	{
		return time / duration;
	}
	static float LinearInOut(float time, float duration)
	{
		return time / duration;
	}

	static float BackIn(float time, float duration)
	{
		constexpr float s = 1.70158f;
		const float postFix = time /= duration;
		return (postFix)*time*((s + 1)*time - s);
	}
	static float BackOut(float time, float duration)
	{
		constexpr float s = 1.70158f;
		return ((time = time / duration - 1)*time*((s + 1)*time + s) + 1);
	}
	static float BackInOut(float time, float duration)
	{
		float s = 1.70158f;
		if ((time /= duration / 2) < 1) return 1.f / 2.f * (time*time*(((s *= (1.525f)) + 1)*time - s));
		const float postFix = time -= 2;
		return 1.f / 2.f * ((postFix)*time*(((s *= (1.525f)) + 1)*time + s) + 2);
	}

	static float BounceIn(float time, float duration)
	{
		return 1.f - BounceOut(duration - time, duration);
	}
	static float BounceOut(float time, float duration)
	{
		if ((time /= duration) < (1.f / 2.75f))
		{
			return 7.5625f*time*time;
		}
		else if (time < (2.f / 2.75f))
		{
			const float postFix = time -= (1.5f / 2.75f);
			return 7.5625f*(postFix)*time + .75f;
		}
		else if (time < (2.5 / 2.75))
		{
			const float postFix = time -= (2.25f / 2.75f);
			return 7.5625f*(postFix)*time + .9375f;
		}
		else
		{
			const float postFix = time -= (2.625f / 2.75f);
			return 7.5625f*(postFix)*time + .984375f;
		}
	}
	static float BounceInOut(float time, float duration)
	{
		if (time < duration / 2) return BounceIn(time * 2, duration) * 0.5f;
		else return BounceOut(time * 2 - duration, duration) * 0.5f + 0.5f;
	}

	static float CircIn(float time, float duration)
	{
		return -1.f * static_cast<float>((sqrt(1 - (time /= duration)*time) - 1));
	}
	static float CircOut(float time, float duration)
	{
		return static_cast<float>(sqrt(1 - (time = time / duration - 1)*time));
	}
	static float CircInOut(float time, float duration)
	{
		if ((time /= duration / 2) < 1) return -1.f / 2.f * static_cast<float>((sqrt(1 - time * time) - 1));
		return 1.f / 2.f * static_cast<float>((sqrt(1 - time * (time -= 2)) + 1));
	}

	static float CubicIn(float time, float duration)
	{
		return (time /= duration)*time*time;
	}
	static float CubicOut(float time, float duration)
	{
		return (time = time / duration - 1)*time*time + 1;
	}
	static float CubicInOut(float time, float duration)
	{
		if ((time /= duration / 2) < 1) return 1.f / 2.f * time*time*time;
		return 1.f / 2.f * ((time -= 2)*time*time + 2);
	}

	static float ElasticIn(float time, float duration)
	{
		if (time == 0) return 0.f;  if ((time /= duration) == 1) return 1.f;
		const float pointEntityMove = duration * 0.3f;
		constexpr float a = 1.f;
		const float s = pointEntityMove / 4;
		const float postFix = static_cast<float>(a*pow(2, 10 * (time -= 1)));
		return -static_cast<float>(postFix * sin((time*(duration)-s)*(2 * (PI)) / pointEntityMove));
	}
	static float ElasticOut(float time, float duration)
	{
		if (time == 0) return 0.f;  if ((time /= duration) == 1) return 1.f;
		const float pointEntityMove = duration * 0.3f;
		constexpr float a = 1.f;
		const float s = pointEntityMove / 4;
		return (static_cast<float>(a*pow(2, -10 * time) * sin((time*(duration)-s)*(2 * static_cast<float>(PI)) / pointEntityMove) + 1.f));
	}
	static float ElasticInOut(float time, float duration)
	{
		if (time == 0) return 0.f;  if ((time /= duration / 2) == 2) return 1.f;
		const float pointEntityMove = duration * (0.3f*1.5f);
		constexpr float a = 1.f;
		const float s = pointEntityMove / 4;

		if (time < 1) {
			const float postFix = static_cast<float>(a*pow(2, 10 * (time -= 1)));
			return -0.5f*static_cast<float>((postFix* sin((time*(duration)-s)*(2 * (PI)) / pointEntityMove)));
		}
		const float postFix = static_cast<float>(a*pow(2, -10 * (time -= 1)));
		return static_cast<float>(postFix * sin((time*(duration)-s)*(2 * static_cast<float>(PI)) / pointEntityMove)*.5f + 1.f);
	}

	static float ExpoIn(float time, float duration)
	{
		return (time == 0) ? 0.f : static_cast<float>(pow(2, 10 * (time / duration - 1)));
	}
	static float ExpoOut(float time, float duration)
	{
		return (time == duration) ? 1.f : static_cast<float>(-pow(2, -10 * time / duration) + 1);
	}
	static float ExpoInOut(float time, float duration)
	{
		if (time == 0) return 0.f;
		if (time == duration) return 1.f;
		if ((time /= duration / 2) < 1) return 1.f / 2.f * static_cast<float>(pow(2, 10 * (time - 1)));
		return 1.f / 2.f * (static_cast<float>(-pow(2, -10 * --time) + 2));
	}

	static float QuadIn(float time, float duration)
	{
		return (time /= duration)*time;
	}
	static float QuadOut(float time, float duration)
	{
		return -1.f * (time /= duration)*(time - 2);
	}
	static float QuadInOut(float time, float duration)
	{
		if ((time /= duration / 2) < 1) return ((1.f / 2.f)*(time*time));
		return -1.f / 2.f * (((time - 2)*(--time)) - 1);
	}

	static float QuartIn(float time, float duration)
	{
		return (time /= duration)*time*time*time;
	}
	static float QuartOut(float time, float duration)
	{
		return -1.f * ((time = time / duration - 1)*time*time*time - 1);
	}
	static float QuartInOut(float time, float duration)
	{
		if ((time /= duration / 2) < 1) return 1.f / 2.f * time*time*time*time;
		return -1.f / 2.f * ((time -= 2)*time*time*time - 2);
	}

	static float QuintIn(float time, float duration)
	{
		return (time /= duration)*time*time*time*time;
	}
	static float QuintOut(float time, float duration)
	{
		return (time = time / duration - 1)*time*time*time*time + 1;
	}
	static float QuintInOut(float time, float duration)
	{
		if ((time /= duration / 2) < 1) return 1.f / 2.f * time*time*time*time*time;
		return 1.f / 2.f * ((time -= 2)*time*time*time*time + 2);
	}

	static float SineIn(float time, float duration)
	{
		return -1.f * static_cast<float>(cos(time / duration * (PI / 2))) + 1.f;
	}
	static float SineOut(float time, float duration)
	{
		return static_cast<float>(sin(time / duration * (PI / 2)));
	}
	static float SineInOut(float time, float duration)
	{
		return -1.f / 2.f * static_cast<float>((cos(PI*time / duration) - 1));
	}
};

class Easing final
{
private:
	Counter_f time_;
	float vol_ = 0.f;
	Ease func_{};
	float startPoint_ = 0.f;
	float endPoint_ = 0.f;
	float durationTime_ = 0.f;

	void run()
	{
		time_.setEndTime(durationTime_);
		time_.add();
		vol_ = func_(time_.getCurrentCount(), durationTime_);
	}
public:
	//!コンストラクタ
	Easing() :
		time_(1, 1)
	{}
	//!コンストラクタ
	Easing(const Ease func, const float& start, const float& end, const float& duration) :
		time_(1, 1),
		func_(func),
		startPoint_(start),
		endPoint_(end),
		durationTime_(duration)
	{}

	/**
	* @brief イージングの初期化
	* @param em イージング動作の関数ポインタ
	* @param start 始点
	* @param end 終点
	* @param durationTime 継続時間(float)
	*/
	void init(const Ease func, const float& start, const float& end, const float& duration)
	{
		reset();
		func_ = (func);
		startPoint_ = (start);
		endPoint_ = (end);
		durationTime_ = (duration);
	}
	/**
	* @brief イージングの実行
	* @param em イージング動作の関数ポインタ
	* @param durationTime 継続時間(float)
	*/
	void run(const Ease em, const float durationTime)
	{
		time_.setEndTime(durationTime);
		time_.add();
		vol_ = em(time_.getCurrentCount(), durationTime);
	}
	
	/**
	* @brief 実行中のイージングの現在値を取得
	* @param startPoint 始点(float)
	* @param endPoint 終点(float)
	* @details run()を呼び出さなければ機能しない
	*/
	[[nodiscard]] const float getVolume(const float startPoint, const float endPoint)
	{
		return startPoint + (vol_ * (endPoint - startPoint));
	}

	/**
	* @brief 実行中のイージングの現在値を取得、毎フレーム呼ぶ
	*/
	[[nodiscard]] const float getVolume()
	{
		run();
		return startPoint_ + (vol_ * (endPoint_ - startPoint_));
	}
	//!イージングが終了したらtrueが返る
	[[nodiscard]] const bool isEaseEnd()
	{
		return time_.isMax();
	}

	//!イージングをリセットする
	void reset()
	{
		time_.reset();
	}

};