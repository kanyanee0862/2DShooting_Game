/**
* @file Input.hpp
* @brief 入力関連の処理をまとめます
* @author tonarinohito
* @date 2018/10/05
*/
#pragma once
#include <memory>
#include <array>
#include <DxLib.h>
/*!
@brief キーイベントクラスです
*/
class Input final
{
public:
	enum class PadButton
	{
		LEFT, UP, RIGHT, DOWN, B, Y, A, X,
	};
private:
	Input() = delete;
	class Singleton final
	{
	private:
		//キーの入力状態を格納する
		int key_[256];
		bool isAnyInput = false;
		int padInput_ = 0;
		const static int PAD_KEY_NUM = 16;
		std::array<int, PAD_KEY_NUM> idArray_{};	    //どのボタンがどのボタンに割り当たっているか示す
		std::array<int, PAD_KEY_NUM> pad_{};			//16ボタンの入力格納
	public:
		
		Singleton()
		{
			idArray_[(int)PadButton::DOWN] = 0;
			idArray_[(int)PadButton::LEFT] = 1;
			idArray_[(int)PadButton::RIGHT] = 2;
			idArray_[(int)PadButton::UP] = 3;
			idArray_[(int)PadButton::A] = 4;
			idArray_[(int)PadButton::B] = 5;
			idArray_[(int)PadButton::X] = 6;
			idArray_[(int)PadButton::Y] = 7;
		}
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;

		/**
		* @brief キーの入力状態を更新します
		*/
		void updateKey()
		{
			char tmpKey[256];
			GetHitKeyStateAll(tmpKey);	//現在のキーの状態を格納
			isAnyInput = false;
			for (int i = 0; i < 256; ++i)
			{
				if (tmpKey[i] != 0)
				{
					++key_[i];
					isAnyInput = true;
				}
				else  //押されていなければ
				{
					key_[i] = 0;
					isAnyInput = isAnyInput || false;
				}
			}
			padInput_ = GetJoypadInputState(DX_INPUT_PAD1);	//パッドの入力状態
			for (int i = 0; i < 16; ++i)
			{
				if (padInput_ & (1 << i))
				{
					++pad_[i];
				}
				else
				{
					pad_[i] = 0;
				}
			}
		}
		/**
		* @brief キーの入力状態を取得します
		* @param keycode 調べたいキーコード
		* @return 押しているフレーム数。押されていない場合0が返ります
		*/
		[[nodiscard]] const int getKeyFrame(int keycode) const
		{
			return key_[keycode];
		}

		/**
		* @brief いずれかのキーが入力されていたらtrueを返す
		* @return 押されているか否か
		*/
		[[nodiscard]] const bool getIsAnyInput() const
		{
			return isAnyInput;
		}

		void vibration(const int pow, const int ms)
		{
			StartJoypadVibration(DX_INPUT_PAD1, pow, ms);
		}

		[[nodiscard]] const int getPadFrame(PadButton id) const
		{
			return pad_[idArray_[(int)id]];
		}
	};
	
public:
	inline static Singleton& Get()
	{
		static std::unique_ptr<Singleton> inst =
			std::make_unique<Singleton>();
		return *inst;
	}
};
