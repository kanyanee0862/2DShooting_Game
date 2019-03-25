/**
* @file JsonIO.hpp
* @brief picojsonの簡単なラッパーです
* @author tonarinohito
* @date 2019/03/14
*/
#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <type_traits>
#include "picojson.h"

using number = double;
using jsonArray =  picojson::array;

//!Jsonをロードし、値を取得するためのクラスです
class JsonRead final
{
private:
	picojson::value v_;
public:
	JsonRead() = default;
	JsonRead(const std::string& path)
	{
		// JSONデータの読み込み。
		std::stringstream ss;
		std::ifstream ifs(path, std::ios::in);
		if (ifs.fail())
		{
			std::cerr << "failed to read json" << std::endl;
		}
		ss << ifs.rdbuf();
		ifs.close();

		//JSONデータを解析する。
		const std::string err = picojson::parse(v_, ss); 
		if (err.empty() == false)
		{
			std::cerr << err << std::endl;
		}
	}

	//!jsonファイルを読み込みます
	bool load(const std::string& path)
	{
		// JSONデータの読み込み。
		std::stringstream ss;
		std::ifstream ifs(path, std::ios::in);
		if (ifs.fail())
		{
			return false;
		}
		ss << ifs.rdbuf();
		ifs.close();

		//JSONデータを解析する。
		const std::string err = picojson::parse(v_, ss);
		if (!err.empty())
		{
			return false;
		}
		return true;
	}

	/*
	読み込んだjsonファイルから値を取得します
	@param name パラメータ名
	@retrun 指定したパラメータ
	@details number,bool,std::stringが指定できます。テンプレート引数で数値型はnumberを指定してください。
	*/
	template <class T>
	[[nodiscard]] const T getParameter(const std::string& name)
	{
		picojson::object obj_ = v_.get<picojson::object>();
		return obj_[name].get<T>();
	}

	/*
	読み込んだjsonファイルから値を取得します
	@param name パラメータ名
	@retrun 指定したパラメータ(floatにキャスト済み)
	*/
	template <>
	[[nodiscard]] const float getParameter(const std::string& name)
	{
		picojson::object obj_ = v_.get<picojson::object>();
		return static_cast<float>(obj_[name].get<number>());
	}

	/*
	読み込んだjsonファイルから値を取得します
	@param name パラメータ名
	@retrun 指定したパラメータ(intにキャスト済み)
	*/
	template <>
	[[nodiscard]] const int getParameter(const std::string& name)
	{
		picojson::object obj_ = v_.get<picojson::object>();
		return static_cast<int>(obj_[name].get<number>());
	}

	/*
	読み込んだjsonファイルから配列の値を取得します
	@param name パラメータ名
	@param index 配列の要素番号
	@retrun 指定したパラメータ
	@details number,bool,std::stringが指定できます。テンプレート引数で数値型はnumberを指定してください。
	*/
	template <class T>
	[[nodiscard]] const T getParameter(const std::string& name, const size_t index)
	{
		picojson::object obj_ = v_.get<picojson::object>();
		const auto& arr = obj_[name].get<jsonArray>().at(index);
		return arr.get<T>();
	}

	/*
	読み込んだjsonファイルから配列の値を取得します
	@param[in] name パラメータ名
	@param[out] data 配列のポインタ
	@param[in] maxIndex 最大要素数
	@details number,bool,std::stringが指定できます。テンプレート引数で数値型はnumberを指定してください。
	*/
	template <class T>
	const void getArrayParameter(const std::string& name, T* data, const size_t maxIndex)
	{
		picojson::object obj_ = v_.get<picojson::object>();
		const auto& arr = obj_[name].get<jsonArray>();
		assert(std::size(arr) == maxIndex);
		size_t i = 0;
		for (const auto& it_j : arr)
		{
			data[i] = it_j.get<T>();
			++i;
			if (i > maxIndex)
			{
				break;
			}
		}
	}

	/*
	読み込んだjsonファイルから値を取得します
	@param objectName 構造体名
	@param name パラメータ名
	@retrun 指定したパラメータ
	@details number,bool,std::stringが指定できます。テンプレート引数で数値型はnumberを指定してください。
	*/
	template <class T>
	[[nodiscard]] const T getParameter(const std::string& objectName, const std::string& name)
	{
		picojson::object obj_ =  v_.get<picojson::object>()[objectName].get<picojson::object>();
		return obj_[name].get<T>();
	}

	/*
	読み込んだjsonファイルから値を取得します
	@param objectName 構造体名
	@param name パラメータ名
	@retrun 指定したパラメータ(floatにキャスト済み)
	*/
	template <>
	[[nodiscard]] const float getParameter (const std::string& objectName, const std::string& name)
	{
		picojson::object obj_ = v_.get<picojson::object>()[objectName].get<picojson::object>();
		return static_cast<float>(obj_[name].get<number>());
	}

	/*
	読み込んだjsonファイルから値を取得します
	@param objectName 構造体名
	@param name パラメータ名
	@retrun 指定したパラメータ(intにキャスト済み)
	*/
	template <>
	[[nodiscard]] const int getParameter(const std::string& objectName, const std::string& name)
	{
		picojson::object obj_ = v_.get<picojson::object>()[objectName].get<picojson::object>();
		return static_cast<int>(obj_[name].get<number>());
	}

	/*
	読み込んだjsonファイルから配列の値を取得します
	@param objectName 構造体名
	@param name パラメータ名
	@param index 配列の要素番号
	@retrun 指定したパラメータ
	@details number,bool,std::stringが指定できます。テンプレート引数で数値型はnumberを指定してください。
	*/
	template <class T>
	[[nodiscard]] const T getParameter(const std::string& objectName, const std::string& name, const size_t index)
	{
		picojson::object obj_ = v_.get<picojson::object>()[objectName].get<picojson::object>();
		const auto& arr = obj_[name].get<jsonArray>().at(index);
		return arr.get<T>();
	}

	/*
	読み込んだjsonファイルから配列の値を取得します
	@param objectName 構造体名
	@param[in] name パラメータ名
	@param[out] data 配列のポインタ
	@param[in] maxIndex 最大要素数
	@details number,bool,std::stringが指定できます。テンプレート引数で数値型はnumberを指定してください。
	*/
	template <class T>
	const void getArrayParameter(const std::string& objectName, const std::string& name, T* data , const size_t maxIndex)
	{
		picojson::object obj_ = v_.get<picojson::object>()[objectName].get<picojson::object>();
		const auto& arr = obj_[name].get<jsonArray>();
		assert(std::size(arr) == maxIndex);
		size_t i = 0;
		for (const auto& it_j : arr)
		{
			data[i] = it_j.get<T>();
			++i;
			if (i > maxIndex)
			{
				break;
			}
		}
	}

};

//!Jsonを作って書き出すためのクラスです
class JsonWrite final
{
private:
	picojson::object obj;
	
public:

	/*
	書き込んだ文字列をそのままjsonファイルに出力します
	@param str 書き出したいjsonの文字列
	@param path 書き出し先
	*/
	void write(const std::string& str, const std::string& path)
	{
		picojson::value val;
		std::string err;
		picojson::parse(val, str.c_str(), str.c_str() + strlen(str.c_str()), &err);
		if (!err.empty())
		{
			std::cerr << err << std::endl;
		}
		std::string out = val.serialize();
		//書き出し
		std::ofstream outputfile(path);
		outputfile << out;
		outputfile.close();

	}

	/*
	jsonファイルに出力したいパラメータを挿入します。書き出しは行いません
	@param name パラメータ名
	@param value 値
	@details number,bool,std::stringが指定できます。テンプレート引数で数値型はnumberを指定してください。
	*/
	template<class T>
	void insert(const std::string& name, const T& value)
	{
		//データの追加
		obj.emplace(std::make_pair(name, picojson::value(static_cast<T>(value))));
	}

	/*
	jsonファイルに出力したい配列パラメータを挿入します。書き出しは行いません
	@param name パラメータ名
	@param value 指定した型のstd::vector
	@details number,bool,std::stringが指定できます。テンプレート引数で数値型はnumberを指定してください。
	*/
	template<class T>
	void insertArray(const std::string& name, const std::vector<T>& value)
	{
		picojson::array arr;
		for (const auto& it : value)
		{
			arr.emplace_back(it);
		}
		
		//データの追加
		obj.emplace(std::make_pair(name, arr));
	}

	//!設定したJsonファイルを書き出します
	void output(const std::string& path)
	{
		//文字列にするためにvalueを使用
		picojson::value val(obj);
		std::string out = val.serialize();
		//書き出し
		std::ofstream outputfile(path);
		outputfile << out;
		outputfile.close();
	}
};